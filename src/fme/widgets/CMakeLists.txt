add_library(libwidgets ${LIB_TYPE}
            AgastWidget.cpp
            AgastWidget.h
            AkazeWidget.cpp
            AkazeWidget.h
            BriskWidget.cpp
            BriskWidget.h
            FastWidget.cpp
            FastWidget.h
            GfttWidget.cpp
            GfttWidget.h
            KazeWidget.cpp
            KazeWidget.h
            MsdWidget.cpp
            MsdWidget.h
            MserWidget.cpp
            MserWidget.h
            OrbWidget.cpp
            OrbWidget.h
            SiftWidget.cpp
            SiftWidget.h
            SurfWidget.cpp
            SurfWidget.h)

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