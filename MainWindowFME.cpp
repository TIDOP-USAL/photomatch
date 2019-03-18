#include "MainWindowFME.h"
#include "ui_MainWindowFME.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include "AboutFME.h"
#include <QDesktopWidget>
#include "SIFT/SIFT_KPDescProcess.h"
#include "SIFT/SIFT_KPDetProcess.h"
#include "MSD/MSD_KPDetProcess.h"
#include "ORB/ORB_KPDetProcess.h"
#include "ORB/ORB_KPDescProcess.h"
#include "SURF/SURF_KPDetProcess.h"
#include "SURF/SUFT_KPDescProcess.h"
#include "HOG/HOG_KPDescProcess.h"
#include "MutualInformation/MutualInformation_KPDescProcess.h"
#include "MTM/MTM_KPDescProcess.h"
#include "LSS/LSS_KPDescProcess.h"
#include "DAISY/DAISY_KPDescProcess.h"
#include "FREAK/FREAK_KPDescProcess.h"
#include "LATCH/LATCH_KPDescProcess.h"
#include "FAST/FAST_KPDetProcess.h"
#include "GFTT/GFTT_KPDetProcess.h"
#include "MSER/MSER_KPDetProcess.h"
#include "BRISK/BRISK_KPDetProcess.h"
#include "BRISK/BRISK_KPDescProcess.h"
#include "BRIEF/BRIEF_KPDescProcess.h"
#include "Matching/FLANNMatcherProcess.h"
#include "Matching/BFMatcherProcess.h"
#include "Matching/RobustMatcherRefinementProcess.h"
#include "GrountTruthBuilderProcess.h"
#include "QMessageBox"
#include <QDateTime>
#include "Matching/WriteMatchesToAperoProcess.h"
#include <QScrollArea>

#include "ImagePreprocessing/ContrastPreservingDecolorization__Process.h"
#include "ImagePreprocessing/WallisFilter_Process.h"
#include "ImagePreprocessing/Downsample_Process.h"
#include "ImagePreprocessing/LCE_BSESCS2014_Process.h"
#include "ImagePreprocessing/RajuNair2014_Process.h"
#include "ImagePreprocessing/Lal2014_Process.h"
#include "ImagePreprocessing/MSRCP2014_Process.h"
#include "ImagePreprocessing/Wang_Zheng_Hu_Li2013_Process.h"
#include "ImagePreprocessing/POHE2013_Process.h"
#include "ImagePreprocessing/Kimori2013_Process.h"
#include "ImagePreprocessing/CelikTjahjadi2012_Process.h"
#include "ImagePreprocessing/LiuJinChenLiuLi2011_Process.h"
#include "ImagePreprocessing/Sundarami2011_Process.h"
#include "ImagePreprocessing/MaryKim2008_Process.h"
#include "ImagePreprocessing/WadudKabirDewanChae2007_Process.h"
#include "ImagePreprocessing/FAHE2006_Process.h"
#include "ImagePreprocessing/LambertiMontrucchioSanna2006_Process.h"
#include "ImagePreprocessing/YuBajaj2004_Process.h"







using namespace std;


