MACRO(DEFINE_TEST_PROCESS name srcs)

    include_directories(${CMAKE_SOURCE_DIR}/src)

    set(test_kind test)
    set(test_KIND TEST)
    
    set(the_target "${test_kind}_${name}")
    add_executable(${the_target} ${srcs})
    
    target_link_libraries(${the_target} PRIVATE 
                          Qt5::Core 
                          Qt5::Widgets 
                          Qt5::Test 
                          libprocess
                          ${OpenCV_LIBS}
                          ${PIXKIT_LIBRARIES})

    set_property(TARGET ${the_target} PROPERTY FOLDER "test/process")
    
    set_target_properties(${the_target} PROPERTIES
      OUTPUT_NAME ${the_target}
      PROJECT_LABEL "(${test_KIND}) ${name}")

    if(ENABLE_SOLUTION_FOLDERS)
      set_target_properties(${the_target} PROPERTIES FOLDER "test/process")
    endif()
  
    add_test(NAME ${the_target} COMMAND $<TARGET_FILE:${the_target}>)
	
ENDMACRO()


add_subdirectory(faheprocess)


