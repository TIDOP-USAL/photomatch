#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/surf.h"

using namespace fme;

class TestSurfDetectorDescriptor : public QObject, public SurfDetectorDescriptor
{
  Q_OBJECT

public:
  TestSurfDetectorDescriptor();
  ~TestSurfDetectorDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_hessianThreshold_data();
  void test_hessianThreshold();
  void test_octaves_data();
  void test_octaves();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_extendedDescriptor_data();
  void test_extendedDescriptor();
  void test_rotatedFeatures_data();
  void test_rotatedFeatures();
  void test_reset();

};

TestSurfDetectorDescriptor::TestSurfDetectorDescriptor()
  : SurfDetectorDescriptor()
{
}

TestSurfDetectorDescriptor::~TestSurfDetectorDescriptor()
{
}

void TestSurfDetectorDescriptor::initTestCase()
{

}

void TestSurfDetectorDescriptor::cleanupTestCase()
{

}

void TestSurfDetectorDescriptor::testDefaultConstructor()
{
  /// Check default values
  SurfDetectorDescriptor surfDetectorDescriptor;
  QCOMPARE(100, surfDetectorDescriptor.hessianThreshold());
  QCOMPARE(4, surfDetectorDescriptor.octaves());
  QCOMPARE(3, surfDetectorDescriptor.octaveLayers());
  QCOMPARE(false, surfDetectorDescriptor.extendedDescriptor());
  QCOMPARE(false, surfDetectorDescriptor.rotatedFeatures());
}

void TestSurfDetectorDescriptor::test_type()
{
  QCOMPARE(SurfDetectorDescriptor::Type::surf, this->type());
}

void TestSurfDetectorDescriptor::test_name()
{
  QCOMPARE("SURF", this->name());
}

void TestSurfDetectorDescriptor::test_hessianThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("50") << 50 << 50;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("200") << 200 << 200;
}

void TestSurfDetectorDescriptor::test_hessianThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setHessianThreshold(value);
  QCOMPARE(result, this->hessianThreshold());
  QCOMPARE(result, this->mSurf->getHessianThreshold());
}

void TestSurfDetectorDescriptor::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
}

void TestSurfDetectorDescriptor::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setOctaves(value);
  QCOMPARE(result, this->octaves());
  QCOMPARE(result, this->mSurf->getNOctaves());
}

void TestSurfDetectorDescriptor::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
}

void TestSurfDetectorDescriptor::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setOctaveLayers(value);
  QCOMPARE(result, this->octaveLayers());
  QCOMPARE(result, this->mSurf->getNOctaveLayers());
}

void TestSurfDetectorDescriptor::test_extendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfDetectorDescriptor::test_extendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setExtendedDescriptor(value);
  QCOMPARE(result, this->extendedDescriptor());
  QCOMPARE(result, this->mSurf->getExtended());
}

void TestSurfDetectorDescriptor::test_rotatedFeatures_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfDetectorDescriptor::test_rotatedFeatures()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  this->setRotatedFeatures(value);
  QCOMPARE(result, this->rotatedFeatures());
  QCOMPARE(result, this->mSurf->getUpright());
}

void TestSurfDetectorDescriptor::test_reset()
{
  this->setHessianThreshold(50.);
  this->setOctaves(2);
  this->setOctaveLayers(5);
  this->setExtendedDescriptor(true);
  this->setRotatedFeatures(true);

  this->reset();

  QCOMPARE(100, this->hessianThreshold());
  QCOMPARE(100, this->mSurf->getHessianThreshold());
  QCOMPARE(4, this->octaves());
  QCOMPARE(4, this->mSurf->getNOctaves());
  QCOMPARE(3, this->octaveLayers());
  QCOMPARE(3, this->mSurf->getNOctaveLayers());
  QCOMPARE(false, this->extendedDescriptor());
  QCOMPARE(false, this->mSurf->getExtended());
  QCOMPARE(false, this->rotatedFeatures());
  QCOMPARE(false, this->mSurf->getUpright());
}

QTEST_APPLESS_MAIN(TestSurfDetectorDescriptor)

#include "tst_surfdetectordescriptor.moc"
