#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/RswheWidget.h"

#include <QSpinBox>
#include <QRadioButton>

using namespace photomatch;

class TestRswheWidgetSignals : public RswheWidgetImp
{
  Q_OBJECT

public:
  TestRswheWidgetSignals();
  ~TestRswheWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_histogramDivisionsChange();
  void test_histogramCutChange();

};

TestRswheWidgetSignals::TestRswheWidgetSignals()
  : RswheWidgetImp()
{

}

TestRswheWidgetSignals::~TestRswheWidgetSignals()
{

}

void TestRswheWidgetSignals::initTestCase()
{

}

void TestRswheWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_histogramDivisionsChange(this, &RswheWidgetImp::histogramDivisionsChange);

  this->setHistogramDivisions(5);

  this->reset();

  QCOMPARE(spy_histogramDivisionsChange.count(), 0);
}

void TestRswheWidgetSignals::test_histogramDivisionsChange()
{
  QSignalSpy spy_histogramDivisionsChange(this, &RswheWidgetImp::histogramDivisionsChange);

  mHistogramDivisions->setValue(4);

  QCOMPARE(spy_histogramDivisionsChange.count(), 1);

  QList<QVariant> args = spy_histogramDivisionsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setHistogramDivisions(10);
  QCOMPARE(spy_histogramDivisionsChange.count(), 0);
}

void TestRswheWidgetSignals::test_histogramCutChange()
{
  QSignalSpy spy_histogramCutChange(this, &RswheWidgetImp::histogramCutChange);

//  QTest::mouseClick(mHistogramCutByMedian, Qt::MouseButton::LeftButton);

//  QCOMPARE(spy_histogramCutChange.count(), 1);

//  QList<QVariant> args = spy_histogramCutChange.takeFirst();
//  QCOMPARE(args.at(0).value<IRswheWidget::HistogramCut>(), IRswheWidget::HistogramCut::by_median);

//  QTest::mouseClick(mHistogramCutByMean, Qt::MouseButton::LeftButton);

//  QCOMPARE(spy_histogramCutChange.count(), 1);

//  args = spy_histogramCutChange.takeFirst();
//  QCOMPARE(args.at(0).value<IRswheWidget::HistogramCut>(), IRswheWidget::HistogramCut::by_mean);

//  this->setHistogramCut(RswheWidget::HistogramCut::by_median);
//  QCOMPARE(spy_histogramCutChange.count(), 0);
}


QTEST_MAIN(TestRswheWidgetSignals)

#include "tst_rswhewidgetsignals.moc"
