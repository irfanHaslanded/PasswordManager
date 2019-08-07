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

void Users::logout(string name) {
  auto search = data.find(name);
  if (search == data.end()) {
    return;
  }
  return search->second.logout();
}

bool Users::createUser(string name, string password) {
  if (data.count(name)) {
    return false;
  }
  data.emplace(make_pair(name, UserData(password)));
  return true;
}

bool Users::deleteUser(string name) {
  if (!data.count(name)) {
    return false;
  }
  data.erase(name);
  return true;
}

string Users::addAccount(string username, string accountname) {
  auto search = data.find(username);
  if (search == data.end()) {
    return "";
  }
  search->second.addAccount(accountname);
  return search->second.getAccountPassword(accountname);
}

string Users::getPassword(string username, string accountname) {
  auto search = data.find(username);
  if (search == data.end()) {
    return "";
  }
  return search->second.getAccountPassword(accountname);
}

bool Users::deleteAccount(string username, string accountname) {
  auto search = data.find(username);
  if (search == data.end()) {
    return false;
  }
  search->second.removeAccount(accountname);
  return true;
}

bool Users::doesUserExist(string name) {
  auto search = data.find(name);
  return search != data.end();
}

bool Users::validatePassword(string name, string password) {
  auto search = data.find(name);
  if (search == data.end()) {
    return false;
  }
  return search->second.login(password);
}

string Users::showAccounts(string name) {
  string s("");
  auto search = data.find(name);
  if (search == data.end()) {
    return s;
  }

  for (auto &d : search->second.getAccounts()) {
    s += "\t" + d;
  }
  return s + "\n";
}

ostream &operator<<(ostream &out, const Users &users) {
  for (auto const &p : users.data) {
    out << "{ " << p.first << " = " << p.second << " }, ";
  }
  return out;
}

istream &operator>>(istream &in, Users &users) {
  string discard;
  string username;
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
