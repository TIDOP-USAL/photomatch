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

  void initTestCase();
  void cleanupTestCase();
  void test_copyConstructor();
  void test_type();
  void test_name();
  void test_contrast_data();
  void test_contrast();
  void test_brightness_data();
  void test_brightness();
  void test_imposedAverage_data();
  void test_imposedAverage();
  void test_imposedLocalStdDev_data();
  void test_imposedLocalStdDev();
  void test_kernelSize_data();
  void test_kernelSize();

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

void TestWallis::initTestCase()
{
  QCOMPARE(1.0, mWallisPreprocess->contrast());
  QCOMPARE(0.2, mWallisPreprocess->brightness());
  QCOMPARE(41, mWallisPreprocess->imposedAverage());
  QCOMPARE(127, mWallisPreprocess->imposedLocalStdDev());
  QCOMPARE(50, mWallisPreprocess->kernelSize());
}

void TestWallis::cleanupTestCase()
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

void TestWallis::test_copyConstructor()
{
  WallisPreprocess wallisPreprocess(1.5, 0.3, 41, 64, 25);
  QCOMPARE(1.5, wallisPreprocess.contrast());
  QCOMPARE(0.3, wallisPreprocess.brightness());
  QCOMPARE(41, wallisPreprocess.imposedAverage());
  QCOMPARE(64, wallisPreprocess.imposedLocalStdDev());
  QCOMPARE(25, wallisPreprocess.kernelSize());
}

void TestWallis::test_type()
{
  QCOMPARE(Preprocess::Type::wallis, mWallisPreprocess->type());
}

void TestWallis::test_name()
{
  QCOMPARE(QString("WALLIS"), mWallisPreprocess->name());
}

void TestWallis::test_contrast_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
}

void TestWallis::test_contrast()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisPreprocess->setContrast(value);
  QCOMPARE(result, mWallisPreprocess->contrast());
}

void TestWallis::test_brightness_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
}

void TestWallis::test_brightness()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mWallisPreprocess->setBrightness(value);
  QCOMPARE(result, mWallisPreprocess->brightness());
}

void TestWallis::test_imposedAverage_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::test_imposedAverage()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setImposedAverage(value);
  QCOMPARE(result, mWallisPreprocess->imposedAverage());
}

void TestWallis::test_imposedLocalStdDev_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::test_imposedLocalStdDev()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setImposedLocalStdDev(value);
  QCOMPARE(result, mWallisPreprocess->imposedLocalStdDev());
}

void TestWallis::test_kernelSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestWallis::test_kernelSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mWallisPreprocess->setKernelSize(value);
  QCOMPARE(result, mWallisPreprocess->kernelSize());
}

QTEST_MAIN(TestWallis)

#include "tst_wallis.moc"
