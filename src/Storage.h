/**
 * Storage.h
 *
 * @date Aug 2, 2019
 *
 * @brief Helper functions to do file i/o
 *
 * @author Irfan M
 */

#ifndef SRC_STORAGE_H_
#define SRC_STORAGE_H_
#include <string>

#include "Users.h"

namespace IrfanSec {

class Storage {
private:
  static const std::string dataFile;

public:
  /**
   * @brief write all data to disk
   * */
  static void write(const Users &users);

  /**
   * @brief read data and construct the Users object
   * */
  static Users read();

  /**
   * @brief delete all data from disk
   * */
  static void remove();

  Storage() = delete;
};

} /* namespace irfan */

#endif /* SRC_STORAGE_H_ */
