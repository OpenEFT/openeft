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

    EFT_OP_TABLE,
    EFT_COMPLIANCE_TABLE,
    EFT_TR_TABLE,
    EFT_PEER_ADV_TABLE,
    EFT_NET_OP_TABLE,
    EFT_NET_COMPLIANCE_TABLE,
    EFT_NET_TR_TABLE,
    EFT_COMMANDS_LAST
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

  virtual uint32_t process(uint32_t cmd) = 0;
  
protected:
  uint32_t retrieve_table(uint32_t table);
  uint32_t reload_config();
  uint32_t checkup();
  uint32_t hard_rest();
};

#endif /* CONTROL_H */

