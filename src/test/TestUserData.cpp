/*
 * TestUserData.cpp
 *
 *  Created on: Aug 3, 2019
 *      Author: Irfan M
 */

#include "../UserData.cpp"
#include <gtest/gtest.h>

namespace IrfanSec {

class Test_UserData : public testing::Test {};

TEST(Test_UserData, basic) {
  UserData d("password");
  std::string account_name("snowwhite@stories.com");
  d.addAccount(account_name);

  std::cout << "master hash is " << d.getMasterHash() << std::endl;
  std::cout << "application hash is " << d.getAppHash() << std::endl;

  ASSERT_EQ(36, d.getAppSalt().length());
  ASSERT_STREQ(d.getAccountPassword(account_name).c_str(),
               d.getAccountPassword(account_name).c_str());
}
TEST(Test_UserData, listAccounts) {
  UserData d("password");
  std::string account_name("snowwhite@stories.com");
  d.addAccount(account_name);
  d.addAccount("cinderella@stories.com");
  std::vector<std::string> expected_result;
  expected_result.push_back("cinderella@stories.com");
  expected_result.push_back("snowwhite@stories.com");

  int n = 0;
  for (const auto &i : d.getAccounts()) {
    ASSERT_STREQ(expected_result[n++].c_str(), i.c_str()) << "index: " << n;
  }

  std::stringstream ss_d;
  ss_d << d;
  UserData e;
  ss_d >> e;

  std::stringstream ss_e;
  ss_e << e;

  // Check that d and e are equal
  ASSERT_STREQ(ss_d.str().c_str(), ss_e.str().c_str());
}
} /* namespace irfan */
