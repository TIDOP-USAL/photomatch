#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/HogWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestHogWidgetSignals : public HogWidgetImp
{
  Q_OBJECT

public:
  TestHogWidgetSignals();
  ~TestHogWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_winSizeChange();
  void test_blockSizeChange();
  void test_blockStrideChange();
  void test_cellSizeChange();
  void test_nbinsChange();
  void test_derivApertureChange();

};

TestHogWidgetSignals::TestHogWidgetSignals()
  : HogWidgetImp()
{

}

TestHogWidgetSignals::~TestHogWidgetSignals()
{

}

void TestHogWidgetSignals::initTestCase()
{

}

void TestHogWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_winSizeChange(this, &HogWidgetImp::winSizeChange);
  QSignalSpy spy_blockSizeChange(this, &HogWidgetImp::blockSizeChange);
  QSignalSpy spy_blockStrideChange(this, &HogWidgetImp::blockStrideChange);
  QSignalSpy spy_cellSizeChange(this, &HogWidgetImp::cellSizeChange);
  QSignalSpy spy_nbinsChange(this, &HogWidgetImp::nbinsChange);
  QSignalSpy spy_derivApertureChange(this, &HogWidgetImp::derivApertureChange);

  this->setWinSize(QSize(30,30));
  this->setBlockSize(QSize(30,30));
  this->setBlockStride(QSize(30,30));
  this->setCellSize(QSize(30,30));
  this->setNbins(40);
  this->setDerivAperture(40);

  this->reset();

  QCOMPARE(spy_winSizeChange.count(), 0);
  QCOMPARE(spy_blockSizeChange.count(), 0);
  QCOMPARE(spy_blockStrideChange.count(), 0);
  QCOMPARE(spy_cellSizeChange.count(), 0);
  QCOMPARE(spy_nbinsChange.count(), 0);
  QCOMPARE(spy_derivApertureChange.count(), 0);
}

void TestHogWidgetSignals::test_winSizeChange()
{
  QSignalSpy spy_winSizeChange(this, &HogWidgetImp::winSizeChange);

  this->mWinSizeWidth->setValue(50);

  QCOMPARE(spy_winSizeChange.count(), 1);

  this->mWinSizeHeight->setValue(50);

  QCOMPARE(spy_winSizeChange.count(), 2);

  QList<QVariant> args = spy_winSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(50,128));
  args = spy_winSizeChange.takeLast();
  QCOMPARE(args.at(0).toSize(), QSize(50,50));

  this->setWinSize(QSize(25,25));
  QCOMPARE(spy_winSizeChange.count(), 0);
}

void TestHogWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &HogWidgetImp::blockSizeChange);

  this->mBlockSizeX->setValue(50);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  this->mBlockSizeY->setValue(50);

  QCOMPARE(spy_blockSizeChange.count(), 2);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(50,16));
  args = spy_blockSizeChange.takeLast();
  QCOMPARE(args.at(0).toSize(), QSize(50,50));

  this->setBlockSize(QSize(25,25));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestHogWidgetSignals::test_blockStrideChange()
{
  QSignalSpy spy_blockStrideChange(this, &HogWidgetImp::blockStrideChange);

  this->mBlockStrideX->setValue(50);

  QCOMPARE(spy_blockStrideChange.count(), 1);

  this->mBlockStrideY->setValue(50);

  QCOMPARE(spy_blockStrideChange.count(), 2);

  QList<QVariant> args = spy_blockStrideChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(50,8));
  args = spy_blockStrideChange.takeLast();
  QCOMPARE(args.at(0).toSize(), QSize(50,50));

  this->setBlockStride(QSize(25,25));
  QCOMPARE(spy_blockStrideChange.count(), 0);
}

void TestHogWidgetSignals::test_cellSizeChange()
{
  QSignalSpy spy_cellSizeChange(this, &HogWidgetImp::cellSizeChange);

  this->mCellSizeX->setValue(50);

  QCOMPARE(spy_cellSizeChange.count(), 1);

  this->mCellSizeY->setValue(50);

  QCOMPARE(spy_cellSizeChange.count(), 2);

  QList<QVariant> args = spy_cellSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(50,8));
  args = spy_cellSizeChange.takeLast();
  QCOMPARE(args.at(0).toSize(), QSize(50,50));

  this->setCellSize(QSize(25,25));
  QCOMPARE(spy_cellSizeChange.count(), 0);
}

void TestHogWidgetSignals::test_nbinsChange()
{
  QSignalSpy spy_nbinsChange(this, &HogWidgetImp::nbinsChange);

  this->mNbins->setValue(10);

  QCOMPARE(spy_nbinsChange.count(), 1);

  QList<QVariant> args = spy_nbinsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setNbins(30);
  QCOMPARE(spy_nbinsChange.count(), 0);
}

void TestHogWidgetSignals::test_derivApertureChange()
{
  QSignalSpy spy_derivApertureChange(this, &HogWidgetImp::derivApertureChange);

  this->mDerivAperture->setValue(10);

  QCOMPARE(spy_derivApertureChange.count(), 1);

  QList<QVariant> args = spy_derivApertureChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setDerivAperture(30);
  QCOMPARE(spy_derivApertureChange.count(), 0);
}



QTEST_MAIN(TestHogWidgetSignals)

#include "tst_hogwidgetsignals.moc"
