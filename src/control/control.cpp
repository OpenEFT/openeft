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
#include "config/config.h"
#include "control.h"
#include "tests/test_comms.h"
#include "tests/test_ec.h"
#include "tests/test_ecdh.h"
#include "tests/test_verify_sig.h"

eftControl::~eftControl() {
}

uint32_t eftControl::help(HelpResult &ret) {
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
  ret.eft_get_comms_benchmark = "Get the latest network interface performance benchmarks.";
  ret.eft_get_ec_benchmark = "Get the Elliptic-curve keypair generation benchmark.";
  ret.eft_get_ecdh_benchmark = "Get the Elliptic-curve Diffie–Hellman (ECDH) performance benchmarks.";
  ret.eft_get_dsa_benchmark = "Get the Digital Signature Algorithm performance benchmark";
  return EFT_OK;
}

uint32_t eftControl::checkup(CheckupResult &ret) {
}

uint32_t eftControl::reload_config(ReloadCfgResult &ret) {
}

uint32_t eftControl::hard_rest(HardResetResult &ret) {
}

uint32_t eftControl::get_op_table(OpTable &ret) {
}

uint32_t eftControl::get_compliance_table(ComplianceTable &ret) {
}

uint32_t eftControl::get_transaction_table(TransactionTable &ret) {
}

uint32_t eftControl::get_peer_adv_table(PeerAdvTable &ret) {
}

uint32_t eftControl::get_net_op_table(NetOpTable &ret) {
}

uint32_t eftControl::get_net_compliance_table(NetComplianceTable &ret) {
}

uint32_t eftControl::get_net_transaction_table(NetTransactionTable &ret) {
}

uint32_t eftControl::get_comms_benchmak(CommsBenchmarkTable &benchmark) {
  eftTestComms::TestResult result;
  eftTestComms* t = new eftTestComms(eftConfig::comms_no_threads,
                                        eftConfig::comms_no_conx,
                                        1,
                                        256 * 3);
  t->stop(result);
  benchmark.duration = result.milli_seconds;
  benchmark.no_connections = result.conx;
  benchmark.no_messages = result.msg_no;
  benchmark.volume =  
          static_cast<double>(result.conx * result.msg_no * result.msg_size) / 1024 / 1024;
  benchmark.rate = ((benchmark.volume * 8) * 1000) / result.milli_seconds;
  delete t;
}

uint32_t eftControl::get_ec_benchmark(EcBenchmarkTable &benchmark) {
  eftTestEc::TestResult result;
  eftTestEc* t = new eftTestEc();
  t->run();
  t->stop(result);
  benchmark.duration = result.duration;
  benchmark.no_keypair = result.keypair_no;
  benchmark.rate = result.rate;

  return EFT_OK;
}

uint32_t eftControl::get_ecdh_benchmak(EcdhBenchmarkTable &benchmark) {
  eftTestEcdh::TestResult result;
  eftTestEcdh* t = new eftTestEcdh();
  t->run();
  t->stop(result);
  benchmark.duration = result.duration;
  benchmark.no_secrets = result.secret_no;
  benchmark.rate = result.rate;

  return EFT_OK;
}

uint32_t eftControl::get_dsa_benchmark(DsaBenchmarkTable &benchmark) {
  eftTestVerifySig::TestResult result;
  eftTestVerifySig* t = new eftTestVerifySig();
  t->run();
  t->stop(result);
  benchmark.duration = result.duration;
  benchmark.no_verify = result.verify_no;
  benchmark.rate = result.rate;

  return EFT_OK;
}

void eftControl::tick() {
  
}