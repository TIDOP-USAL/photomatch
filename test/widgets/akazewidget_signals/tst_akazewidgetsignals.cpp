#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/AkazeWidget.h"

#include <QSpinBox>
#include <QComboBox>

using namespace photomatch;

class TestAkazeWidgetSignals : public AkazeWidgetImp
{
  Q_OBJECT

public:

  TestAkazeWidgetSignals();
  ~TestAkazeWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_descriptorTypeChange();
  void test_descriptorSizeChange();
  void test_descriptorChannelsChange();
  void test_thresholdChange();
  void test_octavesChange();
  void test_octaveLayersChange();
  void test_diffusivityChange();

};

TestAkazeWidgetSignals::TestAkazeWidgetSignals()
  : AkazeWidgetImp()
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
  QSignalSpy spyDescriptorTypeChange(this, &AkazeWidgetImp::descriptorTypeChange);
  QSignalSpy spyDescriptorSizeChange(this, &AkazeWidgetImp::descriptorSizeChange);
  QSignalSpy spyDescriptorChannelsChange(this, &AkazeWidgetImp::descriptorChannelsChange);
  QSignalSpy spyThresholdChange(this, &AkazeWidgetImp::thresholdChange);
  QSignalSpy spyOctavesChange(this, &AkazeWidgetImp::octavesChange);
  QSignalSpy spyOctaveLayersChange(this, &AkazeWidgetImp::octaveLayersChange);
  QSignalSpy spyDiffusivityChange(this, &AkazeWidgetImp::diffusivityChange);

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

void TestAkazeWidgetSignals::test_descriptorTypeChange()
{
  QSignalSpy spyDescriptorTypeChange(this, &AkazeWidgetImp::descriptorTypeChange);

  this->mDescriptorType->setCurrentText("KAZE");

  QCOMPARE(spyDescriptorTypeChange.count(), 1);

  QList<QVariant> args = spyDescriptorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "KAZE");

  this->mDescriptorType->setCurrentText("KAZE");
  QCOMPARE(spyDescriptorTypeChange.count(), 0);

  this->setDescriptorType("KAZE_UPRIGHT");
  QCOMPARE(spyDescriptorTypeChange.count(), 0);
}

void TestAkazeWidgetSignals::test_descriptorSizeChange()
{
  QSignalSpy spyDescriptorSizeChange(this, &AkazeWidgetImp::descriptorSizeChange);

  mDescriptorSize->setValue(64);

  QCOMPARE(spyDescriptorSizeChange.count(), 1);

  QList<QVariant> args = spyDescriptorSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 64);

  this->setDescriptorSize(32);
  QCOMPARE(spyDescriptorSizeChange.count(), 0);
}

void TestAkazeWidgetSignals::test_descriptorChannelsChange()
{
  QSignalSpy spyDescriptorChannelsChange(this, &AkazeWidgetImp::descriptorChannelsChange);

  mDescriptorChannels->setValue(1);

  QCOMPARE(spyDescriptorChannelsChange.count(), 1);

  QList<QVariant> args = spyDescriptorChannelsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 1);

  this->setDescriptorChannels(2);
  QCOMPARE(spyDescriptorChannelsChange.count(), 0);
}

void TestAkazeWidgetSignals::test_thresholdChange()
{
  QSignalSpy spyThresholdChange(this, &AkazeWidgetImp::thresholdChange);

  mThreshold->setValue(25.);

  QCOMPARE(spyThresholdChange.count(), 1);

  QList<QVariant> args = spyThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setThreshold(120);
  QCOMPARE(spyThresholdChange.count(), 0);
}

void TestAkazeWidgetSignals::test_octavesChange()
{
  QSignalSpy spyOctavesChange(this, &AkazeWidgetImp::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spyOctavesChange.count(), 1);

  QList<QVariant> args = spyOctavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(6);
  QCOMPARE(spyOctavesChange.count(), 0);
}

void TestAkazeWidgetSignals::test_octaveLayersChange()
{
  QSignalSpy spyOctaveLayersChange(this, &AkazeWidgetImp::octaveLayersChange);

  mOctaveLayers->setValue(8);

  QCOMPARE(spyOctaveLayersChange.count(), 1);

  QList<QVariant> args = spyOctaveLayersChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayersChange.count(), 0);
}

void TestAkazeWidgetSignals::test_diffusivityChange()
{
  QSignalSpy spyDiffusivityChange(this, &AkazeWidgetImp::diffusivityChange);

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");

  QCOMPARE(spyDiffusivityChange.count(), 1);

  QList<QVariant> args = spyDiffusivityChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "DIFF_PM_G1");

  this->mDiffusivity->setCurrentText("DIFF_PM_G1");
  QCOMPARE(spyDiffusivityChange.count(), 0);

  this->setDiffusivity("DIFF_WEICKERT");
  QCOMPARE(spyDiffusivityChange.count(), 0);
}


QTEST_MAIN(TestAkazeWidgetSignals)

#include "tst_akazewidgetsignals.moc"
