include_directories(${CMAKE_SOURCE_DIR}/third_party)

add_library(libcore ${LIB_TYPE}
            ${CMAKE_SOURCE_DIR}/third_party/msd/MSD.h
            ${CMAKE_SOURCE_DIR}/third_party/msd/MSD.cpp
            ${CMAKE_SOURCE_DIR}/third_party/msd/MSDImgPyramid.h
            ${CMAKE_SOURCE_DIR}/third_party/msd/MSDImgPyramid.cpp
            ${CMAKE_SOURCE_DIR}/third_party/lss/lss.cpp
            ${CMAKE_SOURCE_DIR}/third_party/lss/lss.h
            project.cpp
            project.h
            image.cpp
            image.h
            settings.cpp
            settings.h
            session.cpp
            session.h
            features/features.h
            features/features.cpp
            features/agast.h
            features/agast.cpp
            features/akaze.h
            features/akaze.cpp
            features/boost.h
            features/boost.cpp
            features/brief.h
            features/brief.cpp
            features/brisk.h
            features/brisk.cpp
            features/daisy.h
            features/daisy.cpp
            features/fast.h
            features/fast.cpp
            features/freak.h
            features/freak.cpp
            features/gftt.h
            features/gftt.cpp
            features/hog.h
            features/hog.cpp
            features/latch.h
            features/latch.cpp
            features/lucid.h
            features/lucid.cpp
            features/lss.h
            features/lss.cpp
            features/kaze.h
            features/kaze.cpp
            features/msd.h
            features/msd.cpp
            features/mser.h
            features/mser.cpp
            features/sift.h
            features/sift.cpp
            features/star.h
            features/star.cpp            
            features/surf.h
            features/surf.cpp
            features/orb.h
            features/orb.cpp
            features/vgg.h
            features/vgg.cpp
            features/matcher.cpp
            features/matcher.h
            features/evaluation.h
            features/groundtruth.cpp
            features/groundtruth.h
            features/keypointsfilter.h
            features/keypointsfilter.cpp
            preprocess/preprocess.h
            #preprocess/downsample.cpp
            #preprocess/downsample.h
            preprocess/acebsf.cpp
            preprocess/acebsf.h
            preprocess/clahe.cpp
            preprocess/clahe.h
            preprocess/cmbfhe.cpp
            preprocess/cmbfhe.h
            preprocess/decolor.cpp
            preprocess/decolor.h
            preprocess/dhe.cpp
            preprocess/dhe.h
            preprocess/fahe.cpp
            preprocess/fahe.h
            preprocess/hmclahe.cpp
            preprocess/hmclahe.h
            preprocess/lce_bsescs.cpp
            preprocess/lce_bsescs.h
            preprocess/msrcp.cpp
            preprocess/msrcp.h
            preprocess/noshp.cpp
            preprocess/noshp.h
            preprocess/pohe.cpp
            preprocess/pohe.h
            preprocess/rswhe.cpp
            preprocess/rswhe.h
            preprocess/wallis.cpp
            preprocess/wallis.h
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
#                        DEFINE_SYMBOL PHOTOMATCH_EXPORTS)
#	target_link_libraries(libprocess .... ) 
#else()
  install(TARGETS libcore
          LIBRARY DESTINATION lib 
          ARCHIVE DESTINATION lib)
#endif()

install(DIRECTORY .
        DESTINATION include/photomatch/core
        FILES_MATCHING PATTERN "*.h")
