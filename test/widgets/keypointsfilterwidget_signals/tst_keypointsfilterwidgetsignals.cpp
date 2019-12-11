#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/KeypointsFilterWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestKeypointsFilterWidgetSignals
  : public KeypointsFilterWidget
{
  Q_OBJECT

public:

  TestKeypointsFilterWidgetSignals();
  ~TestKeypointsFilterWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_nPointsChange();
  void test_minSizeChange();
  void test_maxSizeChange();
};

TestKeypointsFilterWidgetSignals::TestKeypointsFilterWidgetSignals()
  : KeypointsFilterWidget()
{

}

TestKeypointsFilterWidgetSignals::~TestKeypointsFilterWidgetSignals()
{

}

void TestKeypointsFilterWidgetSignals::initTestCase()
{

}

void TestKeypointsFilterWidgetSignals::cleanupTestCase()
{

}

void TestKeypointsFilterWidgetSignals::test_nPointsChange()
{
  QSignalSpy spy_nPointsChange(this, &KeypointsFilterWidget::nPointsChange);

  this->mPointsNumber->setValue(6000);

  QCOMPARE(spy_nPointsChange.count(), 1);

  QList<QVariant> args = spy_nPointsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 6000);

  this->setNPoints(7000);
  QCOMPARE(spy_nPointsChange.count(), 0);
}

void TestKeypointsFilterWidgetSignals::test_minSizeChange()
{
  QSignalSpy spy_minSizeChange(this, &KeypointsFilterWidget::minSizeChange);

  this->mMinSize->setValue(5.);

  QCOMPARE(spy_minSizeChange.count(), 1);

  QList<QVariant> args = spy_minSizeChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.);

  this->setMinSize(0.1);
  QCOMPARE(spy_minSizeChange.count(), 0);
}

void TestKeypointsFilterWidgetSignals::test_maxSizeChange()
{
  QSignalSpy spy_maxSizeChange(this, &KeypointsFilterWidget::maxSizeChange);

  this->mMaxSize->setValue(25.);

  QCOMPARE(spy_maxSizeChange.count(), 1);

  QList<QVariant> args = spy_maxSizeChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setMaxSize(120.);
  QCOMPARE(spy_maxSizeChange.count(), 0);

}


QTEST_MAIN(TestKeypointsFilterWidgetSignals)

#include "tst_keypointsfilterwidgetsignals.moc"
