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

#ifndef mvdColorDynamicsController_h
#define mvdColorDynamicsController_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


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
#include "OTBMonteverdiGUIExport.h"
//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdCore.h"
//
#include "mvdAbstractModelController.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.
class ColorDynamicsWidget;

/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class ColorDynamicsController
 *
 * \ingroup OTBMonteverdiGUI
 *
 * \brief Color-dynamics widget controller for VectorImageModel objects.
 */
class OTBMonteverdiGUI_EXPORT ColorDynamicsController : public AbstractModelController
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

  //
  // Public methods.
public:
  /**
   * \brief Constructor.
   *
   * \param widget Controlled widget.
   * \param parent Parent QObject of this QObject.
   */
  ColorDynamicsController(ColorDynamicsWidget* widget, QObject* p = NULL);

  /** \brief Destructor. */
  ~ColorDynamicsController() override;

  /*-[ PUBLIC SLOTS SECTION ]-----------------------------------------------**/

  //
  // Slots.
public Q_SLOTS:
  /**
   * \brief Slot called when the band-index of a RGB channel has
   * changed.
   *
   * \param channel The RGB channel for which the band-index has changed.
   * \param band The new band-index of the RGB channel.
   */
  void OnRgbChannelIndexChanged(RgbwChannel channel, int band);

  /**
   * \brief Slot called when the band-index of the white (gray)
   * channel has changed.
   *
   * \param band The new band-index of the white (gray) channel.
   */
  void OnGrayChannelIndexChanged(int band);

  /**
   * \brief Slot called when the activation-state of the
   * grayscale-mode has changed.
   *
   * \param activated The new grayscale-mode activation state.
   */
  void OnGrayscaleActivated(bool activated);

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

  //
  // Signals.
Q_SIGNALS:
  /**
   * \brief
   */
  void LowIntensityChanged(RgbwChannel channel, double value, bool refresh);

  /**
   * \brief
   */
  void HighIntensityChanged(RgbwChannel channel, double value, bool refresh);

  /**
   */
  void HistogramRefreshed();

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

  //
  // Protected methods.
protected:
  //
  // Protected attributes.
protected:
  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

  //
  // Private methods.
private:
  //
  // AbstractModelController methods.

  void Connect(AbstractModel*) override;

  void ClearWidget() override;

  void virtual_ResetWidget(bool) override;

  void Disconnect(AbstractModel*) override;

  /**
   * \brief Reset intensity ranges to default values for given RGB
   * channels.
   *
   * \param channels Given channels for which to reset current-band
   * index. \see RgbBound() for valid values.
   */
  void ResetIntensityRanges(RgbwChannel);

  /**
   * \brief Reset low and high intensities to default values for given
   * RGB channels.
   *
   * \param channels Given channels for which to reset current-band
   * index. \see RgbBound() for valid values.
   */
  void ResetIntensities(RgbwChannel);

  /**
   * \brief Set low and high intensitied of controlled widget based on
   * the values stored in the model settings.
   *
   * \param channels RGB/W channels for which to set low and high intensities.
   */
  void SetIntensities(RgbwChannel channels);

  /**
   * \brief Reset low and high quantiles to default values for given
   * RGB channels.
   *
   * \param channels Given channels for which to reset current-band
   * index. \see RgbBound() for valid values.
   */
  void ResetQuantiles(RgbwChannel channels);

  /**
   * \brief Restore low and high intensities from quantile values
   * stored in widget when enabling intensity-range bounds again.
   *
   * \param channels Channels for which to reset intensities.
   */
  void RestoreQuantiles(RgbwChannel channels);

  /**
   * \brief Convenience method used to compute integer indices in order
   * to iterate through RGB channels such as, for example:
   * \code
   * for( i=begin; i<end; ++i ) {}
   * \endcode
   *
   * \see mvd::RgbwBounds().
   *
   * \param begin    The resulting first index where to begin iteration.
   * \param end      The resulting upper-boundary index of the iteration.
   * \param channels The channels to be iterated. Valid values are:
   * _ RGBA_CHANNEL_NONE to select no video-channel at all;
   * - RGBA_CHANNEL_RED to select red video-channel;
   * - RGBA_CHANNEL_GREEN to select green video-channel;
   * - RGBA_CHANNEL_BLUE to select blue video-channel;
   * - RGBA_CHANNEL_WHITE is equivalent to RGBA_CHANNEL_RGB;
   * - RGBA_CHANNEL_RGB to select all RGB video-channels;
   * - RGBA_CHANNEL_ALL to select all RGB (without the alpha) video-channels.
   *
   * \return true if iteration indices have been set and loop can be
   * processed.
   */
  inline static bool RgbwBounds(CountType& begin, CountType& end, RgbwChannel channels);

  /**
   */
  void SetNoData();

  /**
   */
  void SetGamma();

  /**
   */
  void SetBoundsEnabled(RgbwChannel, bool);

  //
  // Private attributes.
