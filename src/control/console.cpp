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




CConsole::CConsole(uint32_t fdin, uint32_t fdout)
{
  fdin = fdin;
  fdout = fdout;
  
  cmd_array = [Cmd(EFT_HELP, "help"),
                Cmd(EFT_CHECKUP, "checkup"),
                  Cmd(EFT_HARD_RESET, "reset"),
                Cmd(EFT_RELOAD_CFG, "reload"),
                  Cmd(EFT_GET_TR_TABLE, "get_tr_report"),
                Cmd(EFT_GET_COMPLIANCE_TABLE, "get_compliance_report"),
                  Cmd(EFT_GET_OP_TABLE, "get_op_report"),
                Cmd(EFT_GET_PEER_ADV_TABLE, "get_peer_adv_report"),
                  Cmd(EFT_GET_NET_COMPLIANCE_TABLE, "get_net_compliance_report"),
                Cmd(EFT_GET_NET_OP_TABLE, "get_net_op_report"),
                  Cmd(EFT_GET_NET_TR_TABLE, "get_net_tr_report")];
}

uint32_t CConsole::process()
{
  uint32_t retval;
  fd_set cmd_fds;
  char cmd[32];
  
  struct timeval tmo;
  
  tmo.tv_sec = 0;
  tmo.tv_usec = 1000;


  /* wait only 1 miliseconds for user input */
  FD_ZERO(&cmd_fds);
  FD_SET(fdin, &cmd_fds);
  
  memset(cmd, 0x00, sizeof(cmd));
  
  retval = select(fdin + 1, &cmd_fds, NULL, NULL, &tmo);
    if(retval > 0) {
      if(read(fdin, cmd, sizeof(cmd)) > 0) {
        cmd[strlen(cmd) - 1] = '\0';
        
        int i = 0;
        int right_cmd = 0;
        for (i = 0; i < cmd_array.size(); i++) {
          if (!strcmp(cmd, cmd_array[i].cmd_str)) {
            right_cmd = 1;
          }
        }

      }
    }
  
  return 0;
} 
