#-------------------------------------------------
#
# Project created by QtCreator 2019-04-09T15:32:54
#
#-------------------------------------------------

QT       -= gui

#QT += widgets

TARGET = libprocess
TEMPLATE = lib

DEFINES += QT_PROJECT

include(..\..\..\config.pri)

!FME_EXPORTS {
  CONFIG += staticlib
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../

SOURCES += Process.cpp \
           MultiProcess.cpp \
           ExternalProcess.cpp \
           ProcessConcurrent.cpp \
           brief/BRIEF_KPDescProcess.cpp \
           brisk/BRISK_KPDescProcess.cpp \
           brisk/BRISK_KPDetProcess.cpp \
           daisy/DAISY_KPDescProcess.cpp \
           fast/FAST_KPDetProcess.cpp \
           freak/FREAK_KPDescProcess.cpp \
           gftt/GFTT_KPDetProcess.cpp \
           hog/HOG_KPDescProcess.cpp \
           latch/LATCH_KPDescProcess.cpp \
           # Falta por añadir widget y ver parametros del descriptor
           #lss/LSS_KPDescProcess.cpp \
           #lss/lss.cpp \
           lucid/LUCID_KPDescProcess.cpp \
           msd/MSD_KPDetProcess.cpp \
           msd/MSD.cpp \
           msd/MSDImgPyramid.cpp \
           mser/MSER_KPDetProcess.cpp \
           mtm/mtm.cpp \
           mtm/MTM_KPDescProcess.cpp \
           #mutualinformation/MutualInformation_KPDescProcess.cpp \
           orb/ORB_KPDetProcess.cpp \
           orb/ORB_KPDescProcess.cpp \
           sift/SIFT_KPDescProcess.cpp \
           sift/SIFT_KPDetProcess.cpp \
           surf/SURF_KPDetProcess.cpp \
           surf/SUFT_KPDescProcess.cpp \
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
           ImagePreprocessing/YuBajaj2004_Process.cpp \
           Matching/BFMatcherProcess.cpp \
           Matching/RobustMatcherRefinementProcess.cpp \
           Matching/FLANNMatcherProcess.cpp \
           Matching/WriteMatchesToAperoProcess.cpp

HEADERS += ../fme_global.h \
           Process.h \
           MultiProcess.h \
           ExternalProcess.h \
           ProcessConcurrent.h\
           brief/BRIEF_KPDescProcess.h \
           brisk/BRISK_KPDescProcess.h \
           brisk/BRISK_KPDetProcess.h \
           daisy/DAISY_KPDescProcess.h \
           fast/FAST_KPDetProcess.h \
           freak/FREAK_KPDescProcess.h \
           gftt/GFTT_KPDetProcess.h \
           hog/HOG_KPDescProcess.h \
           latch/LATCH_KPDescProcess.h \
           # Falta por añadir widget y ver parametros del descriptor
           #lss/LSS_KPDescProcess.h \
           #lss/lss.h \
           lucid/LUCID_KPDescProcess.h \
           msd/MSD_KPDetProcess.h \
           msd/MSD.h \
           msd/MSDImgPyramid.h \
           mser/MSER_KPDetProcess.h \
           MTM/mtm.h \
           MTM/MTM_KPDescProcess.h \
           #mutualinformation/MutualInformation_KPDescProcess.h \
           orb/ORB_KPDetProcess.h \
           orb/ORB_KPDescProcess.h \
           surf/SURF_KPDetProcess.h \
           surf/SUFT_KPDescProcess.h \
           sift/SIFT_KPDetProcess.h \
           sift/SIFT_KPDescProcess.h \
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
           ImagePreprocessing/YuBajaj2004_Process.h \
           Matching/BFMatcherProcess.h \
           Matching/RobustMatcherRefinementProcess.h \
           Matching/FLANNMatcherProcess.h \
           Matching/WriteMatchesToAperoProcess.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
