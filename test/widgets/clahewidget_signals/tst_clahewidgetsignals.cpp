#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/CLAHEWidget.h"

#include <QSpinBox>

using namespace fme;


class TestCLAHEWidgetSignals : public CLAHEWidget
{
  Q_OBJECT

public:
  TestCLAHEWidgetSignals();
  ~TestCLAHEWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testClipLimitChange();
  void testTilesGridSizeChange();
  void testReset();

};

TestCLAHEWidgetSignals::TestCLAHEWidgetSignals()
  : CLAHEWidget()
{

}

TestCLAHEWidgetSignals::~TestCLAHEWidgetSignals()
{

}

void TestCLAHEWidgetSignals::initTestCase()
{

}

void TestCLAHEWidgetSignals::cleanupTestCase()
{

}

void TestCLAHEWidgetSignals::testClipLimitChange()
{
  QSignalSpy spyClipLimitChange(this, &CLAHEWidget::clipLimitChange);

  this->mClipLimit->setValue(50.);

  QCOMPARE(spyClipLimitChange.count(), 1);

  QList<QVariant> args = spyClipLimitChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 50.);

  this->setClipLimit(30.);
  QCOMPARE(spyClipLimitChange.count(), 0);
}

void TestCLAHEWidgetSignals::testTilesGridSizeChange()
{
  QSignalSpy spyTilesGridSizeChange(this, &CLAHEWidget::tileGridSizeChange);

  this->mTilesGridX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spyTilesGridSizeChange.count(), 1);

  QList<QVariant> args = spyTilesGridSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 8));

  this->setTilesGridSize(QSize(5, 7));
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}

void TestCLAHEWidgetSignals::testReset()
{
  QSignalSpy spyClipLimitChange(this, &CLAHEWidget::clipLimitChange);
  QSignalSpy spyTilesGridSizeChange(this, &CLAHEWidget::tileGridSizeChange);

  this->setClipLimit(30.);
  this->setTilesGridSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spyClipLimitChange.count(), 0);
  QCOMPARE(spyTilesGridSizeChange.count(), 0);
}

QTEST_MAIN(TestCLAHEWidgetSignals)

#include "tst_clahewidgetsignals.moc"
