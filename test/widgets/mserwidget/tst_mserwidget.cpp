#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/MserWidget.h"

using namespace fme;

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
  void testDelta_data();
  void testDelta();
  void testMinArea_data();
  void testMinArea();
  void testMaxArea_data();
  void testMaxArea();
  void testMaxVariation_data();
  void testMaxVariation();
  void testMinDiversity_data();
  void testMinDiversity();
  void testMaxEvolution_data();
  void testMaxEvolution();
  void testAreaThreshold_data();
  void testAreaThreshold();
  void testMinMargin_data();
  void testMinMargin();
  void testEdgeBlurSize_data();
  void testEdgeBlurSize();
  void testReset();

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

void TestMserWidget::testDelta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::testDelta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setDelta(value);
  QCOMPARE(result, mMserWidget->delta());
}

void TestMserWidget::testMinArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 100001 << 100000;
}

void TestMserWidget::testMinArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMinArea(value);
  QCOMPARE(result, mMserWidget->minArea());
}

void TestMserWidget::testMaxArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("100") << 100 << 100;
  QTest::newRow("100") << 500 << 500;
  QTest::newRow("Out of range value") << 100001 << 100000;
}

void TestMserWidget::testMaxArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMaxArea(value);
  QCOMPARE(result, mMserWidget->maxArea());
}

void TestMserWidget::testMaxVariation_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::testMaxVariation()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMaxVariation(value);
  QCOMPARE(result, mMserWidget->maxVariation());
}

void TestMserWidget::testMinDiversity_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::testMinDiversity()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMinDiversity(value);
  QCOMPARE(result, mMserWidget->minDiversity());
}

void TestMserWidget::testMaxEvolution_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::testMaxEvolution()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setMaxEvolution(value);
  QCOMPARE(result, mMserWidget->maxEvolution());
}

void TestMserWidget::testAreaThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 1.5 << 1.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::testAreaThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setAreaThreshold(value);
  QCOMPARE(result, mMserWidget->areaThreshold());
}

void TestMserWidget::testMinMargin_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 200. << 99.99;
}

void TestMserWidget::testMinMargin()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserWidget->setMinMargin(value);
  QCOMPARE(result, mMserWidget->minMargin());
}

void TestMserWidget::testEdgeBlurSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestMserWidget::testEdgeBlurSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserWidget->setEdgeBlurSize(value);
  QCOMPARE(result, mMserWidget->edgeBlurSize());
}


void TestMserWidget::testReset()
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
