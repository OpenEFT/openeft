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

#ifndef _OPENEFT_CONFIG_H
#define _OPENEFT_CONFIG_H

#include "global.h"

class eftConfig {
public:
  static string config_path;
  
  /* configuing comms async IO pool */
  static uint32_t comms_no_conx;
  static uint32_t comms_no_threads;

  static uint16_t ssl_port;
  static string ssl_ipaddr;
  static string ssl_cert;
  static string ssl_key;

  static string cli_port;
  static string cli_ipaddr;
  static string cli_cafile;
  static string cli_server_crt;
  static string cli_server_key;

  /* fd to collect the logs */
  static uint32_t log_fp;
  static uint32_t log_run_level;
  static bool log_enabled;
  
};

#endif /* CONFIG_H */

