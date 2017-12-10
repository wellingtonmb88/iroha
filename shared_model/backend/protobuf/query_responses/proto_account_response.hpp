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

#ifndef IROHA_SHARED_MODEL_PROTO_ACCOUNT_RESPONSE_HPP
#define IROHA_SHARED_MODEL_PROTO_ACCOUNT_RESPONSE_HPP

#include "backend/protobuf/common_objects/account.hpp"
#include "backend/protobuf/common_objects/trivial_proto.hpp"
#include "interfaces/query_responses/account_response.hpp"
#include "responses.pb.h"
#include "utils/lazy_initializer.hpp"
#include "utils/reference_holder.hpp"

namespace shared_model {
  namespace proto {
    class AccountResponse final
        : public CopyableProto<interface::AccountResponse,
                               iroha::protocol::QueryResponse,
                               AccountResponse> {
     public:
      template <typename QueryResponseType>
      explicit AccountResponse(QueryResponseType &&queryResponse)
          : CopyableProto(std::forward<QueryResponseType>(queryResponse)),
            accountResponse_(detail::makeReferenceGenerator(
                proto_, &iroha::protocol::QueryResponse::account_response)),
            accountRoles_([this] {
              return boost::accumulate(
                  accountResponse_->account_roles(),
                  SetRoleIdType{},
                  [](auto &&roles, const auto &role) {
                    roles.push_back(interface::types::RoleIdType(role));
                    return std::forward<decltype(roles)>(roles);
                  });
            }),
            account_([this] { return Account(accountResponse_->account()); }) {}

      AccountResponse(const AccountResponse &o) : AccountResponse(o.proto_) {}

      AccountResponse(AccountResponse &&o)
          : AccountResponse(std::move(o.proto_)) {}

      const interface::Account &account() const override { return *account_; }

      const SetRoleIdType &roles() const override { return *accountRoles_; }

     private:
      template <typename T>
      using Lazy = detail::LazyInitializer<T>;

      const Lazy<const iroha::protocol::AccountResponse &> accountResponse_;
      const Lazy<SetRoleIdType> accountRoles_;
      const Lazy<shared_model::proto::Account> account_;
    };
  }  // namespace proto
}  // namespace shared_model

#endif  // IROHA_SHARED_MODEL_PROTO_ACCOUNT_RESPONSE_HPP
