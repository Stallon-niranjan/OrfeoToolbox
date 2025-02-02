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

#ifndef mvdSystemError_h
#define mvdSystemError_h

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
#include <stdexcept>

//
// ITK includes (sorted by alphabetic order)
#include "itksys/SystemTools.hxx"

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)

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


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class SystemError
 *
 * \ingroup OTBMonteverdiCore
 *
 * \brief WIP.
 */
class OTBMonteverdiCore_EXPORT SystemError : public std::runtime_error
{

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

  //
  // Public methods.
public:
  /** \brief Constructor. */
  SystemError(const std::string& message = std::string()) : std::runtime_error(itksys::SystemTools::GetLastSystemError() + ": " + message){};

  /** \brief Destructor. */
  ~SystemError() noexcept override{};

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
  /**
   */

  //
  // Private attributes.
private:
};

} // end namespace 'mvd'.

/*****************************************************************************/
/* INLINE SECTION                                                            */


#endif // mvdSystemError_h
