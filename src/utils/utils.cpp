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
#include "utils.h"

namespace eft {

  uint32_t get_thread_id() {
    std::string thread_id = boost::lexical_cast<std::string>(boost::this_thread::get_id());
    uint32_t thread_no = 0;
    sscanf(thread_id.c_str(), "%x", &thread_no);
    return thread_no;
  }

  uint32_t get_process_id() {
    std::string proc_id = boost::lexical_cast<std::string>(boost::this_process::get_id());
    uint32_t proc_no = 0;
    sscanf(proc_id.c_str(), "%x", &proc_no);
    return proc_no;
  }

  void sha_256(const char *str, char outputBuffer[SHA256_DIGEST_LENGTH * 2 + 1]) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);

    for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    return;
  }

  uint32_t sha256_file(const char *path, char outputBuffer[SHA256_DIGEST_LENGTH * 2 + 1]) {
    FILE *file = fopen(path, "rb");
    if (!file)
      return EFT_NOK;

    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    const int bufSize = 32768;
    uint8_t *buffer = (uint8_t*) malloc(bufSize);
    uint32_t bytesRead = 0;
    if (!buffer)
      return ENOMEM;

    while ((bytesRead = fread(buffer, 1, bufSize, file))) {
      SHA256_Update(&sha256, buffer, bytesRead);
    }
    SHA256_Final(hash, &sha256);

    for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    fclose(file);
    free(buffer);

    return EFT_OK;
  }

  void sha_512(const char *str, char outputBuffer[SHA512_DIGEST_LENGTH * 2 + 1]) {
    uint8_t hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, str, strlen(str));
    SHA512_Final(hash, &sha512);

    for (uint32_t i = 0; i < SHA512_DIGEST_LENGTH; i++) {
      sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    return;
  }

  uint32_t sha512_file(const char *path, char outputBuffer[SHA512_DIGEST_LENGTH * 2 + 1]) {
    FILE *file = fopen(path, "rb");
    if (!file)
      return EFT_NOK;

    uint8_t hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    const int bufSize = 32768;
    uint8_t *buffer = (uint8_t*) malloc(bufSize);
    uint32_t bytesRead = 0;
    if (!buffer)
      return ENOMEM;

    while ((bytesRead = fread(buffer, 1, bufSize, file))) {
      SHA512_Update(&sha512, buffer, bytesRead);
    }
    SHA512_Final(hash, &sha512);

    for (uint32_t i = 0; i < SHA512_DIGEST_LENGTH; i++) {
      sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    fclose(file);
    free(buffer);

    return EFT_OK;
  }

}