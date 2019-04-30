#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/KazeWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace fme;

class TestKazeWidgetSignals : public KazeWidget
{
  Q_OBJECT

public:

  TestKazeWidgetSignals();
  ~TestKazeWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testThresholdChange();
  void testOctavesChange();
  void testOctaveLayersChange();
  void testExtendedDescriptorChange();
  void testUprightChange();
  void testDiffusivityChange();
  void testReset();
};

TestKazeWidgetSignals::TestKazeWidgetSignals()
  : KazeWidget()
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

}

void TestKazeWidgetSignals::testThresholdChange()
{
  QSignalSpy spyThresholdChange(this, &KazeWidget::thresholdChange);

  mThreshold->setValue(25.);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setThreshold(120);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestKazeWidgetSignals::testOctavesChange()
{
  QSignalSpy spyOctavesChange(this, &KazeWidget::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestKazeWidgetSignals::testOctaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &KazeWidget::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestKazeWidgetSignals::testExtendedDescriptorChange()
{
  QSignalSpy spyExtendedDescriptorChange(this, &KazeWidget::extendedDescriptorChange);

  QTest::mouseClick(mExtended, Qt::MouseButton::LeftButton);

  QCOMPARE(spyExtendedDescriptorChange.count(), 1);

  QList<QVariant> args = spyExtendedDescriptorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setExtendedDescriptor(true);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
}

void TestKazeWidgetSignals::testUprightChange()
{
  QSignalSpy spyUprightChange(this, &KazeWidget::uprightChange);

  QTest::mouseClick(mUpright, Qt::MouseButton::LeftButton);

  QCOMPARE(spyUprightChange.count(), 1);

  QList<QVariant> args = spyUprightChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUpright(true);
  QCOMPARE(spyUprightChange.count(), 0);
}

void TestKazeWidgetSignals::testDiffusivityChange()
{
  QSignalSpy spyDiffusivityChange(this, &KazeWidget::diffusivityChange);

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");

  QCOMPARE(spyDiffusivityChange.count(), 1);

  QList<QVariant> args = spyDiffusivityChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "DIFF_PM_G1");

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");
  QCOMPARE(spyDiffusivityChange.count(), 0);

  this->setDiffusivity("DIFF_WEICKERT");
  QCOMPARE(spyDiffusivityChange.count(), 0);
}

void TestKazeWidgetSignals::testReset()
{
  QSignalSpy spyThresholdChange(this, &KazeWidget::thresholdChange);
  QSignalSpy spyOctavesChange(this, &KazeWidget::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &KazeWidget::octaveLayersChange);
  QSignalSpy spyExtendedDescriptorChange(this, &KazeWidget::extendedDescriptorChange);
  QSignalSpy spyUprightChange(this, &KazeWidget::uprightChange);
  QSignalSpy spyDiffusivityChange(this, &KazeWidget::diffusivityChange);

  this->setThreshold(120);
  this->setOctaves(6);
  this->setOctaveLayers(6);
  this->setExtendedDescriptor(true);
  this->setUpright(true);
  this->setDiffusivity("DIFF_WEICKERT");

  this->reset();

  QCOMPARE(spyThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
  QCOMPARE(spyExtendedDescriptorChange.count(), 0);
  QCOMPARE(spyUprightChange.count(), 0);
  QCOMPARE(spyDiffusivityChange.count(), 0);
}

QTEST_MAIN(TestKazeWidgetSignals)

#include "tst_kazewidgetsignals.moc"
