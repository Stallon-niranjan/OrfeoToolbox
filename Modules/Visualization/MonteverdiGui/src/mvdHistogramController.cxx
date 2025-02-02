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

#include "mvdHistogramController.h"


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
#include "mvdVectorImageModel.h"
#include "mvdHistogramWidget.h"

namespace mvd
{
/*
  TRANSLATOR mvd::HistogramController

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
HistogramController::HistogramController(HistogramWidget* widget, QObject* p) : AbstractModelController(widget, p)
{
}

/*******************************************************************************/
HistogramController::~HistogramController()
{
}

/*******************************************************************************/
void HistogramController::Connect(AbstractModel*)
{
  // HistogramWidget* widget = GetWidget< HistogramWidget >();

  //
  // Connect GUI to controller.

  //
  // Connect controller to model.
}

/*******************************************************************************/
void HistogramController::Disconnect(AbstractModel*)
{
  // HistogramWidget* widget = GetWidget< HistogramWidget >();

  //
  // Disconnect controller to model.

  //
  // Disconnect GUI from controller.
}

/*******************************************************************************/
void HistogramController::ClearWidget()
{
  assert(GetWidget() == GetWidget<HistogramWidget>());
  HistogramWidget* widget = GetWidget<HistogramWidget>();
  assert(widget != NULL);

  widget->Clear();
}

/*******************************************************************************/
void HistogramController::virtual_ResetWidget(bool)
{
  ResetWidget(RGBW_CHANNEL_ALL);
}

/*******************************************************************************/
void HistogramController::ResetWidget(RgbwChannel channel)
{
  assert(GetModel() == GetModel<VectorImageModel>());
  VectorImageModel* imageModel = GetModel<VectorImageModel>();
  assert(imageModel != NULL);

  HistogramModel* model = imageModel->GetHistogramModel();
  assert(model != NULL);

  if (!model->IsValid())
    return;

  assert(GetWidget() == GetWidget<HistogramWidget>());
  HistogramWidget* widget = GetWidget<HistogramWidget>();
  assert(widget != NULL);

  CountType begin = 0;
  CountType end   = 0;

  if (!RgbwBounds(begin, end, channel))
    return;

  const VectorImageSettings& settings = imageModel->GetSettings();

  widget->SetGrayscaleActivated(settings.IsGrayscaleActivated());

  assert(std::numeric_limits<double>::has_quiet_NaN);

  for (CountType i = begin; i < end; ++i)
  {
    RgbwChannel chan = static_cast<RgbwChannel>(i);

    VectorImageSettings::ChannelVector::value_type band = settings.GetRgbwChannel(chan);

    size_t size = model->GetDataCount(band);

    double* x = new double[size];
    double* y = new double[size];

    double xMin = std::numeric_limits<double>::quiet_NaN();
    double yMin = std::numeric_limits<double>::quiet_NaN();
    double xMax = std::numeric_limits<double>::quiet_NaN();
    double yMax = std::numeric_limits<double>::quiet_NaN();

    model->GetData(band, x, y, xMin, xMax, yMin, yMax);

    widget->SetData(chan, x, y, size, xMin, yMin, xMax, yMax);

    widget->SetPrecision(HistogramModel::GetEpsilon());
    widget->SetLowMarker(chan, settings.GetLowIntensity(chan));
    widget->SetHighMarker(chan, settings.GetHighIntensity(chan));

    delete[] x;
    x = NULL;

    delete[] y;
    y = NULL;
  }

  widget->RefreshScale(true);

  widget->Replot();
}

/*****************************************************************************/
/* SLOTS                                                                     */
/*****************************************************************************/
void HistogramController::OnRgbChannelIndexChanged(RgbwChannel channel, int)
{
  /*
  qDebug()
    << this
    << "::OnRgbChannelIndexChanged("
    << RGBW_CHANNEL_NAMES[ channel ] << ", " << band <<
    ")";
  */

  ResetWidget(channel);
}

/*****************************************************************************/
void HistogramController::OnGrayChannelIndexChanged(int)
{
  /*
  qDebug()
    << this
    << "::OnGrayChannelIndexChanged(" << band << ")";
  */

  ResetWidget(RGBW_CHANNEL_WHITE);
}

/*****************************************************************************/
void HistogramController::OnGrayscaleActivated(bool activated)
{
  /*
  qDebug()
    << this
    << "::OnGrayscaleActivated(" << activated << ")";
  */

  assert(GetWidget() == GetWidget<HistogramWidget>());
  HistogramWidget* widget = GetWidget<HistogramWidget>();
  assert(widget != NULL);

  widget->SetGrayscaleActivated(activated);

  widget->RefreshScale(true);
  widget->Replot();
}

/*****************************************************************************/
void HistogramController::OnLowIntensityChanged(RgbwChannel channel, double value, bool refresh)
{
  assert(GetWidget() == GetWidget<HistogramWidget>());
  HistogramWidget* widget = GetWidget<HistogramWidget>();
  assert(widget != NULL);

  widget->SetLowMarker(channel, value);

  if (refresh)
    widget->Replot();
}

/*****************************************************************************/
void HistogramController::OnHighIntensityChanged(RgbwChannel channel, double value, bool refresh)
{
  assert(GetWidget() == GetWidget<HistogramWidget>());
  HistogramWidget* widget = GetWidget<HistogramWidget>();
  assert(widget != NULL);

  widget->SetHighMarker(channel, value);

  if (refresh)
    widget->Replot();
}

/*****************************************************************************/
void HistogramController::OnHistogramRefreshed()
{
  ResetWidget(RGBW_CHANNEL_ALL);
}

/*****************************************************************************/

} // end namespace 'mvd'
