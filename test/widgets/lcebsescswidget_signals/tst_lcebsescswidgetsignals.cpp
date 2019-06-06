#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/LceBsescsWidget.h"

#include <QSpinBox>

using namespace fme;


class TestLceBsescsWidgetSignals : public LceBsescsWidget
{
  Q_OBJECT

public:
  TestLceBsescsWidgetSignals();
  ~TestLceBsescsWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testTilesGridSizeChange();
  void testReset();

};

TestLceBsescsWidgetSignals::TestLceBsescsWidgetSignals()
  : LceBsescsWidget()
{

}

TestLceBsescsWidgetSignals::~TestLceBsescsWidgetSignals()
{

}

void TestLceBsescsWidgetSignals::initTestCase()
{

}

void TestLceBsescsWidgetSignals::cleanupTestCase()
{

}

void TestLceBsescsWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &LceBsescsWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 33));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestLceBsescsWidgetSignals::testReset()
{
  QSignalSpy spy_blockSizeChange(this, &LceBsescsWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestLceBsescsWidgetSignals)

#include "tst_lcebsescswidgetsignals.moc"
