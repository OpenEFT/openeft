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

#ifndef _OPENEFT_RPC_SERVER_SSL_H
#define _OPENEFT_RPC_SERVER_SSL_H

class eftRpcServerAsync : public eftClass {
public:

  eftRpcServerAsync(std::string ipaddr,
    std::string port,
    std::string cert_path,
    std::string key_path,
    std::string root_path);

  void RegisterService(::grpc::Service* service);
  void RunService();

protected:
  ServerBuilder builder;
  std::unique_ptr<Server> srv;
  std::unique_ptr<ServerCompletionQueue> cq;
};

class eftRpcCallData : public eftClass {
public:
  eftRpcCallData(::grpc::Service* service, ServerCompletionQueue* queue)
  : srv(service), cq(queue), status(CREATE) {}

  virtual void Proceed() = 0;

protected:
  ::grpc::Service* srv;
  ServerCompletionQueue* cq;
 
  enum CallStatus {
    CREATE, PROCESS, FINISH
  };
  CallStatus status;
};


#endif /* RPC_SERVER_SSL_H */

