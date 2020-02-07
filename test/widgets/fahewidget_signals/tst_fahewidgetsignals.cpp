#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/FaheWidget.h"

#include <QSpinBox>

using namespace photomatch;


class TestFaheWidgetSignals : public FaheWidgetImp
{
  Q_OBJECT

public:
  TestFaheWidgetSignals();
  ~TestFaheWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_blockSizeChange();

};

TestFaheWidgetSignals::TestFaheWidgetSignals()
  : FaheWidgetImp()
{

}

TestFaheWidgetSignals::~TestFaheWidgetSignals()
{

}

void TestFaheWidgetSignals::initTestCase()
{

}

void TestFaheWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_blockSizeChange(this, &FaheWidgetImp::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestFaheWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &FaheWidgetImp::blockSizeChange);

  this->mBlockSizeX->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 11));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}


QTEST_MAIN(TestFaheWidgetSignals)

#include "tst_fahewidgetsignals.moc"
