#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/AcebsfWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestAcebsfWidgetSignals : public AcebsfWidget
{
  Q_OBJECT

public:
  TestAcebsfWidgetSignals();
  ~TestAcebsfWidgetSignals();

private slots:

  void test_blockSizeChange();
  void test_lChange();
  void test_k1Change();
  void test_k2Change();
  void test_reset();
};

TestAcebsfWidgetSignals::TestAcebsfWidgetSignals()
  : AcebsfWidget()
{

}

TestAcebsfWidgetSignals::~TestAcebsfWidgetSignals()
{

}

void TestAcebsfWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spy_blockSizeChange(this, &AcebsfWidget::blockSizeChange);

  this->mBlockSizeX->setValue(10);
  //this->mTilesGridY->setValue(10);

  QCOMPARE(spy_blockSizeChange.count(), 1);

  QList<QVariant> args = spy_blockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toSize(), QSize(10, 8));

  this->setBlockSize(QSize(5, 7));
  QCOMPARE(spy_blockSizeChange.count(), 0);
}

void TestAcebsfWidgetSignals::test_lChange()
{
  QSignalSpy spy_lChange(this, &AcebsfWidget::lChange);

  mL->setValue(0.25);

  QCOMPARE(spy_lChange.count(), 1);

  QList<QVariant> args = spy_lChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.25);

  this->setL(0.5);
  QCOMPARE(spy_lChange.count(), 0);
}

void TestAcebsfWidgetSignals::test_k1Change()
{
  QSignalSpy spy_k1Change(this, &AcebsfWidget::k1Change);

  mK1->setValue(20.);

  QCOMPARE(spy_k1Change.count(), 1);

  QList<QVariant> args = spy_k1Change.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20.);

  this->setK1(15.);
  QCOMPARE(spy_k1Change.count(), 0);
}

void TestAcebsfWidgetSignals::test_k2Change()
{
  QSignalSpy spy_k2Change(this, &AcebsfWidget::k2Change);

  mK2->setValue(0.2);

  QCOMPARE(spy_k2Change.count(), 1);

  QList<QVariant> args = spy_k2Change.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.2);

  this->setK2(0.6);
  QCOMPARE(spy_k2Change.count(), 0);
}

void TestAcebsfWidgetSignals::test_reset()
{
  QSignalSpy spy_blockSizeChange(this, &AcebsfWidget::blockSizeChange);
  QSignalSpy spy_k1Change(this, &AcebsfWidget::k1Change);
  QSignalSpy spy_k2Change(this, &AcebsfWidget::k2Change);

  this->setBlockSize(QSize(5, 7));
  this->setK1(15.);
  this->setK2(0.6);

  this->reset();

  QCOMPARE(spy_blockSizeChange.count(), 0);
  QCOMPARE(spy_k1Change.count(), 0);
  QCOMPARE(spy_k2Change.count(), 0);
}


QTEST_MAIN(TestAcebsfWidgetSignals)

#include "tst_acebsfwidgetsignals.moc"
