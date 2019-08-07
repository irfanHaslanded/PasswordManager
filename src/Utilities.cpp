/**
 * Utilities.cpp
 *
 * @date Aug 2, 2019
 * @author Irfan M
 */

extern "C" {
#include <crypt.h>
#include <unistd.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
}

#include <iostream>

#include "Utilities.h"

namespace IrfanSec {
/**
 * @brief convert raw bytes to a valid salt
 * @details salt contains only [a-zA-Z0-9./]
 * */
static std::string saltify(unsigned char *buf, size_t bytes) {
  const char salt_chars[] =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890./";
  size_t width = sizeof(salt_chars) - 1;
  char result[bytes];

  for (size_t i = 0; i < bytes - 1; i++) {
    result[i] = salt_chars[buf[i] % width];
  }
  result[bytes - 1] = '\0';

  return std::string(result);
  }

  /**
   * @brief convert raw bytes to a string of printable/visible chars
   * @details ascii values from ! to ~ are all valid chars for passwords
   * */
  static std::string textify(unsigned char *buf, size_t bytes) {
    char start = '!';
    char end = '~';
    size_t width = 1 + end - start;

    char result[bytes];
    for (size_t i = 0; i < bytes - 1; i++) {
      result[i] = start + buf[i] % width;
    }
    result[bytes - 1] = '\0';

    return std::string(result);
  }

  /**
   * @brief Extract salt from a hash of the format $n$xxxxxxx$yyyyyyyyyy
   * @return $n$xxxxxxx$
   * */
  static std::string extractSalt(const std::string &hash) {
    std::string salt("");
    for (int i = 3; i < hash.length(); i++) {
      if (hash.at(i) == '$') {
        salt = hash.substr(0, i + 1);
      }
    }
    return salt;
  }

  void Utilities::getRandomData(unsigned char *buf, size_t bytes) {
    RAND_bytes((unsigned char *)buf, bytes);
  }

  std::string Utilities::get16ByteSalt() {
    unsigned char buf[17];
    getRandomData(buf, sizeof(buf));
    return "$6$" + saltify(buf, sizeof(buf)) + "$";
  }

  std::string Utilities::get32ByteSalt() {
    unsigned char buf[33];
    getRandomData(buf, sizeof(buf));
    return "$6$" + saltify(buf, sizeof(buf)) + "$";
  }

  std::string Utilities::getStrongPassword() {
    unsigned char buf[36];
    getRandomData(buf, sizeof(buf));
    return textify(buf, sizeof(buf));
  }

  std::string Utilities::hashPassword(const std::string &salt,
                                      const std::string &password) {
    crypt_data data;
    char *str = crypt_r(password.c_str(), salt.c_str(), &data);
    return std::string(str);
  }

  bool Utilities::verifyPassword(const std::string &password,
                                 const std::string &hash) {
    std::string salt = extractSalt(hash);
    std::string computedHash = hashPassword(salt, password);
    return 0 == hash.compare(computedHash);
  }

  std::string Utilities::derivePassword(const std::string &salt,
                                        const std::string &password) {
    unsigned char buf[36];
    PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                      (unsigned char *)salt.c_str(), salt.length(), 1000,
                      EVP_sha512(), sizeof(buf), buf);
    return textify(buf, sizeof(buf));
  }

} /* namespace irfan */
