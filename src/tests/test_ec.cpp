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

#include "eftclass.h"
#include "test_ec.h"

eftTestEc::eftTestEc() {
  
}

eftTestEc::~eftTestEc() {
  
}

void eftTestEc::tick() {
  
}

uint32_t eftTestEc::run() {
  EC_KEY* key;
  char* public_key;
  
  auto start_time = std::chrono::steady_clock::now();

  eft::ec_gen_keypair(NID_secp256k1, key, public_key);
  
  auto stop_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
          stop_time - start_time);
  cur_test_result.duration = static_cast<double> (duration.count());
  cur_test_result.nid = NID_secp256k1;
  cur_test_result.keypair_no = 1;
  cur_test_result.rate = 1;

  return EFT_OK;
}

uint32_t eftTestEc::stop(TestResult& result) {
  last_test_result = cur_test_result;
  result = cur_test_result;
  
  return EFT_OK;
}
