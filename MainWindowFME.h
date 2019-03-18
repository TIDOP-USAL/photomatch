#ifndef MAINWINDOWFME_H
#define MAINWINDOWFME_H

#define MAINWINDOWFME_PROGRAM_NAME         "FME"
#define MAINWINDOWFME_PROGRAM_TAG          "FME"
#define MAINWINDOWFME_VERSION              "1.0"
#define MAINWINDOWFME_BUILD_NUMBER         "3"
#define MAINWINDOWFME_RELEASE_TYPE         "(Release)"


#define PREP_CONTRAST_PRESERVING_DECOLOR    0
#define PREP_WALLIS                         1
#define PREP_LCE_BSESCS2014                 2
#define PREP_Raju_Nair2014                   3
#define PREP_Lal2014                        4
#define PREP_MSRCP2014                      5
#define PREP_Wang_Zheng_Hu_Li2013              6
#define PREP_POHE2013                       7
#define PREP_Kimori2013                     8
#define PREP_Celik_Tjahjadi2012              9
#define PREP_Liu_Jin_Chen_Liu_Li2011            10
#define PREP_Sundarami2011                  11
#define PREP_Mary_Kim2008                    12
#define PREP_Wadud_Kabir_Dewan_Chae2007        13
#define PREP_FAHE2006                       14
#define PREP_Lamberti_Montrucchio_Sanna2006   15
#define PREP_Yu_Bajaj2004                    16
#define PREP_Kim_Kim_Hwang2001                17
#define PREP_Stark2000                      18
#define PREP_MSRCR1997                      19
#define PREP_Global_Histogram_Equalization1992    20
#define PREP_AHE1974                        21
#define PREP_CLAHE1987                      22
#define PREP_CLAHEnon1987                   23
#define PREP_Simplest_Color_Balance           24

#define DETECTOR_SIFT                       0
#define DETECTOR_MSD                        1
#define DETECTOR_ORB                        2
#define DETECTOR_SURF                       3
#define DETECTOR_FAST                       4
#define DETECTOR_GFTT                       5
#define DETECTOR_MSER                       6
#define DETECTOR_BRISK                      7

#define DESCRIPTOR_SIFT                      0
#define DESCRIPTOR_ORB                       1
#define DESCRIPTOR_SURF                      2
#define DESCRIPTOR_HOG                       3
#define DESCRIPTOR_MUTUALINFORMATION         4
#define DESCRIPTOR_MTM_PWC                   5
#define DESCRIPTOR_LSS                       6
#define DESCRIPTOR_DAISY                     7
#define DESCRIPTOR_FREAK                     8
#define DESCRIPTOR_LATCH                     9
#define DESCRIPTOR_BRISK                     10
#define DESCRIPTOR_BRIEF                     11


#define MATCHINGMETHOD_BF                    0
#define MATCHINGMETHOD_FLANN                 1

#define MATCHINGREFINEMENT_LMSE             0
#define MATCHINGREFINEMENT_RANSAC           1
#define MATCHINGREFINEMENT_8POINT           2


#define EVAL_LEFT_IMAGE                     0
#define EVAL_RIGHT_IMAGE                    1

#include <QMainWindow>
#include <QDockWidget>
#include <MatchingViewer/MatchingViewer.h>
#include <QFileInfo>
#include <MatchingViewer/PWImage.h>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "opencv/cv.hpp"

#include "ProgressDialog.h"
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QTabWidget>
#include <QCheckBox>

//#include "SIFT/SIFT_KPDescProcess.h"
//#include "SIFT/SIFT_KPDetProcess.h"
//#include "MSD/MSD_KPDetProcess.h"
//#include "ORB/ORB_KPDetProcess.h"
//#include "ORB/ORB_KPDescProcess.h"
//#include "SURF/SURF_KPDetProcess.h"
//#include "SURF/SUFT_KPDescProcess.h"
#include "ProcessManager/MultiProcess.h"

namespace Ui {
class MainWindowFME;
}

class MainWindowFME : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowFME(QWidget *parent = 0);
    ~MainWindowFME();

private slots:
    void on_actionExit_triggered();

    void on_actionLeft_Image_triggered();

    void on_actionRight_Image_triggered();

