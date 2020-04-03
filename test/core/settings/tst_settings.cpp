#include <QtTest>

#include "photomatch/core/settings.h"
#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/boost.h"
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/vgg.h"
#include "photomatch/core/features/matcher.h"

#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/preprocess/clahe.h"
#include "photomatch/core/preprocess/cmbfhe.h"
#include "photomatch/core/preprocess/dhe.h"
#include "photomatch/core/preprocess/fahe.h"
#include "photomatch/core/preprocess/hmclahe.h"
#include "photomatch/core/preprocess/lce_bsescs.h"
#include "photomatch/core/preprocess/msrcp.h"
#include "photomatch/core/preprocess/noshp.h"
#include "photomatch/core/preprocess/pohe.h"
#include "photomatch/core/preprocess/rswhe.h"
#include "photomatch/core/preprocess/wallis.h"

using namespace photomatch;

class TestSettings : public QObject
{
  Q_OBJECT

public:
  TestSettings();
  ~TestSettings();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_language_data();
  void test_language();
  void test_historyMaxSize_data();
  void test_historyMaxSize();
  void test_imageViewerBGcolor_data();
  void test_imageViewerBGcolor();
  void test_keypointsFormat_data();
  void test_keypointsFormat();
  void test_matchesFormat_data();
  void test_matchesFormat();
  void test_useCuda();

  void test_acebsf();
  void test_clahe();
  void test_cmbfhe();
  void test_dhe();
  void test_fahe();
  void test_hmclahe();
  void test_lceBsescs();
  void test_msrcp();
  void test_noshp();
  void test_pohe();
  void test_rswhe();
  void test_wallis();

  void test_agast();
  void test_akaze();
  void test_boost();
  void test_brief();
  void test_brisk();
  void test_daisy();
  void test_fast();
  void test_freak();
  void test_gftt();
  void test_hog();
  void test_kaze();
  void test_latch();
  void test_lucid();
  void test_msd();
  void test_mser();
  void test_orb();
  void test_sift();
  void test_star();
  void test_surf();
  void test_vgg();

  void test_matchMethod();

  void test_keypointsViewerBGColor_data();
  void test_keypointsViewerBGColor();
  void test_keypointsViewerMarkerSize_data();
  void test_keypointsViewerMarkerSize();
  void test_keypointsViewerMarkerWidth_data();
  void test_keypointsViewerMarkerWidth();
  void test_keypointsViewerMarkerColor_data();
  void test_keypointsViewerMarkerColor();
  void test_keypointsViewerSelectMarkerWidth_data();
  void test_keypointsViewerSelectMarkerWidth();
  void test_keypointsViewerSelectMarkerColor_data();
  void test_keypointsViewerSelectMarkerColor();

  void test_matchesViewerBGColor_data();
  void test_matchesViewerBGColor();
  void test_matchesViewerMarkerSize_data();
  void test_matchesViewerMarkerSize();
  void test_matchesViewerMarkerWidth_data();
  void test_matchesViewerMarkerWidth();
  void test_matchesViewerMarkerColor_data();
  void test_matchesViewerMarkerColor();
  void test_matchesViewerSelectMarkerWidth_data();
  void test_matchesViewerSelectMarkerWidth();
  void test_matchesViewerSelectMarkerColor_data();
  void test_matchesViewerSelectMarkerColor();
  void test_matchesViewerLineColor_data();
  void test_matchesViewerLineColor();
  void test_matchesViewerLineWidth_data();
  void test_matchesViewerLineWidth();

  void test_groundTruthEditorBGColor_data();
  void test_groundTruthEditorBGColor();
  void test_groundTruthEditorMarkerSize_data();
  void test_groundTruthEditorMarkerSize();
  void test_groundTruthEditorMarkerWidth_data();
  void test_groundTruthEditorMarkerWidth();
  void test_groundTruthEditorMarkerColor_data();
  void test_groundTruthEditorMarkerColor();
  void test_groundTruthEditorSelectMarkerWidth_data();
  void test_groundTruthEditorSelectMarkerWidth();
  void test_groundTruthEditorSelectMarkerColor_data();
  void test_groundTruthEditorSelectMarkerColor();

