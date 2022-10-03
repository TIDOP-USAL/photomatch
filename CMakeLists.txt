##########################################################################
#                                                                        #
# Copyright 2016 by Tidop Research Group <daguilera@usal.es>             #
#                                                                        #
# This file is part of PhotoMatch                                        #
#                                                                        #
# PhotoMatch is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# PhotoMatch is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with PhotoMatch. If not, see <http://www.gnu.org/licenses/>.     #
#                                                                        #
# https://spdx.org/licenses/GPL-3.0-or-later.html                        #
#                                                                        #
##########################################################################

cmake_minimum_required(VERSION 3.10.0...3.22)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()


project(PhotoMatch 
        VERSION 1.1.0 
        DESCRIPTION "Open-source multi-view and multimodal feature matching tool for photogrammetric applications."
        HOMEPAGE_URL "https://github.com/TIDOP-USAL/photomatch"
		LANGUAGES CXX)


message(STATUS "\n${PROJECT_NAME} ${PhotoMatch_VERSION}")
message(STATUS ${PhotoMatch_DESCRIPTION})
message(STATUS ${PhotoMatch_HOMEPAGE_URL})


##############################################################
# Configuration                                              #
##############################################################

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CONFIGURATION_TYPES Release;Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")


if(MSVC)

    # Warning level
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

    #/EH (Modelo de control de excepciones)
    #/EHsc captura solo las excepciones de C++ e indica al compilador que suponga que las funciones declaradas como extern "C" jamás inician una excepción de C++.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

    # Las llamadas a los métodos potencialmente no seguros en la biblioteca estandar de C++ dan lugar
    # a una advertencia del compilador (nivel 3) C4996.
    # Para deshabilitar esta advertencia se debe definir la macro _SCL_SECURE_NO_WARNINGS
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE")
	
endif(MSVC)


if (UNIX)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

endif(UNIX)



# Find extra modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

# Build test
OPTION (BUILD_TEST            "Include test"          OFF)

if(BUILD_TEST)
  enable_testing()
endif(BUILD_TEST)

# Se permite elegir entre libreria estatica o dinamica
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)


set (LIB_TYPE STATIC)

if (BUILD_SHARED_LIBS)
  set (LIB_TYPE SHARED)
  
  if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
  endif(MSVC)
  
endif (BUILD_SHARED_LIBS)


include(CompilerInfo)
include(OperatingSystemInfo)

include(CMakeDependentOption)


##########################################################################
#  Dependencies                                                          #
#------------------------------------------------------------------------#
# - TidopLib                  REQUIRED                                   #
# - BOOST                     REQUIRED                                   #
# - CUDA                      REQUIRED                                   #
# - OpenCV                    REQUIRED                                   #
# - COLMAP                    REQUIRED                                   #
# - OpenMP                    OPTIONAL                                   #
# - Qt5                       REQUIRED                                   #
# - CloudCompare              REQUIRED                                   #
# - VLD                       OPTIONAL                                   #
##########################################################################

### No son opcionales
#option(WITH_BOOST    "Include Boost"                   ON)
#option(WITH_OPENCV   "Include OpenCV"                  ON)
option(WITH_PIXKIT   "Include PixKit"                  ON)
if(MSVC)
option (WITH_VLD     "Include Visual Leak Detector Support"    OFF)
endif(MSVC)
option(WITH_CUDA     "Include Cuda"                    ON)


message(STATUS "\nDependency loading:\n")


##########################################################################
# TidopLib (REQUIRED)                                                    #
##########################################################################      

find_package(TidopLib 2.1 REQUIRED)



# Qt
find_package(Qt5 REQUIRED 
             COMPONENTS 
               Core 
               Widgets
               Help
               Concurrent
               LinguistTools
               Charts)

if(BUILD_TEST)
find_package(Qt5 REQUIRED 
             COMPONENTS 
               Test)
endif(BUILD_TEST)

