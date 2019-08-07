#include <sstream>
#include <string>

#include "PasswordManager.h"
#include "Storage.h"

using namespace std;

namespace IrfanSec {

PasswordManager::~PasswordManager() {
  Storage::write(users); // upon exit, write the data to disk storage
}

void PasswordManager::start() {
  prompt = "passMgr> ";

  while (true) { // Forever read the cli input
    char buf[1024];
    cout << prompt;
    flush(cout);

    cin.getline(buf, sizeof(buf));

    execute(buf); // validate and execute the user commands
    cout << endl;
  }
}

PasswordManager::PasswordManager() {
  users = Storage::read(); // Load all data from disk on startup
  isLoggedIn = "";
}

static bool isCommand(string cmd, string token) {
  return 0 == cmd.compare(0, token.length(), token);
}

static void helpText() {
  cout
      << "signup \t Create a new passMgr user" << endl
      << "login  \t Login into a passMgr account" << endl
      << "logout \t Logout from the current session" << endl
      << "quit   \t Exit the program" << endl
      << "exit   \t Exit the program" << endl
      << "create-password \t Create a password for the specified account"
      << endl
      << "show-password   \t Show the password for the specified account"
      << endl
      << "delete-password \t Delete the data related to the specified account"
      << endl
      << "show-accounts   \t Show all accounts managed by passMgr for this user"
      << endl
      << "help            \t Print this help text" << endl;
}

/**
 * @brief Execute a single cmd
 * */
void PasswordManager::execute(string cmd) {
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
    cerr << "Not logged in" << endl;
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
    cout << "not implemented <" << cmd << ">" << endl;
  }
}

static string getLoginName() {
  string name;
  cout << "Enter username: ";
  cin >> name;
  if (name.length() <= 0 || name.length() > 30) {
    cout << "Invalid user name" << endl;
    return "";
  }
  return name;
}

bool PasswordManager::login() {
  char buf[32];

  string name = getLoginName();
  string pass, confirmPass;
  if (name.length() == 0) {
    return false;
  }
  // Check if user exists.
  if (users.doesUserExist(name)) {
    do {
      cout << "Enter password: ";
      cin >> pass;
    } while (!users.validatePassword(name, pass));

  } else {
    cout << "No such user exists" << endl;
    return false;
  }

  prompt = name + "@" + prompt; // Change the prompt so we know who is logged in
  loggedInUser = name;
  isLoggedIn = true;
  cin.getline(buf, sizeof(buf));
  return true;
}

void PasswordManager::logout() {
  users.logout(loggedInUser);

  prompt = "passMgr> "; // Set the prompt back to default logged out state
  loggedInUser = "";
  isLoggedIn = false;
}

void PasswordManager::createPassword(string cmd) {
  stringstream ss(cmd);
  string discard;
  string account;
  ss >> discard;
  ss >> account;
  if (users.getPassword(loggedInUser, account).length() > 0) {
    cerr << "Account already exists" << endl;
    return;
  }
  string password = users.addAccount(loggedInUser, account);
  cout << "Password for " << account << " is: " << password << endl;
}

void PasswordManager::showPassword(string cmd) {
  stringstream ss(cmd);
  string account;
  string discard;
  ss >> discard;
  ss >> account;
  if (account.length() == 0) {
    cerr << "Specify an account" << endl;
    return;
  }
  string password = users.getPassword(loggedInUser, account);
  if (password.length() == 0) {
    cerr << "account does not exist: " << account << endl;
  } else {
    cout << "Password is: " << password << endl;
  }
}

void PasswordManager::deletePassword(string cmd) {
  stringstream ss(cmd);
  string account;
  string discard;
  ss >> discard;
  ss >> account;
  if (account.length() == 0) {
    cerr << "Specify account to delete" << endl;
    return;
  }
  if (users.deleteAccount(loggedInUser, account)) {
    cout << "Account deleted: " << account << endl;
  } else {
    cerr << "Account does not exist: " << account << endl;
  }
}

bool PasswordManager::signup() {
  string pass;
  string confirmPass;
  string name = getLoginName();
  // Create the user
  if (users.doesUserExist(name)) {
    cout << "User name is not available" << endl;
    return false;
  }
  do {
    cout << "Enter Master Password: ";
    cin >> pass;
    cout << "Confirm master password: ";
    cin >> confirmPass;

  } while (pass.compare(confirmPass) != 0);

  if (users.createUser(name, pass)) {
    cout << "Successfully generated a master password." << endl;
    return true;
  }
  return false;
}

void PasswordManager::showAccounts() {
  cout << users.showAccounts(loggedInUser);
}

} /* namespace irfan */

int main(int argc, char **argv) {
  IrfanSec::PasswordManager mgr;
  mgr.start();
  return 0;
}
