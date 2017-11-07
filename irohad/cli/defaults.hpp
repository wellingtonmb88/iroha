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

#ifndef IROHA_CLI_DEFAULTS_HPP_
#define IROHA_CLI_DEFAULTS_HPP_

#include <chrono>
#include <cstdint>
#include "ametsuchi/config.hpp"
#include "cli/env-vars.hpp"

namespace defaults {
  using namespace std::literals::chrono_literals;

  const std::string LOCALHOST = "localhost";
  const std::string ALLHOST = "0.0.0.0";

  const std::string postgresHost = LOCALHOST;
  const std::uint16_t postgresPort = 6379;

  const std::string peerHost = LOCALHOST;
  const std::uint16_t peerPort = 11111;

  const std::string redisHost = LOCALHOST;
  const std::uint16_t redisPort = 5432;

  const std::string blockStoragePath = "blocks";

  const std::string toriiHost = LOCALHOST;
  const std::uint16_t toriiPort = 50051;

  const auto loadDelay = 5000ms;
  const auto voteDelay = 5000ms;
  const auto proposalDelay = 5000ms;
  const std::size_t proposalSize = 10;
}
#endif  //  IROHA_CLI_DEFAULTS_HPP_
