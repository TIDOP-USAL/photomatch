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

set(FME_SRC
    main.cpp
    mvp.h
    MainWindowModel.cpp
    MainWindowModel.h
    MainWindowPresenter.cpp
    MainWindowPresenter.h
    MainWindowView.cpp
    MainWindowView.h
    NewProjectInterfaces.h
    NewProjectView.cpp
    NewProjectView.h
    NewProjectPresenter.cpp
    NewProjectPresenter.h
    ProjectModel.cpp
    ProjectModel.h
    SettingsModel.cpp
    SettingsModel.h
    SettingsPresenter.cpp
    SettingsPresenter.h
    SettingsView.cpp
    SettingsView.h
)  

if(MSVC)
  #list(APPEND FME_SRC ui/resource.h ui/fme.rc)
endif(MSVC)

# forms
set(FME_FORMS
  MainWindowView.ui
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
               ${FME_SRC}
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
                      Qt5::Core
                      Qt5::Widgets
                      libcore
#                      ${OpenCV_LIBS}
#                      ${Boost_SYSTEM_LIBRARY}
#                      ${Boost_THREAD_LIBRARY}
#                      ${Boost_CHRONO_LIBRARY}
#                      ${Boost_DATE_TIME_LIBRARY}
#                      ${Boost_ATOMIC_LIBRARY}
#                      ${PIXKIT_LIBRARIES}
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


