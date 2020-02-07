#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/LucidWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestLucidWidgetSignals : public LucidWidgetImp
{
  Q_OBJECT

public:

  TestLucidWidgetSignals();
  ~TestLucidWidgetSignals();

private slots:

  void test_lucidKernelChange();
  void test_blurKernelChange();

};

TestLucidWidgetSignals::TestLucidWidgetSignals()
  : LucidWidgetImp()
{

}

TestLucidWidgetSignals::~TestLucidWidgetSignals()
{

}

void TestLucidWidgetSignals::test_lucidKernelChange()
{
  QSignalSpy spy_lucidKernelChange(this, &LucidWidgetImp::lucidKernelChange);

  this->mLucidKernel->setValue(3);

  QCOMPARE(spy_lucidKernelChange.count(), 1);

  QList<QVariant> args = spy_lucidKernelChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setLucidKernel(2);
  QCOMPARE(spy_lucidKernelChange.count(), 0);
}

void TestLucidWidgetSignals::test_blurKernelChange()
{
  QSignalSpy spy_blurKernelChange(this, &LucidWidgetImp::blurKernelChange);

  this->mBlurKernel->setValue(3);

  QCOMPARE(spy_blurKernelChange.count(), 1);

  QList<QVariant> args = spy_blurKernelChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setBlurKernel(2);
  QCOMPARE(spy_blurKernelChange.count(), 0);
}


QTEST_MAIN(TestLucidWidgetSignals)

#include "tst_lucidwidgetsignals.moc"
