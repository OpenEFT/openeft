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
#ifndef _OPENEFT_OPENEFT_H
#define _OPENEFT_OPENEFT_H

#include "global.h"
#include "eftclass.h"
#include "log/log.h"
#include "config/config.h"
#include "control/console.h"

/*
 ** The main entry of this program.
 */
class eftOpeneft : public eftClass {
public:
  ~eftOpeneft();
  eftOpeneft();
  
  void tick();

  eftConsole *console;
  eftConfig cfg;
};


#endif /* OPENEFT_H */

