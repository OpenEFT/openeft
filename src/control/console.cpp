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
#include "control.h"
#include "console.h"
#include "log/log.h"

eftConsole::eftConsole() {

  cmd_list = {
    {EFT_HELP, "help"},
    {EFT_CHECKUP, "checkup"},
    {EFT_HARD_RESET, "reset"},
    {EFT_RELOAD_CFG, "reload"},
    {EFT_GET_TR_TABLE, "get_tr_report"},
    {EFT_GET_COMPLIANCE_TABLE, "get_compliance_report"},
    {EFT_GET_OP_TABLE, "get_op_report"},
    {EFT_GET_PEER_ADV_TABLE, "get_peer_adv_report"},
    {EFT_GET_NET_COMPLIANCE_TABLE, "get_net_compliance_report"},
    {EFT_GET_NET_OP_TABLE, "get_net_op_report"},
    {EFT_GET_NET_TR_TABLE, "get_net_tr_report"}
  };
}

eftConsole::~eftConsole() {
  
}

void eftConsole::tick() {
  usleep(OPENEFT_HEARTBEAT_MICROSEC);
  log(LOG_DEBUG, "Beating");
}