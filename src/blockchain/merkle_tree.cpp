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

#ifndef _OPENEFT_MERKLE_TREE_CPP
#define _OPENEFT_MERKLE_TREE_CPP

#include "global.h"
#include "merkle_tree.h"

eftMerkleTree::eftMerkleTree() {
  
}

eftMerkleTree::~eftMerkleTree() {
  
}

uint32_t compute_root(const vector<std::string> &list, std::string &hash) {

  uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1] = {0};
  uint8_t hash_out_left[SHA256_DIGEST_LENGTH * 2 + 1] = {0};
  uint8_t hash_out_right[SHA256_DIGEST_LENGTH * 2 + 1] = {0};
  
  if(list.empty())
    return EFT_NOK;
  if(list.size() == 1) {
    eft::sha_256(list[0].c_str(), hash_out);
    hash = (char*)hash_out;
    return EFT_OK;
  }

  vector<string> merkle = list;
  while (merkle.size() > 1) {
    if (merkle.size() % 2 == 1) /* if odd */
      merkle.push_back(merkle.back()); /* copying the left leaf to the right */

    vector<string> result;

    for (int i = 0; i < merkle.size(); i += 2) {
      
      eft::sha_256(merkle[i].c_str(), hash_out_left);
      eft::sha_256(merkle[i + 1].c_str(), hash_out_right);
      
      std::string combined = std::string((char*)hash_out_left) +
                              std::string((char*)hash_out_right);
      
      eft::sha_256(combined.c_str(), hash_out);

      result.push_back((char*)hash_out);
    }
    merkle = result;
  }

  hash = merkle[0];
  return EFT_OK;
}

#endif /* MERKLE_TREE_CPP */

