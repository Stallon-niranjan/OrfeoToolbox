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


#include "otbKMLVectorDataIO.h"
#include <iostream>

int otbKMLVectorDataIOTestCanRead(int itkNotUsed(argc), char* argv[])
{
  typedef otb::KMLVectorDataIO KMLVectorDataIOType;
  KMLVectorDataIOType::Pointer object   = KMLVectorDataIOType::New();
  bool                         lCanRead = object->CanReadFile(argv[1]);
  if (lCanRead == false)
  {
    std::cerr << "Erreur otb::KMLVectorDataIO : impossible to open the file " << argv[1] << "." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
