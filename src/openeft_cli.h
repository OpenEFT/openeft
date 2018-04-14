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
#ifndef _OPENEFT_CLI_OPENEFT_H
#define _OPENEFT_CLI_OPENEFT_H

#include "global.h"
#include "eftclass.h"
#include "log/log.h"
#include "config/config_cli.h"
#include "control/console.h"

/*
 ** The main entry of this program.
 */
class eftOpeneftCli : public eftClass {
public:
  ~eftOpeneftCli();
  eftOpeneftCli();
  
  uint32_t init();
  uint32_t init_cli_config();
  uint32_t init_console(); /* Initialize console */
  uint32_t shutdown(); /* Graceful exit */
  
  eftConsole *console;
  eftConfigCli cfg;
};


#endif /* OPENEFT_CLI_H */

