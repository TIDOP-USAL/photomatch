#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/gftt.h"

using namespace fme;

class TestGfttDetector : public QObject, public GfttDetector
{
  Q_OBJECT

public:

  TestGfttDetector();
  ~TestGfttDetector();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void test_maxFeatures_data();
  void test_maxFeatures();
  void test_qualityLevel_data();
  void test_qualityLevel();
  void test_minDistance_data();
  void test_minDistance();
  void test_blockSize_data();
  void test_blockSize();
  void test_harrisDetector_data();
  void test_harrisDetector();
  void test_k_data();
  void test_k();
  void test_reset();

};

TestGfttDetector::TestGfttDetector()
  : GfttDetector()
{

}

TestGfttDetector::~TestGfttDetector()
{

}

void TestGfttDetector::initTestCase()
{

}

void TestGfttDetector::cleanupTestCase()
{

}

void TestGfttDetector::testDefaultConstructor()
{
  /// Check default values
  GfttDetector gfttDetector;
  QCOMPARE(1000, gfttDetector.maxFeatures());
  QCOMPARE(0.01, gfttDetector.qualityLevel());
  QCOMPARE(1, gfttDetector.minDistance());
  QCOMPARE(3, gfttDetector.blockSize());
  QCOMPARE(false, gfttDetector.harrisDetector());
  QCOMPARE(0.04, gfttDetector.k());
}

void TestGfttDetector::test_type()
{
  QCOMPARE(GfttDetector::Type::gftt, this->type());
}

void TestGfttDetector::test_maxFeatures_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("1000000") << 1000000 << 1000000;
}

void TestGfttDetector::test_maxFeatures()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setMaxFeatures(value);
  QCOMPARE(result, this->maxFeatures());
  QCOMPARE(result, this->mGFTT->getMaxFeatures());
}

void TestGfttDetector::test_qualityLevel_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.01 << 0.01;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
}

void TestGfttDetector::test_qualityLevel()
{
  QFETCH(double, value);
  QFETCH(double, result);

  this->setQualityLevel(value);
  QCOMPARE(result, this->qualityLevel());
  QCOMPARE(result, this->mGFTT->getQualityLevel());
}

void TestGfttDetector::test_minDistance_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 1. << 1.;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("10000.") << 10000. << 10000.;
}

void TestGfttDetector::test_minDistance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  this->setMinDistance(value);
  QCOMPARE(result, this->minDistance());
  QCOMPARE(result, this->mGFTT->getMinDistance());
}

void TestGfttDetector::test_blockSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("default") << 3 << 3;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("100") << 100 << 100;
}

void TestGfttDetector::test_blockSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setBlockSize(value);
  QCOMPARE(result, this->blockSize());
  QCOMPARE(result, this->mGFTT->getBlockSize());
}

void TestGfttDetector::test_harrisDetector_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestGfttDetector::test_harrisDetector()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setHarrisDetector(value);
  QCOMPARE(result, this->harrisDetector());
  QCOMPARE(result, this->mGFTT->getHarrisDetector());
}

void TestGfttDetector::test_k_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("default") << 0.04 << 0.04;
  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("100.") << 100. << 100.;
}

void TestGfttDetector::test_k()
{
  QFETCH(double, value);
  QFETCH(double, result);

  this->setK(value);
  QCOMPARE(result, this->k());
  QCOMPARE(result, this->mGFTT->getK());
}

void TestGfttDetector::test_reset()
{
  this->setMaxFeatures(5000);
  this->setQualityLevel(0.1);
  this->setMinDistance(3.);
  this->setBlockSize(1);
  this->setHarrisDetector(true);
  this->setK(0.1);

  this->reset();

  QCOMPARE(1000, this->maxFeatures());
  QCOMPARE(1000, this->mGFTT->getMaxFeatures());
  QCOMPARE(0.01, this->qualityLevel());
  QCOMPARE(0.01, this->mGFTT->getQualityLevel());
  QCOMPARE(1., this->minDistance());
  QCOMPARE(1., this->mGFTT->getMinDistance());
  QCOMPARE(3, this->blockSize());
  QCOMPARE(3, this->mGFTT->getBlockSize());
  QCOMPARE(false, this->harrisDetector());
  QCOMPARE(false, this->mGFTT->getHarrisDetector());
  QCOMPARE(0.04, this->k());
  QCOMPARE(0.04, this->mGFTT->getK());
}

QTEST_APPLESS_MAIN(TestGfttDetector)

#include "tst_gfttdetector.moc"
