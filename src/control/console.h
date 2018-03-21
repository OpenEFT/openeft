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

#include "control.h"

using namespace std;

/*
 * Listens to fdin and executes commands 
 */
class eftConsole : public eftControl {
public:
  eftConsole();
  
  virtual ~eftConsole();
  virtual void tick();
  
  uint32_t handle_command(string cmd);
  
private:
  struct Command {
    int id;
    string name;
    uint32_t (eftConsole::*command_fptr)();
    string dump() {
      return "id [" + to_string(id) + "] " + name;
    }
  };
  vector<Command> cmd_list;

  uint32_t help_cmd();
  uint32_t checkup_cmd();
  uint32_t hard_reset_cmd();
  uint32_t reload_cfg_cmd();
  uint32_t get_tr_table_cmd();
  uint32_t get_compliance_table_cmd();
  uint32_t get_op_table_cmd();
  uint32_t get_peer_adv_table_cmd();
  uint32_t get_net_compliance_table_cmd();
  uint32_t get_net_op_table_cmd();
  uint32_t get_net_tr_table_cmd();    
};



#endif /* CONSOLE_H */

