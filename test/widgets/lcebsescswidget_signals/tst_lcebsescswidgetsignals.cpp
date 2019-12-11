#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/LceBsescsWidget.h"

#include <QSpinBox>

using namespace photomatch;


class TestLceBsescsWidgetSignals : public LceBsescsWidget
{
  Q_OBJECT

public:
  TestLceBsescsWidgetSignals();
  ~TestLceBsescsWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_blockSizeChange();
  void test_reset();

};

TestLceBsescsWidgetSignals::TestLceBsescsWidgetSignals()
  : LceBsescsWidget()
{

}

TestLceBsescsWidgetSignals::~TestLceBsescsWidgetSignals()
{

}

void TestLceBsescsWidgetSignals::initTestCase()
{

}

void TestLceBsescsWidgetSignals::cleanupTestCase()
{

}

void TestLceBsescsWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &LceBsescsWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 33));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestLceBsescsWidgetSignals::test_reset()
{
  QSignalSpy spy_blockSizeChange(this, &LceBsescsWidget::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestLceBsescsWidgetSignals)

#include "tst_lcebsescswidgetsignals.moc"