MainWindowFME::MainWindowFME(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowFME)
{
//    QFile f(":qdarkstyle/style.qss");
//    if (!f.exists())
//    {
//        printf("Unable to set stylesheet, file not found\n");
//    }
//    else
//    {
//        f.open(QFile::ReadOnly | QFile::Text);
//        QTextStream ts(&f);
//        qApp->setStyleSheet(ts.readAll());
//    }

    ui->setupUi(this);
    mHaveGroundTrugh=false;

    //Set logo
    setWindowIcon(QIcon(":/PW/icons/img/FME.png"));
    setWindowTitle("Feature Matching Evaluation");
    mDockImageParams = new QDockWidget(tr("Image Feature Detection"),this);
    mDockResults = new QDockWidget(tr("Results"),this);
    mDockImageParams->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mDockResults->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mDockImageParams->setFeatures ( QDockWidget::NoDockWidgetFeatures );
    mDockResults->setFeatures ( QDockWidget::NoDockWidgetFeatures );
    mDockImageParams->setMinimumWidth(350);
    mDockResults->setMinimumHeight(QApplication::desktop()->screenGeometry().height()/6);


    addDockWidget(Qt::LeftDockWidgetArea, mDockImageParams);
    addDockWidget(Qt::BottomDockWidgetArea, mDockResults);

    //LeftDock content;
    QScrollArea *leftDockScrollArea = new QScrollArea();
    leftDockScrollArea->setWidgetResizable(true);
    QFrame *ImageDockContent = new QFrame();
    QVBoxLayout *ImageDockContentLayout = new QVBoxLayout();
    ImageDockContentLayout->setAlignment(Qt::AlignTop);
    //General info
    QFrame *imagesInfoFrame= new QFrame();
    QHBoxLayout *imagesInfoFrameLayout = new QHBoxLayout();
    imagesInfoFrameLayout->setContentsMargins(0,0,0,0);

    mGbLeftImageInfo = new QGroupBox("Left image info");
    QGridLayout *leftImageInfoLayout = new QGridLayout();
    leftImageInfoLayout->addWidget(new QLabel("Name:"),0,0);
    mLbLeftImageName= new QLabel();
    leftImageInfoLayout->addWidget(mLbLeftImageName,0,1);
    leftImageInfoLayout->addWidget(new QLabel("Size:"),1,0);
    mLbLeftImageSize= new QLabel();
    leftImageInfoLayout->addWidget(mLbLeftImageSize,1,1);

    //    QPixmap pix(":/check.png");
    //    pix.scaledToHeight(10,Qt::SmoothTransformation);
    //    mLeftCheck = new QLabel();
    //    mLeftCheck->setPixmap(pix);
    //    leftImageInfoLayout->addWidget(mLeftCheck,0,2,2,1);
    //    mLeftCheck->hide();

    mGbLeftImageInfo->setLayout(leftImageInfoLayout);
    imagesInfoFrameLayout->addWidget(mGbLeftImageInfo);
    //GeneralInfo
    mGbRightImageInfo = new QGroupBox("Right image info");
    QGridLayout *RightImageInfoLayout = new QGridLayout();
    RightImageInfoLayout->addWidget(new QLabel("Name:"),0,0);
    mLbRightImageName= new QLabel();
    RightImageInfoLayout->addWidget(mLbRightImageName,0,1);
    RightImageInfoLayout->addWidget(new QLabel("Size:"),1,0);
    mLbRightImageSize= new QLabel();
    RightImageInfoLayout->addWidget(mLbRightImageSize,1,1);

    //    mRightCheck = new QLabel();
    //    mRightCheck->setPixmap(pix);
    //    RightImageInfoLayout->addWidget(mRightCheck,0,2,2,1);
    //    mRightCheck->hide();

    mGbRightImageInfo->setLayout(RightImageInfoLayout);
    imagesInfoFrameLayout->addWidget(mGbRightImageInfo);

    imagesInfoFrame->setLayout(imagesInfoFrameLayout);
    ImageDockContentLayout->addWidget(imagesInfoFrame);


    ////////////
    //Preprocessing
    mGbPreprocessing = new QGroupBox("Feature detection parameters");
    QGridLayout *preprocessingLayout = new QGridLayout();
    mChDownsampleImages = new QCheckBox("Downsample images");
    mChDownsampleImages->setChecked(true);
    preprocessingLayout->addWidget(mChDownsampleImages,0,0);
    mSbDownsamplingMaxSize = new QSpinBox();
    mSbDownsamplingMaxSize->setRange(1,10000000);
    mSbDownsamplingMaxSize->setSingleStep(100);
    mSbDownsamplingMaxSize->setValue(1500);
    preprocessingLayout->addWidget(mSbDownsamplingMaxSize,0,1);
    connect(mChDownsampleImages,SIGNAL(clicked(bool)),mSbDownsamplingMaxSize,SLOT(setEnabled(bool)));


    preprocessingLayout->addWidget(new QLabel("Preprocessing algorithm:"),1,0);
    mCbPreprocessingAlgorithm = new QComboBox();
    mCbPreprocessingAlgorithm->addItem("Contrast preserving decolorization");
    mCbPreprocessingAlgorithm->addItem("Wallis");
    mCbPreprocessingAlgorithm->addItem("LCE_BSESCS2014");
    mCbPreprocessingAlgorithm->addItem("RajuNair2014");
    mCbPreprocessingAlgorithm->addItem("Lal2014");
    mCbPreprocessingAlgorithm->addItem("MSRCP2014");
    mCbPreprocessingAlgorithm->addItem("WangZhengHuLi2013");
    mCbPreprocessingAlgorithm->addItem("POHE2013");
    mCbPreprocessingAlgorithm->addItem("Kimori2013");
    mCbPreprocessingAlgorithm->addItem("CelikTjahjadi2012");
    mCbPreprocessingAlgorithm->addItem("LiuJinChenLiuLi2011");
    mCbPreprocessingAlgorithm->addItem("Sundarami2011");
    mCbPreprocessingAlgorithm->addItem("MaryKim2008");
    mCbPreprocessingAlgorithm->addItem("WadudKabirDewanChae2007");
    mCbPreprocessingAlgorithm->addItem("FAHE2006");
    mCbPreprocessingAlgorithm->addItem("LambertiMontrucchioSanna2006");
    mCbPreprocessingAlgorithm->addItem("YuBajaj2004");
    mCbPreprocessingAlgorithm->addItem("KimKimHwang2001");
    mCbPreprocessingAlgorithm->addItem("Stark2000");
    mCbPreprocessingAlgorithm->addItem("MSRCR1997");
    mCbPreprocessingAlgorithm->addItem("GlobalHistogramEqualization1992");
    mCbPreprocessingAlgorithm->addItem("AHE1974");
    mCbPreprocessingAlgorithm->addItem("CLAHE1987");
    mCbPreprocessingAlgorithm->addItem("CLAHEnon1987");
    mCbPreprocessingAlgorithm->addItem("SimplestColorBalance");


    //    connect(mCbPreprocessingAlgorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(on_LeftImageFeatureDetector_ItemChanged(int)));

    preprocessingLayout->addWidget(mCbPreprocessingAlgorithm,1,1);

    //WallisConf
    mWallisConf = new QGroupBox("Wallis Advanced Parameters");
    QGridLayout *wallisLayout = new QGridLayout();

    wallisLayout->addWidget(new QLabel("Contrast:"),0,0);
    mDsbWallis_Contrast= new QDoubleSpinBox();
    mDsbWallis_Contrast->setRange(0,1);
    mDsbWallis_Contrast->setSingleStep(0.1);
    mDsbWallis_Contrast->setValue(1.0);
    wallisLayout->addWidget(mDsbWallis_Contrast,0,1);

    wallisLayout->addWidget(new QLabel("Brightness:"),0,2);
    mDsbWallis_Brightness= new QDoubleSpinBox();
    mDsbWallis_Brightness->setRange(0,1);
    mDsbWallis_Brightness->setSingleStep(0.1);
    mDsbWallis_Brightness->setValue(0.2);
    wallisLayout->addWidget(mDsbWallis_Brightness,0,3);

    wallisLayout->addWidget(new QLabel("Imposed Average:"),1,0);
    mSbWallis_ImposedAverage = new QSpinBox();
    mSbWallis_ImposedAverage->setRange(1,1000);
    mSbWallis_ImposedAverage->setSingleStep(1);
    mSbWallis_ImposedAverage->setValue(41);
    wallisLayout->addWidget(mSbWallis_ImposedAverage,1,1);

    wallisLayout->addWidget(new QLabel("Imposed Local StdDev:"),1,2);
    mSbWallis_ImposedLocalStandardDeviation = new QSpinBox();
    mSbWallis_ImposedLocalStandardDeviation->setRange(1,10000);
    mSbWallis_ImposedLocalStandardDeviation->setSingleStep(1);
    mSbWallis_ImposedLocalStandardDeviation->setValue(127);
    wallisLayout->addWidget(mSbWallis_ImposedLocalStandardDeviation,1,3);

    wallisLayout->addWidget(new QLabel("Kernel Size:"),2,0);
    mSbWallis_KernelSize = new QSpinBox();
    mSbWallis_KernelSize->setRange(1,10000);
    mSbWallis_KernelSize->setSingleStep(1);
    mSbWallis_KernelSize->setValue(50);
    wallisLayout->addWidget(mSbWallis_KernelSize,2,1);

    mWallisConf->setLayout(wallisLayout);
    preprocessingLayout->addWidget(mWallisConf,2,0,1,2);
    mWallisConf->hide();

    mPbComputePreprocessing= new QPushButton("Compute preprocessing");
    connect(mPbComputePreprocessing,SIGNAL(clicked()),this,SLOT(on_PbComputePreprocessing_triggered()));
    preprocessingLayout->addWidget(mPbComputePreprocessing,3,0,1,2);

    //

    mGbPreprocessing->setLayout(preprocessingLayout);
    ImageDockContentLayout->addWidget(mGbPreprocessing);

    mGbPreprocessing->setEnabled(false);

    connect(mCbPreprocessingAlgorithm,SIGNAL(currentIndexChanged(int)),this,SLOT(on_Preprocessing_ItemChanged(int)));


    //////////////
    //Feature detection
    mGbFeatureDetection = new QGroupBox("Feature detection parameters");
    QGridLayout *featureDetectionLayout = new QGridLayout();
    featureDetectionLayout->addWidget(new QLabel("Left Image Key-point detector:"),0,0);
    mCbLeftDetector = new QComboBox();
    mCbLeftDetector->addItem("SIFT");
    mCbLeftDetector->addItem("MSD");
    mCbLeftDetector->addItem("ORB");
    mCbLeftDetector->addItem("SURF");
    mCbLeftDetector->addItem("FAST");
    mCbLeftDetector->addItem("GFTT");
    mCbLeftDetector->addItem("MSER");
    mCbLeftDetector->addItem("BRISK");

    connect(mCbLeftDetector,SIGNAL(currentIndexChanged(int)),this,SLOT(on_LeftImageFeatureDetector_ItemChanged(int)));

    featureDetectionLayout->addWidget(mCbLeftDetector,0,1);

    mMSDconf_LeftImage = new QGroupBox("MSD Advanced Parameters (Left image)");
    QGridLayout *msdConfLeftLayout = new QGridLayout();

    msdConfLeftLayout->addWidget(new QLabel("Threshold Saliency:"),0,0,1,2);
    mDsbMSD_Left_ThSaliency= new QDoubleSpinBox();
    mDsbMSD_Left_ThSaliency->setRange(0,2000);
    mDsbMSD_Left_ThSaliency->setSingleStep(1);
    mDsbMSD_Left_ThSaliency->setValue(250);
    msdConfLeftLayout->addWidget(mDsbMSD_Left_ThSaliency,0,2,1,2);


    msdConfLeftLayout->addWidget(new QLabel("Path radius"),1,0);
    mSbMSD_Left_PatchRadius = new QSpinBox();
    mSbMSD_Left_PatchRadius->setRange(1,10);
    mSbMSD_Left_PatchRadius->setSingleStep(1);
    mSbMSD_Left_PatchRadius->setValue(3);
    msdConfLeftLayout->addWidget(mSbMSD_Left_PatchRadius,1,1);

    msdConfLeftLayout->addWidget(new QLabel("KNN:"),1,2);
    mSbMSD_Left_KNN = new QSpinBox();
    mSbMSD_Left_KNN->setRange(1,10);
    mSbMSD_Left_KNN->setSingleStep(1);
    mSbMSD_Left_KNN->setValue(4);
    msdConfLeftLayout->addWidget(mSbMSD_Left_KNN,1,3);

    msdConfLeftLayout->addWidget(new QLabel("Area radius:"),2,0);
    mSbMSD_Left_AreaRadius = new QSpinBox();
    mSbMSD_Left_AreaRadius->setRange(1,10);
    mSbMSD_Left_AreaRadius->setSingleStep(1);
    mSbMSD_Left_AreaRadius->setValue(5);
    msdConfLeftLayout->addWidget(mSbMSD_Left_AreaRadius,2,1);

    msdConfLeftLayout->addWidget(new QLabel("Scale factor:"),2,2);
    mDsbMSD_Left_ScaleFactor = new QDoubleSpinBox();
    mDsbMSD_Left_ScaleFactor->setRange(1,10);
    mDsbMSD_Left_ScaleFactor->setSingleStep(0.05);
    mDsbMSD_Left_ScaleFactor->setValue(1.25);
    msdConfLeftLayout->addWidget(mDsbMSD_Left_ScaleFactor,2,3);

    msdConfLeftLayout->addWidget(new QLabel("NMS radius:"),3,0);
    mSbMSD_Left_NMSRadius = new QSpinBox();
    mSbMSD_Left_NMSRadius->setRange(1,10);
    mSbMSD_Left_NMSRadius->setSingleStep(1);
    mSbMSD_Left_NMSRadius->setValue(5);
    msdConfLeftLayout->addWidget(mSbMSD_Left_NMSRadius,3,1);

    msdConfLeftLayout->addWidget(new QLabel("N Scales:"),3,2);
    mSbMSD_Left_NScales = new QSpinBox();
    mSbMSD_Left_NScales->setRange(-1,10);
    mSbMSD_Left_NScales->setSingleStep(1);
    mSbMSD_Left_NScales->setValue(-1);

    msdConfLeftLayout->addWidget(mSbMSD_Left_NScales,3,3);

    msdConfLeftLayout->addWidget(new QLabel("NMS Scale R.:"),4,0);
    mSbMSD_Left_NMSScaleR = new QSpinBox();
    mSbMSD_Left_NMSScaleR->setRange(0,10);
    mSbMSD_Left_NMSScaleR->setSingleStep(1);
    mSbMSD_Left_NMSScaleR->setValue(0);
    msdConfLeftLayout->addWidget(mSbMSD_Left_NMSScaleR,4,1);

    mCbMSD_Left_ComputeOrientations = new QCheckBox("Compute orientations");
    msdConfLeftLayout->addWidget(mCbMSD_Left_ComputeOrientations,4,2,1,2); //Check orientations

    mCbMSD_Left_Affine = new QCheckBox("Affine MSD");
    msdConfLeftLayout->addWidget(mCbMSD_Left_Affine,5,0,1,2); //CheckAffine

    msdConfLeftLayout->addWidget(new QLabel("Tilts:"),5,2);
    mSbMSD_Left_AffineTilts = new QSpinBox();
    mSbMSD_Left_AffineTilts->setRange(3,10);
    mSbMSD_Left_AffineTilts->setSingleStep(1);
    mSbMSD_Left_AffineTilts->setValue(3);
    msdConfLeftLayout->addWidget(mSbMSD_Left_AffineTilts,5,3);

    mMSDconf_LeftImage->setLayout(msdConfLeftLayout);
    featureDetectionLayout->addWidget(mMSDconf_LeftImage,1,0,1,2);
    mMSDconf_LeftImage->hide();

    mORBconf_LeftImage = new QGroupBox("ORB Advanced Parameters (Left image)");
    QGridLayout *orbConfLeftLayout = new QGridLayout();
    orbConfLeftLayout->addWidget(new QLabel("KeyPoints count:"),0,0);
    mOrbKpLeft = new QSpinBox();
    mOrbKpLeft->setRange(10,1000000);
    mOrbKpLeft->setSingleStep(100);
    mOrbKpLeft->setValue(5000);
    orbConfLeftLayout->addWidget(mOrbKpLeft,0,1);
    mORBconf_LeftImage->setLayout(orbConfLeftLayout);
    featureDetectionLayout->addWidget(mORBconf_LeftImage,2,0,1,2);
    mORBconf_LeftImage->hide();


    featureDetectionLayout->addWidget(new QLabel("Right Image Key-point detector:"),3,0);

    mCbRightDetector = new QComboBox();
    mCbRightDetector->addItem("SIFT");
    mCbRightDetector->addItem("MSD");
    mCbRightDetector->addItem("ORB");
    mCbRightDetector->addItem("SURF");
    mCbRightDetector->addItem("FAST");
    mCbRightDetector->addItem("GFTT");
    mCbRightDetector->addItem("MSER");
    mCbRightDetector->addItem("BRISK");

    connect(mCbRightDetector,SIGNAL(currentIndexChanged(int)),this,SLOT(on_RightImageFeatureDetector_ItemChanged(int)));
    featureDetectionLayout->addWidget(mCbRightDetector,3,1);

    mMSDconf_RightImage = new QGroupBox("MSD Advanced Parameters (Right image)");
    QGridLayout *msdConfRightLayout = new QGridLayout();

    msdConfRightLayout->addWidget(new QLabel("Threshold Saliency:"),0,0,1,2);
    mDsbMSD_Right_ThSaliency= new QDoubleSpinBox();
    mDsbMSD_Right_ThSaliency->setRange(0,2000);
    mDsbMSD_Right_ThSaliency->setSingleStep(1);
    mDsbMSD_Right_ThSaliency->setValue(250);
    msdConfRightLayout->addWidget(mDsbMSD_Right_ThSaliency,0,2,1,2);


    msdConfRightLayout->addWidget(new QLabel("Path radius"),1,0);
    mSbMSD_Right_PatchRadius = new QSpinBox();
    mSbMSD_Right_PatchRadius->setRange(1,10);
    mSbMSD_Right_PatchRadius->setSingleStep(1);
    mSbMSD_Right_PatchRadius->setValue(3);
    msdConfRightLayout->addWidget(mSbMSD_Right_PatchRadius,1,1);

    msdConfRightLayout->addWidget(new QLabel("KNN:"),1,2);
    mSbMSD_Right_KNN = new QSpinBox();
    mSbMSD_Right_KNN->setRange(1,10);
    mSbMSD_Right_KNN->setSingleStep(1);
    mSbMSD_Right_KNN->setValue(4);
    msdConfRightLayout->addWidget(mSbMSD_Right_KNN,1,3);

    msdConfRightLayout->addWidget(new QLabel("Area radius:"),2,0);
    mSbMSD_Right_AreaRadius = new QSpinBox();
    mSbMSD_Right_AreaRadius->setRange(1,10);
    mSbMSD_Right_AreaRadius->setSingleStep(1);
    mSbMSD_Right_AreaRadius->setValue(5);
    msdConfRightLayout->addWidget(mSbMSD_Right_AreaRadius,2,1);

    msdConfRightLayout->addWidget(new QLabel("Scale factor:"),2,2);
    mDsbMSD_Right_ScaleFactor = new QDoubleSpinBox();
    mDsbMSD_Right_ScaleFactor->setRange(1,10);
    mDsbMSD_Right_ScaleFactor->setSingleStep(0.05);
    mDsbMSD_Right_ScaleFactor->setValue(1.25);
    msdConfRightLayout->addWidget(mDsbMSD_Right_ScaleFactor,2,3);

    msdConfRightLayout->addWidget(new QLabel("NMS radius:"),3,0);
    mSbMSD_Right_NMSRadius = new QSpinBox();
    mSbMSD_Right_NMSRadius->setRange(1,10);
    mSbMSD_Right_NMSRadius->setSingleStep(1);
    mSbMSD_Right_NMSRadius->setValue(5);
    msdConfRightLayout->addWidget(mSbMSD_Right_NMSRadius,3,1);

    msdConfRightLayout->addWidget(new QLabel("N Scales:"),3,2);
    mSbMSD_Right_NScales = new QSpinBox();
    mSbMSD_Right_NScales->setRange(-1,10);
    mSbMSD_Right_NScales->setSingleStep(1);
    mSbMSD_Right_NScales->setValue(-1);

    msdConfRightLayout->addWidget(mSbMSD_Right_NScales,3,3);

    msdConfRightLayout->addWidget(new QLabel("NMS Scale R.:"),4,0);
    mSbMSD_Right_NMSScaleR = new QSpinBox();
    mSbMSD_Right_NMSScaleR->setRange(0,10);
    mSbMSD_Right_NMSScaleR->setSingleStep(1);
    mSbMSD_Right_NMSScaleR->setValue(0);
    msdConfRightLayout->addWidget(mSbMSD_Right_NMSScaleR,4,1);

    mCbMSD_Right_ComputeOrientations = new QCheckBox("Compute orientations");
    msdConfRightLayout->addWidget(mCbMSD_Right_ComputeOrientations,4,2,1,2); //Check orientations

    mCbMSD_Right_Affine = new QCheckBox("Affine MSD");
    msdConfRightLayout->addWidget(mCbMSD_Right_Affine,5,0,1,2); //CheckAffine

    msdConfRightLayout->addWidget(new QLabel("Tilts:"),5,2);
    mSbMSD_Right_AffineTilts = new QSpinBox();
    mSbMSD_Right_AffineTilts->setRange(3,10);
    mSbMSD_Right_AffineTilts->setSingleStep(1);
    mSbMSD_Right_AffineTilts->setValue(3);
    msdConfRightLayout->addWidget(mSbMSD_Right_AffineTilts,5,3);

    mMSDconf_RightImage->setLayout(msdConfRightLayout);
    featureDetectionLayout->addWidget(mMSDconf_RightImage,4,0,1,2);
    mMSDconf_RightImage->hide();

    mORBconf_RightImage = new QGroupBox("ORB Advanced Parameters (Right image)");
    QGridLayout *orbConfRightLayout = new QGridLayout();
    orbConfRightLayout->addWidget(new QLabel("KeyPoints count:"),0,0);
    mOrbKpRight = new QSpinBox();
    mOrbKpRight->setRange(10,1000000);
    mOrbKpRight->setSingleStep(100);
    mOrbKpRight->setValue(5000);
    orbConfRightLayout->addWidget(mOrbKpRight,0,1);
    mORBconf_RightImage->setLayout(orbConfRightLayout);
    featureDetectionLayout->addWidget(mORBconf_RightImage,5,0,1,2);
    mORBconf_RightImage->hide();

    featureDetectionLayout->addWidget(new QLabel("Key-point descriptor:"),6,0);
    mCbDescriptor = new QComboBox();
    mCbDescriptor->addItem("SIFT");
    mCbDescriptor->addItem("ORB");
    mCbDescriptor->addItem("SURF");
    mCbDescriptor->addItem("HOG");
    mCbDescriptor->addItem("Mutual Information");
    mCbDescriptor->addItem("MTM PWC");
    mCbDescriptor->addItem("LSS");
    mCbDescriptor->addItem("DAISY");
    mCbDescriptor->addItem("FREAK");
    mCbDescriptor->addItem("LATCH");
    mCbDescriptor->addItem("BRISK");
    mCbDescriptor->addItem("BRIEF");

    featureDetectionLayout->addWidget(mCbDescriptor,6,1);

    mPbComputeFeatures= new QPushButton("Compute features");
    connect(mPbComputeFeatures,SIGNAL(clicked()),this,SLOT(on_PbComputeFeatures_triggered()));
    featureDetectionLayout->addWidget(mPbComputeFeatures,7,0,1,2);

    mGbFeatureDetection->setLayout(featureDetectionLayout);
    ImageDockContentLayout->addWidget(mGbFeatureDetection);

    mGbFeatureDetection->setEnabled(false);

    mGbFeatureMatching = new QGroupBox("Feature matching");
    QGridLayout *featureMatchingLayout = new QGridLayout();
    featureMatchingLayout->addWidget(new QLabel("Matching method:"),0,0);
    mCbMatchingMethod = new QComboBox();
    mCbMatchingMethod->addItem("Robust Matcher");
    mCbMatchingMethod->addItem("FLANN");
    featureMatchingLayout->addWidget(mCbMatchingMethod,0,1);
    connect(mCbMatchingMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbMatchingMethod_ItemChanged(int)));
    mGbRobustMatcherConf = new QGroupBox("Robust matcher parameters");
    QGridLayout *robustMatcherConfLayout = new QGridLayout();

    robustMatcherConfLayout->addWidget(new QLabel("Refinement method:"),1,0);
    mCbMatchingRefinementMethod = new QComboBox();
    mCbMatchingRefinementMethod->addItem("LMSE");
    mCbMatchingRefinementMethod->addItem("RANSAC");
    mCbMatchingRefinementMethod->addItem("8-Points");
    robustMatcherConfLayout->addWidget(mCbMatchingRefinementMethod,1,1);
    connect(mCbMatchingRefinementMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_cbMatchingRefinementMethod_ItemChanged(int)));
    robustMatcherConfLayout->addWidget(new QLabel("K:"),2,0);
    mDsbMatching_K = new QDoubleSpinBox();
    mDsbMatching_K->setRange(0,1);
    mDsbMatching_K->setSingleStep(0.05);
    mDsbMatching_K->setDecimals(2);
    mDsbMatching_K->setValue(0.8);
    robustMatcherConfLayout->addWidget(mDsbMatching_K,2,1);


    mchRatioTest = new QCheckBox("Ratio: ");
    robustMatcherConfLayout->addWidget(mchRatioTest,3,0);
    mchRatioTest->setChecked(true);
    mDsbMatching_Ratio = new QDoubleSpinBox();
    mDsbMatching_Ratio->setRange(0,1);
    mDsbMatching_Ratio->setSingleStep(0.05);
    mDsbMatching_Ratio->setDecimals(2);
    mDsbMatching_Ratio->setValue(0.85);
    robustMatcherConfLayout->addWidget(mDsbMatching_Ratio,3,1);

    connect(mchRatioTest,SIGNAL(clicked(bool)),mDsbMatching_Ratio,SLOT(setEnabled(bool)));

    mRansacDistConf = new QFrame;
    QGridLayout *ransacDistConfLayout = new QGridLayout();
    ransacDistConfLayout->setContentsMargins(0,0,0,0);
    ransacDistConfLayout->addWidget(new QLabel("Distance:"),4,0);
    mDsbMatching_Distance = new QDoubleSpinBox();
    mDsbMatching_Distance->setRange(0,100);
    mDsbMatching_Distance->setSingleStep(1.00);
    mDsbMatching_Distance->setDecimals(2);
    mDsbMatching_Distance->setValue(3.00);
    ransacDistConfLayout->addWidget(mDsbMatching_Distance,4,1);

    ransacDistConfLayout->addWidget(new QLabel("Confidence:"),5,0);
    mDsbMatching_Confidence = new QDoubleSpinBox();
    mDsbMatching_Confidence->setRange(0,1);
    mDsbMatching_Confidence->setSingleStep(0.01);
    mDsbMatching_Confidence->setDecimals(2);
    mDsbMatching_Confidence->setValue(0.98);
    ransacDistConfLayout->addWidget(mDsbMatching_Confidence,5,1);
    mRansacDistConf->setLayout(ransacDistConfLayout);
    mRansacDistConf->setVisible(false);
    robustMatcherConfLayout->addWidget(mRansacDistConf,4,0,1,2);

    mGbRobustMatcherConf->setLayout(robustMatcherConfLayout);

    featureMatchingLayout->addWidget(mGbRobustMatcherConf,1,0,1,2);

    mPbComputeMatching = new QPushButton("Compute Matching");
    featureMatchingLayout->addWidget(mPbComputeMatching,2,0,1,2);
    connect(mPbComputeMatching,SIGNAL(clicked()),this,SLOT(on_PbComputeMatching_triggered()));

    mGbFeatureMatching->setLayout(featureMatchingLayout);
    ImageDockContentLayout->addWidget(mGbFeatureMatching);

    mGbFeatureMatching->setEnabled(false);

    ImageDockContentLayout->addStretch();
    ImageDockContent->setLayout(ImageDockContentLayout);
    leftDockScrollArea->setWidget(ImageDockContent);

    mDockImageParams->setWidget(leftDockScrollArea);

    //ResultsWidget;
    QFrame *resultsFrame= new QFrame();
    QHBoxLayout *resultsFrameLayout = new QHBoxLayout();
    mGbFeatureDetectionResults = new QGroupBox("Feature detection");
    mGbFeatureDetectionResults->setMinimumWidth(300);

    QGridLayout *featureDetectionResultsLayout = new QGridLayout();
    featureDetectionResultsLayout->setAlignment(Qt::AlignTop);
    featureDetectionResultsLayout->addWidget(new QLabel("Left image detector algorithm: "),0,0);
    mLbLeftDetector = new QLabel("-");
    featureDetectionResultsLayout->addWidget(mLbLeftDetector,0,1);
    featureDetectionResultsLayout->addWidget(new QLabel("Left image detected features: "),1,0);
    mLbLeftFeatures = new QLabel("-");
    featureDetectionResultsLayout->addWidget(mLbLeftFeatures,1,1);
    featureDetectionResultsLayout->addWidget(new QLabel("Right image detector algorithm: "),2,0);
    mLbRightDetector = new QLabel("-");
    featureDetectionResultsLayout->addWidget(mLbRightDetector,2,1);
    featureDetectionResultsLayout->addWidget(new QLabel("Right image detected features: "),3,0);
    mLbRightFeatures = new QLabel("-");
    featureDetectionResultsLayout->addWidget(mLbRightFeatures,3,1);
    featureDetectionResultsLayout->addWidget(new QLabel("Feature descriptor: "),4,0);
    mLbDescriptor = new QLabel("-");
    featureDetectionResultsLayout->addWidget(mLbDescriptor,4,1);


    mGbFeatureDetectionResults->setLayout(featureDetectionResultsLayout);
    resultsFrameLayout->addWidget(mGbFeatureDetectionResults);

    mGbMatchingResults = new QGroupBox("Matching results");
    mGbMatchingResults->setMinimumWidth(300);
    QGridLayout *matchingResultsLayout = new QGridLayout();
    matchingResultsLayout->setAlignment(Qt::AlignTop);
    matchingResultsLayout->addWidget(new QLabel("Brute force matches (L2R): "),0,0);
    mLbBFMatchesL2R = new QLabel("-");
    matchingResultsLayout->addWidget(mLbBFMatchesL2R,0,1);
    matchingResultsLayout->addWidget(new QLabel("Brute force matches (R2L): "),1,0);
    mLbBFMatchesR2L = new QLabel("-");
    matchingResultsLayout->addWidget(mLbBFMatchesR2L,1,1);
    matchingResultsLayout->addWidget(new QLabel("Robust matcher refinement: "),2,0);
    mLbRMMatches = new QLabel("-");
    matchingResultsLayout->addWidget(mLbRMMatches,2,1);

    matchingResultsLayout->addWidget(new QLabel("Ground truth: "),3,0);
    mLbGTAvailable = new QLabel("Not available");
    matchingResultsLayout->addWidget(mLbGTAvailable,3,1);
    matchingResultsLayout->addWidget(new QLabel("Correct matches: "),4,0);
    mLbCorrectMatches = new QLabel("-");
    matchingResultsLayout->addWidget(mLbCorrectMatches,4,1);
    matchingResultsLayout->addWidget(new QLabel("Wrong matches: "),5,0);
    mLbWrongMatches = new QLabel("-");
    matchingResultsLayout->addWidget(mLbWrongMatches,5,1);


    mGbMatchingResults->setLayout(matchingResultsLayout);
    resultsFrameLayout->addWidget(mGbMatchingResults);
    resultsFrameLayout->addStretch();

    QLabel *logoLabel= new QLabel();
    QPixmap logoPix(":/FMELogo.png");

    logoLabel->setPixmap(logoPix.scaledToHeight(QApplication::desktop()->screenGeometry().height()/6,Qt::SmoothTransformation));
    resultsFrameLayout->addWidget(logoLabel);

    resultsFrame->setLayout(resultsFrameLayout);
    mDockResults->setWidget(resultsFrame);

    //CentralWidget
    //Setup matchings viewer

    mMainTabWidget = new QTabWidget;
    mPreprocessingView= new QWidget;
    mHomographyView= new QWidget;

    mKeyPointsView= new QWidget();
    mMatchingsView = new QWidget();
    mCorrectMatchesView=new QWidget();
    mWrongMatchesView= new QWidget();
    mMainTabWidget->addTab(mPreprocessingView,tr("Preprocessing"));
    mMainTabWidget->addTab(mKeyPointsView, tr("Features"));
    mMainTabWidget->addTab(mMatchingsView, tr("Matchings"));
    mMainTabWidget->addTab(mCorrectMatchesView, tr("Correct matchings"));
    mMainTabWidget->addTab(mWrongMatchesView, tr("Wrong matchings"));
    mMainTabWidget->addTab(mHomographyView, tr("Homography"));


    mMainTabWidget->setTabEnabled(1, false);
    mMainTabWidget->setTabEnabled(2, false);
    mMainTabWidget->setTabEnabled(3, false);
    mMainTabWidget->setTabEnabled(4, false);
    mMainTabWidget->setTabEnabled(5, false);


    //PreprocessingTab
    QVBoxLayout *mPreprocessingViewLayout = new QVBoxLayout();
    mPreprocessingViewLayout->setContentsMargins(0,0,0,0);
    mPreprocessingViewer = new MatchingViewer(this);
    mPreprocessingViewLayout->addWidget(mPreprocessingViewer->getView());
    mPreprocessingView->setLayout(mPreprocessingViewLayout);

    //FeaturesTab
    QVBoxLayout *mKeyPointsViewLayout = new QVBoxLayout();
    mKeyPointsViewLayout->setContentsMargins(0,0,0,0);
    mKeyPointsViewer = new MatchingViewer(this);
    mKeyPointsViewLayout->addWidget(mKeyPointsViewer->getView());
    mKeyPointsView->setLayout(mKeyPointsViewLayout);


    QVBoxLayout *mMatchingsViewLayout = new QVBoxLayout();
    mMatchingsViewLayout->setContentsMargins(0,0,0,0);
    mMatchingsViewer = new MatchingViewer(this);
    mMatchingsViewLayout->addWidget(mMatchingsViewer->getView());
    mMatchingsView->setLayout(mMatchingsViewLayout);

    //CorrectMatchesTab
    QVBoxLayout *mCorrectMatchesViewLayout = new QVBoxLayout();
    mCorrectMatchesViewLayout->setContentsMargins(0,0,0,0);
    mCorrectMatchingsViewer = new MatchingViewer(this);
    mCorrectMatchesViewLayout->addWidget(mCorrectMatchingsViewer->getView());
    mCorrectMatchesView->setLayout(mCorrectMatchesViewLayout);

    //wrongMatchesTab
    QVBoxLayout *mWrongMatchesViewLayout = new QVBoxLayout();
    mWrongMatchesViewLayout->setContentsMargins(0,0,0,0);
    mWrongMatchingsViewer = new MatchingViewer(this);
    mWrongMatchesViewLayout->addWidget(mWrongMatchingsViewer->getView());
    mWrongMatchesView->setLayout(mWrongMatchesViewLayout);


    //HomographyTab
    QVBoxLayout *mHomographyViewLayout = new QVBoxLayout();
    mHomographyViewLayout->setContentsMargins(0,0,0,0);
    mHomographyViewer = new MatchingViewer(this);
    mHomographyViewLayout->addWidget(mHomographyViewer->getView());
    mHomographyView->setLayout(mHomographyViewLayout);

    setCentralWidget(mMainTabWidget);

    leftImageLoaded=false;
    rightImageLoaded=false;


    mProgressDialog = new ProgressDialog(this);
    mConsole = new QTextEdit(this);
    QFont* font = new QFont("Courier");
    font->setPixelSize(10);
    mConsole->setFont(*font);
    mConsole->setReadOnly(true);
    mProgressDialog->setConsole(mConsole);

    mImageLeft = new PWImage("");
    mImageRight = new PWImage("");

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

    ui->actionCreate->setEnabled(false);
    ui->actionLoad->setEnabled(false);

    mGTruth=cv::Mat::eye(3, 3, CV_32F);
    ui->menuExport->setEnabled(false);
    ui->actionCorrect_matches->setEnabled(false);
    connect(ui->actionRobust_matches,SIGNAL(triggered()),this,SLOT(on_actionWriteRobustMatches_triggered()));
    connect(ui->actionCorrect_matches,SIGNAL(triggered()),this,SLOT(on_actionWriteCorrectMatches_triggered()));

    this->showMaximized();

}

