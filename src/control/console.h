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
  virtual uint32_t process();
  
  struct ForkPipes {
    /* pipe 0 */
    struct pipe_0 {
      int child_in;
      int parent_out;
    }p0;
    /* pipe 1 */
    struct pipe_1 {
      int parent_in;
      int child_out;
    }p1;
  } fork_pipes;

  uint32_t init_stdio(ForkPipes *pipes);
  uint32_t close_stdio();
#define READ_FD  0
#define WRITE_FD 1
  
private:

  struct Command {
    int id;
    string name;
  };
  vector<Command> cmd_list;
};



#endif /* CONSOLE_H */

