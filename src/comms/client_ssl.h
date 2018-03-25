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

#ifndef _OPENEFT_CLIENT_SSL_H
#define _OPENEFT_CLIENT_SSL_H

#include "eftclass.h"

class ClientConnection : public eftClass {
public:
    ClientConnection(asio::io_service &ioService,
        asio::ip::tcp::resolver::iterator iterator, std::size_t messageSize);

    virtual ~ClientConnection();
    virtual void tick();
    
    void asyncSend(std::size_t messages);

private:
    asio::ssl::context m_context;
    asio::ssl::stream<asio::ip::tcp::socket> m_socket;
    std::vector<char> m_buffer;
};


#endif /* CLIENT_SSL_H */

