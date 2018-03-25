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

class eftIoService {
public:

  eftIoService(uint32_t number);
  ~eftIoService();

  void stop();

  asio::io_service &get();

private:
  std::atomic<size_t> next_service{0};
  vector<asio::io_service> io_services;
  vector<asio::io_service::work> idle_works;
  vector<std::thread> threads;
};

class eftCommSession {
public:
  eftCommSession(asio::io_service &io_srv, asio::ssl::context &context,
    uint32_t msg_size);
  ~eftCommSession();

  asio::ssl::stream<asio::ip::tcp::socket>::lowest_layer_type &get_socket();
  void start(std::shared_ptr<eftCommSession> self, uint32_t no_messages);
  static uint32_t running_connections();

private:
  void async_read(std::shared_ptr<eftCommSession> self, uint32_t no_messages);

  static std::atomic<uint32_t> running_conx;
  asio::ssl::stream<asio::ip::tcp::socket> socket;
  vector<char> buffer;
};

class eftServer : public eftClass {
public:
  eftServer(eftIoService &io_srv, uint32_t connections,
    uint32_t no_msgs, uint32_t msg_size);

  virtual ~eftServer();
  virtual void tick();

private:

  void async_accept(uint32_t connections);

  eftIoService &io_services;
  uint32_t no_messages;
  uint32_t message_size;

  asio::ssl::context context;
  asio::ip::tcp::acceptor acceptor;
};


#endif /* SERVER_SSL_H */

