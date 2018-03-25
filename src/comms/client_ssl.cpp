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
#include "client_ssl.h"


ClientConnection::ClientConnection(asio::io_service &ioService,
        asio::ip::tcp::resolver::iterator iterator, std::size_t messageSize)
        : m_context{asio::ssl::context::tlsv12_client}
        , m_socket{ioService, m_context}
        , m_buffer(messageSize) {
  log(LOG_DEBUG, " ");
  asio::connect(m_socket.lowest_layer(), iterator);
  log(LOG_DEBUG, " ");
  m_socket.handshake(asio::ssl::stream_base::client);
  log(LOG_DEBUG, " ");
}
        
ClientConnection::~ClientConnection() {

}

void ClientConnection::tick() {

}


void ClientConnection::asyncSend(std::size_t messages) {
log(LOG_DEBUG, " ");
  asio::async_write(m_socket, asio::buffer(m_buffer),
          [ = ](const system::error_code &, std::size_t){
    if (messages > 1) {
      log(LOG_DEBUG, " ");
            asyncSend(messages - 1);
    }
    });
}