  void test_history();

protected:

  Settings *mSettings;
};

TestSettings::TestSettings()
  : mSettings(new SettingsImp)
{

}

TestSettings::~TestSettings()
{

}

void TestSettings::initTestCase()
{

  QCOMPARE("en", mSettings->language());
  QCOMPARE(10, mSettings->historyMaxSize());
  QCOMPARE(QStringList(), mSettings->history());
  QCOMPARE(QString("#dcdcdc"), mSettings->imageViewerBGcolor());
  QCOMPARE(QString("XML"), mSettings->keypointsFormat());
  QCOMPARE(QString("XML"), mSettings->matchesFormat());
  QCOMPARE(false, mSettings->useCuda());
  QCOMPARE(QString("Flann Based Matching"), mSettings->matchMethod());
  QCOMPARE(QString("Robust Matcher"), mSettings->matchStrategy());
  QCOMPARE("#dcdcdc", mSettings->keypointsViewerBGColor());
  QCOMPARE(0, mSettings->keypointsViewerMarkerType());
  QCOMPARE(20, mSettings->keypointsViewerMarkerSize());
  QCOMPARE(2, mSettings->keypointsViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettings->keypointsViewerMarkerColor());
  QCOMPARE(2, mSettings->keypointsViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->keypointsViewerSelectMarkerColor());
  QCOMPARE("#dcdcdc", mSettings->matchesViewerBGColor());
  QCOMPARE(0, mSettings->matchesViewerMarkerType());
  QCOMPARE(20, mSettings->matchesViewerMarkerSize());
  QCOMPARE(2, mSettings->matchesViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettings->matchesViewerMarkerColor());
  QCOMPARE(2, mSettings->matchesViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->matchesViewerSelectMarkerColor());
  QCOMPARE("#0000ff", mSettings->matchesViewerLineColor());
  QCOMPARE(2, mSettings->matchesViewerLineWidth());
  QCOMPARE("#dcdcdc", mSettings->groundTruthEditorBGColor());
  QCOMPARE(20, mSettings->groundTruthEditorMarkerSize());
  QCOMPARE(2, mSettings->groundTruthEditorMarkerWidth());
  QCOMPARE("#00aa00", mSettings->groundTruthEditorMarkerColor());
  QCOMPARE(2, mSettings->groundTruthEditorSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->groundTruthEditorSelectMarkerColor());
}

