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

#ifndef _OPENEFT_SERVER_SSL_H
#define _OPENEFT_SERVER_SSL_H


class IoServices {
public:

  IoServices(size_t number);
  ~IoServices();
  
  void stop();
  
  asio::io_service &get();

private:
  std::atomic<size_t> m_nextService{0};
  vector<asio::io_service> m_ioServices;
  vector<asio::io_service::work> m_idleWorks;
  vector<std::thread> m_threads;
};

class ServerConnection {
public:
  ServerConnection(asio::io_service &ioService, asio::ssl::context &context,
    size_t messageSize);
  ~ServerConnection();

  asio::ssl::stream<asio::ip::tcp::socket>::lowest_layer_type &socket();
  void start(std::shared_ptr<ServerConnection> self, size_t messages);
  static size_t runningConnections();

private:
  void asyncRead(std::shared_ptr<ServerConnection> self, size_t messages);

  static std::atomic<std::size_t> s_runningConnections;
  asio::ssl::stream<asio::ip::tcp::socket> m_socket;
  vector<char> m_buffer;
};

class Server : public eftClass {
public:
  Server(IoServices &ioServices, size_t connections,
    size_t messages, size_t messageSize);
  
  virtual ~Server();
  
  virtual void tick();

private:

  void asyncAccept(size_t connections);

  IoServices &m_ioServices;
  size_t m_messages;
  size_t m_messageSize;

  asio::ssl::context m_context;
  asio::ip::tcp::acceptor m_acceptor;
};


#endif /* SERVER_SSL_H */

