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
#include "log/log.h"

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

  uint32_t ecdh_gen_keypair(uint32_t nid,
          EC_KEY* eckey,
          char* public_key) {

    if (NULL == (eckey = EC_KEY_new_by_curve_name(nid))) {
      log(LOG_ERR, "Failed to set the DH curve name.");
      return EFT_NOK;
    }

    if (1 != EC_KEY_generate_key(eckey)) {
      log(LOG_ERR, "Failed to generate a key pair.");
      return EFT_NOK;
    }

    public_key =
            EC_POINT_point2hex(EC_KEY_get0_group(eckey),
            EC_KEY_get0_public_key(eckey),
            POINT_CONVERSION_COMPRESSED,
            NULL);

    log(LOG_DEBUG, "Public key:\n %s", public_key);
    log(LOG_DEBUG, "Private key:\n %s", BN_bn2hex(EC_KEY_get0_private_key(eckey)));

    return EFT_OK;
  }

  uint32_t ecdh_derive_secret(EC_KEY* eckey,
          uint32_t nid,
          char* peer_key,
          char* secret) {
    EC_KEY* peer_pub_eckey;
    EC_POINT* pub = NULL;
    unsigned char* sec;
    unsigned int sec_len;

    uint32_t field_size =
            EC_GROUP_get_degree(EC_KEY_get0_group(eckey));
    sec_len = (field_size + 7) / 8;

    if (NULL == (sec = (unsigned char*) OPENSSL_malloc(sec_len))) {
      log(LOG_ERR, "Failed to allocate openssl object.");
      return EFT_NOK;
    }

    peer_pub_eckey = EC_KEY_new_by_curve_name(nid);
    pub = EC_POINT_hex2point(EC_KEY_get0_group(eckey), peer_key, pub, NULL);
    EC_KEY_set_public_key(peer_pub_eckey, pub);

    /* Derive the shared secret */
    sec_len = ECDH_compute_key(sec,
            sec_len,
            EC_KEY_get0_public_key(peer_pub_eckey),
            eckey,
            NULL);
    
    strcpy(secret, bytes_to_hex(sec, sec_len).c_str());
    
    OPENSSL_free(sec);

    return EFT_OK;
  }

  void hex_to_bytes(const std::string& hex, unsigned char* buffer) {
    std::vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
      std::string byteString = hex.substr(i, 2);
      unsigned char byte = (char) strtol(byteString.c_str(), NULL, 16);
      bytes.push_back(byte);
    }
    
    std::copy(bytes.begin(), bytes.end(), buffer);

    return;
  }

  std::string bytes_to_hex(const unsigned char* buffer, uint32_t size) {
    std::stringstream str;
    str.setf(std::ios_base::hex, std::ios::basefield);
    str.setf(std::ios_base::uppercase);
    str.fill('0');

    for (uint32_t i = 0; i < size; ++i) {
      str << std::setw(2) << (unsigned short) (unsigned char) buffer[i];
    }
    return str.str();
  }

  template< typename T > std::array< unsigned char, sizeof (T) > to_bytes(const T& object) {
    std::array< unsigned char, sizeof (T) > bytes;

    const unsigned char* begin = reinterpret_cast<const unsigned char*> (std::addressof(object));
    const unsigned char* end = begin + sizeof (T);
    std::copy(begin, end, std::begin(bytes));

    return bytes;
  }

  template< typename T >
  T& from_bytes(const std::array< unsigned char, sizeof (T) >& bytes, T& object) {
    static_assert(std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type");

    unsigned char* begin_object = reinterpret_cast<unsigned char*> (std::addressof(object));
    std::copy(std::begin(bytes), std::end(bytes), begin_object);

    return object;
  }

}