void TestSettings::cleanupTestCase()
{
  mSettings->setLanguage("es");
  mSettings->setHistoryMaxSize(20);
  mSettings->setImageViewerBGcolor("#ff00ff");
  mSettings->setKeypointsFormat("YML");
  mSettings->setMatchesFormat("YML");
  mSettings->setUseCuda(true);
  mSettings->setKeypointsViewerBGColor("#ffffff");
  mSettings->setKeypointsViewerMarkerType(2);
  mSettings->setKeypointsViewerMarkerSize(30);
  mSettings->setKeypointsViewerMarkerWidth(5);
  mSettings->setKeypointsViewerMarkerColor("#ffffff");
  mSettings->setKeypointsViewerSelectMarkerWidth(1);
  mSettings->setKeypointsViewerSelectMarkerColor("#ffffff");
  mSettings->setMatchesViewerBGColor("#ffffff");
  mSettings->setMatchesViewerMarkerType(2);
  mSettings->setMatchesViewerMarkerSize(25);
  mSettings->setMatchesViewerMarkerWidth(5);
  mSettings->setMatchesViewerMarkerColor("#ffffff");
  mSettings->setMatchesViewerLineColor("#ffffff");
  mSettings->setMatchesViewerLineWidth(5);
  mSettings->setMatchesViewerSelectMarkerWidth(3);
  mSettings->setMatchesViewerSelectMarkerColor("#ffffff");
  mSettings->setGroundTruthEditorBGColor("#ffffff");
  mSettings->setGroundTruthEditorMarkerSize(25);
  mSettings->setGroundTruthEditorMarkerWidth(5);
  mSettings->setGroundTruthEditorMarkerColor("#ffffff");
  mSettings->setGroundTruthEditorSelectMarkerWidth(4);
  mSettings->setGroundTruthEditorSelectMarkerColor("#ffffff");

  mSettings->acebsf()->setL(0.05);
  mSettings->clahe()->setClipLimit(30.);
  mSettings->cmbfhe()->setBlockSize(QSize(7,7));
  mSettings->dhe()->setX(2);
  mSettings->fahe()->setBlockSize(QSize(11,11));
  mSettings->hmclahe()->setL(0.5);
  mSettings->lceBsescs()->setBlockSize(QSize(33, 33));
  mSettings->msrcp()->setMidScale(110.);
  mSettings->noshp()->setBlockSize(QSize(111, 111));
  mSettings->pohe()->setBlockSize(QSize(111, 111));
  mSettings->rswhe()->setHistogramDivisions(4);
  mSettings->wallis()->setContrast(0.5);

  mSettings->reset();


  QCOMPARE("en", mSettings->language());
  QCOMPARE(10, mSettings->historyMaxSize());
  QCOMPARE(QStringList(), mSettings->history());
  QCOMPARE(QString("#dcdcdc"), mSettings->imageViewerBGcolor());
  QCOMPARE(QString("XML"), mSettings->keypointsFormat());
  QCOMPARE(QString("XML"), mSettings->matchesFormat());
  QCOMPARE(false, mSettings->useCuda());
  QCOMPARE("#dcdcdc", mSettings->keypointsViewerBGColor());
  QCOMPARE(0, mSettings->keypointsViewerMarkerType());
  QCOMPARE(20, mSettings->keypointsViewerMarkerSize());
  QCOMPARE(2, mSettings->keypointsViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettings->keypointsViewerMarkerColor());
  QCOMPARE(2, mSettings->keypointsViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->keypointsViewerSelectMarkerColor());
  QCOMPARE("#dcdcdc", mSettings->matchesViewerBGColor());
  QCOMPARE(0, mSettings->matchesViewerMarkerType());
  QCOMPARE(20, mSettings->matchesViewerMarkerSize());
  QCOMPARE(2, mSettings->matchesViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettings->matchesViewerMarkerColor());
  QCOMPARE("#0000ff", mSettings->matchesViewerLineColor());
  QCOMPARE(2, mSettings->matchesViewerLineWidth());
  QCOMPARE(2, mSettings->matchesViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->matchesViewerSelectMarkerColor());
  QCOMPARE("#dcdcdc", mSettings->groundTruthEditorBGColor());
  QCOMPARE(20, mSettings->groundTruthEditorMarkerSize());
  QCOMPARE(2, mSettings->groundTruthEditorMarkerWidth());
  QCOMPARE("#00aa00", mSettings->groundTruthEditorMarkerColor());
  QCOMPARE(2, mSettings->groundTruthEditorSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettings->groundTruthEditorSelectMarkerColor());

  QCOMPARE(0.03, mSettings->acebsf()->l());
  QCOMPARE(40., mSettings->clahe()->clipLimit());
  QCOMPARE(QSize(11,11), mSettings->cmbfhe()->blockSize());
  QCOMPARE(1, mSettings->dhe()->x());
  QCOMPARE(QSize(11,11), mSettings->fahe()->blockSize());
  QCOMPARE(0.03, mSettings->hmclahe()->l());
  QCOMPARE(QSize(33, 33), mSettings->lceBsescs()->blockSize());
  QCOMPARE(100., mSettings->msrcp()->midScale());
  QCOMPARE(QSize(127, 127), mSettings->noshp()->blockSize());
  QCOMPARE(QSize(127, 127), mSettings->pohe()->blockSize());
  QCOMPARE(2, mSettings->rswhe()->histogramDivisions());
  QCOMPARE(1.0, mSettings->wallis()->contrast());

}

void TestSettings::test_language_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("en") << "en" << "en";
  QTest::newRow("es") << "es" << "es";
}

void TestSettings::test_language()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setLanguage(value);
  QCOMPARE(result, mSettings->language());
}

void TestSettings::test_historyMaxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
}

void TestSettings::test_historyMaxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setHistoryMaxSize(value);
  QCOMPARE(result, mSettings->historyMaxSize());
}

