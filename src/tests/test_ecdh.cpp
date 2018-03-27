
#include "eftclass.h"
#include "test_ecdh.h"

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

#include "test_ecdh.h"

eftTestEcdh::eftTestEcdh() {
  
}

eftTestEcdh::~eftTestEcdh() {
  
}

void eftTestEcdh::tick() {
  
}

uint32_t eftTestEcdh::run() {
  EC_KEY* key;
  char* public_key;
  char* peer_pub_key;
  unsigned char* secret;
  uint32_t* secret_len;
  eft::ecdh_gen_keypair(NID_X9_62_c2pnb163v1, key, public_key);
  
  /* exchange the public key with peer(s) */
  
  eft::ecdh_derive_secret(key, NID_X9_62_c2pnb163v1,
                      peer_pub_key, secret, secret_len);
}

