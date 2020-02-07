#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/GfttWidget.h"

#include <QSpinBox>
#include <QCheckBox>

using namespace photomatch;

class TestGfttWidgetSignals : public GfttWidgetImp
{
  Q_OBJECT

public:

  TestGfttWidgetSignals();
  ~TestGfttWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_maxFeaturesChange();
  void test_qualityLevel();
  void test_minDistanceChange();
  void test_blockSizeChange();
  void test_harrisDetectorChange();
  void test_kChange();

};

TestGfttWidgetSignals::TestGfttWidgetSignals()
  : GfttWidgetImp()
{

}

TestGfttWidgetSignals::~TestGfttWidgetSignals()
{

}

void TestGfttWidgetSignals::initTestCase()
{
}

void TestGfttWidgetSignals::cleanupTestCase()
{
  QSignalSpy spyMaxFeaturesChange(this, &GfttWidgetImp::maxFeaturesChange);
  QSignalSpy spyQualityLevelChange(this, &GfttWidgetImp::qualityLevelChange);
  QSignalSpy spyMinDistanceChange(this, &GfttWidgetImp::minDistanceChange);
  QSignalSpy spyBlockSizeChange(this, &GfttWidgetImp::blockSizeChange);
  QSignalSpy spyHarrisDetectorChange(this, &GfttWidgetImp::harrisDetectorChange);
  QSignalSpy spyKChange(this, &GfttWidgetImp::kChange);

  this->setMaxFeatures(5000);
  this->setQualityLevel(0.1);
  this->setMinDistance(3.);
  this->setBlockSize(1);
  this->setHarrisDetector(true);
  this->setK(0.1);

  this->reset();

  QCOMPARE(spyMaxFeaturesChange.count(), 0);
  QCOMPARE(spyQualityLevelChange.count(), 0);
  QCOMPARE(spyMinDistanceChange.count(), 0);
  QCOMPARE(spyBlockSizeChange.count(), 0);
  QCOMPARE(spyHarrisDetectorChange.count(), 0);
  QCOMPARE(spyKChange.count(), 0);
}

void TestGfttWidgetSignals::test_maxFeaturesChange()
{
  QSignalSpy spyMaxFeaturesChange(this, &GfttWidgetImp::maxFeaturesChange);

  this->mMaxFeatures->setValue(5000);

  QCOMPARE(spyMaxFeaturesChange.count(), 1);

  QList<QVariant> args = spyMaxFeaturesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5000);

  this->setMaxFeatures(2000);
  QCOMPARE(spyMaxFeaturesChange.count(), 0);
}

void TestGfttWidgetSignals::test_qualityLevel()
{
  QSignalSpy spyQualityLevelChange(this, &GfttWidgetImp::qualityLevelChange);

  this->mQualityLevel->setValue(0.5);

  QCOMPARE(spyQualityLevelChange.count(), 1);

  QList<QVariant> args = spyQualityLevelChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setQualityLevel(1.);
  QCOMPARE(spyQualityLevelChange.count(), 0);
}

void TestGfttWidgetSignals::test_minDistanceChange()
{
  QSignalSpy spyMinDistanceChange(this, &GfttWidgetImp::minDistanceChange);

  this->mMinDistance->setValue(5.0);

  QCOMPARE(spyMinDistanceChange.count(), 1);

  QList<QVariant> args = spyMinDistanceChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.0);

  this->setMinDistance(1.5);
  QCOMPARE(spyMinDistanceChange.count(), 0);
}

void TestGfttWidgetSignals::test_blockSizeChange()
{
  QSignalSpy spyBlockSizeChange(this, &GfttWidgetImp::blockSizeChange);

  this->mBlockSize->setValue(50);

  QCOMPARE(spyBlockSizeChange.count(), 1);

  QList<QVariant> args = spyBlockSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setBlockSize(60);
  QCOMPARE(spyBlockSizeChange.count(), 0);
}

void TestGfttWidgetSignals::test_harrisDetectorChange()
{
  QSignalSpy spyHarrisDetectorChange(this, &GfttWidgetImp::harrisDetectorChange);

  QTest::mouseClick(mHarrisDetector, Qt::MouseButton::LeftButton);

  QCOMPARE(spyHarrisDetectorChange.count(), 1);

  QList<QVariant> args = spyHarrisDetectorChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setHarrisDetector(true);
  QCOMPARE(spyHarrisDetectorChange.count(), 0);
}

void TestGfttWidgetSignals::test_kChange()
{
  QSignalSpy spyKChange(this, &GfttWidgetImp::kChange);

  this->mK->setValue(5.0);

  QCOMPARE(spyKChange.count(), 1);

  QList<QVariant> args = spyKChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.0);

  this->setK(1.5);
  QCOMPARE(spyKChange.count(), 0);
}



QTEST_MAIN(TestGfttWidgetSignals)

#include "tst_gfttwidgetsignals.moc"
