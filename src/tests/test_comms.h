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
    uint32_t milli_seconds;
  };

  
  void stop(TestResult& result);
 
private:
  std::vector<std::shared_ptr<eftClientCon>> create_clients(
    eftIoService &io_srvs, uint32_t msg_size, uint32_t number);

  std::chrono::milliseconds measure_transfer_time(
    std::vector<std::shared_ptr<eftClientCon>> &clients,
    uint32_t messages);

  eftIoService io_services;
  eftServer server;
  std::vector<std::shared_ptr<eftClientCon>> clients;

  uint32_t conx;
  uint32_t msg_no;
  uint32_t msg_size;
  
  TestResult last_test_result;
};

#endif /* TEST_COMMS_H */