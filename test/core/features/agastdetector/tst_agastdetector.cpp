#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/agast.h"

using namespace photomatch;

class TestAgastDetector
  : public QObject,
    public AgastDetector
{
  Q_OBJECT

public:

  TestAgastDetector();
  ~TestAgastDetector();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
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
  void test_reset();

};

TestAgastDetector::TestAgastDetector()
  : AgastDetector()
{

}

TestAgastDetector::~TestAgastDetector()
{

}

void TestAgastDetector::initTestCase()
{

}

void TestAgastDetector::cleanupTestCase()
{

}

void TestAgastDetector::test_defaultConstructor()
{
  /// Check default values
  AgastDetector agastDetector;
  QCOMPARE(10, agastDetector.threshold());
  QCOMPARE("OAST_9_16", agastDetector.detectorType());
  QCOMPARE(true, agastDetector.nonmaxSuppression());
}

void TestAgastDetector::test_constructor()
{
  AgastDetector agastDetector(20, false, "AGAST_7_12s");
  QCOMPARE(20, agastDetector.threshold());
  QCOMPARE("AGAST_7_12s", agastDetector.detectorType());
  QCOMPARE(false, agastDetector.nonmaxSuppression());
}

void TestAgastDetector::test_copy_constructor()
{
  AgastDetector obj(20, false, "AGAST_7_12s");
  AgastDetector agastDetector(obj);
  QCOMPARE(20, agastDetector.threshold());
  QCOMPARE("AGAST_7_12s", agastDetector.detectorType());
  QCOMPARE(false, agastDetector.nonmaxSuppression());
}

void TestAgastDetector::test_type()
{
  QCOMPARE(AgastDetector::Type::agast, this->type());
}

void TestAgastDetector::test_name()
{
  QCOMPARE("AGAST", this->name());
}

void TestAgastDetector::test_threshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestAgastDetector::test_threshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setThreshold(value);
  QCOMPARE(result, this->threshold());
  QCOMPARE(result, this->mAgast->getThreshold());
}

void TestAgastDetector::test_nonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestAgastDetector::test_nonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setNonmaxSuppression(value);
  QCOMPARE(result, this->nonmaxSuppression());
  QCOMPARE(result, this->mAgast->getNonmaxSuppression());
}

void TestAgastDetector::test_detectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << "AGAST_5_8";
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << "AGAST_7_12d";
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << "AGAST_7_12s";
  QTest::newRow("OAST_9_16") << "OAST_9_16" << "OAST_9_16";
  QTest::newRow("bad_value") << "bad_value" << "OAST_9_16";
}

void TestAgastDetector::test_detectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->detectorType());

}

void TestAgastDetector::test_detectorType2_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << 0;
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << 1;
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << 2;
  QTest::newRow("OAST_9_16") << "OAST_9_16" << 3;
}

void TestAgastDetector::test_detectorType2()
{
  QFETCH(QString, value);
  QFETCH(int, result);

  this->setDetectorType(value);
  QCOMPARE(result, this->mAgast->getType());
}
void TestAgastDetector::test_reset()
{
  this->setThreshold(3);
  this->setDetectorType("AGAST_7_12s");
  this->setNonmaxSuppression(false);

  this->reset();

  QCOMPARE(10, this->threshold());
  QCOMPARE(10, this->mAgast->getThreshold());
  QCOMPARE("OAST_9_16", this->detectorType());
  QCOMPARE(3, this->mAgast->getType());
  QCOMPARE(true, this->nonmaxSuppression());
  QCOMPARE(true, this->mAgast->getNonmaxSuppression());
}

QTEST_APPLESS_MAIN(TestAgastDetector)

#include "tst_agastdetector.moc"
