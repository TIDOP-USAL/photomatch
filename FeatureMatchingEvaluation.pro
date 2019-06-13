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

include(FeatureMatchingEvaluation.pri)


INCLUDEPATH +=  src \
                third_party

SOURCES +=  main.cpp \
            MainWindowFME.cpp \
            src/fme/ui/MatchingViewer/MatchigGraphicsView.cpp \
            src/fme/ui/MatchingViewer/MatchingViewer.cpp \
            src/fme/ui/MatchingViewer/PWImage.cpp \
            src/fme/ui/MatchingViewer/Camera.cpp \
            src/fme/ui/MatchingViewer/CameraModel.cpp \
            src/fme/ui/MatchingViewer/ExternalOrientation.cpp \
            src/fme/ui/MatchingViewer/PW2dPoint.cpp \
            src/fme/ui/MatchingViewer/PWPoint.cpp \
            src/fme/process/ExternalProcess.cpp \
            src/fme/process/MultiProcess.cpp \
            src/fme/process/Process.cpp \
            src/fme/process/ProcessConcurrent.cpp \
            src/fme/process/brief/BRIEF_KPDescProcess.cpp \
            src/fme/process/brisk/BRISK_KPDetProcess.cpp \
            src/fme/process/brisk/BRISK_KPDescProcess.cpp \
            src/fme/process/daisy/DAISY_KPDescProcess.cpp \
            src/fme/process/fast/FAST_KPDetProcess.cpp \
            src/fme/process/freak/FREAK_KPDescProcess.cpp \
            src/fme/process/gftt/GFTT_KPDetProcess.cpp \
            src/fme/process/hog/HOG_KPDescProcess.cpp \
            src/fme/process/latch/LATCH_KPDescProcess.cpp \
            src/fme/process/lss/LSS_KPDescProcess.cpp \
            src/fme/process/lss/lss.cpp \
            src/fme/process/lucid/LUCID_KPDescProcess.cpp \
            src/fme/process/msd/MSD_KPDetProcess.cpp \
            src/fme/process/msd/MSD.cpp \
            src/fme/process/msd/MSDImgPyramid.cpp \
            src/fme/process/mser/MSER_KPDetProcess.cpp \
            src/fme/process/mtm/mtm.cpp \
            src/fme/process/mtm/MTM_KPDescProcess.cpp \
            src/fme/process/mutualinformation/MutualInformation_KPDescProcess.cpp \
            src/fme/process/orb/ORB_KPDetProcess.cpp \
            src/fme/process/orb/ORB_KPDescProcess.cpp \
            src/fme/process/sift/SIFT_KPDescProcess.cpp \
            src/fme/process/sift/SIFT_KPDetProcess.cpp \
            src/fme/process/surf/SURF_KPDetProcess.cpp \
            src/fme/process/surf/SUFT_KPDescProcess.cpp \
            src/fme/process/ImagePreprocessing/ContrastPreservingDecolorization__Process.cpp \
            src/fme/process/ImagePreprocessing/WallisFilter_Process.cpp \
            src/fme/process/ImagePreprocessing/Downsample_Process.cpp \
            src/fme/process/ImagePreprocessing/LCE_BSESCS2014_Process.cpp \
            src/fme/process/ImagePreprocessing/RajuNair2014_Process.cpp \
            src/fme/process/ImagePreprocessing/Lal2014_Process.cpp \
            src/fme/process/ImagePreprocessing/MSRCP2014_Process.cpp \
            src/fme/process/ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.cpp \
            src/fme/process/ImagePreprocessing/POHE2013_Process.cpp \
            src/fme/process/ImagePreprocessing/Kimori2013_Process.cpp \
            src/fme/process/ImagePreprocessing/CelikTjahjadi2012_Process.cpp \
            src/fme/process/ImagePreprocessing/LiuJinChenLiuLi2011_Process.cpp \
            src/fme/process/ImagePreprocessing/Sundarami2011_Process.cpp \
            src/fme/process/ImagePreprocessing/MaryKim2008_Process.cpp \
            src/fme/process/ImagePreprocessing/WadudKabirDewanChae2007_Process.cpp \
            src/fme/process/ImagePreprocessing/FAHE2006_Process.cpp \
            src/fme/process/ImagePreprocessing/LambertiMontrucchioSanna2006_Process.cpp \
            src/fme/process/ImagePreprocessing/YuBajaj2004_Process.cpp \
            src/fme/process/Matching/BFMatcherProcess.cpp \
            src/fme/process/Matching/RobustMatcherRefinementProcess.cpp \
            src/fme/process/Matching/FLANNMatcherProcess.cpp \
            src/fme/process/Matching/WriteMatchesToAperoProcess.cpp \
            third_party/photo/image.cpp \
            third_party/photo/thumbnail.cpp \
            third_party/photo/tabshortcuts.cpp \
            third_party/photo/tabgeneral.cpp \
            third_party/photo/settings.cpp \
            third_party/photo/menu.cpp \
            third_party/photo/photoviewer.cpp \
            third_party/photo/pixmapitem.cpp \
            third_party/photo/CrossGraphicItem.cpp \
            third_party/photo/crosshairgraphicsitem.cpp \
            DependencyInfoWidget.cpp \
            ProgressDialog.cpp \
            AboutFME.cpp \
            GrountTruthBuilderProcess.cpp

