/**
 * UserData.h
 *
 * Created on: Aug 2, 2019
 *
 * @author Irfan M
 *
 * @brief Class that handles all data related to a single user
 *
 */

#ifndef SRC_USERDATA_H_
#define SRC_USERDATA_H_

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace IrfanSec {

class UserData {
public:
  /**
   * @brief creates a UserData object
   * @details Initializes the master_hash, master_salt, and app_salt with the
   * master_password input
   * */
  UserData(string master_password);
  UserData();

  void reset();

  const map<string, string> &getAccountData() const;

  const string &getAppHash() const;

  const string &getAppSalt() const;

  const string &getMasterHash() const;

  const string &getMasterSalt() const;

  /**
   * @brief Derive a password for the specified account
   * */
  string addAccount(const string &account);

  bool removeAccount(const string &account);

  /**
   * @brief Validate the master password and login the user
   * @details Generate the app hash to create accounts
   * */
  bool login(const string &password);
  void logout();

  string getAccountPassword(const string &account);

  /**
   * @brief Get a list of all accounts
   * */
  vector<string> getAccounts();

  friend ostream &operator<<(ostream &out, const UserData &data);
  friend istream &operator>>(istream &in, UserData &data);

private:
  string master_salt;
  string master_hash;               // for validating users
  string app_salt;                  // to derive app_hash
  string app_hash;                  // to derive passwords
  map<string, string> account_data; // all the accounts of this user
};

} /* namespace irfan */

#endif /* SRC_USERDATA_H_ */
