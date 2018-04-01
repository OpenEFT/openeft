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

  uint32_t split_str(const std::string &txt, std::vector<std::string> &strs, char ch) {
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    while (pos != std::string::npos) {
      strs.push_back(txt.substr(initialPos, pos - initialPos));
      initialPos = pos + 1;

      pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return (uint32_t) strs.size();
  }

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

  std::string random_string(uint32_t length) {
    auto randchar = []() -> char {
      const char charset[] =
              "0123456789"
              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
              "abcdefghijklmnopqrstuvwxyz";
      const size_t max_index = (sizeof (charset) - 1);
      return charset[ rand() % max_index ];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
  }

  void sha_256(const char *str, uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1]) {
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);

    for (uint32_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      sprintf((char*) hash_out + (i * 2), "%02x", hash[i]);
    }

    return;
  }

  uint32_t sha256_file(const char *path, uint8_t hash_out[SHA256_DIGEST_LENGTH * 2 + 1]) {
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
      sprintf((char*) hash_out + (i * 2), "%02x", hash[i]);
    }

    fclose(file);
    free(buffer);

    return EFT_OK;
  }

  void sha_512(const char *str, uint8_t hash_out[SHA512_DIGEST_LENGTH * 2 + 1]) {
    uint8_t hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, str, strlen(str));
    SHA512_Final(hash, &sha512);

    for (uint32_t i = 0; i < SHA512_DIGEST_LENGTH; i++) {
      sprintf((char*) hash_out + (i * 2), "%02x", hash[i]);
    }

    return;
  }

  uint32_t sha512_file(const char *path, uint8_t hash_out[SHA512_DIGEST_LENGTH * 2 + 1]) {
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
      sprintf((char*) hash_out + (i * 2), "%02x", hash[i]);
    }

    fclose(file);
    free(buffer);

    return EFT_OK;
  }

  uint32_t ec_gen_keypair(uint32_t nid,
          EC_KEY** ec_keypair,
          char* public_key) {

    EC_KEY* ec_key = NULL;
    if (NULL == (ec_key = EC_KEY_new_by_curve_name(nid))) {
      log(LOG_ERR, "Failed to set the DH curve name.");
      return EFT_NOK;
    }

    if (1 != EC_KEY_generate_key(ec_key)) {
      log(LOG_ERR, "Failed to generate a key pair.");
      return EFT_NOK;
    }

    public_key =
            EC_POINT_point2hex(EC_KEY_get0_group(ec_key),
            EC_KEY_get0_public_key(ec_key),
            POINT_CONVERSION_COMPRESSED,
            NULL);

    log(LOG_DEBUG, "Public key:\n[%s]", public_key);
    log(LOG_DEBUG, "Private key:\n[%s]", BN_bn2hex(EC_KEY_get0_private_key(ec_key)));

    *ec_keypair = ec_key;
    return EFT_OK;
  }
  
  uint32_t ec_to_raw_pp(const EC_KEY* ec_keypair,
                          unsigned char **public_key, int& pubkey_len,
                          unsigned char **private_key, int& privkey_len) {
    const EC_POINT* pub_point = NULL;
    const BIGNUM *priv_bn = NULL;
    unsigned char *pubkey = NULL, *privkey = NULL;
    const EC_GROUP *ec_group = NULL;
    size_t pubkey_hex_size, privkey_hex_size;
    
    ec_group = EC_KEY_get0_group(ec_keypair);
    
    pub_point = EC_KEY_get0_public_key(ec_keypair);
    priv_bn = EC_KEY_get0_private_key(ec_keypair);
    
    pubkey_hex_size = 
            EC_POINT_point2oct(ec_group, pub_point, POINT_CONVERSION_COMPRESSED, 0, 0, 0);
    pubkey = (unsigned char*)OPENSSL_malloc(pubkey_hex_size);
    
    EC_POINT_point2oct(ec_group, pub_point, POINT_CONVERSION_COMPRESSED, 
                      pubkey, pubkey_hex_size, 0);
    
    
    privkey_hex_size = BN_num_bytes(priv_bn);
    privkey = (unsigned char*)OPENSSL_malloc(privkey_hex_size);
    BN_bn2bin(priv_bn, privkey);
    
    pubkey_len = pubkey_hex_size;
    privkey_len = privkey_hex_size;
    
    *public_key = pubkey;
    *private_key = privkey;  
    
    return EFT_OK;
  }

  uint32_t ec_get_pubkey(unsigned char *raw_privkey, int privkey_len,
            unsigned char **pubkey, int& pubkey_len) {
    BN_CTX *ctx;
    EC_KEY *privkey;
    const EC_GROUP *group;
    EC_POINT *pubkey_point;
    BIGNUM *bn_privkey, *bn_pubkey;

    bn_privkey = BN_bin2bn(raw_privkey, privkey_len, NULL);

    privkey = EC_KEY_new_by_curve_name(NID_secp256k1);
    group = EC_KEY_get0_group(privkey);
    pubkey_point = EC_POINT_new(group);
    EC_KEY_set_private_key(privkey, bn_privkey);
    
    ctx = BN_CTX_new();
    bn_pubkey = BN_new();
    
    EC_POINT_mul(group, pubkey_point, bn_privkey, NULL, NULL, ctx);
    bn_pubkey = EC_POINT_point2bn(group, pubkey_point,
            POINT_CONVERSION_COMPRESSED, bn_pubkey, ctx);
    
    *pubkey = (unsigned char *) malloc(sizeof (unsigned char) * (BN_num_bytes(bn_pubkey) + 1));
    pubkey_len = BN_num_bytes(bn_pubkey);
    
    BN_free(bn_pubkey);
    EC_POINT_free(pubkey_point);
    EC_KEY_free(privkey);
    BN_CTX_free(ctx);
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

  uint32_t ecdsa_signature(EC_KEY* eckey, std::string hash, ECDSA_SIG** sig) {
    uint32_t len = 0;
    ECDSA_SIG* signature = NULL;
    do {
      signature = ECDSA_do_sign((const uint8_t*) hash.c_str(), hash.length(), eckey);
      if (NULL == signature) {
        log(LOG_ERR, "Failed to generate ECDSA signature.");
        return EFT_NOK;
      }

      len = i2d_ECDSA_SIG(signature, NULL);
    } while (len != 0x48);

    uint8_t *der, *der_copy;
    uint32_t der_sig_len;
    der = (uint8_t*) OPENSSL_malloc(len);
    der_copy = der;
    der_sig_len = i2d_ECDSA_SIG(signature, &der_copy);

    logb(LOG_DEBUG, "ECDSA signature:", der, len);

    OPENSSL_free(der);

    *sig = signature;
    return EFT_OK;
  }

  uint32_t ecdsa_verify(EC_KEY* eckey, std::string hash, const ECDSA_SIG* sig, uint32_t& verified) {
    uint32_t verify_status = ECDSA_do_verify((const uint8_t*) hash.c_str(), hash.length(), sig, eckey);
    if (verify_status == -1) {
      log(LOG_ERR, "Error in signature verification process.");
      return EFT_NOK;
    }

    verified = verify_status;

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

  template<typename T> std::array<unsigned char, sizeof (T) > to_bytes(const T& object) {
    std::array<unsigned char, sizeof (T) > bytes;

    const unsigned char* begin = reinterpret_cast<const unsigned char*> (std::addressof(object));
    const unsigned char* end = begin + sizeof (T);
    std::copy(begin, end, std::begin(bytes));

    return bytes;
  }

  template<typename T>
  T& from_bytes(const std::array<unsigned char, sizeof (T)>& bytes, T& object) {
    static_assert(std::is_trivially_copyable<T>::value, "not a TriviallyCopyable type");

    unsigned char* begin_object = reinterpret_cast<unsigned char*> (std::addressof(object));
    std::copy(std::begin(bytes), std::end(bytes), begin_object);

    return object;
  }

  uint32_t enc_base64(const std::string &data_str, std::string &base64_str) {
    typedef insert_linebreaks<base64_from_binary
            <transform_width<string::const_iterator, 6, 8> >, 96> it_base64_t;

    unsigned int write_pad_char = (3 - data_str.length() % 3) % 3;
    std::string str(it_base64_t(data_str.begin()), it_base64_t(data_str.end()));
    str.append(write_pad_char, '=');
    base64_str = str;

    return EFT_OK;
  }

  uint32_t dec_base64(const std::string& base64_str, std::string &data_str) {
    typedef transform_width< binary_from_base64
            <remove_whitespace<string::const_iterator> >, 8, 6> it_binary_t;

    std::string base64_input = base64_str;
    unsigned int padded_char = count(base64_input.begin(), base64_input.end(), '=');
    std::replace(base64_input.begin(), base64_input.end(), '=', 'A');
    std::string str(it_binary_t(base64_str.begin()), it_binary_t(base64_str.end()));
    str.erase(str.end() - padded_char, str.end());
    data_str = str;

    return EFT_OK;
  }

}
