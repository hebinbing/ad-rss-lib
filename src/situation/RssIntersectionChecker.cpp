// ----------------- BEGIN LICENSE BLOCK ---------------------------------
//
// Copyright (c) 2018-2019 Intel Corporation
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
//    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
//    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//    OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//    POSSIBILITY OF SUCH DAMAGE.
//
// ----------------- END LICENSE BLOCK -----------------------------------

#include "situation/RssIntersectionChecker.hpp"
#include <cmath>
#include <limits>
#include "physics/Math.hpp"
#include "situation/RssFormulas.hpp"
#include "situation/RssSituation.hpp"

namespace ad_rss {
namespace situation {

using physics::Duration;
using physics::calculateTimeToCoverDistance;

RssIntersectionChecker::RssIntersectionChecker()
{
}

RssIntersectionChecker::~RssIntersectionChecker()
{
  mLastSafeStateMap.clear();
  mCurrentSafeStateMap.clear();
}

bool checkLateralIntersect(Situation const &situation, bool &isSafe)
{
  isSafe = false;

  /**
   * Check if in any case the first vehicle has passed the intersection before the other
   * vehicle arrives at that point
   */

  Duration timeToReachEgo;
  Duration timeToReachOther;
  Duration timeToLeaveEgo;
  Duration timeToLeaveOther;

  bool result = calculateTimeToCoverDistance(situation.egoVehicleState.velocity.speedLon.maximum,
                                             situation.egoVehicleState.dynamics.responseTime,
                                             situation.egoVehicleState.dynamics.alphaLon.accelMax,
                                             situation.egoVehicleState.dynamics.alphaLon.brakeMin,
                                             situation.egoVehicleState.distanceToEnterIntersection,
                                             timeToReachEgo);

  result = result && calculateTimeToCoverDistance(situation.otherVehicleState.velocity.speedLon.maximum,
                                                  situation.otherVehicleState.dynamics.responseTime,
                                                  situation.otherVehicleState.dynamics.alphaLon.accelMax,
                                                  situation.otherVehicleState.dynamics.alphaLon.brakeMin,
                                                  situation.otherVehicleState.distanceToEnterIntersection,
                                                  timeToReachOther);

  result = result && calculateTimeToCoverDistance(situation.egoVehicleState.velocity.speedLon.minimum,
                                                  situation.egoVehicleState.dynamics.responseTime,
                                                  -1. * situation.egoVehicleState.dynamics.alphaLon.brakeMax,
                                                  situation.egoVehicleState.dynamics.alphaLon.brakeMax,
                                                  situation.egoVehicleState.distanceToLeaveIntersection,
                                                  timeToLeaveEgo);

  result = result && calculateTimeToCoverDistance(situation.otherVehicleState.velocity.speedLon.minimum,
                                                  situation.otherVehicleState.dynamics.responseTime,
                                                  -1. * situation.otherVehicleState.dynamics.alphaLon.brakeMax,
                                                  situation.otherVehicleState.dynamics.alphaLon.brakeMax,
                                                  situation.otherVehicleState.distanceToLeaveIntersection,
                                                  timeToLeaveOther);

  if (result)
  {
    if ((timeToReachEgo > timeToLeaveOther) || (timeToReachOther > timeToLeaveEgo)
        || ((timeToReachEgo == std::numeric_limits<Duration>::max())
            && (timeToReachOther == std::numeric_limits<Duration>::max())))
    {
      /**
       * Currently we assume lateral overlap when there is a vehicle in an intersection
       * @todo This could be relaxed by calculating lateral distance here as well
       */
      isSafe = true;
    }
  }

  return result;
}

bool checkIntersectionSafe(Situation const &situation,
                           ::ad_rss::state::RssStateInformation &rssStateInformation,
                           bool &isSafe,
                           IntersectionState &intersectionState)
{
  if ((situation.egoVehicleState.distanceToLeaveIntersection < situation.egoVehicleState.distanceToEnterIntersection)
      || (situation.otherVehicleState.distanceToLeaveIntersection
          < situation.otherVehicleState.distanceToEnterIntersection))
  {
    return false;
  }

  bool result = true;
  isSafe = false;

  /**
   * Check if a non prio vehicle has safe distance to the intersection
   */
  if (!situation.egoVehicleState.hasPriority)
  {
    rssStateInformation.evaluator = state::RssStateEvaluator::IntersectionOtherPriorityEgoAbleToStop;
    rssStateInformation.currentDistance = situation.egoVehicleState.distanceToEnterIntersection;
    result = checkStopInFrontIntersection(situation.egoVehicleState, rssStateInformation.safeDistance, isSafe);
  }
  if (result && !isSafe && !situation.otherVehicleState.hasPriority)
  {
    rssStateInformation.evaluator = state::RssStateEvaluator::IntersectionEgoPriorityOtherAbleToStop;
    rssStateInformation.currentDistance = situation.otherVehicleState.distanceToEnterIntersection;
    result = checkStopInFrontIntersection(situation.otherVehicleState, rssStateInformation.safeDistance, isSafe);
  }

  if (isSafe)
  {
    intersectionState = IntersectionState::NonPrioAbleToBreak;
  }
  else if (result)
  {
    rssStateInformation.currentDistance = situation.relativePosition.longitudinalDistance;
    /**
     * Check if there is a safe longitudinal distance between the vehicles
     */
    if (situation.relativePosition.longitudinalPosition == LongitudinalRelativePosition::InFront)
    {
      rssStateInformation.evaluator = state::RssStateEvaluator::IntersectionEgoInFront;
      result = checkSafeLongitudinalDistanceSameDirection(situation.egoVehicleState,
                                                          situation.otherVehicleState,
                                                          situation.relativePosition.longitudinalDistance,
                                                          rssStateInformation.safeDistance,
                                                          isSafe);
    }
    else
    {
      rssStateInformation.evaluator = state::RssStateEvaluator::IntersectionOtherInFront;
      result = checkSafeLongitudinalDistanceSameDirection(situation.otherVehicleState,
                                                          situation.egoVehicleState,
                                                          situation.relativePosition.longitudinalDistance,
                                                          rssStateInformation.safeDistance,
                                                          isSafe);
    }
    if (isSafe)
    {
      intersectionState = IntersectionState::SafeLongitudinalDistance;
    }
    else if (result)
    {
      rssStateInformation.evaluator = state::RssStateEvaluator::IntersectionOverlap;
      rssStateInformation.currentDistance = physics::Distance(0.);
      rssStateInformation.safeDistance = physics::Distance(0.);
      result = checkLateralIntersect(situation, isSafe);

      if (isSafe)
      {
        intersectionState = IntersectionState::NoTimeOverlap;
      }
    }
  }

  return result;
}

bool RssIntersectionChecker::calculateRssStateIntersection(physics::TimeIndex const &timeIndex,
                                                           Situation const &situation,
                                                           state::RssState &rssState)
{
  if (situation.egoVehicleState.hasPriority && situation.otherVehicleState.hasPriority)
  {
    // both cannot have priority over the other at the same time
    return false;
  }
  bool result = false;
  try
  {
    if (timeIndex != mCurrentTimeIndex)
    {
      /**
       * next time step: current safe state map becomes last state now
       */
      mLastSafeStateMap.swap(mCurrentSafeStateMap);
      mCurrentSafeStateMap.clear();
      mCurrentTimeIndex = timeIndex;
    }

    rssState.longitudinalState.isSafe = false;
    rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::BrakeMin;

    /**
     * An intersection situation is lateral unsafe but usually doesn't require a lateral brake
     * @todo: if taking lateral intersection handling into account, this also has to be updated
     */
    rssState.lateralStateLeft.isSafe = false;
    rssState.lateralStateLeft.response = ::ad_rss::state::LateralResponse::None;
    rssState.lateralStateLeft.rssStateInformation.evaluator = state::RssStateEvaluator::LateralDistance;
    rssState.lateralStateLeft.rssStateInformation.currentDistance = physics::Distance(0);
    rssState.lateralStateLeft.rssStateInformation.safeDistance = physics::Distance(0);
    rssState.lateralStateRight.isSafe = false;
    rssState.lateralStateRight.response = ::ad_rss::state::LateralResponse::None;
    rssState.lateralStateRight.rssStateInformation.evaluator = state::RssStateEvaluator::LateralDistance;
    rssState.lateralStateRight.rssStateInformation.currentDistance = physics::Distance(0);
    rssState.lateralStateRight.rssStateInformation.safeDistance = physics::Distance(0);

    bool isSafe = false;
    IntersectionState intersectionState = IntersectionState::NonPrioAbleToBreak;

    /**
     * Check if the intersection is safe and determine the intersection state of the situation
     */
    result
      = checkIntersectionSafe(situation, rssState.longitudinalState.rssStateInformation, isSafe, intersectionState);

    if (result)
    {
      rssState.longitudinalState.isSafe = isSafe;

      auto const previousIntersectionState = mLastSafeStateMap.find(situation.situationId);

      if (!isSafe)
      {
        /**
         * Situation is unsafe determine proper response
         */
        if (previousIntersectionState != mLastSafeStateMap.end())
        {
          switch (previousIntersectionState->second)
          {
            case IntersectionState::NonPrioAbleToBreak:
            {
              if (situation.egoVehicleState.hasPriority)
              {
                rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::None;
              }
              break;
            }
            case IntersectionState::SafeLongitudinalDistance:
            {
              if (situation.relativePosition.longitudinalPosition == LongitudinalRelativePosition::InFront)
              {
                rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::None;
              }
              break;
            }
            case IntersectionState::NoTimeOverlap:
            {
              // @todo If we don't assume always lateral overlap we might need to brake laterally as well
              rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::BrakeMin;
              break;
            }
            default:
            {
              // LCOV_EXCL_START: unreachable code, keep to be on the safe side
              result = false;
              break;
              // LCOV_EXCL_STOP: unreachable code, keep to be on the safe side
            }
          }

          /**
           * Store the last safe intersection state for next time step
           */
          mCurrentSafeStateMap.insert(
            RssIntersectionStateMap::value_type(situation.situationId, previousIntersectionState->second));
        }
        else
        {
          /**
           * Situation is unsafe but there is no previous safe state. Therefore we can only decide to brake.
           */
          rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::BrakeMin;
        }
      }
      else
      {
        /**
         * Situation is safe
         */
        rssState.longitudinalState.response = ::ad_rss::state::LongitudinalResponse::None;

        // Update the last safe state
        mCurrentSafeStateMap.insert(RssIntersectionStateMap::value_type(situation.situationId, intersectionState));
      }
    }
  }
  catch (...)
  {
    result = false;
  }
  return result;
}

} // namespace situation
} // namespace ad_rss