void TestSettings::test_imageViewerBGcolor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_imageViewerBGcolor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setImageViewerBGcolor(value);
  QCOMPARE(result, mSettings->imageViewerBGcolor());
}

void TestSettings::test_keypointsFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettings::test_keypointsFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsFormat(value);
  QCOMPARE(result, mSettings->keypointsFormat());
}

void TestSettings::test_matchesFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettings::test_matchesFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesFormat(value);
  QCOMPARE(result, mSettings->matchesFormat());
}

void TestSettings::test_useCuda()
{
  mSettings->setUseCuda(true);
  QCOMPARE(true, mSettings->useCuda());

  mSettings->setUseCuda(false);
  QCOMPARE(false, mSettings->useCuda());
}

void TestSettings::test_acebsf()
{
  QCOMPARE(QSize(8, 8), mSettings->acebsf()->blockSize());
  QCOMPARE(0.03, mSettings->acebsf()->l());
  QCOMPARE(10., mSettings->acebsf()->k1());
  QCOMPARE(0.5, mSettings->acebsf()->k2());
}

void TestSettings::test_clahe()
{
  QCOMPARE(40.0, mSettings->clahe()->clipLimit());
  QCOMPARE(QSize(8, 8), mSettings->clahe()->tilesGridSize());
}

void TestSettings::test_cmbfhe()
{
  QCOMPARE(QSize(11, 11), mSettings->cmbfhe()->blockSize());
}

void TestSettings::test_dhe()
{
  QCOMPARE(1, mSettings->dhe()->x());
}

void TestSettings::test_fahe()
{
  QCOMPARE(QSize(11, 11), mSettings->fahe()->blockSize());
}

void TestSettings::test_hmclahe()
{
  QCOMPARE(QSize(17, 17), mSettings->hmclahe()->blockSize());
  QCOMPARE(0.03, mSettings->hmclahe()->l());
  QCOMPARE(0.5, mSettings->hmclahe()->phi());
}

void TestSettings::test_lceBsescs()
{
  QCOMPARE(QSize(33, 33), mSettings->lceBsescs()->blockSize());
}

void TestSettings::test_msrcp()
{
  QCOMPARE(10., mSettings->msrcp()->smallScale());
  QCOMPARE(100., mSettings->msrcp()->midScale());
  QCOMPARE(220., mSettings->msrcp()->largeScale());
}

void TestSettings::test_noshp()
{
  QCOMPARE(QSize(127, 127), mSettings->noshp()->blockSize());
}

void TestSettings::test_pohe()
{
  QCOMPARE(QSize(127, 127), mSettings->pohe()->blockSize());
}

void TestSettings::test_rswhe()
{
  QCOMPARE(2, mSettings->rswhe()->histogramDivisions());
  QCOMPARE(Rswhe::HistogramCut::by_mean, mSettings->rswhe()->histogramCut());
}

void TestSettings::test_wallis()
{
  QCOMPARE(1.0, mSettings->wallis()->contrast());
  QCOMPARE(0.2, mSettings->wallis()->brightness());
  QCOMPARE(41, mSettings->wallis()->imposedAverage());
  QCOMPARE(127, mSettings->wallis()->imposedLocalStdDev());
  QCOMPARE(50, mSettings->wallis()->kernelSize());
}

void TestSettings::test_agast()
{
  QCOMPARE(10, mSettings->agast()->threshold());
  QCOMPARE("OAST_9_16", mSettings->agast()->detectorType());
  QCOMPARE(true, mSettings->agast()->nonmaxSuppression());
}

void TestSettings::test_akaze()
{
  QCOMPARE("MLDB", mSettings->akaze()->descriptorType());
  QCOMPARE(0, mSettings->akaze()->descriptorSize());
  QCOMPARE(3, mSettings->akaze()->descriptorChannels());
  qFuzzyCompare(0.001, mSettings->akaze()->threshold());
  QCOMPARE(4, mSettings->akaze()->octaves());
  QCOMPARE(4, mSettings->akaze()->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mSettings->akaze()->diffusivity());
}

void TestSettings::test_boost()
{
  QCOMPARE("BINBOOST_256", mSettings->boost()->descriptorType());
  QCOMPARE(true, mSettings->boost()->useOrientation());
  QCOMPARE(6.25, mSettings->boost()->scaleFactor());
}

