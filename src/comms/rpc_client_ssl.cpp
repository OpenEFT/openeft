
#include "config/config_cli.h"

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
template <class T>
eftRpcClientService<T>::eftRpcClientService(std::string cert,
                  std::string key,
                  std::string root) {
  read(client_crt, cert);
  read(client_key, key);
  read(cafile, root);
  
  grpc::SslCredentialsOptions opts = {root, key, cert};
  channel = grpc::CreateChannel(
      eftConfigCli::ipaddr + ":" + eftConfigCli::port,
      grpc::SslCredentials(opts));
  stub = T::NewStub(channel);
}
eftRpcClientService<T>::~eftRpcClientService() {
  
}