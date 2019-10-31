include_directories(${CMAKE_SOURCE_DIR}/third_party)

add_library(libprocess ${LIB_TYPE}
            Process.cpp
            Process.h
            MultiProcess.cpp
            MultiProcess.h
            ExternalProcess.cpp
            ExternalProcess.h
            ProcessConcurrent.cpp
            ProcessConcurrent.h
            features/FeatureExtractorProcess.cpp
            features/FeatureExtractorProcess.h
            preprocess/ImagePreprocess.cpp
            preprocess/ImagePreprocess.h
            Matching/MatchingProcess.cpp
            Matching/MatchingProcess.h
           )

set_property(TARGET libprocess PROPERTY FOLDER "lib")

#if(BUILD_SHARED_LIBS)
#    
#  install(TARGETS libgraphos
#          RUNTIME DESTINATION bin
#          LIBRARY DESTINATION lib
#          ARCHIVE DESTINATION lib)
#	
#  set_target_properties(libgraphos PROPERTIES
#                        DEFINE_SYMBOL PHOTOMATCH_EXPORTS)
#	target_link_libraries(libprocess .... ) 
#else()
  install(TARGETS libprocess 
          LIBRARY DESTINATION lib 
          ARCHIVE DESTINATION lib)
#endif()

install(DIRECTORY .
        DESTINATION include/photomatch/process
        FILES_MATCHING PATTERN "*.h")
