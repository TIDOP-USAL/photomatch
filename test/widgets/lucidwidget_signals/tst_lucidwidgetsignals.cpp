#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/LucidWidget.h"

#include <QSpinBox>

using namespace fme;

class TestLucidWidgetSignals : public LucidWidget
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
  : LucidWidget()
{

}

TestLucidWidgetSignals::~TestLucidWidgetSignals()
{

}

void TestLucidWidgetSignals::test_lucidKernelChange()
{
  QSignalSpy spy_lucidKernelChange(this, &LucidWidget::lucidKernelChange);

  this->mLucidKernel->setValue(3);

  QCOMPARE(spy_lucidKernelChange.count(), 1);

  QList<QVariant> args = spy_lucidKernelChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setLucidKernel(2);
  QCOMPARE(spy_lucidKernelChange.count(), 0);
}

void TestLucidWidgetSignals::test_blurKernelChange()
{
  QSignalSpy spy_blurKernelChange(this, &LucidWidget::blurKernelChange);

  this->mBlurKernel->setValue(3);

  QCOMPARE(spy_blurKernelChange.count(), 1);

  QList<QVariant> args = spy_blurKernelChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setBlurKernel(2);
  QCOMPARE(spy_blurKernelChange.count(), 0);
}


QTEST_MAIN(TestLucidWidgetSignals)

#include "tst_lucidwidgetsignals.moc"
