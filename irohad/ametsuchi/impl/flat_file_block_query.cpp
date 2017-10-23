/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ametsuchi/impl/flat_file_block_query.hpp"

#include <deque>
#include "crypto/hash.hpp"
#include "model/commands/add_asset_quantity.hpp"
#include "model/commands/transfer_asset.hpp"

namespace iroha {
  namespace ametsuchi {
    FlatFileBlockQuery::FlatFileBlockQuery(FlatFile &block_store)
      : block_store_(block_store) {}

    rxcpp::observable<model::Block> FlatFileBlockQuery::getBlocks(
      uint32_t height, uint32_t count) {
      auto to = height + count;
      auto last_id = block_store_.last_id();
      if (to > last_id) {
        to = last_id;
      }
      if (height > to) {
        return rxcpp::observable<>::empty<model::Block>();
      }
      return rxcpp::observable<>::range(height, to).flat_map([this](auto i) {
        auto bytes = block_store_.get(i);
        return rxcpp::observable<>::create<model::Block>([this, bytes](auto s) {
          if (not bytes.has_value()) {
            s.on_completed();
            return;
          }
          auto document =
            model::converters::stringToJson(bytesToString(bytes.value()));
          if (not document.has_value()) {
            s.on_completed();
            return;
          }
          auto block = serializer_.deserialize(document.value());
          if (not block.has_value()) {
            s.on_completed();
            return;
          }
          s.on_next(block.value());
          s.on_completed();
        });
      });
    }

    rxcpp::observable<model::Block> FlatFileBlockQuery::getBlocksFrom(
      uint32_t height) {
      return getBlocks(height, block_store_.last_id());
    }

    rxcpp::observable<model::Block> FlatFileBlockQuery::getTopBlocks(
      uint32_t count) {
      auto last_id = block_store_.last_id();
      if (count > last_id) {
        count = last_id;
      }
      return getBlocks(last_id - count + 1, count);
    }

    rxcpp::observable<model::Transaction>
    FlatFileBlockQuery::getAccountTransactions(
      std::string account_id, model::Pager pager) {
      std::deque<model::Transaction> reverser;
      getBlocksFrom(1)
        .flat_map([](auto block) {
          return rxcpp::observable<>::iterate(block.transactions);
        })
        .take_while([&](auto tx) { return iroha::hash(tx) != pager.tx_hash; })
          // filter txs by specified creator after take_while until tx_hash
          // to deal with other creator's tx_hash
        .filter([account_id](auto tx) {
          return tx.creator_account_id == account_id;
        })
          // size of retrievable blocks and transactions should be restricted
          // in stateless validation.
        .take_last(pager.limit)
          // reverse transactions by pushing front of deque.
        .subscribe([&](auto tx) { reverser.push_front(tx); });
      return rxcpp::observable<>::iterate(reverser);
    }

    rxcpp::observable<model::Transaction>
    FlatFileBlockQuery::getAccountAssetTransactions(
      std::string account_id, std::vector<std::string> assets_id,
      model::Pager pager) {
      using iroha::model::TransferAsset;
      using iroha::model::AddAssetQuantity;

      const auto check_command = [&](auto const& command) -> bool {
        // TransferAsset
        if (const auto transfer =
          std::dynamic_pointer_cast<TransferAsset>(command)) {
          return (transfer->src_account_id == account_id or
                  transfer->dest_account_id == account_id) and
                 // size of commands should be restricted
                 // in stateless validation.
                 std::any_of(assets_id.begin(), assets_id.end(),
                             [&](auto const &a) {
                               return a == transfer->asset_id;
                             });
        }

        // AddAssetQuantity
        if (const auto add =
          std::dynamic_pointer_cast<AddAssetQuantity>(command)) {
          return add->account_id == account_id and
                 std::any_of(assets_id.begin(), assets_id.end(),
                             [&](auto const &a) {
                               return a == add->asset_id;
                             });
        }
        return false;
      };

      std::deque<model::Transaction> reverser;
      getBlocksFrom(1)
        .flat_map([](auto block) {
          return rxcpp::observable<>::iterate(block.transactions);
        })
          // local variables can be captured because this observable will be
          // subscribed in this function.
        .take_while([&](auto const &tx) {
          return iroha::hash(tx) != pager.tx_hash;
        })
        .filter([&](auto const &tx) {
          return std::any_of(tx.commands.begin(),
                             tx.commands.end(), check_command);
        })
          // size of retrievable blocks and transactions should be
          // restricted in stateless validation.
        .take_last(pager.limit)
          // reverse transactions by pushing front of deque.
        .subscribe([&](auto tx) { reverser.push_front(tx); });
      return rxcpp::observable<>::iterate(reverser);
    }

  }  // namespace ametsuchi
}  // namespace iroha
