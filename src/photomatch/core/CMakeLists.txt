##########################################################################
#                                                                        #
# Copyright 2016 by Tidop Research Group <daguilera@usal.es>             #
#                                                                        #
# This file is part of PhotoMatch                                        #
#                                                                        #
# PhotoMatch is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# PhotoMatch is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with PhotoMatch. If not, see <http://www.gnu.org/licenses/>.     #
#                                                                        #
# https://spdx.org/licenses/GPL-3.0-or-later.html                        #
#                                                                        #
##########################################################################

include_directories(${CMAKE_SOURCE_DIR}/third_party)

project(Core LANGUAGES CXX)

set(PHOTOMATCH_CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/third_party/msd/MSD.cpp
    ${CMAKE_SOURCE_DIR}/third_party/msd/MSDImgPyramid.cpp
    ${CMAKE_SOURCE_DIR}/third_party/lss/lss.cpp
    project.cpp
    image.cpp
    settings.cpp
    session.cpp
    features/agast.cpp
    features/akaze.cpp
    features/boost.cpp
    features/brief.cpp
    features/brisk.cpp
    features/daisy.cpp
    features/fast.cpp
    features/freak.cpp
    features/gftt.cpp
    features/hog.cpp
    features/latch.cpp
    features/lucid.cpp
    features/lss.cpp
    features/kaze.cpp
    features/msd.cpp
    features/mser.cpp
    features/sift.cpp
    features/star.cpp            
    features/surf.cpp
    features/orb.cpp
    features/vgg.cpp
    features/matchio.cpp
    features/groundtruth.cpp
    features/keypointsfilter.cpp
    features/featio.cpp
    features/flann.cpp
    features/bfmatch.cpp
    features/robustmatch.cpp
    features/gsm.cpp
    preprocess/acebsf.cpp
    preprocess/clahe.cpp
    preprocess/cmbfhe.cpp
    preprocess/decolor.cpp
    preprocess/dhe.cpp
    preprocess/fahe.cpp
    preprocess/hmclahe.cpp
    preprocess/lce_bsescs.cpp
    preprocess/msrcp.cpp
    preprocess/noshp.cpp
    preprocess/pohe.cpp
    preprocess/rswhe.cpp
    preprocess/wallis.cpp
    utils.cpp)


set(PHOTOMATCH_CORE_HEADERS 
    ${CMAKE_SOURCE_DIR}/third_party/msd/MSD.h
    ${CMAKE_SOURCE_DIR}/third_party/msd/MSDImgPyramid.h
    ${CMAKE_SOURCE_DIR}/third_party/lss/lss.h
    project.h
    image.h
    settings.h
    session.h
    features/features.h
    features/agast.h
    features/akaze.h
    features/boost.h
    features/brief.h
    features/brisk.h
    features/daisy.h
    features/fast.h
    features/freak.h
    features/gftt.h
    features/hog.h
    features/latch.h
    features/lucid.h
    features/lss.h
    features/kaze.h
    features/msd.h
    features/mser.h
    features/sift.h
    features/star.h         
    features/surf.h
    features/orb.h
    features/vgg.h
    features/matcher.h
    features/matchio.h
    features/evaluation.h
    features/groundtruth.h
    features/keypointsfilter.h
    features/featio.h
    features/flann.h
    features/bfmatch.h
    features/robustmatch.h
    features/gsm.h
    preprocess/preprocess.h
    preprocess/acebsf.h
    preprocess/clahe.h
    preprocess/cmbfhe.h
    preprocess/decolor.h
    preprocess/dhe.h
    preprocess/fahe.h
    preprocess/hmclahe.h
    preprocess/lce_bsescs.h
    preprocess/msrcp.h
    preprocess/noshp.h
    preprocess/pohe.h
    preprocess/rswhe.h
    preprocess/wallis.h
    utils.h)

add_library(${PROJECT_NAME} ${LIB_TYPE}
            ${PHOTOMATCH_CORE_SOURCES}
            ${PHOTOMATCH_CORE_HEADERS})

add_library(PhotoMatch::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

foreach(_source IN ITEMS ${PHOTOMATCH_CORE_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _group_path "${_source_path}")
    source_group("Source Files\\${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${PHOTOMATCH_CORE_HEADERS})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _group_path "${_source_path}")
    source_group("Header Files\\${_group_path}" FILES "${_source}")
endforeach()

target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${PHOTOMATCH_SOURCE_DIR}/src>
                           $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} PUBLIC
                      TidopLib::Core
                      TidopLib::Geom
                      TidopLib::Img
                      TidopLib::Math
                      ${CUDA_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      FOLDER "lib"
                      OUTPUT_NAME "libcore")

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "lib")


install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)


install(DIRECTORY .
        DESTINATION include/photomatch/core
        FILES_MATCHING PATTERN "*.h")
