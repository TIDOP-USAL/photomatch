set(test_filename tst_projectmodel.cpp)
get_filename_component(test_name ${test_filename} NAME_WE)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/third_party)

set(test_kind test)
set(test_KIND TEST)

set(the_target "${test_kind}_${test_name}")
add_executable(${the_target}
    ${test_filename}
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/ProjectModel.cpp
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/ProjectModel.h
    ${CMAKE_SOURCE_DIR}/src/photomatch/ui/mvp.h
    )

target_link_libraries(${the_target} PRIVATE
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Test
                      tl_core
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

set_property(TARGET ${the_target} PROPERTY FOLDER "test/project_model")

set_target_properties(${the_target} PROPERTIES
  OUTPUT_NAME ${the_target}
  PROJECT_LABEL "(${test_KIND}) ${test_name}")

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${the_target} PROPERTIES FOLDER "test/project_model")
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
