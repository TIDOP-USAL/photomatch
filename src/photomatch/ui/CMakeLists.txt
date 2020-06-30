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
# Ejecutable PhotoMatch                                                                             #
#--------------------------------------------------------------------------------------------#

project(photomatch)

set(PHOTOMATCH_SOURCES
    main.cpp
    ComponentsManager.cpp
    MainWindowModel.cpp
    MainWindowPresenter.cpp
    MainWindowView.cpp
    createproj/NewProjectView.cpp
    createproj/NewProjectPresenter.cpp
    createsession/NewSessionView.cpp
    createsession/NewSessionPresenter.cpp
    ProjectModel.cpp
    settings/SettingsModel.cpp
    settings/SettingsPresenter.cpp
    settings/SettingsView.cpp
    preprocess/PreprocessView.cpp
    preprocess/PreprocessModel.cpp
    preprocess/PreprocessPresenter.cpp
    featextract/FeatureExtractorView.cpp
    featextract/FeatureExtractorModel.cpp
    featextract/FeatureExtractorPresenter.cpp
    featmatch/DescriptorMatcherView.cpp
    featmatch/DescriptorMatcherModel.cpp
    featmatch/DescriptorMatcherPresenter.cpp
    featviewer/FeaturesViewerView.cpp
    featviewer/FeaturesViewerModel.cpp
    featviewer/FeaturesViewerPresenter.cpp
    matchviewer/MatchViewerModel.cpp
    matchviewer/MatchViewerView.cpp
    matchviewer/MatchViewerPresenter.cpp
    multiview/MultiViewModel.cpp
    multiview/MultiViewView.cpp
    multiview/MultiViewPresenter.cpp
    homography/HomographyViewerModel.cpp
    homography/HomographyViewerView.cpp
    homography/HomographyViewerPresenter.cpp
    curves/CurvesViewerModel.cpp
    curves/CurvesViewerView.cpp
    curves/CurvesViewerPresenter.cpp
    groundtruth/GroundTruthModel.cpp
    groundtruth/GroundTruthView.cpp
    groundtruth/GroundTruthPresenter.cpp
    repeatability/RepeatabilityModel.cpp
    repeatability/RepeatabilityView.cpp
    repeatability/RepeatabilityPresenter.cpp
    exportfeat/ExportFeaturesModel.cpp
    exportfeat/ExportFeaturesView.cpp
    exportfeat/ExportFeaturesPresenter.cpp
    exportmatch/ExportMatchesModel.cpp
    exportmatch/ExportMatchesView.cpp
    exportmatch/ExportMatchesPresenter.cpp
    #BatchModel.cpp
    #BatchView.cpp
    #BatchPresenter.cpp
    AboutDialog.cpp
    HelpDialog.cpp
    utils/GraphicViewer.cpp
    utils/ProgressDialog.cpp
    utils/Progress.cpp
    #utils/KeyPointGraphicsItem.cpp
    #utils/CrossGraphicItem.cpp
    #utils/DiagonalCrossGraphicItem.cpp
    #utils/CircleGraphicItem.cpp
    utils/GraphicItem.cpp
    utils/TabHandler.cpp
    ${CMAKE_SOURCE_DIR}/third_party/easyexif/exif.cpp
)

