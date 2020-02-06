#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/CmbfheWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestCmbfheWidgetSignals : public CmbfheWidgetImp
{
  Q_OBJECT

public:
  TestCmbfheWidgetSignals();
  ~TestCmbfheWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_tilesGridSizeChange();

};

TestCmbfheWidgetSignals::TestCmbfheWidgetSignals()
  : CmbfheWidgetImp()
{

}

TestCmbfheWidgetSignals::~TestCmbfheWidgetSignals()
{

}

void TestCmbfheWidgetSignals::initTestCase()
{

}

void TestCmbfheWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_blockSizeChange(this, &CmbfheWidgetImp::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestCmbfheWidgetSignals::test_tilesGridSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &CmbfheWidgetImp::blockSizeChange);

  this->mBlockSizeX->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 11));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}



QTEST_MAIN(TestCmbfheWidgetSignals)

#include "tst_cmbfhewidgetsignals.moc"
