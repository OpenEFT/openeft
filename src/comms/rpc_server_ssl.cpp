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
#include "eftclass.h"
#include "rpc_server_ssl.h"



eftRpcServerAsync::eftRpcServerAsync(std::string ipaddr,
  std::string port,
  std::string cert_path,
  std::string key_path,
  std::string root_path) {

  std::string cert;
  std::string key;
  std::string root;

  read(cert_path, cert);
  read(key_path, key);
  read(root_path, root);

  std::string server_address(ipaddr + ":" + port);
  grpc::SslServerCredentialsOptions::PemKeyCertPair keycert = {key, cert};
  grpc::SslServerCredentialsOptions sslOps;

  sslOps.pem_root_certs = root;
  sslOps.pem_key_cert_pairs.push_back(keycert);

  builder.AddListeningPort(server_address, grpc::SslServerCredentials(sslOps));
  cq = builder.AddCompletionQueue();
}

void eftRpcServerAsync::RegisterService(::grpc::Service* service) {
  builder.RegisterService(service);
}

void eftRpcServerAsync::RunService() {
  srv = builder.BuildAndStart();
}

