/**
 * Users.h
 *
 * @author Irfan M
 * @date Aug 2, 2019
 */

#ifndef SRC_USERS_H_
#define SRC_USERS_H_

#include <iostream>
#include <map>

#include "UserData.h"

namespace IrfanSec {
class Users {
public:
  bool createUser(std::string name, std::string password);
  bool deleteUser(std::string name);
  bool doesUserExist(std::string name);

  bool validatePassword(std::string name, std::string password);

  void logout(std::string name);

  std::string addAccount(std::string username, std::string accountname);
  std::string getPassword(std::string username, std::string accountname);
  bool deleteAccount(std::string username, std::string accountname);
  std::string showAccounts(std::string name);

  friend std::ostream &operator<<(std::ostream &out, const Users &users);
  friend std::istream &operator>>(std::istream &in, Users &users);

private:
  std::map<std::string, UserData> data;
};

} /* namespace irfan */

#endif /* SRC_USERS_H_ */
