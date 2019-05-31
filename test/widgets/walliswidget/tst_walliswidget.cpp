#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/WallisWidget.h"

using namespace fme;

class TestWallisWidget : public QObject
{
  Q_OBJECT

public:
  TestWallisWidget();
  ~TestWallisWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testContrast_data();
  void testContrast();
  void testBrightness_data();
  void testBrightness();
  void testImposedAverage_data();
  void testImposedAverage();
  void testImposedLocalStdDev_data();
  void testImposedLocalStdDev();
  void testKernelSize_data();
  void testKernelSize();
  void testReset();

private:

  IWallisWidget *mWallisWidget;
};

TestWallisWidget::TestWallisWidget()
  : mWallisWidget(new WallisWidget)
{

}

TestWallisWidget::~TestWallisWidget()
{
  if (mWallisWidget){
    delete mWallisWidget;
    mWallisWidget = nullptr;
  }
}

void TestWallisWidget::initTestCase()
{

}

void TestWallisWidget::cleanupTestCase()
{

}

void TestWallisWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(1.0, mWallisWidget->contrast());
  QCOMPARE(0.2, mWallisWidget->brightness());
  QCOMPARE(41, mWallisWidget->imposedAverage());
  QCOMPARE(127, mWallisWidget->imposedLocalStdDev());
  QCOMPARE(50, mWallisWidget->kernelSize());
}

void TestWallisWidget::testContrast_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("Out of range value") << 2. << 1.;
}

void TestWallisWidget::testContrast()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisWidget->setContrast(value);
  QCOMPARE(result, mWallisWidget->contrast());
}

void TestWallisWidget::testBrightness_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("Out of range value") << 2. << 1.;
}

void TestWallisWidget::testBrightness()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisWidget->setBrightness(value);
  QCOMPARE(result, mWallisWidget->brightness());
}

void TestWallisWidget::testImposedAverage_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 1001 << 1000;
}

void TestWallisWidget::testImposedAverage()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setImposedAverage(value);
  QCOMPARE(result, mWallisWidget->imposedAverage());
}

void TestWallisWidget::testImposedLocalStdDev_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestWallisWidget::testImposedLocalStdDev()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setImposedLocalStdDev(value);
  QCOMPARE(result, mWallisWidget->imposedLocalStdDev());
}

void TestWallisWidget::testKernelSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestWallisWidget::testKernelSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setKernelSize(value);
  QCOMPARE(result, mWallisWidget->kernelSize());
}

void TestWallisWidget::testReset()
{
  mWallisWidget->setContrast(.5);
  mWallisWidget->setBrightness(0.5);
  mWallisWidget->setImposedAverage(35);
  mWallisWidget->setImposedLocalStdDev(150);
  mWallisWidget->setKernelSize(60);

  mWallisWidget->reset();

  QCOMPARE(1.0, mWallisWidget->contrast());
  QCOMPARE(0.2, mWallisWidget->brightness());
  QCOMPARE(41, mWallisWidget->imposedAverage());
  QCOMPARE(127, mWallisWidget->imposedLocalStdDev());
  QCOMPARE(50, mWallisWidget->kernelSize());
}

QTEST_MAIN(TestWallisWidget)

#include "tst_walliswidget.moc"
