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
#include "config_cli.h"


/* G E N E R A L */
string eftConfigCli::config_path = "openeft-cli.conf";

/* S S L */
string eftConfigCli::port = "9846";
string eftConfigCli::ipaddr = "localhost";
string eftConfigCli::cafile = "certroot/eftnode_cli_ca.crt";
string eftConfigCli::client_crt = "certroot/eftnode_cli_client.crt";
string eftConfigCli::client_key = "certroot/eftnode_cli_client.key";


/* L O G S */
uint32_t eftConfigCli::log_fp = fileno(stdout);
uint32_t eftConfigCli::log_run_level = LOG_DEBUG;
bool eftConfigCli::log_enabled = true;
