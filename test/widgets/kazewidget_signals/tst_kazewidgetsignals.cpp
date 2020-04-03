#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/KazeWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestKazeWidgetSignals : public KazeWidgetImp
{
  Q_OBJECT

public:

  TestKazeWidgetSignals();
  ~TestKazeWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_thresholdChange();
  void test_octavesChange();
  void test_octaveLayersChange();
  void test_extendedDescriptorChange();
  void test_uprightChange();
  void test_diffusivityChange();
};

TestKazeWidgetSignals::TestKazeWidgetSignals()
  : KazeWidgetImp()
{

}

TestKazeWidgetSignals::~TestKazeWidgetSignals()
{

}

void TestKazeWidgetSignals::initTestCase()
{
}

void TestKazeWidgetSignals::cleanupTestCase()
{
  QSignalSpy spyThresholdChange(this, &KazeWidgetImp::thresholdChange);
  QSignalSpy spyOctavesChange(this, &KazeWidgetImp::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &KazeWidgetImp::octaveLayersChange);
  QSignalSpy spyExtendedDescriptorChange(this, &KazeWidgetImp::extendedDescriptorChange);
  QSignalSpy spyUprightChange(this, &KazeWidgetImp::uprightDescriptorChange);
  QSignalSpy spyDiffusivityChange(this, &KazeWidgetImp::diffusivityChange);

  this->setThreshold(120);
  this->setOctaves(6);
  this->setOctaveLayers(6);
  this->setExtendedDescriptor(true);
  this->setUprightDescriptor(true);
  this->setDiffusivity("DIFF_WEICKERT");

  this->reset();

  QCOMPARE(spyThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
  QCOMPARE(spyUprightChange.count(), 0);
  QCOMPARE(spyDiffusivityChange.count(), 0);
}

void TestKazeWidgetSignals::test_thresholdChange()
{
  QSignalSpy spyThresholdChange(this, &KazeWidgetImp::thresholdChange);

  mThreshold->setValue(25.);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setThreshold(120);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestKazeWidgetSignals::test_octavesChange()
{
  QSignalSpy spyOctavesChange(this, &KazeWidgetImp::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestKazeWidgetSignals::test_octaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &KazeWidgetImp::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestKazeWidgetSignals::test_extendedDescriptorChange()
{
  QSignalSpy spyExtendedDescriptorChange(this, &KazeWidgetImp::extendedDescriptorChange);

  QTest::mouseClick(mExtended, Qt::MouseButton::LeftButton);

  QCOMPARE(spyExtendedDescriptorChange.count(), 1);

  QList<QVariant> args = spyExtendedDescriptorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setExtendedDescriptor(true);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
}

void TestKazeWidgetSignals::test_uprightChange()
{
  QSignalSpy spyUprightChange(this, &KazeWidgetImp::uprightDescriptorChange);

  QTest::mouseClick(mUpright, Qt::MouseButton::LeftButton);

  QCOMPARE(spyUprightChange.count(), 1);

  QList<QVariant> args = spyUprightChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUprightDescriptor(true);
  QCOMPARE(spyUprightChange.count(), 0);
}

void TestKazeWidgetSignals::test_diffusivityChange()
{
  QSignalSpy spyDiffusivityChange(this, &KazeWidgetImp::diffusivityChange);

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");

  QCOMPARE(spyDiffusivityChange.count(), 1);

  QList<QVariant> args = spyDiffusivityChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "DIFF_PM_G1");

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");
  QCOMPARE(spyDiffusivityChange.count(), 0);

  this->setDiffusivity("DIFF_WEICKERT");
  QCOMPARE(spyDiffusivityChange.count(), 0);
}


QTEST_MAIN(TestKazeWidgetSignals)

#include "tst_kazewidgetsignals.moc"
