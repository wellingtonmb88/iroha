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

#ifndef IROHA_FLAGS_HPP_
#define IROHA_FLAGS_HPP_

#include <CLI/CLI.hpp>
#include <boost/assert.hpp>
#include <boost/filesystem.hpp>
#include "ametsuchi/config.hpp"
#include "common.hpp"
#include "env-vars.hpp"
#include "torii/config.hpp"
#include "util/network.hpp"

namespace flag {

  const auto IROHA_PORT_MIN = 1;
  const auto IROHA_PORT_MAX = 65535;
  const auto IROHA_DELAY_MIN = 1;
  const auto IROHA_DELAY_MAX = 100000;
  const auto IROHA_SIZE_MIN = 1;
  const auto IROHA_SIZE_MAX = 100000;

  inline void addPeerFlags(CLI::App *p,
                           iroha::config::Peer *peer,
                           iroha::torii::config::Torii *torii,
                           iroha::config::Cryptography *crypto) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(torii);
    BOOST_ASSERT(crypto);
    BOOST_ASSERT(peer);

    // both flags can be used for the same thing
    p->add_option("--api-host,--torii-host",        /* option's name */
                  torii->host,                      /* bind to this variable */
                  "Client API (torii) listen host", /* description */
                  true /* use initial value as default */)
        ->envname(IROHA_TORII_HOST)
        ->group("Peer")
        ->check(iroha::network::is_host_valid);

    p->add_option("--api-port,--torii-port",
                  torii->port,
                  "Client API (torii) listen port",
                  true)
        ->envname(IROHA_TORII_PORT)
        ->check(CLI::Range(IROHA_PORT_MIN, IROHA_PORT_MAX))
        ->group("Peer");

    p->add_option("--host", peer->host, "Peer's listen address", true)
        ->envname(IROHA_TORII_HOST)
        ->group("Peer")
        ->check(iroha::network::is_host_valid);

    p->add_option("--port", peer->port, "Peer's listen port", true)
        ->envname(IROHA_TORII_PORT)
        ->check(CLI::Range(IROHA_PORT_MIN, IROHA_PORT_MAX))
        ->group("Peer");

    p->add_option(
         "--pubkey", crypto->public_key, "Path to peer's public key", false)
        ->required()
        ->envname(IROHA_PEER_PUBKEY)
        ->group("Peer")
        ->check(CLI::ExistingFile);

    p->add_option(
         "--privkey", crypto->private_key, "Path to peer's private key", false)
        ->required()
        ->envname(IROHA_PEER_PRIVKEY)
        ->group("Peer")
        ->check(CLI::ExistingFile);
  }

  inline void addPostgresFlags(CLI::App *p,
                               iroha::ametsuchi::config::Postgres *postgres) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(postgres);
    p->add_option(
         "--pghost", postgres->host, "PostgreSQL database host. ", true)
        ->envname(IROHA_PGHOST)
        ->group("PostgreSQL")
        ->check(iroha::network::is_host_valid);

    p->add_option("--pgport", postgres->port, "PostgreSQL database port.", true)
        ->envname(IROHA_PGPORT)
        ->check(CLI::Range(IROHA_PORT_MIN, IROHA_PORT_MAX))
        ->group("PostgreSQL");

    p->add_option(
         "--pgdatabase", postgres->database, "PostgreSQL database name", true)
        ->envname(IROHA_PGDATABASE)
        ->group("PostgreSQL");

    p->add_option("--pguser", postgres->username, "PostgreSQL username", false)
        ->required()
        ->envname(IROHA_PGUSER)
        ->group("PostgreSQL");

    p->add_option(
         "--pgpassword", postgres->password, "PostgreSQL password", false)
        ->required()
        ->envname(IROHA_PGPASSWORD)
        ->group("PostgreSQL");
  }

  inline void addRedisFlags(CLI::App *p,
                            iroha::ametsuchi::config::Redis *redis) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(redis);
    p->add_option("--rdhost", redis->host, "Redis database host", true)
        ->envname(IROHA_RDHOST)
        ->group("Redis")
        ->check(iroha::network::is_host_valid);

    p->add_option("--rdport", redis->port, "Redis database port", true)
        ->envname(IROHA_RDPORT)
        ->check(CLI::Range(IROHA_PORT_MIN, IROHA_PORT_MAX))
        ->group("Redis");
  }

  inline void addBlockStorageFlags(
      CLI::App *p, iroha::ametsuchi::config::BlockStorage *storage) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(storage);
    p->add_option("--blockspath",
                  storage->path,
                  "Path to the folder, where blocks are saved",
                  true)
        ->envname(IROHA_BLOCKSPATH)
        ->group("Block Storage");
  }

  inline void addCreateLedgerFlags(CLI::App *p, std::string *genesis) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(genesis);
    p->add_option("genesis-block", *genesis, "Path to the genesis block")
        ->required()
        ->check(CLI::ExistingFile);
  }

  inline void addOtherOptionsFlags(CLI::App *p,
                                   iroha::config::OtherOptions *options) {
    BOOST_ASSERT(p);
    BOOST_ASSERT(options);

    p->add_option(
         "--load-delay",
         options->load_delay,
         "Waiting time before loading committed block from next, milliseconds",
         true)
        ->group("Other")
        ->check(CLI::Range(IROHA_DELAY_MIN, IROHA_DELAY_MAX))
        ->envname(IROHA_OTHER_LOADDELAY);

    p->add_option("--vote-delay",
                  options->vote_delay,
                  "Waiting time before sending vote to next peer, milliseconds",
                  true)
        ->group("Other")
        ->check(CLI::Range(IROHA_DELAY_MIN, IROHA_DELAY_MAX))
        ->envname(IROHA_OTHER_VOTEDELAY);

    p->add_option("--proposal-delay",
                  options->proposal_delay,
                  "maximum waiting time util emitting new proposal",
                  true)
        ->group("Other")
        ->check(CLI::Range(IROHA_DELAY_MIN, IROHA_DELAY_MAX))
        ->envname(IROHA_OTHER_PROPOSALDELAY);

    p->add_option("--proposal-size",
                  options->max_proposal_size,
                  "Maximum transactions in one proposal",
                  true)
        ->group("Other")
        ->check(CLI::Range(IROHA_SIZE_MIN, IROHA_SIZE_MAX))
        ->envname(IROHA_OTHER_PROPOSALSIZE);
  }
}

#endif  //  IROHA_FLAGS_HPP_
