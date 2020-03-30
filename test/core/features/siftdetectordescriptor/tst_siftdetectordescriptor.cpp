#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/sift.h"

using namespace photomatch;

class TestSiftDetectorDescriptor : public QObject
{
  Q_OBJECT

public:
  TestSiftDetectorDescriptor();
  ~TestSiftDetectorDescriptor();

private slots:

#ifdef OPENCV_ENABLE_NONFREE
  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_featuresNumber_data();
  void test_featuresNumber();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_contrastThreshold_data();
  void test_contrastThreshold();
  void test_edgeThreshold_data();
  void test_edgeThreshold();
  void test_sigma_data();
  void test_sigma();

private:

  SiftDetectorDescriptor *mSiftDetectorDescriptor;
#endif

};


TestSiftDetectorDescriptor::TestSiftDetectorDescriptor()
{
#ifdef OPENCV_ENABLE_NONFREE
  mSiftDetectorDescriptor = new SiftDetectorDescriptor();
#endif
}

TestSiftDetectorDescriptor::~TestSiftDetectorDescriptor()
{
#ifdef OPENCV_ENABLE_NONFREE
  if (mSiftDetectorDescriptor){
    delete mSiftDetectorDescriptor;
    mSiftDetectorDescriptor = nullptr;
  }
#endif
}

#ifdef OPENCV_ENABLE_NONFREE

void TestSiftDetectorDescriptor::initTestCase()
{
  QCOMPARE(5000, mSiftDetectorDescriptor->featuresNumber());
  QCOMPARE(3, mSiftDetectorDescriptor->octaveLayers());
  QCOMPARE(0.04, mSiftDetectorDescriptor->contrastThreshold());
  QCOMPARE(10., mSiftDetectorDescriptor->edgeThreshold());
  QCOMPARE(1.6, mSiftDetectorDescriptor->sigma());
}

void TestSiftDetectorDescriptor::cleanupTestCase()
{
  mSiftDetectorDescriptor->setFeaturesNumber(500);
  mSiftDetectorDescriptor->setOctaveLayers(4);
  mSiftDetectorDescriptor->setContrastThreshold(0.5);
  mSiftDetectorDescriptor->setEdgeThreshold(20.);
  mSiftDetectorDescriptor->setSigma(3.);

  mSiftDetectorDescriptor->reset();

  QCOMPARE(5000, mSiftDetectorDescriptor->featuresNumber());
  QCOMPARE(3, mSiftDetectorDescriptor->octaveLayers());
  QCOMPARE(0.04, mSiftDetectorDescriptor->contrastThreshold());
  QCOMPARE(10., mSiftDetectorDescriptor->edgeThreshold());
  QCOMPARE(1.6, mSiftDetectorDescriptor->sigma());
}

void TestSiftDetectorDescriptor::test_constructor()
{
  SiftDetectorDescriptor siftDetectorDescriptor(500, 4, 0.5, 20., 3.);
  QCOMPARE(500, siftDetectorDescriptor.featuresNumber());
  QCOMPARE(4, siftDetectorDescriptor.octaveLayers());
  QCOMPARE(0.5, siftDetectorDescriptor.contrastThreshold());
  QCOMPARE(20., siftDetectorDescriptor.edgeThreshold());
  QCOMPARE(3., siftDetectorDescriptor.sigma());
}

void TestSiftDetectorDescriptor::test_copy_constructor()
{
  SiftDetectorDescriptor siftDetectorDescriptor(500, 4, 0.5, 20., 3.);
  SiftDetectorDescriptor c(siftDetectorDescriptor);
  QCOMPARE(500, c.featuresNumber());
  QCOMPARE(4, c.octaveLayers());
  QCOMPARE(0.5, c.contrastThreshold());
  QCOMPARE(20., c.edgeThreshold());
  QCOMPARE(3., c.sigma());
}

void TestSiftDetectorDescriptor::test_type()
{
  QCOMPARE(SiftDetectorDescriptor::Type::sift, mSiftDetectorDescriptor->type());
}

void TestSiftDetectorDescriptor::test_name()
{
  QCOMPARE("SIFT", mSiftDetectorDescriptor->name());
}

void TestSiftDetectorDescriptor::test_featuresNumber_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("10000") << 10000 << 10000;
}

void TestSiftDetectorDescriptor::test_featuresNumber()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSiftDetectorDescriptor->setFeaturesNumber(value);
  QCOMPARE(result, mSiftDetectorDescriptor->featuresNumber());
}

void TestSiftDetectorDescriptor::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("4") << 4 << 4;
  QTest::newRow("7") << 7 << 7;
}

void TestSiftDetectorDescriptor::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSiftDetectorDescriptor->setOctaveLayers(value);
  QCOMPARE(result, mSiftDetectorDescriptor->octaveLayers());
}

void TestSiftDetectorDescriptor::test_contrastThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.04") << 0.04 << 0.04;
  QTest::newRow("0.1") << 0.1 << 0.1;
  QTest::newRow("0.2") << 0.2 << 0.2;
}

void TestSiftDetectorDescriptor::test_contrastThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftDetectorDescriptor->setContrastThreshold(value);
  QCOMPARE(result, mSiftDetectorDescriptor->contrastThreshold());
}

void TestSiftDetectorDescriptor::test_edgeThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("20.") << 20. << 20.;
}

void TestSiftDetectorDescriptor::test_edgeThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftDetectorDescriptor->setEdgeThreshold(value);
  QCOMPARE(result, mSiftDetectorDescriptor->edgeThreshold());
}

void TestSiftDetectorDescriptor::test_sigma_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.") << 10. << 10.;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("20.") << 20. << 20.;
}

void TestSiftDetectorDescriptor::test_sigma()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mSiftDetectorDescriptor->setSigma(value);
  QCOMPARE(result, mSiftDetectorDescriptor->sigma());
}


#endif

QTEST_APPLESS_MAIN(TestSiftDetectorDescriptor)

#include "tst_siftdetectordescriptor.moc"
