#include <QtTest>

#include "photomatch/ui/SettingsModel.h"

using namespace photomatch;


class SettingsRWFake
  : public SettingsController
{

protected:

  struct Data{
    QString lang = "en";
    QStringList history;
  };

public:

  SettingsRWFake()
    : SettingsController()
  {}

  ~SettingsRWFake() override {}

// ISettingsRW interface

public:

  void read(Settings &settings) override
  {
    settings.setLanguage(this->data.lang);
  }

  void write(const Settings &settings) override
  {
    this->data.lang = settings.language();
  }

  void writeHistory(const Settings &settings) override
  {
    this->data.history = settings.history();
  }

protected:

  Data data;


};





class TestSettingsModel : public QObject
{
  Q_OBJECT

public:
  TestSettingsModel();
  ~TestSettingsModel();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultValues();
  void test_language();
  void test_languages();
  void test_history();

  void test_acebsfBlockSize();
  void test_acebsfL();
  void test_acebsfK1();
  void test_acebsfK2();

  /* CLAHE */
  void test_claheClipLimit();
  void test_claheTilesGridSize();

  /* DHE */
  void test_cmbfheBlockSize();

  /* CMBFHE */
  void test_dheX();

  /* FAHE */
  void test_faheBlockSize();

  /* HMCLAHE */
  void test_hmclaheBlockSize();
  void test_hmclaheL();
  void test_hmclahePhi();

  void test_lceBsescsBlockSize();

  void test_msrcpSmallScale();
  void test_msrcpMidScale();
  void test_msrcpLargeScale();

  void test_noshpBlockSize();

  void test_poheBlockSize();

  void test_rswheHistogramDivisions();
  void test_rswheHistogramCut();

  void test_wallisContrast();
  void test_wallisBrightness();
  void test_wallisImposedAverage();
  void test_wallisImposedLocalStdDev();
  void test_wallisKernelSize();

  /* AGAST */
  void test_agastThreshold();
  void test_agastNonmaxSuppression();
  void test_agastDetectorType_data();
  void test_agastDetectorType();

  /* AKAZE */
  void test_akazeDescriptorType_data();
  void test_akazeDescriptorType();
  void test_akazeDescriptorSize();
  void test_akazeDescriptorChannels();
  void test_akazeThreshold();
  void test_akazeOctaves();
  void test_akazeOctaveLayers();
  void test_akazeDiffusivity_data();
  void test_akazeDiffusivity();

  /* BOOST */
  void test_boostDescriptorType_data();
  void test_boostDescriptorType();
  void test_boostUseOrientation();
  void test_boostScaleFactor_data();
  void test_boostScaleFactor();

  /* BRIEF */
  void test_briefBytes();
  void test_briefUseOrientation();

  /* BRISK */
  void test_briskThreshold();
  void test_briskOctaves();
  void test_briskPatternScale();

  /* DAISY */
  void test_daisyRadius();
  void test_daisyQRadius();
  void test_daisyQTheta();
  void test_daisyQHist();
  void test_daisyNorm();
  void test_daisyInterpolation();
  void test_daisyUseOrientation();

  /* FAST */
  void test_fastThreshold();
  void test_fastNonmaxSuppression();
  void test_fastDetectorType();

  void test_freakOrientationNormalized();
  void test_freakScaleNormalized();
  void test_freakPatternScale();
  void test_freakOctaves();

  void test_gfttMaxFeatures();
  void test_gfttQualityLevel();
  void test_gfttMinDistance();
  void test_gfttBlockSize();
  void test_gfttHarrisDetector();
  void test_gfttK();

  void test_hogWinSize();
  void test_hogBlockSize();
  void test_hogBlockStride();
  void test_hogCellSize();
  void test_hogNbins();
  void test_hogDerivAperture();

  void test_kazeExtendedDescriptor();
  void test_kazeUpright();
  void test_kazeThreshold();
  void test_kazeOctaves();
  void test_kazeOctaveLayers();
  void test_kazeDiffusivity();

  void test_latchBytes();
  void test_latchRotationInvariance();
  void test_latchHalfSsdSize();

  void test_lucidLucidKernel();
  void test_lucidBlurKernel();

  void test_msdThresholdSaliency();
  void test_msdPathRadius();
  void test_msdKnn();
  void test_msdAreaRadius();
  void test_msdScaleFactor();
  void test_msdNMSRadius();
  void test_msdNScales();
  void test_msdNMSScaleR();
  void test_msdComputeOrientations();
  void test_msdAffineMSD();
  void test_msdTilts();

  void test_mserDelta();
  void test_mserMinArea();
  void test_mserMaxArea();
  void test_mserMaxVariation();
  void test_mserMinDiversity();
  void test_mserMaxEvolution();
  void test_mserAreaThreshold();
  void test_mserMinMargin();
  void test_mserEdgeBlurSize();

  void test_orbFeaturesNumber();
  void test_orbScaleFactor();
  void test_orbLevelsNumber();
  void test_orbEdgeThreshold();
  void test_orbWta_k();
  void test_orbScoreType();
  void test_orbPatchSize();
  void test_orbFastThreshold();

  /* SURF */
  void test_surfHessianThreshold();
  void test_surfOctaves();
  void test_surfOctaveLayers();
  void test_surfExtendedDescriptor();
  void test_surfRotatedFeatures();

  void test_siftFeaturesNumber();
  void test_siftOctaveLayers();
  void test_siftContrastThreshold();
  void test_siftEdgeThreshold();
  void test_siftSigma();

  void test_starMaxSize();
  void test_starResponseThreshold();
  void test_starLineThresholdProjected();
  void test_starLineThresholdBinarized();
  void test_starSuppressNonmaxSize();

  void test_matchMatchingMethod();
  void test_matchNormType();
  void test_matchRatio();
  void test_matchDistance();
  void test_matchConfidence();
  void test_matchCrossMatching();

  void test_keypointsViewerBGColor();
  void test_keypointsViewerMarkerType();
  void test_keypointsViewerMarkerSize();
  void test_keypointsViewerMarkerWidth();
  void test_keypointsViewerMarkerColor();

  void test_matchesViewerBGColor();
  void test_matchesViewerMarkerType();
  void test_matchesViewerMarkerSize();
  void test_matchesViewerMarkerWidth();
  void test_matchesViewerMarkerColor();
  void test_matchesViewerLineColor();
  void test_matchesViewerLineWidth();

  void test_groundTruthEditorBGColor();
  void test_groundTruthEditorMarkerSize();
  void test_groundTruthEditorMarkerWidth();
  void test_groundTruthEditorMarkerColor();

  void test_reset();

protected:

  Settings *mSettings;
  SettingsController *mSettingsRWFake;
  ISettingsModel *mSettingsModel;

};

TestSettingsModel::TestSettingsModel()
  : mSettings(new SettingsImp),
    mSettingsRWFake(new SettingsRWFake)
{
  mSettingsModel = new SettingsModel(mSettings, mSettingsRWFake);
}

TestSettingsModel::~TestSettingsModel()
{
  if (mSettings){
    delete mSettings;
    mSettings = nullptr;
  }

  if (mSettingsRWFake){
    delete mSettingsRWFake;
    mSettingsRWFake = nullptr;
  }

  if (mSettingsModel){
    delete mSettingsModel;
    mSettingsModel = nullptr;
  }
}

void TestSettingsModel::initTestCase()
{
  mSettingsModel->read();
}

void TestSettingsModel::cleanupTestCase()
{

}

