#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/DheWidget.h"

#include <QSpinBox>
#include <QRadioButton>

using namespace fme;

class TestDheWidgetSignals : public DheWidget
{
  Q_OBJECT

public:

  TestDheWidgetSignals();
  ~TestDheWidgetSignals();

private slots:

  void test_histogramDivisionsChange();
  void test_reset();

};

TestDheWidgetSignals::TestDheWidgetSignals()
  : DheWidget()
{

}

TestDheWidgetSignals::~TestDheWidgetSignals()
{

}

void TestDheWidgetSignals::test_histogramDivisionsChange()
{
  QSignalSpy spy_xChange(this, &DheWidget::xChange);

  mX->setValue(3);

  QCOMPARE(spy_xChange.count(), 1);

  QList<QVariant> args = spy_xChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setX(2);
  QCOMPARE(spy_xChange.count(), 0);
}

void TestDheWidgetSignals::test_reset()
{
  QSignalSpy spy_XChange(this, &DheWidget::xChange);

  this->setX(5);

  this->reset();

  QCOMPARE(spy_XChange.count(), 0);
}

QTEST_MAIN(TestDheWidgetSignals)

#include "tst_dhewidgetsignals.moc"
