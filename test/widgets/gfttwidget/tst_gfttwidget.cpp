#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/GfttWidget.h"

using namespace fme;

class TestGfttWidget : public QObject
{
  Q_OBJECT

public:

  TestGfttWidget();
  ~TestGfttWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testMaxFeatures_data();
  void testMaxFeatures();
  void testQualityLevel_data();
  void testQualityLevel();
  void testMinDistance_data();
  void testMinDistance();
  void testBlockSize_data();
  void testBlockSize();
  void testHarrisDetector_data();
  void testHarrisDetector();
  void testB_data();
  void testB();
  void testReset();

private:

  IGfttWidget *mGfttWidget;
};

TestGfttWidget::TestGfttWidget()
  : mGfttWidget(new GfttWidget)
{

}

TestGfttWidget::~TestGfttWidget()
{
  delete mGfttWidget;
  mGfttWidget = nullptr;
}

void TestGfttWidget::initTestCase()
{

}

void TestGfttWidget::cleanupTestCase()
{

}

void TestGfttWidget::testDefaultConstructor()
{
  /// Check default values
  GfttWidget gfttWidget;
  QCOMPARE(1000, gfttWidget.maxFeatures());
  QCOMPARE(0.01, gfttWidget.qualityLevel());
  QCOMPARE(1, gfttWidget.minDistance());
  QCOMPARE(3, gfttWidget.blockSize());
  QCOMPARE(false, gfttWidget.harrisDetector());
  QCOMPARE(0.04, gfttWidget.k());
}

void TestGfttWidget::testMaxFeatures_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("1000000") << 1000000 << 1000000;
  QTest::newRow("Out of range value") << 1000001 << 1000000;
}

void TestGfttWidget::testMaxFeatures()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mGfttWidget->setMaxFeatures(value);
  QCOMPARE(result, mGfttWidget->maxFeatures());
}

void TestGfttWidget::testQualityLevel_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.01 << 0.01;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestGfttWidget::testQualityLevel()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setQualityLevel(value);
  QCOMPARE(result, mGfttWidget->qualityLevel());
}

void TestGfttWidget::testMinDistance_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 1. << 1.;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("10000.") << 10000. << 10000.;
  QTest::newRow("Out of range value") << 10000.1 << 10000.;
}

void TestGfttWidget::testMinDistance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setMinDistance(value);
  QCOMPARE(result, mGfttWidget->minDistance());
}

void TestGfttWidget::testBlockSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("default") << 3 << 3;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestGfttWidget::testBlockSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mGfttWidget->setBlockSize(value);
  QCOMPARE(result, mGfttWidget->blockSize());
}

void TestGfttWidget::testHarrisDetector_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestGfttWidget::testHarrisDetector()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mGfttWidget->setHarrisDetector(value);
  QCOMPARE(result, mGfttWidget->harrisDetector());
}

void TestGfttWidget::testB_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.04 << 0.04;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestGfttWidget::testB()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setK(value);
  QCOMPARE(result, mGfttWidget->k());
}

void TestGfttWidget::testReset()
{
  mGfttWidget->setMaxFeatures(5000);
  mGfttWidget->setQualityLevel(0.1);
  mGfttWidget->setMinDistance(3.);
  mGfttWidget->setBlockSize(1);
  mGfttWidget->setHarrisDetector(true);
  mGfttWidget->setK(0.1);

  mGfttWidget->reset();

  QCOMPARE(1000, mGfttWidget->maxFeatures());
  QCOMPARE(0.01, mGfttWidget->qualityLevel());
  QCOMPARE(1., mGfttWidget->minDistance());
  QCOMPARE(3, mGfttWidget->blockSize());
  QCOMPARE(false, mGfttWidget->harrisDetector());
  QCOMPARE(0.04, mGfttWidget->k());
}

QTEST_MAIN(TestGfttWidget)

#include "tst_gfttwidget.moc"
