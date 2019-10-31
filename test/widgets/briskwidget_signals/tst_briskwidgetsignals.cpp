#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/BriskWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestBriskWidgetSignals : public BriskWidget
{
    Q_OBJECT

public:

  TestBriskWidgetSignals();
  ~TestBriskWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testThresholdChange();
  void testOctavesChange();
  void testPatternScaleChange();
  void testReset();
};

TestBriskWidgetSignals::TestBriskWidgetSignals()
  : BriskWidget()
{

}

TestBriskWidgetSignals::~TestBriskWidgetSignals()
{

}

void TestBriskWidgetSignals::initTestCase()
{

}

void TestBriskWidgetSignals::cleanupTestCase()
{

}

void TestBriskWidgetSignals::testThresholdChange()
{
  QSignalSpy spyThresholdChange(this, &BriskWidget::thresholdChange);

  mThreshold->setValue(20);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20);

  this->setThreshold(50);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestBriskWidgetSignals::testOctavesChange()
{
  QSignalSpy spyOctavesChange(this, &BriskWidget::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestBriskWidgetSignals::testPatternScaleChange()
{
  QSignalSpy spyPatternScaleChange(this, &BriskWidget::patternScaleChange);

  mPatternScale->setValue(20.);

  QCOMPARE(spyPatternScaleChange.count(), 1);

  QList<QVariant> args = spyPatternScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20.);

  this->setPatternScale(50.);
  QCOMPARE(spyPatternScaleChange.count(), 0);
}

void TestBriskWidgetSignals::testReset()
{
  QSignalSpy spyThresholdChange(this, &BriskWidget::thresholdChange);
  QSignalSpy spyOctavesChange(this, &BriskWidget::octavesChange);
  QSignalSpy spyPatternScaleChange(this, &BriskWidget::patternScaleChange);

  this->setThreshold(20);
  this->setOctaves(4);
  this->setPatternScale(50.);

  this->reset();

  QCOMPARE(spyThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyPatternScaleChange.count(), 0);
}

QTEST_MAIN(TestBriskWidgetSignals)

#include "tst_briskwidgetsignals.moc"