void TestSettingsModel::test_defaultValues()
{
  SettingsImp settings;
  SettingsRWFake rw;
  SettingsModel settingsModel(&settings, &rw);

  QCOMPARE("en", settingsModel.language());

  QCOMPARE(10, settingsModel.historyMaxSize());
  QCOMPARE(QStringList(), settingsModel.history());

  QCOMPARE(QString("#dcdcdc"), settingsModel.imageViewerBGcolor());

  QCOMPARE(QString("XML"), settingsModel.keypointsFormat());
  QCOMPARE(QString("XML"), settingsModel.matchesFormat());

  QCOMPARE(false, settingsModel.useCuda());

  QCOMPARE(QSize(8, 8), settingsModel.acebsfBlockSize());
  QCOMPARE(0.03, settingsModel.acebsfL());
  QCOMPARE(10., settingsModel.acebsfK1());
  QCOMPARE(0.5, settingsModel.acebsfK2());

  QCOMPARE(40., settingsModel.claheClipLimit());
  QCOMPARE(QSize(8, 8), settingsModel.claheTilesGridSize());

  QCOMPARE(QSize(11,11), settingsModel.cmbfheBlockSize());

  QCOMPARE(1, settingsModel.dheX());

  QCOMPARE(QSize(11,11), settingsModel.faheBlockSize());

  QCOMPARE(QSize(17,17), settingsModel.hmclaheBlockSize());
  QCOMPARE(0.03, settingsModel.hmclaheL());
  QCOMPARE(0.5, settingsModel.hmclahePhi());

  QCOMPARE(QSize(33, 33), settingsModel.lceBsescsBlockSize());

  QCOMPARE(10., settingsModel.msrcpSmallScale());
  QCOMPARE(100., settingsModel.msrcpMidScale());
  QCOMPARE(220., settingsModel.msrcpLargeScale());

  QCOMPARE(QSize(127, 127), settingsModel.noshpBlockSize());

  QCOMPARE(QSize(127, 127), settingsModel.poheBlockSize());

  QCOMPARE(2, settingsModel.rswheHistogramDivisions());
  QCOMPARE(0, settingsModel.rswheHistogramCut());

  QCOMPARE(1.0, settingsModel.wallisContrast());
  QCOMPARE(0.2, settingsModel.wallisBrightness());
  QCOMPARE(41, settingsModel.wallisImposedAverage());
  QCOMPARE(127, settingsModel.wallisImposedLocalStdDev());
  QCOMPARE(50, settingsModel.wallisKernelSize());

  QCOMPARE(10, settingsModel.agastThreshold());
  QCOMPARE(true, settingsModel.agastNonmaxSuppression());
  QCOMPARE("OAST_9_16", settingsModel.agastDetectorType());

  QCOMPARE("MLDB", settingsModel.akazeDescriptorType());
  QCOMPARE(0, settingsModel.akazeDescriptorSize());
  QCOMPARE(3, settingsModel.akazeDescriptorChannels());
  QCOMPARE(0.001, settingsModel.akazeThreshold());
  QCOMPARE(4, settingsModel.akazeOctaves());
  QCOMPARE(4, settingsModel.akazeOctaveLayers());
  QCOMPARE("DIFF_PM_G2", settingsModel.akazeDiffusivity());

  QCOMPARE("BINBOOST_256", settingsModel.boostDescriptorType());
  QCOMPARE(true, settingsModel.boostUseOrientation());
  QCOMPARE(6.25, settingsModel.boostScaleFactor());

  QCOMPARE("32", settingsModel.briefBytes());
  QCOMPARE(false, settingsModel.briefUseOrientation());

  QCOMPARE(30, settingsModel.briskThreshold());
  QCOMPARE(3, settingsModel.briskOctaves());
  QCOMPARE(1., settingsModel.briskPatternScale());

  QCOMPARE(15., settingsModel.daisyRadius());
  QCOMPARE(3, settingsModel.daisyQRadius());
  QCOMPARE(8, settingsModel.daisyQTheta());
  QCOMPARE(8, settingsModel.daisyQHist());
  QCOMPARE("NRM_NONE", settingsModel.daisyNorm());
  QCOMPARE(true, settingsModel.daisyInterpolation());
  QCOMPARE(false, settingsModel.daisyUseOrientation());

  QCOMPARE(10, settingsModel.fastThreshold());
  QCOMPARE(true, settingsModel.fastNonmaxSuppression());
  QCOMPARE("TYPE_9_16", settingsModel.fastdetectorType());

  QCOMPARE(true, settingsModel.freakOrientationNormalized());
  QCOMPARE(true, settingsModel.freakScaleNormalized());
  QCOMPARE(22., settingsModel.freakPatternScale());
  QCOMPARE(4, settingsModel.freakOctaves());

  QCOMPARE(1000, settingsModel.gfttMaxFeatures());
  QCOMPARE(0.01, settingsModel.gfttQualityLevel());
  QCOMPARE(1, settingsModel.gfttMinDistance());
  QCOMPARE(3, settingsModel.gfttBlockSize());
  QCOMPARE(false, settingsModel.gfttHarrisDetector());
  QCOMPARE(0.04, settingsModel.gfttK());

  QCOMPARE(QSize(16,16), settingsModel.hogWinSize());
  QCOMPARE(QSize(4,4), settingsModel.hogBlockSize());
  QCOMPARE(QSize(2,2), settingsModel.hogBlockStride());
  QCOMPARE(QSize(2,2), settingsModel.hogCellSize());
  QCOMPARE(9, settingsModel.hogNbins());
  QCOMPARE(1, settingsModel.hogDerivAperture());

  QCOMPARE(false, settingsModel.kazeExtendedDescriptor());
  QCOMPARE(false, settingsModel.kazeUpright());
  QCOMPARE(0.001, settingsModel.kazeThreshold());
  QCOMPARE(4, settingsModel.kazeOctaves());
  QCOMPARE(4, settingsModel.kazeOctaveLayers());
  QCOMPARE("DIFF_PM_G2", settingsModel.kazeDiffusivity());

  QCOMPARE("32", settingsModel.latchBytes());
  QCOMPARE(true, settingsModel.latchRotationInvariance());
  QCOMPARE(3, settingsModel.latchHalfSsdSize());

  QCOMPARE(1, settingsModel.lucidKernel());
  QCOMPARE(2, settingsModel.lucidBlurKernel());

  QCOMPARE(250, settingsModel.msdThresholdSaliency());
  QCOMPARE(3, settingsModel.msdPathRadius());
  QCOMPARE(4, settingsModel.msdKnn());
  QCOMPARE(5, settingsModel.msdAreaRadius());
  QCOMPARE(1.25, settingsModel.msdScaleFactor());
  QCOMPARE(5, settingsModel.msdNMSRadius());
  QCOMPARE(-1, settingsModel.msdNScales());
  QCOMPARE(0, settingsModel.msdNMSScaleR());
  QCOMPARE(false, settingsModel.msdComputeOrientations());
  QCOMPARE(false, settingsModel.msdAffineMSD());
  QCOMPARE(3, settingsModel.msdTilts());

  QCOMPARE(5, settingsModel.mserDelta());
  QCOMPARE(60, settingsModel.mserMinArea());
  QCOMPARE(14400, settingsModel.mserMaxArea());
  QCOMPARE(0.25, settingsModel.mserMaxVariation());
  QCOMPARE(0.2, settingsModel.mserMinDiversity());
  QCOMPARE(200, settingsModel.mserMaxEvolution());
  QCOMPARE(1.01, settingsModel.mserAreaThreshold());
  QCOMPARE(0.003, settingsModel.mserMinMargin());
  QCOMPARE(5, settingsModel.mserEdgeBlurSize());

  QCOMPARE(5000, settingsModel.orbFeaturesNumber());
  QCOMPARE(1.2, settingsModel.orbScaleFactor());
  QCOMPARE(8, settingsModel.orbLevelsNumber());
  QCOMPARE(31, settingsModel.orbEdgeThreshold());
  QCOMPARE(2, settingsModel.orbWta_k());
  QCOMPARE("Harris", settingsModel.orbScoreType());
  QCOMPARE(31, settingsModel.orbPatchSize());
  QCOMPARE(20, settingsModel.orbFastThreshold());

  QCOMPARE(100, settingsModel.surfHessianThreshold());
  QCOMPARE(4, settingsModel.surfOctaves());
  QCOMPARE(3, settingsModel.surfOctaveLayers());
  QCOMPARE(false, settingsModel.surfExtendedDescriptor());
  QCOMPARE(false, settingsModel.surfRotatedFeatures());

  QCOMPARE(5000, settingsModel.siftFeaturesNumber());
  QCOMPARE(3, settingsModel.siftOctaveLayers());
  QCOMPARE(0.04, settingsModel.siftContrastThreshold());
  QCOMPARE(10., settingsModel.siftEdgeThreshold());
  QCOMPARE(1.6, settingsModel.siftSigma());

  QCOMPARE(45, settingsModel.starMaxSize());
  QCOMPARE(30, settingsModel.starResponseThreshold());
  QCOMPARE(10, settingsModel.starLineThresholdProjected());
  QCOMPARE(8, settingsModel.starLineThresholdBinarized());
  QCOMPARE(5, settingsModel.starSuppressNonmaxSize());

  QCOMPARE("VGG_120", settingsModel.vggDescriptorType());
  QCOMPARE(6.25, settingsModel.vggScaleFactor());
  QCOMPARE(1.4, settingsModel.vggSigma());
  QCOMPARE(false, settingsModel.vggUseNormalizeDescriptor());
  QCOMPARE(true, settingsModel.vggUseNormalizeImage());
  QCOMPARE(true, settingsModel.vggUseScaleOrientation());

  QCOMPARE("Flann Based Matching", settingsModel.matchMethod());
  QCOMPARE("NORM_L2", settingsModel.matchNormType());
  QCOMPARE(0.8, settingsModel.matchRatio());
  QCOMPARE(0.7, settingsModel.matchDistance());
  QCOMPARE(0.999, settingsModel.matchConfidence());
  QCOMPARE(true, settingsModel.matchCrossMatching());
  QCOMPARE(2000, settingsModel.matchMaxIters());
  QCOMPARE("Fundamental Matrix", settingsModel.matchGeometricTest());
  QCOMPARE("RANSAC", settingsModel.matchHomographyComputeMethod());
  QCOMPARE("RANSAC", settingsModel.matchFundamentalComputeMethod());
  QCOMPARE("RANSAC", settingsModel.matchEssentialComputeMethod());

  QCOMPARE("#dcdcdc", settingsModel.keypointsViewerBGColor());
  QCOMPARE(0, settingsModel.keypointsViewerMarkerType());
  QCOMPARE(20, settingsModel.keypointsViewerMarkerSize());
  QCOMPARE(2, settingsModel.keypointsViewerMarkerWidth());
  QCOMPARE("#00aa00", settingsModel.keypointsViewerMarkerColor());
  QCOMPARE(2, settingsModel.keypointsViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", settingsModel.keypointsViewerSelectMarkerColor());

  QCOMPARE("#dcdcdc", settingsModel.matchesViewerBGColor());
  QCOMPARE(0, settingsModel.matchesViewerMarkerType());
  QCOMPARE(20, settingsModel.matchesViewerMarkerSize());
  QCOMPARE(2, settingsModel.matchesViewerMarkerWidth());
  QCOMPARE("#00aa00", settingsModel.matchesViewerMarkerColor());
  QCOMPARE("#0000ff", settingsModel.matchesViewerLineColor());
  QCOMPARE(2, settingsModel.matchesViewerLineWidth());
  QCOMPARE(2, settingsModel.matchesViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", settingsModel.matchesViewerSelectMarkerColor());

  QCOMPARE("#dcdcdc", settingsModel.groundTruthEditorBGColor());
  QCOMPARE(20, settingsModel.groundTruthEditorMarkerSize());
  QCOMPARE(2, settingsModel.groundTruthEditorMarkerWidth());
  QCOMPARE("#00aa00", settingsModel.groundTruthEditorMarkerColor());
  QCOMPARE(2, settingsModel.groundTruthEditorSelectMarkerWidth());
  QCOMPARE("#e5097e", settingsModel.groundTruthEditorSelectMarkerColor());

}

void TestSettingsModel::test_language()
{
  QCOMPARE("en", mSettingsModel->language());

  mSettingsModel->setLanguage("es");
  QCOMPARE("es", mSettingsModel->language());
}

void TestSettingsModel::test_languages()
{
  /// Sólo se chequea el valor por defecto (si no existen ficheros de idioma)
  QStringList languages = mSettingsModel->languages();
  QCOMPARE("photomatch_en.qm", languages[0]);
}

void TestSettingsModel::test_history()
{
  mSettingsModel->setHistoryMaxSize(8);
  QCOMPARE(8, mSettingsModel->historyMaxSize());

  /// Se añaden proyectos al historial

  mSettingsModel->addToHistory("c://projects/prj01.xml");
  mSettingsModel->addToHistory("c://projects/prj02.xml");
  mSettingsModel->addToHistory("c://projects/prj03.xml");
  mSettingsModel->addToHistory("c://projects/prj04.xml");
  mSettingsModel->addToHistory("c://projects/prj05.xml");
  mSettingsModel->addToHistory("c://projects/prj06.xml");
  mSettingsModel->addToHistory("c://projects/prj07.xml");
  mSettingsModel->addToHistory("c://projects/prj08.xml");
  mSettingsModel->addToHistory("c://projects/prj09.xml");
  mSettingsModel->addToHistory("c://projects/prj10.xml");
  mSettingsModel->addToHistory("c://projects/prj11.xml");

  /// Se recupera el historial
  QStringList h = mSettingsModel->history();
  QCOMPARE(8, h.size());
  QCOMPARE("c://projects/prj11.xml", h[0]);

  /// Se borra el historial
  mSettingsModel->clearHistory();
  h = mSettings->history();
  QCOMPARE(0, h.size());
}

void TestSettingsModel::test_acebsfBlockSize()
{
  mSettingsModel->setAcebsfBlockSize(QSize(20, 20));
  QCOMPARE(QSize(20, 20), mSettingsModel->acebsfBlockSize());
}

void TestSettingsModel::test_acebsfL()
{
  mSettingsModel->setAcebsfL(0.05);
  QCOMPARE(0.05, mSettingsModel->acebsfL());
}

void TestSettingsModel::test_acebsfK1()
{
  mSettingsModel->setAcebsfK1(9.);
  QCOMPARE(9., mSettingsModel->acebsfK1());
}

void TestSettingsModel::test_acebsfK2()
{
  mSettingsModel->setAcebsfK2(0.5);
  QCOMPARE(0.5, mSettingsModel->acebsfK2());
}

void TestSettingsModel::test_claheClipLimit()
{
  mSettingsModel->setClaheClipLimit(20.);
  QCOMPARE(20., mSettingsModel->claheClipLimit());
}

void TestSettingsModel::test_claheTilesGridSize()
{
  mSettingsModel->setClaheTilesGridSize(QSize(4, 4));
  QCOMPARE(QSize(4, 4), mSettingsModel->claheTilesGridSize());
}

void TestSettingsModel::test_cmbfheBlockSize()
{
  mSettingsModel->setCmbfheBlockSize(QSize(7,7));
  QCOMPARE(QSize(7,7), mSettingsModel->cmbfheBlockSize());
}

void TestSettingsModel::test_dheX()
{
  mSettingsModel->setDheX(3);
  QCOMPARE(3, mSettingsModel->dheX());
}

void TestSettingsModel::test_faheBlockSize()
{
  mSettingsModel->setFaheBlockSize(QSize(7,7));
  QCOMPARE(QSize(7,7), mSettingsModel->faheBlockSize());
}

void TestSettingsModel::test_hmclaheBlockSize()
{
  mSettingsModel->setHmclaheBlockSize(QSize(7,7));
  QCOMPARE(QSize(7,7), mSettingsModel->hmclaheBlockSize());
}

void TestSettingsModel::test_hmclaheL()
{
  mSettingsModel->setHmclaheL(0.06);
  QCOMPARE(0.06, mSettingsModel->hmclaheL());
}

void TestSettingsModel::test_hmclahePhi()
{
  mSettingsModel->setHmclahePhi(0.4);
  QCOMPARE(0.4, mSettingsModel->hmclahePhi());
}

void TestSettingsModel::test_lceBsescsBlockSize()
{
  mSettingsModel->setLceBsescsBlockSize(QSize(11, 11));
  QCOMPARE(QSize(11, 11), mSettingsModel->lceBsescsBlockSize());
}

void TestSettingsModel::test_msrcpSmallScale()
{
  mSettingsModel->setMsrcpSmallScale(5.);
  QCOMPARE(5., mSettingsModel->msrcpSmallScale());
}

void TestSettingsModel::test_msrcpMidScale()
{
  mSettingsModel->setMsrcpMidScale(80.);
  QCOMPARE(80., mSettingsModel->msrcpMidScale());
}

void TestSettingsModel::test_msrcpLargeScale()
{
  mSettingsModel->setMsrcpLargeScale(180.);
  QCOMPARE(180., mSettingsModel->msrcpLargeScale());
}

void TestSettingsModel::test_noshpBlockSize()
{
  mSettingsModel->setNoshpBlockSize(QSize(50, 50));
  QCOMPARE(QSize(50, 50), mSettingsModel->noshpBlockSize());
}

void TestSettingsModel::test_poheBlockSize()
{
  mSettingsModel->setPoheBlockSize(QSize(50, 50));
  QCOMPARE(QSize(50, 50), mSettingsModel->poheBlockSize());
}

void TestSettingsModel::test_rswheHistogramDivisions()
{
  mSettingsModel->setRswheHistogramDivisions(4);
  QCOMPARE(4, mSettingsModel->rswheHistogramDivisions());
}

void TestSettingsModel::test_rswheHistogramCut()
{
  mSettingsModel->setRswheHistogramCut(1);
  QCOMPARE(1, mSettingsModel->rswheHistogramCut());
}

void TestSettingsModel::test_wallisContrast()
{
  mSettingsModel->setWallisContrast(2.0);
  QCOMPARE(2.0, mSettingsModel->wallisContrast());
}

void TestSettingsModel::test_wallisBrightness()
{
  mSettingsModel->setWallisBrightness(0.4);
  QCOMPARE(0.4, mSettingsModel->wallisBrightness());
}

void TestSettingsModel::test_wallisImposedAverage()
{
  mSettingsModel->setWallisImposedAverage(11);
  QCOMPARE(11, mSettingsModel->wallisImposedAverage());
}

void TestSettingsModel::test_wallisImposedLocalStdDev()
{
  mSettingsModel->setWallisImposedLocalStdDev(25);
  QCOMPARE(25, mSettingsModel->wallisImposedLocalStdDev());
}

void TestSettingsModel::test_wallisKernelSize()
{
  mSettingsModel->setWallisKernelSize(20);
  QCOMPARE(20, mSettingsModel->wallisKernelSize());
}

void TestSettingsModel::test_agastThreshold()
{
  mSettingsModel->setAgastThreshold(20);
  QCOMPARE(20, mSettingsModel->agastThreshold());
}

void TestSettingsModel::test_agastNonmaxSuppression()
{
  mSettingsModel->setAgastNonmaxSuppression(false);
  QCOMPARE(false, mSettingsModel->agastNonmaxSuppression());
}

void TestSettingsModel::test_agastDetectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << "AGAST_5_8";
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << "AGAST_7_12d";
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << "AGAST_7_12s";
  QTest::newRow("OAST_9_16") << "OAST_9_16" << "OAST_9_16";
  QTest::newRow("bad_value") << "bad_value" << "OAST_9_16";
}

void TestSettingsModel::test_agastDetectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettingsModel->setAgastDetectorType(value);
  QCOMPARE(result, mSettingsModel->agastDetectorType());
}

