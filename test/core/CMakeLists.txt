MACRO(DEFINE_TEST_CORE name srcs)

    include_directories(${CMAKE_SOURCE_DIR}/src)
    include_directories(${CMAKE_SOURCE_DIR}/third_party)

    set(test_kind test)
    set(test_KIND TEST)

    set(the_target "${test_kind}_${name}")
    add_executable(${the_target} ${srcs})

    target_link_libraries(${the_target} PRIVATE Qt5::Core Qt5::Test libcore)

    set_property(TARGET ${the_target} PROPERTY FOLDER "test/core")

    set_target_properties(${the_target} PROPERTIES
      OUTPUT_NAME ${the_target}
      PROJECT_LABEL "(${test_KIND}) ${name}")

    if(ENABLE_SOLUTION_FOLDERS)
      set_target_properties(${the_target} PROPERTIES FOLDER "test/core")
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

ENDMACRO()

add_subdirectory(image)
add_subdirectory(project)
add_subdirectory(settings)
add_subdirectory(session)
