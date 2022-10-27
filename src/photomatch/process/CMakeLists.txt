include_directories(${CMAKE_SOURCE_DIR}/third_party)

project(Process LANGUAGES CXX)

add_library(${PROJECT_NAME} ${LIB_TYPE}
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
            Matching/PassPointsGroupingProcess.cpp
            Matching/PassPointsGroupingProcess.h )

add_library(PhotoMatch::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
                      TidopLib::Core)

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      FOLDER "lib"
                      OUTPUT_NAME "libprocess")


install(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)

install(DIRECTORY .
        DESTINATION include/photomatch/process
        FILES_MATCHING PATTERN "*.h")
