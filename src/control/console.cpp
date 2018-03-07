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
  
  cmd_list = {{EFT_HELP, "help"},
                {EFT_CHECKUP, "checkup"},
                {EFT_HARD_RESET, "reset"},
                {EFT_RELOAD_CFG, "reload"},
                {EFT_GET_TR_TABLE, "get_tr_report"},
                {EFT_GET_COMPLIANCE_TABLE, "get_compliance_report"},
                {EFT_GET_OP_TABLE, "get_op_report"},
                {EFT_GET_PEER_ADV_TABLE, "get_peer_adv_report"},
                {EFT_GET_NET_COMPLIANCE_TABLE, "get_net_compliance_report"},
                {EFT_GET_NET_OP_TABLE, "get_net_op_report"},
                {EFT_GET_NET_TR_TABLE, "get_net_tr_report"}};
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
        for (i = 0; i < cmd_list.size(); i++) {
          if (!strcmp(cmd, cmd_list[i].name.c_str())) {
            right_cmd = 1;
          }
        }
      }
    }
  
  return 0;
} 


uint32_t init_console()
{
  int pipes[2][2];
  
  /* always in a pipe[], pipe[0] is for read and 
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1

  /* pipes for parent to write and read */
  pipe(pipes[0]); /* write */
  pipe(pipes[1]); /* read */
  
  if(!fork()) {
    dup2(pipes[0][READ_FD], STDIN_FILENO);
    dup2(pipes[1][WRITE_FD], STDOUT_FILENO);
    
    char command[20];
    memset(command, 0x00, sizeof(command));
    read(STDIN_FILENO, command, sizeof(command));
        
    printf("Command is %s.\n", command);
  } else {
    char buffer[100];
    int count;
 
    /* close fds not required by parent */       
    close(pipes[0][READ_FD]);
    close(pipes[1][WRITE_FD]);
 
    /* Write to child’s stdin */
    write(pipes[0][WRITE_FD], "help", 4);
  
    /* Read from child’s stdout */
    count = read(pipes[1][READ_FD], buffer, sizeof(buffer)-1);
    if (count >= 0) {
        buffer[count] = 0;
        printf("%s", buffer);
    } else {
        printf("IO Error\n");
    }
  }

  
  return EFT_OK;
}