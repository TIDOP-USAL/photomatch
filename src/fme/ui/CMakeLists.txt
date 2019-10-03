include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

#--------------------------------------------------------------------------------------------#
# Configuración para Qt                                                                      #
#--------------------------------------------------------------------------------------------#

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#--------------------------------------------------------------------------------------------#
# Ejecutable FME                                                                             #
#--------------------------------------------------------------------------------------------#

project(fme)

set(FME_SOURCES
    main.cpp
    MainWindowModel.cpp
    MainWindowPresenter.cpp
    MainWindowView.cpp
    NewProjectView.cpp
    NewProjectPresenter.cpp
    NewSessionView.cpp
    NewSessionPresenter.cpp
    ProjectModel.cpp
    SettingsModel.cpp
    SettingsPresenter.cpp
    SettingsView.cpp
    PreprocessView.cpp
    PreprocessModel.cpp
    PreprocessPresenter.cpp
    FeatureExtractorView.cpp
    FeatureExtractorModel.cpp
    FeatureExtractorPresenter.cpp
    DescriptorMatcherView.cpp
    DescriptorMatcherModel.cpp
    DescriptorMatcherPresenter.cpp
    MatchViewerModel.cpp
    MatchViewerView.cpp
    MatchViewerPresenter.cpp
    HomographyViewerModel.cpp
    HomographyViewerView.cpp
    HomographyViewerPresenter.cpp
    CurvesViewerModel.cpp
    CurvesViewerView.cpp
    CurvesViewerPresenter.cpp
    GroundTruthModel.cpp
    GroundTruthView.cpp
    GroundTruthPresenter.cpp
    AboutDialog.cpp
    utils/GraphicViewer.cpp
    utils/ProgressDialog.cpp
    utils/Progress.cpp
    utils/KeyPointGraphicsItem.cpp
    utils/CrossGraphicItem.cpp
    utils/DiagonalCrossGraphicItem.cpp
    ${CMAKE_SOURCE_DIR}/third_party/easyexif/exif.cpp
)  

set(FME_HEADERS
    mvp.h
    MainWindowModel.h
    MainWindowPresenter.h
    MainWindowView.h
    NewProjectView.h
    NewProjectPresenter.h
    NewSessionView.h
    NewSessionPresenter.h
    ProjectModel.h
    SettingsModel.h
    SettingsPresenter.h
    SettingsView.h
    PreprocessView.h
    PreprocessModel.h
    PreprocessPresenter.h
    FeatureExtractorView.h
    FeatureExtractorModel.h
    FeatureExtractorPresenter.h
    DescriptorMatcherView.h
    DescriptorMatcherModel.h
    DescriptorMatcherPresenter.h
    MatchViewerModel.h
    MatchViewerView.h
    MatchViewerPresenter.h
    HomographyViewerModel.h
    HomographyViewerView.h
    HomographyViewerPresenter.h
    CurvesViewerModel.h
    CurvesViewerView.h
    CurvesViewerPresenter.h
    GroundTruthModel.h
    GroundTruthView.h
    GroundTruthPresenter.h
    AboutDialog.h
    utils/GraphicViewer.h
    utils/ProgressDialog.h
    utils/Progress.h
    utils/KeyPointGraphicsItem.h
    utils/CrossGraphicItem.h
    utils/DiagonalCrossGraphicItem.h
    ${CMAKE_SOURCE_DIR}/third_party/easyexif/exif.h
)

if(MSVC)
  #list(APPEND FME_SRC ui/resource.h ui/fme.rc)
endif(MSVC)

# forms
set(FME_FORMS
  MainWindowView.ui
  AboutDialog.ui
  utils/ProgressDialog.ui
)

# Translation files
### TODO: Por si se quiere añadir soporte para varios idiomas
#SET(FME_TS_FILES
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_en.ts
#    ${CMAKE_SOURCE_DIR}/resources/lang/fme_es.ts
#)

#qt5_add_translation(FME_QM_FILES ${FME_TS_FILES})

QT5_ADD_RESOURCES(UI_FME_RES ${FME_RESOURCES} )

add_executable(${PROJECT_NAME} WIN32
               ${FME_SOURCES}
               ${FME_HEADERS}
               ${FME_FORMS}
               ${UI_FME_RES}
               #${FME_TS_FILES}
)

source_group("Form Files"  FILES ${FME_FORMS})
source_group("Resource Files"  FILES ${FME_RESOURCES})
#source_group("Translation Files"  FILES ${FME_TS_FILES})

# Lincado de librerias
target_link_libraries(${PROJECT_NAME}
                      tl_core
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Help
                      Qt5::Concurrent
                      Qt5::Charts
                      libcore
                      libwidgets
                      libprocess
                      ${OpenCV_LIBS}
#                      ${Boost_ATOMIC_LIBRARY}
                      ${PIXKIT_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${Boost_DATE_TIME_LIBRARY}
                      ${Boost_CHRONO_LIBRARY})

if(HAVE_VLD)
target_link_libraries(${PROJECT_NAME} ${VLD_LIBRARY})
endif()

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