void TestSettingsModel::test_akazeDescriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("KAZE") << "KAZE" << "KAZE";
  QTest::newRow("KAZE_UPRIGHT") << "KAZE_UPRIGHT" << "KAZE_UPRIGHT";
  QTest::newRow("MLDB") << "MLDB" << "MLDB";
  QTest::newRow("MLDB_UPRIGHT") << "MLDB_UPRIGHT" << "MLDB_UPRIGHT";
  QTest::newRow("bad_value") << "bad_value" << "MLDB_UPRIGHT";
}

void TestSettingsModel::test_akazeDescriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettingsModel->setAkazeDescriptorType(value);
  QCOMPARE(result, mSettingsModel->akazeDescriptorType());
}

void TestSettingsModel::test_akazeDescriptorSize()
{
  mSettingsModel->setAkazeDescriptorSize(32);
  QCOMPARE(32, mSettingsModel->akazeDescriptorSize());
}

void TestSettingsModel::test_akazeDescriptorChannels()
{
  mSettingsModel->setAkazeDescriptorChannels(2);
  QCOMPARE(2, mSettingsModel->akazeDescriptorChannels());
}

void TestSettingsModel::test_akazeThreshold()
{
  mSettingsModel->setAkazeThreshold(10.);
  QCOMPARE(10., mSettingsModel->akazeThreshold());
}

