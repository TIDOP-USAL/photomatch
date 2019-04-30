#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/SurfWidget.h"

#include <QSpinBox>
#include <QCheckBox>

using namespace fme;

class TestSurfWidgetSignals : public SurfWidget
{
  Q_OBJECT

public:

  TestSurfWidgetSignals();
  ~TestSurfWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testHessianThresholdChange();
  void testOctavesChange();
  void testOctaveLayersChange();
  void testExtendedDescriptorChange();
  void testRotatedFeaturesChange();
  void testReset();
};

TestSurfWidgetSignals::TestSurfWidgetSignals()
  : SurfWidget()
{

}

TestSurfWidgetSignals::~TestSurfWidgetSignals()
{

}

void TestSurfWidgetSignals::initTestCase()
{
}

void TestSurfWidgetSignals::cleanupTestCase()
{

}

void TestSurfWidgetSignals::testHessianThresholdChange()
{
  QSignalSpy spyHessianThresholdChange(this, &SurfWidget::hessianThresholdChange);

  mHessianThreshold->setValue(150);

  QCOMPARE(spyHessianThresholdChange.count(), 1);

  QList<QVariant> args = spyHessianThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 150);

  this->setHessianThreshold(120);
  QCOMPARE(spyHessianThresholdChange.count(), 0);
}

void TestSurfWidgetSignals::testOctavesChange()
{
  QSignalSpy spyOctavesChange(this, &SurfWidget::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestSurfWidgetSignals::testOctaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &SurfWidget::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestSurfWidgetSignals::testExtendedDescriptorChange()
{
  QSignalSpy spyExtendedDescriptorChange(this, &SurfWidget::extendedDescriptorChange);

  QTest::mouseClick(mExtendedDescriptor, Qt::MouseButton::LeftButton);

  QCOMPARE(spyExtendedDescriptorChange.count(), 1);

  QList<QVariant> args = spyExtendedDescriptorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setExtendedDescriptor(true);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
}

void TestSurfWidgetSignals::testRotatedFeaturesChange()
{
  QSignalSpy spyRotatedFeaturesChange(this, &SurfWidget::rotatedFeaturesChange);

  QTest::mouseClick(mRotatedFeatures, Qt::MouseButton::LeftButton);

  QCOMPARE(spyRotatedFeaturesChange.count(), 1);

  QList<QVariant> args = spyRotatedFeaturesChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setRotatedFeatures(true);
  QCOMPARE(spyRotatedFeaturesChange.count(), 0);
}

void TestSurfWidgetSignals::testReset()
{
  QSignalSpy spyHessianThresholdChange(this, &SurfWidget::hessianThresholdChange);
  QSignalSpy spyOctavesChange(this, &SurfWidget::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &SurfWidget::octaveLayersChange);
  QSignalSpy spyExtendedDescriptorChange(this, &SurfWidget::extendedDescriptorChange);
  QSignalSpy spyRotatedFeaturesChange(this, &SurfWidget::rotatedFeaturesChange);

  this->setHessianThreshold(120);
  this->setOctaves(6);
  this->setOctaveLayers(6);
  this->setExtendedDescriptor(true);
  this->setRotatedFeatures(true);

  this->reset();

  QCOMPARE(spyHessianThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
  QCOMPARE(spyRotatedFeaturesChange.count(), 0);
}

QTEST_MAIN(TestSurfWidgetSignals)

#include "tst_surfwidgetsignals.moc"
