/**
 * Utilities.h
 *
 * @date Aug 2, 2019
 * @author Irfan M
 *
 * @brief Provides convenience wrappers around crypto functionalities
 *
 * @details Utils to derive cryptographically strong random numbers
 *          Create SHA512 based hashes with 16 byte and 32 byte salts
 *          Derive new passwords from a stored hash
 *
 */

#ifndef SRC_UTILITIES_H_
#define SRC_UTILITIES_H_

#include <stdlib.h>
#include <string>

using namespace std;

namespace IrfanSec {

class Utilities {
public:
  /**
   * @brief Use openssl RAND_bytes to get 'bytes' of crypto strong random data
   * */
  static void getRandomData(unsigned char *buf, size_t bytes);

  static string get16ByteSalt();
  static string get32ByteSalt();

  /**
   * @brief Return a independent strong password of 35 chars long
   * */
  static string getStrongPassword();

  /**
   * @brief User crypt_r to hash a password with the specified salt
   * @return Return the hash as a string
   * */
  static string hashPassword(const string &salt, const string &password);

  /**
   * @brief check if password would result in a specified hash
   * */
  static bool verifyPassword(const string &password, const string &hash);

  /**
   * @brief Derive a password 35 chars long, from salt and password
   * @details PDKDF2 based on sha512
   * */
  static string derivePassword(const string &salt, const string &password);

  virtual ~Utilities();

private:
  Utilities() =
      delete; // utility class, with static functions. no need of objects
};

} /* namespace irfan */

#endif /* SRC_UTILITIES_H_ */
