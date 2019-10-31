#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/GfttWidget.h"

using namespace photomatch;

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
  void test_windowTitle();
  void test_maxFeatures_data();
  void test_maxFeatures();
  void test_qualityLevel_data();
  void test_qualityLevel();
  void test_minDistance_data();
  void test_minDistance();
  void test_blockSize_data();
  void test_blockSize();
  void test_harrisDetector_data();
  void test_harrisDetector();
  void test_k_data();
  void test_k();
  void test_reset();

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
  QCOMPARE(1000, mGfttWidget->maxFeatures());
  QCOMPARE(0.01, mGfttWidget->qualityLevel());
  QCOMPARE(1, mGfttWidget->minDistance());
  QCOMPARE(3, mGfttWidget->blockSize());
  QCOMPARE(false, mGfttWidget->harrisDetector());
  QCOMPARE(0.04, mGfttWidget->k());
}

void TestGfttWidget::test_windowTitle()
{
  QCOMPARE("GFTT", mGfttWidget->windowTitle());
}

void TestGfttWidget::test_maxFeatures_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("1000000") << 1000000 << 1000000;
  QTest::newRow("Out of range value") << 1000001 << 1000000;
}

void TestGfttWidget::test_maxFeatures()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mGfttWidget->setMaxFeatures(value);
  QCOMPARE(result, mGfttWidget->maxFeatures());
}

void TestGfttWidget::test_qualityLevel_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.01 << 0.01;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestGfttWidget::test_qualityLevel()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setQualityLevel(value);
  QCOMPARE(result, mGfttWidget->qualityLevel());
}

void TestGfttWidget::test_minDistance_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 1. << 1.;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("10000.") << 10000. << 10000.;
  QTest::newRow("Out of range value") << 10000.1 << 10000.;
}

void TestGfttWidget::test_minDistance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setMinDistance(value);
  QCOMPARE(result, mGfttWidget->minDistance());
}

void TestGfttWidget::test_blockSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("default") << 3 << 3;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestGfttWidget::test_blockSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mGfttWidget->setBlockSize(value);
  QCOMPARE(result, mGfttWidget->blockSize());
}

void TestGfttWidget::test_harrisDetector_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestGfttWidget::test_harrisDetector()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mGfttWidget->setHarrisDetector(value);
  QCOMPARE(result, mGfttWidget->harrisDetector());
}

void TestGfttWidget::test_k_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.04 << 0.04;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestGfttWidget::test_k()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGfttWidget->setK(value);
  QCOMPARE(result, mGfttWidget->k());
}

void TestGfttWidget::test_reset()
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
