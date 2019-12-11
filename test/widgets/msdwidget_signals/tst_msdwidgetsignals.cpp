#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MsdWidget.h"

#include <QSpinBox>
#include <QCheckBox>

using namespace photomatch;

class TestMsdWidgetSignals : public MsdWidget
{
  Q_OBJECT

public:

  TestMsdWidgetSignals();
  ~TestMsdWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_thresholdSaliencyChange();
  void test_pathRadiusChange();
  void test_KNNChange();
  void test_areaRadiusChange();
  void test_scaleFactorChange();
  void test_NMSRadiusChange();
  void test_NScalesChange();
  void test_NMSScaleRChange();
  void test_computeOrientationsChange();
  void test_affineMSDChange();
  void test_tiltsChange();
  void test_reset();
};

TestMsdWidgetSignals::TestMsdWidgetSignals()
  : MsdWidget()
{

}

TestMsdWidgetSignals::~TestMsdWidgetSignals()
{

}

void TestMsdWidgetSignals::initTestCase()
{

}

void TestMsdWidgetSignals::cleanupTestCase()
{

}

void TestMsdWidgetSignals::test_thresholdSaliencyChange()
{
  QSignalSpy spyThresholdSaliencyChange(this, &MsdWidget::thresholdSaliencyChange);

  this->mThresholdSaliency->setValue(500);

  QCOMPARE(spyThresholdSaliencyChange.count(), 1);

  QList<QVariant> args = spyThresholdSaliencyChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 500);

  this->setThresholdSaliency(1000);
  QCOMPARE(spyThresholdSaliencyChange.count(), 0);
}

void TestMsdWidgetSignals::test_pathRadiusChange()
{
  QSignalSpy spyPathRadiusChange(this, &MsdWidget::pathRadiusChange);

  this->mPathRadius->setValue(5);

  QCOMPARE(spyPathRadiusChange.count(), 1);

  QList<QVariant> args = spyPathRadiusChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setPatchRadius(10);
  QCOMPARE(spyPathRadiusChange.count(), 0);
}

void TestMsdWidgetSignals::test_KNNChange()
{
  QSignalSpy spyKNNChange(this, &MsdWidget::KNNChange);

  this->mKNN->setValue(5);

  QCOMPARE(spyKNNChange.count(), 1);

  QList<QVariant> args = spyKNNChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setKNN(10);
  QCOMPARE(spyKNNChange.count(), 0);
}

void TestMsdWidgetSignals::test_areaRadiusChange()
{
  QSignalSpy spyAreaRadiusChange(this, &MsdWidget::areaRadiusChange);

  this->mAreaRadius->setValue(4);

  QCOMPARE(spyAreaRadiusChange.count(), 1);

  QList<QVariant> args = spyAreaRadiusChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setAreaRadius(10);
  QCOMPARE(spyAreaRadiusChange.count(), 0);
}

void TestMsdWidgetSignals::test_scaleFactorChange()
{
  QSignalSpy spyScaleFactorChange(this, &MsdWidget::scaleFactorChange);

  this->mScaleFactor->setValue(5.);

  QCOMPARE(spyScaleFactorChange.count(), 1);

  QList<QVariant> args = spyScaleFactorChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.);

  this->setScaleFactor(10.);
  QCOMPARE(spyScaleFactorChange.count(), 0);
}

void TestMsdWidgetSignals::test_NMSRadiusChange()
{
  QSignalSpy spyNMSRadiusChange(this, &MsdWidget::NMSRadiusChange);

  this->mNMSRadius->setValue(4);

  QCOMPARE(spyNMSRadiusChange.count(), 1);

  QList<QVariant> args = spyNMSRadiusChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setNMSRadius(10);
  QCOMPARE(spyNMSRadiusChange.count(), 0);
}

void TestMsdWidgetSignals::test_NScalesChange()
{
  QSignalSpy spyNScalesChange(this, &MsdWidget::nScalesChange);

  this->mNScales->setValue(4);

  QCOMPARE(spyNScalesChange.count(), 1);

  QList<QVariant> args = spyNScalesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setNScales(10);
  QCOMPARE(spyNScalesChange.count(), 0);
}

