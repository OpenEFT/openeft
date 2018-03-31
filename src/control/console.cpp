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
#include "log/log.h"

eftConsole::eftConsole() {

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
    {EFT_COMMANDS_NOID, "console_log", &eftConsole::console_log_cmd}
  };
}

eftConsole::~eftConsole() {

}

void eftConsole::tick() {
  bool console_active = false;
  string cmd = "";

  while (true) {
    usleep(OPENEFT_HEARTBEAT_MICROSEC);

    std::getline(std::cin, cmd);

    if (console_active == false && cmd.empty()) {
      console_active = true;
      eftConfig::log_enabled = false;
      log(LOG_CONSOLE, "Console activated");
    }

    if (console_active == true)
      if (cmd == "exit") {
        console_active = false;
        eftConfig::log_enabled = true;
        log(LOG_CONSOLE, "Console deactivated");
        continue;
      }

    if (!cmd.empty())
      handle_command(cmd);
  }
}

uint32_t eftConsole::handle_command(string cmd) {
  uint32_t ret = EFT_OK;
  uint32_t i = 0;
  bool cmd_recognized = false;
  std::vector<std::string> strs;
  vector<string>::iterator it;
  
  eft::split_str(cmd, strs, ' ');
  
  for (it = strs.begin(); it != strs.end(); it++, i++) {
    boost::algorithm::to_lower(*it);
    if(i == 0)
      log(LOG_DEBUG, "Command [%s] received", (*it).c_str());
  }
 
  for (vector<Command>::iterator it = cmd_list.begin();
          it != cmd_list.end();
          it++) {
    Command *command = &(*it);

    if (command->name == strs[0]) {
      cmd_recognized = true;
      log(LOG_DEBUG, "%s", command->dump().c_str());
      CALL_MEMBER_FN(this, command->command_fptr)(strs);
    }
  }
  
  if (cmd_recognized == false)
    log(LOG_CONSOLE, "Command [%s] not recognized.", strs[0].c_str());

  return ret;
}

uint32_t eftConsole::help_cmd(std::vector<std::string>& args) {

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
  get_comms_benchmak(benchmark);
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
  get_ec_benchmark(benchmark);
  log(LOG_CONSOLE, "Elliptic-curve keypair generation benchmark information:");
  log(LOG_CONSOLE, "Number of keypairs: [%d]", benchmark.no_keypair);
  log(LOG_CONSOLE, "Duration: [%d]ms", benchmark.duration);
  log(LOG_CONSOLE, "Rate: [%d]kps", benchmark.rate);
  return EFT_OK;
}

uint32_t eftConsole::benchmark_ecdh_cmd(std::vector<std::string>& args) {
  EcdhBenchmarkTable benchmark;
  get_ecdh_benchmak(benchmark);
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