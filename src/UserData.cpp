/**
 * UserData.cpp
 *
 * @date Aug 2, 2019
 * @author Irfan M
 */

#include "UserData.h"
#include "Utilities.h"
#include <iostream>

namespace IrfanSec {
UserData::UserData() {}
UserData::UserData(std::string password) {
  master_salt = Utilities::get32ByteSalt();
  app_salt = Utilities::get32ByteSalt();
  master_hash = Utilities::hashPassword(master_salt, password);
}

const std::map<std::string, std::string> &UserData::getAccountData() const {
  return account_data;
}

const std::string &UserData::getAppHash() const { return app_hash; }

const std::string &UserData::getAppSalt() const { return app_salt; }

const std::string &UserData::getMasterHash() const { return master_hash; }

const std::string &UserData::getMasterSalt() const { return master_salt; }

std::string UserData::addAccount(const std::string &account) {
  std::string salt = Utilities::get16ByteSalt();

  account_data.emplace(make_pair(account, salt));

  return Utilities::derivePassword(salt, account + app_hash);
}

std::string UserData::getAccountPassword(const std::string &account) {
  auto search = account_data.find(account);
  if (search == account_data.end()) {
    return "";
  }
  std::string salt = search->second;
  return Utilities::derivePassword(salt, account + app_hash);
}

std::vector<std::string> UserData::getAccounts() {
  std::vector<std::string> result;
  for (auto const &p : account_data) {
    result.push_back(p.first);
  }
  return result;
  }

  bool UserData::removeAccount(const std::string &account) {
    if (account_data.count(account)) {
      account_data.erase(account);
      return true;
    } else {
      return false;
    }
  }

  bool UserData::login(const std::string &password) {
    std::string computedHash = Utilities::hashPassword(master_salt, password);
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

  std::istream &operator>>(std::istream &in, UserData &data) {
    data.reset();
    std::string discard;
    int count = 0;
    in >> discard                      // "{"
        >> discard                     // " app_salt: "
        >> data.app_salt >> discard    // " master_hash: "
        >> data.master_hash >> discard // " master_salt: "
        >> data.master_salt >> discard // " accounts: "
        >> count >> discard            //" [ ";
        ;
    std::string key;
    std::string value;

    while (count-- > 0) {
      in >> discard           /* "{" */
          >> key >> discard   // "="
          >> value >> discard // "},"
          ;

      data.account_data.insert(std::make_pair(key, value));
    }
    in >> discard >> discard; // discard the trailing "] } "
    return in;
  }
  std::ostream &operator<<(std::ostream &out, const UserData &data) {
    out << "{ "
        << " app_salt: " << data.app_salt
        << " master_hash: " << data.master_hash
        << " master_salt: " << data.master_salt
        << " accounts: " << data.account_data.size() << " [ ";

    for (auto const &p : data.account_data) {
      out << "{ " << p.first << " = " << p.second << " }, ";
    }

    out << "] }";

    return out;
  }


} /* namespace irfan */