void TestMsdWidgetSignals::test_NMSScaleRChange()
{
  QSignalSpy spyNMSScaleRChange(this, &MsdWidget::NMSScaleRChange);

  this->mNMSScaleR->setValue(4);

  QCOMPARE(spyNMSScaleRChange.count(), 1);

  QList<QVariant> args = spyNMSScaleRChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setNMSScaleR(10);
  QCOMPARE(spyNMSScaleRChange.count(), 0);
}

void TestMsdWidgetSignals::test_computeOrientationsChange()
{
  QSignalSpy spyComputeOrientationsChange(this, &MsdWidget::computeOrientationsChange);

  QTest::mouseClick(mComputeOrientations, Qt::MouseButton::LeftButton);

  QCOMPARE(spyComputeOrientationsChange.count(), 1);

  QList<QVariant> args = spyComputeOrientationsChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setComputeOrientations(false);
  QCOMPARE(spyComputeOrientationsChange.count(), 0);
}

void TestMsdWidgetSignals::test_affineMSDChange()
{
  QSignalSpy spyAffineMSDChange(this, &MsdWidget::affineMSDChange);

  QTest::mouseClick(mAffineMSD, Qt::MouseButton::LeftButton);

  QCOMPARE(spyAffineMSDChange.count(), 1);

  QList<QVariant> args = spyAffineMSDChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setAffineMSD(false);
  QCOMPARE(spyAffineMSDChange.count(), 0);
}

void TestMsdWidgetSignals::test_tiltsChange()
{
  QSignalSpy spyTiltsChange(this, &MsdWidget::tiltsChange);

  this->mTilts->setValue(4);

  QCOMPARE(spyTiltsChange.count(), 1);

  QList<QVariant> args = spyTiltsChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 4);

  this->setTilts(10);
  QCOMPARE(spyTiltsChange.count(), 0);
}

void TestMsdWidgetSignals::test_reset()
{
  QSignalSpy spyThresholdSaliencyChange(this, &MsdWidget::thresholdSaliencyChange);
  QSignalSpy spyPathRadiusChange(this, &MsdWidget::pathRadiusChange);
  QSignalSpy spyKNNChange(this, &MsdWidget::KNNChange);
  QSignalSpy spyAreaRadiusChange(this, &MsdWidget::areaRadiusChange);
  QSignalSpy spyScaleFactorChange(this, &MsdWidget::scaleFactorChange);
  QSignalSpy spyNMSRadiusChange(this, &MsdWidget::NMSRadiusChange);
  QSignalSpy spyNScalesChange(this, &MsdWidget::nScalesChange);
  QSignalSpy spyNMSScaleRChange(this, &MsdWidget::NMSScaleRChange);
  QSignalSpy spyComputeOrientationsChange(this, &MsdWidget::computeOrientationsChange);
  QSignalSpy spyAffineMSDChange(this, &MsdWidget::affineMSDChange);
  QSignalSpy spyTiltsChange(this, &MsdWidget::tiltsChange);

  this->setThresholdSaliency(1500);
  this->setPatchRadius(9);
  this->setKNN(9);
  this->setAreaRadius(8);
  this->setScaleFactor(9.);
  this->setNMSRadius(9);
  this->setNScales(9);
  this->setNMSScaleR(9);
  this->setComputeOrientations(true);
  this->setAffineMSD(true);
  this->setTilts(9);

  this->reset();

  QCOMPARE(spyThresholdSaliencyChange.count(), 0);
  QCOMPARE(spyPathRadiusChange.count(), 0);
  QCOMPARE(spyKNNChange.count(), 0);
  QCOMPARE(spyAreaRadiusChange.count(), 0);
  QCOMPARE(spyScaleFactorChange.count(), 0);
  QCOMPARE(spyNMSRadiusChange.count(), 0);
  QCOMPARE(spyNScalesChange.count(), 0);
  QCOMPARE(spyNMSScaleRChange.count(), 0);
  QCOMPARE(spyComputeOrientationsChange.count(), 0);
  QCOMPARE(spyAffineMSDChange.count(), 0);
  QCOMPARE(spyTiltsChange.count(), 0);
}

QTEST_MAIN(TestMsdWidgetSignals)

#include "tst_msdwidgetsignals.moc"
