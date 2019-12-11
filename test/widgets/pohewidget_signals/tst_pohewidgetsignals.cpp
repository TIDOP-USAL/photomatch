#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/PoheWidget.h"

#include <QSpinBox>

using namespace photomatch;


class TestPoheWidgetSignals : public PoheWidget
{
  Q_OBJECT

public:
  TestPoheWidgetSignals();
  ~TestPoheWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_blockSizeChange();
  void test_reset();

};

TestPoheWidgetSignals::TestPoheWidgetSignals()
  : PoheWidget()
{

}

TestPoheWidgetSignals::~TestPoheWidgetSignals()
{

}

void TestPoheWidgetSignals::initTestCase()
{

}

void TestPoheWidgetSignals::cleanupTestCase()
{

}

void TestPoheWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &PoheWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 127));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestPoheWidgetSignals::test_reset()
{
  QSignalSpy spy_blockSizeChange(this, &PoheWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestPoheWidgetSignals)

#include "tst_pohewidgetsignals.moc"
