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

#ifndef _OPENEFT_CONTROL_H
#define _OPENEFT_CONTROL_H

#include <string>

using namespace std;

/* 
 * Keep track of the status and respond to control commands
 */
class CControl
{
public:
  
  enum EFT_COMMANDS
  {
    EFT_HELP = 0,
    EFT_CHECKUP,
    EFT_RELOAD_CFG,
    EFT_HARD_RESET,
 
    /* I add a set of MIBs here. Hope somewhen in the 
    future we would have standard MIBs for blockchains. */

    EFT_GET_OP_TABLE,
    EFT_GET_COMPLIANCE_TABLE,
    EFT_GET_TR_TABLE,
    EFT_GET_PEER_ADV_TABLE,
    EFT_GET_NET_OP_TABLE,
    EFT_GET_NET_COMPLIANCE_TABLE,
    EFT_GET_NET_TR_TABLE,
    EFT_COMMANDS_LAST
  };
  
  struct HelpResult
  {
    string eft_checkup;
    string eft_reload_cfg;
    string eft_hard_reset;
    string eft_get_op_table;
    string eft_get_compliance_table;
    string eft_get_tr_table;
    string eft_get_peer_adv_table;
    string eft_get_net_op_table;
    string eft_get_net_compliance_table;
    string eft_get_net_tr_table;
  };
  
  struct CheckupResult
  {
  };
  
  struct ReloadCfgResult
  {
  };
  
  struct HardResetResult
  {
  };
  
  struct OpTable
  {
    
  };
  
  struct ComplianceTable
  {
    
  };
  
  struct TransactionTable
  {
    
  };
  
  struct PeerAdvTable
  {
    
  };
  
  struct NetOpTable
  {
    
  };
  
  struct NetComplianceTable
  {
    
  };
  
  struct NetTransactionTable
  {
    
  };

  virtual uint32_t process() = 0;
  
protected:
  
  uint32_t help(HelpResult &ret);
  uint32_t checkup(CheckupResult &ret);
  uint32_t reload_config(ReloadCfgResult &ret);  
  uint32_t hard_rest(HardResetResult &ret);
  uint32_t get_op_table(OpTable &ret);
  uint32_t get_compliance_table(ComplianceTable &ret);
  uint32_t get_transaction_table(TransactionTable &ret);
  uint32_t get_peer_adv_table(PeerAdvTable &ret);
  uint32_t get_net_op_table(NetOpTable &ret);
  uint32_t get_net_compliance_table(NetComplianceTable &ret);
  uint32_t get_net_transaction_table(NetTransactionTable &ret);
  
};

#endif /* CONTROL_H */