if (Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif(Qt5_POSITION_INDEPENDENT_CODE)

if(Qt5_FOUND)

    include_directories(${Qt5Core_INCLUDE_DIRS}
                        ${Qt5Widgets_INCLUDE_DIRS}
                        ${Qt5Help_INCLUDE_DIRS}
                        ${Qt5Concurrent_INCLUDE_DIRS}
                        ${Qt5LinguistTools_INCLUDE_DIRS}
                        ${Qt5Charts_INCLUDE_DIRS})

    message(STATUS "\n")
    message(STATUS "Found Qt")
    message(STATUS "  Module : ${Qt5Core_DIR}")
    message(STATUS "  Module : ${Qt5Widgets_DIR}")
    message(STATUS "  Module : ${Qt5Help_DIR}")
    message(STATUS "  Module : ${Qt5Concurrent_DIR}")
    message(STATUS "  Module : ${Qt5LinguistTools_DIR}")
    message(STATUS "  Module : ${Qt5Charts_DIR}")
    message(STATUS "\n")
endif()

#------------------------------------------------------------#

# Boost


set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)

find_package(Boost REQUIRED
             COMPONENTS
                 thread
                 chrono
                 filesystem
                 system
                 date_time
                 atomic)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    set(HAVE_BOOST YES)
    message(STATUS "\n")
else()
    set(HAVE_BOOST NO)
endif(Boost_FOUND)



#------------------------------------------------------------#

if (WITH_CUDA)
find_package(CUDA)
include_directories(${CUDA_INCLUDE_DIRS})

if (CUDA_FOUND)
  message(STATUS "  Includes: ${CUDA_INCLUDE_DIRS}")
  message(STATUS "  Libraries: ${CUDA_LIBRARIES}")
  set(HAVE_CUDA YES)
else()
  set(HAVE_CUDA NO)
endif()

endif(WITH_CUDA)

# OpenCV


list(APPEND OPENCV_MODULES
    core
    highgui
    photo
    xfeatures2d
    imgproc
    imgcodecs
    calib3d
    features2d
    flann
    objdetect)

if(WITH_CUDA)
    list(APPEND OPENCV_MODULES
        cudafilters
        cudawarping
        cudev
        cudaarithm
        cudafeatures2d)
    #set(HAVE_CUDA YES)
else()
    #set(HAVE_CUDA NO)
endif(WITH_CUDA)

find_package(OpenCV REQUIRED
             COMPONENTS ${OPENCV_MODULES})

if(NOT OPENCV_FOUND)
    set(HAVE_OPENCV NO)
else()
    set(HAVE_OPENCV YES)
    include_directories(${OpenCV_INCLUDE_DIRS})
    message(STATUS "Found OpenCV")
    message(STATUS "  Include:  ${OpenCV_INCLUDE_DIRS}")
    message(STATUS "  Libraries: ${OpenCV_LIBS}")
endif()

#------------------------------------------------------------#

# PixKit

if(WITH_PIXKIT)

    find_package(PIXKIT REQUIRED)
    if(NOT PIXKIT_FOUND)
        set(HAVE_PIXKIT NO)
    else()
        set(HAVE_PIXKIT YES)
        include_directories(${PIXKIT_INCLUDE_DIRS})
    endif()

endif(WITH_PIXKIT)


#------------------------------------------------------------#

# VLD

if(WITH_VLD)

    find_package(VLD)

    if(NOT VLD_FOUND)
        set(HAVE_VLD NO)
    else()
        set(HAVE_VLD YES)
        include_directories(${VLD_INCLUDE_DIRS})
    endif()

endif(WITH_VLD)


##############################################################
# LIB / EXE                                                  #
##############################################################

set(TL_MESSAGE_HANDLER YES)
message(STATUS "[TidopLib] Message manager enabled")

#configure_file("${PROJECT_SOURCE_DIR}/cmake/config_tl.h.in" "${PROJECT_BINARY_DIR}/config_tl.h")
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(third_party)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Configuration header file
configure_file("${PROJECT_SOURCE_DIR}/cmake/config_photomatch.h.in" "${PROJECT_BINARY_DIR}/config_photomatch.h")


# resources
set(PHOTOMATCH_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/res/res.qrc)

add_subdirectory(src)


##############################################################
# Test                                                       #
##############################################################

if (BUILD_TEST)
add_subdirectory(test)
endif(BUILD_TEST)




##############################################################
# Install                                                    #
##############################################################
#
#if(WIN32)
#    if (MSVC AND NOT BUILD_SHARED_LIBS)
#        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
#    endif()
#
#    install(TARGETS ${PROJECT_NAME}
#            RUNTIME DESTINATION "${PROJECT_BINARY_DIR}"
#            COMPONENT bin)
#endif()
