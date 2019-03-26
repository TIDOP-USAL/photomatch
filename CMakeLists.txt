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




##############################################################
# 3rd-party libraries                                        #
##############################################################

### No son opcionales
option(WITH_BOOST    "Include Boost"                   ON)
option(WITH_OPENCV   "Include OpenCV"                  ON)
option(WITH_PIXKIT   "Include PixKit"                  ON)


#------------------------------------------------------------#

# Qt
find_package(Qt5 REQUIRED
             COMPONENTS
                 Core
                 Widgets)

if (Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif(Qt5_POSITION_INDEPENDENT_CODE)

if(Qt5_FOUND)

    include_directories(${Qt5Core_INCLUDE_DIRS}
                        ${Qt5Widgets_INCLUDE_DIRS}
                        )

    message(STATUS "Found Qt")
    message(STATUS "  Module : ${Qt5Core_DIR}")
    message(STATUS "  Module : ${Qt5Widgets_DIR}")
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




##############################################################
# EXE                                                        #
##############################################################

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# includes
include_directories(${CMAKE_BUILD_DIR})
include_directories(photo)

# sources
set(FME_SRC
    main.cpp
    MainWindowFME.cpp
    MatchingViewer/MatchigGraphicsView.cpp
    MatchingViewer/MatchingViewer.cpp
    ProcessManager/ExternalProcess.cpp
    ProcessManager/MultiProcess.cpp
    ProcessManager/Process.cpp
    ProcessManager/ProcessConcurrent.cpp
    photo/image.cpp
    photo/thumbnail.cpp
    photo/tabshortcuts.cpp
    photo/tabgeneral.cpp
    photo/settings.cpp
    photo/menu.cpp
    photo/photoviewer.cpp
    photo/pixmapitem.cpp
    photo/CrossGraphicItem.cpp
    photo/crosshairgraphicsitem.cpp
    MatchingViewer/PWImage.cpp
    MatchingViewer/Camera.cpp
    MatchingViewer/CameraModel.cpp
    MatchingViewer/ExternalOrientation.cpp
    MatchingViewer/PW2dPoint.cpp
    MatchingViewer/PWPoint.cpp
    SIFT/SIFT_KPDetProcess.cpp
    SIFT/SIFT_KPDescProcess.cpp
    DependencyInfoWidget.cpp
    ProgressDialog.cpp
    MSD/MSD_KPDetProcess.cpp
    MSD/MSD.cpp
    MSD/MSDImgPyramid.cpp
    ORB/ORB_KPDetProcess.cpp
    SURF/SURF_KPDetProcess.cpp
    SURF/SUFT_KPDescProcess.cpp
    HOG/HOG_KPDescProcess.cpp
    ORB/ORB_KPDescProcess.cpp
    MutualInformation/MutualInformation_KPDescProcess.cpp
    MTM/mtm.cpp
    LSS/lss.cpp
    MTM/MTM_KPDescProcess.cpp
    LSS/LSS_KPDescProcess.cpp
    AboutFME.cpp
    Matching/BFMatcherProcess.cpp
    Matching/RobustMatcherRefinementProcess.cpp
    GrountTruthBuilderProcess.cpp
    DAISY/DAISY_KPDescProcess.cpp
    FREAK/FREAK_KPDescProcess.cpp
    LATCH/LATCH_KPDescProcess.cpp
    LUCID/LUCID_KPDescProcess.cpp
    FAST/FAST_KPDetProcess.cpp
    GFTT/GFTT_KPDetProcess.cpp
    MSER/MSER_KPDetProcess.cpp
    BRISK/BRISK_KPDetProcess.cpp
    BRISK/BRISK_KPDescProcess.cpp
    BRIEF/BRIEF_KPDescProcess.cpp
    Matching/FLANNMatcherProcess.cpp
    Matching/WriteMatchesToAperoProcess.cpp
    ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp
    ImagePreprocessing/WallisFilter_Process.cpp
    ImagePreprocessing/Downsample_Process.cpp
    ImagePreprocessing/LCE_BSESCS2014_Process.cpp
    ImagePreprocessing/RajuNair2014_Process.cpp
    ImagePreprocessing/Lal2014_Process.cpp
    ImagePreprocessing/MSRCP2014_Process.cpp
    ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp
    ImagePreprocessing/POHE2013_Process.cpp
    ImagePreprocessing/Kimori2013_Process.cpp
    ImagePreprocessing/CelikTjahjadi2012_Process.cpp
    ImagePreprocessing/LiuJinChenLiuLi2011_Process.cpp
    ImagePreprocessing/Sundarami2011_Process.cpp
    ImagePreprocessing/MaryKim2008_Process.cpp
    ImagePreprocessing/WadudKabirDewanChae2007_Process.cpp
    ImagePreprocessing/FAHE2006_Process.cpp
    ImagePreprocessing/LambertiMontrucchioSanna2006_Process.cpp
    ImagePreprocessing/YuBajaj2004_Process.cpp
)

# headers
set(FME_HEADERS
    MainWindowFME.h
    MatchingViewer/MatchigGraphicsView.h
    MatchingViewer/MatchingViewer.h
    ProcessManager/ExternalProcess.h
    ProcessManager/MultiProcess.h
    ProcessManager/Process.h
    ProcessManager/ProcessConcurrent.h
    photo/image.h
    photo/thumbnail.h
    photo/thbthread.h
    photo/tabshortcuts.h
    photo/tabgeneral.h
    photo/settings.h
    photo/menu.h
    photo/photoviewer.h
    photo/pixmapitem.h
    photo/CrossGraphicItem.h
    photo/crosshairgraphicsitem.h
    MatchingViewer/PWImage.h
    MatchingViewer/Camera.h
    MatchingViewer/CameraModel.h
    MatchingViewer/ExternalOrientation.h
    MatchingViewer/PW2dPoint.h
    MatchingViewer/PWPoint.h
    SIFT/SIFT_KPDetProcess.h
    SIFT/SIFT_KPDescProcess.h
    DependencyInfoWidget.h
    ProgressDialog.h
    MSD/MSD_KPDetProcess.h
    MSD/MSD.h
    MSD/MSDImgPyramid.h
    ORB/ORB_KPDetProcess.h
    SURF/SURF_KPDetProcess.h
    SURF/SUFT_KPDescProcess.h
    HOG/HOG_KPDescProcess.h
    ORB/ORB_KPDescProcess.h
    MutualInformation/MutualInformation_KPDescProcess.h
    MTM/mtm.h
    LSS/lss.h
    MTM/MTM_KPDescProcess.h
    LSS/LSS_KPDescProcess.h
    AboutFME.h
    Matching/BFMatcherProcess.h
    Matching/RobustMatcherRefinementProcess.h
    GrountTruthBuilderProcess.h
    DAISY/DAISY_KPDescProcess.h
    FREAK/FREAK_KPDescProcess.h
    LATCH/LATCH_KPDescProcess.h
    LUCID/LUCID_KPDescProcess.h
    FAST/FAST_KPDetProcess.h
    GFTT/GFTT_KPDetProcess.h
    MSER/MSER_KPDetProcess.h
    BRISK/BRISK_KPDetProcess.h
    BRISK/BRISK_KPDescProcess.h
    BRIEF/BRIEF_KPDescProcess.h
    Matching/FLANNMatcherProcess.h
    Matching/WriteMatchesToAperoProcess.h
    ImagePreprocessing/ContrastPreservingDecolorization__Process.h
    ImagePreprocessing/WallisFilter_Process.h
    ImagePreprocessing/Downsample_Process.h
    ImagePreprocessing/LCE_BSESCS2014_Process.h
    ImagePreprocessing/RajuNair2014_Process.h
    ImagePreprocessing/Lal2014_Process.h
    ImagePreprocessing/MSRCP2014_Process.h
    ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h
    ImagePreprocessing/POHE2013_Process.h
    ImagePreprocessing/Kimori2013_Process.h
    ImagePreprocessing/CelikTjahjadi2012_Process.h
    ImagePreprocessing/LiuJinChenLiuLi2011_Process.h
    ImagePreprocessing/Sundarami2011_Process.h
    ImagePreprocessing/MaryKim2008_Process.h
    ImagePreprocessing/WadudKabirDewanChae2007_Process.h
    ImagePreprocessing/FAHE2006_Process.h
    ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h
    ImagePreprocessing/YuBajaj2004_Process.h
)

# forms
set(FME_FORMS
    MainWindowFME.ui
    ProgressDialog.ui
    AboutFME.ui
)

# resources
set(FME_RES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/style.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/photo/res.qrc)

list(APPEND FME_SRC FME.rc)

# Translation files
### TODO: Por si se quiere añadir soporte para varios idiomas
#SET(FME_TS_FILES
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_en.ts
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_es.ts
#)
#
#qt5_add_translation(FME_QM_FILES ${FME_TS_FILES})

qt5_add_resources(UI_FME_RES ${FME_RES})


add_executable(${PROJECT_NAME} WIN32
               ${FME_SRC}
               ${FME_HEADERS}
               ${FME_FORMS}
               ${UI_FME_RES}
               #${FME_TS_FILES}
)

source_group("Form Files"  FILES ${FME_FORMS})
source_group("Resource Files"  FILES ${FME_RES})
#source_group("Translation Files"  FILES ${FME_TS_FILES})

# Lincado de librerias
target_link_libraries(${PROJECT_NAME}
                      Qt5::Core
                      Qt5::Widgets
                      ${OpenCV_LIBS}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${Boost_CHRONO_LIBRARY}
                      ${Boost_DATE_TIME_LIBRARY}
                      ${Boost_ATOMIC_LIBRARY}
                      ${PIXKIT_LIBRARIES}
)

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${PROJECT_NAME}  PROPERTIES FOLDER "fme")
endif()



##############################################################
# Install                                                    #
##############################################################

if(WIN32)
    if (MSVC AND NOT BUILD_SHARED_LIBS)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
    endif()

    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION "${PROJECT_BINARY_DIR}"
            COMPONENT bin)
endif()