private:
  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

  //
  // Slots.
private Q_SLOTS:
  /**
   */
  void RefreshHistogram();

  /**
   * \brief Slot called when low quantile value of a RGB channel has
   * been edited.
   *
   * \param channel RGB channel for which the quantile value has
   * changed.
   * \param quantile The new quantile value.
   */
  void OnLowQuantileChanged(RgbwChannel channel, double quantile);

  /**
   * \brief Slot called when high quantile value of a RGB channel has
   * been edited.
   *
   * \param channel RGB channel for which the quantile value has
   * changed.
   * \param quantile The new quantile value.
   */
  void OnHighQuantileChanged(RgbwChannel channel, double quantile);

  /**
   * \brief Slot called when low intensity value of a RGB channel has
   * been edited.
   *
   * \param channel RGB channel for which the intensity value has
   * changed.
   * \param intensity The new intensity value.
   */
  void OnLowIntensityChanged(RgbwChannel channel, double intensity);

  /**
   * \brief Slot called when high intensity value of a RGB channel has
   * been edited.
   *
   * \param channel RGB channel for which the intensity value has
   * changed.
   * \param intensity The new intensity value.
   */
  void OnHighIntensityChanged(RgbwChannel channel, double intensity);

  /**
   * \brief Slot called when the reset intensities button has been
   * clicked.
   *
   * \param channel RGB channel for which to reset low and high
   * intensities.
   */
  void OnResetIntensityClicked(RgbwChannel channel);

  /**
   * \brief Slot called when the reset quantiles button has been
   * clicked.
   *
   * \param channel RGB channel for which to reset low and high
   * quantiles.
   */
  void OnResetQuantileClicked(RgbwChannel channel);

  /**
   * \brief Slot called when the apply all button has been clicked.
   *
   * \param channel RGB channel for which to reset low and high
   * quantiles.
   */
  void OnApplyAllClicked(RgbwChannel channel, double low, double high);

  /**
   * \brief Slot called when the NoDataFlagToggled() signal of the
   * controlled widget has been emitted (\see ColorDynamicsWidget).
   *
   * \param enabled true when the no-data flag is enabled.
   */
  void OnNoDataFlagToggled(bool enabled);

  /**
   * \brief Slot called when the NoDataValueChanged() signal of the
   * controlled widget has been emitted (\see ColorDynamicsWidget).
   */
  void OnNoDataValueChanged(double value);

  /**
   * \brief Slot called when the link button has been toggled.
   *
   * \param channel RGB channel for which the link button has been toggled.
   * \param checked The state of the button.
   */
  void OnLinkToggled(RgbwChannel channel, bool checked);


  /**
   * \brief Slot called when gamma value is changed
   *
   * \param value Gamma value.
   */
  void OnGammaValueChanged(double value);
};

} // end namespace 'mvd'.

/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{

/*******************************************************************************/
inline bool ColorDynamicsController::RgbwBounds(CountType& begin, CountType& end, RgbwChannel channels)
{
#if 0
  return mvd::RgbBounds(
    begin, end,
    channels==RGBW_CHANNEL_WHITE
    ? RGBW_CHANNEL_RGB
    : channels
  );
#else
  return mvd::RgbwBounds(begin, end, channels);
#endif
}

} // end namespace 'mvd'

#endif // mvdColorDynamicsController_h
