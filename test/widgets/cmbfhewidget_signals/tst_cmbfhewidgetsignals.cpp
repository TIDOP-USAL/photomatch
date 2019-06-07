#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/CmbfheWidget.h"

#include <QSpinBox>

using namespace fme;

class TestCmbfheWidgetSignals : public CmbfheWidget
{
  Q_OBJECT

public:
  TestCmbfheWidgetSignals();
  ~TestCmbfheWidgetSignals();

private slots:

  void testTilesGridSizeChange();
  void testReset();

};

TestCmbfheWidgetSignals::TestCmbfheWidgetSignals()
  : CmbfheWidget()
{

}

TestCmbfheWidgetSignals::~TestCmbfheWidgetSignals()
{

}

void TestCmbfheWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &CmbfheWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 11));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestCmbfheWidgetSignals::testReset()
{
  QSignalSpy spy_blockSizeChange(this, &CmbfheWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestCmbfheWidgetSignals)

#include "tst_cmbfhewidgetsignals.moc"
