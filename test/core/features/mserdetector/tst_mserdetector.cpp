#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/mser.h"

using namespace photomatch;

class TestMserDetector
  : public QObject
{
  Q_OBJECT

public:

  TestMserDetector();
  ~TestMserDetector();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_type();
  void test_name();
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

protected:

  MserDetector *mMserDetector;
};

TestMserDetector::TestMserDetector()
  : mMserDetector(new MserDetector)
{

}

TestMserDetector::~TestMserDetector()
{
  if (mMserDetector){
    delete mMserDetector;
    mMserDetector = nullptr;
  }
}

void TestMserDetector::initTestCase()
{

}

void TestMserDetector::cleanupTestCase()
{

}

void TestMserDetector::test_defaultConstructor()
{
  /// Check default values
  MserDetector mserDetector;
  QCOMPARE(5, mserDetector.delta());
  QCOMPARE(60, mserDetector.minArea());
  QCOMPARE(14400, mserDetector.maxArea());
  QCOMPARE(0.25, mserDetector.maxVariation());
  QCOMPARE(.2, mserDetector.minDiversity());
  QCOMPARE(200, mserDetector.maxEvolution());
  QCOMPARE(1.01, mserDetector.areaThreshold());
  QCOMPARE(0.003, mserDetector.minMargin());
  QCOMPARE(5, mserDetector.edgeBlurSize());
}

void TestMserDetector::test_constructor()
{
  MserDetector mserDetector(10, 50, 10000, 0.5, .3, 150, 1.1, 0.01, 6);
  QCOMPARE(10, mserDetector.delta());
  QCOMPARE(50, mserDetector.minArea());
  QCOMPARE(10000, mserDetector.maxArea());
  QCOMPARE(0.5, mserDetector.maxVariation());
  QCOMPARE(.3, mserDetector.minDiversity());
  QCOMPARE(150, mserDetector.maxEvolution());
  QCOMPARE(1.1, mserDetector.areaThreshold());
  QCOMPARE(0.01, mserDetector.minMargin());
  QCOMPARE(6, mserDetector.edgeBlurSize());
}

void TestMserDetector::test_type()
{
  QCOMPARE(MserDetector::Type::mser, mMserDetector->type());
}

void TestMserDetector::test_name()
{
  QCOMPARE("MSER", mMserDetector->name());
}

void TestMserDetector::test_delta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestMserDetector::test_delta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserDetector->setDelta(value);
  QCOMPARE(result, mMserDetector->delta());
}

void TestMserDetector::test_minArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestMserDetector::test_minArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserDetector->setMinArea(value);
  QCOMPARE(result, mMserDetector->minArea());
}

void TestMserDetector::test_maxArea_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("100") << 100 << 100;
  QTest::newRow("100") << 500 << 500;
}

void TestMserDetector::test_maxArea()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserDetector->setMaxArea(value);
  QCOMPARE(result, mMserDetector->maxArea());
}

void TestMserDetector::test_maxVariation_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
}

void TestMserDetector::test_maxVariation()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserDetector->setMaxVariation(value);
  QCOMPARE(result, mMserDetector->maxVariation());
}

void TestMserDetector::test_minDiversity_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
}

void TestMserDetector::test_minDiversity()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserDetector->setMinDiversity(value);
  QCOMPARE(result, mMserDetector->minDiversity());
}

void TestMserDetector::test_maxEvolution_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestMserDetector::test_maxEvolution()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserDetector->setMaxEvolution(value);
  QCOMPARE(result, mMserDetector->maxEvolution());
}

void TestMserDetector::test_areaThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 1.5 << 1.5;
}

void TestMserDetector::test_areaThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserDetector->setAreaThreshold(value);
  QCOMPARE(result, mMserDetector->areaThreshold());
}

void TestMserDetector::test_minMargin_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 0.25 << 0.25;
  QTest::newRow("100") << 0.5 << 0.5;
}

void TestMserDetector::test_minMargin()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMserDetector->setMinMargin(value);
  QCOMPARE(result, mMserDetector->minMargin());
}

void TestMserDetector::test_edgeBlurSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestMserDetector::test_edgeBlurSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMserDetector->setEdgeBlurSize(value);
  QCOMPARE(result, mMserDetector->edgeBlurSize());
}


void TestMserDetector::test_reset()
{
  mMserDetector->setDelta(10);
  mMserDetector->setMinArea(50);
  mMserDetector->setMaxArea(10000);
  mMserDetector->setMaxVariation(0.5);
  mMserDetector->setMinDiversity(0.3);
  mMserDetector->setMaxEvolution(150);
  mMserDetector->setAreaThreshold(1.1);
  mMserDetector->setMinMargin(0.01);
  mMserDetector->setEdgeBlurSize(6);

  mMserDetector->reset();

  /// Check default values
  QCOMPARE(5, mMserDetector->delta());
  QCOMPARE(60, mMserDetector->minArea());
  QCOMPARE(14400, mMserDetector->maxArea());
  QCOMPARE(0.25, mMserDetector->maxVariation());
  QCOMPARE(.2, mMserDetector->minDiversity());
  QCOMPARE(200, mMserDetector->maxEvolution());
  QCOMPARE(1.01, mMserDetector->areaThreshold());
  QCOMPARE(0.003, mMserDetector->minMargin());
  QCOMPARE(5, mMserDetector->edgeBlurSize());
}

QTEST_APPLESS_MAIN(TestMserDetector)

#include "tst_mserdetector.moc"
