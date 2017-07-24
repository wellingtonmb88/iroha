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

#ifndef IROHA_YAC_HASH_PROVIDER_HPP
#define IROHA_YAC_HASH_PROVIDER_HPP

#include <functional>
#include <string>
#include <vector>
#include "consensus/yac/cluster_order.hpp"
#include "model/block.hpp"
#include "model/peer.hpp"

namespace iroha {
  namespace consensus {
    namespace yac {

      class YacHash {
       public:
        YacHash(std::string proposal, std::string block)
            : proposal_hash(proposal), block_hash(block) {}

        YacHash() = default;

        /**
         * Hash computed from proposal
         */
        std::string proposal_hash;

        /**
         * Hash computed from block;
         */
        std::string block_hash;

        bool operator==(const YacHash &obj) const {
          return proposal_hash == obj.proposal_hash and
                 block_hash == obj.block_hash;
        };

        bool operator!=(const YacHash &obj) const {
          return !this->operator==(obj);
        }
      };

      /**
       * Provide methods related to hash operations in ya consensus
       */
      class YacHashProvider {
        /**
         * Make hash from block
         * @param block - for hashing
         * @return hashed value of block
         */
        virtual YacHash makeHash(model::Block block) = 0;

        /**
         * Make ordering on cluster
         * @param hash
         * @param initial_order
         * @return cluster ordering based on hash and initial order
         */
        virtual ClusterOrdering order(
            YacHash hash, std::vector<model::Peer> initial_order) = 0;

        virtual ~YacHashProvider() = default;
      };
    }  // namespace yac
  }    // namespace consensus
}  // namespace iroha

namespace std {

  template <>
  struct hash<iroha::consensus::yac::YacHash> {
    std::size_t operator()(const iroha::consensus::yac::YacHash &obj) const {
      return std::hash<std::string>()(obj.proposal_hash + obj.block_hash);
    }
  };
}

#endif  // IROHA_YAC_HASH_PROVIDER_HPP
