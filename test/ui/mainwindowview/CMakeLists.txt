include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

set(test_filename tst_mainwindowview.cpp)
get_filename_component(test_name ${test_filename} NAME_WE)

set(test_kind test)
set(test_KIND TEST)

set(the_target "${test_kind}_${test_name}")
add_executable(${the_target}
    ${test_filename}
    ${CMAKE_SOURCE_DIR}/src/fme/ui/MainWindowView.cpp
    ${CMAKE_SOURCE_DIR}/src/fme/ui/MainWindowView.h
    ${CMAKE_SOURCE_DIR}/src/fme/ui/MainWindowView.ui
    )

target_link_libraries(${the_target} PRIVATE
                      tl_core
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Test
                      Qt5::Concurrent
                      libcore
                      libwidgets
                      ${OpenCV_LIBS})

target_link_libraries(${the_target} PRIVATE ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})


set_property(TARGET ${the_target} PROPERTY FOLDER "test/mainwindowview")

set_target_properties(${the_target} PROPERTIES
  OUTPUT_NAME ${the_target}
  PROJECT_LABEL "(${test_KIND}) ${test_name}")

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${the_target} PROPERTIES FOLDER "test/mainwindowview")
endif()

#if(WIN32)
#  if (MSVC AND NOT BUILD_SHARED_LIBS)
#    set_target_properties(${the_target} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:atlthunk.lib /NODEFAULTLIB:atlsd.lib /DEBUG")
#  endif()
#  install(TARGETS ${the_target}
#          RUNTIME DESTINATION "${PROJECT_BINARY_DIR}" COMPONENT test)
#endif()


#if (BUILD_SHARED_LIBS)
#  set_target_properties(${the_target}
#    PROPERTIES
#    COMPILE_DEFINITIONS "GTEST_LINKED_AS_SHARED_LIBRARY=1")
#endif()

add_test(NAME ${the_target} COMMAND $<TARGET_FILE:${the_target}>)
