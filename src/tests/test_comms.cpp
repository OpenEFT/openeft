//----------------------------------------------------------------------
// Copyright (C) 2018  openeft.org
// Copyright (C) Reza Schadmani <reza.schadmani@openeft.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------

#include "global.h"
#include "log/log.h"
#include "comms/client_ssl.h"
#include "comms/server_ssl.h"
#include "config/config.h"
#include "test_comms.h"


eftTestComms::eftTestComms(uint32_t threads_no,
            uint32_t no_connections,
            uint32_t no_messages,
            uint32_t message_size)
            : conx(no_connections)
            , msg_no(no_messages)
            , msg_size(message_size)
            , ioServices(threads_no)
            , server{ioServices, conx, msg_no, msg_size} {
  log(LOG_DEBUG, " ");
  clients = createClients(ioServices, msg_size, conx);
}

eftTestComms::~eftTestComms() {
  
}

void eftTestComms::tick() {
  
}

std::vector<std::shared_ptr<ClientConnection>> eftTestComms::createClients(
        IoServices &ioServices, std::size_t messageSize, std::size_t number) {
  asio::ip::tcp::resolver resolver{ioServices.get()};
log(LOG_DEBUG, " ");
  auto iterator = 
      resolver.resolve({eftConfig::ssl_ipaddr, to_string(eftConfig::ssl_port)});
log(LOG_DEBUG, " ");
  std::vector<std::shared_ptr < ClientConnection>> clients;
  log(LOG_DEBUG, " ");
  std::generate_n(std::back_inserter(clients), number, [&] {
    return std::make_shared<ClientConnection>(
            ioServices.get(), iterator, messageSize);
  });

  return clients;
}

std::chrono::milliseconds eftTestComms::measureTransferTime(
    std::vector<std::shared_ptr<ClientConnection>> &clients,
    std::size_t messages)
{
    auto startTime = std::chrono::steady_clock::now();
log(LOG_DEBUG, " ");
    for (auto &client : clients) {
      log(LOG_DEBUG, " ");
        client->asyncSend(messages);
    }
    while (ServerConnection::runningConnections() != 0) {
      log(LOG_DEBUG, " ");
        std::this_thread::sleep_for(std::chrono::milliseconds{10});
    }
log(LOG_DEBUG, " ");
    auto stopTime = std::chrono::steady_clock::now();
log(LOG_DEBUG, " ");
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        stopTime - startTime);
}

void eftTestComms::stop(TestResult& result) {
  auto duration = measureTransferTime(clients, msg_no);
  result.seconds = static_cast<double> (duration.count()) / 1000;  
  
  result.conx = conx;
  result.msg_no = msg_no;
  result.msg_size = msg_size;
  
  last_test_result = result;
  
  ioServices.stop();
}