void TestSettings::test_brief()
{
  QCOMPARE("32", mSettings->brief()->bytes());
  QCOMPARE(false, mSettings->brief()->useOrientation());
}

void TestSettings::test_brisk()
{
  QCOMPARE(30, mSettings->brisk()->threshold());
  QCOMPARE(3, mSettings->brisk()->octaves());
  QCOMPARE(1.0, mSettings->brisk()->patternScale());
}

void TestSettings::test_daisy()
{
  QCOMPARE(15., mSettings->daisy()->radius());
  QCOMPARE(3, mSettings->daisy()->qRadius());
  QCOMPARE(8, mSettings->daisy()->qTheta());
  QCOMPARE(8, mSettings->daisy()->qHist());
  QCOMPARE("NRM_NONE", mSettings->daisy()->norm());
  QCOMPARE(true, mSettings->daisy()->interpolation());
  QCOMPARE(false, mSettings->daisy()->useOrientation());
}

void TestSettings::test_fast()
{
  QCOMPARE(10, mSettings->fast()->threshold());
  QCOMPARE("TYPE_9_16", mSettings->fast()->detectorType());
  QCOMPARE(true, mSettings->fast()->nonmaxSuppression());
}

void TestSettings::test_freak()
{
  QCOMPARE(true, mSettings->freak()->orientationNormalized());
  QCOMPARE(true, mSettings->freak()->scaleNormalized());
  QCOMPARE(22., mSettings->freak()->patternScale());
  QCOMPARE(4, mSettings->freak()->octaves());
}

void TestSettings::test_gftt()
{
  QCOMPARE(1000, mSettings->gftt()->maxFeatures());
  QCOMPARE(0.01, mSettings->gftt()->qualityLevel());
  QCOMPARE(1, mSettings->gftt()->minDistance());
  QCOMPARE(3, mSettings->gftt()->blockSize());
  QCOMPARE(false, mSettings->gftt()->harrisDetector());
  QCOMPARE(0.04, mSettings->gftt()->k());
}

void TestSettings::test_hog()
{
  QCOMPARE(QSize(16, 16), mSettings->hog()->winSize());
  QCOMPARE(QSize(4, 4), mSettings->hog()->blockSize());
  QCOMPARE(QSize(2, 2), mSettings->hog()->blockStride());
  QCOMPARE(QSize(2, 2), mSettings->hog()->cellSize());
  QCOMPARE(9, mSettings->hog()->nbins());
  QCOMPARE(1, mSettings->hog()->derivAperture());
}

void TestSettings::test_kaze()
{
  QCOMPARE(false, mSettings->kaze()->extendedDescriptor());
  QCOMPARE(false, mSettings->kaze()->uprightDescriptor());
  QCOMPARE(0.001, mSettings->kaze()->threshold());
  QCOMPARE(4, mSettings->kaze()->octaves());
  QCOMPARE(4, mSettings->kaze()->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mSettings->kaze()->diffusivity());
}

void TestSettings::test_latch()
{
  QCOMPARE("32", mSettings->latch()->bytes());
  QCOMPARE(true, mSettings->latch()->rotationInvariance());
  QCOMPARE(3, mSettings->latch()->halfSsdSize());
}

void TestSettings::test_lucid()
{
  QCOMPARE(1, mSettings->lucid()->lucidKernel());
  QCOMPARE(2, mSettings->lucid()->blurKernel());
}

void TestSettings::test_msd()
{
  QCOMPARE(250, mSettings->msd()->thresholdSaliency());
  QCOMPARE(3, mSettings->msd()->patchRadius());
  QCOMPARE(4, mSettings->msd()->knn());
  QCOMPARE(5, mSettings->msd()->searchAreaRadius());
  QCOMPARE(1.25, mSettings->msd()->scaleFactor());
  QCOMPARE(5, mSettings->msd()->NMSRadius());
  QCOMPARE(-1, mSettings->msd()->nScales());
  QCOMPARE(0, mSettings->msd()->NMSScaleRadius());
  QCOMPARE(false, mSettings->msd()->computeOrientation());
  QCOMPARE(false, mSettings->msd()->affineMSD());
  QCOMPARE(3, mSettings->msd()->affineTilts());
}

