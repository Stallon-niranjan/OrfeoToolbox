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

#include "mvdAbstractWorker.h"


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
#include "mvdI18nCoreApplication.h"

namespace mvd
{
/*
  TRANSLATOR mvd::AbstractWorker

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */

namespace
{
} // end of anonymous namespace.

/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
AbstractWorker::AbstractWorker(QObject* p) : QObject(p)
{
}

/*******************************************************************************/
AbstractWorker::~AbstractWorker()
{
}

/*****************************************************************************/
void AbstractWorker::Do() noexcept
{
  QObject* result = NULL;

  try
  {
    // Just do it and get resulting QObject.
    result = virtual_Do();

    // Access application.
    const QCoreApplication* app = QCoreApplication::instance();
    assert(app != NULL);

    // Move object into application's main thread.
    //
    // We can only push to another thread,
    // so thread affinity must be set here,
    // and not in the slot that receives the object.
    if (result != NULL && result->thread() != app->thread())
      result->moveToThread(app->thread());

    // Emit task/job has correctly been done giving resulting object
    // to main thread.
    Q_EMIT Done(result);
  }
  catch (std::exception& exc)
  {
    // Delete allocated object.
    delete result;
    result = NULL;

    // Emit task/job has incorrectly been done giving clone of
    // exception to main thread.
    Q_EMIT ExceptionRaised(FromStdString(exc.what()));
  }

  // Emit task/job has finished (thread can be signal to quit()).
  Q_EMIT Finished();
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/

} // end namespace 'mvd'
