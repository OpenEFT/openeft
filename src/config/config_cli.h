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

#ifndef _OPENEFT_CONFIG_CLI_H
#define _OPENEFT_CONFIG_CLI_H

#include "global.h"

class eftConfigCli {
public:
  static string config_path;
  
  static string port;
  static string ipaddr;
  static string cafile;
  static string client_crt;
  static string client_key;

  /* fd to collect the logs */
  static uint32_t log_fp;
  static uint32_t log_run_level;
  static bool log_enabled;
  
};

#endif /* CONFIG_CLI_H */

