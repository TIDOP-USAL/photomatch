#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/SiftWidget.h"

#include <QSpinBox>

using namespace photomatch;

class TestSiftWidgetSignals : public SiftWidget
{
  Q_OBJECT

public:

  TestSiftWidgetSignals();
  ~TestSiftWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testFeaturesNumberChange();
  void testOctaveLayersChange();
  void testContrastThresholdChange();
  void testEdgeThresholdChange();
  void testSigmaChange();
  void testReset();
};

TestSiftWidgetSignals::TestSiftWidgetSignals()
  : SiftWidget()
{

}

TestSiftWidgetSignals::~TestSiftWidgetSignals()
{

}

void TestSiftWidgetSignals::initTestCase()
{

}

void TestSiftWidgetSignals::cleanupTestCase()
{

}

void TestSiftWidgetSignals::testFeaturesNumberChange()
{
  QSignalSpy spyFeaturesNumber(this, &SiftWidget::featuresNumberChange);

  this->mFeaturesNumber->setValue(1500);

  QCOMPARE(spyFeaturesNumber.count(), 1);

  QList<QVariant> args = spyFeaturesNumber.takeFirst();
  QCOMPARE(args.at(0).toInt(), 1500);

  this->setFeaturesNumber(5000);
  QCOMPARE(spyFeaturesNumber.count(), 0);
}

void TestSiftWidgetSignals::testOctaveLayersChange()
{
  QSignalSpy spyOctaveLayers(this, &SiftWidget::octaveLayersChange);

  this->mOctaveLayers->setValue(5);

  QCOMPARE(spyOctaveLayers.count(), 1);

  QList<QVariant> args = spyOctaveLayers.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setOctaveLayers(6);
  QCOMPARE(spyOctaveLayers.count(), 0);
}

void TestSiftWidgetSignals::testContrastThresholdChange()
{
  QSignalSpy spyContrastThreshold(this, &SiftWidget::contrastThresholdChange);

  this->mContrastThreshold->setValue(0.5);

  QCOMPARE(spyContrastThreshold.count(), 1);

  QList<QVariant> args = spyContrastThreshold.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setContrastThreshold(0.6);
  QCOMPARE(spyContrastThreshold.count(), 0);
}

void TestSiftWidgetSignals::testEdgeThresholdChange()
{
  QSignalSpy spyEdgeThreshold(this, &SiftWidget::edgeThresholdChange);

  this->mEdgeThreshold->setValue(20.);

  QCOMPARE(spyEdgeThreshold.count(), 1);

  QList<QVariant> args = spyEdgeThreshold.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 20.);

  this->setEdgeThreshold(15.);
  QCOMPARE(spyEdgeThreshold.count(), 0);
}

void TestSiftWidgetSignals::testSigmaChange()
{
  QSignalSpy spySigma(this, &SiftWidget::sigmaChange);

  this->mSigma->setValue(3.2);

  QCOMPARE(spySigma.count(), 1);

  QList<QVariant> args = spySigma.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 3.2);

  this->setSigma(5.2);
  QCOMPARE(spySigma.count(), 0);
}

void TestSiftWidgetSignals::testReset()
{
  QSignalSpy spyFeaturesNumber(this, &SiftWidget::featuresNumberChange);
  QSignalSpy spyOctaveLayers(this, &SiftWidget::octaveLayersChange);
  QSignalSpy spyContrastThreshold(this, &SiftWidget::contrastThresholdChange);
  QSignalSpy spyEdgeThreshold(this, &SiftWidget::edgeThresholdChange);
  QSignalSpy spySigma(this, &SiftWidget::sigmaChange);

  this->setFeaturesNumber(5000);
  this->setOctaveLayers(6);
  this->setContrastThreshold(0.6);
  this->setEdgeThreshold(15.);
  this->setSigma(5.2);

  this->reset();

  QCOMPARE(spyFeaturesNumber.count(), 0);
  QCOMPARE(spyOctaveLayers.count(), 0);
  QCOMPARE(spyContrastThreshold.count(), 0);
  QCOMPARE(spyEdgeThreshold.count(), 0);
  QCOMPARE(spySigma.count(), 0);
}

QTEST_MAIN(TestSiftWidgetSignals)

#include "tst_siftwidgetsignals.moc"
