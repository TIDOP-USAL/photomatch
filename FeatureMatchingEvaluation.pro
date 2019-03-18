#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T16:42:53
#
#-------------------------------------------------

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}

# ensure one "debug" or "release" in CONFIG so they can be used as
# conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
    }
CONFIG(release, debug|release) {
        CONFIG -= debug release
        CONFIG += release
}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FeatureMatchingEvaluation
TEMPLATE = app

INCLUDEPATH += ../photo/ \
                ../../Libs/OpenCV_3.3.1_vc14_x64/include \
                ../../Libs/boost_1_61_0_vc14_x64/include \
                ../../Libs/PixKit_vc14_x64/include


SOURCES += main.cpp\
        MainWindowFME.cpp \
    MatchingViewer/MatchigGraphicsView.cpp \
    MatchingViewer/MatchingViewer.cpp \
    ProcessManager/ExternalProcess.cpp \
    ProcessManager/MultiProcess.cpp \
    ProcessManager/Process.cpp \
    ProcessManager/ProcessConcurrent.cpp \
    photo/image.cpp \
    photo/thumbnail.cpp \
    photo/tabshortcuts.cpp \
    photo/tabgeneral.cpp \
    photo/settings.cpp \
    photo/menu.cpp \
    photo/photoviewer.cpp \
    photo/pixmapitem.cpp \
    photo/CrossGraphicItem.cpp \
    photo/crosshairgraphicsitem.cpp \
    MatchingViewer/PWImage.cpp \
    MatchingViewer/Camera.cpp \
    MatchingViewer/CameraModel.cpp \
    MatchingViewer/ExternalOrientation.cpp \
    MatchingViewer/PW2dPoint.cpp \
    MatchingViewer/PWPoint.cpp \
    SIFT/SIFT_KPDetProcess.cpp \
    SIFT/SIFT_KPDescProcess.cpp \
    DependencyInfoWidget.cpp \
    ProgressDialog.cpp \
    MSD/MSD_KPDetProcess.cpp \
    MSD/MSD.cpp \
    MSD/MSDImgPyramid.cpp \
    ORB/ORB_KPDetProcess.cpp \
    SURF/SURF_KPDetProcess.cpp \
    SURF/SUFT_KPDescProcess.cpp \
    HOG/HOG_KPDescProcess.cpp \
    ORB/ORB_KPDescProcess.cpp \
    MutualInformation/MutualInformation_KPDescProcess.cpp \
    MTM/mtm.cpp \
    LSS/lss.cpp \
    MTM/MTM_KPDescProcess.cpp \
    LSS/LSS_KPDescProcess.cpp \
    AboutFME.cpp \
    Matching/BFMatcherProcess.cpp \
    Matching/RobustMatcherRefinementProcess.cpp \
    GrountTruthBuilderProcess.cpp \
    DAISY/DAISY_KPDescProcess.cpp \
    FREAK/FREAK_KPDescProcess.cpp \
    LATCH/LATCH_KPDescProcess.cpp \
    LUCID/LUCID_KPDescProcess.cpp \
    FAST/FAST_KPDetProcess.cpp \
    GFTT/GFTT_KPDetProcess.cpp \
    MSER/MSER_KPDetProcess.cpp \
    BRISK/BRISK_KPDetProcess.cpp \
    BRISK/BRISK_KPDescProcess.cpp \
    BRIEF/BRIEF_KPDescProcess.cpp \
    Matching/FLANNMatcherProcess.cpp \
    Matching/WriteMatchesToAperoProcess.cpp \
    ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp \
    ImagePreprocessing/WallisFilter_Process.cpp \
    ImagePreprocessing/Downsample_Process.cpp \
    ImagePreprocessing/LCE_BSESCS2014_Process.cpp \
    ImagePreprocessing/RajuNair2014_Process.cpp \
    ImagePreprocessing/Lal2014_Process.cpp \
    ImagePreprocessing/MSRCP2014_Process.cpp \
    ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp \
    ImagePreprocessing/POHE2013_Process.cpp \
    ImagePreprocessing/Kimori2013_Process.cpp \
    ImagePreprocessing/CelikTjahjadi2012_Process.cpp \
    ImagePreprocessing/LiuJinChenLiuLi2011_Process.cpp \
    ImagePreprocessing/Sundarami2011_Process.cpp \
    ImagePreprocessing/MaryKim2008_Process.cpp \
    ImagePreprocessing/WadudKabirDewanChae2007_Process.cpp \
    ImagePreprocessing/FAHE2006_Process.cpp \
    ImagePreprocessing/LambertiMontrucchioSanna2006_Process.cpp \
    ImagePreprocessing/YuBajaj2004_Process.cpp