MainWindowFME::~MainWindowFME()
{
    delete ui;
}

void MainWindowFME::on_actionExit_triggered()
{
    this->close();
}

void MainWindowFME::on_actionLeft_Image_triggered()
{

    QString filters("Image Files (*.png *.jpg *.bmp *.tif)");
    QString defaultFilter ="Image Files (*.png *.jpg *.bmp *.tif)";

    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Open File"), "C://",filters,&defaultFilter);
    if (!selectedFile.isEmpty()) {
        mEvaluatinImage=EVAL_LEFT_IMAGE;
        mLeftImageFileInfo = new QFileInfo(selectedFile);
        mLbLeftImageName->setText(mLeftImageFileInfo->fileName());
        mImageLeft = new PWImage(mLeftImageFileInfo->absoluteFilePath());
        QString imageSize(QString::number(mImageLeft->getSize().width()));
        imageSize.append("x");
        imageSize.append(QString::number(mImageLeft->getSize().height()));
        mLbLeftImageSize->setText(imageSize);
        //        mLeftCheck->show();

        mGtFileInfo= new QFileInfo(mLeftImageFileInfo->absoluteDir().absoluteFilePath("verdad_terreno"));
//        mCvImg_left = cv::imread(mLeftImageFileInfo->absoluteFilePath().toStdString(), CV_LOAD_IMAGE_COLOR);
        //        cv::cvtColor(mCvImg_left,mCvImg_left,CV_BGR2GRAY);

        leftImageLoaded=true;

        mGbFeatureMatching->setEnabled(false);

    }
    QList<QVector<float>> correctMatching_coords;
    mKeyPointsViewer->loadImagesPair(mImageLeft, mImageRight,correctMatching_coords,correctMatching_coords);
    mPreprocessingViewer->loadImagesPair(mImageLeft, mImageRight,correctMatching_coords,correctMatching_coords);

    if (rightImageLoaded && leftImageLoaded) {
        mGbPreprocessing->setEnabled(true);
        //        mGbFeatureDetection->setEnabled(true);
        ui->actionCreate->setEnabled(true);
        ui->actionLoad->setEnabled(true);
    }
}

