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


eftClientCon::eftClientCon(asio::io_service &io_srv,
        asio::ip::tcp::resolver::iterator iterator, uint32_t msg_size)
: context{asio::ssl::context::tlsv12_client}
, socket{io_srv, context}
, buffer(msg_size) {
  asio::connect(socket.lowest_layer(), iterator);
  socket.handshake(asio::ssl::stream_base::client);
}

eftClientCon::~eftClientCon() {
}

void eftClientCon::tick() {
}

void eftClientCon::async_send(uint32_t messages) {
  asio::async_write(socket, asio::buffer(buffer),
          [ = ](const system::error_code &, uint32_t){
    if (messages > 1) {
      async_send(messages - 1);
    }
  });

}
