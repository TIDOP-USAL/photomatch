#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/star.h"

using namespace photomatch;

class TestStarDetector : public QObject
{
  Q_OBJECT

public:

  TestStarDetector();
  ~TestStarDetector();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_maxSize_data();
  void test_maxSize();
  void test_responseThreshold_data();
  void test_responseThreshold();
  void test_lineThresholdProjected_data();
  void test_lineThresholdProjected();
  void test_lineThresholdBinarized_data();
  void test_lineThresholdBinarized();
  void test_suppressNonmaxSize_data();
  void test_suppressNonmaxSize();
  void test_reset();

protected:

  StarDetector *mStarDetector;

};

TestStarDetector::TestStarDetector()
  : mStarDetector(new StarDetector())
{

}

TestStarDetector::~TestStarDetector()
{
  if (mStarDetector){
    delete mStarDetector;
    mStarDetector = nullptr;
  }
}

void TestStarDetector::initTestCase()
{

}

void TestStarDetector::cleanupTestCase()
{

}

void TestStarDetector::test_defaultConstructor()
{
  /// Check default values
  StarDetector starDetector;
  QCOMPARE(45, starDetector.maxSize());
  QCOMPARE(30, starDetector.responseThreshold());
  QCOMPARE(10, starDetector.lineThresholdProjected());
  QCOMPARE(8, starDetector.lineThresholdBinarized());
  QCOMPARE(5, starDetector.suppressNonmaxSize());
}

void TestStarDetector::test_constructor()
{
  StarDetector starDetector(35, 20, 20, 10, 20);
  QCOMPARE(35, starDetector.maxSize());
  QCOMPARE(20, starDetector.responseThreshold());
  QCOMPARE(20, starDetector.lineThresholdProjected());
  QCOMPARE(10, starDetector.lineThresholdBinarized());
  QCOMPARE(20, starDetector.suppressNonmaxSize());
}

void TestStarDetector::test_copy_constructor()
{
  StarDetector starDetector(35, 20, 20, 10, 20);
  StarDetector c(starDetector);
  QCOMPARE(35, c.maxSize());
  QCOMPARE(20, c.responseThreshold());
  QCOMPARE(20, c.lineThresholdProjected());
  QCOMPARE(10, c.lineThresholdBinarized());
  QCOMPARE(20, c.suppressNonmaxSize());
}

void TestStarDetector::test_type()
{
  QCOMPARE(StarDetector::Type::star, mStarDetector->type());
}

void TestStarDetector::test_name()
{
  QCOMPARE("STAR", mStarDetector->name());
}

void TestStarDetector::test_maxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestStarDetector::test_maxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarDetector->setMaxSize(value);
  QCOMPARE(result, mStarDetector->maxSize());
}

void TestStarDetector::test_responseThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestStarDetector::test_responseThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarDetector->setResponseThreshold(value);
  QCOMPARE(result, mStarDetector->responseThreshold());
}

void TestStarDetector::test_lineThresholdProjected_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestStarDetector::test_lineThresholdProjected()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarDetector->setLineThresholdProjected(value);
  QCOMPARE(result, mStarDetector->lineThresholdProjected());
}

void TestStarDetector::test_lineThresholdBinarized_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestStarDetector::test_lineThresholdBinarized()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarDetector->setLineThresholdBinarized(value);
  QCOMPARE(result, mStarDetector->lineThresholdBinarized());
}

void TestStarDetector::test_suppressNonmaxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestStarDetector::test_suppressNonmaxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarDetector->setSuppressNonmaxSize(value);
  QCOMPARE(result, mStarDetector->suppressNonmaxSize());
}

void TestStarDetector::test_reset()
{
  mStarDetector->setMaxSize(35);
  mStarDetector->setResponseThreshold(20);
  mStarDetector->setLineThresholdProjected(20);
  mStarDetector->setLineThresholdBinarized(10);
  mStarDetector->setSuppressNonmaxSize(20);

  mStarDetector->reset();

  /// Check default values
  QCOMPARE(45, mStarDetector->maxSize());
  QCOMPARE(30, mStarDetector->responseThreshold());
  QCOMPARE(10, mStarDetector->lineThresholdProjected());
  QCOMPARE(8, mStarDetector->lineThresholdBinarized());
  QCOMPARE(5, mStarDetector->suppressNonmaxSize());
}

QTEST_APPLESS_MAIN(TestStarDetector)

#include "tst_stardetector.moc"