set(PHOTOMATCH_HEADERS
    mvp.h
    ComponentsManager.h
    ComponentsManager.cpp
    MainWindowModel.h
    MainWindowPresenter.h
    MainWindowView.h
    createproj/NewProject.h
    createproj/NewProjectView.h
    createproj/NewProjectPresenter.h
    createsession/NewSession.h
    createsession/NewSessionView.h
    createsession/NewSessionPresenter.h
    ProjectModel.h
    settings/Settings.h
    settings/SettingsModel.h
    settings/SettingsPresenter.h
    settings/SettingsView.h
    preprocess/Preprocess.h
    preprocess/PreprocessView.h
    preprocess/PreprocessModel.h
    preprocess/PreprocessPresenter.h
    featextract/FeatureExtractor.h
    featextract/FeatureExtractorView.h
    featextract/FeatureExtractorModel.h
    featextract/FeatureExtractorPresenter.h
    featmatch/DescriptorMatcher.h
    featmatch/DescriptorMatcherView.h
    featmatch/DescriptorMatcherModel.h
    featmatch/DescriptorMatcherPresenter.h
    featviewer/FeaturesViewer.h
    featviewer/FeaturesViewerView.h
    featviewer/FeaturesViewerModel.h
    featviewer/FeaturesViewerPresenter.h
    matchviewer/MatchViewer.h
    matchviewer/MatchViewerModel.h
    matchviewer/MatchViewerView.h
    matchviewer/MatchViewerPresenter.h
    multiview/Multiview.h
    multiview/MultiViewModel.h
    multiview/MultiViewView.h
    multiview/MultiViewPresenter.h
    homography/HomographyViewer.h
    homography/HomographyViewerModel.h
    homography/HomographyViewerView.h
    homography/HomographyViewerPresenter.h
    curves/CurvesViewer.h
    curves/CurvesViewerModel.h
    curves/CurvesViewerView.h
    curves/CurvesViewerPresenter.h
    groundtruth/GroundTruth.h
    groundtruth/GroundTruthModel.h
    groundtruth/GroundTruthView.h
    groundtruth/GroundTruthPresenter.h
    repeatability/Repeatability.h
    repeatability/RepeatabilityModel.h
    repeatability/RepeatabilityView.h
    repeatability/RepeatabilityPresenter.h
    exportfeat/ExportFeatures.h
    exportfeat/ExportFeaturesModel.h
    exportfeat/ExportFeaturesView.h
    exportfeat/ExportFeaturesPresenter.h
    exportmatch/ExportMatches.h
    exportmatch/ExportMatchesModel.h
    exportmatch/ExportMatchesView.h
    exportmatch/ExportMatchesPresenter.h
    #BatchModel.h
    #BatchView.h
    #BatchPresenter.h
    AboutDialog.h
    HelpDialog.h
    utils/GraphicViewer.h
    utils/ProgressDialog.h
    utils/Progress.h
    #utils/KeyPointGraphicsItem.h
    #utils/CrossGraphicItem.h
    #utils/DiagonalCrossGraphicItem.h
    #utils/CircleGraphicItem.h
    utils/GraphicItem.h
    utils/TabHandler.h
    ${CMAKE_SOURCE_DIR}/third_party/easyexif/exif.h
)

if(MSVC)
  list(APPEND PHOTOMATCH_SOURCES resource.h photomatch.rc)
endif(MSVC)

# forms
set(PHOTOMATCH_FORMS
  MainWindowView.ui
  AboutDialog.ui
  utils/ProgressDialog.ui
)

# Translation files
### TODO: Por si se quiere añadir soporte para varios idiomas
SET(PHOTOMATCH_TS_FILES
    ${CMAKE_SOURCE_DIR}/res/lang/photomatch_en.ts
    ${CMAKE_SOURCE_DIR}/res/lang/photomatch_es.ts
)

#qt5_add_translation(PHOTOMATCH_QM_FILES ${PHOTOMATCH_TS_FILES})
qt5_create_translation(PHOTOMATCH_QM_FILES ${CMAKE_SOURCE_DIR} photomatch_en.ts photomatch_es.ts)

QT5_ADD_RESOURCES(UI_PHOTOMATCH_RES ${PHOTOMATCH_RESOURCES} )

add_executable(${PROJECT_NAME} WIN32
               ${PHOTOMATCH_SOURCES}
               ${PHOTOMATCH_HEADERS}
               ${PHOTOMATCH_FORMS}
               ${UI_PHOTOMATCH_RES}
#               ${PHOTOMATCH_TS_FILES}
)

source_group("Form Files"  FILES ${PHOTOMATCH_FORMS})
source_group("Resource Files"  FILES ${PHOTOMATCH_RESOURCES})
#source_group("Translation Files"  FILES ${PHOTOMATCH_TS_FILES})
#source_group("Header Files\\createproj" FILES ${PHOTOMATCH_HEADERS_CREATE_PROJECT})
#source_group("Source Files\\createproj" FILES ${PHOTOMATCH_SOURCES_CREATE_PROJECT})

foreach(_source IN ITEMS ${PHOTOMATCH_SOURCES} ${PHOTOMATCH_HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    #file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path}")
    source_group("Source Files\\${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${PHOTOMATCH_HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    #file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path}")
    source_group("Header Files\\${_group_path}" FILES "${_source}")
endforeach()

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
                      ${PIXKIT_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${Boost_DATE_TIME_LIBRARY}
                      ${Boost_CHRONO_LIBRARY})

if(HAVE_VLD)
target_link_libraries(${PROJECT_NAME}
                      ${VLD_LIBRARY})
endif()

if (HAVE_CUDA)
target_link_libraries(${PROJECT_NAME}
                      ${CUDA_LIBRARIES})
endif()

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${PROJECT_NAME}  PROPERTIES FOLDER "photomatch")
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


