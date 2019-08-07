/*
 * TestUsers.h
 *
 *  Created on: Aug 3, 2019
 *      Author: Irfan M
 */

#ifndef SRC_TEST_TESTUSERS_H_
#define SRC_TEST_TESTUSERS_H_

#include "../Users.h"
#include <gtest/gtest.h>
namespace IrfanSec {

class TestUsers : public ::testing::Test {
public:
  static Users testUser;
  void SetUp(void) override;
  void TearDown(void) override;
};

} /* namespace passMgr */

#endif /* SRC_TEST_TESTUSERS_H_ */
