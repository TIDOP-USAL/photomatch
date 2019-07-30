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
            brief/BRIEF_KPDescProcess.cpp
            brief/BRIEF_KPDescProcess.h
            brisk/BRISK_KPDescProcess.cpp
            brisk/BRISK_KPDescProcess.h
            brisk/BRISK_KPDetProcess.cpp
            brisk/BRISK_KPDetProcess.h
            daisy/DAISY_KPDescProcess.cpp
            daisy/DAISY_KPDescProcess.h
            fast/FAST_KPDetProcess.cpp
            fast/FAST_KPDetProcess.h
            freak/FREAK_KPDescProcess.cpp
            freak/FREAK_KPDescProcess.h
            gftt/GFTT_KPDetProcess.cpp
            gftt/GFTT_KPDetProcess.h
            hog/HOG_KPDescProcess.cpp
            hog/HOG_KPDescProcess.h
            latch/LATCH_KPDescProcess.cpp
            latch/LATCH_KPDescProcess.h
            lss/LSS_KPDescProcess.cpp
            lss/LSS_KPDescProcess.h
            lss/lss.cpp
            lss/lss.h
            lucid/LUCID_KPDescProcess.cpp
            lucid/LUCID_KPDescProcess.h
            msd/MSD_KPDetProcess.cpp
            msd/MSD_KPDetProcess.h
            msd/MSD.cpp
            msd/MSD.h
            msd/MSDImgPyramid.cpp
            msd/MSDImgPyramid.h
            mser/MSER_KPDetProcess.cpp
            mser/MSER_KPDetProcess.h
            mtm/mtm.cpp
            mtm/mtm.h
            mtm/MTM_KPDescProcess.cpp
            mtm/MTM_KPDescProcess.h
            mutualinformation/MutualInformation_KPDescProcess.cpp
            mutualinformation/MutualInformation_KPDescProcess.h
            orb/ORB_KPDetProcess.cpp
            orb/ORB_KPDetProcess.h
            orb/ORB_KPDescProcess.cpp
            orb/ORB_KPDescProcess.h
            sift/SIFT_KPDescProcess.cpp
            sift/SIFT_KPDescProcess.h
            sift/SIFT_KPDetProcess.cpp
            sift/SIFT_KPDetProcess.h
            surf/SURF_KPDetProcess.cpp
            surf/SURF_KPDetProcess.h
            surf/SUFT_KPDescProcess.cpp
            surf/SUFT_KPDescProcess.h
            ImagePreprocessing/AcebsfProcess.cpp
            ImagePreprocessing/AcebsfProcess.h
            ImagePreprocessing/ClaheProcess.cpp
            ImagePreprocessing/ClaheProcess.h
            ImagePreprocessing/CmbfheProcess.cpp
            ImagePreprocessing/CmbfheProcess.h
            ImagePreprocessing/DheProcess.cpp
            ImagePreprocessing/DheProcess.h
            ImagePreprocessing/FaheProcess.cpp
            ImagePreprocessing/FaheProcess.h
            ImagePreprocessing/HmclaheProcess.cpp
            ImagePreprocessing/HmclaheProcess.h
            ImagePreprocessing/LceBsescsProcess.cpp
            ImagePreprocessing/LceBsescsProcess.h
            ImagePreprocessing/MsrcpProcess.cpp
            ImagePreprocessing/MsrcpProcess.h
            ImagePreprocessing/NoshpProcess.cpp
            ImagePreprocessing/NoshpProcess.h
            ImagePreprocessing/PoheProcess.cpp
            ImagePreprocessing/PoheProcess.h      
            ImagePreprocessing/RswheProcess.cpp
            ImagePreprocessing/RswheProcess.h
            ImagePreprocessing/WallisProcess.cpp
            ImagePreprocessing/WallisProcess.h            
            ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp
            ImagePreprocessing/ContrastPreservingDecolorization__Process.h
            ImagePreprocessing/Downsample_Process.cpp
            ImagePreprocessing/Downsample_Process.h
            ImagePreprocessing/RajuNair2014_Process.cpp
            ImagePreprocessing/RajuNair2014_Process.h
            ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp
            ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h
            ImagePreprocessing/Kimori2013_Process.cpp
            ImagePreprocessing/Kimori2013_Process.h
            ImagePreprocessing/CelikTjahjadi2012_Process.cpp
            ImagePreprocessing/CelikTjahjadi2012_Process.h
            ImagePreprocessing/YuBajaj2004_Process.cpp
            ImagePreprocessing/YuBajaj2004_Process.h
            features/FeatureExtractorProcess.cpp
            features/FeatureExtractorProcess.h
            Matching/BFMatcherProcess.cpp
            Matching/BFMatcherProcess.h
            Matching/RobustMatcherRefinementProcess.cpp
            Matching/RobustMatcherRefinementProcess.h
            Matching/FLANNMatcherProcess.cpp
            Matching/FLANNMatcherProcess.h
            Matching/WriteMatchesToAperoProcess.cpp
            Matching/WriteMatchesToAperoProcess.h
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
