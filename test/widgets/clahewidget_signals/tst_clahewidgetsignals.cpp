#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/ClaheWidget.h"

#include <QSpinBox>

using namespace fme;


class TestClaheWidgetSignals : public ClaheWidget
{
  Q_OBJECT

public:
  TestClaheWidgetSignals();
  ~TestClaheWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testClipLimitChange();
  void testTilesGridSizeChange();
  void testReset();

};

TestClaheWidgetSignals::TestClaheWidgetSignals()
  : ClaheWidget()
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

}

void TestClaheWidgetSignals::testClipLimitChange()
{
  QSignalSpy spyClipLimitChange(this, &ClaheWidget::clipLimitChange);

  this->mClipLimit->setValue(50.);

  QCOMPARE(spyClipLimitChange.count(), 1);

  QList<QVariant> args = spyClipLimitChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 50.);

  this->setClipLimit(30.);
  QCOMPARE(spyClipLimitChange.count(), 0);
}

void TestClaheWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spyTilesGridSizeChange(this, &ClaheWidget::tileGridSizeChange);

  this->mTilesGridX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spyTilesGridSizeChange.count(), 1);

  QList<QVariant> args = spyTilesGridSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 8));

  this->setTilesGridSize(QSize(5, 7));
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}

void TestClaheWidgetSignals::testReset()
{
  QSignalSpy spyClipLimitChange(this, &ClaheWidget::clipLimitChange);
  QSignalSpy spyTilesGridSizeChange(this, &ClaheWidget::tileGridSizeChange);

  this->setClipLimit(30.);
  this->setTilesGridSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spyClipLimitChange.count(), 0);
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}

QTEST_MAIN(TestClaheWidgetSignals)

#include "tst_clahewidgetsignals.moc"