void TestSettingsModel::test_akazeOctaves()
{
  mSettingsModel->setAkazeOctaves(2);
  QCOMPARE(2, mSettingsModel->akazeOctaves());
}

void TestSettingsModel::test_akazeOctaveLayers()
{
  mSettingsModel->setAkazeOctaveLayers(5);
  QCOMPARE(5, mSettingsModel->akazeOctaveLayers());
}

void TestSettingsModel::test_akazeDiffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestSettingsModel::test_akazeDiffusivity()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettingsModel->setAkazeDiffusivity(value);
  QCOMPARE(result, mSettingsModel->akazeDiffusivity());
}

void TestSettingsModel::test_boostDescriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("BGM") << "BGM" << "BGM";
  QTest::newRow("BGM_HARD") << "BGM_HARD" << "BGM_HARD";
  QTest::newRow("BGM_BILINEAR") << "BGM_BILINEAR" << "BGM_BILINEAR";
  QTest::newRow("LBGM") << "LBGM" << "LBGM";
  QTest::newRow("BINBOOST_64") << "BINBOOST_64" << "BINBOOST_64";
  QTest::newRow("BINBOOST_128") << "BINBOOST_128" << "BINBOOST_128";
  QTest::newRow("BINBOOST_256") << "BINBOOST_256" << "BINBOOST_256";
  QTest::newRow("bad_value") << "bad_value" << "BINBOOST_256";
}

void TestSettingsModel::test_boostDescriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettingsModel->setBoostDescriptorType(value);
  QCOMPARE(result, mSettingsModel->boostDescriptorType());
}

void TestSettingsModel::test_boostUseOrientation()
{
  mSettingsModel->setBoostUseOrientation(true);
  QCOMPARE(true, mSettingsModel->boostUseOrientation());

  mSettingsModel->setBoostUseOrientation(false);
  QCOMPARE(false, mSettingsModel->boostUseOrientation());
}

void TestSettingsModel::test_boostScaleFactor_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("6.75") << 6.75 << 6.75;
  QTest::newRow("6.25") << 6.25 << 6.25;
  QTest::newRow("5.00") << 5.00 << 5.00;
  QTest::newRow("0.75") << 0.75 << 0.75;
  QTest::newRow("1.50") << 1.50 << 1.50;
}

void TestSettingsModel::test_boostScaleFactor()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSettingsModel->setBoostScaleFactor(value);
  QCOMPARE(result, mSettingsModel->boostScaleFactor());
}

void TestSettingsModel::test_briefBytes()
{
  mSettingsModel->setBriefBytes("16");
  QCOMPARE("16", mSettingsModel->briefBytes());
}

void TestSettingsModel::test_briefUseOrientation()
{
  mSettingsModel->setBriefUseOrientation(true);
  QCOMPARE(true, mSettingsModel->briefUseOrientation());
}

void TestSettingsModel::test_briskThreshold()
{
  mSettingsModel->setBriskThreshold(20);
  QCOMPARE(20, mSettingsModel->briskThreshold());
}

void TestSettingsModel::test_briskOctaves()
{
  mSettingsModel->setBriskOctaves(2);
  QCOMPARE(2, mSettingsModel->briskOctaves());
}

void TestSettingsModel::test_briskPatternScale()
{
  mSettingsModel->setBriskPatternScale(0.5);
  QCOMPARE(0.5, mSettingsModel->briskPatternScale());
}

void TestSettingsModel::test_daisyRadius()
{
  mSettingsModel->setDaisyRadius(10.);
  QCOMPARE(10., mSettingsModel->daisyRadius());
}

void TestSettingsModel::test_daisyQRadius()
{
  mSettingsModel->setDaisyQRadius(2);
  QCOMPARE(2, mSettingsModel->daisyQRadius());
}

void TestSettingsModel::test_daisyQTheta()
{
  mSettingsModel->setDaisyQTheta(4);
  QCOMPARE(4, mSettingsModel->daisyQTheta());
}

void TestSettingsModel::test_daisyQHist()
{
  mSettingsModel->setDaisyQHist(4);
  QCOMPARE(4, mSettingsModel->daisyQHist());
}

void TestSettingsModel::test_daisyNorm()
{
  mSettingsModel->setDaisyNorm("NRM_PARTIAL");

  QCOMPARE("NRM_PARTIAL", mSettingsModel->daisyNorm());
}

void TestSettingsModel::test_daisyInterpolation()
{
  mSettingsModel->setDaisyInterpolation(false);

  QCOMPARE(false, mSettingsModel->daisyInterpolation());
}

void TestSettingsModel::test_daisyUseOrientation()
{
  mSettingsModel->setDaisyUseOrientation(true);
  QCOMPARE(true, mSettingsModel->daisyUseOrientation());
}

void TestSettingsModel::test_fastThreshold()
{
  mSettingsModel->setFastThreshold(20);
  QCOMPARE(20, mSettingsModel->fastThreshold());

}

void TestSettingsModel::test_fastNonmaxSuppression()
{
  mSettingsModel->setFastNonmaxSuppression(false);
  QCOMPARE(false, mSettingsModel->fastNonmaxSuppression());
}

void TestSettingsModel::test_fastDetectorType()
{
  mSettingsModel->setFastDetectorType("TYPE_7_12");
  QCOMPARE("TYPE_7_12", mSettingsModel->fastdetectorType());
}

void TestSettingsModel::test_freakOrientationNormalized()
{
  mSettingsModel->setFreakOrientationNormalized(false);
  QCOMPARE(false, mSettingsModel->freakOrientationNormalized());
}

void TestSettingsModel::test_freakScaleNormalized()
{
  mSettingsModel->setFreakScaleNormalized(false);
  QCOMPARE(false, mSettingsModel->freakScaleNormalized());
}

void TestSettingsModel::test_freakPatternScale()
{
  mSettingsModel->setFreakPatternScale(11.);
  QCOMPARE(11., mSettingsModel->freakPatternScale());
}

void TestSettingsModel::test_freakOctaves()
{
  mSettingsModel->setFreakOctaves(6);
  QCOMPARE(6, mSettingsModel->freakOctaves());
}

void TestSettingsModel::test_gfttMaxFeatures()
{
  mSettingsModel->setGfttMaxFeatures(500);
  QCOMPARE(500, mSettingsModel->gfttMaxFeatures());
}

void TestSettingsModel::test_gfttQualityLevel()
{
  mSettingsModel->setGfttQualityLevel(0.1);
  QCOMPARE(0.1, mSettingsModel->gfttQualityLevel());
}

void TestSettingsModel::test_gfttMinDistance()
{
  mSettingsModel->setGfttMinDistance(2);
  QCOMPARE(2, mSettingsModel->gfttMinDistance());
}

void TestSettingsModel::test_gfttBlockSize()
{
  mSettingsModel->setGfttBlockSize(6);
  QCOMPARE(6, mSettingsModel->gfttBlockSize());
}

void TestSettingsModel::test_gfttHarrisDetector()
{
  mSettingsModel->setGfttHarrisDetector(true);
  QCOMPARE(true, mSettingsModel->gfttHarrisDetector());
}

void TestSettingsModel::test_gfttK()
{
  mSettingsModel->setGfttK(0.2);
  QCOMPARE(0.2, mSettingsModel->gfttK());
}

void TestSettingsModel::test_hogWinSize()
{
  mSettingsModel->setHogWinSize(QSize(64,64));
  QCOMPARE(QSize(64,64), mSettingsModel->hogWinSize());
}

void TestSettingsModel::test_hogBlockSize()
{
  mSettingsModel->setHogBlockSize(QSize(8,8));
  QCOMPARE(QSize(8,8), mSettingsModel->hogBlockSize());
}

void TestSettingsModel::test_hogBlockStride()
{
  mSettingsModel->setHogBlockStride(QSize(4,4));
  QCOMPARE(QSize(4,4), mSettingsModel->hogBlockStride());
}

void TestSettingsModel::test_hogCellSize()
{
  mSettingsModel->setHogCellSize(QSize(4,4));
  QCOMPARE(QSize(4,4), mSettingsModel->hogCellSize());
}

void TestSettingsModel::test_hogNbins()
{
  mSettingsModel->setHogNbins(6);
  QCOMPARE(6, mSettingsModel->hogNbins());
}

void TestSettingsModel::test_hogDerivAperture()
{
  mSettingsModel->setHogDerivAperture(2);
  QCOMPARE(2, mSettingsModel->hogDerivAperture());
}

