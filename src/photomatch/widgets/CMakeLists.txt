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

project(Widgets LANGUAGES CXX)

add_library(${PROJECT_NAME} ${LIB_TYPE}
            AcebsfWidget.cpp
            AcebsfWidget.h
            AgastWidget.cpp
            AgastWidget.h
            AkazeWidget.cpp
            AkazeWidget.h
            ASiftWidget.cpp
            ASiftWidget.h
            BoostWidget.cpp
            BoostWidget.h
            BriefWidget.cpp
            BriefWidget.h
            BriskWidget.cpp
            BriskWidget.h
            CLaheWidget.cpp
            CLaheWidget.h
            CmbfheWidget.cpp
            CmbfheWidget.h
            DaisyWidget.cpp
            DaisyWidget.h
            DescriptorMatcherWidget.cpp
            DescriptorMatcherWidget.h
            DecolorWidget.cpp
            DecolorWidget.h
            DheWidget.cpp
            DheWidget.h
            FaheWidget.cpp
            FaheWidget.h
            FastWidget.cpp
            FastWidget.h
            PhotoMatchWidget.h
            FreakWidget.cpp
            FreakWidget.h
            GfttWidget.cpp
            GfttWidget.h
            HmclaheWidget.cpp
            HmclaheWidget.h
            HogWidget.cpp
            HogWidget.h
            KazeWidget.cpp
            KazeWidget.h
            LatchWidget.cpp
            LatchWidget.h
            LceBsescsWidget.cpp
            LceBsescsWidget.h            
            LucidWidget.cpp
            LucidWidget.h
            LssWidget.cpp
            LssWidget.h
            MsdWidget.cpp
            MsdWidget.h
            MserWidget.cpp
            MserWidget.h
            MsrcpWidget.cpp
            MsrcpWidget.h
            NoshpWidget.cpp
            NoshpWidget.h
            OrbWidget.cpp
            OrbWidget.h
            PoheWidget.cpp
            PoheWidget.h
            RswheWidget.cpp
            RswheWidget.h
            SiftWidget.cpp
            SiftWidget.h
            StarWidget.cpp
            StarWidget.h
            SurfWidget.cpp
            SurfWidget.h
            WallisWidget.cpp
            WallisWidget.h
            ThumbnailsWidget.cpp
            ThumbnailsWidget.h
            LogWidget.cpp
            LogWidget.h
            VggWidget.cpp
            VggWidget.h
            KeypointsFilterWidget.cpp
            KeypointsFilterWidget.h
            StartPageWidget.cpp
            StartPageWidget.h)

add_library(PhotoMatch::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME} PUBLIC
                      TidopLib::Core
                      TidopLib::Img)

set_target_properties(${PROJECT_NAME} PROPERTIES 
                      FOLDER "lib"
                      OUTPUT_NAME "libwidgets")

install(TARGETS ${PROJECT_NAME} 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)

install(DIRECTORY .
        DESTINATION include/photomatch/widgets
        FILES_MATCHING PATTERN "*.h")
