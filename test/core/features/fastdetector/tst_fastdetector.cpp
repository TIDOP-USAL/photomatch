#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/fast.h"

using namespace photomatch;

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
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_threshold_data();
  void test_threshold();
  void test_nonmaxSuppression_data();
  void test_nonmaxSuppression();
  void test_detectorType_data();
  void test_detectorType();
  void test_detectorType2_data();
  void test_detectorType2();

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
  QCOMPARE(10, this->threshold());
  QCOMPARE("TYPE_9_16", this->detectorType());
  QCOMPARE(true, this->nonmaxSuppression());
}

void TestFastDetector::cleanupTestCase()
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

void TestFastDetector::test_constructor()
{
  FastDetector fastDetector(11, false, "TYPE_7_12");
  QCOMPARE(11, fastDetector.threshold());
  QCOMPARE("TYPE_7_12", fastDetector.detectorType());
  QCOMPARE(false, fastDetector.nonmaxSuppression());
}

void TestFastDetector::test_copy_constructor()
{
  FastDetector fastDetector(11, false, "TYPE_7_12");
  FastDetector copy(fastDetector);
  QCOMPARE(11, copy.threshold());
  QCOMPARE("TYPE_7_12", copy.detectorType());
  QCOMPARE(false, copy.nonmaxSuppression());
}

void TestFastDetector::test_type()
{
  QCOMPARE(FastDetector::Type::fast, this->type());
}

void TestFastDetector::test_name()
{
  QCOMPARE("FAST", this->name());
}

void TestFastDetector::test_threshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestFastDetector::test_threshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setThreshold(value);
  QCOMPARE(result, this->threshold());
  QCOMPARE(result, this->mFast->getThreshold());
}

void TestFastDetector::test_nonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestFastDetector::test_nonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setNonmaxSuppression(value);
  QCOMPARE(result, this->nonmaxSuppression());
  QCOMPARE(result, this->mFast->getNonmaxSuppression());
}

void TestFastDetector::test_detectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << "TYPE_5_8";
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << "TYPE_7_12";
  QTest::newRow("TYPE_9_16") << "TYPE_9_16" << "TYPE_9_16";
}

void TestFastDetector::test_detectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->detectorType());
}

void TestFastDetector::test_detectorType2_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << 0;
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << 1;
  QTest::newRow("TYPE_9_16") << "TYPE_9_16" << 2;
}

void TestFastDetector::test_detectorType2()
{
  QFETCH(QString, value);
  QFETCH(int, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->mFast->getType());
}

QTEST_APPLESS_MAIN(TestFastDetector)

#include "tst_fastdetector.moc"
