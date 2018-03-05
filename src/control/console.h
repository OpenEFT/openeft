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


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MOV_COL_RIGHT_BOOT	"\033[70G"
#define MOV_COL_RIGHT_CMD  	"\033[20G"

#define BOOT_OK		MOV_COL_RIGHT_BOOT "[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_RESET "]" 
#define BOOT_FAILED	MOV_COL_RIGHT_BOOT "[" ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "]"

using namespace std;

/*
 * Listens to fdin and executes commands 
 */ 
class CConsole : public CControl
{
  public:
    /* Calling process can pipe and dup the in and out fds and make
                 this object a child and leave her on her own */
    CConsole(uint32_t fdin, uint32_t fdout);
    virtual uint32_t process();
    
    private:
      uint32_t fdin, fdout;
      
      struct Cmd
      {
        int cmd_id; /* Command ID from enum EFT_COMMANDS */
        string cmd_str; /* Command string that the user types in the console. */
      };
      
      vector<Cmd> cmd_array;
};



#endif /* CONSOLE_H */

