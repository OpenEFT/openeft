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


uint32_t CControl::help(HelpResult &ret)
{
  ret.eft_checkup = "Checkup the whole system and returns the latest status.";
  ret.eft_hard_reset = "Reset the configuration to default and reboot the eftnode daemon.";
  ret.eft_reload_cfg = "Reload and apply the latest configurations to the eftnode daemon without "
          "reboot";
  ret.eft_get_op_table = "Get the latest operational reports.";
  ret.eft_get_compliance_table = "Get the latest compliancy report for this node.";
  ret.eft_get_peer_adv_table = "Get the latest peer advertisement reports.";
  ret.eft_get_tr_table = "Get the latest transaction reports for this node. "
          "Search criteria applied.";
  ret.eft_get_net_tr_table = "Get the latest transaction reports for the whole EFT network. "
          "Search criteria applied.";
  ret.eft_get_net_compliance_table = "Get the latest compliancy report for the whole EFT network.";
 
  return EFT_OK;
}

uint32_t CControl::checkup(CheckupResult &ret)
{
}

uint32_t CControl::reload_config(ReloadCfgResult &ret)
{
}

uint32_t CControl::hard_rest(HardResetResult &ret)
{
}

uint32_t CControl::get_op_table(OpTable &ret)
{
}

uint32_t CControl::get_compliance_table(ComplianceTable &ret)
{
}

uint32_t CControl::get_transaction_table(TransactionTable &ret)
{
}

uint32_t CControl::get_peer_adv_table(PeerAdvTable &ret)
{
}

uint32_t CControl::get_net_op_table(NetOpTable &ret)
{
}

uint32_t CControl::get_net_compliance_table(NetComplianceTable &ret)
{
}

uint32_t CControl::get_net_transaction_table(NetTransactionTable &ret)
{
}




uint32_t init_control()
{
  return EFT_OK;
}