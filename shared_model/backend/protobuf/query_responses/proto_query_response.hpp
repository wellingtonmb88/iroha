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

#ifndef IROHA_PROTO_QUERY_RESPONSE_HPP
#define IROHA_PROTO_QUERY_RESPONSE_HPP

#include "backend/protobuf/common_objects/trivial_proto.hpp"
#include "backend/protobuf/query_responses/proto_account_asset_response.hpp"
#include "backend/protobuf/query_responses/proto_account_response.hpp"
#include "backend/protobuf/query_responses/proto_error_query_response.hpp"
#include "interfaces/queries/query.hpp"
#include "interfaces/query_responses/query_response.hpp"
#include "responses.pb.h"
#include "utils/lazy_initializer.hpp"
#include "utils/variant_deserializer.hpp"

template <typename... T, typename Archive>
auto loadQueryResponse(Archive &&ar) {
  int which =
      ar.GetDescriptor()->FindFieldByNumber(ar.response_case())->index();
  return shared_model::detail::variant_impl<T...>::template load<
      shared_model::interface::QueryResponse::QueryResponseVariantType>(
      std::forward<Archive>(ar), which);
}

namespace shared_model {
  namespace proto {
    class QueryResponse final
        : public CopyableProto<interface::QueryResponse,
                               iroha::protocol::QueryResponse,
                               QueryResponse> {
     private:
      template <typename... Value>
      using w = boost::variant<detail::PolymorphicWrapper<Value>...>;

      template <typename T>
      using Lazy = detail::LazyInitializer<T>;

      using LazyVariantType = Lazy<QueryResponseVariantType>;

     public:
      /// type of proto variant
      using ProtoQueryResponseVariantType =
          w<AccountAssetResponse, AccountResponse, ErrorQueryResponse>;

      /// list of types in variant
      using ProtoQueryResponseListType = ProtoQueryResponseVariantType::types;

      /// Type of query hash
      using QueryHashType = interface::Query::HashType;

      template <typename QueryResponseType>
      explicit QueryResponse(QueryResponseType &&queryResponse)
          : CopyableProto(std::forward<QueryResponseType>(queryResponse)),
            variant_([this] {
              return loadQueryResponse<ProtoQueryResponseListType>(*proto_);
            }),
            hash_([this] { return QueryHashType(proto_->query_hash()); }) {}

      QueryResponse(const QueryResponse &o) : QueryResponse(o.proto_) {}

      QueryResponse(QueryResponse &&o) noexcept
          : QueryResponse(std::move(o.proto_)) {}

      const QueryResponseVariantType &get() const override { return *variant_; }

      const QueryHashType &queryHash() const override { return *hash_; }

     private:
      const LazyVariantType variant_;
      const Lazy<QueryHashType> hash_;
    };
  }  // namespace proto
}  // namespace shared_model

#endif  // IROHA_PROTO_QUERY_RESPONSE_HPP
