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
: io_services(threads_no)
, server{io_services, no_connections, no_messages, message_size}
{

  conx = no_connections;
  msg_no = no_messages;
  msg_size = message_size;

  clients = create_clients(io_services, msg_size, conx);
}

eftTestComms::~eftTestComms() {

}

void eftTestComms::tick() {

}

std::vector<std::shared_ptr<eftClientCon>> eftTestComms::create_clients(
        eftIoService &io_srvs, uint32_t msg_size, uint32_t number) {
  asio::ip::tcp::resolver resolver{io_srvs.get()};
  auto iterator =
          resolver.resolve({eftConfig::ssl_ipaddr, to_string(eftConfig::ssl_port)});
  std::vector<std::shared_ptr < eftClientCon>> clients;
  std::generate_n(std::back_inserter(clients), number, [&] {
    return std::make_shared<eftClientCon>(
            io_services.get(), iterator, msg_size);
  });

  return clients;
}

std::chrono::milliseconds eftTestComms::measure_transfer_time(
        std::vector<std::shared_ptr<eftClientCon>> &clients,
        uint32_t messages) {
  auto start_time = std::chrono::steady_clock::now();

  for (auto &client : clients) {
    client->async_send(messages);
  }
  while (eftCommSession::running_connections() != 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds{10});
  }

  auto stop_time = std::chrono::steady_clock::now();

  return std::chrono::duration_cast<std::chrono::milliseconds>(
          stop_time - start_time);
}

void eftTestComms::stop(TestResult& result) {

  auto duration = measure_transfer_time(clients, msg_no);

  result.milli_seconds = static_cast<double> (duration.count());

  result.conx = conx;
  result.msg_no = msg_no;
  result.msg_size = msg_size;

  last_test_result = result;

  io_services.stop();
}
