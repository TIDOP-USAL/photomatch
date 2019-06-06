#include <QtTest>
#include <QCoreApplication>
#include <QSize>

#include "fme/widgets/HogWidget.h"

using namespace fme;

class TestHogWidget
  : public QObject
{
  Q_OBJECT

public:
  TestHogWidget();
  ~TestHogWidget();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testWinSize_data();
  void testWinSize();
  void testBlockSize_data();
  void testBlockSize();
  void testBlockStride_data();
  void testBlockStride();
  void testCellSize_data();
  void testCellSize();
  void testNbins_data();
  void testNbins();
  void testDerivAperture_data();
  void testDerivAperture();
//  void testWinSigma();
//  void testHistogramNormType();
//  void testL2HysThreshold();
//  void testGammaCorrection();
//  void testFree_coef();
//  void testNlevels();
//  void testSignedGradient();
  void testReset();

private:

  IHogWidget *mHogWidget;
};

TestHogWidget::TestHogWidget()
  : mHogWidget(new HogWidget)
{

}

TestHogWidget::~TestHogWidget()
{
  if (mHogWidget){
    delete mHogWidget;
    mHogWidget = nullptr;
  }
}

void TestHogWidget::initTestCase()
{

}

void TestHogWidget::cleanupTestCase()
{

}

void TestHogWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(QSize(64,128), mHogWidget->winSize());
  QCOMPARE(QSize(16,16), mHogWidget->blockSize());
  QCOMPARE(QSize(8,8), mHogWidget->blockStride());
  QCOMPARE(QSize(8,8), mHogWidget->cellSize());
  QCOMPARE(9, mHogWidget->nbins());
  QCOMPARE(1, mHogWidget->derivAperture());
//  QCOMPARE(-1, mHogWidget->winSigma());
//  QCOMPARE("L2Hys", mHogWidget->histogramNormType());
//  QCOMPARE(0.2, mHogWidget->l2HysThreshold());
//  QCOMPARE(true, mHogWidget->gammaCorrection());
//  QCOMPARE(-1., mHogWidget->freeCoef());
//  QCOMPARE(64, mHogWidget->nlevels());
//  QCOMPARE(false, mHogWidget->signedGradient());
}

void TestHogWidget::testWinSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::testWinSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setWinSize(value);
  QCOMPARE(result, mHogWidget->winSize());
}

void TestHogWidget::testBlockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::testBlockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setBlockSize(value);
  QCOMPARE(result, mHogWidget->blockSize());
}

void TestHogWidget::testBlockStride_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::testBlockStride()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setBlockStride(value);
  QCOMPARE(result, mHogWidget->blockStride());
}

void TestHogWidget::testCellSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::testCellSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setCellSize(value);
  QCOMPARE(result, mHogWidget->cellSize());
}

void TestHogWidget::testNbins_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestHogWidget::testNbins()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mHogWidget->setNbins(value);
  QCOMPARE(result, mHogWidget->nbins());
}

void TestHogWidget::testDerivAperture_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestHogWidget::testDerivAperture()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mHogWidget->setDerivAperture(value);
  QCOMPARE(result, mHogWidget->derivAperture());
}

//void TestHogWidget::testWinSigma()
//{

//}

//void TestHogWidget::testHistogramNormType()
//{

//}

//void TestHogWidget::testL2HysThreshold()
//{

//}

//void TestHogWidget::testGammaCorrection()
//{

//}

//void TestHogWidget::testFree_coef()
//{

//}

//void TestHogWidget::testNlevels()
//{

//}

//void TestHogWidget::testSignedGradient()
//{

//}

void TestHogWidget::testReset()
{
  mHogWidget->setWinSize(QSize(64,64));
  mHogWidget->setBlockSize(QSize(64,64));
  mHogWidget->setBlockStride(QSize(64,64));
  mHogWidget->setCellSize(QSize(64,64));
  mHogWidget->setNbins(250);
  mHogWidget->setDerivAperture(250);

  mHogWidget->reset();

  QCOMPARE(QSize(64,128), mHogWidget->winSize());
  QCOMPARE(QSize(16,16), mHogWidget->blockSize());
  QCOMPARE(QSize(8,8), mHogWidget->blockStride());
  QCOMPARE(QSize(8,8), mHogWidget->cellSize());
  QCOMPARE(9, mHogWidget->nbins());
  QCOMPARE(1, mHogWidget->derivAperture());
//  QCOMPARE(-1, mHogWidget->winSigma());
//  QCOMPARE("L2Hys", mHogWidget->histogramNormType());
//  QCOMPARE(0.2, mHogWidget->l2HysThreshold());
//  QCOMPARE(true, mHogWidget->gammaCorrection());
//  QCOMPARE(-1., mHogWidget->freeCoef());
//  QCOMPARE(64, mHogWidget->nlevels());
//  QCOMPARE(false, mHogWidget->signedGradient());
}


QTEST_MAIN(TestHogWidget)

#include "tst_hogwidget.moc"
