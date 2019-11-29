##DEPENDENCIES

### [pixkit](https://github.com/estebanrdo/pixkit)


### [OpenCV](https://github.com/opencv/opencv)

CMAKE:
- OPENCV_EXTRA_MODULES_PATH
- OPENCV_ENABLE_NONFREE (for SIFT and SURF)

### [Boost](https://www.boost.org)

https://sourceforge.net/projects/boost/files/boost-binaries/

Microsoft Visual Studio 2013 - msvc-12.0 - Update 5
Microsoft Visual Studio 2015 - msvc-14.0 - Update 3
Microsoft Visual Studio 2017 - msvc-14.1 - VS 15.9.12
Microsoft Visual Studio 2019 - msvc-14.2 - VS 16.1.1

#CMAKE


#QMAKE

Crear un fichero llamado FeatureMatchingEvaluation.pri e incluirlo en el mismo directorio que FeatureMatchingEvaluation.pro. Este fichero tiene que incluir las dependencias como se muestra a continuación:


INCLUDEPATH +=  ../../libs/opencv/3.3.1/include \
                ../../libs/boost/1.61.0 \
                ../../libs/PixKit/vc14/include
                
                
LIBS += -L$$PWD/../../Libs/opencv/3.3.1/x64/vc14/bin
LIBS += -L$$PWD/../../libs/opencv/3.3.1/x64/vc14/lib
LIBS += -L$$PWD/../../libs/boost/1.61.0/lib64-msvc-14.0
LIBS += -L$$PWD/../../libs/PixKit/vc14/lib/x64

debug{

      LIBS += -lpixkit_cv052d -lpixkit_file052d -lpixkit_image052d -lpixkit_ml052d -lpixkit_timer052d
      LIBS += -lopencv_photo331d -lopencv_xfeatures2d331d  -lopencv_core331d -lopencv_highgui331d -lopencv_imgproc331d -lopencv_imgcodecs331d -lopencv_video331d -lopencv_videostab331d -lopencv_videoio331d -lopencv_calib3d331d -lopencv_features2d331d  -lopencv_flann331d -lopencv_objdetect331d

}else{

      LIBS += -lpixkit_cv052 -lpixkit_file052 -lpixkit_image052 -lpixkit_ml052 -lpixkit_timer052
      LIBS += -lopencv_photo331 -lopencv_xfeatures2d331 -lopencv_core331 -lopencv_highgui331 -lopencv_imgproc331 -lopencv_imgcodecs331 -lopencv_video331 -lopencv_videostab331 -lopencv_videoio331 -lopencv_calib3d331 -lopencv_features2d331  -lopencv_flann331 -lopencv_objdetect331

}