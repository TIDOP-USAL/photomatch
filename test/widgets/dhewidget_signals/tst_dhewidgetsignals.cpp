#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DheWidget.h"

#include <QSpinBox>
#include <QRadioButton>

using namespace photomatch;

class TestDheWidgetSignals : public DheWidgetImp
{
  Q_OBJECT

public:

  TestDheWidgetSignals();
  ~TestDheWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_histogramDivisionsChange();

};

TestDheWidgetSignals::TestDheWidgetSignals()
  : DheWidgetImp()
{

}

TestDheWidgetSignals::~TestDheWidgetSignals()
{

}

void TestDheWidgetSignals::initTestCase()
{

}

void TestDheWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_XChange(this, &DheWidgetImp::xChange);

  this->setX(5);

  this->reset();

  QCOMPARE(spy_XChange.count(), 0);
}

void TestDheWidgetSignals::test_histogramDivisionsChange()
{
  QSignalSpy spy_xChange(this, &DheWidgetImp::xChange);

  mX->setValue(3);

  QCOMPARE(spy_xChange.count(), 1);

  QList<QVariant> args = spy_xChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 3);

  this->setX(2);
  QCOMPARE(spy_xChange.count(), 0);
}



QTEST_MAIN(TestDheWidgetSignals)

#include "tst_dhewidgetsignals.moc"
