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

#ifndef IROHA_PROTO_SIGNATURE_HPP
#define IROHA_PROTO_SIGNATURE_HPP

#include "interfaces/common_objects/signature.hpp"
#include "interfaces/hashable.hpp"
#include "primitive.pb.h"

namespace shared_model {
  namespace proto {
    class Signature final : public interface::Signature {
     private:
      using RefSignature = detail::ReferenceHolder<iroha::protocol::Signature>;

     public:
      explicit Signature(const iroha::protocol::Signature &signature)
          : Signature(RefSignature(signature)) {}

      explicit Signature(iroha::protocol::Signature &&signature)
          : Signature(RefSignature(std::move(signature))) {}

      const PublicKeyType &publicKey() const override { return *pubkey_; }

      const SignedType &signedData() const override {
        return *signed_data_;
      }

      ModelType *copy() const override {
        iroha::protocol::Signature signature = *signature_;
        return new Signature(std::move(signature));
      }

     private:
      // ----------------------------| private API |----------------------------
      explicit Signature(RefSignature &&ref)
          : signature_(std::move(ref)),
            pubkey_([this] { return PublicKeyType(signature_->pubkey()); }),
            signed_data_(
                [this] { return crypto::Signed(signature_->signature()); }) {}

      // ------------------------------| fields |-------------------------------

      // proto
      RefSignature signature_;

      template <typename Value>
      using Lazy = detail::LazyInitializer<Value>;
      Lazy<PublicKeyType> pubkey_;
      Lazy<SignedType> signed_data_;
    };

  }  // namespace proto
}  // namespace shared_model

#endif  // IROHA_PROTO_SIGNATURE_HPP
