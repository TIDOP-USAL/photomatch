add_library(libwidgets ${LIB_TYPE}
            AgastWidget.cpp
            AgastWidget.h
            AkazeWidget.cpp
            AkazeWidget.h
            BriefWidget.cpp
            BriefWidget.h
            BriskWidget.cpp
            BriskWidget.h
            CLAHEWidget.cpp
            CLAHEWidget.h
            DaisyWidget.cpp
            DaisyWidget.h
            DescriptorMatcherWidget.cpp
            DescriptorMatcherWidget.h
            FastWidget.cpp
            FastWidget.h
            FreakWidget.cpp
            FreakWidget.h
            GfttWidget.cpp
            GfttWidget.h
            HogWidget.cpp
            HogWidget.h
            KazeWidget.cpp
            KazeWidget.h
            LatchWidget.cpp
            LatchWidget.h
            LucidWidget.cpp
            LucidWidget.h
            MsdWidget.cpp
            MsdWidget.h
            MserWidget.cpp
            MserWidget.h
            OrbWidget.cpp
            OrbWidget.h
            SiftWidget.cpp
            SiftWidget.h
            StarWidget.cpp
            StarWidget.h
            SurfWidget.cpp
            SurfWidget.h
            WallisWidget.cpp
            WallisWidget.h
            LceBsescsWidget.cpp
            LceBsescsWidget.h
            AcebsfWidget.cpp
            AcebsfWidget.h)

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
        DESTINATION include/widgets
        FILES_MATCHING PATTERN "*.h")
