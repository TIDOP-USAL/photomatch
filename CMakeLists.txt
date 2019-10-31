# Minimum version required CMAKE
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# PhotoMatch
project(photomatch CXX)



##############################################################
# Configuration                                              #
##############################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_DEBUG_POSTFIX d)

set(CMAKE_CONFIGURATION_TYPES Release;Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

if(MSVC)

    # Warning level
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

    #/EH (Modelo de control de excepciones)
    #/EHsc captura solo las excepciones de C++ e indica al compilador que suponga que las funciones declaradas como extern "C" jamás inician una excepción de C++.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

endif(MSVC)

if (UNIX)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

endif(UNIX)

# Find extra modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})


# Build test
OPTION (BUILD_TEST            "Include test"          OFF)

if(BUILD_TEST)
  enable_testing()
endif(BUILD_TEST)

# Se permite elegir entre libreria estatica o dinamica
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

# Por defecto se establece el tipo de librería estática
set (LIB_TYPE STATIC)

if (BUILD_SHARED_LIBS)
  # Se configura como libreria estática
  set (LIB_TYPE SHARED)
  
  if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
  endif(MSVC)
  
endif (BUILD_SHARED_LIBS)

##############################################################
# 3rd-party libraries                                        #
##############################################################

### No son opcionales
option(WITH_BOOST    "Include Boost"                   ON)
option(WITH_OPENCV   "Include OpenCV"                  ON)
option(WITH_PIXKIT   "Include PixKit"                  ON)
if(MSVC)
option (WITH_VLD     "Include Visual Leak Detector Support"    OFF)
endif(MSVC)
option(WITH_CUDA     "Include Cuda"                    OFF)

#------------------------------------------------------------#

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

if(WITH_BOOST)

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

endif(WITH_BOOST)

#------------------------------------------------------------#

# OpenCV

set(HAVE_CUDA NO)

if(WITH_OPENCV)

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
  endif(WITH_CUDA)

    find_package(OpenCV REQUIRED
                 COMPONENTS ${OPENCV_MODULES})

    if(NOT OPENCV_FOUND)
        set(HAVE_OPENCV NO)
    else()
        set(HAVE_OPENCV YES)
        include_directories(${OpenCV_INCLUDE_DIRS})
        message(STATUS "Found OpenCV")
        message(STATUS "  Includes:  ${OpenCV_INCLUDE_DIRS}")
        message(STATUS "  Libraries: ${OpenCV_LIBS}")
        if(WITH_CUDA)
            set(HAVE_CUDA YES)
        endif(WITH_CUDA)
    endif()

endif(WITH_OPENCV)

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

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Configuration header file
configure_file("${PROJECT_SOURCE_DIR}/cmake/config_photomatch.h.in" "${PROJECT_BINARY_DIR}/config_photomatch.h")
include_directories("${PROJECT_BINARY_DIR}")

# resources
set(PHOTOMATCH_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/res/res.qrc)

add_subdirectory(third_party)
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
