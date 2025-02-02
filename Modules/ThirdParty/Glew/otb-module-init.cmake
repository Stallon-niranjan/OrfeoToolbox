#
# Copyright (C) 2005-2022 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

find_package(GLEW REQUIRED)

# FIX: glew-config.cmake import GLEW::GLEW target but does not necessarily set GLEW_LIBRARY
if(NOT GLEW_LIBRARY)
  if(WIN32)
    get_target_property(GLEW_LIBRARY GLEW::GLEW IMPORTED_IMPLIB_RELEASE)
  else()
    get_target_property(GLEW_LIBRARY GLEW::GLEW IMPORTED_LOCATION_RELEASE)
  endif()
endif()

mark_as_advanced(GLEW_INCLUDE_DIR)
mark_as_advanced(GLEW_LIBRARY)

if(NOT GLEW_FOUND)
 message(FATAL_ERROR "Cannot find Glew. Set GLEW_INCLUDE_DIR and GLEW_LIBRARY")
endif()
