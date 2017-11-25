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

#ifndef IROHA_INTERACTIVE_MULTISIG_HPP
#define IROHA_INTERACTIVE_MULTISIG_HPP

#include "client.hpp"
#include "interactive/interactive_common_cli.hpp"
#include "logger/logger.hpp"
#include "model/generators/query_generator.hpp"
#include "model/model_crypto_provider.hpp"

namespace iroha_cli {
  namespace interactive {
    class InteractiveMultiSigCli {
     public:
      /**
       * @param account_id creator's account identification
       * @param query_counter counter associated with creator's account
       */
      InteractiveMultiSigCli(
          const std::string &account_id,
          uint64_t query_counter,
          const CliClient &client,
          std::shared_ptr<iroha::model::ModelCryptoProvider> provider);
      /**
       * Run interactive query command line
       */
      void run();

     private:
      /**
       * Fetch from Iroha Peer multisig transactions related to account_id
       * @return MenuPoints with last transactions that need signature of
       * account
       */
      nonstd::optional<iroha::protocol::TransactionsResponse>
      fetchUncompletedTransactions();

      // ------- Client for Iroha Peer interaction -----

      CliClient client_;

      // ------- Query data -----------
      // Creator account id
      std::string creator_;

      // Local query counter of account creator_
      uint64_t query_counter_;

      // Query generator for new queries
      iroha::model::generators::QueryGenerator generator_;

      // Logger
      logger::Logger log_;

      // Crypto provider
      std::shared_ptr<iroha::model::ModelCryptoProvider> provider_;

      std::vector<iroha::model::Transaction> uncompleted_transactions;
    };
  }  // namespace interactive
}  // namespace iroha_cli

#endif  // IROHA_INTERACTIVE_MULTISIG_HPP