void TestSettingsModel::test_kazeExtendedDescriptor()
{
  mSettingsModel->setKazeExtendedDescriptor(true);
  QCOMPARE(true, mSettingsModel->kazeExtendedDescriptor());
}

void TestSettingsModel::test_kazeUpright()
{
  mSettingsModel->setKazeUpright(true);
  QCOMPARE(true, mSettingsModel->kazeUpright());
}

void TestSettingsModel::test_kazeThreshold()
{
  mSettingsModel->setKazeThreshold(0.005);
  QCOMPARE(0.005, mSettingsModel->kazeThreshold());
}

void TestSettingsModel::test_kazeOctaves()
{
  mSettingsModel->setKazeOctaves(2);
  QCOMPARE(2, mSettingsModel->kazeOctaves());
}

void TestSettingsModel::test_kazeOctaveLayers()
{
  mSettingsModel->setKazeOctaveLayers(3);
  QCOMPARE(3, mSettingsModel->kazeOctaveLayers());
}

void TestSettingsModel::test_kazeDiffusivity()
{
  mSettingsModel->setKazeDiffusivity("DIFF_WEICKERT");
  QCOMPARE("DIFF_WEICKERT", mSettingsModel->kazeDiffusivity());
}

void TestSettingsModel::test_latchBytes()
{
  mSettingsModel->setLatchBytes("16");
  QCOMPARE("16", mSettingsModel->latchBytes());
}

void TestSettingsModel::test_latchRotationInvariance()
{
  mSettingsModel->setLatchRotationInvariance(true);
  QCOMPARE(true, mSettingsModel->latchRotationInvariance());
}

void TestSettingsModel::test_latchHalfSsdSize()
{
  mSettingsModel->setLatchHalfSsdSize(5);
  QCOMPARE(5, mSettingsModel->latchHalfSsdSize());
}

void TestSettingsModel::test_lucidLucidKernel()
{
  mSettingsModel->setLucidKernel(2);
  QCOMPARE(2, mSettingsModel->lucidKernel());
}

void TestSettingsModel::test_lucidBlurKernel()
{
  mSettingsModel->setLucidBlurKernel(3);
  QCOMPARE(3, mSettingsModel->lucidBlurKernel());
}

void TestSettingsModel::test_msdThresholdSaliency()
{
  mSettingsModel->setMsdThresholdSaliency(150);
  QCOMPARE(150, mSettingsModel->msdThresholdSaliency());
}

void TestSettingsModel::test_msdPathRadius()
{
  mSettingsModel->setMsdPathRadius(5);
  QCOMPARE(5, mSettingsModel->msdPathRadius());
}


void TestSettingsModel::test_msdKnn()
{
  mSettingsModel->setMsdKNN(2);
  QCOMPARE(2, mSettingsModel->msdKnn());
}

void TestSettingsModel::test_msdAreaRadius()
{
  mSettingsModel->setMsdAreaRadius(10);
  QCOMPARE(10, mSettingsModel->msdAreaRadius());
}

void TestSettingsModel::test_msdScaleFactor()
{
  mSettingsModel->setMsdScaleFactor(1.5);
  QCOMPARE(1.5, mSettingsModel->msdScaleFactor());
}

void TestSettingsModel::test_msdNMSRadius()
{
  mSettingsModel->setMsdNMSRadius(10);
  QCOMPARE(10, mSettingsModel->msdNMSRadius());
}

void TestSettingsModel::test_msdNScales()
{
  mSettingsModel->setMsdNScales(-1);
  QCOMPARE(-1, mSettingsModel->msdNScales());
}

void TestSettingsModel::test_msdNMSScaleR()
{
  mSettingsModel->setMsdNMSScaleR(1);
  QCOMPARE(1, mSettingsModel->msdNMSScaleR());
}

void TestSettingsModel::test_msdComputeOrientations()
{
  mSettingsModel->setMsdComputeOrientations(true);
  QCOMPARE(true, mSettingsModel->msdComputeOrientations());
}

void TestSettingsModel::test_msdAffineMSD()
{
  mSettingsModel->setMsdAffineMSD(true);
  QCOMPARE(true, mSettingsModel->msdAffineMSD());
}

void TestSettingsModel::test_msdTilts()
{
  mSettingsModel->setMsdTilts(5);
  QCOMPARE(5, mSettingsModel->msdTilts());
}

void TestSettingsModel::test_mserDelta()
{
  mSettingsModel->setMserDelta(10);
  QCOMPARE(10, mSettingsModel->mserDelta());
}

void TestSettingsModel::test_mserMinArea()
{
  mSettingsModel->setMserMinArea(120);
  QCOMPARE(120, mSettingsModel->mserMinArea());
}

void TestSettingsModel::test_mserMaxArea()
{
  mSettingsModel->setMserMaxArea(10000);
  QCOMPARE(10000, mSettingsModel->mserMaxArea());
}

void TestSettingsModel::test_mserMaxVariation()
{
  mSettingsModel->setMserMaxVariation(0.5);
  QCOMPARE(0.5, mSettingsModel->mserMaxVariation());
}

void TestSettingsModel::test_mserMinDiversity()
{
  mSettingsModel->setMserMinDiversity(0.5);
  QCOMPARE(0.5, mSettingsModel->mserMinDiversity());
}

void TestSettingsModel::test_mserMaxEvolution()
{
  mSettingsModel->setMserMaxEvolution(100);
  QCOMPARE(100, mSettingsModel->mserMaxEvolution());
}

void TestSettingsModel::test_mserAreaThreshold()
{
  mSettingsModel->setMserAreaThreshold(1.5);
  QCOMPARE(1.5, mSettingsModel->mserAreaThreshold());
}

void TestSettingsModel::test_mserMinMargin()
{
  mSettingsModel->setMserMinMargin(0.05);
  QCOMPARE(0.05, mSettingsModel->mserMinMargin());
}

void TestSettingsModel::test_mserEdgeBlurSize()
{
  mSettingsModel->setMserEdgeBlurSize(10);
  QCOMPARE(10, mSettingsModel->mserEdgeBlurSize());
}

void TestSettingsModel::test_orbFeaturesNumber()
{
  mSettingsModel->setOrbFeaturesNumber(6000);
  QCOMPARE(6000, mSettingsModel->orbFeaturesNumber());
}

void TestSettingsModel::test_orbScaleFactor()
{
  mSettingsModel->setOrbScaleFactor(1.5);
  QCOMPARE(1.5, mSettingsModel->orbScaleFactor());
}

void TestSettingsModel::test_orbLevelsNumber()
{
  mSettingsModel->setOrbLevelsNumber(4);
  QCOMPARE(4, mSettingsModel->orbLevelsNumber());
}

void TestSettingsModel::test_orbEdgeThreshold()
{
  mSettingsModel->setOrbEdgeThreshold(15);
  QCOMPARE(15, mSettingsModel->orbEdgeThreshold());
}

void TestSettingsModel::test_orbWta_k()
{
  mSettingsModel->setOrbWTA_K(4);
  QCOMPARE(4, mSettingsModel->orbWta_k());
}

void TestSettingsModel::test_orbScoreType()
{
  mSettingsModel->setOrbScoreType("FAST");
  QCOMPARE("FAST", mSettingsModel->orbScoreType());
}

void TestSettingsModel::test_orbPatchSize()
{
  mSettingsModel->setOrbPatchSize(11);
  QCOMPARE(11, mSettingsModel->orbPatchSize());
}

void TestSettingsModel::test_orbFastThreshold()
{
  mSettingsModel->setOrbFastThreshold(50);
  QCOMPARE(50, mSettingsModel->orbFastThreshold());
}

void TestSettingsModel::test_surfHessianThreshold()
{
  mSettingsModel->setSurfHessianThreshold(150.);
  QCOMPARE(150., mSettingsModel->surfHessianThreshold());
}

void TestSettingsModel::test_surfOctaves()
{
  mSettingsModel->setSurfOctaves(6);
  QCOMPARE(6, mSettingsModel->surfOctaves());
}

void TestSettingsModel::test_surfOctaveLayers()
{
  mSettingsModel->setSurfOctaveLayers(4);
  QCOMPARE(4, mSettingsModel->surfOctaveLayers());
}

void TestSettingsModel::test_surfExtendedDescriptor()
{
  mSettingsModel->setSurfExtendedDescriptor(true);
  QCOMPARE(true, mSettingsModel->surfExtendedDescriptor());
}

void TestSettingsModel::test_surfRotatedFeatures()
{
  mSettingsModel->setSurfRotatedFeatures(true);
  QCOMPARE(true, mSettingsModel->surfRotatedFeatures());
}

void TestSettingsModel::test_siftFeaturesNumber()
{
  mSettingsModel->setSiftFeaturesNumber(10000);
  QCOMPARE(10000, mSettingsModel->siftFeaturesNumber());
}

void TestSettingsModel::test_siftOctaveLayers()
{
  mSettingsModel->setSiftOctaveLayers(4);
  QCOMPARE(4, mSettingsModel->siftOctaveLayers());
}

void TestSettingsModel::test_siftContrastThreshold()
{
  mSettingsModel->setSiftContrastThreshold(0.1);
  QCOMPARE(0.1, mSettingsModel->siftContrastThreshold());
}

void TestSettingsModel::test_siftEdgeThreshold()
{
  mSettingsModel->setSiftEdgeThreshold(20.);
  QCOMPARE(20., mSettingsModel->siftEdgeThreshold());
}

