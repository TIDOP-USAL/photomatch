
unset(PIXKIT_FOUND)

SET(PIXKIT_DIR "" CACHE PATH "Root folder of PIXKIT dependency")

list(APPEND PIXKIT_INCLUDE_DIRS
     ${PIXKIT_DIR}/include
     /opt/local/include
     /opt/local/include/ufsparse # Mac OS X
     /usr/local/homebrew/include # Mac OS X
     /usr/local/include
     /usr/include)
     
list(APPEND PIXKIT_LIBRARY_DIRS
     ${PIXKIT_DIR}/lib
     ${PIXKIT_DIR}/lib/x64
     /opt/local/lib
     /opt/local/lib/ufsparse # Mac OS X
     /usr/local/homebrew/lib # Mac OS X
     /usr/local/lib
     /usr/lib)
     
include(FindPackageHandleStandardArgs)

# Include
find_path(PIXKIT_INCLUDE_DIR
          NAMES pixkit-cv.hpp
          PATHS ${PIXKIT_INCLUDE_DIRS}
          PATH_SUFFIXES pixkit
)

################################### 
# pixkit_cv
find_library(PIXKIT_CV_LIBRARY
             NAMES pixkit_cv pixkit_cv052
             PATHS ${PIXKIT_LIBRARY_DIRS}
)
find_library(PIXKIT_CV_LIBRARY_DEBUG
             NAMES pixkit_cvd pixkit_cv052d
             PATHS ${PIXKIT_LIBRARY_DIRS}
)

find_package_handle_standard_args(PIXKIT_CV
                                  FOUND_VAR PIXKIT_CV_FOUND
                                  REQUIRED_VARS
                                    PIXKIT_CV_LIBRARY
                                    PIXKIT_CV_LIBRARY_DEBUG
                                    PIXKIT_INCLUDE_DIR
)

if(PIXKIT_CV_FOUND)
  set(PIXKIT_INCLUDE_DIRS ${PIXKIT_CV_INCLUDE_DIR})
  set(PIXKIT_CV_LIBRARIES debug ${PIXKIT_CV_LIBRARY_DEBUG} optimized ${PIXKIT_CV_LIBRARY})
  set(PIXKIT_CV_DEFINITIONS ${PIXKIT_CV_CFLAGS_OTHER})
endif()

################################### 


###################################
# PIXKIT_FILE
find_library(PIXKIT_FILE_LIBRARY
             NAMES pixkit_file pixkit_file052
             PATHS ${PIXKIT_LIBRARY_DIRS}
)
find_library(PIXKIT_FILE_LIBRARY_DEBUG
             NAMES pixkit_filed pixkit_file052d
             PATHS ${PIXKIT_LIBRARY_DIRS}
)

find_package_handle_standard_args(PIXKIT_FILE
                                  FOUND_VAR PIXKIT_FILE_FOUND
                                  REQUIRED_VARS
                                    PIXKIT_FILE_LIBRARY
                                    PIXKIT_FILE_LIBRARY_DEBUG
                                    PIXKIT_INCLUDE_DIR
)

if(PIXKIT_FILE_FOUND)
  set(PIXKIT_FILE_LIBRARIES debug ${PIXKIT_FILE_LIBRARY_DEBUG} optimized ${PIXKIT_FILE_LIBRARY})
  set(PIXKIT_FILE_DEFINITIONS ${PIXKIT_FILE_CFLAGS_OTHER})
endif()
################################### 


###################################  
# PIXKIT_IMAGE
find_library(PIXKIT_IMAGE_LIBRARY
             NAMES pixkit_image pixkit_image052
             PATHS ${PIXKIT_LIBRARY_DIRS}
)   
find_library(PIXKIT_IMAGE_LIBRARY_DEBUG
             NAMES pixkit_imaged pixkit_image052d
             PATHS ${PIXKIT_LIBRARY_DIRS}
)   

