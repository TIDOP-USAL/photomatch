#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/ClaheWidget.h"

#include <QSpinBox>

using namespace photomatch;


class TestClaheWidgetSignals : public ClaheWidgetImp
{
  Q_OBJECT

public:
  TestClaheWidgetSignals();
  ~TestClaheWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_clipLimitChange();
  void test_tilesGridSizeChange();


};

TestClaheWidgetSignals::TestClaheWidgetSignals()
  : ClaheWidgetImp()
{

}

TestClaheWidgetSignals::~TestClaheWidgetSignals()
{

}

void TestClaheWidgetSignals::initTestCase()
{

}

void TestClaheWidgetSignals::cleanupTestCase()
{
  QSignalSpy spyClipLimitChange(this, &ClaheWidgetImp::clipLimitChange);
  QSignalSpy spyTilesGridSizeChange(this, &ClaheWidgetImp::tileGridSizeChange);

  this->setClipLimit(30.);
  this->setTilesGridSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spyClipLimitChange.count(), 0);
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}

void TestClaheWidgetSignals::test_clipLimitChange()
{
  QSignalSpy spyClipLimitChange(this, &ClaheWidgetImp::clipLimitChange);

  this->mClipLimit->setValue(50.);

  QCOMPARE(spyClipLimitChange.count(), 1);

  QList<QVariant> args = spyClipLimitChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 50.);

  this->setClipLimit(30.);
  QCOMPARE(spyClipLimitChange.count(), 0);
}

void TestClaheWidgetSignals::test_tilesGridSizeChange()
{
  QSignalSpy spyTilesGridSizeChange(this, &ClaheWidgetImp::tileGridSizeChange);

  this->mTilesGridX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spyTilesGridSizeChange.count(), 1);

  QList<QVariant> args = spyTilesGridSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 8));

  this->setTilesGridSize(QSize(5, 7));
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}


QTEST_MAIN(TestClaheWidgetSignals)

#include "tst_clahewidgetsignals.moc"