void TestSettingsModel::test_siftSigma()
{
  mSettingsModel->setSiftSigma(1.);
  QCOMPARE(1., mSettingsModel->siftSigma());
}

void TestSettingsModel::test_starMaxSize()
{
  mSettingsModel->setStarMaxSize(25);
  QCOMPARE(25, mSettingsModel->starMaxSize());
}

void TestSettingsModel::test_starResponseThreshold()
{
  mSettingsModel->setStarResponseThreshold(15);
  QCOMPARE(15, mSettingsModel->starResponseThreshold());
}

void TestSettingsModel::test_starLineThresholdProjected()
{
  mSettingsModel->setStarLineThresholdProjected(5);
  QCOMPARE(5, mSettingsModel->starLineThresholdProjected());
}

void TestSettingsModel::test_starLineThresholdBinarized()
{
  mSettingsModel->setStarLineThresholdBinarized(4);
  QCOMPARE(4, mSettingsModel->starLineThresholdBinarized());
}

void TestSettingsModel::test_starSuppressNonmaxSize()
{
  mSettingsModel->setStarSuppressNonmaxSize(10);
  QCOMPARE(10, mSettingsModel->starSuppressNonmaxSize());
}

void TestSettingsModel::test_matchMatchingMethod()
{
//  mSettingsModel->setMatchMatchingMethod("Brute-Force");
//  QCOMPARE("Brute-Force", mSettingsModel->matchMatchingMethod());
}

void TestSettingsModel::test_matchNormType()
{
//  mSettingsModel->setMatchNormType("NORM_L1");
//  QCOMPARE("NORM_L1", mSettingsModel->matchNormType());
}

void TestSettingsModel::test_matchRatio()
{
//  mSettingsModel->setMatchRatio(0.5);
//  QCOMPARE(0.5, mSettingsModel->matchRatio());
}

void TestSettingsModel::test_matchDistance()
{
//  mSettingsModel->setMatchDistance(0.8);
//  QCOMPARE(0.8, mSettingsModel->matchDistance());
}

void TestSettingsModel::test_matchConfidence()
{
//  mSettingsModel->setMatchConfidence(0.95);
//  QCOMPARE(0.95, mSettingsModel->matchConfidence());
}

void TestSettingsModel::test_matchCrossMatching()
{
//  mSettingsModel->setMatchCrossMatching(false);
  //  QCOMPARE(false, mSettingsModel->matchCrossMatching());
}

void TestSettingsModel::test_keypointsViewerBGColor()
{
  mSettingsModel->setKeypointsViewerBGColor("#FF00FF");
  QCOMPARE("#FF00FF", mSettingsModel->keypointsViewerBGColor());
}

void TestSettingsModel::test_keypointsViewerMarkerType()
{
  mSettingsModel->setKeypointsViewerMarkerType(2);
  QCOMPARE(2, mSettingsModel->keypointsViewerMarkerType());
}

void TestSettingsModel::test_keypointsViewerMarkerSize()
{
  mSettingsModel->setKeypointsViewerMarkerSize(30);
  QCOMPARE(30, mSettingsModel->keypointsViewerMarkerSize());
}

void TestSettingsModel::test_keypointsViewerMarkerWidth()
{
  mSettingsModel->setKeypointsViewerMarkerWidth(3);
  QCOMPARE(3, mSettingsModel->keypointsViewerMarkerWidth());
}

void TestSettingsModel::test_keypointsViewerMarkerColor()
{
  mSettingsModel->setKeypointsViewerMarkerColor("#0000FF");
  QCOMPARE("#0000FF", mSettingsModel->keypointsViewerMarkerColor());
}

void TestSettingsModel::test_matchesViewerBGColor()
{
  mSettingsModel->setMatchesViewerBGColor("#FF0055");
  QCOMPARE("#FF0055", mSettingsModel->matchesViewerBGColor());
}

void TestSettingsModel::test_matchesViewerMarkerType()
{
  mSettingsModel->setMatchesViewerMarkerType(2);
  QCOMPARE(2, mSettingsModel->matchesViewerMarkerType());
}

void TestSettingsModel::test_matchesViewerMarkerSize()
{
  mSettingsModel->setMatchesViewerMarkerSize(30);
  QCOMPARE(30, mSettingsModel->matchesViewerMarkerSize());
}

void TestSettingsModel::test_matchesViewerMarkerWidth()
{
  mSettingsModel->setMatchesViewerMarkerWidth(3);
  QCOMPARE(3, mSettingsModel->matchesViewerMarkerWidth());
}

void TestSettingsModel::test_matchesViewerMarkerColor()
{
  mSettingsModel->setMatchesViewerMarkerColor("#330055");
  QCOMPARE("#330055", mSettingsModel->matchesViewerMarkerColor());
}

void TestSettingsModel::test_matchesViewerLineColor()
{
  mSettingsModel->setMatchesViewerLineColor("#340155");
  QCOMPARE("#340155", mSettingsModel->matchesViewerLineColor());
}

void TestSettingsModel::test_matchesViewerLineWidth()
{
  mSettingsModel->setMatchesViewerLineWidth(3);
  QCOMPARE(3, mSettingsModel->matchesViewerLineWidth());
}

void TestSettingsModel::test_groundTruthEditorBGColor()
{
  mSettingsModel->setGroundTruthEditorBGColor("#FF0055");
  QCOMPARE("#FF0055", mSettingsModel->groundTruthEditorBGColor());
}

void TestSettingsModel::test_groundTruthEditorMarkerSize()
{
  mSettingsModel->setGroundTruthEditorMarkerSize(30);
  QCOMPARE(30, mSettingsModel->groundTruthEditorMarkerSize());
}

void TestSettingsModel::test_groundTruthEditorMarkerWidth()
{
  mSettingsModel->setGroundTruthEditorMarkerWidth(3);
  QCOMPARE(3, mSettingsModel->groundTruthEditorMarkerWidth());
}

void TestSettingsModel::test_groundTruthEditorMarkerColor()
{
  mSettingsModel->setGroundTruthEditorMarkerColor("#330055");
  QCOMPARE("#330055", mSettingsModel->groundTruthEditorMarkerColor());
}

