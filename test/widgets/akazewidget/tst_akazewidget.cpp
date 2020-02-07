#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/AkazeWidget.h"

using namespace photomatch;

class TestAkazeWidget : public QObject
{
  Q_OBJECT

public:
  TestAkazeWidget();
  ~TestAkazeWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_descriptorType_data();
  void test_descriptorType();
  void test_descriptorSize_data();
  void test_descriptorSize();
  void test_descriptorChannels_data();
  void test_descriptorChannels();
  void test_threshold_data();
  void test_threshold();
  void test_octaves_data();
  void test_octaves();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_diffusivity_data();
  void test_diffusivity();

private:

  AkazeWidget *mAkazeWidget;

};

TestAkazeWidget::TestAkazeWidget()
{
  mAkazeWidget = new AkazeWidgetImp();
}

TestAkazeWidget::~TestAkazeWidget()
{
  if (mAkazeWidget){
    delete mAkazeWidget;
    mAkazeWidget = nullptr;
  }
}

void TestAkazeWidget::initTestCase()
{
  QCOMPARE("MLDB", mAkazeWidget->descriptorType());
  QCOMPARE(0, mAkazeWidget->descriptorSize());
  QCOMPARE(3, mAkazeWidget->descriptorChannels());
  QCOMPARE(0.001, mAkazeWidget->threshold());
  QCOMPARE(4, mAkazeWidget->octaves());
  QCOMPARE(4, mAkazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mAkazeWidget->diffusivity());
}

void TestAkazeWidget::cleanupTestCase()
{
  mAkazeWidget->setDescriptorType("KAZE");
  mAkazeWidget->setDescriptorSize(32);
  mAkazeWidget->setDescriptorChannels(2);
  mAkazeWidget->setThreshold(50.);
  mAkazeWidget->setOctaves(2);
  mAkazeWidget->setOctaveLayers(5);
  mAkazeWidget->setDiffusivity("DIFF_PM_G1");

  mAkazeWidget->reset();

  QCOMPARE("MLDB", mAkazeWidget->descriptorType());
  QCOMPARE(0, mAkazeWidget->descriptorSize());
  QCOMPARE(3, mAkazeWidget->descriptorChannels());
  QCOMPARE(0.001, mAkazeWidget->threshold());
  QCOMPARE(4, mAkazeWidget->octaves());
  QCOMPARE(4, mAkazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mAkazeWidget->diffusivity());
}

void TestAkazeWidget::test_windowTitle()
{
  QCOMPARE("AKAZE", mAkazeWidget->windowTitle());
}

void TestAkazeWidget::test_descriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("KAZE") << "KAZE" << "KAZE";
  QTest::newRow("KAZE_UPRIGHT") << "KAZE_UPRIGHT" << "KAZE_UPRIGHT";
  QTest::newRow("MLDB") << "MLDB" << "MLDB";
  QTest::newRow("MLDB_UPRIGHT") << "MLDB_UPRIGHT" << "MLDB_UPRIGHT";
  QTest::newRow("bad_value") << "bad_value" << "MLDB_UPRIGHT";
}

void TestAkazeWidget::test_descriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAkazeWidget->setDescriptorType(value);
  QCOMPARE(result, mAkazeWidget->descriptorType());
}

void TestAkazeWidget::test_descriptorSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("32") << 32 << 32;
  QTest::newRow("64") << 64 << 64;
  QTest::newRow("Out of range value") << 124 << 64;
}

void TestAkazeWidget::test_descriptorSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setDescriptorSize(value);
  QCOMPARE(result, mAkazeWidget->descriptorSize());
}

void TestAkazeWidget::test_descriptorChannels_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("3") << 3 << 3;
  QTest::newRow("Out of range value") << 4 << 3;
}

void TestAkazeWidget::test_descriptorChannels()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setDescriptorChannels(value);
  QCOMPARE(result, mAkazeWidget->descriptorChannels());
}

void TestAkazeWidget::test_threshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 100. << 99.99;
}

void TestAkazeWidget::test_threshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAkazeWidget->setThreshold(value);
  QCOMPARE(result, mAkazeWidget->threshold());
}

void TestAkazeWidget::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAkazeWidget::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setOctaves(value);
  QCOMPARE(result, mAkazeWidget->octaves());
}

void TestAkazeWidget::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAkazeWidget::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setOctaveLayers(value);
  QCOMPARE(result, mAkazeWidget->octaveLayers());
}

void TestAkazeWidget::test_diffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestAkazeWidget::test_diffusivity()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAkazeWidget->setDiffusivity(value);
  QCOMPARE(result, mAkazeWidget->diffusivity());
}


QTEST_MAIN(TestAkazeWidget)

#include "tst_akazewidget.moc"
