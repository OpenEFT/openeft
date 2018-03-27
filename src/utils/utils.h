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

  /* boost toolbox */
  uint32_t get_thread_id();
  uint32_t get_process_id();

  /* openssl toolbox */
  void sha_256(string str, uint8_t outputBuffer[SHA256_DIGEST_LENGTH * 2 + 1]);
  void sha_512(string str, uint8_t outputBuffer[SHA512_DIGEST_LENGTH * 2 + 1]);

  uint32_t sha256_file(uint8_t *path, uint8_t outputBuffer[SHA256_DIGEST_LENGTH * 2 + 1]);
  uint32_t sha512_file(uint8_t *path, uint8_t outputBuffer[SHA512_DIGEST_LENGTH * 2 + 1]);

  
  uint32_t ecdh_gen_keypair(uint32_t nid, EC_KEY* eckey, char* public_key);

  /* Elliptic Curve Diffie Hellman shared secret key generation */
  uint32_t ecdh_derive_secret(EC_KEY* eckey, uint32_t nid, char* peer_key,
                unsigned char* secret, uint32_t* secret_len);
}

#endif /* UTILS_H */
