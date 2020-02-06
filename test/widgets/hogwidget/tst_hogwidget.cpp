#include <QtTest>
#include <QCoreApplication>
#include <QSize>

#include "photomatch/widgets/HogWidget.h"

using namespace photomatch;

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
  void test_windowTitle();
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
//  void testWinSigma();
//  void testHistogramNormType();
//  void testL2HysThreshold();
//  void testGammaCorrection();
//  void testFree_coef();
//  void testNlevels();
//  void testSignedGradient();

private:

  HogWidget *mHogWidget;
};

TestHogWidget::TestHogWidget()
  : mHogWidget(new HogWidgetImp)
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

void TestHogWidget::cleanupTestCase()
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


void TestHogWidget::test_windowTitle()
{
  QCOMPARE("HOG", mHogWidget->windowTitle());
}

void TestHogWidget::test_winSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::test_winSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setWinSize(value);
  QCOMPARE(result, mHogWidget->winSize());
}

void TestHogWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setBlockSize(value);
  QCOMPARE(result, mHogWidget->blockSize());
}

void TestHogWidget::test_blockStride_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::test_blockStride()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setBlockStride(value);
  QCOMPARE(result, mHogWidget->blockStride());
}

void TestHogWidget::test_cellSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(0,0)") << QSize(0,0) << QSize(0,0);
  QTest::newRow("QSize(64,64)") << QSize(64,64) << QSize(64,64);
  QTest::newRow("QSize(64,128)") << QSize(64,128) << QSize(64,128);
  QTest::newRow("Out of range value 1") << QSize(10001,128) << QSize(10000,128);
  QTest::newRow("Out of range value 2") << QSize(64,10001) << QSize(64,10000);
}

void TestHogWidget::test_cellSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHogWidget->setCellSize(value);
  QCOMPARE(result, mHogWidget->cellSize());
}

void TestHogWidget::test_nbins_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestHogWidget::test_nbins()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mHogWidget->setNbins(value);
  QCOMPARE(result, mHogWidget->nbins());
}

void TestHogWidget::test_derivAperture_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestHogWidget::test_derivAperture()
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



QTEST_MAIN(TestHogWidget)

#include "tst_hogwidget.moc"
