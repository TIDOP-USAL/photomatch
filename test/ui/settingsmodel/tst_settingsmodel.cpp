#include <QtTest>

#include "fme/ui/SettingsModel.h"

using namespace fme;


class SettingsRWFake
  : public ISettingsRW
{

protected:

  struct Data{
    QString lang = "en";
    QStringList history;
  };

public:

  SettingsRWFake()
    : ISettingsRW()
  {}

  ~SettingsRWFake() override {}

// ISettingsRW interface

public:

  void read(ISettings &settings) override
  {
    settings.setLanguage(this->data.lang);
  }

  void write(const ISettings &settings) override
  {
    this->data.lang = settings.language();
  }

  void writeHistory(const ISettings &settings) override
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

  /* CLAHE */
  void test_claheClipLimit();
  void test_claheTilesGridSize();

  /* FAHE */
  void test_faheBlockSize();

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

  void test_reset();

protected:

  ISettings *mSettings;
  ISettingsRW *mSettingsRWFake;
  ISettingsModel *mSettingsModel;

};

TestSettingsModel::TestSettingsModel()
  : mSettings(new Settings),
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
  Settings settings;
  SettingsRWFake rw;
  SettingsModel settingsModel(&settings, &rw);

  QCOMPARE("en", settingsModel.language());

  QCOMPARE(10, settingsModel.historyMaxSize());
  QCOMPARE(QStringList(), settingsModel.history());

  QCOMPARE(40., settingsModel.claheClipLimit());
  QCOMPARE(QSize(8, 8), settingsModel.claheTilesGridSize());

  QCOMPARE(QSize(11,11), settingsModel.faheBlockSize());

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
  QCOMPARE("fme_en.qm", languages[0]);
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

void TestSettingsModel::test_faheBlockSize()
{
  mSettingsModel->setFaheBlockSize(QSize(7,7));
  QCOMPARE(QSize(7,7), mSettingsModel->faheBlockSize());
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

void TestSettingsModel::test_reset()
{
  mSettingsModel->setLanguage("es");
  mSettingsModel->setClaheClipLimit(20.);
  mSettingsModel->setClaheTilesGridSize(QSize(4, 4));
  mSettingsModel->setFaheBlockSize(QSize(7,7));
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

  mSettingsModel->reset();

  QCOMPARE("en", mSettingsModel->language());

  QCOMPARE(40., mSettingsModel->claheClipLimit());
  QCOMPARE(QSize(8, 8), mSettingsModel->claheTilesGridSize());

  QCOMPARE(QSize(11,11), mSettingsModel->faheBlockSize());

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
}

QTEST_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"