HEADERS  += MainWindowFME.h \
    MatchingViewer/MatchigGraphicsView.h \
    MatchingViewer/MatchingViewer.h \
    ProcessManager/ExternalProcess.h \
    ProcessManager/MultiProcess.h \
    ProcessManager/Process.h \
    ProcessManager/ProcessConcurrent.h \
    photo/image.h \
    photo/thumbnail.h \
    photo/thbthread.h \
    photo/tabshortcuts.h \
    photo/tabgeneral.h \
    photo/settings.h \
    photo/menu.h \
    photo/photoviewer.h \
    photo/pixmapitem.h \
    photo/CrossGraphicItem.h \
    photo/crosshairgraphicsitem.h \
    MatchingViewer/PWImage.h \
    MatchingViewer/Camera.h \
    MatchingViewer/CameraModel.h \
    MatchingViewer/ExternalOrientation.h \
    MatchingViewer/PW2dPoint.h \
    MatchingViewer/PWPoint.h \
    SIFT/SIFT_KPDetProcess.h \
    SIFT/SIFT_KPDescProcess.h \
    DependencyInfoWidget.h \
    ProgressDialog.h \
    MSD/MSD_KPDetProcess.h \
    MSD/MSD.h \
    MSD/MSDImgPyramid.h \
    ORB/ORB_KPDetProcess.h \
    SURF/SURF_KPDetProcess.h \
    SURF/SUFT_KPDescProcess.h \
    HOG/HOG_KPDescProcess.h \
    ORB/ORB_KPDescProcess.h \
    MutualInformation/MutualInformation_KPDescProcess.h \
    MTM/mtm.h \
    LSS/lss.h \
    MTM/MTM_KPDescProcess.h \
    LSS/LSS_KPDescProcess.h \
    AboutFME.h \
    Matching/BFMatcherProcess.h \
    Matching/RobustMatcherRefinementProcess.h \
    GrountTruthBuilderProcess.h \
    DAISY/DAISY_KPDescProcess.h \
    FREAK/FREAK_KPDescProcess.h \
    LATCH/LATCH_KPDescProcess.h \
    LUCID/LUCID_KPDescProcess.h \
    FAST/FAST_KPDetProcess.h \
    GFTT/GFTT_KPDetProcess.h \
    MSER/MSER_KPDetProcess.h \
    BRISK/BRISK_KPDetProcess.h \
    BRISK/BRISK_KPDescProcess.h \
    BRIEF/BRIEF_KPDescProcess.h \
    Matching/FLANNMatcherProcess.h \
    Matching/WriteMatchesToAperoProcess.h \
    ImagePreprocessing/ContrastPreservingDecolorization__Process.h \
    ImagePreprocessing/WallisFilter_Process.h \
    ImagePreprocessing/Downsample_Process.h \
    ImagePreprocessing/LCE_BSESCS2014_Process.h \
    ImagePreprocessing/RajuNair2014_Process.h \
    ImagePreprocessing/Lal2014_Process.h \
    ImagePreprocessing/MSRCP2014_Process.h \
    ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h \
    ImagePreprocessing/POHE2013_Process.h \
    ImagePreprocessing/Kimori2013_Process.h \
    ImagePreprocessing/CelikTjahjadi2012_Process.h \
    ImagePreprocessing/LiuJinChenLiuLi2011_Process.h \
    ImagePreprocessing/Sundarami2011_Process.h \
    ImagePreprocessing/MaryKim2008_Process.h \
    ImagePreprocessing/WadudKabirDewanChae2007_Process.h \
    ImagePreprocessing/FAHE2006_Process.h \
    ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h \
    ImagePreprocessing/YuBajaj2004_Process.h

RESOURCES += photo/res.qrc \
    resources.qrc \
    style.qrc


FORMS    += MainWindowFME.ui \
            ProgressDialog.ui \
    AboutFME.ui

            LIBS += -L$$PWD/../../Libs/OpenCV_3.3.1_vc14_x64/x64/vc14/bin
            LIBS += -L$$PWD/../../Libs/OpenCV_3.3.1_vc14_x64/x64/vc14/lib
            LIBS += -L$$PWD/../../Libs/boost_1_61_0_vc14_x64/bin
            LIBS += -L$$PWD/../../Libs/PixKit_vc14_x64/lib/x64
debug{

                LIBS += -lpixkit_cv052d -lpixkit_file052d -lpixkit_image052d -lpixkit_ml052d -lpixkit_timer052d
                LIBS += -lopencv_photo331d -lopencv_xfeatures2d331d  -lopencv_core331d -lopencv_highgui331d -lopencv_imgproc331d -lopencv_imgcodecs331d -lopencv_video331d -lopencv_videostab331d -lopencv_videoio331d -lopencv_calib3d331d -lopencv_features2d331d  -lopencv_flann331d -lopencv_objdetect331d


}else{


            LIBS += -lpixkit_cv052 -lpixkit_file052 -lpixkit_image052 -lpixkit_ml052 -lpixkit_timer052

            LIBS += -lopencv_photo331 -lopencv_xfeatures2d331 -lopencv_core331 -lopencv_highgui331 -lopencv_imgproc331 -lopencv_imgcodecs331 -lopencv_video331 -lopencv_videostab331 -lopencv_videoio331 -lopencv_calib3d331 -lopencv_features2d331  -lopencv_flann331 -lopencv_objdetect331

}

RC_FILE = FME.rc
