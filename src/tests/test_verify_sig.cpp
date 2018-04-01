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
#include "log/log.h"
#include "test_verify_sig.h"

eftTestVerifySig::eftTestVerifySig() {

}

eftTestVerifySig::~eftTestVerifySig() {

}

void eftTestVerifySig::tick() {

}

uint32_t eftTestVerifySig::run() {
  EC_KEY* key = NULL;
  char* public_key = NULL;
  ECDSA_SIG* signature = NULL;
  uint32_t verified = 0;
  uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1];
  memset(hash_out, 0x00, sizeof (hash_out));

  auto start_time = std::chrono::steady_clock::now();

  eft::ec_gen_keypair(NID_secp256k1, &key, public_key);

  unsigned char *pubkey, *privkey;
  int pubkey_len, privkey_len;

  eft::ec_to_raw_pp(key, &pubkey, pubkey_len, &privkey, privkey_len);
  logb(LOG_DEBUG, "Public key bytes:", pubkey, pubkey_len);
  logb(LOG_DEBUG, "Private key bytes:", privkey, privkey_len);
  OPENSSL_free(pubkey);
  pubkey = NULL;
  eft::ec_get_pubkey(privkey, privkey_len, &pubkey, pubkey_len);
  logb(LOG_DEBUG, "Public key bytes derived from the private key:", pubkey, pubkey_len);
  OPENSSL_free(pubkey);
  OPENSSL_free(privkey);

  std::string rand_str = eft::random_string(256);
  eft::sha_256(rand_str.c_str(), hash_out);

  log(LOG_DEBUG, "Random string:\n[%s]", rand_str.c_str());
  log(LOG_DEBUG, "Hash:\n[%s]", hash_out);

  eft::ecdsa_signature(key, std::string((char*) hash_out), &signature);
  eft::ecdsa_verify(key, std::string((char*) hash_out), signature, verified);

  log(LOG_DEBUG, "Verify code [%d]", verified);

  auto stop_time = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
          stop_time - start_time);


  cur_test_result.duration = static_cast<double> (duration.count());
  cur_test_result.nid = NID_secp256k1;
  cur_test_result.verify_no = 1;
  cur_test_result.rate = 1;

  return EFT_OK;
}

uint32_t eftTestVerifySig::stop(TestResult& result) {
  last_test_result = cur_test_result;
  result = cur_test_result;

  return EFT_OK;
}
