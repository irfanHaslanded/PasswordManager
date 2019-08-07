/**
 * GNU General Public License v3.0
 * Permissions of this strong copyleft license are conditioned
 * on making available complete source code of licensed works and modifications,
 * which include larger works using a licensed work, under the same license.
 * Copyright and license notices must be preserved.
 * Contributors provide an express grant of patent rights.
 * */

/**
 * PasswordManager.h
 *
 * @date Aug 2, 2019
 * @author Irfan M
 */

#ifndef SRC_PASSWORDMANAGER_H_
#define SRC_PASSWORDMANAGER_H_

#include "Users.h"

namespace IrfanSec {

class PasswordManager {
public:
  PasswordManager();
  virtual ~PasswordManager();
  void start();
  void execute(std::string cmd);
  bool signup();
  bool login();
  void logout();
  void createPassword(std::string cmd);
  void showPassword(std::string cmd);
  void deletePassword(std::string cmd);
  void showAccounts();

private:
  Users users;
  std::string prompt;
  std::string loggedInUser;
  bool isLoggedIn;
};

} /* namespace irfan */

#endif /* SRC_PASSWORDMANAGER_H_ */
