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

#ifndef IROHA_MESSAGES_HPP
#define IROHA_MESSAGES_HPP

#include <vector>
#include "consensus/yac/yac_hash_provider.hpp"
#include "model/signature.hpp"

namespace iroha {
  namespace consensus {
    namespace yac {

      /**
       * VoteMessage represents voting for some block;
       */
      struct VoteMessage {
        YacHash hash;
        model::Signature signature;
      };

      /**
       * CommitMsg means consensus on cluster achieved.
       * All nodes deals on some solution
       */
      struct CommitMessage {
        CommitMessage() {}

        CommitMessage(std::vector<VoteMessage> votes) { this->votes = votes; }

        std::vector<VoteMessage> votes;
      };

      /**
       * Reject means that there is impossible
       * to collect supermajority for any block
       */
      struct RejectMessage {
        std::vector<VoteMessage> votes;
      };
    }  // namespace yac
  }    // namespace consensus
}  // namespace iroha
#endif  // IROHA_MESSAGES_HPP
