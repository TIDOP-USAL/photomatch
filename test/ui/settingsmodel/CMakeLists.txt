set(test_filename tst_settingsmodel.cpp)
get_filename_component(test_name ${test_filename} NAME_WE)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

set(test_kind test)
set(test_KIND TEST)

set(the_target "${test_kind}_${test_name}")
add_executable(${the_target}
    ${test_filename}
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/settings/SettingsModel.cpp
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/settings/SettingsModel.h
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/settings/Settings.h
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/mvp.h
    )

target_link_libraries(${the_target} PRIVATE
                      tl_core
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Test
                      libcore
                      ${OpenCV_LIBS}
                      ${PIXKIT_LIBRARIES})

target_link_libraries(${the_target} PRIVATE
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_THREAD_LIBRARY}
                      ${Boost_DATE_TIME_LIBRARY}
                      ${Boost_CHRONO_LIBRARY})

if (HAVE_CUDA)
target_link_libraries(${the_target} PRIVATE
                      ${CUDA_LIBRARIES})
endif()

set_property(TARGET ${the_target} PROPERTY FOLDER "test/settings_model")

set_target_properties(${the_target} PROPERTIES
  OUTPUT_NAME ${the_target}
  PROJECT_LABEL "(${test_KIND}) ${test_name}")

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${the_target} PROPERTIES FOLDER "test/settings_model")
endif()


add_test(NAME ${the_target} COMMAND $<TARGET_FILE:${the_target}>)