private:
    bool mHaveGroundTrugh;
    int mEvaluatinImage;
    Ui::MainWindowFME *ui;
    ProgressDialog *mProgressDialog;
    QTextEdit *mConsole;
    //    QLabel *mLeftCheck,*mRightCheck;
    QFrame *mRansacDistConf;
    QCheckBox *mchRatioTest;
    QLabel *mLbLeftDetector,*mLbRightDetector,*mLbDescriptor, *mLbLeftFeatures,*mLbRightFeatures;
    QLabel *mLbBFMatchesL2R, *mLbBFMatchesR2L, *mLbRMMatches,*mLbCorrectMatches, *mLbWrongMatches,*mLbGTAvailable;
    QDockWidget *mDockImageParams, *mDockResults;
    QGroupBox *mMSDconf_LeftImage,*mMSDconf_RightImage;
    QGroupBox *mORBconf_LeftImage,*mORBconf_RightImage;
    QGroupBox *mGbRobustMatcherConf;
    QGroupBox *mGbFeatureDetectionResults,*mGbMatchingResults;
    QGroupBox *mWallisConf;
    MatchingViewer *mPreprocessingViewer,*mKeyPointsViewer,*mMatchingsViewer,*mCorrectMatchingsViewer,*mWrongMatchingsViewer,*mHomographyViewer;

    QFileInfo *mLeftImageFileInfo, *mRightImageFileInfo;
    PWImage *mImageLeft,*mImageRight,*mHomography;
    bool leftImageLoaded, rightImageLoaded;
    QGroupBox *mGbPreprocessing,*mGbLeftImageInfo, *mGbRightImageInfo, *mGbFeatureDetection, *mGbFeatureMatching;
    QLabel *mLbLeftImageName,*mLbRightImageName,*mLbLeftImageSize,*mLbRightImageSize;
    QPushButton *mPbComputePreprocessing,*mPbComputeFeatures,*mPbComputeMatching;
    QComboBox *mCbPreprocessingAlgorithm,*mCbLeftDetector,*mCbDescriptor,*mCbRightDetector, *mCbMatchingRefinementMethod,*mCbMatchingMethod;
    QDoubleSpinBox *mDsbMatching_K,*mDsbMatching_Ratio, *mDsbMatching_Distance, *mDsbMatching_Confidence;

    QDoubleSpinBox *mDsbMSD_Left_ScaleFactor, *mDsbMSD_Left_ThSaliency;
    QSpinBox *mSbDownsamplingMaxSize;
    QCheckBox *mChDownsampleImages;
    QSpinBox *mSbMSD_Left_PatchRadius, *mSbMSD_Left_AreaRadius, *mSbMSD_Left_NMSRadius, *mSbMSD_Left_NMSScaleR, *mSbMSD_Left_KNN, *mSbMSD_Left_NScales, *mSbMSD_Left_AffineTilts;
    QCheckBox *mCbMSD_Left_ComputeOrientations, *mCbMSD_Left_Affine;

    QDoubleSpinBox *mDsbMSD_Right_ScaleFactor, *mDsbMSD_Right_ThSaliency;
    QSpinBox *mSbMSD_Right_PatchRadius, *mSbMSD_Right_AreaRadius, *mSbMSD_Right_NMSRadius, *mSbMSD_Right_NMSScaleR, *mSbMSD_Right_KNN, *mSbMSD_Right_NScales, *mSbMSD_Right_AffineTilts;
    QCheckBox *mCbMSD_Right_ComputeOrientations, *mCbMSD_Right_Affine;


    //Wallis values
    QDoubleSpinBox *mDsbWallis_Contrast, *mDsbWallis_Brightness;
    QSpinBox *mSbWallis_ImposedAverage, *mSbWallis_ImposedLocalStandardDeviation, *mSbWallis_KernelSize;



    QTabWidget *mMainTabWidget;
    QWidget *mPreprocessingView,*mKeyPointsView,*mMatchingsView,*mCorrectMatchesView,*mWrongMatchesView,*mHomographyView;

    QSpinBox *mOrbKpLeft,*mOrbKpRight;

    cv::Mat mGTruth;
    QFileInfo *mGtFileInfo;
    //Feature variables
    cv::Mat mCvImg_left;
    cv::Mat mCvImg_right;
    std::vector<cv::KeyPoint> mCvLeft_key;
    std::vector<cv::KeyPoint> mCvRight_key;
    cv::Mat mCvLeft_Desc;
    cv::Mat mCvRight_Desc;
    std::vector<std::vector<cv::DMatch>> mMatchesL2R;
    std::vector<std::vector<cv::DMatch>> mMatchesR2L;
    std::vector<cv::DMatch> mCorrectMatches;
    std::vector<cv::DMatch> mWrongMatches;

    MultiProcess *mProcessContainer;


    void showMatches();
    void showFeatureDetectionResults();
    void showMatchingResults();

    void writeKeyPoints(QString filename, std::vector<cv::KeyPoint>& keyPoints);
private slots:
    void on_PbComputePreprocessing_triggered();
    void on_PbComputeFeatures_triggered();
    void on_PbComputeMatching_triggered();

    void on_ImagePreprocessing_Finished();
    void on_FeatureDetectionAndDescriptionFinished();
    void on_actionAbout_FME_triggered();
    void on_FeatureMatchingFinished();
    void on_LeftImageFeatureDetector_ItemChanged(int currentItem);
    void on_RightImageFeatureDetector_ItemChanged(int currentItem);

    void on_actionLoad_triggered();
    void on_actionCreate_triggered();
    void on_GroundTruthBuilderProcess_finished();
    void manageProccesStdOutput(QString message);
    void on_cbMatchingMethod_ItemChanged(int currentItem);
    void on_writeMatches_Finished();
    void on_actionWriteRobustMatches_triggered();
    void on_actionWriteCorrectMatches_triggered();
    void on_actionDisplacement_map_triggered();
    void on_cbMatchingRefinementMethod_ItemChanged(int currentItem);
    void on_Preprocessing_ItemChanged(int currentItem);
};

#endif // MAINWINDOWFME_H
