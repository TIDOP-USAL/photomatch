#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MserWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestMserWidgetSignals : public MserWidgetImp
{
  Q_OBJECT

public:

  TestMserWidgetSignals();
  ~TestMserWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_deltaChange();
  void test_minAreaChange();
  void test_maxAreaChange();
  void test_maxVariationChange();
  void test_minDiversityChange();
  void test_maxEvolutionChange();
  void test_areaThresholdChange();
  void test_minMarginChange();
  void test_edgeBlurSizeChange();
};

TestMserWidgetSignals::TestMserWidgetSignals()
  : MserWidgetImp()
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
  QSignalSpy spyDeltaChange(this, &MserWidgetImp::deltaChange);
  QSignalSpy spyMinAreaChange(this, &MserWidgetImp::minAreaChange);
  QSignalSpy spyMaxAreaChange(this, &MserWidgetImp::maxAreaChange);
  QSignalSpy spyMaxVariationChange(this, &MserWidgetImp::maxVariationChange);
  QSignalSpy spyMinDiversityChange(this, &MserWidgetImp::minDiversityChange);
  QSignalSpy spyMaxEvolutionChange(this, &MserWidgetImp::maxEvolutionChange);
  QSignalSpy spyAreaThresholdChange(this, &MserWidgetImp::areaThresholdChange);
  QSignalSpy spyMinMarginChange(this, &MserWidgetImp::minMarginChange);
  QSignalSpy spyEdgeBlurSizeChange(this, &MserWidgetImp::edgeBlurSizeChange);

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

void TestMserWidgetSignals::test_deltaChange()
{
  QSignalSpy spyDeltaChange(this, &MserWidgetImp::deltaChange);

  this->mDelta->setValue(10);

  QCOMPARE(spyDeltaChange.count(), 1);

  QList<QVariant> args = spyDeltaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setDelta(15);
  QCOMPARE(spyDeltaChange.count(), 0);
}

void TestMserWidgetSignals::test_minAreaChange()
{
  QSignalSpy spyMinAreaChange(this, &MserWidgetImp::minAreaChange);

  this->mMinArea->setValue(10);

  QCOMPARE(spyMinAreaChange.count(), 1);

  QList<QVariant> args = spyMinAreaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 10);

  this->setMinArea(15);
  QCOMPARE(spyMinAreaChange.count(), 0);
}

void TestMserWidgetSignals::test_maxAreaChange()
{
  QSignalSpy spyMaxAreaChange(this, &MserWidgetImp::maxAreaChange);

  this->mMaxArea->setValue(5000);

  QCOMPARE(spyMaxAreaChange.count(), 1);

  QList<QVariant> args = spyMaxAreaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5000);

  this->setMaxArea(10000);
  QCOMPARE(spyMaxAreaChange.count(), 0);
}

void TestMserWidgetSignals::test_maxVariationChange()
{
  QSignalSpy spyMaxVariationChange(this, &MserWidgetImp::maxVariationChange);

  this->mMaxVariation->setValue(0.5);

  QCOMPARE(spyMaxVariationChange.count(), 1);

  QList<QVariant> args = spyMaxVariationChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setMaxVariation(0.6);
  QCOMPARE(spyMaxVariationChange.count(), 0);
}

void TestMserWidgetSignals::test_minDiversityChange()
{
  QSignalSpy spyMinDiversityChange(this, &MserWidgetImp::minDiversityChange);

  this->mMinDiversity->setValue(0.8);

  QCOMPARE(spyMinDiversityChange.count(), 1);

  QList<QVariant> args = spyMinDiversityChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setMinDiversity(0.3);
  QCOMPARE(spyMinDiversityChange.count(), 0);
}

void TestMserWidgetSignals::test_maxEvolutionChange()
{
  QSignalSpy spyMaxEvolutionChange(this, &MserWidgetImp::maxEvolutionChange);

  this->mMaxEvolution->setValue(500);

  QCOMPARE(spyMaxEvolutionChange.count(), 1);

  QList<QVariant> args = spyMaxEvolutionChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 500);

  this->setMaxEvolution(150);
  QCOMPARE(spyMaxEvolutionChange.count(), 0);
}

void TestMserWidgetSignals::test_areaThresholdChange()
{
  QSignalSpy spyAreaThresholdChange(this, &MserWidgetImp::areaThresholdChange);

  this->mAreaThreshold->setValue(0.8);

  QCOMPARE(spyAreaThresholdChange.count(), 1);

  QList<QVariant> args = spyAreaThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setAreaThreshold(1.0);
  QCOMPARE(spyAreaThresholdChange.count(), 0);
}

void TestMserWidgetSignals::test_minMarginChange()
{
  QSignalSpy spyMinMarginChange(this, &MserWidgetImp::minMarginChange);

  this->mMinMargin->setValue(0.8);

  QCOMPARE(spyMinMarginChange.count(), 1);

  QList<QVariant> args = spyMinMarginChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.8);

  this->setMinMargin(0.05);
  QCOMPARE(spyMinMarginChange.count(), 0);
}

void TestMserWidgetSignals::test_edgeBlurSizeChange()
{
  QSignalSpy spyEdgeBlurSizeChange(this, &MserWidgetImp::edgeBlurSizeChange);

  this->mEdgeBlurSize->setValue(20);

  QCOMPARE(spyEdgeBlurSizeChange.count(), 1);

  QList<QVariant> args = spyEdgeBlurSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 20);

  this->setEdgeBlurSize(10);
  QCOMPARE(spyEdgeBlurSizeChange.count(), 0);
}


QTEST_MAIN(TestMserWidgetSignals)

#include "tst_mserwidgetsignals.moc"
