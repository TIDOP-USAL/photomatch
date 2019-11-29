#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/KeypointsFilterWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestKeypointsFilterWidgetSignals : public KeypointsFilterWidget
{
  Q_OBJECT

public:

  TestKeypointsFilterWidgetSignals();
  ~TestKeypointsFilterWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testReset();
};

TestKeypointsFilterWidgetSignals::TestKeypointsFilterWidgetSignals()
  : KeypointsFilterWidget()
{

}

TestKeypointsFilterWidgetSignals::~TestKeypointsFilterWidgetSignals()
{

}

void TestKeypointsFilterWidgetSignals::initTestCase()
{

}

void TestKeypointsFilterWidgetSignals::cleanupTestCase()
{

}

void TestKeypointsFilterWidgetSignals::testReset()
{

}


QTEST_MAIN(TestKeypointsFilterWidgetSignals)

#include "tst_keypointsfilterwidgetsignals.moc"
