/*
 * TestUtilities.cpp
 *
 *  Created on: Aug 2, 2019
 *      Author: Irfan M
 */

#include <gtest/gtest.h>

#include "../Utilities.cpp"

using namespace std;
using namespace testing;

namespace IrfanSec {

class TestUtilities : public testing::Test {};

TEST(TestUtilities, randomBytes) {
  char buf[1024] = "";

  Utilities::getRandomData((unsigned char *)buf, 0);
  ASSERT_STREQ("", buf);

  Utilities::getRandomData((unsigned char *)buf, sizeof(buf));
  string text = textify((unsigned char *)buf, sizeof(buf));
  cout << "textified random data is" << text << endl;

  ASSERT_EQ(sizeof(buf) - 1, text.length()) << text << endl;
}

TEST(TestUtilities, salts) {
  string salt = Utilities::get16ByteSalt();
  cout << "16 byte salt is " << salt << endl;
  ASSERT_EQ(20, salt.length()) << salt << endl;
  salt = Utilities::get32ByteSalt();
  cout << "32 byte salt is " << salt << endl;
  ASSERT_EQ(36, salt.length()) << endl;
}

TEST(TestUtilities, passwords) {
  string password = Utilities::getStrongPassword();
  cout << "35 byte password is " << password << endl;
  ASSERT_EQ(35, password.length());
}

TEST(TestUtilities, extractSalt) {
  ASSERT_STREQ("", extractSalt("").c_str());
  ASSERT_STREQ("", extractSalt("$1$").c_str());
  ASSERT_STREQ("$1$salt$", extractSalt("$1$salt$xxx").c_str());
  ASSERT_STREQ("$1$saltsaltsaltsalt$",
               extractSalt("$1$saltsaltsaltsalt$").c_str());
}

TEST(TestUtilities, hashPassword) {
  ASSERT_STREQ("$6$saltsalt$qFmFH.bQmmtXzyBY0s9v7Oicd2z4XSIecDzlB5KiA2/"
               "jctKu9YterLp8wwnSq.qc.eoxqOmSuNp2xS0ktL3nh/",
               Utilities::hashPassword("$6$saltsalt$", "password").c_str());
}
} /* namespace irfan */
