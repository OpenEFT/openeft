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
#include "control.h"
#include "console.h"

using namespace control_proto;

eftConsole::eftConsole(std::string ipaddr,
              std::string port,
              std::string cert_path,
              std::string key_path,
              std::string root_path)
              : eftRpcClientService(ipaddr,
                        port,
                        cert_path,
                        key_path,
                        root_path) {
  
  stub = ControlSrv::NewStub(channel);

  cmd_list = {
    {EFT_HELP, "help", &eftConsole::help_cmd},
    {EFT_CHECKUP, "checkup", &eftConsole::checkup_cmd},
    {EFT_HARD_RESET, "reset", &eftConsole::hard_reset_cmd},
    {EFT_RELOAD_CFG, "reload", &eftConsole::reload_cfg_cmd},
    {EFT_GET_TR_TABLE, "get_tr_report", &eftConsole::get_tr_table_cmd},
    {EFT_GET_COMPLIANCE_TABLE, "get_compliance_report", &eftConsole::get_compliance_table_cmd},
    {EFT_GET_OP_TABLE, "get_op_report", &eftConsole::get_op_table_cmd},
    {EFT_GET_PEER_ADV_TABLE, "get_peer_adv_report", &eftConsole::get_peer_adv_table_cmd},
    {EFT_GET_NET_COMPLIANCE_TABLE, "get_net_compliance_report", &eftConsole::get_net_compliance_table_cmd},
    {EFT_GET_NET_OP_TABLE, "get_net_op_report", &eftConsole::get_net_op_table_cmd},
    {EFT_GET_NET_TR_TABLE, "get_net_tr_report", &eftConsole::get_net_tr_table_cmd},
    {EFT_GET_COMMS_BENCHMARK, "get_comms_benchmark", &eftConsole::banchmark_comms_cmd},
    {EFT_GET_EC_BENCHMARK, "get_ec_benchmark", &eftConsole::benchmark_ec_cmd},
    {EFT_GET_ECDH_BENCHMARK, "get_ecdh_benchmark", &eftConsole::benchmark_ecdh_cmd},
    {EFT_GET_DSA_BENCHMARK, "get_dsa_benchmark", &eftConsole::benchmark_dsa_cmd},
    {EFT_COMMANDS_NOID, "console_log", &eftConsole::console_log_cmd}
  };
}

eftConsole::~eftConsole() {

}

uint32_t eftConsole::handle_command(string &cmd) {
  uint32_t ret = EFT_OK;
  uint32_t i = 0;
  bool cmd_recognized = false;
  std::vector<std::string> params;
  vector<string>::iterator it;
  
  log(LOG_DEBUG, "Command received [%s]", cmd.c_str());
  
  eft::split_str(cmd, params, ' ');
  
  for (it = params.begin(); it != params.end(); it++, i++) {
    boost::algorithm::to_lower(*it);
  }
 
  for (vector<Command>::iterator it = cmd_list.begin();
          it != cmd_list.end();
          it++) {
    Command *command = &(*it);

    if (command->name == params[0]) {
      cmd_recognized = true;
      CALL_MEMBER_FN(this, command->command_fptr)(params);
      break;
    }
  }
  
  if (cmd_recognized == false)
    log(LOG_CONSOLE, "Command [%s] not recognized.", params[0].c_str());

  return ret;
}

uint32_t eftConsole::help_cmd(std::vector<std::string>& args) {
  VoidRequest request;
  HelpReply reply;
  ClientContext context;
  CompletionQueue cq;
  Status status;
  std::unique_ptr<ClientAsyncResponseReader<HelpReply> > rpc(
        stub->PrepareAsynchelp(&context, request, &cq));
  rpc->StartCall();
  rpc->Finish(&reply, &status, (void*)EFT_HELP);
  void* got_tag = NULL;
  bool ok = false;
  
  GPR_ASSERT(cq.Next(&got_tag, &ok));
  GPR_ASSERT(got_tag == (void*)EFT_HELP);
  GPR_ASSERT(ok);
  
  if (!status.ok()) {
    log(LOG_CONSOLE, "RPC failed");
    return EFT_NOK;
  }
  
  return EFT_OK;
}

uint32_t eftConsole::checkup_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::hard_reset_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::reload_cfg_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_tr_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_compliance_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_op_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_peer_adv_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_net_compliance_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_net_op_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::get_net_tr_table_cmd(std::vector<std::string>& args) {

}

uint32_t eftConsole::banchmark_comms_cmd(std::vector<std::string>& args) {
  CommsBenchmarkTable benchmark;
  //get_comms_benchmak(benchmark);
  log(LOG_CONSOLE, "Communication benchmark information:");
  log(LOG_CONSOLE, "Number of connections: [%d]", benchmark.no_connections);
  log(LOG_CONSOLE, "Number of messages: [%d]", benchmark.no_messages);
  log(LOG_CONSOLE, "Total volume transferred: [%d]MB", benchmark.volume);
  log(LOG_CONSOLE, "Duration: [%d]ms", benchmark.duration);
  log(LOG_CONSOLE, "Rate: [%d]Mbs", benchmark.rate);
  return EFT_OK;
}

uint32_t eftConsole::benchmark_ec_cmd(std::vector<std::string>& args) {
  EcBenchmarkTable benchmark;
  //get_ec_benchmark(benchmark);
  log(LOG_CONSOLE, "Elliptic-curve keypair generation benchmark information:");
  log(LOG_CONSOLE, "Number of keypairs: [%d]", benchmark.no_keypair);
  log(LOG_CONSOLE, "Duration: [%d]ms", benchmark.duration);
  log(LOG_CONSOLE, "Rate: [%d]kps", benchmark.rate);
  return EFT_OK;
}

uint32_t eftConsole::benchmark_ecdh_cmd(std::vector<std::string>& args) {
  EcdhBenchmarkTable benchmark;
  //get_ecdh_benchmak(benchmark);
  log(LOG_CONSOLE, "Elliptic-curve Diffie–Hellman benchmark information:");
  log(LOG_CONSOLE, "Number of secrets: [%d]", benchmark.no_secrets);
  log(LOG_CONSOLE, "Duration: [%d]ms", benchmark.duration);
  log(LOG_CONSOLE, "Rate: [%d]kps", benchmark.rate);
  return EFT_OK;
}

uint32_t eftConsole::console_log_cmd(std::vector<std::string>& args) {
  
  if(args.size() == 1) {
    log(LOG_CONSOLE, "Parameter missed.");
    return EFT_NOK;
  }
  
  if(args[1] == "on") {
    eftConfig::log_enabled = true;
    log(LOG_CONSOLE, "Console log enabled. Application log disabled.");
  }
  else if(args[1] == "off") {
    log(LOG_CONSOLE, "Console log disabled. Application log reset to [%d]",
                  eftConfig::log_run_level);
    eftConfig::log_enabled = false;
  }
  else {
    log(LOG_CONSOLE, "Parameter [%s] not recognized.", args[1].c_str());
  }

  return EFT_OK;
}

uint32_t eftConsole::benchmark_dsa_cmd(std::vector<std::string>& args) {
  DsaBenchmarkTable benchmark;
  //get_dsa_benchmark(benchmark);
  log(LOG_CONSOLE, "Elliptic-curve DSA benchmark information:");
  log(LOG_CONSOLE, "Number of verifies: [%d]", benchmark.no_verify);
  log(LOG_CONSOLE, "Duration: [%d]ms", benchmark.duration);
  log(LOG_CONSOLE, "Rate: [%d]kps", benchmark.rate);
  return EFT_OK;
}