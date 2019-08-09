#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/fast.h"

using namespace fme;

class TestFastDetector
  : public QObject,
    public FastDetector
{
  Q_OBJECT

public:

  TestFastDetector();
  ~TestFastDetector();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void testThreshold_data();
  void testThreshold();
  void testNonmaxSuppression_data();
  void testNonmaxSuppression();
  void testDetectorType_data();
  void testDetectorType();
  void testDetectorType2_data();
  void testDetectorType2();
  void testReset();

};

TestFastDetector::TestFastDetector()
  : FastDetector()
{

}

TestFastDetector::~TestFastDetector()
{
}

void TestFastDetector::initTestCase()
{

}

void TestFastDetector::cleanupTestCase()
{

}

void TestFastDetector::testDefaultConstructor()
{
  /// Check default values
  FastDetector fastDetector;
  QCOMPARE(10, fastDetector.threshold());
  QCOMPARE("TYPE_9_16", fastDetector.detectorType());
  QCOMPARE(true, fastDetector.nonmaxSuppression());
}

void TestFastDetector::test_type()
{
  QCOMPARE(FastDetector::Type::fast, this->type());
}

void TestFastDetector::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestFastDetector::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setThreshold(value);
  QCOMPARE(result, this->threshold());
  QCOMPARE(result, this->mFast->getThreshold());
}

void TestFastDetector::testNonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestFastDetector::testNonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setNonmaxSuppression(value);
  QCOMPARE(result, this->nonmaxSuppression());
  QCOMPARE(result, this->mFast->getNonmaxSuppression());
}

void TestFastDetector::testDetectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << "TYPE_5_8";
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << "TYPE_7_12";
  QTest::newRow("TYPE_9_16") << "TYPE_9_16" << "TYPE_9_16";
}

void TestFastDetector::testDetectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->detectorType());
}

void TestFastDetector::testDetectorType2_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << 0;
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << 1;
  QTest::newRow("TYPE_9_16") << "TYPE_9_16" << 2;
}

void TestFastDetector::testDetectorType2()
{
  QFETCH(QString, value);
  QFETCH(int, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->mFast->getType());
}

void TestFastDetector::testReset()
{
  this->setThreshold(3);
  this->setDetectorType("TYPE_7_12");
  this->setNonmaxSuppression(false);

  this->reset();

  QCOMPARE(10, this->threshold());
  QCOMPARE(10, this->mFast->getThreshold());
  QCOMPARE("TYPE_9_16", this->detectorType());
  QCOMPARE(2, this->mFast->getType());
  QCOMPARE(true, this->nonmaxSuppression());
  QCOMPARE(true, this->mFast->getNonmaxSuppression());
}

QTEST_APPLESS_MAIN(TestFastDetector)

#include "tst_fastdetector.moc"
