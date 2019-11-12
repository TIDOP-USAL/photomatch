#include <QtTest>

#include "photomatch/widgets/BoostWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>

using namespace photomatch;

class TestBoostWidgetsSignals : public BoostWidget
{
  Q_OBJECT

public:

  TestBoostWidgetsSignals();
  ~TestBoostWidgetsSignals();

private slots:

  void test_descriptorTypeChange();
  void test_scaleFactorChange();
  void test_useOrientationChange();
  void test_reset();

};

TestBoostWidgetsSignals::TestBoostWidgetsSignals()
  : BoostWidget()
{

}

TestBoostWidgetsSignals::~TestBoostWidgetsSignals()
{

}

void TestBoostWidgetsSignals::test_descriptorTypeChange()
{
  QSignalSpy spy_descriptorTypeChange(this, &BoostWidget::descriptorTypeChange);

  this->mDescriptorType->setCurrentText("BGM");

  QCOMPARE(spy_descriptorTypeChange.count(), 1);

  QList<QVariant> args = spy_descriptorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "BGM");

  this->mDescriptorType->setCurrentText("BGM");
  QCOMPARE(spy_descriptorTypeChange.count(), 0);

  this->setDescriptorType("BINBOOST_64");
  QCOMPARE(spy_descriptorTypeChange.count(), 0);
}

void TestBoostWidgetsSignals::test_scaleFactorChange()
{
  QSignalSpy spy_scaleFactorChange(this, &BoostWidget::scaleFactorChange);

  mScaleFactor->setValue(5.00);

  QCOMPARE(spy_scaleFactorChange.count(), 1);

  QList<QVariant> args = spy_scaleFactorChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.00);

  this->setScaleFactor(1.50);
  QCOMPARE(spy_scaleFactorChange.count(), 0);
}

void TestBoostWidgetsSignals::test_useOrientationChange()
{
  QSignalSpy spy_useOrientationChange(this, &BoostWidget::useOrientationChange);

  QTest::mouseClick(mUseOrientation, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useOrientationChange.count(), 1);

  QList<QVariant> args = spy_useOrientationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setUseOrientation(true);
  QCOMPARE(spy_useOrientationChange.count(), 0);
}

void TestBoostWidgetsSignals::test_reset()
{
  QSignalSpy spy_useOrientationChange(this, &BoostWidget::useOrientationChange);

  this->setUseOrientation(true);

  this->reset();

  QCOMPARE(spy_useOrientationChange.count(), 0);
}

QTEST_MAIN(TestBoostWidgetsSignals)

#include "tst_boostwidgetssignals.moc"