void TestSettings::test_mser()
{
  QCOMPARE(5, mSettings->mser()->delta());
  QCOMPARE(60, mSettings->mser()->minArea());
  QCOMPARE(14400, mSettings->mser()->maxArea());
  QCOMPARE(0.25, mSettings->mser()->maxVariation());
  QCOMPARE(.2, mSettings->mser()->minDiversity());
  QCOMPARE(200, mSettings->mser()->maxEvolution());
  QCOMPARE(1.01, mSettings->mser()->areaThreshold());
  QCOMPARE(0.003, mSettings->mser()->minMargin());
  QCOMPARE(5, mSettings->mser()->edgeBlurSize());
}

void TestSettings::test_orb()
{
  QCOMPARE(5000, mSettings->orb()->featuresNumber());
  QCOMPARE(1.2, mSettings->orb()->scaleFactor());
  QCOMPARE(8, mSettings->orb()->levelsNumber());
  QCOMPARE(31, mSettings->orb()->edgeThreshold());
  QCOMPARE(2, mSettings->orb()->wta_k());
  QCOMPARE("Harris", mSettings->orb()->scoreType());
  QCOMPARE(31, mSettings->orb()->patchSize());
  QCOMPARE(20, mSettings->orb()->fastThreshold());
}

void TestSettings::test_sift()
{
  QCOMPARE(5000, mSettings->sift()->featuresNumber());
  QCOMPARE(3, mSettings->sift()->octaveLayers());
  QCOMPARE(0.04, mSettings->sift()->contrastThreshold());
  QCOMPARE(10., mSettings->sift()->edgeThreshold());
  QCOMPARE(1.6, mSettings->sift()->sigma());
}

void TestSettings::test_star()
{
  QCOMPARE(45, mSettings->star()->maxSize());
  QCOMPARE(30, mSettings->star()->responseThreshold());
  QCOMPARE(10, mSettings->star()->lineThresholdProjected());
  QCOMPARE(8, mSettings->star()->lineThresholdBinarized());
  QCOMPARE(5, mSettings->star()->suppressNonmaxSize());
}

void TestSettings::test_surf()
{
  QCOMPARE(100, mSettings->surf()->hessianThreshold());
  QCOMPARE(4, mSettings->surf()->octaves());
  QCOMPARE(3, mSettings->surf()->octaveLayers());
  QCOMPARE(false, mSettings->surf()->extendedDescriptor());
  QCOMPARE(false, mSettings->surf()->upright());
}

void TestSettings::test_vgg()
{
  QCOMPARE("VGG_120", mSettings->vgg()->descriptorType());
  QCOMPARE(6.25, mSettings->vgg()->scaleFactor());
  QCOMPARE(1.4, mSettings->vgg()->sigma());
  QCOMPARE(false, mSettings->vgg()->useNormalizeDescriptor());
  QCOMPARE(true, mSettings->vgg()->useNormalizeImage());
  QCOMPARE(true, mSettings->vgg()->useScaleOrientation());
}

void TestSettings::test_matchMethod()
{
  mSettings->setMatchMethod("Flann Based Matching");
  QCOMPARE(QString("Flann Based Matching"), mSettings->matchMethod());

  mSettings->setMatchMethod("Brute Force Matching");
  QCOMPARE(QString("Brute Force Matching"), mSettings->matchMethod());
}

void TestSettings::test_keypointsViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_keypointsViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsViewerBGColor(value);
  QCOMPARE(result, mSettings->keypointsViewerBGColor());
}

void TestSettings::test_keypointsViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_keypointsViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setKeypointsViewerMarkerSize(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerSize());
}

void TestSettings::test_keypointsViewerMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_keypointsViewerMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setKeypointsViewerMarkerWidth(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerWidth());
}

void TestSettings::test_keypointsViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_keypointsViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsViewerMarkerColor(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerColor());
}

void TestSettings::test_keypointsViewerSelectMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_keypointsViewerSelectMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setKeypointsViewerSelectMarkerWidth(value);
  QCOMPARE(result, mSettings->keypointsViewerSelectMarkerWidth());
}

