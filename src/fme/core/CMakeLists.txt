include_directories(${CMAKE_SOURCE_DIR}/third_party)

add_library(libcore ${LIB_TYPE}
            project.cpp
            project.h
            image.cpp
            image.h
            settings.cpp
            settings.h
            session.cpp
            session.h
            features.h
            preprocess.h
            utils.cpp
            utils.h)

set_property(TARGET libcore PROPERTY FOLDER "lib")

#if(BUILD_SHARED_LIBS)
#    
#  install(TARGETS libgraphos
#          RUNTIME DESTINATION bin
#          LIBRARY DESTINATION lib
#          ARCHIVE DESTINATION lib)
#	
#  set_target_properties(libgraphos PROPERTIES
#                        DEFINE_SYMBOL FME_EXPORTS)
#	target_link_libraries(libprocess .... ) 
#else()
  install(TARGETS libcore
          LIBRARY DESTINATION lib 
          ARCHIVE DESTINATION lib)
#endif()

install(DIRECTORY .
        DESTINATION include/fme/core
        FILES_MATCHING PATTERN "*.h")
