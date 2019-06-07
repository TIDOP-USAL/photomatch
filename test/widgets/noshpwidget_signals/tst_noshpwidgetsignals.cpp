#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/NoshpWidget.h"

#include <QSpinBox>

using namespace fme;


class TestNoshpWidgetSignals : public NoshpWidget
{
  Q_OBJECT

public:
  TestNoshpWidgetSignals();
  ~TestNoshpWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testTilesGridSizeChange();
  void testReset();

};

TestNoshpWidgetSignals::TestNoshpWidgetSignals()
  : NoshpWidget()
{

}

TestNoshpWidgetSignals::~TestNoshpWidgetSignals()
{

}

void TestNoshpWidgetSignals::initTestCase()
{

}

void TestNoshpWidgetSignals::cleanupTestCase()
{

}

void TestNoshpWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &NoshpWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 127));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestNoshpWidgetSignals::testReset()
{
  QSignalSpy spy_blockSizeChange(this, &NoshpWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestNoshpWidgetSignals)

#include "tst_noshpwidgetsignals.moc"
