#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MsrcpWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestMsrcpWidgetSignals : public MsrcpWidgetImp
{
  Q_OBJECT

public:
  TestMsrcpWidgetSignals();
  ~TestMsrcpWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_smallScaleChange();
  void test_midScaleChange();
  void test_largeScaleChange();

};

TestMsrcpWidgetSignals::TestMsrcpWidgetSignals()
  : MsrcpWidgetImp()
{

}

TestMsrcpWidgetSignals::~TestMsrcpWidgetSignals()
{

}

void TestMsrcpWidgetSignals::cleanupTestCase()
{

}

void TestMsrcpWidgetSignals::initTestCase()
{
  QSignalSpy spy_smallScaleChange(this, &MsrcpWidgetImp::smallScaleChange);
  QSignalSpy spy_midScaleChange(this, &MsrcpWidgetImp::midScaleChange);
  QSignalSpy spy_largeScaleChange(this, &MsrcpWidgetImp::largeScaleChange);

  this->setSmallScale(15.);
  this->setMidScale(100.);
  this->setLargeScale(250.);

  this->reset();

  QCOMPARE(spy_smallScaleChange.count(), 0);
  QCOMPARE(spy_midScaleChange.count(), 0);
  QCOMPARE(spy_largeScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_smallScaleChange()
{
  QSignalSpy spy_smallScaleChange(this, &MsrcpWidgetImp::smallScaleChange);

  mSmallScale->setValue(5.);

  QCOMPARE(spy_smallScaleChange.count(), 1);

  QList<QVariant> args = spy_smallScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.);

  this->setSmallScale(10.);
  QCOMPARE(spy_smallScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_midScaleChange()
{
  QSignalSpy spy_midScaleChange(this, &MsrcpWidgetImp::midScaleChange);

  mMidScale->setValue(150.);

  QCOMPARE(spy_midScaleChange.count(), 1);

  QList<QVariant> args = spy_midScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 150.);

  this->setMidScale(100.);
  QCOMPARE(spy_midScaleChange.count(), 0);
}

void TestMsrcpWidgetSignals::test_largeScaleChange()
{
  QSignalSpy spy_largeScaleChange(this, &MsrcpWidgetImp::largeScaleChange);

  mLargeScale->setValue(225.);

  QCOMPARE(spy_largeScaleChange.count(), 1);

  QList<QVariant> args = spy_largeScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 225.);

  this->setLargeScale(250.);
  QCOMPARE(spy_largeScaleChange.count(), 0);
}



QTEST_MAIN(TestMsrcpWidgetSignals)

#include "tst_msrcpwidgetsignals.moc"
