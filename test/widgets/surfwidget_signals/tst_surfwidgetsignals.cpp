#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/SurfWidget.h"

#include <QSpinBox>
#include <QCheckBox>

using namespace photomatch;

class TestSurfWidgetSignals : public SurfWidgetImp
{
  Q_OBJECT

public:

  TestSurfWidgetSignals();
  ~TestSurfWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_hessianThresholdChange();
  void test_octavesChange();
  void test_octaveLayersChange();
  void test_extendedDescriptorChange();
  void test_uprightChange();
};

TestSurfWidgetSignals::TestSurfWidgetSignals()
  : SurfWidgetImp()
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
  QSignalSpy spyHessianThresholdChange(this, &SurfWidgetImp::hessianThresholdChange);
  QSignalSpy spyOctavesChange(this, &SurfWidgetImp::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &SurfWidgetImp::octaveLayersChange);
  QSignalSpy spyExtendedDescriptorChange(this, &SurfWidgetImp::extendedDescriptorChange);
  QSignalSpy spyRotatedFeaturesChange(this, &SurfWidgetImp::uprightChange);

  this->setHessianThreshold(120);
  this->setOctaves(6);
  this->setOctaveLayers(6);
  this->setExtendedDescriptor(true);
  this->seUpright(true);

  this->reset();

  QCOMPARE(spyHessianThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
  QCOMPARE(spyRotatedFeaturesChange.count(), 0);
}

void TestSurfWidgetSignals::test_hessianThresholdChange()
{
  QSignalSpy spyHessianThresholdChange(this, &SurfWidgetImp::hessianThresholdChange);

  mHessianThreshold->setValue(150);

  QCOMPARE(spyHessianThresholdChange.count(), 1);

  QList<QVariant> args = spyHessianThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 150);

  this->setHessianThreshold(120);
  QCOMPARE(spyHessianThresholdChange.count(), 0);
}

void TestSurfWidgetSignals::test_octavesChange()
{
  QSignalSpy spyOctavesChange(this, &SurfWidgetImp::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestSurfWidgetSignals::test_octaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &SurfWidgetImp::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestSurfWidgetSignals::test_extendedDescriptorChange()
{
  QSignalSpy spyExtendedDescriptorChange(this, &SurfWidgetImp::extendedDescriptorChange);

  QTest::mouseClick(mExtendedDescriptor, Qt::MouseButton::LeftButton);

  QCOMPARE(spyExtendedDescriptorChange.count(), 1);

  QList<QVariant> args = spyExtendedDescriptorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setExtendedDescriptor(true);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
}

void TestSurfWidgetSignals::test_uprightChange()
{
  QSignalSpy spy_uprightChange(this, &SurfWidgetImp::uprightChange);

  QTest::mouseClick(mUpright, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_uprightChange.count(), 1);

  QList<QVariant> args = spy_uprightChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->seUpright(true);
  QCOMPARE(spy_uprightChange.count(), 0);
}

QTEST_MAIN(TestSurfWidgetSignals)

#include "tst_surfwidgetsignals.moc"
