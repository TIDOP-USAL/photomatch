# Modulo Core de la librería TIDOP

add_definitions(-DUNICODE)

set(CMAKE_DEBUG_POSTFIX d)

set(TL_MESSAGE_HANDLER YES)
message(STATUS "[TidopLib] Message manager enabled")

configure_file("${PROJECT_SOURCE_DIR}/cmake/config_tl.h.in" "${PROJECT_BINARY_DIR}/config_tl.h")

add_library(tl_core ${LIB_TYPE}
            console.cpp
            console.h
            defs.h
            exception.cpp
            exception.h
            flags.h
            messages.cpp
            messages.h
            log.cpp
            log.h
            utils.cpp
            utils.h
            process.cpp
            process.h
)
  
set_property(TARGET tl_core
             PROPERTY FOLDER "lib")

# Instalación
if(BUILD_SHARED_LIBS)
    install(TARGETS tl_core
            EXPORT "${TARGETS_EXPORT_NAME}"
            RUNTIME DESTINATION ${TL_INSTALL_BINARIES_PREFIX}/bin
            LIBRARY DESTINATION ${TL_INSTALL_BINARIES_PREFIX}/lib
            ARCHIVE DESTINATION ${TL_INSTALL_BINARIES_PREFIX}/lib)
	
    set_target_properties(tl_core PROPERTIES
                          DEFINE_SYMBOL TIDOPLIB_EXPORTS)
						  
    target_link_libraries(tl_core ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
    
	if (HAVE_GDAL)
        target_link_libraries(tl_core ${GDAL_LIBRARY})
    endif(HAVE_GDAL)

else()
    install(TARGETS tl_core
            EXPORT "${TARGETS_EXPORT_NAME}"
            LIBRARY DESTINATION ${TL_INSTALL_BINARIES_PREFIX}/lib 
            ARCHIVE DESTINATION ${TL_INSTALL_BINARIES_PREFIX}/lib)
endif()

#target_include_directories(
#    tl_core PUBLIC
#    "$<INSTALL_INTERFACE:include>"
#)

install(DIRECTORY .
        DESTINATION include/tidop/core
        FILES_MATCHING PATTERN "*.h")

install(FILES ${PROJECT_BINARY_DIR}/config_tl.h DESTINATION include)

set(TidopLib_LIBRARIES ${TidopLib_LIBRARIES} tl_core)

