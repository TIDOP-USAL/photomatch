#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/MserWidget.h"

#include <QSpinBox>

using namespace fme;

class TestMserWidgetSignals : public MserWidget
{
  Q_OBJECT

public:

  TestMserWidgetSignals();
  ~TestMserWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDeltaChange();
  void testMinAreaChange();
  void testMaxAreaChange();
  void testMaxVariationChange();
  void testMinDiversityChange();
  void testMaxEvolutionChange();
  void testAreaThresholdChange();
  void testMinMarginChange();
  void testEdgeBlurSizeChange();
  void testReset();
};

TestMserWidgetSignals::TestMserWidgetSignals()
  : MserWidget()
{

}

TestMserWidgetSignals::~TestMserWidgetSignals()
{

}

void TestMserWidgetSignals::initTestCase()
{

}

void TestMserWidgetSignals::cleanupTestCase()
{

}

void TestMserWidgetSignals::testDeltaChange()
{
  QSignalSpy spyDeltaChange(this, &MserWidget::deltaChange);

  this->mDelta->setValue(10);

  QCOMPARE(spyDeltaChange.count(), 1);

  QList<QVariant> args = spyDeltaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setDelta(15);
  QCOMPARE(spyDeltaChange.count(), 0);
}

void TestMserWidgetSignals::testMinAreaChange()
{
  QSignalSpy spyMinAreaChange(this, &MserWidget::minAreaChange);

  this->mMinArea->setValue(10);

  QCOMPARE(spyMinAreaChange.count(), 1);

  QList<QVariant> args = spyMinAreaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setMinArea(15);
  QCOMPARE(spyMinAreaChange.count(), 0);
}

void TestMserWidgetSignals::testMaxAreaChange()
{
  QSignalSpy spyMaxAreaChange(this, &MserWidget::maxAreaChange);

  this->mMaxArea->setValue(5000);

  QCOMPARE(spyMaxAreaChange.count(), 1);

  QList<QVariant> args = spyMaxAreaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5000);

  this->setMaxArea(10000);
  QCOMPARE(spyMaxAreaChange.count(), 0);
}

void TestMserWidgetSignals::testMaxVariationChange()
{
  QSignalSpy spyMaxVariationChange(this, &MserWidget::maxVariationChange);

  this->mMaxVariation->setValue(0.5);

  QCOMPARE(spyMaxVariationChange.count(), 1);

  QList<QVariant> args = spyMaxVariationChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setMaxVariation(0.6);
  QCOMPARE(spyMaxVariationChange.count(), 0);
}

void TestMserWidgetSignals::testMinDiversityChange()
{
  QSignalSpy spyMinDiversityChange(this, &MserWidget::minDiversityChange);

  this->mMinDiversity->setValue(0.8);

  QCOMPARE(spyMinDiversityChange.count(), 1);

  QList<QVariant> args = spyMinDiversityChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setMinDiversity(0.3);
  QCOMPARE(spyMinDiversityChange.count(), 0);
}

void TestMserWidgetSignals::testMaxEvolutionChange()
{
  QSignalSpy spyMaxEvolutionChange(this, &MserWidget::maxEvolutionChange);

  this->mMaxEvolution->setValue(500);

  QCOMPARE(spyMaxEvolutionChange.count(), 1);

  QList<QVariant> args = spyMaxEvolutionChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 500);

  this->setMaxEvolution(150);
  QCOMPARE(spyMaxEvolutionChange.count(), 0);
}

void TestMserWidgetSignals::testAreaThresholdChange()
{
  QSignalSpy spyAreaThresholdChange(this, &MserWidget::areaThresholdChange);

  this->mAreaThreshold->setValue(0.8);

  QCOMPARE(spyAreaThresholdChange.count(), 1);

  QList<QVariant> args = spyAreaThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setAreaThreshold(1.0);
  QCOMPARE(spyAreaThresholdChange.count(), 0);
}

void TestMserWidgetSignals::testMinMarginChange()
{
  QSignalSpy spyMinMarginChange(this, &MserWidget::minMarginChange);

  this->mMinMargin->setValue(0.8);

  QCOMPARE(spyMinMarginChange.count(), 1);

  QList<QVariant> args = spyMinMarginChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setMinMargin(0.05);
  QCOMPARE(spyMinMarginChange.count(), 0);
}

void TestMserWidgetSignals::testEdgeBlurSizeChange()
{
  QSignalSpy spyEdgeBlurSizeChange(this, &MserWidget::edgeBlurSizeChange);

  this->mEdgeBlurSize->setValue(20);

  QCOMPARE(spyEdgeBlurSizeChange.count(), 1);

  QList<QVariant> args = spyEdgeBlurSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 20);

  this->setEdgeBlurSize(10);
  QCOMPARE(spyEdgeBlurSizeChange.count(), 0);
}

void TestMserWidgetSignals::testReset()
{
  QSignalSpy spyDeltaChange(this, &MserWidget::deltaChange);
  QSignalSpy spyMinAreaChange(this, &MserWidget::minAreaChange);
  QSignalSpy spyMaxAreaChange(this, &MserWidget::maxAreaChange);
  QSignalSpy spyMaxVariationChange(this, &MserWidget::maxVariationChange);
  QSignalSpy spyMinDiversityChange(this, &MserWidget::minDiversityChange);
  QSignalSpy spyMaxEvolutionChange(this, &MserWidget::maxEvolutionChange);
  QSignalSpy spyAreaThresholdChange(this, &MserWidget::areaThresholdChange);
  QSignalSpy spyMinMarginChange(this, &MserWidget::minMarginChange);
  QSignalSpy spyEdgeBlurSizeChange(this, &MserWidget::edgeBlurSizeChange);

  this->setDelta(15);
  this->setMinArea(15);
  this->setMaxArea(10000);
  this->setMaxVariation(0.6);
  this->setMinDiversity(0.3);
  this->setMaxEvolution(150);
  this->setAreaThreshold(1.0);
  this->setMinMargin(0.05);
  this->setEdgeBlurSize(10);

  this->reset();

  QCOMPARE(spyDeltaChange.count(), 0);
  QCOMPARE(spyMinAreaChange.count(), 0);
  QCOMPARE(spyMaxAreaChange.count(), 0);
  QCOMPARE(spyMaxVariationChange.count(), 0);
  QCOMPARE(spyMinDiversityChange.count(), 0);
  QCOMPARE(spyMaxEvolutionChange.count(), 0);
  QCOMPARE(spyAreaThresholdChange.count(), 0);
  QCOMPARE(spyMinMarginChange.count(), 0);
  QCOMPARE(spyEdgeBlurSizeChange.count(), 0);
}


QTEST_MAIN(TestMserWidgetSignals)

#include "tst_mserwidgetsignals.moc"
