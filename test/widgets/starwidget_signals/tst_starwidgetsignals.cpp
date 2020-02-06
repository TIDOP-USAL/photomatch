#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/StarWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestStarWidgetSignals : public StarWidgetImp
{
  Q_OBJECT

public:

  TestStarWidgetSignals();
  ~TestStarWidgetSignals();

private slots:

  void test_maxSizeChange();
  void test_responseThresholdChange();
  void test_lineThresholdProjectedChange();
  void test_lineThresholdBinarizedChange();
  void test_suppressNonmaxSizeChange();

};

TestStarWidgetSignals::TestStarWidgetSignals()
  : StarWidgetImp()
{

}

TestStarWidgetSignals::~TestStarWidgetSignals()
{

}

void TestStarWidgetSignals::test_maxSizeChange()
{
  QSignalSpy spy_maxSizeChange(this, &StarWidgetImp::maxSizeChange);

  this->mMaxSize->setValue(50);

  QCOMPARE(spy_maxSizeChange.count(), 1);

  QList<QVariant> args = spy_maxSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setMaxSize(25);
  QCOMPARE(spy_maxSizeChange.count(), 0);
}

void TestStarWidgetSignals::test_responseThresholdChange()
{
  QSignalSpy spy_responseThresholdChange(this, &StarWidgetImp::responseThresholdChange);

  this->mResponseThreshold->setValue(50);

  QCOMPARE(spy_responseThresholdChange.count(), 1);

  QList<QVariant> args = spy_responseThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setResponseThreshold(25);
  QCOMPARE(spy_responseThresholdChange.count(), 0);
}

void TestStarWidgetSignals::test_lineThresholdProjectedChange()
{
  QSignalSpy spy_lineThresholdProjectedChange(this, &StarWidgetImp::lineThresholdProjectedChange);

  this->mLineThresholdProjected->setValue(50);

  QCOMPARE(spy_lineThresholdProjectedChange.count(), 1);

  QList<QVariant> args = spy_lineThresholdProjectedChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setLineThresholdProjected(25);
  QCOMPARE(spy_lineThresholdProjectedChange.count(), 0);
}

void TestStarWidgetSignals::test_lineThresholdBinarizedChange()
{
  QSignalSpy spy_lineThresholdBinarizedChange(this, &StarWidgetImp::lineThresholdBinarizedChange);

  this->mLineThresholdBinarized->setValue(50);

  QCOMPARE(spy_lineThresholdBinarizedChange.count(), 1);

  QList<QVariant> args = spy_lineThresholdBinarizedChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setLineThresholdBinarized(25);
  QCOMPARE(spy_lineThresholdBinarizedChange.count(), 0);
}

void TestStarWidgetSignals::test_suppressNonmaxSizeChange()
{
  QSignalSpy spy_suppressNonmaxSizeChange(this, &StarWidgetImp::suppressNonmaxSizeChange);

  this->mSuppressNonmaxSize->setValue(50);

  QCOMPARE(spy_suppressNonmaxSizeChange.count(), 1);

  QList<QVariant> args = spy_suppressNonmaxSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setSuppressNonmaxSize(25);
  QCOMPARE(spy_suppressNonmaxSizeChange.count(), 0);
}

QTEST_MAIN(TestStarWidgetSignals)

#include "tst_starwidgetsignals.moc"