HEADERS  += MainWindowFME.h \
            src/fme/ui/MatchingViewer/MatchigGraphicsView.h \
            src/fme/ui/MatchingViewer/MatchingViewer.h \
            src/fme/ui/MatchingViewer/PWImage.h \
            src/fme/ui/MatchingViewer/Camera.h \
            src/fme/ui/MatchingViewer/CameraModel.h \
            src/fme/ui/MatchingViewer/ExternalOrientation.h \
            src/fme/ui/MatchingViewer/PW2dPoint.h \
            src/fme/ui/MatchingViewer/PWPoint.h \
            src/fme/process/ExternalProcess.h \
            src/fme/process/MultiProcess.h \
            src/fme/process/Process.h \
            src/fme/process/ProcessConcurrent.h \
            src/fme/process/brief/BRIEF_KPDescProcess.h \
            src/fme/process/brisk/BRISK_KPDetProcess.h \
            src/fme/process/brisk/BRISK_KPDescProcess.h \
            src/fme/process/daisy/DAISY_KPDescProcess.h \
            src/fme/process/fast/FAST_KPDetProcess.h \
            src/fme/process/freak/FREAK_KPDescProcess.h \
            src/fme/process/gftt/GFTT_KPDetProcess.h \
            src/fme/process/hog/HOG_KPDescProcess.h \
            src/fme/process/latch/LATCH_KPDescProcess.h \
            src/fme/process/lss/LSS_KPDescProcess.h \
            src/fme/process/lss/lss.h \
            src/fme/process/lucid/LUCID_KPDescProcess.h \
            src/fme/process/msd/MSD_KPDetProcess.h \
            src/fme/process/msd/MSD.h \
            src/fme/process/msd/MSDImgPyramid.h \
            src/fme/process/mser/MSER_KPDetProcess.h \
            src/fme/process/MTM/mtm.h \
            src/fme/process/MTM/MTM_KPDescProcess.h \
            src/fme/process/mutualinformation/MutualInformation_KPDescProcess.h \
            src/fme/process/orb/ORB_KPDetProcess.h \
            src/fme/process/orb/ORB_KPDescProcess.h \
            src/fme/process/surf/SURF_KPDetProcess.h \
            src/fme/process/surf/SUFT_KPDescProcess.h \
            src/fme/process/sift/SIFT_KPDetProcess.h \
            src/fme/process/sift/SIFT_KPDescProcess.h \
            src/fme/process/ImagePreprocessing/ContrastPreservingDecolorization__Process.h \
            src/fme/process/ImagePreprocessing/WallisFilter_Process.h \
            src/fme/process/ImagePreprocessing/Downsample_Process.h \
            src/fme/process/ImagePreprocessing/LCE_BSESCS2014_Process.h \
            src/fme/process/ImagePreprocessing/RajuNair2014_Process.h \
            src/fme/process/ImagePreprocessing/Lal2014_Process.h \
            src/fme/process/ImagePreprocessing/MSRCP2014_Process.h \
            src/fme/process/ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h \
            src/fme/process/ImagePreprocessing/POHE2013_Process.h \
            src/fme/process/ImagePreprocessing/Kimori2013_Process.h \
            src/fme/process/ImagePreprocessing/CelikTjahjadi2012_Process.h \
            src/fme/process/ImagePreprocessing/LiuJinChenLiuLi2011_Process.h \
            src/fme/process/ImagePreprocessing/Sundarami2011_Process.h \
            src/fme/process/ImagePreprocessing/MaryKim2008_Process.h \
            src/fme/process/ImagePreprocessing/WadudKabirDewanChae2007_Process.h \
            src/fme/process/ImagePreprocessing/FAHE2006_Process.h \
            src/fme/process/ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h \
            src/fme/process/ImagePreprocessing/YuBajaj2004_Process.h \
            src/fme/process/Matching/BFMatcherProcess.h \
            src/fme/process/Matching/RobustMatcherRefinementProcess.h \
            src/fme/process/Matching/FLANNMatcherProcess.h \
            src/fme/process/Matching/WriteMatchesToAperoProcess.h \
            third_party/photo/image.h \
            third_party/photo/thumbnail.h \
            third_party/photo/thbthread.h \
            third_party/photo/tabshortcuts.h \
            third_party/photo/tabgeneral.h \
            third_party/photo/settings.h \
            third_party/photo/menu.h \
            third_party/photo/photoviewer.h \
            third_party/photo/pixmapitem.h \
            third_party/photo/CrossGraphicItem.h \
            third_party/photo/crosshairgraphicsitem.h \
            DependencyInfoWidget.h \
            ProgressDialog.h \
            AboutFME.h \
            GrountTruthBuilderProcess.h

RESOURCES += third_party/photo/res.qrc \
    resources.qrc \
    style.qrc


FORMS    += MainWindowFME.ui \
            ProgressDialog.ui \
    AboutFME.ui



RC_FILE = FME.rc
