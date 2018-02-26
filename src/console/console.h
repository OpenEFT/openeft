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


#define CONSOLE_CMD_HELP		"help"
#define CONSOLE_CMD_HELP_DESC		"Help with server commands"
#define CONSOLE_CMD_LIST		"ls"
#define CONSOLE_CMD_LIST_DESC		"List the fds that are currently connected to this EFTnode"
#define CONSOLE_CMD_RAND		"rand"
#define CONSOLE_CMD_RAND_DESC		"Generate a random number"
#define CONSOLE_CMD_CHECKUP		"checkup"
#define CONSOLE_CMD_CHECKUP_DESC	"Checkup the server health"
#define CONSOLE_CMD_RELOAD		"reload"
#define CONSOLE_CMD_RELOAD_DESC		"Reload openeft configurations"
#define CONSOLE_NUMBER_OF_COMMANDS	5





#endif /* CONSOLE_H */

