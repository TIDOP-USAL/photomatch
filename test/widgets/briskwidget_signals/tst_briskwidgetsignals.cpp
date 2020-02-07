#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/BriskWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestBriskWidgetSignals : public BriskWidgetImp
{
    Q_OBJECT

public:

  TestBriskWidgetSignals();
  ~TestBriskWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_thresholdChange();
  void test_octavesChange();
  void test_patternScaleChange();

};

TestBriskWidgetSignals::TestBriskWidgetSignals()
  : BriskWidgetImp()
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
  QSignalSpy spyThresholdChange(this, &BriskWidgetImp::thresholdChange);
  QSignalSpy spyOctavesChange(this, &BriskWidgetImp::octavesChange);
  QSignalSpy spyPatternScaleChange(this, &BriskWidgetImp::patternScaleChange);

  this->setThreshold(20);
  this->setOctaves(4);
  this->setPatternScale(50.);

  this->reset();

  QCOMPARE(spyThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyPatternScaleChange.count(), 0);
}

void TestBriskWidgetSignals::test_thresholdChange()
{
  QSignalSpy spyThresholdChange(this, &BriskWidgetImp::thresholdChange);

  mThreshold->setValue(20);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20);

  this->setThreshold(50);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestBriskWidgetSignals::test_octavesChange()
{
  QSignalSpy spyOctavesChange(this, &BriskWidgetImp::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestBriskWidgetSignals::test_patternScaleChange()
{
  QSignalSpy spyPatternScaleChange(this, &BriskWidgetImp::patternScaleChange);

  mPatternScale->setValue(20.);

  QCOMPARE(spyPatternScaleChange.count(), 1);

  QList<QVariant> args = spyPatternScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20.);

  this->setPatternScale(50.);
  QCOMPARE(spyPatternScaleChange.count(), 0);
}



QTEST_MAIN(TestBriskWidgetSignals)

#include "tst_briskwidgetsignals.moc"
