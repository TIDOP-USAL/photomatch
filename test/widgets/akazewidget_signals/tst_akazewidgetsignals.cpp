#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/AkazeWidget.h"

#include <QSpinBox>
#include <QComboBox>

using namespace fme;

class TestAkazeWidgetSignals : public AkazeWidget
{
  Q_OBJECT

public:

  TestAkazeWidgetSignals();
  ~TestAkazeWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDescriptorTypeChange();
  void testDescriptorSizeChange();
  void testDescriptorChannelsChange();
  void testThresholdChange();
  void testOctavesChange();
  void testOctaveLayersChange();
  void testDiffusivityChange();
  void testReset();
};

TestAkazeWidgetSignals::TestAkazeWidgetSignals()
  : AkazeWidget()
{

}

TestAkazeWidgetSignals::~TestAkazeWidgetSignals()
{

}

void TestAkazeWidgetSignals::initTestCase()
{
}

void TestAkazeWidgetSignals::cleanupTestCase()
{

}

void TestAkazeWidgetSignals::testDescriptorTypeChange()
{
  QSignalSpy spyDescriptorTypeChange(this, &AkazeWidget::descriptorTypeChange);

  this->mDescriptorType->setCurrentText("KAZE");

  QCOMPARE(spyDescriptorTypeChange.count(), 1);

  QList<QVariant> args = spyDescriptorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "KAZE");

  this->mDescriptorType->setCurrentText("KAZE");
  QCOMPARE(spyDescriptorTypeChange.count(), 0);

  this->setDescriptorType("KAZE_UPRIGHT");
  QCOMPARE(spyDescriptorTypeChange.count(), 0);
}

void TestAkazeWidgetSignals::testDescriptorSizeChange()
{
  QSignalSpy spyDescriptorSizeChange(this, &AkazeWidget::descriptorSizeChange);

  mDescriptorSize->setValue(64);

  QCOMPARE(spyDescriptorSizeChange.count(), 1);

  QList<QVariant> args = spyDescriptorSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 64);

  this->setDescriptorSize(32);
  QCOMPARE(spyDescriptorSizeChange.count(), 0);
}

void TestAkazeWidgetSignals::testDescriptorChannelsChange()
{
  QSignalSpy spyDescriptorChannelsChange(this, &AkazeWidget::descriptorChannelsChange);

  mDescriptorChannels->setValue(1);

  QCOMPARE(spyDescriptorChannelsChange.count(), 1);

  QList<QVariant> args = spyDescriptorChannelsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 1);

  this->setDescriptorChannels(2);
  QCOMPARE(spyDescriptorChannelsChange.count(), 0);
}

void TestAkazeWidgetSignals::testThresholdChange()
{
  QSignalSpy spyThresholdChange(this, &AkazeWidget::thresholdChange);

  mThreshold->setValue(25.);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setThreshold(120);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestAkazeWidgetSignals::testOctavesChange()
{
  QSignalSpy spyOctavesChange(this, &AkazeWidget::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestAkazeWidgetSignals::testOctaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &AkazeWidget::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestAkazeWidgetSignals::testDiffusivityChange()
{
  QSignalSpy spyDiffusivityChange(this, &AkazeWidget::diffusivityChange);

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");

  QCOMPARE(spyDiffusivityChange.count(), 1);

  QList<QVariant> args = spyDiffusivityChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "DIFF_PM_G1");

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");
  QCOMPARE(spyDiffusivityChange.count(), 0);

  this->setDiffusivity("DIFF_WEICKERT");
  QCOMPARE(spyDiffusivityChange.count(), 0);
}

void TestAkazeWidgetSignals::testReset()
{
  QSignalSpy spyDescriptorTypeChange(this, &AkazeWidget::descriptorTypeChange);
  QSignalSpy spyDescriptorSizeChange(this, &AkazeWidget::descriptorSizeChange);
  QSignalSpy spyDescriptorChannelsChange(this, &AkazeWidget::descriptorChannelsChange);
  QSignalSpy spyThresholdChange(this, &AkazeWidget::thresholdChange);
  QSignalSpy spyOctavesChange(this, &AkazeWidget::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &AkazeWidget::octaveLayersChange);
  QSignalSpy spyDiffusivityChange(this, &AkazeWidget::diffusivityChange);

  this->setDescriptorType("KAZE_UPRIGHT");
  this->setDescriptorSize(32);
  this->setDescriptorChannels(2);
  this->setThreshold(120);
  this->setOctaves(6);
  this->setOctaveLayers(6);
  this->setDiffusivity("DIFF_WEICKERT");

  this->reset();

  QCOMPARE(spyDescriptorTypeChange.count(), 0);
  QCOMPARE(spyDescriptorSizeChange.count(), 0);
  QCOMPARE(spyDescriptorChannelsChange.count(), 0);
  QCOMPARE(spyThresholdChange.count(), 0);
  QCOMPARE(spyOctavesChange.count(), 0);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
  QCOMPARE(spyDiffusivityChange.count(), 0);
}

QTEST_MAIN(TestAkazeWidgetSignals)

#include "tst_akazewidgetsignals.moc"
