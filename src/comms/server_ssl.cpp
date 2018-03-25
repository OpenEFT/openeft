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


std::atomic<std::size_t> ServerConnection::s_runningConnections {
  0
};

ServerConnection::ServerConnection(asio::io_service &ioService, asio::ssl::context &context,
        std::size_t messageSize)
: m_socket{ioService, context}

, m_buffer(messageSize) {
log(LOG_DEBUG, " ");
  ++s_runningConnections;
}

ServerConnection::~ServerConnection() {
  log(LOG_DEBUG, " ");
  --s_runningConnections;
}

asio::ssl::stream<asio::ip::tcp::socket>::lowest_layer_type& ServerConnection::socket() {
  log(LOG_DEBUG, " ");
  return m_socket.lowest_layer();
}

void ServerConnection::start(std::shared_ptr<ServerConnection> self, std::size_t messages) {
  log(LOG_DEBUG, " ");
  m_socket.async_handshake(asio::ssl::stream_base::server,
          [ = ](const system::error_code &){asyncRead(self, messages);});
}

std::size_t ServerConnection::runningConnections() {
  log(LOG_DEBUG, " ");
  return s_runningConnections;
}

void ServerConnection::asyncRead(std::shared_ptr<ServerConnection> self, size_t messages) {
  log(LOG_DEBUG, " ");
  asio::async_read(m_socket, boost::asio::buffer(m_buffer),
          [ = ](const system::error_code &, std::size_t){
            log(LOG_DEBUG, " ");
    if (messages > 1) {
      log(LOG_DEBUG, " ");
            asyncRead(self, messages - 1);
    }
    });
}

IoServices::IoServices(std::size_t number)
: m_ioServices(number) {
  log(LOG_DEBUG, " ");
  for (auto &ioService : m_ioServices) {
    log(LOG_DEBUG, " ");
    m_idleWorks.emplace_back(ioService);
    m_threads.emplace_back([&] {
      ioService.run(); });
  }
}

void IoServices::stop() {
  log(LOG_DEBUG, " ");
  for (auto &ioService : m_ioServices)
    ioService.stop();
log(LOG_DEBUG, " ");
  for (auto &thread : m_threads)
    if (thread.joinable())
      thread.join();
}

IoServices::~IoServices() {
  log(LOG_DEBUG, " ");
  stop();
}

asio::io_service& IoServices::get() {
  return m_ioServices[(m_nextService++ % m_ioServices.size())];
}

Server::Server(IoServices &ioServices, std::size_t connections,
        std::size_t messages, std::size_t messageSize)
: m_context{asio::ssl::context::tlsv12_server}

, m_acceptor{m_ioServices.get(), {
    asio::ip::tcp::v4(), eftConfig::ssl_port
  }}
, m_ioServices{ioServices}
, m_messages{messages}
, m_messageSize{messageSize}
{
  log(LOG_DEBUG, " ");
  m_context.use_certificate_chain_file(eftConfig::ssl_cert);
  m_context.use_private_key_file(eftConfig::ssl_key, asio::ssl::context::pem);
  asyncAccept(connections);
}

Server::~Server() {

}

void Server::tick() {

}

void Server::asyncAccept(std::size_t connections) {
  log(LOG_DEBUG, " ");
  auto conn = std::make_shared<ServerConnection>(
          m_ioServices.get(), m_context, m_messageSize);
  log(LOG_DEBUG, " ");
  m_acceptor.async_accept(conn->socket(), [ = ](const system::error_code &){
    log(LOG_DEBUG, " ");
    conn->start(conn, m_messages);
    log(LOG_DEBUG, " ");
    if (connections > 1) {
      log(LOG_DEBUG, " ");
            asyncAccept(connections - 1);
    }
    });
}

