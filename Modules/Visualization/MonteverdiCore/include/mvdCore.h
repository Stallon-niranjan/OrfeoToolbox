/*
 * Copyright (C) 2005-2022 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef mvdCore_h
#define mvdCore_h


//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


#include "OTBMonteverdiCoreExport.h"

/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdTypes.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

//
// Internal classes pre-declaration.
namespace mvd
{
} // end namespace 'mvd'


/*****************************************************************************/
/* TYPE DEFINITION SECTION                                                   */

namespace mvd
{

/**
 * Constants identifying the video-channels.
 */
enum RgbwChannel
{
  RGBW_CHANNEL_NONE = -1,

  RGBW_CHANNEL_RED = 0,
  RGBW_CHANNEL_GREEN,
  RGBW_CHANNEL_BLUE,

  RGBW_CHANNEL_WHITE,

  RGBW_CHANNEL_RGB,

  RGBW_CHANNEL_ALL,

  RGBW_CHANNEL_COUNT,
};

/**
 * Constant naming video-channels.
 */
extern OTBMonteverdiCore_EXPORT const char* RGBW_CHANNEL_NAMES[RGBW_CHANNEL_COUNT];

/**
 */
enum Bound
{
  BOUND_LOWER = 0,
  BOUND_UPPER,
  BOUND_COUNT
};

/**
 * Constant naming bound values.
 */
extern const char* BOUND_NAMES[BOUND_COUNT];

/**
 */
enum Effect
{
  EFFECT_NONE = -1,
  //
  EFFECT_CHESSBOARD = 0,
  EFFECT_GRADIENT,
  EFFECT_LOCAL_CONTRAST,
  EFFECT_LOCAL_TRANSLUCENCY,
  EFFECT_NORMAL,
  EFFECT_SWIPE_H,
  EFFECT_SWIPE_V,
  EFFECT_SPECTRAL_ANGLE,
  EFFECT_LUT_JET,
  EFFECT_LUT_LOCAL_JET,
  EFFECT_LUT_HOT,
  EFFECT_LUT_LOCAL_HOT,
  EFFECT_LUT_WINTER,
  EFFECT_LUT_LOCAL_WINTER,
  EFFECT_LUT_SUMMER,
  EFFECT_LUT_LOCAL_SUMMER,
  EFFECT_LUT_COOL,
  EFFECT_LUT_LOCAL_COOL,
  //
  EFFECT_COUNT
};

/**
 * Constant naming effect values.
 */
OTBMonteverdiCore_EXPORT extern char const* const EFFECT_NAMES[EFFECT_COUNT];

/**
 */
OTBMonteverdiCore_EXPORT extern bool OVERVIEWS_ENABLED_DEFAULT;

/**
 */
OTBMonteverdiCore_EXPORT extern int OVERVIEWS_SIZE_DEFAULT;

} // end of namespace mvd.


/*****************************************************************************/
/* FUNCTION DECLARATION SECTION                                              */

namespace mvd
{

/**
 * \brief Convenience method used to compute integer indices in order
 * to iterate through RGB channels such as, for example:
 * \code
 * for( i=begin; i<end; ++i ) {}
 * \endcode
 *
 * \param begin    The resulting first index where to begin iteration.
 * \param end      The resulting upper-boundary index of the iteration.
 * \param channels The channels to be iterated. Valid values are:
 * _ RGBA_CHANNEL_NONE to select no video-channel at all;
 * - RGBA_CHANNEL_RED to select red video-channel;
 * - RGBA_CHANNEL_GREEN to select green video-channel;
 * - RGBA_CHANNEL_BLUE to select blue video-channel;
 * - RGBA_CHANNEL_WHITE is equivalent to RGBA_CHANNEL_NONE;
 * - RGBA_CHANNEL_RGB to select all RGB video-channels;
 * - RGBA_CHANNEL_ALL to select all RGB (without the alpha) video-channels.
 *
 * \return true if iteration indices have been set and loop can be
 * processed.
 */
inline bool RgbBounds(CountType& begin, CountType& end, RgbwChannel channels);

/**
 * \brief Convenience method used to compute integer indices in order
 * to iterate through RGBA channels such as, for example:
 * \code
 * for( i=begin; i<end; ++i ) {}
 * \endcode
 *
 * \param begin    The first index where to begin iteration.
 * \param end      The upper-boundary index of the iteration.
 * \param channels The channels to be iterated. Valid values are:
 * _ RGBA_CHANNEL_NONE to select no video-channel at all;
 * - RGBA_CHANNEL_RED to select red video-channel;
 * - RGBA_CHANNEL_GREEN to select green video-channel;
 * - RGBA_CHANNEL_BLUE to select blue video-channel;
 * - RGBA_CHANNEL_WHITE to select the white video-channel;
 * - RGBA_CHANNEL_RGB to select all RGB (without the alpha) video-channels;
 * - RGBA_CHANNEL_ALL to select all RGBA video-channels.
 *
 * \return true if iteration indices have been set and loop can be
 * processed.
 */
inline bool RgbwBounds(CountType& begin, CountType& end, RgbwChannel channels);

/**
 * \brief Provide a lexicographical version-string 'M.m.p' less operator.
 *
 * \param v0 Left-operand version string.
 * \param v1 Right-operand version string.
 *
 * \return true if left-operand is lesser than right-operand.
 */
inline bool IsVersionLess(const QString& v0, const QString& v1);

/**
 * \brief Provide a lexicographical version-string 'M.m.p'
 * greater-or-equal operator.
 *
 * \param v0 Left-operand version string.
 * \param v1 Right-operand version string.
 *
 * \return true if left-operand is greater-or-equal than right-operand.
 */
inline bool IsVersionGreaterEqual(const QString& v0, const QString& v1);

/**
 * \brief Provide a lexicographical version-string 'M.m.p' equal
 * operator.
 *
 * \param v0 Left-operand version string.
 * \param v1 Right-operand version string.
 *
 * \return true if left-operand is equal than right-operand.
 */
inline bool IsVersionEqual(const QString& v0, const QString& v1);

} // end namespace 'mvd'.


