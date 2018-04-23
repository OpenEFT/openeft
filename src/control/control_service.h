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

#ifndef _OPENEFT_CONTROL_SERVICE_H
#define _OPENEFT_CONTROL_SERVICE_H

#include "protos/control.grpc.pb.h"
#include "comms/rpc_server_ssl.h"

using namespace control_proto;

class eftCallDataHelp;

class eftControlService : public eftRpcServerAsync {
public:

  eftControlService(eftControl* control,
    std::string addr,
    std::string port,
    std::string cert,
    std::string key,
    std::string root) :
  ctrl(control),
  eftRpcServerAsync(addr, port, cert, key, root) {
  }
  
  void tick();

  void run();
  void HandleRpcs();

private:

  ControlSrv::AsyncService srv;
  eftControl* ctrl;
};


class eftCallDataHelp : public eftRpcCallData {
public:

  eftCallDataHelp(::grpc::Service* service, ServerCompletionQueue* cq, eftControl* control);
  virtual void Proceed();

private:
  ServerContext ctx;
  control_proto::VoidRequest request;
  control_proto::HelpReply reply;
  ServerAsyncResponseWriter<HelpReply> responder;
  eftControl* ctrl;
};


#endif /* CONTROL_SERVICE_H */

