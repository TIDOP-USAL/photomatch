#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MsrcpWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestMsrcpWidgetSignals : public MsrcpWidget
{
  Q_OBJECT

public:
  TestMsrcpWidgetSignals();
  ~TestMsrcpWidgetSignals();

private slots:

  void test_smallScaleChange();
  void test_midScaleChange();
  void test_largeScaleChange();
  void test_reset();

};

TestMsrcpWidgetSignals::TestMsrcpWidgetSignals()
  : MsrcpWidget()
{

}

TestMsrcpWidgetSignals::~TestMsrcpWidgetSignals()
{

}

void TestMsrcpWidgetSignals::test_smallScaleChange()
{
  QSignalSpy spy_smallScaleChange(this, &MsrcpWidget::smallScaleChange);

  mSmallScale->setValue(5.);

  QCOMPARE(spy_smallScaleChange.count(), 1);

  QList<QVariant> args = spy_smallScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.);

  this->setSmallScale(10.);
  QCOMPARE(spy_smallScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_midScaleChange()
{
  QSignalSpy spy_midScaleChange(this, &MsrcpWidget::midScaleChange);

  mMidScale->setValue(150.);

  QCOMPARE(spy_midScaleChange.count(), 1);

  QList<QVariant> args = spy_midScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 150.);

  this->setMidScale(100.);
  QCOMPARE(spy_midScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_largeScaleChange()
{
  QSignalSpy spy_largeScaleChange(this, &MsrcpWidget::largeScaleChange);

  mLargeScale->setValue(225.);

  QCOMPARE(spy_largeScaleChange.count(), 1);

  QList<QVariant> args = spy_largeScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 225.);

  this->setLargeScale(250.);
  QCOMPARE(spy_largeScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_reset()
{
  QSignalSpy spy_smallScaleChange(this, &MsrcpWidget::smallScaleChange);
  QSignalSpy spy_midScaleChange(this, &MsrcpWidget::midScaleChange);
  QSignalSpy spy_largeScaleChange(this, &MsrcpWidget::largeScaleChange);

  this->setSmallScale(15.);
  this->setMidScale(100.);
  this->setLargeScale(250.);

  this->reset();

  QCOMPARE(spy_smallScaleChange.count(), 0);
  QCOMPARE(spy_midScaleChange.count(), 0);
  QCOMPARE(spy_largeScaleChange.count(), 0);
}


QTEST_MAIN(TestMsrcpWidgetSignals)

#include "tst_msrcpwidgetsignals.moc"