void TestSettingsModel::test_reset()
{
  mSettingsModel->setLanguage("es");
  mSettingsModel->setHistoryMaxSize(20);
  mSettingsModel->setImageViewerBGcolor("#ff00ff");

  mSettingsModel->setKeypointsFormat("YML");
  mSettingsModel->setMatchesFormat("YML");

  mSettingsModel->setUseCuda(true);

  mSettingsModel->setAcebsfBlockSize(QSize(20, 20));
  mSettingsModel->setAcebsfL(0.05);
  mSettingsModel->setAcebsfK1(9.);
  mSettingsModel->setAcebsfK2(0.5);
  mSettingsModel->setClaheClipLimit(20.);
  mSettingsModel->setClaheTilesGridSize(QSize(4, 4));
  mSettingsModel->setCmbfheBlockSize(QSize(7,7));
  mSettingsModel->setDheX(3);
  mSettingsModel->setFaheBlockSize(QSize(7,7));
  mSettingsModel->setHmclaheBlockSize(QSize(7,7));
  mSettingsModel->setHmclaheL(0.06);
  mSettingsModel->setHmclahePhi(0.4);
  mSettingsModel->setLceBsescsBlockSize(QSize(11, 11));
  mSettingsModel->setMsrcpSmallScale(5.);
  mSettingsModel->setMsrcpMidScale(80.);
  mSettingsModel->setMsrcpLargeScale(180.);
  mSettingsModel->setNoshpBlockSize(QSize(50, 50));
  mSettingsModel->setPoheBlockSize(QSize(50, 50));
  mSettingsModel->setRswheHistogramDivisions(4);
  mSettingsModel->setRswheHistogramCut(1);
  mSettingsModel->setWallisContrast(2.0);
  mSettingsModel->setWallisBrightness(0.4);
  mSettingsModel->setWallisImposedAverage(11);
  mSettingsModel->setWallisImposedLocalStdDev(25);
  mSettingsModel->setWallisKernelSize(20);
  mSettingsModel->setAgastThreshold(30);
  mSettingsModel->setAgastDetectorType("AGAST_7_12s");
  mSettingsModel->setAgastNonmaxSuppression(false);
  mSettingsModel->setAkazeOctaves(3);
  mSettingsModel->setAkazeThreshold(0.005);
  mSettingsModel->setAkazeDiffusivity("DIFF_CHARBONNIER");
  mSettingsModel->setAkazeOctaveLayers(3);
  mSettingsModel->setAkazeDescriptorSize(32);
  mSettingsModel->setAkazeDescriptorType("MLDB_UPRIGHT");
  mSettingsModel->setAkazeDescriptorChannels(4);
  mSettingsModel->setBoostDescriptorType("BINBOOST_64");
  mSettingsModel->setBoostUseOrientation(false);
  mSettingsModel->setBoostScaleFactor(5.);
  mSettingsModel->setBriefBytes("16");
  mSettingsModel->setBriefUseOrientation(true);
  mSettingsModel->setBriskThreshold(20);
  mSettingsModel->setBriskOctaves(2);
  mSettingsModel->setBriskPatternScale(0.5);
  mSettingsModel->setDaisyRadius(10.);
  mSettingsModel->setDaisyQRadius(2);
  mSettingsModel->setDaisyQTheta(4);
  mSettingsModel->setDaisyQHist(4);
  mSettingsModel->setDaisyNorm("NRM_PARTIAL");
  mSettingsModel->setDaisyInterpolation(false);
  mSettingsModel->setDaisyUseOrientation(true);
  mSettingsModel->setFastThreshold(20);
  mSettingsModel->setFastNonmaxSuppression(false);
  mSettingsModel->setFastDetectorType("TYPE_7_12");
  mSettingsModel->setFreakOrientationNormalized(false);
  mSettingsModel->setFreakScaleNormalized(false);
  mSettingsModel->setFreakPatternScale(11.);
  mSettingsModel->setFreakOctaves(6);
  mSettingsModel->setGfttMaxFeatures(500);
  mSettingsModel->setGfttQualityLevel(0.1);
  mSettingsModel->setGfttMinDistance(2);
  mSettingsModel->setGfttBlockSize(6);
  mSettingsModel->setGfttHarrisDetector(true);
  mSettingsModel->setGfttK(0.2);
  mSettingsModel->setHogWinSize(QSize(64,64));
  mSettingsModel->setHogBlockSize(QSize(8,8));
  mSettingsModel->setHogBlockStride(QSize(4,4));
  mSettingsModel->setHogCellSize(QSize(4,4));
  mSettingsModel->setHogNbins(6);
  mSettingsModel->setHogDerivAperture(2);
  mSettingsModel->setKazeExtendedDescriptor(true);
  mSettingsModel->setKazeUpright(true);
  mSettingsModel->setKazeThreshold(0.005);
  mSettingsModel->setKazeOctaves(2);
  mSettingsModel->setKazeOctaveLayers(3);
  mSettingsModel->setKazeDiffusivity("DIFF_WEICKERT");
  mSettingsModel->setLatchBytes("16");
  mSettingsModel->setLatchRotationInvariance(true);
  mSettingsModel->setLatchHalfSsdSize(5);
  mSettingsModel->setLucidKernel(2);
  mSettingsModel->setLucidBlurKernel(3);
  mSettingsModel->setMsdThresholdSaliency(150);
  mSettingsModel->setMsdPathRadius(5);
  mSettingsModel->setMsdKNN(2);
  mSettingsModel->setMsdAreaRadius(10);
  mSettingsModel->setMsdScaleFactor(1.5);
  mSettingsModel->setMsdNMSRadius(10);
  mSettingsModel->setMsdNScales(-1);
  mSettingsModel->setMsdNMSScaleR(1);
  mSettingsModel->setMsdComputeOrientations(true);
  mSettingsModel->setMsdAffineMSD(true);
  mSettingsModel->setMsdTilts(5);
  mSettingsModel->setMserDelta(10);
  mSettingsModel->setMserMinArea(120);
  mSettingsModel->setMserMaxArea(10000);
  mSettingsModel->setMserMaxVariation(0.5);
  mSettingsModel->setMserMinDiversity(0.5);
  mSettingsModel->setMserMaxEvolution(100);
  mSettingsModel->setMserAreaThreshold(1.5);
  mSettingsModel->setMserMinMargin(0.05);
  mSettingsModel->setMserEdgeBlurSize(10);
  mSettingsModel->setOrbFeaturesNumber(6000);
  mSettingsModel->setOrbScaleFactor(1.5);
  mSettingsModel->setOrbLevelsNumber(4);
  mSettingsModel->setOrbEdgeThreshold(15);
  mSettingsModel->setOrbWTA_K(4);
  mSettingsModel->setOrbScoreType("FAST");
  mSettingsModel->setOrbPatchSize(11);
  mSettingsModel->setOrbFastThreshold(50);
  mSettingsModel->setSurfOctaves(2);
  mSettingsModel->setSurfOctaveLayers(2);
  mSettingsModel->setSurfRotatedFeatures(true);
  mSettingsModel->setSurfHessianThreshold(50);
  mSettingsModel->setSurfExtendedDescriptor(true);
  mSettingsModel->setSiftSigma(3.2);
  mSettingsModel->setSiftOctaveLayers(4);
  mSettingsModel->setSiftEdgeThreshold(5.);
  mSettingsModel->setSiftFeaturesNumber(10000);
  mSettingsModel->setSiftContrastThreshold(0.1);
  mSettingsModel->setStarResponseThreshold(15);
  mSettingsModel->setStarMaxSize(25);
  mSettingsModel->setStarLineThresholdProjected(5);
  mSettingsModel->setStarLineThresholdBinarized(4);
  mSettingsModel->setStarSuppressNonmaxSize(10);
  mSettingsModel->setVggDescriptorType("VGG_80");
  mSettingsModel->setVggScaleFactor(5.);
  mSettingsModel->setVggSigma(1.1);
  mSettingsModel->setVggUseNormalizeDescriptor(true);
  mSettingsModel->setVggUseNormalizeImage(false);
  mSettingsModel->setVggUseScaleOrientation(false);
  mSettingsModel->setKeypointsViewerBGColor("#ffffff");
  mSettingsModel->setKeypointsViewerMarkerType(2);
  mSettingsModel->setKeypointsViewerMarkerSize(30);
  mSettingsModel->setKeypointsViewerMarkerWidth(5);
  mSettingsModel->setKeypointsViewerMarkerColor("#ffffff");
  mSettingsModel->setKeypointsViewerSelectMarkerWidth(1);
  mSettingsModel->setKeypointsViewerSelectMarkerColor("#ffffff");
  mSettingsModel->setMatchesViewerBGColor("#ffffff");
  mSettingsModel->setMatchesViewerMarkerType(2);
  mSettingsModel->setMatchesViewerMarkerSize(25);
  mSettingsModel->setMatchesViewerMarkerWidth(5);
  mSettingsModel->setMatchesViewerMarkerColor("#ffffff");
  mSettingsModel->setMatchesViewerLineColor("#ffffff");
  mSettingsModel->setMatchesViewerLineWidth(5);
  mSettingsModel->setMatchesViewerSelectMarkerWidth(3);
  mSettingsModel->setMatchesViewerSelectMarkerColor("#ffffff");
  mSettingsModel->setGroundTruthEditorBGColor("#ffffff");
  mSettingsModel->setGroundTruthEditorMarkerSize(25);
  mSettingsModel->setGroundTruthEditorMarkerWidth(5);
  mSettingsModel->setGroundTruthEditorMarkerColor("#ffffff");
  mSettingsModel->setGroundTruthEditorSelectMarkerWidth(4);
  mSettingsModel->setGroundTruthEditorSelectMarkerColor("#ffffff");

  mSettingsModel->reset();

  QCOMPARE("en", mSettingsModel->language());

  QCOMPARE(10, mSettingsModel->historyMaxSize());
  QCOMPARE(QStringList(), mSettingsModel->history());

  QCOMPARE(QString("#dcdcdc"), mSettingsModel->imageViewerBGcolor());

  QCOMPARE(QString("XML"), mSettingsModel->keypointsFormat());
  QCOMPARE(QString("XML"), mSettingsModel->matchesFormat());

  QCOMPARE(false, mSettingsModel->useCuda());

  QCOMPARE(QSize(8, 8), mSettingsModel->acebsfBlockSize());
  QCOMPARE(0.03, mSettingsModel->acebsfL());
  QCOMPARE(10., mSettingsModel->acebsfK1());
  QCOMPARE(0.5, mSettingsModel->acebsfK2());

  QCOMPARE(40., mSettingsModel->claheClipLimit());
  QCOMPARE(QSize(8, 8), mSettingsModel->claheTilesGridSize());

  QCOMPARE(QSize(11,11), mSettingsModel->cmbfheBlockSize());

  QCOMPARE(1, mSettingsModel->dheX());

  QCOMPARE(QSize(11,11), mSettingsModel->faheBlockSize());

  QCOMPARE(QSize(17,17), mSettingsModel->hmclaheBlockSize());
  QCOMPARE(0.03, mSettingsModel->hmclaheL());
  QCOMPARE(0.5, mSettingsModel->hmclahePhi());

  QCOMPARE(QSize(33, 33), mSettingsModel->lceBsescsBlockSize());

  QCOMPARE(10., mSettingsModel->msrcpSmallScale());
  QCOMPARE(100., mSettingsModel->msrcpMidScale());
  QCOMPARE(220., mSettingsModel->msrcpLargeScale());

  QCOMPARE(QSize(127, 127), mSettingsModel->noshpBlockSize());

  QCOMPARE(QSize(127, 127), mSettingsModel->poheBlockSize());

  QCOMPARE(2, mSettingsModel->rswheHistogramDivisions());
  QCOMPARE(0, mSettingsModel->rswheHistogramCut());

  QCOMPARE(1.0, mSettingsModel->wallisContrast());
  QCOMPARE(0.2, mSettingsModel->wallisBrightness());
  QCOMPARE(41, mSettingsModel->wallisImposedAverage());
  QCOMPARE(127, mSettingsModel->wallisImposedLocalStdDev());
  QCOMPARE(50, mSettingsModel->wallisKernelSize());

  QCOMPARE(10, mSettingsModel->agastThreshold());
  QCOMPARE(true, mSettingsModel->agastNonmaxSuppression());
  QCOMPARE("OAST_9_16", mSettingsModel->agastDetectorType());

  QCOMPARE("MLDB", mSettingsModel->akazeDescriptorType());
  QCOMPARE(0, mSettingsModel->akazeDescriptorSize());
  QCOMPARE(3, mSettingsModel->akazeDescriptorChannels());
  QCOMPARE(0.001, mSettingsModel->akazeThreshold());
  QCOMPARE(4, mSettingsModel->akazeOctaves());
  QCOMPARE(4, mSettingsModel->akazeOctaveLayers());
  QCOMPARE("DIFF_PM_G2", mSettingsModel->akazeDiffusivity());

  QCOMPARE("32", mSettingsModel->briefBytes());
  QCOMPARE(false, mSettingsModel->briefUseOrientation());

  QCOMPARE("BINBOOST_256", mSettingsModel->boostDescriptorType());
  QCOMPARE(true, mSettingsModel->boostUseOrientation());
  QCOMPARE(6.25, mSettingsModel->boostScaleFactor());

  QCOMPARE(30, mSettingsModel->briskThreshold());
  QCOMPARE(3, mSettingsModel->briskOctaves());
  QCOMPARE(1., mSettingsModel->briskPatternScale());

  QCOMPARE(15., mSettingsModel->daisyRadius());
  QCOMPARE(3, mSettingsModel->daisyQRadius());
  QCOMPARE(8, mSettingsModel->daisyQTheta());
  QCOMPARE(8, mSettingsModel->daisyQHist());
  QCOMPARE("NRM_NONE", mSettingsModel->daisyNorm());
  QCOMPARE(true, mSettingsModel->daisyInterpolation());
  QCOMPARE(false, mSettingsModel->daisyUseOrientation());

  QCOMPARE(10, mSettingsModel->fastThreshold());
  QCOMPARE(true, mSettingsModel->fastNonmaxSuppression());
  QCOMPARE("TYPE_9_16", mSettingsModel->fastdetectorType());

  QCOMPARE(true, mSettingsModel->freakOrientationNormalized());
  QCOMPARE(true, mSettingsModel->freakScaleNormalized());
  QCOMPARE(22., mSettingsModel->freakPatternScale());
  QCOMPARE(4, mSettingsModel->freakOctaves());

  QCOMPARE(1000, mSettingsModel->gfttMaxFeatures());
  QCOMPARE(0.01, mSettingsModel->gfttQualityLevel());
  QCOMPARE(1, mSettingsModel->gfttMinDistance());
  QCOMPARE(3, mSettingsModel->gfttBlockSize());
  QCOMPARE(false, mSettingsModel->gfttHarrisDetector());
  QCOMPARE(0.04, mSettingsModel->gfttK());

  QCOMPARE(QSize(16,16), mSettingsModel->hogWinSize());
  QCOMPARE(QSize(4,4), mSettingsModel->hogBlockSize());
  QCOMPARE(QSize(2,2), mSettingsModel->hogBlockStride());
  QCOMPARE(QSize(2,2), mSettingsModel->hogCellSize());
  QCOMPARE(9, mSettingsModel->hogNbins());
  QCOMPARE(1, mSettingsModel->hogDerivAperture());

  QCOMPARE(false, mSettingsModel->kazeExtendedDescriptor());
  QCOMPARE(false, mSettingsModel->kazeUpright());
  QCOMPARE(0.001, mSettingsModel->kazeThreshold());
  QCOMPARE(4, mSettingsModel->kazeOctaves());
  QCOMPARE(4, mSettingsModel->kazeOctaveLayers());
  QCOMPARE("DIFF_PM_G2", mSettingsModel->kazeDiffusivity());

  QCOMPARE("32", mSettingsModel->latchBytes());
  QCOMPARE(true, mSettingsModel->latchRotationInvariance());
  QCOMPARE(3, mSettingsModel->latchHalfSsdSize());

  QCOMPARE(1, mSettingsModel->lucidKernel());
  QCOMPARE(2, mSettingsModel->lucidBlurKernel());

  QCOMPARE(250, mSettingsModel->msdThresholdSaliency());
  QCOMPARE(3, mSettingsModel->msdPathRadius());
  QCOMPARE(4, mSettingsModel->msdKnn());
  QCOMPARE(5, mSettingsModel->msdAreaRadius());
  QCOMPARE(1.25, mSettingsModel->msdScaleFactor());
  QCOMPARE(5, mSettingsModel->msdNMSRadius());
  QCOMPARE(-1, mSettingsModel->msdNScales());
  QCOMPARE(0, mSettingsModel->msdNMSScaleR());
  QCOMPARE(false, mSettingsModel->msdComputeOrientations());
  QCOMPARE(false, mSettingsModel->msdAffineMSD());
  QCOMPARE(3, mSettingsModel->msdTilts());

  QCOMPARE(5, mSettingsModel->mserDelta());
  QCOMPARE(60, mSettingsModel->mserMinArea());
  QCOMPARE(14400, mSettingsModel->mserMaxArea());
  QCOMPARE(0.25, mSettingsModel->mserMaxVariation());
  QCOMPARE(0.2, mSettingsModel->mserMinDiversity());
  QCOMPARE(200, mSettingsModel->mserMaxEvolution());
  QCOMPARE(1.01, mSettingsModel->mserAreaThreshold());
  QCOMPARE(0.003, mSettingsModel->mserMinMargin());
  QCOMPARE(5, mSettingsModel->mserEdgeBlurSize());

  QCOMPARE(5000, mSettingsModel->orbFeaturesNumber());
  QCOMPARE(1.2, mSettingsModel->orbScaleFactor());
  QCOMPARE(8, mSettingsModel->orbLevelsNumber());
  QCOMPARE(31, mSettingsModel->orbEdgeThreshold());
  QCOMPARE(2, mSettingsModel->orbWta_k());
  QCOMPARE("Harris", mSettingsModel->orbScoreType());
  QCOMPARE(31, mSettingsModel->orbPatchSize());
  QCOMPARE(20, mSettingsModel->orbFastThreshold());

  QCOMPARE(100, mSettingsModel->surfHessianThreshold());
  QCOMPARE(4, mSettingsModel->surfOctaves());
  QCOMPARE(3, mSettingsModel->surfOctaveLayers());
  QCOMPARE(false, mSettingsModel->surfExtendedDescriptor());
  QCOMPARE(false, mSettingsModel->surfRotatedFeatures());

  QCOMPARE(5000, mSettingsModel->siftFeaturesNumber());
  QCOMPARE(3, mSettingsModel->siftOctaveLayers());
  QCOMPARE(0.04, mSettingsModel->siftContrastThreshold());
  QCOMPARE(10., mSettingsModel->siftEdgeThreshold());
  QCOMPARE(1.6, mSettingsModel->siftSigma());

  QCOMPARE(45, mSettingsModel->starMaxSize());
  QCOMPARE(30, mSettingsModel->starResponseThreshold());
  QCOMPARE(10, mSettingsModel->starLineThresholdProjected());
  QCOMPARE(8, mSettingsModel->starLineThresholdBinarized());
  QCOMPARE(5, mSettingsModel->starSuppressNonmaxSize());

  QCOMPARE("VGG_120", mSettingsModel->vggDescriptorType());
  QCOMPARE(6.25, mSettingsModel->vggScaleFactor());
  QCOMPARE(1.4, mSettingsModel->vggSigma());
  QCOMPARE(false, mSettingsModel->vggUseNormalizeDescriptor());
  QCOMPARE(true, mSettingsModel->vggUseNormalizeImage());
  QCOMPARE(true, mSettingsModel->vggUseScaleOrientation());

  QCOMPARE("#dcdcdc", mSettingsModel->keypointsViewerBGColor());
  QCOMPARE(0, mSettingsModel->keypointsViewerMarkerType());
  QCOMPARE(20, mSettingsModel->keypointsViewerMarkerSize());
  QCOMPARE(2, mSettingsModel->keypointsViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettingsModel->keypointsViewerMarkerColor());
  QCOMPARE(2, mSettingsModel->keypointsViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettingsModel->keypointsViewerSelectMarkerColor());

  QCOMPARE("#dcdcdc", mSettingsModel->matchesViewerBGColor());
  QCOMPARE(0, mSettingsModel->matchesViewerMarkerType());
  QCOMPARE(20, mSettingsModel->matchesViewerMarkerSize());
  QCOMPARE(2, mSettingsModel->matchesViewerMarkerWidth());
  QCOMPARE("#00aa00", mSettingsModel->matchesViewerMarkerColor());
  QCOMPARE("#0000ff", mSettingsModel->matchesViewerLineColor());
  QCOMPARE(2, mSettingsModel->matchesViewerLineWidth());
  QCOMPARE(2, mSettingsModel->matchesViewerSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettingsModel->matchesViewerSelectMarkerColor());

  QCOMPARE("#dcdcdc", mSettingsModel->groundTruthEditorBGColor());
  QCOMPARE(20, mSettingsModel->groundTruthEditorMarkerSize());
  QCOMPARE(2, mSettingsModel->groundTruthEditorMarkerWidth());
  QCOMPARE("#00aa00", mSettingsModel->groundTruthEditorMarkerColor());
  QCOMPARE(2, mSettingsModel->groundTruthEditorSelectMarkerWidth());
  QCOMPARE("#e5097e", mSettingsModel->groundTruthEditorSelectMarkerColor());
}

QTEST_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"
