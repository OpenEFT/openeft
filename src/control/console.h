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
class CConsole : public CControl
{
  public:
    /* Calling process can pipe and dup the in and out fds and make
                 this object a child and leave her on her own */
    CConsole(uint32_t fdin, uint32_t fdout);
    virtual uint32_t process();
    
    private:
      uint32_t fdin, fdout;
      struct Command {
        int id;
        string name;
      };
      vector<Command> cmd_list;
};



#endif /* CONSOLE_H */

