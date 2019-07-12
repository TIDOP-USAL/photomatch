add_library(libwidgets ${LIB_TYPE}
            AcebsfWidget.cpp
            AcebsfWidget.h
            AgastWidget.cpp
            AgastWidget.h
            AkazeWidget.cpp
            AkazeWidget.h
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
            DheWidget.cpp
            DheWidget.h
            FaheWidget.cpp
            FaheWidget.h
            FastWidget.cpp
            FastWidget.h
            FmeWidget.h
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
            ThumbnailsWidget.h)

set_property(TARGET libwidgets PROPERTY FOLDER "lib")

#if(BUILD_SHARED_LIBS)
#    
#  install(TARGETS libgraphos
#          RUNTIME DESTINATION bin
#          LIBRARY DESTINATION lib
#          ARCHIVE DESTINATION lib)
#	
#  set_target_properties(libgraphos PROPERTIES
#                        DEFINE_SYMBOL FME_EXPORTS)
#	target_link_libraries(libwidgets .... ) 
#else()
  install(TARGETS libwidgets 
          LIBRARY DESTINATION lib 
          ARCHIVE DESTINATION lib)
#endif()

install(DIRECTORY .
        DESTINATION include/fme/widgets
        FILES_MATCHING PATTERN "*.h")
