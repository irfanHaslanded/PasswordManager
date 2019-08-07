#include <sstream>
#include <string>

extern "C" {

#include <termios.h>
#include <unistd.h>
}

#include "PasswordManager.h"
#include "Storage.h"

namespace IrfanSec {

PasswordManager::~PasswordManager() {
  Storage::write(users); // upon exit, write the data to disk storage
}

void PasswordManager::start() {
  prompt = "passMgr> ";

  while (true) { // Forever read the cli input
    char buf[1024];
    std::cout << prompt;
    std::flush(std::cout);

    std::cin.getline(buf, sizeof(buf));

    execute(buf); // validate and execute the user commands
    std::cout << std::endl;
  }
  }

  PasswordManager::PasswordManager() {
    users = Storage::read(); // Load all data from disk on startup
    isLoggedIn = "";
  }

  static bool isCommand(std::string cmd, std::string token) {
    return 0 == cmd.compare(0, token.length(), token);
  }

  static void helpText() {
    std::cout
        << "signup \t Create a new passMgr user" << std::endl
        << "login  \t Login into a passMgr account" << std::endl
        << "logout \t Logout from the current session" << std::endl
        << "quit   \t Exit the program" << std::endl
        << "exit   \t Exit the program" << std::endl
        << "create-password \t Create a password for the specified account"
        << std::endl
        << "show-password   \t Show the password for the specified account"
        << std::endl
        << "delete-password \t Delete the data related to the specified account"
        << std::endl
        << "show-accounts   \t Show all accounts managed by passMgr for this "
           "user"
        << std::endl
        << "help            \t Print this help text" << std::endl;
  }

  /**
   * @brief Execute a single cmd
   * */
  void PasswordManager::execute(std::string cmd) {
    if (cmd.length() == 0) {

    } else if (isCommand(cmd, "help")) {
      helpText();
    } else if (isCommand(cmd, "signup")) {
      if (signup()) {
        Storage::write(users);
      }
    } else if (isCommand(cmd, "login")) {
      login();
    } else if (isCommand(cmd, "quit") || isCommand(cmd, "exit")) {
      exit(0);
    } else if (!isLoggedIn) {
      std::cerr << "Not logged in" << std::endl;
    } else if (isCommand(cmd, "logout")) {
      logout();
    } else if (isCommand(cmd, "create-password")) {
      createPassword(cmd);
      Storage::write(users);
    } else if (isCommand(cmd, "show-password")) {
      showPassword(cmd);
    } else if (isCommand(cmd, "delete-password")) {
      deletePassword(cmd);
      Storage::write(users);
    } else if (isCommand(cmd, "show-accounts")) {
      showAccounts();
    } else {
      std::cout << "not implemented <" << cmd << ">" << std::endl;
    }
  }

  static std::string readLoginName() {
    std::string name;
    std::cout << "Enter username: ";
    std::cin >> name;
    if (name.length() <= 0 || name.length() > 30) {
      std::cout << "Invalid user name" << std::endl;
      return "";
    }
    return name;
  }

  static std::string readPassword() {
    std::string password;

    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::cin >> password;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
  }

  bool PasswordManager::login() {
    char buf[32];

    std::string name = readLoginName();
    std::string pass, confirmPass;
    if (name.length() == 0) {
      return false;
    }
    // Check if user exists.
    if (users.doesUserExist(name)) {
      do {
        std::cout << "Enter password: ";
        pass = readPassword();
      } while (!users.validatePassword(name, pass));

    } else {
      std::cout << "No such user exists" << std::endl;
      return false;
    }

    prompt =
        name + "@" + prompt; // Change the prompt so we know who is logged in
    loggedInUser = name;
    isLoggedIn = true;
    std::cin.getline(buf, sizeof(buf));
    return true;
  }

  void PasswordManager::logout() {
    users.logout(loggedInUser);

    prompt = "passMgr> "; // Set the prompt back to default logged out state
    loggedInUser = "";
    isLoggedIn = false;
  }

  void PasswordManager::createPassword(std::string cmd) {
    std::stringstream ss(cmd);
    std::string discard;
    std::string account;
    ss >> discard;
    ss >> account;
    if (users.getPassword(loggedInUser, account).length() > 0) {
      std::cerr << "Account already exists" << std::endl;
      return;
    }
    std::string password = users.addAccount(loggedInUser, account);
    std::cout << "Password for " << account << " is: " << password << std::endl;
  }

  void PasswordManager::showPassword(std::string cmd) {
    std::stringstream ss(cmd);
    std::string account;
    std::string discard;
    ss >> discard;
    ss >> account;
    if (account.length() == 0) {
      std::cerr << "Specify an account" << std::endl;
      return;
    }
    std::string password = users.getPassword(loggedInUser, account);
    if (password.length() == 0) {
      std::cerr << "account does not exist: " << account << std::endl;
    } else {
      std::cout << "Password is: " << password << std::endl;
    }
  }

  void PasswordManager::deletePassword(std::string cmd) {
    std::stringstream ss(cmd);
    std::string account;
    std::string discard;
    ss >> discard;
    ss >> account;
    if (account.length() == 0) {
      std::cerr << "Specify account to delete" << std::endl;
      return;
    }
    if (users.deleteAccount(loggedInUser, account)) {
      std::cout << "Account deleted: " << account << std::endl;
    } else {
      std::cerr << "Account does not exist: " << account << std::endl;
    }
  }

  bool PasswordManager::signup() {
    std::string pass;
    std::string confirmPass;
    std::string name = readLoginName();
    // Create the user
    if (users.doesUserExist(name)) {
      std::cout << "User name is not available" << std::endl;
      return false;
    }
    do {

      std::cout << "Enter Master Password: ";
      pass = readPassword();

      std::cout << std::endl << "Confirm master password: ";
      confirmPass = readPassword();

    } while (pass.compare(confirmPass) != 0);

    if (users.createUser(name, pass)) {
      std::cout << "Successfully generated a master password." << std::endl;
      return true;
    }
    return false;
  }

  void PasswordManager::showAccounts() {
    std::cout << users.showAccounts(loggedInUser);
  }

} /* namespace irfan */

int main(int argc, char **argv) {
  IrfanSec::PasswordManager mgr;
  mgr.start();
  return 0;
}
