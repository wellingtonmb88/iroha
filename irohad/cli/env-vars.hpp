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

#ifndef IROHA_ENV_VARS_HPP_
#define IROHA_ENV_VARS_HPP_

// peer flags
const std::string IROHA_PEER_HOST = "IROHA_PEER_HOST";
const std::string IROHA_PEER_PORT = "IROHA_PEER_PORT";
const std::string IROHA_PEER_PUBKEY = "IROHA_PEER_PUBKEY";
const std::string IROHA_PEER_PRIVKEY = "IROHA_PEER_PRIVKEY";

// torii flags
const std::string IROHA_TORII_HOST = "IROHA_TORII_HOST";
const std::string IROHA_TORII_PORT = "IROHA_TORII_PORT";

// postgres flags
const std::string IROHA_PGHOST = "IROHA_POSTGRES_HOST";
const std::string IROHA_PGPORT = "IROHA_POSTGRES_PORT";
const std::string IROHA_PGUSER = "IROHA_POSTGRES_USER";
const std::string IROHA_PGPASSWORD = "IROHA_POSTGRES_PASSWORD";
const std::string IROHA_PGDATABASE = "IROHA_POSTGRES_DATABASE";

// redis flags
const std::string IROHA_RDHOST = "IROHA_REDIS_HOST";
const std::string IROHA_RDPORT = "IROHA_REDIS_PORT";

// block storage flags
const std::string IROHA_BLOCKSPATH = "IROHA_BLOCKSPATH";

// other
const std::string IROHA_OTHER_LOADDELAY = "IROHA_OTHER_LOADDELAY";
const std::string IROHA_OTHER_VOTEDELAY = "IROHA_OTHER_VOTEDELAY";
const std::string IROHA_OTHER_PROPOSALDELAY = "IROHA_OTHER_PROPOSALDELAY";
const std::string IROHA_OTHER_PROPOSALSIZE = "IROHA_OTHER_PROPOSALSIZE";

#endif  //  IROHA_ENV_VARS_HPP_
