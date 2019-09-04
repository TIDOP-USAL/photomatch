#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/hog.h"

using namespace fme;

class TestHogDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestHogDescriptor();
  ~TestHogDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_winSize_data();
  void test_winSize();
  void test_blockSize_data();
  void test_blockSize();
  void test_blockStride_data();
  void test_blockStride();
  void test_cellSize_data();
  void test_cellSize();
  void test_nbins_data();
  void test_nbins();
  void test_derivAperture_data();
  void test_derivAperture();
  void test_reset();

private:

  HogDescriptor *mHogDescriptor;
};

TestHogDescriptor::TestHogDescriptor()
  : mHogDescriptor(new HogDescriptor)
{

}

TestHogDescriptor::~TestHogDescriptor()
{
  if (mHogDescriptor){
    delete mHogDescriptor;
    mHogDescriptor = nullptr;
  }
}

void TestHogDescriptor::initTestCase()
{

}

void TestHogDescriptor::cleanupTestCase()
{

}

void TestHogDescriptor::testDefaultConstructor()
{
  /// Check default values
  HogDescriptor hogDescriptor;
  /// Check default values
  QCOMPARE(QSize(16, 16), hogDescriptor.winSize());
  QCOMPARE(QSize(4, 4), hogDescriptor.blockSize());
  QCOMPARE(QSize(2, 2), hogDescriptor.blockStride());
  QCOMPARE(QSize(2, 2), hogDescriptor.cellSize());
  QCOMPARE(9, hogDescriptor.nbins());
  QCOMPARE(1, hogDescriptor.derivAperture());
//  QCOMPARE(-1, hogDescriptor.winSigma());
//  QCOMPARE("L2Hys", hogDescriptor.histogramNormType());
//  QCOMPARE(0.2, hogDescriptor.l2HysThreshold());
//  QCOMPARE(true, hogDescriptor.gammaCorrection());
//  QCOMPARE(-1., hogDescriptor.freeCoef());
//  QCOMPARE(64, hogDescriptor.nlevels());
  //  QCOMPARE(false, hogDescriptor.signedGradient());
}

void TestHogDescriptor::test_type()
{
  QCOMPARE(HogDescriptor::Type::hog, mHogDescriptor->type());
}

void TestHogDescriptor::test_name()
{
  QCOMPARE("HOG", mHogDescriptor->name());
}

void TestHogDescriptor::test_winSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
}

void TestHogDescriptor::test_winSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogDescriptor->setWinSize(value);
  QCOMPARE(result, mHogDescriptor->winSize());
}

void TestHogDescriptor::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
}

void TestHogDescriptor::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogDescriptor->setBlockSize(value);
  QCOMPARE(result, mHogDescriptor->blockSize());
}

void TestHogDescriptor::test_blockStride_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
}

void TestHogDescriptor::test_blockStride()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogDescriptor->setBlockStride(value);
  QCOMPARE(result, mHogDescriptor->blockStride());
}

void TestHogDescriptor::test_cellSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
}

void TestHogDescriptor::test_cellSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogDescriptor->setCellSize(value);
  QCOMPARE(result, mHogDescriptor->cellSize());
}

void TestHogDescriptor::test_nbins_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestHogDescriptor::test_nbins()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mHogDescriptor->setNbins(value);
  QCOMPARE(result, mHogDescriptor->nbins());
}

void TestHogDescriptor::test_derivAperture_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
}

void TestHogDescriptor::test_derivAperture()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mHogDescriptor->setDerivAperture(value);
  QCOMPARE(result, mHogDescriptor->derivAperture());
}

void TestHogDescriptor::test_reset()
{
  mHogDescriptor->setWinSize(QSize(64,64));
  mHogDescriptor->setBlockSize(QSize(64,64));
  mHogDescriptor->setBlockStride(QSize(64,64));
  mHogDescriptor->setCellSize(QSize(64,64));
  mHogDescriptor->setNbins(250);
  mHogDescriptor->setDerivAperture(250);

  mHogDescriptor->reset();

  QCOMPARE(QSize(16, 16), mHogDescriptor->winSize());
  QCOMPARE(QSize(4, 4), mHogDescriptor->blockSize());
  QCOMPARE(QSize(2, 2), mHogDescriptor->blockStride());
  QCOMPARE(QSize(2, 2), mHogDescriptor->cellSize());
  QCOMPARE(9, mHogDescriptor->nbins());
  QCOMPARE(1, mHogDescriptor->derivAperture());
//  QCOMPARE(-1, mHogDescriptor->winSigma());
//  QCOMPARE("L2Hys", mHogDescriptor->histogramNormType());
//  QCOMPARE(0.2, mHogDescriptor->l2HysThreshold());
//  QCOMPARE(true, mHogDescriptor->gammaCorrection());
//  QCOMPARE(-1., mHogDescriptor->freeCoef());
//  QCOMPARE(64, mHogDescriptor->nlevels());
//  QCOMPARE(false, mHogDescriptor->signedGradient());
}


QTEST_APPLESS_MAIN(TestHogDescriptor)

#include "tst_hogdescriptor.moc"
