#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/WallisWidget.h"

using namespace photomatch;

class TestWallisWidget : public QObject
{
  Q_OBJECT

public:
  TestWallisWidget();
  ~TestWallisWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_contrast_data();
  void test_contrast();
  void test_brightness_data();
  void test_brightness();
  void test_imposedAverage_data();
  void test_imposedAverage();
  void test_imposedLocalStdDev_data();
  void test_imposedLocalStdDev();
  void test_kernelSize_data();
  void test_kernelSize();

private:

  WallisWidget *mWallisWidget;
};

TestWallisWidget::TestWallisWidget()
  : mWallisWidget(new WallisWidgetImp)
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
  QCOMPARE(1.0, mWallisWidget->contrast());
  QCOMPARE(0.2, mWallisWidget->brightness());
  QCOMPARE(41, mWallisWidget->imposedAverage());
  QCOMPARE(127, mWallisWidget->imposedLocalStdDev());
  QCOMPARE(50, mWallisWidget->kernelSize());
}

void TestWallisWidget::cleanupTestCase()
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

void TestWallisWidget::test_windowTitle()
{
  QCOMPARE("Wallis Filter", mWallisWidget->windowTitle());
}

void TestWallisWidget::test_contrast_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("Out of range value") << 2. << 1.;
}

void TestWallisWidget::test_contrast()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisWidget->setContrast(value);
  QCOMPARE(result, mWallisWidget->contrast());
}

void TestWallisWidget::test_brightness_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("Out of range value") << 2. << 1.;
}

void TestWallisWidget::test_brightness()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisWidget->setBrightness(value);
  QCOMPARE(result, mWallisWidget->brightness());
}

void TestWallisWidget::test_imposedAverage_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 1001 << 1000;
}

void TestWallisWidget::test_imposedAverage()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setImposedAverage(value);
  QCOMPARE(result, mWallisWidget->imposedAverage());
}

void TestWallisWidget::test_imposedLocalStdDev_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestWallisWidget::test_imposedLocalStdDev()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setImposedLocalStdDev(value);
  QCOMPARE(result, mWallisWidget->imposedLocalStdDev());
}

void TestWallisWidget::test_kernelSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestWallisWidget::test_kernelSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisWidget->setKernelSize(value);
  QCOMPARE(result, mWallisWidget->kernelSize());
}


QTEST_MAIN(TestWallisWidget)

#include "tst_walliswidget.moc"