void MainWindowFME::on_actionRight_Image_triggered()
{
    QString filters("Image Files (*.png *.jpg *.bmp *.tif)");
    QString defaultFilter ="Image Files (*.png *.jpg *.bmp *.tif)";

    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Open File"), "C://",filters,&defaultFilter);
    if (!selectedFile.isEmpty()) {
        mRightImageFileInfo = new QFileInfo(selectedFile);
        mLbRightImageName->setText(mRightImageFileInfo->fileName());
        mImageRight = new PWImage(mRightImageFileInfo->absoluteFilePath());
        QString imageSize(QString::number(mImageRight->getSize().width()));
        imageSize.append("x");
        imageSize.append(QString::number(mImageRight->getSize().height()));
        mLbRightImageSize->setText(imageSize);
        //        mRightCheck->show();

//        mCvImg_right = cv::imread(mRightImageFileInfo->absoluteFilePath().toStdString(), CV_LOAD_IMAGE_COLOR);
        //        cv::cvtColor(mCvImg_right,mCvImg_right,CV_BGR2GRAY);

        rightImageLoaded=true;
        mGbFeatureMatching->setEnabled(false);

    }

    QList<QVector<float>> matching_coords;
    mKeyPointsViewer->loadImagesPair(mImageLeft, mImageRight,matching_coords,matching_coords);
    mPreprocessingViewer->loadImagesPair(mImageLeft, mImageRight,matching_coords,matching_coords);

    if (rightImageLoaded && leftImageLoaded) {
        mGbPreprocessing->setEnabled(true);
        //        mGbFeatureDetection->setEnabled(true);
        ui->actionCreate->setEnabled(true);
        ui->actionLoad->setEnabled(true);
    }
}