/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{
/*****************************************************************************/
inline bool RgbBounds(CountType& begin, CountType& end, RgbwChannel channels)
{
  assert(channels != RGBW_CHANNEL_COUNT);

  switch (channels)
  {
  case RGBW_CHANNEL_NONE:
  case RGBW_CHANNEL_WHITE:
    begin = RGBW_CHANNEL_NONE;
    end   = RGBW_CHANNEL_NONE;
    break;

  case RGBW_CHANNEL_RED:
  case RGBW_CHANNEL_GREEN:
  case RGBW_CHANNEL_BLUE:
    begin = channels;
    end   = channels + 1;
    break;

  case RGBW_CHANNEL_RGB:
  case RGBW_CHANNEL_ALL:
    begin = RGBW_CHANNEL_RED;
    end   = RGBW_CHANNEL_WHITE;
    break;

  default:
    assert(false && "Non-managed RgbwChannel value.!");
    return false;
    break;
  }

  return true;
}

/*****************************************************************************/
inline bool RgbwBounds(CountType& begin, CountType& end, RgbwChannel channels)
{
  assert(channels != RGBW_CHANNEL_COUNT);

  switch (channels)
  {
  case RGBW_CHANNEL_NONE:
    begin = RGBW_CHANNEL_NONE;
    end   = RGBW_CHANNEL_NONE;
    break;

  case RGBW_CHANNEL_RED:
  case RGBW_CHANNEL_GREEN:
  case RGBW_CHANNEL_BLUE:
  case RGBW_CHANNEL_WHITE:
    begin = channels;
    end   = channels + 1;
    break;

  case RGBW_CHANNEL_RGB:
    begin = RGBW_CHANNEL_RED;
    end   = RGBW_CHANNEL_WHITE;
    break;

  case RGBW_CHANNEL_ALL:
    begin = RGBW_CHANNEL_RED;
    end   = RGBW_CHANNEL_RGB;
    break;

  default:
    assert(false && "Non-managed RgbwChannel value.!");
    return false;
    break;
  }

  return true;
}

/*****************************************************************************/
inline bool IsVersionLess(const QString& v0, const QString& v1)
{
  QStringList V0List(v0.split("."));
  assert(V0List.size() >= 3);

  QStringList V1List(v1.split("."));
  assert(V1List.size() >= 3);

  return V0List[0].toInt() < V1List[0].toInt() ||

         (V0List[0].toInt() == V1List[0].toInt() && V0List[1].toInt() < V1List[1].toInt()) ||

         (V0List[1].toInt() == V1List[1].toInt() && V0List[2].toInt() < V1List[2].toInt());
}

/*****************************************************************************/
inline bool IsVersionEqual(const QString& v0, const QString& v1)
{
  QStringList V0List(v0.split("."));
  assert(V0List.size() >= 3);

  QStringList V1List(v1.split("."));
  assert(V1List.size() >= 3);

  return V0List[0].toInt() == V1List[0].toInt() && V0List[1].toInt() == V1List[1].toInt() && V0List[2].toInt() == V1List[2].toInt();
}

/*****************************************************************************/
inline bool IsVersionGreaterEqual(const QString& v0, const QString& v1)
{
  QStringList V0List(v0.split("."));
  assert(V0List.size() >= 3);

  QStringList V1List(v1.split("."));
  assert(V1List.size() >= 3);

  return V0List[0].toInt() > V1List[0].toInt() ||

         (V0List[0].toInt() == V1List[0].toInt() && V0List[1].toInt() > V1List[1].toInt()) ||

         (V0List[1].toInt() == V1List[1].toInt() && V0List[2].toInt() >= V1List[2].toInt());
}

} // end namespace 'mvd'.

#endif // mvdCore_h
