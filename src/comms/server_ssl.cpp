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
#include "eftclass.h"
#include "server_ssl.h"

#include "config/config.h"


std::atomic<uint32_t> eftCommSession::running_conx {
  0
};

eftCommSession::eftCommSession(asio::io_service &io_srv, asio::ssl::context &context,
        uint32_t msg_size)
: socket{io_srv, context}

, buffer(msg_size) {
  ++running_conx;
}

eftCommSession::~eftCommSession() {
  --running_conx;
}

asio::ssl::stream<asio::ip::tcp::socket>::lowest_layer_type& eftCommSession::get_socket() {
  return socket.lowest_layer();
}

void eftCommSession::start(std::shared_ptr<eftCommSession> self, uint32_t no_messages) {
  socket.async_handshake(asio::ssl::stream_base::server,
          [ = ](const system::error_code &){async_read(self, no_messages);});
}

uint32_t eftCommSession::running_connections() {
  return running_conx;
}

void eftCommSession::async_read(std::shared_ptr<eftCommSession> self, uint32_t no_messages) {
  asio::async_read(socket, boost::asio::buffer(buffer),
          [ = ](const system::error_code &, uint32_t){
    if (no_messages > 1) {
            async_read(self, no_messages - 1);
    }
    });
}

eftIoService::eftIoService(uint32_t number)
: io_services(number) {
  for (auto &io_srv : io_services) {
    idle_works.emplace_back(io_srv);
    threads.emplace_back([&] {
      io_srv.run(); });
  }
}

void eftIoService::stop() {
  for (auto &io_srv : io_services)
    io_srv.stop();
  for (auto &thread : threads)
    if (thread.joinable())
      thread.join();
}

eftIoService::~eftIoService() {
  stop();
}

asio::io_service& eftIoService::get() {
  return io_services[(next_service++ % io_services.size())];
}

eftServer::eftServer(eftIoService &io_srvs, uint32_t connections,
        uint32_t no_msgs, uint32_t msg_size)
: context{asio::ssl::context::tlsv12_server}

, acceptor{io_srvs.get(), {
    asio::ip::tcp::v4(), eftConfig::ssl_port
  }}
, io_services{io_srvs}
, no_messages{no_msgs}
, message_size{msg_size}
{
  context.use_certificate_chain_file(eftConfig::ssl_cert);
  context.use_private_key_file(eftConfig::ssl_key, asio::ssl::context::pem);
  async_accept(connections);
}

eftServer::~eftServer() {

}

void eftServer::tick() {}

void eftServer::async_accept(uint32_t connections) {
  auto conn = std::make_shared<eftCommSession>(
          io_services.get(), context, message_size);
  acceptor.async_accept(conn->get_socket(), [ = ](const system::error_code &){
    conn->start(conn, no_messages);
    if (connections > 1) {
      async_accept(connections - 1);
    }
  });
}

