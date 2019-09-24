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
            #ImagePreprocessing/AcebsfProcess.cpp
            #ImagePreprocessing/AcebsfProcess.h
            #ImagePreprocessing/ClaheProcess.cpp
            #ImagePreprocessing/ClaheProcess.h
            #ImagePreprocessing/CmbfheProcess.cpp
            #ImagePreprocessing/CmbfheProcess.h
            #ImagePreprocessing/DheProcess.cpp
            #ImagePreprocessing/DheProcess.h
            #ImagePreprocessing/FaheProcess.cpp
            #ImagePreprocessing/FaheProcess.h
            #ImagePreprocessing/HmclaheProcess.cpp
            #ImagePreprocessing/HmclaheProcess.h
            #ImagePreprocessing/LceBsescsProcess.cpp
            #ImagePreprocessing/LceBsescsProcess.h
            #ImagePreprocessing/MsrcpProcess.cpp
            #ImagePreprocessing/MsrcpProcess.h
            #ImagePreprocessing/NoshpProcess.cpp
            #ImagePreprocessing/NoshpProcess.h
            #ImagePreprocessing/PoheProcess.cpp
            #ImagePreprocessing/PoheProcess.h
            #ImagePreprocessing/RswheProcess.cpp
            #ImagePreprocessing/RswheProcess.h
            #ImagePreprocessing/WallisProcess.cpp
            #ImagePreprocessing/WallisProcess.h
            #ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp
            #ImagePreprocessing/ContrastPreservingDecolorization__Process.h
            #ImagePreprocessing/Downsample_Process.cpp
            #ImagePreprocessing/Downsample_Process.h
            #ImagePreprocessing/RajuNair2014_Process.cpp
            #ImagePreprocessing/RajuNair2014_Process.h
            #ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp
            #ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h
            #ImagePreprocessing/Kimori2013_Process.cpp
            #ImagePreprocessing/Kimori2013_Process.h
            #ImagePreprocessing/CelikTjahjadi2012_Process.cpp
            #ImagePreprocessing/CelikTjahjadi2012_Process.h
            #ImagePreprocessing/YuBajaj2004_Process.cpp
            #ImagePreprocessing/YuBajaj2004_Process.h
            features/FeatureExtractorProcess.cpp
            features/FeatureExtractorProcess.h
            preprocess/ImagePreprocess.cpp
            preprocess/ImagePreprocess.h
            #Matching/BFMatcherProcess.cpp
            #Matching/BFMatcherProcess.h
            #Matching/RobustMatcherRefinementProcess.cpp
            #Matching/RobustMatcherRefinementProcess.h
            #Matching/FLANNMatcherProcess.cpp
            #Matching/FLANNMatcherProcess.h
            #Matching/WriteMatchesToAperoProcess.cpp
            #Matching/WriteMatchesToAperoProcess.h
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
#                        DEFINE_SYMBOL FME_EXPORTS)
#	target_link_libraries(libprocess .... ) 
#else()
  install(TARGETS libprocess 
          LIBRARY DESTINATION lib 
          ARCHIVE DESTINATION lib)
#endif()

install(DIRECTORY .
        DESTINATION include/fme/process
        FILES_MATCHING PATTERN "*.h")
