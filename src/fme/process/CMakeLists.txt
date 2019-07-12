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
            ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp
            ImagePreprocessing/ContrastPreservingDecolorization__Process.h
            ImagePreprocessing/WallisFilter_Process.cpp
            ImagePreprocessing/WallisFilter_Process.h
            ImagePreprocessing/Downsample_Process.cpp
            ImagePreprocessing/Downsample_Process.h
            ImagePreprocessing/LCE_BSESCS2014_Process.cpp
            ImagePreprocessing/LCE_BSESCS2014_Process.h
            ImagePreprocessing/RajuNair2014_Process.cpp
            ImagePreprocessing/RajuNair2014_Process.h
            ImagePreprocessing/Lal2014_Process.cpp
            ImagePreprocessing/Lal2014_Process.h
            ImagePreprocessing/MSRCP2014_Process.cpp
            ImagePreprocessing/MSRCP2014_Process.h
            ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp
            ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h
            ImagePreprocessing/POHE2013_Process.cpp
            ImagePreprocessing/POHE2013_Process.h
            ImagePreprocessing/Kimori2013_Process.cpp
            ImagePreprocessing/Kimori2013_Process.h
            ImagePreprocessing/CelikTjahjadi2012_Process.cpp
            ImagePreprocessing/CelikTjahjadi2012_Process.h
            ImagePreprocessing/LiuJinChenLiuLi2011_Process.cpp
            ImagePreprocessing/LiuJinChenLiuLi2011_Process.h
            ImagePreprocessing/Sundarami2011_Process.cpp
            ImagePreprocessing/Sundarami2011_Process.h
            ImagePreprocessing/MaryKim2008_Process.cpp
            ImagePreprocessing/MaryKim2008_Process.h
            ImagePreprocessing/WadudKabirDewanChae2007_Process.cpp
            ImagePreprocessing/WadudKabirDewanChae2007_Process.h
            ImagePreprocessing/FaheProcess.cpp
            ImagePreprocessing/FaheProcess.h
            ImagePreprocessing/LambertiMontrucchioSanna2006_Process.cpp
            ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h
            ImagePreprocessing/YuBajaj2004_Process.cpp
            ImagePreprocessing/YuBajaj2004_Process.h
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
