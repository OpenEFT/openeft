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

#ifndef _OPENEFT_TEST_COMMS_H
#define _OPENEFT_TEST_COMMS_H

#include "comms/client_ssl.h"
#include "comms/server_ssl.h"

class eftTestComms : public eftClass {
public:
  eftTestComms(uint32_t threads_no,
                uint32_t no_connections,
                uint32_t no_messages,
                uint32_t message_size);
  ~eftTestComms();

  virtual void tick();
  
  struct TestResult {
    uint32_t conx;
    uint32_t msg_no;
    uint32_t msg_size;
    uint32_t seconds;
  };

  
  void stop(TestResult& result);
 
private:
  std::vector<std::shared_ptr<ClientConnection>> createClients(
    IoServices &ioServices, std::size_t messageSize, std::size_t number);

  std::chrono::milliseconds measureTransferTime(
    std::vector<std::shared_ptr<ClientConnection>> &clients,
    std::size_t messages);

  IoServices ioServices;
  Server server;
  std::vector<std::shared_ptr<ClientConnection>> clients;

  uint32_t conx;
  uint32_t msg_no;
  uint32_t msg_size;
  
  TestResult last_test_result;
};

#endif /* TEST_COMMS_H */