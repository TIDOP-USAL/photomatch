#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/SiftWidget.h"

using namespace fme;

class TestSiftWidget : public QObject
{
  Q_OBJECT

public:
  TestSiftWidget();
  ~TestSiftWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testFeaturesNumber_data();
  void testFeaturesNumber();
  void testOctaveLayers_data();
  void testOctaveLayers();
  void testContrastThreshold_data();
  void testContrastThreshold();
  void testEdgeThreshold_data();
  void testEdgeThreshold();
  void testSigma_data();
  void testSigma();
  void testReset();

private:

  ISiftWidget *mSiftWidget;

};

TestSiftWidget::TestSiftWidget()
{
  mSiftWidget = new SiftWidget();
}

TestSiftWidget::~TestSiftWidget()
{
  if (mSiftWidget){
    delete mSiftWidget;
    mSiftWidget = nullptr;
  }
}

void TestSiftWidget::initTestCase()
{

}

void TestSiftWidget::cleanupTestCase()
{

}

void TestSiftWidget::testDefaultConstructor()
{
  /// Check default values
  SiftWidget siftWidget;
  QCOMPARE(5000, siftWidget.featuresNumber());
  QCOMPARE(3, siftWidget.octaveLayers());
  QCOMPARE(0.04, siftWidget.contrastThreshold());
  QCOMPARE(10., siftWidget.edgeThreshold());
  QCOMPARE(1.6, siftWidget.sigma());
}

void TestSiftWidget::testFeaturesNumber_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("Out of range value") << 50001 << 50000;
}

void TestSiftWidget::testFeaturesNumber()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSiftWidget->setFeaturesNumber(value);
  QCOMPARE(result, mSiftWidget->featuresNumber());
}

void TestSiftWidget::testOctaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("4") << 4 << 4;
  QTest::newRow("7") << 7 << 7;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestSiftWidget::testOctaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSiftWidget->setOctaveLayers(value);
  QCOMPARE(result, mSiftWidget->octaveLayers());
}

void TestSiftWidget::testContrastThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.04") << 0.04 << 0.04;
  QTest::newRow("0.1") << 0.1 << 0.1;
  QTest::newRow("0.2") << 0.2 << 0.2;
  QTest::newRow("Out of range value") << 11.1 << 10.;
}

void TestSiftWidget::testContrastThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftWidget->setContrastThreshold(value);
  QCOMPARE(result, mSiftWidget->contrastThreshold());
}

void TestSiftWidget::testEdgeThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("20.") << 20. << 20.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestSiftWidget::testEdgeThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftWidget->setEdgeThreshold(value);
  QCOMPARE(result, mSiftWidget->edgeThreshold());
}

void TestSiftWidget::testSigma_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("20.") << 20. << 20.;
  QTest::newRow("Out of range value") << 100.1 << 100.;
}

void TestSiftWidget::testSigma()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftWidget->setSigma(value);
  QCOMPARE(result, mSiftWidget->sigma());
}

void TestSiftWidget::testReset()
{
  mSiftWidget->setFeaturesNumber(500);
  mSiftWidget->setOctaveLayers(4);
  mSiftWidget->setContrastThreshold(0.5);
  mSiftWidget->setEdgeThreshold(20.);
  mSiftWidget->setSigma(3.);

  mSiftWidget->reset();

  QCOMPARE(5000, mSiftWidget->featuresNumber());
  QCOMPARE(3, mSiftWidget->octaveLayers());
  QCOMPARE(0.04, mSiftWidget->contrastThreshold());
  QCOMPARE(10., mSiftWidget->edgeThreshold());
  QCOMPARE(1.6, mSiftWidget->sigma());
}

QTEST_MAIN(TestSiftWidget)

#include "tst_siftwidget.moc"
