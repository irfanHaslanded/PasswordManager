/**
 * Users.cpp
 *
 * @date Aug 2, 2019
 * @author Irfan M
 *
 */

#include "Users.h"
#include <cstring>
#include <sstream>

namespace IrfanSec {

void Users::logout(std::string name) {
  auto search = data.find(name);
  if (search == data.end()) {
    return;
  }
  return search->second.logout();
  }

  bool Users::createUser(std::string name, std::string password) {
    if (data.count(name)) {
      return false;
    }
    data.emplace(std::make_pair(name, UserData(password)));
    return true;
  }

  bool Users::deleteUser(std::string name) {
    if (!data.count(name)) {
      return false;
    }
    data.erase(name);
    return true;
  }

  std::string Users::addAccount(std::string username, std::string accountname) {
    auto search = data.find(username);
    if (search == data.end()) {
      return "";
    }
    search->second.addAccount(accountname);
    return search->second.getAccountPassword(accountname);
  }

  std::string Users::getPassword(std::string username,
                                 std::string accountname) {
    auto search = data.find(username);
    if (search == data.end()) {
      return "";
    }
    return search->second.getAccountPassword(accountname);
  }

  bool Users::deleteAccount(std::string username, std::string accountname) {
    auto search = data.find(username);
    if (search == data.end()) {
      return false;
    }
    search->second.removeAccount(accountname);
    return true;
  }

  bool Users::doesUserExist(std::string name) {
    auto search = data.find(name);
    return search != data.end();
  }

  bool Users::validatePassword(std::string name, std::string password) {
    auto search = data.find(name);
    if (search == data.end()) {
      return false;
    }
    return search->second.login(password);
  }

  std::string Users::showAccounts(std::string name) {
    std::string s("");
    auto search = data.find(name);
    if (search == data.end()) {
      return s;
    }

    for (auto &d : search->second.getAccounts()) {
      s += "\t" + d;
    }
    return s + "\n";
  }

  std::ostream &operator<<(std::ostream &out, const Users &users) {
    for (auto const &p : users.data) {
      out << "{ " << p.first << " = " << p.second << " }, ";
    }
    return out;
  }

  std::istream &operator>>(std::istream &in, Users &users) {
    std::string discard;
    std::string username;
    UserData userData;
    while (in >> discard) {
      in >> username >> discard  // =
          >> userData >> discard // },
          ;

      users.data.insert(make_pair(username, userData));
    }
    return in;
  }
} /* namespace irfan */