void MainWindowFME::on_PbComputeFeatures_triggered(){

    mCvLeft_key.clear();
    mCvRight_key.clear();

    ui->menuExport->setEnabled(false);

    mMainTabWidget->setCurrentIndex(0);

    mMainTabWidget->setTabEnabled(1, false);
    mMainTabWidget->setTabEnabled(2, false);
    mMainTabWidget->setTabEnabled(3, false);
    mMainTabWidget->setTabEnabled(4, false);
    mMainTabWidget->setTabEnabled(5, false);

    //    QList<QVector<float>> correctMatching_coords;
    //    mKeyPointsViewer->loadImagesPair(mImageLeft, mImageRight,correctMatching_coords,correctMatching_coords);

    mProcessContainer = new MultiProcess(true);

    //Left feature detection
    MultiProcess *concurrentFeatureDetectionProcess = new MultiProcess(false);
    switch (mCbLeftDetector->currentIndex()) {
    case DETECTOR_SIFT:
        concurrentFeatureDetectionProcess->appendProcess(new SIFT_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_MSD:
        concurrentFeatureDetectionProcess->appendProcess(new MSD_KPDetProcess(mCvImg_left,mCvLeft_key,mSbMSD_Left_PatchRadius->value(),mSbMSD_Left_AreaRadius->value(),mSbMSD_Left_NMSRadius->value(),mSbMSD_Left_NMSScaleR->value(),mDsbMSD_Left_ThSaliency->value(),mSbMSD_Left_KNN->value(),mDsbMSD_Left_ScaleFactor->value(),mSbMSD_Left_NScales->value(),mCbMSD_Left_ComputeOrientations->isChecked(),mCbMSD_Left_Affine->isChecked(),mSbMSD_Left_AffineTilts->value(),mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_ORB:
        concurrentFeatureDetectionProcess->appendProcess(new ORB_KPDetProcess(mCvImg_left,mCvLeft_key,mOrbKpLeft->value(),mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_SURF:
        concurrentFeatureDetectionProcess->appendProcess(new SURF_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_FAST:
        concurrentFeatureDetectionProcess->appendProcess(new FAST_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_GFTT:
        concurrentFeatureDetectionProcess->appendProcess(new GFTT_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_MSER:
        concurrentFeatureDetectionProcess->appendProcess(new MSER_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    case DETECTOR_BRISK:
        concurrentFeatureDetectionProcess->appendProcess(new BRISK_KPDetProcess(mCvImg_left,mCvLeft_key,mLeftImageFileInfo->fileName()));
        break;
    }

    //Right feature detection
    switch (mCbRightDetector->currentIndex()) {
    case DETECTOR_SIFT:
        concurrentFeatureDetectionProcess->appendProcess(new SIFT_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_MSD:
        concurrentFeatureDetectionProcess->appendProcess(new MSD_KPDetProcess(mCvImg_right,mCvRight_key,mSbMSD_Right_PatchRadius->value(),mSbMSD_Right_AreaRadius->value(),mSbMSD_Right_NMSRadius->value(),mSbMSD_Right_NMSScaleR->value(),mDsbMSD_Right_ThSaliency->value(),mSbMSD_Right_KNN->value(),mDsbMSD_Right_ScaleFactor->value(),mSbMSD_Right_NScales->value(),mCbMSD_Right_ComputeOrientations->isChecked(),mCbMSD_Right_Affine->isChecked(),mSbMSD_Right_AffineTilts->value(),mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_ORB:
        concurrentFeatureDetectionProcess->appendProcess(new ORB_KPDetProcess(mCvImg_right,mCvRight_key,mOrbKpRight->value(),mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_SURF:
        concurrentFeatureDetectionProcess->appendProcess(new SURF_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_FAST:
        concurrentFeatureDetectionProcess->appendProcess(new FAST_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_GFTT:
        concurrentFeatureDetectionProcess->appendProcess(new GFTT_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_MSER:
        concurrentFeatureDetectionProcess->appendProcess(new MSER_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    case DETECTOR_BRISK:
        concurrentFeatureDetectionProcess->appendProcess(new BRISK_KPDetProcess(mCvImg_right,mCvRight_key,mRightImageFileInfo->fileName()));
        break;
    }
    mProcessContainer->appendProcess(concurrentFeatureDetectionProcess);

    //Feature description
    MultiProcess *concurrentFeatureDescriptionProcess = new MultiProcess(false);

    switch (mCbDescriptor->currentIndex()) {
    case DESCRIPTOR_SIFT:
        concurrentFeatureDescriptionProcess->appendProcess(new SIFT_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new SIFT_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_ORB:
        concurrentFeatureDescriptionProcess->appendProcess(new ORB_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new ORB_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_SURF:
        concurrentFeatureDescriptionProcess->appendProcess(new SUFT_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new SUFT_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_HOG:
        concurrentFeatureDescriptionProcess->appendProcess(new HOG_KPDescProcess(mCvImg_left,mCvImg_right,mCvLeft_key,mCvRight_key,mCvLeft_Desc,mCvRight_Desc,16,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_MUTUALINFORMATION:
        concurrentFeatureDescriptionProcess->appendProcess(new MutualInformation_KPDescProcess(mCvImg_left,mCvImg_right,mCvLeft_key,mCvRight_key,mMatchesL2R,mMatchesR2L,16,40,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_MTM_PWC:
        concurrentFeatureDescriptionProcess->appendProcess(new MTM_KPDescProcess(mCvImg_left,mCvImg_right,mCvLeft_key,mCvRight_key,mMatchesL2R,mMatchesR2L,16,40,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_LSS:
        concurrentFeatureDescriptionProcess->appendProcess(new LSS_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new LSS_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_DAISY:
        concurrentFeatureDescriptionProcess->appendProcess(new DAISY_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new DAISY_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_FREAK:
        concurrentFeatureDescriptionProcess->appendProcess(new FREAK_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new FREAK_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_LATCH:
        concurrentFeatureDescriptionProcess->appendProcess(new LATCH_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new LATCH_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_BRISK:
        concurrentFeatureDescriptionProcess->appendProcess(new BRISK_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new BRISK_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    case DESCRIPTOR_BRIEF:
        concurrentFeatureDescriptionProcess->appendProcess(new BRIEF_KPDescProcess(mCvImg_left,mCvLeft_key,mCvLeft_Desc,mLeftImageFileInfo->fileName()));
        concurrentFeatureDescriptionProcess->appendProcess(new BRIEF_KPDescProcess(mCvImg_right,mCvRight_key,mCvRight_Desc,mRightImageFileInfo->fileName()));
        break;
    }

    mProcessContainer->appendProcess(concurrentFeatureDescriptionProcess);
    connect(mProcessContainer, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProcessContainer, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_FeatureDetectionAndDescriptionFinished()));

    connect(mProcessContainer, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Computing Features...");
    mProgressDialog->setStatusText("Computing Features...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mProcessContainer->start();
}

void MainWindowFME::on_FeatureDetectionAndDescriptionFinished(){
    if (!mProcessContainer->isStopped()) {
        writeKeyPoints("KeyPointsLeft.txt",mCvLeft_key);
        writeKeyPoints("KeyPointsRight.txt",mCvRight_key);

        if (mCbDescriptor->currentIndex()==DESCRIPTOR_MUTUALINFORMATION|| mCbDescriptor->currentIndex()==DESCRIPTOR_MTM_PWC) {
            mCbMatchingMethod->setCurrentIndex(MATCHINGMETHOD_BF);
            mCbMatchingMethod->setEnabled(false);
        }else {
            mCbMatchingMethod->setEnabled(true);
        }
        mKeyPointsViewer->loadImagesPair(mImageLeft, mImageRight,mCvLeft_key,mCvRight_key);
        showFeatureDetectionResults();
        mGbFeatureMatching->setEnabled(true);
        mMainTabWidget->setCurrentIndex(1);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setFinished(true);
        mProgressDialog->setStatusText(tr("Feature detection and description finished."));

    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));
    disconnect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_FeatureDetectionAndDescriptionFinished()));

}

void MainWindowFME::on_actionAbout_FME_triggered()
{
    AboutFME *about =new  AboutFME(this);

    about->exec();
}
void MainWindowFME::on_PbComputeMatching_triggered(){
    mCorrectMatches.clear();
    mWrongMatches.clear();


    mProcessContainer = new MultiProcess(true);
    float ratioVal=-1;

    switch (mCbMatchingMethod->currentIndex()) {
    case MATCHINGMETHOD_BF:
        if (mCbDescriptor->currentIndex()!=DESCRIPTOR_MUTUALINFORMATION && mCbDescriptor->currentIndex()!=DESCRIPTOR_MTM_PWC) {
            mMatchesL2R.clear();
            mMatchesR2L.clear();
            mProcessContainer->appendProcess(new BFMatcherProcess(mCvLeft_Desc,mCvRight_Desc,mMatchesL2R,mMatchesR2L,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName()));
        }
        if (mchRatioTest->isChecked()) {
            ratioVal=mDsbMatching_Ratio->value();
        }

        mProcessContainer->appendProcess(new RobustMatcherRefinementProcess(mCvImg_left,mCvImg_right,mCvLeft_key,mCvRight_key,mMatchesL2R,mMatchesR2L,mCorrectMatches,mWrongMatches,mCbMatchingRefinementMethod->currentIndex(),mDsbMatching_K->value(),ratioVal,mDsbMatching_Distance->value(),mDsbMatching_Confidence->value(),mCbDescriptor->currentIndex()==DESCRIPTOR_MUTUALINFORMATION,mHaveGroundTrugh,mGTruth,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName(),mRightImageFileInfo->absoluteDir()));
        break;
    case MATCHINGMETHOD_FLANN:
        mProcessContainer->appendProcess(new FLANNMatcherProcess(mCvImg_left,mCvImg_right,mCvLeft_key,mCvRight_key,mCvLeft_Desc,mCvRight_Desc,mCorrectMatches,mWrongMatches,mHaveGroundTrugh,mGTruth,mLeftImageFileInfo->fileName(),mRightImageFileInfo->fileName()));
        break;
    }

    connect(mProcessContainer, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProcessContainer, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_FeatureMatchingFinished()));

    connect(mProcessContainer, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Matching Features...");
    mProgressDialog->setStatusText("Matching Features...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mProcessContainer->start();
}
void MainWindowFME::on_FeatureMatchingFinished(){
    if (!mProcessContainer->isStopped()) {
        showMatchingResults();
        mHomography = new PWImage(mLeftImageFileInfo->absoluteDir().absoluteFilePath("homography.png"));

        QList<QVector<float>> tmp;
        mHomographyViewer->loadImagesPair(mHomography, new PWImage(""),tmp,tmp);

        mMainTabWidget->setTabEnabled(5, true);
        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setFinished(true);
        mProgressDialog->setStatusText(tr("Feature matching finished."));
        ui->menuExport->setEnabled(true);
        if (mHaveGroundTrugh) {
            ui->actionCorrect_matches->setEnabled(true);
        }
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));
    disconnect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_FeatureMatchingFinished()));
    showMatches();
}

void MainWindowFME::showMatches(){
    QList<QVector<float>> correctMatching_coords,wrongMatching_coords,aux;
    //loadCorrectMatches
    foreach (cv::DMatch evaluatedMatch, mCorrectMatches) {
        QVector<float> match;
        match.append(mCvLeft_key.at(evaluatedMatch.queryIdx).pt.x);
        match.append(mCvLeft_key.at(evaluatedMatch.queryIdx).pt.y);
        match.append(mCvRight_key.at(evaluatedMatch.trainIdx).pt.x);
        match.append(mCvRight_key.at(evaluatedMatch.trainIdx).pt.y);
        match.append(0);
        correctMatching_coords.append(match);
    }

    if (mHaveGroundTrugh) {
        //loadWrongMatches
        foreach (cv::DMatch evaluatedMatch, mWrongMatches) {
            QVector<float> match;
            match.append(mCvLeft_key.at(evaluatedMatch.queryIdx).pt.x);
            match.append(mCvLeft_key.at(evaluatedMatch.queryIdx).pt.y);
            match.append(mCvRight_key.at(evaluatedMatch.trainIdx).pt.x);
            match.append(mCvRight_key.at(evaluatedMatch.trainIdx).pt.y);
            match.append(0);
            wrongMatching_coords.append(match);
        }
        mCorrectMatchingsViewer->loadImagesPair(mImageLeft, mImageRight,correctMatching_coords,aux);
        mWrongMatchingsViewer->loadImagesPair(mImageLeft, mImageRight,aux,wrongMatching_coords);
        mMainTabWidget->setTabEnabled(3, true);
        mMainTabWidget->setTabEnabled(4, true);
        mMainTabWidget->setTabEnabled(5, false);

    }
    mMainTabWidget->setTabEnabled(2, true);
    mMatchingsViewer->loadImagesPair(mImageLeft, mImageRight,correctMatching_coords,wrongMatching_coords);
    mMainTabWidget->setCurrentIndex(2);
}

void MainWindowFME::on_LeftImageFeatureDetector_ItemChanged(int currentItem){
    switch (currentItem) {
    case 0:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->hide();
        break;
    case 1:
        mMSDconf_LeftImage->show();
        mORBconf_LeftImage->hide();
        break;
    case 2:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->show();
        break;
    case 3:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->hide();
        break;
    case 4:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->hide();
        break;
    case 5:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->hide();
        break;
    case 6:
        mMSDconf_LeftImage->hide();
        mORBconf_LeftImage->hide();
        break;
    default:
        break;
    }
}
void MainWindowFME::on_RightImageFeatureDetector_ItemChanged(int currentItem){
    switch (currentItem) {
    case 0:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->hide();

        break;
    case 1:
        mMSDconf_RightImage->show();
        mORBconf_RightImage->hide();

        break;
    case 2:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->show();
        break;
    case 3:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->hide();
        break;
    case 4:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->hide();
        break;
    case 5:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->hide();
        break;
    case 6:
        mMSDconf_RightImage->hide();
        mORBconf_RightImage->hide();
        break;
    default:
        break;
    }
}

void MainWindowFME::showFeatureDetectionResults(){
    mLbLeftDetector->setText(mCbLeftDetector->currentText());
    QString leftFeaturesText(QString::number(mCvLeft_key.size()));
    leftFeaturesText.append(" features");
    mLbLeftFeatures->setText(leftFeaturesText);
    mLbRightDetector->setText(mCbRightDetector->currentText());
    QString rightFeaturesText(QString::number(mCvRight_key.size()));
    rightFeaturesText.append(" features");
    mLbRightFeatures->setText(rightFeaturesText);
    mLbDescriptor->setText(mCbDescriptor->currentText());
    mMainTabWidget->setTabEnabled(1, true);

}

void MainWindowFME::showMatchingResults(){
    QString matchesL2RText(QString::number(mMatchesL2R.size()*2));
    matchesL2RText.append(" matches");
    mLbBFMatchesL2R->setText(matchesL2RText);

    QString matchesR2LText(QString::number(mMatchesR2L.size()*2));
    matchesR2LText.append(" matches");
    mLbBFMatchesR2L->setText(matchesR2LText);

    QString matchesRBText(QString::number(mCorrectMatches.size()+mWrongMatches.size()));
    matchesRBText.append(" matches");
    mLbRMMatches->setText(matchesRBText);

    QString matchesCorrectText(QString::number(mCorrectMatches.size()));
    matchesCorrectText.append(" matches");
    mLbCorrectMatches->setText(matchesCorrectText);

    QString matchesWrongText(QString::number(mWrongMatches.size()));
    matchesWrongText.append(" matches");
    mLbWrongMatches->setText(matchesWrongText);

}

void MainWindowFME::on_actionLoad_triggered()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, tr("Open File"), "C://");
    if (!selectedFile.isEmpty()) {

        FileStorage fs;
        fs.open(selectedFile.toStdString(), FileStorage::READ);
        fs["matrix"] >> mGTruth;
        mHaveGroundTrugh=true;
        mLbGTAvailable->setText("Available");

        cv::Mat salida;
        cv::warpPerspective(mCvImg_right, salida, mGTruth.inv(), mCvImg_left.size(), cv::INTER_LINEAR);//affine transformation;
        cv::Mat merged;
        cv::addWeighted(mCvImg_left, 0.5, salida, 0.3, 0.0, merged);

        cvNamedWindow("Result", 2);
        imshow("Result", merged);
    }

    QList<QVector<float>> matching_coords;
    mKeyPointsViewer->loadImagesPair(mImageLeft, mImageRight,matching_coords,matching_coords);

    if (rightImageLoaded && leftImageLoaded) {
        mGbFeatureDetection->setEnabled(true);
    }
}

void MainWindowFME::on_actionCreate_triggered()
{
    if (mGtFileInfo->exists()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Previous results", "Previous results will be removed.<br>Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    if (mGtFileInfo->exists()) {
        QFile(mGtFileInfo->absoluteFilePath()).remove();
    }
    mProcessContainer = new MultiProcess(true);

    mProcessContainer->appendProcess(new GrountTruthBuilderProcess(mLeftImageFileInfo,mRightImageFileInfo));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_GroundTruthBuilderProcess_finished()));
    mProcessContainer->start();
}

void MainWindowFME::on_GroundTruthBuilderProcess_finished(){
    FileStorage fs;
    if(fs.open(mGtFileInfo->absoluteFilePath().toStdString(), FileStorage::READ)){
        fs["matrix"] >> mGTruth;
        mHaveGroundTrugh=true;
        mLbGTAvailable->setText("Available");

        cv::Mat salida;
        cv::warpPerspective(mCvImg_right, salida, mGTruth.inv(), mCvImg_left.size(), cv::INTER_LINEAR);//affine transformation;
        cv::Mat merged;
        cv::addWeighted(mCvImg_left, 0.5, salida, 0.3, 0.0, merged);

        cvNamedWindow("Result", 2);
        imshow("Result", merged);
        mLbGTAvailable->setText("Available");
        mHaveGroundTrugh=true;
    }else {
        mLbGTAvailable->setText("Not Available");
    }
}

void MainWindowFME::manageProccesStdOutput(QString message){

    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    mProgressDialog->writeinConsole(dateTimeString+" - "+message);
}

void MainWindowFME::on_cbMatchingMethod_ItemChanged(int currentItem){
    if (currentItem==MATCHINGMETHOD_BF) {
        mGbRobustMatcherConf->setVisible(true);
    }else {
        mGbRobustMatcherConf->setVisible(false);
    }
}


void MainWindowFME::on_writeMatches_Finished(){
    if (!mProcessContainer->isStopped()) {
        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setFinished(true);
        mProgressDialog->setStatusText(tr("Feature matching finished."));
        mProgressDialog->close();
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));
    disconnect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_writeMatches_Finished()));
}

void MainWindowFME::on_actionWriteRobustMatches_triggered()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "C://",
                                                    tr("Text File (*.txt)"));
    mProcessContainer = new MultiProcess(true);

    mProcessContainer->appendProcess(new WriteMatchesToAperoProcess(fileName,mCvLeft_key,mCvRight_key,mCorrectMatches));
    mProcessContainer->appendProcess(new WriteMatchesToAperoProcess(fileName,mCvLeft_key,mCvRight_key,mWrongMatches));

    connect(mProcessContainer, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProcessContainer, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_writeMatches_Finished()));

    connect(mProcessContainer, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Writing matches...");
    mProgressDialog->setStatusText("Writing matches...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mProcessContainer->start();
}
void MainWindowFME::on_actionWriteCorrectMatches_triggered(){

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "C://",
                                                    tr("Text File (*.txt)"));
    mProcessContainer = new MultiProcess(true);

    mProcessContainer->appendProcess(new WriteMatchesToAperoProcess(fileName,mCvLeft_key,mCvRight_key,mCorrectMatches));

    connect(mProcessContainer, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProcessContainer, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_writeMatches_Finished()));

    connect(mProcessContainer, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Writing matches...");
    mProgressDialog->setStatusText("Writing matches...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mProcessContainer->start();
}

void MainWindowFME::on_actionDisplacement_map_triggered()
{

}

void MainWindowFME::on_cbMatchingRefinementMethod_ItemChanged(int currentItem){
    if (currentItem==1) {
        mRansacDistConf->setVisible(true);
    }else {
        mRansacDistConf->setVisible(false);
    }
}

void MainWindowFME::on_PbComputePreprocessing_triggered(){


    //Remove previous preprocessing image

    QFile::remove(mLeftImageFileInfo->absoluteDir().absoluteFilePath("leftPreprocessed.png"));
    QFile::remove(mLeftImageFileInfo->absoluteDir().absoluteFilePath("rightPreprocessed.png"));

    mMainTabWidget->setCurrentIndex(0);

    mMainTabWidget->setTabEnabled(1, false);
    mMainTabWidget->setTabEnabled(2, false);
    mMainTabWidget->setTabEnabled(3, false);
    mMainTabWidget->setTabEnabled(4, false);
    mMainTabWidget->setTabEnabled(5, false);
    mCvImg_left = cv::imread(mLeftImageFileInfo->absoluteFilePath().toStdString(), CV_LOAD_IMAGE_COLOR);
    mCvImg_right = cv::imread(mRightImageFileInfo->absoluteFilePath().toStdString(), CV_LOAD_IMAGE_COLOR);

    mCvLeft_key.clear();

    mCvRight_key.clear();

    mProcessContainer = new MultiProcess(true);
    if (mChDownsampleImages->isChecked()) {
        mProcessContainer->appendProcess(new Downsample_Process(mCvImg_left,mCvImg_right,mSbDownsamplingMaxSize->value()));
    }

    switch (mCbPreprocessingAlgorithm->currentIndex()) {
    case PREP_CONTRAST_PRESERVING_DECOLOR:
        mProcessContainer->appendProcess(new ContrastPreservingDecolorization__Process(mCvImg_left,mCvImg_right,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_WALLIS:
        mProcessContainer->appendProcess(new WallisFilter_Process(mCvImg_left,mCvImg_right,mDsbWallis_Contrast->value(),mDsbWallis_Brightness->value(),mSbWallis_ImposedAverage->value(),mSbWallis_ImposedLocalStandardDeviation->value(),mSbWallis_KernelSize->value(),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_LCE_BSESCS2014:
        mProcessContainer->appendProcess(new LCE_BSESCS2014_Process(mCvImg_left,mCvImg_right,cv::Size(33,33),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Raju_Nair2014:
        mProcessContainer->appendProcess(new RajuNair2014_Process(mCvImg_left,mCvImg_right,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Lal2014:
        mProcessContainer->appendProcess(new Lal2014_Process(mCvImg_left,mCvImg_right,cv::Size(8,8),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_MSRCP2014:
        mProcessContainer->appendProcess(new MSRCP2014_Process(mCvImg_left,mCvImg_right,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Wang_Zheng_Hu_Li2013:
        mProcessContainer->appendProcess(new Wang_Zheng_Hu_Li2013_Process(mCvImg_left,mCvImg_right,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_POHE2013:
        mProcessContainer->appendProcess(new POHE2013_Process(mCvImg_left,mCvImg_right,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Kimori2013:
        mProcessContainer->appendProcess(new Kimori2013_Process(mCvImg_left,mCvImg_right,cv::Size(9,9),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Celik_Tjahjadi2012:
        mProcessContainer->appendProcess(new CelikTjahjadi2012_Process(mCvImg_left,mCvImg_right,4,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Liu_Jin_Chen_Liu_Li2011:
        mProcessContainer->appendProcess(new LiuJinChenLiuLi2011_Process(mCvImg_left,mCvImg_right,cv::Size(9,9),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Sundarami2011:
        mProcessContainer->appendProcess(new Sundarami2011_Process(mCvImg_left,mCvImg_right,cv::Size(17,17),0.03f,0.5f,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Mary_Kim2008:
        mProcessContainer->appendProcess(new MaryKim2008_Process(mCvImg_left,mCvImg_right,1,2,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Wadud_Kabir_Dewan_Chae2007:
        mProcessContainer->appendProcess(new WadudKabirDewanChae2007_Process(mCvImg_left,mCvImg_right,5,mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_FAHE2006:
        mProcessContainer->appendProcess(new FAHE2006_Process(mCvImg_left,mCvImg_right,cv::Size(11,11),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Lamberti_Montrucchio_Sanna2006:
        mProcessContainer->appendProcess(new LambertiMontrucchioSanna2006_Process(mCvImg_left,mCvImg_right,cv::Size(11,11),cv::Size(44,44),mLeftImageFileInfo->absoluteDir()));
        break;
    case PREP_Yu_Bajaj2004:
        mProcessContainer->appendProcess(new YuBajaj2004_Process(mCvImg_left,mCvImg_right,cv::Size(11,11),1,false,0.1,mLeftImageFileInfo->absoluteDir()));
        break;


    }

    connect(mProcessContainer, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProcessContainer, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_ImagePreprocessing_Finished()));

    connect(mProcessContainer, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Preprocessing images...");
    mProgressDialog->setStatusText("Preprocessing images...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mProcessContainer->start();
}

void MainWindowFME::on_ImagePreprocessing_Finished(){

    if (!mProcessContainer->isStopped() && QFile(mLeftImageFileInfo->absoluteDir().absoluteFilePath("leftPreprocessed.png")).exists() && QFile(mLeftImageFileInfo->absoluteDir().absoluteFilePath("rightPreprocessed.png")).exists()) {
        mImageLeft = new PWImage(mLeftImageFileInfo->absoluteDir().absoluteFilePath("leftPreprocessed.png"));
        mImageRight = new PWImage(mLeftImageFileInfo->absoluteDir().absoluteFilePath("rightPreprocessed.png"));

        QString imageSizeLeft(QString::number(mImageLeft->getSize().width()));
        imageSizeLeft.append("x");
        imageSizeLeft.append(QString::number(mImageLeft->getSize().height()));
        mLbLeftImageSize->setText(imageSizeLeft);

        QString imageSizeRight(QString::number(mImageRight->getSize().width()));
        imageSizeRight.append("x");
        imageSizeRight.append(QString::number(mImageRight->getSize().height()));
        mLbRightImageSize->setText(imageSizeRight);

        mPreprocessingViewer->loadImagesPair(mImageLeft, mImageRight,mCvLeft_key,mCvRight_key);
        mGbFeatureDetection->setEnabled(true);
        mMainTabWidget->setCurrentIndex(0);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setFinished(true);
        mProgressDialog->setStatusText(tr("Image preprocessing finished."));

    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mProcessContainer,SLOT(stop()));
    disconnect(mProcessContainer, SIGNAL(finished()),this,SLOT(on_ImagePreprocessing_Finished()));
}

void MainWindowFME::on_Preprocessing_ItemChanged(int currentItem){
    switch (currentItem) {
    case 0:
        mWallisConf->hide();

        break;
    case 1:
        mWallisConf->show();

        break;
    case 2:
        mWallisConf->hide();

        break;
    case 3:
        mWallisConf->hide();

        break;
    case 4:
        mWallisConf->hide();

        break;
    case 5:
        mWallisConf->hide();

        break;
    case 6:
        mWallisConf->hide();

        break;
    case 7:
        mWallisConf->hide();

        break;
    case 8:
        mWallisConf->hide();

        break;
    case 9:
        mWallisConf->hide();

        break;
    case 10:
        mWallisConf->hide();

        break;
    case 11:
        mWallisConf->hide();

        break;
    case 12:
        mWallisConf->hide();

        break;
    default:
        break;
    }
}

void MainWindowFME::writeKeyPoints(QString filename, std::vector<cv::KeyPoint>& keyPoints){
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "x\ty\tangle\tresponse" << endl;

        for (int i = 0; i < keyPoints.size(); ++i) {
            stream << QString::number(keyPoints[i].pt.x) <<"\t"<< QString::number(keyPoints[i].pt.y) << "\t"<< QString::number(keyPoints[i].angle) << "\t" << QString::number(keyPoints[i].response) << endl;
        }
    }
}
