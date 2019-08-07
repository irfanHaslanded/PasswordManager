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

namespace IrfanSec {

class UserData {
public:
  /**
   * @brief creates a UserData object
   * @details Initializes the master_hash, master_salt, and app_salt with the
   * master_password input
   * */
  UserData(std::string master_password);
  UserData();

  void reset();

  const std::map<std::string, std::string> &getAccountData() const;

  const std::string &getAppHash() const;

  const std::string &getAppSalt() const;

  const std::string &getMasterHash() const;

  const std::string &getMasterSalt() const;

  /**
   * @brief Derive a password for the specified account
   * */
  std::string addAccount(const std::string &account);

  bool removeAccount(const std::string &account);

  /**
   * @brief Validate the master password and login the user
   * @details Generate the app hash to create accounts
   * */
  bool login(const std::string &password);
  void logout();

  std::string getAccountPassword(const std::string &account);

  /**
   * @brief Get a list of all accounts
   * */
  std::vector<std::string> getAccounts();

  friend std::ostream &operator<<(std::ostream &out, const UserData &data);
  friend std::istream &operator>>(std::istream &in, UserData &data);

private:
  std::string master_salt;
  std::string master_hash; // for validating users
  std::string app_salt;    // to derive app_hash
  std::string app_hash;    // to derive passwords
  std::map<std::string, std::string>
      account_data; // all the accounts of this user
};

} /* namespace irfan */

#endif /* SRC_USERDATA_H_ */
