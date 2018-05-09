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

#ifndef _OPENEFT_CONSOLE_H
#define _OPENEFT_CONSOLE_H

#include "protos/control.grpc.pb.h"
#include "kernel/protos/generic.grpc.pb.h"
#include "comms/rpc_client_ssl.h"


/*
 * Listens to fdin and executes commands 
 */
class eftConsole : public eftRpcClientService {
public:
  eftConsole(std::string ipaddr,
              std::string port,
              std::string cert_path,
              std::string key_path,
              std::string root_path);

  virtual ~eftConsole();

  uint32_t handle_command(string &cmd);
  
private:
  struct Command {
    int id;
    string name;
    uint32_t (eftConsole::*command_fptr)(std::vector<std::string> &);
    string dump() {
      return "id [" + to_string(id) + "] " + name;
    }
  };
  vector<Command> cmd_list;

  uint32_t help_cmd(std::vector<std::string>& args);
  uint32_t checkup_cmd(std::vector<std::string>& args);
  uint32_t hard_reset_cmd(std::vector<std::string>& args);
  uint32_t reload_cfg_cmd(std::vector<std::string>& args);
  uint32_t get_tr_table_cmd(std::vector<std::string>& args);
  uint32_t get_compliance_table_cmd(std::vector<std::string>& args);
  uint32_t get_op_table_cmd(std::vector<std::string>& args);
  uint32_t get_peer_adv_table_cmd(std::vector<std::string>& args);
  uint32_t get_net_compliance_table_cmd(std::vector<std::string>& args);
  uint32_t get_net_op_table_cmd(std::vector<std::string>& args);
  uint32_t get_net_tr_table_cmd(std::vector<std::string>& args);
  
  /* Benchmarks */
  uint32_t banchmark_comms_cmd(std::vector<std::string>& args);
  uint32_t benchmark_ec_cmd(std::vector<std::string>& args);
  uint32_t benchmark_ecdh_cmd(std::vector<std::string>& args);
  uint32_t benchmark_dsa_cmd(std::vector<std::string>& args);
  
  /* Other commands */
  uint32_t console_log_cmd(std::vector<std::string>& args);
  
  
  std::unique_ptr<control_proto::ControlSrv::Stub> stub;
};



#endif /* CONSOLE_H */

