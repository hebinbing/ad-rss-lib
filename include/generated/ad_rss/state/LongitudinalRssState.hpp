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

/**
 * Generated file
 * @file
 *
 */

#pragma once

#include <memory>
#include "ad_rss/state/LongitudinalResponse.hpp"
#include "ad_rss/state/RssStateInformation.hpp"
/*!
 * @brief namespace ad_rss
 */
namespace ad_rss {
/*!
 * @brief namespace state
 */
namespace state {

/*!
 * \brief DataType LongitudinalRssState
 *
 * Struct to store the longitudinal RSS state.
 */
struct LongitudinalRssState
{
  /*!
   * \brief standard constructor
   */
  LongitudinalRssState() = default;

  /*!
   * \brief standard destructor
   */
  ~LongitudinalRssState() = default;

  /*!
   * \brief standard copy constructor
   */
  LongitudinalRssState(const LongitudinalRssState &other) = default;

  /*!
   * \brief standard move constructor
   */
  LongitudinalRssState(LongitudinalRssState &&other) = default;

  /**
   * \brief standard assignment operator
   *
   * \param[in] other Other LongitudinalRssState
   *
   * \returns Reference to this LongitudinalRssState.
   */
  LongitudinalRssState &operator=(const LongitudinalRssState &other) = default;

  /**
   * \brief standard move operator
   *
   * \param[in] other Other LongitudinalRssState
   *
   * \returns Reference to this LongitudinalRssState.
   */
  LongitudinalRssState &operator=(LongitudinalRssState &&other) = default;

  /**
   * \brief standard comparison operator
   *
   * \param[in] other Other LongitudinalRssState
   *
   * \returns \c true if both LongitudinalRssState are equal
   */
  bool operator==(const LongitudinalRssState &other) const
  {
    return (isSafe == other.isSafe) && (response == other.response)
      && (rssStateInformation == other.rssStateInformation);
  }

  /**
   * \brief standard comparison operator
   *
   * \param[in] other Other LongitudinalRssState.
   *
   * \returns \c true if both LongitudinalRssState are different
   */
  bool operator!=(const LongitudinalRssState &other) const
  {
    return !operator==(other);
  }

  /*!
   * Flag to indicate if the state is longitudinal safe.
   */
  bool isSafe{false};

  /*!
   * required response in longitudinal direction
   */
  ::ad_rss::state::LongitudinalResponse response{::ad_rss::state::LongitudinalResponse::BrakeMin};

  /*!
   * Information on the evaluation of the Rss state.
   */
  ::ad_rss::state::RssStateInformation rssStateInformation;
};

} // namespace state
} // namespace ad_rss
