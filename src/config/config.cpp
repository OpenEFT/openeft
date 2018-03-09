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
string eftConfig::config_path = "";

/* S S H */
bool eftConfig::ssh_enabled = false;
uint16_t eftConfig::ssh_port = 22;

/* L O G S */
uint32_t eftConfig::log_fp = 0;
uint32_t eftConfig::log_run_level = LOG_DEBUG;

uint32_t init_config(const eftConfig &cfg) {
  return EFT_OK;
}