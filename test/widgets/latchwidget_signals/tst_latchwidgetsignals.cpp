#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/LatchWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestLatchWidgetSignals : public LatchWidget
{
  Q_OBJECT

public:
  TestLatchWidgetSignals();
  ~TestLatchWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_bytesChange();
  void test_rotationInvarianceChange();
  void test_halfSsdSizeChange();
  void test_reset();

};

TestLatchWidgetSignals::TestLatchWidgetSignals()
  : LatchWidget()
{

}

TestLatchWidgetSignals::~TestLatchWidgetSignals()
{

}

void TestLatchWidgetSignals::initTestCase()
{

}

void TestLatchWidgetSignals::cleanupTestCase()
{

}

void TestLatchWidgetSignals::test_bytesChange()
{
  QSignalSpy spy_bytesChange(this, &LatchWidget::bytesChange);

  this->mBytes->setCurrentText("4");

  QCOMPARE(spy_bytesChange.count(), 1);

  QList<QVariant> args = spy_bytesChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "4");

  this->mBytes->setCurrentText("4");
  QCOMPARE(spy_bytesChange.count(), 0);

  this->setBytes("8");
  QCOMPARE(spy_bytesChange.count(), 0);
}

void TestLatchWidgetSignals::test_rotationInvarianceChange()
{
  QSignalSpy spy_rotationInvarianceChange(this, &LatchWidget::rotationInvarianceChange);

  QTest::mouseClick(mRotationInvariance, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_rotationInvarianceChange.count(), 1);

  QList<QVariant> args = spy_rotationInvarianceChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setRotationInvariance(false);
  QCOMPARE(spy_rotationInvarianceChange.count(), 0);
}

void TestLatchWidgetSignals::test_halfSsdSizeChange()
{
  QSignalSpy spy_halfSsdSizeChange(this, &LatchWidget::halfSsdSizeChange);

  this->mHalfSsdSize->setValue(7);

  QCOMPARE(spy_halfSsdSizeChange.count(), 1);

  QList<QVariant> args = spy_halfSsdSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 7);

  this->setHalfSsdSize(5);
  QCOMPARE(spy_halfSsdSizeChange.count(), 0);
}

void TestLatchWidgetSignals::test_reset()
{

}

QTEST_MAIN(TestLatchWidgetSignals)

#include "tst_latchwidgetsignals.moc"
