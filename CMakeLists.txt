# Minimum version required CMAKE
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# FME (Feature Matching Evaluation)
project(fme CXX)



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

    message(STATUS "Found Qt")
    message(STATUS "  Module : ${Qt5Core_DIR}")
    message(STATUS "  Module : ${Qt5Widgets_DIR}")
    message(STATUS "  Module : ${Qt5Help_DIR}")
    message(STATUS "  Module : ${Qt5Concurrent_DIR}")
    message(STATUS "  Module : ${Qt5LinguistTools_DIR}")
    message(STATUS "  Module : ${Qt5Charts_DIR}")
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
    else()
        set(HAVE_BOOST NO)
    endif(Boost_FOUND)

endif(WITH_BOOST)

#------------------------------------------------------------#

# OpenCV

if(WITH_OPENCV)

    find_package(OpenCV REQUIRED
                 COMPONENTS
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

    if(NOT OPENCV_FOUND)
        set(HAVE_OPENCV NO)
    else()
        set(HAVE_OPENCV YES)
        include_directories(${OpenCV_INCLUDE_DIRS})
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

endif()

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
configure_file("${PROJECT_SOURCE_DIR}/cmake/config_fme.h.in" "${PROJECT_BINARY_DIR}/config_fme.h")
include_directories("${PROJECT_BINARY_DIR}")

# resources
set(FME_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/res/res.qrc)

add_subdirectory(third_party)
add_subdirectory(src)


## includes
#include_directories(${CMAKE_BUILD_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/third_party)
#include_directories(${CMAKE_SOURCE_DIR}/src)
#
## sources
#set(FME_SRC
#    main.cpp
#    MainWindowFME.cpp
#    src/fme/ui/MatchingViewer/MatchigGraphicsView.cpp
#    src/fme/ui/MatchingViewer/MatchingViewer.cpp
#    src/fme/ui/MatchingViewer/PWImage.cpp
#    src/fme/ui/MatchingViewer/Camera.cpp
#    src/fme/ui/MatchingViewer/CameraModel.cpp
#    src/fme/ui/MatchingViewer/ExternalOrientation.cpp
#    src/fme/ui/MatchingViewer/PW2dPoint.cpp
#    src/fme/ui/MatchingViewer/PWPoint.cpp
#    src/fme/process/ExternalProcess.cpp
#    src/fme/process/MultiProcess.cpp
#    src/fme/process/Process.cpp
#    src/fme/process/ProcessConcurrent.cpp
#    src/fme/process/brief/BRIEF_KPDescProcess.cpp
#    src/fme/process/brisk/BRISK_KPDetProcess.cpp
#    src/fme/process/brisk/BRISK_KPDescProcess.cpp
#    src/fme/process/daisy/DAISY_KPDescProcess.cpp
#    src/fme/process/fast/FAST_KPDetProcess.cpp
#    src/fme/process/freak/FREAK_KPDescProcess.cpp
#    src/fme/process/gftt/GFTT_KPDetProcess.cpp
#    src/fme/process/hog/HOG_KPDescProcess.cpp
#    src/fme/process/latch/LATCH_KPDescProcess.cpp
#    # Falta por añadir widget y ver parametros del descriptor
#	src/fme/process/lss/LSS_KPDescProcess.cpp
#    src/fme/process/lss/lss.cpp
#    src/fme/process/lucid/LUCID_KPDescProcess.cpp
#    src/fme/process/msd/MSD_KPDetProcess.cpp
#    src/fme/process/msd/MSD.cpp
#    src/fme/process/msd/MSDImgPyramid.cpp
#    src/fme/process/mser/MSER_KPDetProcess.cpp
#    src/fme/process/mtm/mtm.cpp
#    src/fme/process/mtm/MTM_KPDescProcess.cpp
#    #TODO: Quitar
#	src/fme/process/mutualinformation/MutualInformation_KPDescProcess.cpp
#    src/fme/process/orb/ORB_KPDetProcess.cpp
#    src/fme/process/orb/ORB_KPDescProcess.cpp
#    src/fme/process/sift/SIFT_KPDescProcess.cpp
#    src/fme/process/sift/SIFT_KPDetProcess.cpp
#    src/fme/process/surf/SURF_KPDetProcess.cpp
#    src/fme/process/surf/SUFT_KPDescProcess.cpp
#    src/fme/process/ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp
#    src/fme/process/ImagePreprocessing/WallisFilter_Process.cpp
#    src/fme/process/ImagePreprocessing/Downsample_Process.cpp
#    src/fme/process/ImagePreprocessing/LCE_BSESCS2014_Process.cpp
#    src/fme/process/ImagePreprocessing/RajuNair2014_Process.cpp
#    src/fme/process/ImagePreprocessing/Lal2014_Process.cpp
#    src/fme/process/ImagePreprocessing/MSRCP2014_Process.cpp
#    src/fme/process/ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp
#    src/fme/process/ImagePreprocessing/POHE2013_Process.cpp
#    src/fme/process/ImagePreprocessing/Kimori2013_Process.cpp
#    src/fme/process/ImagePreprocessing/CelikTjahjadi2012_Process.cpp
#    src/fme/process/ImagePreprocessing/LiuJinChenLiuLi2011_Process.cpp
#    src/fme/process/ImagePreprocessing/Sundarami2011_Process.cpp
#    src/fme/process/ImagePreprocessing/MaryKim2008_Process.cpp
#    src/fme/process/ImagePreprocessing/WadudKabirDewanChae2007_Process.cpp
#    src/fme/process/ImagePreprocessing/FAHE2006_Process.cpp
#    src/fme/process/ImagePreprocessing/LambertiMontrucchioSanna2006_Process.cpp
#    src/fme/process/ImagePreprocessing/YuBajaj2004_Process.cpp
#    src/fme/process/Matching/BFMatcherProcess.cpp
#    src/fme/process/Matching/RobustMatcherRefinementProcess.cpp
#    src/fme/process/Matching/FLANNMatcherProcess.cpp
#    src/fme/process/Matching/WriteMatchesToAperoProcess.cpp
#    third_party/photo/image.cpp
#    third_party/photo/thumbnail.cpp
#    third_party/photo/tabshortcuts.cpp
#    third_party/photo/tabgeneral.cpp
#    third_party/photo/settings.cpp
#    third_party/photo/menu.cpp
#    third_party/photo/photoviewer.cpp
#    third_party/photo/pixmapitem.cpp
#    third_party/photo/CrossGraphicItem.cpp
#    third_party/photo/crosshairgraphicsitem.cpp
#    DependencyInfoWidget.cpp
#    ProgressDialog.cpp
#    AboutFME.cpp
#    GrountTruthBuilderProcess.cpp
#)
#
## headers
#set(FME_HEADERS
#    MainWindowFME.h
#    src/fme/ui/MatchingViewer/MatchigGraphicsView.h
#    src/fme/ui/MatchingViewer/MatchingViewer.h
#    src/fme/ui/MatchingViewer/PWImage.h
#    src/fme/ui/MatchingViewer/Camera.h
#    src/fme/ui/MatchingViewer/CameraModel.h
#    src/fme/ui/MatchingViewer/ExternalOrientation.h
#    src/fme/ui/MatchingViewer/PW2dPoint.h
#    src/fme/ui/MatchingViewer/PWPoint.h
#    src/fme/process/ExternalProcess.h
#    src/fme/process/MultiProcess.h
#    src/fme/process/Process.h
#    src/fme/process/ProcessConcurrent.h
#    src/fme/process/brief/BRIEF_KPDescProcess.h
#    src/fme/process/brisk/BRISK_KPDetProcess.h
#    src/fme/process/brisk/BRISK_KPDescProcess.h
#    src/fme/process/daisy/DAISY_KPDescProcess.h
#    src/fme/process/fast/FAST_KPDetProcess.h
#    src/fme/process/freak/FREAK_KPDescProcess.h
#    src/fme/process/gftt/GFTT_KPDetProcess.h
#    src/fme/process/hog/HOG_KPDescProcess.h
#    src/fme/process/latch/LATCH_KPDescProcess.h
#    # Falta por añadir widget y ver parametros del descriptor
#	src/fme/process/lss/LSS_KPDescProcess.h
#    src/fme/process/lss/lss.h
#    src/fme/process/lucid/LUCID_KPDescProcess.h
#    src/fme/process/msd/MSD_KPDetProcess.h
#    src/fme/process/msd/MSD.h
#    src/fme/process/msd/MSDImgPyramid.h
#    src/fme/process/mser/MSER_KPDetProcess.h
#    src/fme/process/MTM/mtm.h
#    src/fme/process/MTM/MTM_KPDescProcess.h
#    #TODO: Quitar
#	src/fme/process/mutualinformation/MutualInformation_KPDescProcess.h
#    src/fme/process/orb/ORB_KPDetProcess.h
#    src/fme/process/orb/ORB_KPDescProcess.h
#    src/fme/process/surf/SURF_KPDetProcess.h
#    src/fme/process/surf/SUFT_KPDescProcess.h
#    src/fme/process/sift/SIFT_KPDetProcess.h
#    src/fme/process/sift/SIFT_KPDescProcess.h
#    src/fme/process/ImagePreprocessing/ContrastPreservingDecolorization__Process.h
#    src/fme/process/ImagePreprocessing/WallisFilter_Process.h
#    src/fme/process/ImagePreprocessing/Downsample_Process.h
#    src/fme/process/ImagePreprocessing/LCE_BSESCS2014_Process.h
#    src/fme/process/ImagePreprocessing/RajuNair2014_Process.h
#    src/fme/process/ImagePreprocessing/Lal2014_Process.h
#    src/fme/process/ImagePreprocessing/MSRCP2014_Process.h
#    src/fme/process/ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h
#    src/fme/process/ImagePreprocessing/POHE2013_Process.h
#    src/fme/process/ImagePreprocessing/Kimori2013_Process.h
#    src/fme/process/ImagePreprocessing/CelikTjahjadi2012_Process.h
#    src/fme/process/ImagePreprocessing/LiuJinChenLiuLi2011_Process.h
#    src/fme/process/ImagePreprocessing/Sundarami2011_Process.h
#    src/fme/process/ImagePreprocessing/MaryKim2008_Process.h
#    src/fme/process/ImagePreprocessing/WadudKabirDewanChae2007_Process.h
#    src/fme/process/ImagePreprocessing/FAHE2006_Process.h
#    src/fme/process/ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h
#    src/fme/process/ImagePreprocessing/YuBajaj2004_Process.h
#    src/fme/process/Matching/BFMatcherProcess.h
#    src/fme/process/Matching/RobustMatcherRefinementProcess.h
#    src/fme/process/Matching/FLANNMatcherProcess.h
#    src/fme/process/Matching/WriteMatchesToAperoProcess.h
#    third_party/photo/image.h
#    third_party/photo/thumbnail.h
#    third_party/photo/thbthread.h
#    third_party/photo/tabshortcuts.h
#    third_party/photo/tabgeneral.h
#    third_party/photo/settings.h
#    third_party/photo/menu.h
#    third_party/photo/photoviewer.h
#    third_party/photo/pixmapitem.h
#    third_party/photo/CrossGraphicItem.h
#    third_party/photo/crosshairgraphicsitem.h
#    DependencyInfoWidget.h
#    ProgressDialog.h
#    AboutFME.h
#    GrountTruthBuilderProcess.h
#)
#
## forms
#set(FME_FORMS
#    MainWindowFME.ui
#    ProgressDialog.ui
#    AboutFME.ui
#)
#
## resources
#set(FME_RES
#    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
#    ${CMAKE_CURRENT_SOURCE_DIR}/style.qrc
#    ${CMAKE_CURRENT_SOURCE_DIR}/photo/res.qrc)
#
#list(APPEND FME_SRC FME.rc)
#
## Translation files
### TODO: Por si se quiere añadir soporte para varios idiomas
#SET(FME_TS_FILES
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_en.ts
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_es.ts
#)
#
#qt5_add_translation(FME_QM_FILES ${FME_TS_FILES})
#
#qt5_add_resources(UI_FME_RES ${FME_RES})
#
#
#add_executable(${PROJECT_NAME} WIN32
#               ${FME_SRC}
#               ${FME_HEADERS}
#               ${FME_FORMS}
#               ${UI_FME_RES}
#               #${FME_TS_FILES}
#)
#
#source_group("Form Files"  FILES ${FME_FORMS})
#source_group("Resource Files"  FILES ${FME_RES})
##source_group("Translation Files"  FILES ${FME_TS_FILES})
#
## Lincado de librerias
#target_link_libraries(${PROJECT_NAME}
#                      Qt5::Core
#                      Qt5::Widgets
#                      ${OpenCV_LIBS}
#                      ${Boost_SYSTEM_LIBRARY}
#                      ${Boost_THREAD_LIBRARY}
#                      ${Boost_CHRONO_LIBRARY}
#                      ${Boost_DATE_TIME_LIBRARY}
#                      ${Boost_ATOMIC_LIBRARY}
#                      ${PIXKIT_LIBRARIES}
#)
#
#if(ENABLE_SOLUTION_FOLDERS)
#  set_target_properties(${PROJECT_NAME}  PROPERTIES FOLDER "fme")
#endif()



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
