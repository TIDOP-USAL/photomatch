#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MserWidget.h"

using namespace photomatch;

class TestMserWidget : public QObject
{
  Q_OBJECT

public:

  TestMserWidget();
  ~TestMserWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void test_delta_data();
  void test_delta();
  void test_minArea_data();
  void test_minArea();
  void test_maxArea_data();
  void test_maxArea();
  void test_maxVariation_data();
  void test_maxVariation();
  void test_minDiversity_data();
  void test_minDiversity();
  void test_maxEvolution_data();
  void test_maxEvolution();
  void test_areaThreshold_data();
  void test_areaThreshold();
  void test_minMargin_data();
  void test_minMargin();
  void test_edgeBlurSize_data();
  void test_edgeBlurSize();
  void test_reset();

private:

  IMserWidget *mMserWidget;
};

TestMserWidget::TestMserWidget()
  : mMserWidget(new MserWidget)
{

}

TestMserWidget::~TestMserWidget()
{
  if (mMserWidget){
    delete mMserWidget;
    mMserWidget = nullptr;
  }
}

void TestMserWidget::initTestCase()
{

}

void TestMserWidget::cleanupTestCase()
{

}

void TestMserWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(5, mMserWidget->delta());
  QCOMPARE(60, mMserWidget->minArea());
  QCOMPARE(14400, mMserWidget->maxArea());
  QCOMPARE(0.25, mMserWidget->maxVariation());
  QCOMPARE(.2, mMserWidget->minDiversity());
  QCOMPARE(200, mMserWidget->maxEvolution());
  QCOMPARE(1.01, mMserWidget->areaThreshold());
  QCOMPARE(0.003, mMserWidget->minMargin());
  QCOMPARE(5, mMserWidget->edgeBlurSize());
}

void TestMserWidget::test_windowTitle()
{
  QCOMPARE("MSER", mMserWidget->windowTitle());
}

void TestMserWidget::test_delta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::test_delta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setDelta(value);
  QCOMPARE(result, mMserWidget->delta());
}

void TestMserWidget::test_minArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 100001 << 100000;
}

void TestMserWidget::test_minArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMinArea(value);
  QCOMPARE(result, mMserWidget->minArea());
}

void TestMserWidget::test_maxArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("100") << 100 << 100;
  QTest::newRow("100") << 500 << 500;
  QTest::newRow("Out of range value") << 100001 << 100000;
}

void TestMserWidget::test_maxArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMaxArea(value);
  QCOMPARE(result, mMserWidget->maxArea());
}

void TestMserWidget::test_maxVariation_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::test_maxVariation()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMaxVariation(value);
  QCOMPARE(result, mMserWidget->maxVariation());
}

void TestMserWidget::test_minDiversity_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::test_minDiversity()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMinDiversity(value);
  QCOMPARE(result, mMserWidget->minDiversity());
}

void TestMserWidget::test_maxEvolution_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::test_maxEvolution()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMaxEvolution(value);
  QCOMPARE(result, mMserWidget->maxEvolution());
}

void TestMserWidget::test_areaThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 1.5 << 1.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::test_areaThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setAreaThreshold(value);
  QCOMPARE(result, mMserWidget->areaThreshold());
}

void TestMserWidget::test_minMargin_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::test_minMargin()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMinMargin(value);
  QCOMPARE(result, mMserWidget->minMargin());
}

void TestMserWidget::test_edgeBlurSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::test_edgeBlurSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setEdgeBlurSize(value);
  QCOMPARE(result, mMserWidget->edgeBlurSize());
}


void TestMserWidget::test_reset()
{
  mMserWidget->setDelta(10);
  mMserWidget->setMinArea(50);
  mMserWidget->setMaxArea(10000);
  mMserWidget->setMaxVariation(0.5);
  mMserWidget->setMinDiversity(0.3);
  mMserWidget->setMaxEvolution(150);
  mMserWidget->setAreaThreshold(1.1);
  mMserWidget->setMinMargin(0.01);
  mMserWidget->setEdgeBlurSize(6);

  mMserWidget->reset();

  /// Check default values
  QCOMPARE(5, mMserWidget->delta());
  QCOMPARE(60, mMserWidget->minArea());
  QCOMPARE(14400, mMserWidget->maxArea());
  QCOMPARE(0.25, mMserWidget->maxVariation());
  QCOMPARE(.2, mMserWidget->minDiversity());
  QCOMPARE(200, mMserWidget->maxEvolution());
  QCOMPARE(1.01, mMserWidget->areaThreshold());
  QCOMPARE(0.003, mMserWidget->minMargin());
  QCOMPARE(5, mMserWidget->edgeBlurSize());
}


QTEST_MAIN(TestMserWidget)

#include "tst_mserwidget.moc"
