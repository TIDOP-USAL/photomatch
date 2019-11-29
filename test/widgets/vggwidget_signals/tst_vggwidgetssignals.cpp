#include <QtTest>

#include "photomatch/widgets/VggWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>

using namespace photomatch;

class TestVggWidgetsSignals : public VggWidget
{
  Q_OBJECT

public:

  TestVggWidgetsSignals();
  ~TestVggWidgetsSignals();

private slots:

  void test_descriptorTypeChange();
  void test_scaleFactorChange();
  void test_sigmaChange();
  void test_useNormalizeDescriptorChange();
  void test_useNormalizeImageChange();
  void test_useScaleOrientationChange();

};

TestVggWidgetsSignals::TestVggWidgetsSignals()
  : VggWidget()
{

}

TestVggWidgetsSignals::~TestVggWidgetsSignals()
{

}

void TestVggWidgetsSignals::test_descriptorTypeChange()
{
  QSignalSpy spy_descriptorTypeChange(this, &VggWidget::descriptorTypeChange);

  this->mDescriptorType->setCurrentText("VGG_80");

  QCOMPARE(spy_descriptorTypeChange.count(), 1);

  QList<QVariant> args = spy_descriptorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "VGG_80");

  this->mDescriptorType->setCurrentText("VGG_80");
  QCOMPARE(spy_descriptorTypeChange.count(), 0);

  this->setDescriptorType("VGG_48");
  QCOMPARE(spy_descriptorTypeChange.count(), 0);
}

void TestVggWidgetsSignals::test_scaleFactorChange()
{
  QSignalSpy spy_scaleFactorChange(this, &VggWidget::scaleFactorChange);

  mScaleFactor->setValue(5.00);

  QCOMPARE(spy_scaleFactorChange.count(), 1);

  QList<QVariant> args = spy_scaleFactorChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.00);

  this->setScaleFactor(1.50);
  QCOMPARE(spy_scaleFactorChange.count(), 0);
}

void TestVggWidgetsSignals::test_sigmaChange()
{
  QSignalSpy spy_sigmaChange(this, &VggWidget::sigmaChange);

  mSigma->setValue(1.6);

  QCOMPARE(spy_sigmaChange.count(), 1);

  QList<QVariant> args = spy_sigmaChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 1.6);

  this->setSigma(1.2);
  QCOMPARE(spy_sigmaChange.count(), 0);
}

void TestVggWidgetsSignals::test_useNormalizeDescriptorChange()
{
  QSignalSpy spy_useNormalizeDescriptorChange(this, &VggWidget::useNormalizeDescriptorChange);

  QTest::mouseClick(mUseNormalizeDescriptor, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useNormalizeDescriptorChange.count(), 1);

  QList<QVariant> args = spy_useNormalizeDescriptorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUseNormalizeDescriptor(false);
  QCOMPARE(spy_useNormalizeDescriptorChange.count(), 0);
}

void TestVggWidgetsSignals::test_useNormalizeImageChange()
{
  QSignalSpy spy_useNormalizeImageChange(this, &VggWidget::useNormalizeImageChange);

  QTest::mouseClick(mUseNormalizeImage, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useNormalizeImageChange.count(), 1);

  QList<QVariant> args = spy_useNormalizeImageChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setUseNormalizeImage(true);
  QCOMPARE(spy_useNormalizeImageChange.count(), 0);
}

void TestVggWidgetsSignals::test_useScaleOrientationChange()
{
  QSignalSpy spy_useScaleOrientationChange(this, &VggWidget::useScaleOrientationChange);

  QTest::mouseClick(mUseScaleOrientation, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useScaleOrientationChange.count(), 1);

  QList<QVariant> args = spy_useScaleOrientationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setUseScaleOrientation(true);
  QCOMPARE(spy_useScaleOrientationChange.count(), 0);
}

QTEST_MAIN(TestVggWidgetsSignals)

#include "tst_vggwidgetssignals.moc"
