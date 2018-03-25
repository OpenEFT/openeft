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
#include "config.h"


/* G E N E R A L */
string eftConfig::config_path = "openeft.conf";

/* S S L */
uint16_t eftConfig::ssl_port = 9845;
string eftConfig::ssl_ipaddr = "127.0.0.1";
string eftConfig::ssl_cert = "certroot/eftnode_comm_cert.pem";
string eftConfig::ssl_key = "certroot/eftnode_comm_key.pem";


/* L O G S */
uint32_t eftConfig::log_fp = 0;
uint32_t eftConfig::log_run_level = LOG_DEBUG;
bool eftConfig::log_enabled = true;

/* A S Y N C   I O     P O O L */
uint32_t eftConfig::comms_no_conx = 400;
uint32_t eftConfig::comms_no_threads = 10;
