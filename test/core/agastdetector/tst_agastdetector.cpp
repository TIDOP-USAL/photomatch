#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/agast.h"

using namespace fme;

class TestAgastDetector : public QObject
{
  Q_OBJECT

public:

  TestAgastDetector();
  ~TestAgastDetector();

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
  void testReset();

private:

  AgastDetector *mAgastDetector;
};

TestAgastDetector::TestAgastDetector()
  : mAgastDetector(new AgastDetector)
{

}

TestAgastDetector::~TestAgastDetector()
{
  if (mAgastDetector){
    delete mAgastDetector;
    mAgastDetector = nullptr;
  }
}

void TestAgastDetector::initTestCase()
{

}

void TestAgastDetector::cleanupTestCase()
{

}

void TestAgastDetector::testDefaultConstructor()
{
  /// Check default values
  AgastDetector agastDetector;
  QCOMPARE(10, agastDetector.threshold());
  QCOMPARE("OAST_9_16", agastDetector.detectorType());
  QCOMPARE(true, agastDetector.nonmaxSuppression());
}

void TestAgastDetector::test_type()
{
  QCOMPARE(AgastDetector::Type::agast, mAgastDetector->type());
}

void TestAgastDetector::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestAgastDetector::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAgastDetector->setThreshold(value);
  QCOMPARE(result, mAgastDetector->threshold());
}

void TestAgastDetector::testNonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestAgastDetector::testNonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mAgastDetector->setNonmaxSuppression(value);
  QCOMPARE(result, mAgastDetector->nonmaxSuppression());
}

void TestAgastDetector::testDetectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << "AGAST_5_8";
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << "AGAST_7_12d";
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << "AGAST_7_12s";
  QTest::newRow("OAST_9_16") << "OAST_9_16" << "OAST_9_16";
  QTest::newRow("bad_value") << "bad_value" << "OAST_9_16";
}

void TestAgastDetector::testDetectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAgastDetector->setDetectorType(value);
  QCOMPARE(result, mAgastDetector->detectorType());
}

void TestAgastDetector::testReset()
{
  mAgastDetector->setThreshold(3);
  mAgastDetector->setDetectorType("AGAST_7_12s");
  mAgastDetector->setNonmaxSuppression(false);

  mAgastDetector->reset();

  QCOMPARE(10, mAgastDetector->threshold());
  QCOMPARE("OAST_9_16", mAgastDetector->detectorType());
  QCOMPARE(true, mAgastDetector->nonmaxSuppression());
}

QTEST_APPLESS_MAIN(TestAgastDetector)

#include "tst_agastdetector.moc"
