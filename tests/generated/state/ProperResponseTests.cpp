/*
 * ----------------- BEGIN LICENSE BLOCK ---------------------------------
 *
 * Copyright (c) 2018-2019 Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 *    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *    POSSIBILITY OF SUCH DAMAGE.
 *
 * ----------------- END LICENSE BLOCK -----------------------------------
 */

/*
 * Generated file
 */

#include <gtest/gtest.h>
#include <limits>
#include "ad_rss/state/ProperResponse.hpp"

class ProperResponseTests : public testing::Test
{
protected:
  virtual void SetUp() override
  {
    // valid initialization
    ::ad_rss::state::ProperResponse value;
    ::ad_rss::physics::TimeIndex valueTimeIndex(std::numeric_limits<::ad_rss::physics::TimeIndex>::lowest());
    valueTimeIndex = ::ad_rss::physics::TimeIndex(1); // set to valid value within struct
    value.timeIndex = valueTimeIndex;
    bool valueIsSafe{true};
    value.isSafe = valueIsSafe;
    ::ad_rss::world::ObjectIdVector valueDangerousObjects;
    value.dangerousObjects = valueDangerousObjects;
    ::ad_rss::state::LongitudinalResponse valueLongitudinalResponse(::ad_rss::state::LongitudinalResponse::None);
    value.longitudinalResponse = valueLongitudinalResponse;
    ::ad_rss::state::LateralResponse valueLateralResponseRight(::ad_rss::state::LateralResponse::None);
    value.lateralResponseRight = valueLateralResponseRight;
    ::ad_rss::state::LateralResponse valueLateralResponseLeft(::ad_rss::state::LateralResponse::None);
    value.lateralResponseLeft = valueLateralResponseLeft;
    mValue = value;
  }

  ::ad_rss::state::ProperResponse mValue;
};

TEST_F(ProperResponseTests, copyConstruction)
{
  ::ad_rss::state::ProperResponse value(mValue);
  EXPECT_EQ(mValue, value);
}

TEST_F(ProperResponseTests, moveConstruction)
{
  ::ad_rss::state::ProperResponse value(std::move(::ad_rss::state::ProperResponse(mValue)));
  EXPECT_EQ(mValue, value);
}

TEST_F(ProperResponseTests, copyAssignment)
{
  ::ad_rss::state::ProperResponse value;
  value = mValue;
  EXPECT_EQ(mValue, value);
}

TEST_F(ProperResponseTests, moveAssignment)
{
  ::ad_rss::state::ProperResponse value;
  value = std::move(::ad_rss::state::ProperResponse(mValue));
  EXPECT_EQ(mValue, value);
}

TEST_F(ProperResponseTests, comparisonOperatorEqual)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_TRUE(valueA == valueB);
  EXPECT_FALSE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorTimeIndexDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::physics::TimeIndex timeIndex(std::numeric_limits<::ad_rss::physics::TimeIndex>::max());
  valueA.timeIndex = timeIndex;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorIsSafeDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  bool isSafe{false};
  valueA.isSafe = isSafe;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorDangerousObjectsDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::world::ObjectIdVector dangerousObjects;
  ::ad_rss::world::ObjectId dangerousObjectsElement(std::numeric_limits<::ad_rss::world::ObjectId>::max());
  dangerousObjects.resize(0 + 1, dangerousObjectsElement);
  valueA.dangerousObjects = dangerousObjects;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorLongitudinalResponseDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::state::LongitudinalResponse longitudinalResponse(::ad_rss::state::LongitudinalResponse::BrakeMin);
  valueA.longitudinalResponse = longitudinalResponse;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorLateralResponseRightDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::state::LateralResponse lateralResponseRight(::ad_rss::state::LateralResponse::BrakeMin);
  valueA.lateralResponseRight = lateralResponseRight;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}

TEST_F(ProperResponseTests, comparisonOperatorLateralResponseLeftDiffers)
{
  ::ad_rss::state::ProperResponse valueA = mValue;
  ::ad_rss::state::LateralResponse lateralResponseLeft(::ad_rss::state::LateralResponse::BrakeMin);
  valueA.lateralResponseLeft = lateralResponseLeft;
  ::ad_rss::state::ProperResponse valueB = mValue;

  EXPECT_FALSE(valueA == valueB);
  EXPECT_TRUE(valueA != valueB);
}