find_package_handle_standard_args(PIXKIT_IMAGE
                                  FOUND_VAR PIXKIT_IMAGE_FOUND
                                  REQUIRED_VARS
                                    PIXKIT_IMAGE_LIBRARY
                                    PIXKIT_IMAGE_LIBRARY_DEBUG
                                    PIXKIT_INCLUDE_DIR
)

if(PIXKIT_IMAGE_FOUND)
  set(PIXKIT_IMAGE_LIBRARIES debug ${PIXKIT_IMAGE_LIBRARY_DEBUG} optimized ${PIXKIT_IMAGE_LIBRARY} )
  set(PIXKIT_IMAGE_DEFINITIONS ${PIXKIT_IMAGE_CFLAGS_OTHER})
endif()
################################### 


###################################
# PIXKIT_ML
find_library(PIXKIT_ML_LIBRARY
             NAMES pixkit_ml pixkit_ml052
             PATHS ${PIXKIT_LIBRARY_DIRS}
)  
find_library(PIXKIT_ML_LIBRARY_DEBUG
             NAMES pixkit_mld pixkit_ml052d
             PATHS ${PIXKIT_LIBRARY_DIRS}
)  

find_package_handle_standard_args(PIXKIT_ML
                                  FOUND_VAR PIXKIT_ML_FOUND
                                  REQUIRED_VARS
                                    PIXKIT_ML_LIBRARY
                                    PIXKIT_ML_LIBRARY_DEBUG
                                    PIXKIT_INCLUDE_DIR
)

if(PIXKIT_ML_FOUND)
  set(PIXKIT_ML_LIBRARIES debug ${PIXKIT_ML_LIBRARY_DEBUG} optimized  ${PIXKIT_ML_LIBRARY})
  set(PIXKIT_ML_DEFINITIONS ${PIXKIT_ML_CFLAGS_OTHER})
endif()
################################### 
 
###################################
# PIXKIT_TIMER
find_library(PIXKIT_TIMER_LIBRARY
             NAMES pixkit_timer pixkit_timer052
             PATHS ${PIXKIT_LIBRARY_DIRS}
)  
find_library(PIXKIT_TIMER_LIBRARY_DEBUG
             NAMES pixkit_timerd pixkit_timer052d
             PATHS ${PIXKIT_LIBRARY_DIRS}
)  

find_package_handle_standard_args(PIXKIT_TIMER
                                  FOUND_VAR PIXKIT_TIMER_FOUND
                                  REQUIRED_VARS
                                    PIXKIT_TIMER_LIBRARY
                                    PIXKIT_TIMER_LIBRARY_DEBUG
                                    PIXKIT_INCLUDE_DIR
)

if(PIXKIT_TIMER_FOUND)
  set(PIXKIT_TIMER_LIBRARIES debug ${PIXKIT_TIMER_LIBRARY_DEBUG} optimized ${PIXKIT_TIMER_LIBRARY})
  set(PIXKIT_TIMER_DEFINITIONS ${PIXKIT_TIMER_CFLAGS_OTHER})
endif()
################################### 


list(APPEND PIXKIT_INCLUDE_DIRS ${PIXKIT_INCLUDE_DIR})  

list(APPEND PIXKIT_LIBRARIES
     ${PIXKIT_CV_LIBRARIES}
     ${PIXKIT_FILE_LIBRARIES}
     ${PIXKIT_IMAGE_LIBRARIES}
     ${PIXKIT_ML_LIBRARIES}
     ${PIXKIT_TIMER_LIBRARIES})    
    
if (PIXKIT_INCLUDE_DIRS AND PIXKIT_LIBRARIES)
    set(PIXKIT_FOUND TRUE)
    message(STATUS "Found PixKit")
    message(STATUS "  Include   : ${PIXKIT_INCLUDE_DIR}")
    message(STATUS "  Libraries : ${PIXKIT_CV_LIBRARY} ${PIXKIT_FILE_LIBRARY} ${PIXKIT_IMAGE_LIBRARY} ${PIXKIT_ML_LIBRARY} ${PIXKIT_TIMER_LIBRARY}")
else()
    if(PIXKIT_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find PixKit")
    endif()
endif()
