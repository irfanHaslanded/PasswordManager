/**
 * UserData.cpp
 *
 * @date Aug 2, 2019
 * @author Irfan M
 */

#include "UserData.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

namespace IrfanSec {
UserData::UserData() {}
UserData::UserData(string password) {
  master_salt = Utilities::get32ByteSalt();
  app_salt = Utilities::get32ByteSalt();
  master_hash = Utilities::hashPassword(master_salt, password);
}

const map<string, string> &UserData::getAccountData() const {
  return account_data;
}

const string &UserData::getAppHash() const { return app_hash; }

const string &UserData::getAppSalt() const { return app_salt; }

const string &UserData::getMasterHash() const { return master_hash; }

const string &UserData::getMasterSalt() const { return master_salt; }

string UserData::addAccount(const string &account) {
  string salt = Utilities::get16ByteSalt();

  account_data.emplace(make_pair(account, salt));

  return Utilities::derivePassword(salt, account + app_hash);
}

string UserData::getAccountPassword(const string &account) {
  auto search = account_data.find(account);
  if (search == account_data.end()) {
    return "";
  }
  string salt = search->second;
  return Utilities::derivePassword(salt, account + app_hash);
}

vector<string> UserData::getAccounts() {
  vector<string> result;
  for (auto const &p : account_data) {
    result.push_back(p.first);
  }
  return result;
}

bool UserData::removeAccount(const string &account) {
  if (account_data.count(account)) {
    account_data.erase(account);
    return true;
  } else {
    return false;
  }
}

bool UserData::login(const string &password) {
  string computedHash = Utilities::hashPassword(master_salt, password);
  if (computedHash.compare(master_hash)) {
    return false;
  }
  app_hash = Utilities::hashPassword(app_salt, password);
  return true;
}

void UserData::logout() { app_hash = ""; }

void UserData::reset() {
  app_salt = "";
  master_hash = "";
  master_salt = "";
  account_data.clear();
}

istream &operator>>(istream &in, UserData &data) {
  data.reset();
  string discard;
  int count = 0;
  in >> discard                      // "{"
      >> discard                     // " app_salt: "
      >> data.app_salt >> discard    // " master_hash: "
      >> data.master_hash >> discard // " master_salt: "
      >> data.master_salt >> discard // " accounts: "
      >> count >> discard            //" [ ";
      ;
  string key;
  string value;

  while (count-- > 0) {
    in >> discard           /* "{" */
        >> key >> discard   // "="
        >> value >> discard // "},"
        ;

    data.account_data.insert(make_pair(key, value));
  }
  in >> discard >> discard; // discard the trailing "] } "
  return in;
}
ostream &operator<<(ostream &out, const UserData &data) {
  out << "{ "
      << " app_salt: " << data.app_salt << " master_hash: " << data.master_hash
      << " master_salt: " << data.master_salt
      << " accounts: " << data.account_data.size() << " [ ";

  for (auto const &p : data.account_data) {
    out << "{ " << p.first << " = " << p.second << " }, ";
  }

  out << "] }";

  return out;
}

} /* namespace irfan */
