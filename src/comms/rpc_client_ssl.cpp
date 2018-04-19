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
#include "eftclass.h"
#include "log/log.h"
#include "rpc_client_ssl.h"

eftRpcClientService::eftRpcClientService(
                  std::string ipaddr,
                  std::port,
                  std::string cert_path,
                  std::string key_path,
                  std::string root_path) {
  std::string cert;
  std::string key;
  std::string root;
  
  read(cert_path, cert);
  read(key_path, key);
  read(root_path, root);
  
  grpc::SslCredentialsOptions opts = {root, key, cert};
  channel = grpc::CreateChannel(
      ipaddr + ":" + port,
      grpc::SslCredentials(opts));
}

eftRpcClientService::~eftRpcClientService() {
  
}
