#include <gtest/gtest.h>

#include <iostream>

#include "PID.h"
#include "helper.hpp"

// class PIDTest : public ::testing::Test {
//  PID pid;
//};

TEST(helpers, test_pi) {
  ASSERT_DOUBLE_EQ(pi(), 3.1415926535897931);
  ASSERT_DOUBLE_EQ(deg2rad(180), pi());
  ASSERT_DOUBLE_EQ(rad2deg(pi()), 180);
  ASSERT_DOUBLE_EQ(deg2rad(360), 2 * pi());
  ASSERT_DOUBLE_EQ(rad2deg(2 * pi()), 360);
}

TEST(helpers, test_has_data) {
  // empty string
  ASSERT_EQ(hasData(""), "");
  // has null in it
  ASSERT_EQ(hasData(R"({"null":"2"})"), "");
  //  ASSERT_EQ(hasData(R"(42["telemetry"{"data":"123"}])"),
  //  R"([{"data":"123"}])");
}