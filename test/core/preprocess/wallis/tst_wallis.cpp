#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/wallis.h"

using namespace photomatch;

class TestWallis
  : public QObject
{
  Q_OBJECT

public:

  TestWallis();
  ~TestWallis();

private slots:

  void test_constructors();
  void test_type();
  void test_name();
  void testContrast_data();
  void testContrast();
  void testBrightness_data();
  void testBrightness();
  void testImposedAverage_data();
  void testImposedAverage();
  void testImposedLocalStdDev_data();
  void testImposedLocalStdDev();
  void testKernelSize_data();
  void testKernelSize();
  void testReset();

private:

  WallisPreprocess *mWallisPreprocess;
};

TestWallis::TestWallis()
  : mWallisPreprocess(new WallisPreprocess)
{

}

TestWallis::~TestWallis()
{
  if (mWallisPreprocess){
    delete mWallisPreprocess;
    mWallisPreprocess = nullptr;
  }
}

void TestWallis::test_constructors()
{
  WallisPreprocess wallisPreprocess;
  QCOMPARE(1.0, wallisPreprocess.contrast());
  QCOMPARE(0.2, wallisPreprocess.brightness());
  QCOMPARE(41, wallisPreprocess.imposedAverage());
  QCOMPARE(127, wallisPreprocess.imposedLocalStdDev());
  QCOMPARE(50, wallisPreprocess.kernelSize());
}

void TestWallis::test_type()
{
  QCOMPARE(Preprocess::Type::wallis, mWallisPreprocess->type());
}

void TestWallis::test_name()
{
  QCOMPARE(QString("WALLIS"), mWallisPreprocess->name());
}

void TestWallis::testContrast_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
}

void TestWallis::testContrast()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisPreprocess->setContrast(value);
  QCOMPARE(result, mWallisPreprocess->contrast());
}

void TestWallis::testBrightness_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
}

void TestWallis::testBrightness()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisPreprocess->setBrightness(value);
  QCOMPARE(result, mWallisPreprocess->brightness());
}

void TestWallis::testImposedAverage_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::testImposedAverage()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setImposedAverage(value);
  QCOMPARE(result, mWallisPreprocess->imposedAverage());
}

void TestWallis::testImposedLocalStdDev_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::testImposedLocalStdDev()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setImposedLocalStdDev(value);
  QCOMPARE(result, mWallisPreprocess->imposedLocalStdDev());
}

void TestWallis::testKernelSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::testKernelSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setKernelSize(value);
  QCOMPARE(result, mWallisPreprocess->kernelSize());
}

void TestWallis::testReset()
{
  mWallisPreprocess->setContrast(.5);
  mWallisPreprocess->setBrightness(0.5);
  mWallisPreprocess->setImposedAverage(35);
  mWallisPreprocess->setImposedLocalStdDev(150);
  mWallisPreprocess->setKernelSize(60);

  mWallisPreprocess->reset();

  QCOMPARE(1.0, mWallisPreprocess->contrast());
  QCOMPARE(0.2, mWallisPreprocess->brightness());
  QCOMPARE(41, mWallisPreprocess->imposedAverage());
  QCOMPARE(127, mWallisPreprocess->imposedLocalStdDev());
  QCOMPARE(50, mWallisPreprocess->kernelSize());
}

QTEST_MAIN(TestWallis)

#include "tst_wallis.moc"
