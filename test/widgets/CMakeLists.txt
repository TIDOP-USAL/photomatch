MACRO(DEFINE_TEST_WIDGETS name srcs)

    include_directories(${CMAKE_SOURCE_DIR}/src)

    set(test_kind test)
    set(test_KIND TEST)
    
    set(the_target "${test_kind}_${name}")
    add_executable(${the_target} ${srcs})
    
    target_link_libraries(${the_target} PRIVATE Qt5::Core Qt5::Widgets Qt5::Test libwidgets)

    set_property(TARGET ${the_target} PROPERTY FOLDER "test/widgets")
    
    set_target_properties(${the_target} PROPERTIES
      OUTPUT_NAME ${the_target}
      PROJECT_LABEL "(${test_KIND}) ${name}")

    if(ENABLE_SOLUTION_FOLDERS)
      set_target_properties(${the_target} PROPERTIES FOLDER "test/widgets")
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

add_subdirectory(acebsfwidget)
add_subdirectory(acebsfwidget_signals)
add_subdirectory(agastwidget)
add_subdirectory(agastwidget_signals)
add_subdirectory(akazewidget)
add_subdirectory(akazewidget_signals)
add_subdirectory(briefwidget)
add_subdirectory(briefwidget_signals)
add_subdirectory(briskwidget)
add_subdirectory(briskwidget_signals)
add_subdirectory(clahewidget)
add_subdirectory(clahewidget_signals)
add_subdirectory(cmbfhewidget)
add_subdirectory(cmbfhewidget_signals)
add_subdirectory(daisywidget)
add_subdirectory(daisywidget_signals)
add_subdirectory(descriptormatcherwidget)
add_subdirectory(descriptormatcherwidget_signals)
add_subdirectory(fahewidget)
add_subdirectory(fahewidget_signals)
add_subdirectory(fastwidget)
add_subdirectory(fastwidget_signals)
add_subdirectory(freakwidget)
add_subdirectory(freakwidget_signals)
add_subdirectory(gfttwidget)
add_subdirectory(gfttwidget_signals)
add_subdirectory(hmclahewidget)
add_subdirectory(hmclahewidget_signals)
add_subdirectory(hogwidget)
add_subdirectory(hogwidget_signals)
add_subdirectory(kazewidget)
add_subdirectory(kazewidget_signals)
add_subdirectory(latchwidget)
add_subdirectory(latchwidget_signals)
add_subdirectory(lcebsescswidget)
add_subdirectory(lcebsescswidget_signals)
add_subdirectory(lucidwidget)
add_subdirectory(lucidwidget_signals)
add_subdirectory(msdwidget)
add_subdirectory(msdwidget_signals)
add_subdirectory(mserwidget)
add_subdirectory(mserwidget_signals)
add_subdirectory(msrcpwidget)
add_subdirectory(msrcpwidget_signals)
add_subdirectory(noshpwidget)
add_subdirectory(noshpwidget_signals)
add_subdirectory(orbwidget)
add_subdirectory(orbwidget_signals)
add_subdirectory(pohewidget)
add_subdirectory(pohewidget_signals)
add_subdirectory(siftwidget)
add_subdirectory(siftwidget_signals)
add_subdirectory(starwidget)
add_subdirectory(starwidget_signals)
add_subdirectory(surfwidget)
add_subdirectory(surfwidget_signals)
add_subdirectory(walliswidget)
add_subdirectory(walliswidget_signals)




