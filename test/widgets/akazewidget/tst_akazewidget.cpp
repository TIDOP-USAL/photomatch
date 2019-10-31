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
  void testDefaultConstructor();
  void test_windowTitle();
  void testDescriptorType_data();
  void testDescriptorType();
  void testDescriptorSize_data();
  void testDescriptorSize();
  void testDescriptorChannels_data();
  void testDescriptorChannels();
  void testThreshold_data();
  void testThreshold();
  void testOctaves_data();
  void testOctaves();
  void testOctaveLayers_data();
  void testOctaveLayers();
  void testDiffusivity_data();
  void testDiffusivity();
  void testReset();

private:

  IAkazeWidget *mAkazeWidget;

};

TestAkazeWidget::TestAkazeWidget()
{
  mAkazeWidget = new AkazeWidget();
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

}

void TestAkazeWidget::cleanupTestCase()
{

}

void TestAkazeWidget::testDefaultConstructor()
{
  /// Check default values
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

void TestAkazeWidget::testDescriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("KAZE") << "KAZE" << "KAZE";
  QTest::newRow("KAZE_UPRIGHT") << "KAZE_UPRIGHT" << "KAZE_UPRIGHT";
  QTest::newRow("MLDB") << "MLDB" << "MLDB";
  QTest::newRow("MLDB_UPRIGHT") << "MLDB_UPRIGHT" << "MLDB_UPRIGHT";
  QTest::newRow("bad_value") << "bad_value" << "MLDB_UPRIGHT";
}

void TestAkazeWidget::testDescriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAkazeWidget->setDescriptorType(value);
  QCOMPARE(result, mAkazeWidget->descriptorType());
}

void TestAkazeWidget::testDescriptorSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("32") << 32 << 32;
  QTest::newRow("64") << 64 << 64;
  QTest::newRow("Out of range value") << 124 << 64;
}

void TestAkazeWidget::testDescriptorSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setDescriptorSize(value);
  QCOMPARE(result, mAkazeWidget->descriptorSize());
}

void TestAkazeWidget::testDescriptorChannels_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("3") << 3 << 3;
  QTest::newRow("Out of range value") << 4 << 3;
}

void TestAkazeWidget::testDescriptorChannels()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setDescriptorChannels(value);
  QCOMPARE(result, mAkazeWidget->descriptorChannels());
}

void TestAkazeWidget::testThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 100. << 99.99;
}

void TestAkazeWidget::testThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAkazeWidget->setThreshold(value);
  QCOMPARE(result, mAkazeWidget->threshold());
}

void TestAkazeWidget::testOctaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAkazeWidget::testOctaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setOctaves(value);
  QCOMPARE(result, mAkazeWidget->octaves());
}

void TestAkazeWidget::testOctaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAkazeWidget::testOctaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAkazeWidget->setOctaveLayers(value);
  QCOMPARE(result, mAkazeWidget->octaveLayers());
}

void TestAkazeWidget::testDiffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestAkazeWidget::testDiffusivity()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAkazeWidget->setDiffusivity(value);
  QCOMPARE(result, mAkazeWidget->diffusivity());
}

void TestAkazeWidget::testReset()
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

QTEST_MAIN(TestAkazeWidget)

#include "tst_akazewidget.moc"
