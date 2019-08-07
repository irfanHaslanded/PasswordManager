/*
 * TestUsers.cpp
 *
 *  Created on: Aug 3, 2019
 *      Author: Irfan M
 */

#include "TestUsers.h"
#include "../Storage.cpp"
#include "../Users.cpp"

using namespace std;

namespace IrfanSec {
Users TestUsers::testUser;

void TestUsers::SetUp(void) {
  ASSERT_TRUE(testUser.createUser("Batman", "DarkKnight"));
  ASSERT_FALSE(testUser.createUser("Batman", "DarkKnight"));
  string password = testUser.addAccount("Batman", "batman@bats.org");

  string passwordGet = testUser.getPassword("Batman", "batman@bats.org");
  ASSERT_STREQ(password.c_str(), passwordGet.c_str());

  ASSERT_TRUE(testUser.createUser("AntMan", "AntsAreCool"));
  testUser.addAccount("AntMan", "AntMan@ants.org");
}

void TestUsers::TearDown(void) {
  ASSERT_TRUE(testUser.deleteAccount("Batman", "batman@bats.org"));
  ASSERT_TRUE(testUser.deleteUser("Batman"));
  ASSERT_TRUE(testUser.deleteUser("AntMan"));

  Storage::remove();
}

TEST_F(TestUsers, basic) {
  // Tests from SetUp and TearDown are executed here
}

TEST_F(TestUsers, streams) {
  stringstream out;
  out << TestUsers::testUser;
  Users readBack;
  out >> readBack;
  stringstream in;
  in << readBack;

  cout << __func__ << "." << __LINE__ << ": " << TestUsers::testUser << endl;
  cout << __func__ << "." << __LINE__ << ": " << readBack << endl;
  ASSERT_STREQ(out.str().c_str(), in.str().c_str());
}

TEST_F(TestUsers, storage) {
  Storage::write(TestUsers::testUser);
  Users readBack = Storage::read();

  stringstream out;
  out << TestUsers::testUser;

  stringstream in;
  in << readBack;

  ASSERT_STREQ(out.str().c_str(), in.str().c_str());
}
} /* namespace passMgr */
