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
#include "global.h"
#include "eftclass.h"


/* 
 * Keep track of the status and respond to control commands
 */
class eftControl : public eftClass {
public:

  virtual ~eftControl();
  virtual void tick();

  enum EFT_COMMANDS {
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

    /* Some generic commands */
    EFT_GET_COMMS_BENCHMARK,
    EFT_GET_EC_BENCHMARK,
    EFT_GET_ECDH_BENCHMARK,
    EFT_GET_DSA_BENCHMARK,
    
    EFT_COMMANDS_NOID,
    EFT_COMMANDS_LAST
  };

  struct HelpResult {
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
    string eft_get_comms_benchmark;
    string eft_get_ec_benchmark;
    string eft_get_ecdh_benchmark;
    string eft_get_dsa_benchmark;
  };

  struct CheckupResult {
  };

  struct ReloadCfgResult {
  };

  struct HardResetResult {
  };

  struct OpTable {
  };

  struct ComplianceTable {
  };

  struct TransactionTable {
  };

  struct PeerAdvTable {
  };

  struct NetOpTable {
  };

  struct NetComplianceTable {
  };

  struct NetTransactionTable {
  };
  
  struct CommsBenchmarkTable {
    uint32_t no_connections;
    uint32_t no_messages;
    uint32_t volume;
    uint32_t duration; /* millisecond */
    uint32_t rate; /* Mbs */
  };
  
  struct EcBenchmarkTable {
    uint32_t no_keypair;
    uint32_t duration;
    uint32_t rate; /* keypair per seconds */
  };
  
  struct EcdhBenchmarkTable {
    uint32_t no_secrets;
    uint32_t duration;
    uint32_t rate; /* Secret key per seconds */
  };
  
  struct DsaBenchmarkTable {
    uint32_t no_verify;
    uint32_t duration;
    uint32_t rate; /* verify signature per seconds */
  };
  

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
  uint32_t get_comms_benchmak(CommsBenchmarkTable &benchmark);
  uint32_t get_ec_benchmark(EcBenchmarkTable &benchmark);
  uint32_t get_ecdh_benchmak(EcdhBenchmarkTable &benchmark);
  uint32_t get_dsa_benchmark(DsaBenchmarkTable &benchmark);
};

#endif /* CONTROL_H */

