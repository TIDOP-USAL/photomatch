#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/NoshpWidget.h"

#include <QSpinBox>

using namespace photomatch;


class TestNoshpWidgetSignals : public NoshpWidgetImp
{
  Q_OBJECT

public:
  TestNoshpWidgetSignals();
  ~TestNoshpWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_blockSizeChange();

};

TestNoshpWidgetSignals::TestNoshpWidgetSignals()
  : NoshpWidgetImp()
{

}

TestNoshpWidgetSignals::~TestNoshpWidgetSignals()
{

}

void TestNoshpWidgetSignals::initTestCase()
{

}

void TestNoshpWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_blockSizeChange(this, &NoshpWidgetImp::blockSizeChange);

  this->setBlockSize(QSize(5, 7));

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestNoshpWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &NoshpWidgetImp::blockSizeChange);

  this->mBlockSizeX->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 127));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

QTEST_MAIN(TestNoshpWidgetSignals)

#include "tst_noshpwidgetsignals.moc"
