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

#ifndef _OPENEFT_UTILS_H
#define _OPENEFT_UTILS_H

#include "global.h"


namespace eft {

  void ltrim(std::string &s);
  void rtrim(std::string &s);
  void trim(std::string &s);
  std::string ltrim_copy(std::string s);
  std::string rtrim_copy(std::string s);
  std::string trim_copy(std::string s);

  void read_file_str(const std::string& filename, std::string& data);

  uint32_t split_str(const std::string &txt,
    std::vector<std::string> &strs, char ch);

  /* boost toolbox */
  uint32_t get_thread_id();
  uint32_t get_process_id();

  std::string random_string(uint32_t length);

  /* openssl toolbox */
  void sha_256(const char *str, uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1]);
  void sha_512(const char *str, uint8_t hash_out[SHA512_DIGEST_LENGTH * 2 + 1]);

  uint32_t sha256_file(uint8_t *path, uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1]);
  uint32_t sha512_file(uint8_t *path, uint8_t hash_out[SHA512_DIGEST_LENGTH * 2 + 1]);

  /* Elliptic Curve keypair generation */
  uint32_t ec_gen_keypair(uint32_t nid, EC_KEY** ec_keypair, char* public_key);

  uint32_t ec_to_raw_pp(const EC_KEY* ec_keypair,
    unsigned char **pubkey, int& pubkey_len,
    unsigned char **privkey, int& privkey_len);

  /* get public key from the input private key */
  uint32_t ec_get_pubkey(unsigned char *raw_privkey, int privkey_len,
    unsigned char **pubkey, int& pubkey_len);

  /* Elliptic Curve Diffie Hellman shared secret key generation */
  uint32_t ecdh_derive_secret(EC_KEY* eckey,
    uint32_t nid,
    char* peer_key,
    char** secret);

  uint32_t ecdsa_signature(EC_KEY* eckey, std::string hash, ECDSA_SIG** sig);
  uint32_t ecdsa_verify(EC_KEY* eckey, std::string hash,
    const ECDSA_SIG* sig, uint32_t& verified);

  void hex_to_bytes(const std::string& hex, unsigned char* buffer);
  std::string bytes_to_hex(const unsigned char* buffer, uint32_t size);

  template<typename T> std::array<unsigned char, sizeof (T) > to_bytes(const T& object);
  template<typename T>
  T& from_bytes(const std::array<unsigned char, sizeof (T)>& bytes, T& object);

  uint32_t enc_base64(const std::string &data_str, std::string &base64_str);
  uint32_t dec_base64(const std::string& base64_str, std::string &data_str);
}

#endif /* UTILS_H */

