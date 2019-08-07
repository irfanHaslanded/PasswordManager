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

using namespace std;

namespace IrfanSec {
class Users {
public:
  bool createUser(string name, string password);
  bool deleteUser(string name);
  bool doesUserExist(string name);

  bool validatePassword(string name, string password);

  void logout(string name);

  string addAccount(string username, string accountname);
  string getPassword(string username, string accountname);
  bool deleteAccount(string username, string accountname);
  string showAccounts(string name);

  friend ostream &operator<<(ostream &out, const Users &users);
  friend istream &operator>>(istream &in, Users &users);

private:
  map<string, UserData> data;
};

} /* namespace irfan */

#endif /* SRC_USERS_H_ */