void TestSettings::test_keypointsViewerSelectMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_keypointsViewerSelectMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsViewerSelectMarkerColor(value);
  QCOMPARE(result, mSettings->keypointsViewerSelectMarkerColor());
}

void TestSettings::test_matchesViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerBGColor(value);
  QCOMPARE(result, mSettings->matchesViewerBGColor());
}

void TestSettings::test_matchesViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerMarkerSize(value);
  QCOMPARE(result, mSettings->matchesViewerMarkerSize());
}

void TestSettings::test_matchesViewerMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerMarkerWidth(value);
  QCOMPARE(result, mSettings->matchesViewerMarkerWidth());
}

void TestSettings::test_matchesViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerMarkerColor(value);
  QCOMPARE(result, mSettings->matchesViewerMarkerColor());
}

void TestSettings::test_matchesViewerSelectMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerSelectMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerSelectMarkerWidth(value);
  QCOMPARE(result, mSettings->matchesViewerSelectMarkerWidth());
}

void TestSettings::test_matchesViewerSelectMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerSelectMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerSelectMarkerColor(value);
  QCOMPARE(result, mSettings->matchesViewerSelectMarkerColor());
}

void TestSettings::test_matchesViewerLineColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerLineColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerLineColor(value);
  QCOMPARE(result, mSettings->matchesViewerLineColor());
}

void TestSettings::test_matchesViewerLineWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerLineWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerLineWidth(value);
  QCOMPARE(result, mSettings->matchesViewerLineWidth());
}

void TestSettings::test_groundTruthEditorBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_groundTruthEditorBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setGroundTruthEditorBGColor(value);
  QCOMPARE(result, mSettings->groundTruthEditorBGColor());
}

void TestSettings::test_groundTruthEditorMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_groundTruthEditorMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setGroundTruthEditorMarkerSize(value);
  QCOMPARE(result, mSettings->groundTruthEditorMarkerSize());
}

void TestSettings::test_groundTruthEditorMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_groundTruthEditorMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setGroundTruthEditorMarkerWidth(value);
  QCOMPARE(result, mSettings->groundTruthEditorMarkerWidth());
}

void TestSettings::test_groundTruthEditorMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_groundTruthEditorMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setGroundTruthEditorMarkerColor(value);
  QCOMPARE(result, mSettings->groundTruthEditorMarkerColor());
}

void TestSettings::test_groundTruthEditorSelectMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_groundTruthEditorSelectMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setGroundTruthEditorSelectMarkerWidth(value);
  QCOMPARE(result, mSettings->groundTruthEditorSelectMarkerWidth());
}

void TestSettings::test_groundTruthEditorSelectMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_groundTruthEditorSelectMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setGroundTruthEditorSelectMarkerColor(value);
  QCOMPARE(result, mSettings->groundTruthEditorSelectMarkerColor());
}

void TestSettings::test_history()
{
  mSettings->setHistoryMaxSize(8);
  QCOMPARE(8, mSettings->historyMaxSize());

  /// Se añaden proyectos al historial

  mSettings->addToHistory("c://projects/prj01.xml");
  mSettings->addToHistory("c://projects/prj02.xml");
  mSettings->addToHistory("c://projects/prj03.xml");
  mSettings->addToHistory("c://projects/prj04.xml");
  mSettings->addToHistory("c://projects/prj05.xml");
  mSettings->addToHistory("c://projects/prj06.xml");
  mSettings->addToHistory("c://projects/prj07.xml");
  mSettings->addToHistory("c://projects/prj08.xml");
  mSettings->addToHistory("c://projects/prj09.xml");
  mSettings->addToHistory("c://projects/prj10.xml");
  mSettings->addToHistory("c://projects/prj11.xml");

  /// Se recupera el historial
  QStringList h = mSettings->history();
  QCOMPARE(8, h.size());
  QCOMPARE("c://projects/prj11.xml", h[0]);

  /// Se borra el historial
  mSettings->clearHistory();
  h = mSettings->history();
  QCOMPARE(0, h.size());
}


QTEST_APPLESS_MAIN(TestSettings)

#include "tst_settings.moc"
