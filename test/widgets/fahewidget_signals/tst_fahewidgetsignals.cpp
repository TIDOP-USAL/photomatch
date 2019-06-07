#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/FaheWidget.h"

#include <QSpinBox>

using namespace fme;


class TestFaheWidgetSignals : public FaheWidget
{
  Q_OBJECT

public:
  TestFaheWidgetSignals();
  ~TestFaheWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testTilesGridSizeChange();
  void testReset();

};

TestFaheWidgetSignals::TestFaheWidgetSignals()
  : FaheWidget()
{

}

TestFaheWidgetSignals::~TestFaheWidgetSignals()
{

}

void TestFaheWidgetSignals::initTestCase()
{

}

void TestFaheWidgetSignals::cleanupTestCase()
{

}

void TestFaheWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &FaheWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 11));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestFaheWidgetSignals::testReset()
{
  QSignalSpy spy_blockSizeChange(this, &FaheWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestFaheWidgetSignals)

#include "tst_fahewidgetsignals.moc"
