#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DescriptorMatcherWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>

using namespace photomatch;

class TestDescriptorMatcherWidgetSignals : public DescriptorMatcherWidgetImp
{
  Q_OBJECT

public:
  TestDescriptorMatcherWidgetSignals();
  ~TestDescriptorMatcherWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_matchingMethodChange();
  void test_normTypeChange();
  void test_ratioChange();
  void test_geometricTestChange();
  void test_homographyComputeMethodChange();
  void test_fundamentalComputeMethodChange();
  void test_essentialComputeMethodChange();
  void test_distanceChange();
  void test_confidenceChange();
  void test_crossMatchingChange();
  void test_maxItersChange();
  void test_update();
  void test_gmsRotationChange();
  void test_gmsScaleChange();
  void test_gmsThresholdChange();
};

TestDescriptorMatcherWidgetSignals::TestDescriptorMatcherWidgetSignals()
  : DescriptorMatcherWidgetImp()
{

}

TestDescriptorMatcherWidgetSignals::~TestDescriptorMatcherWidgetSignals()
{

}

void TestDescriptorMatcherWidgetSignals::initTestCase()
{

}

void TestDescriptorMatcherWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_detectorMethodChange(this, &DescriptorMatcherWidgetImp::matchingMethodChange);
  QSignalSpy spy_detectorTypeChange(this, &DescriptorMatcherWidgetImp::normTypeChange);
  QSignalSpy spy_ratioChange(this, &DescriptorMatcherWidgetImp::ratioChange);
  QSignalSpy spy_distanceChange(this, &DescriptorMatcherWidgetImp::distanceChange);
  QSignalSpy spy_confidenceChange(this, &DescriptorMatcherWidgetImp::confidenceChange);
  QSignalSpy spy_crossMatchingChange(this, &DescriptorMatcherWidgetImp::crossMatchingChange);
  QSignalSpy spy_geometricTestChange(this, &DescriptorMatcherWidgetImp::geometricTestChange);
  QSignalSpy spy_homographyComputeMethodChange(this, &DescriptorMatcherWidgetImp::homographyComputeMethodChange);
  QSignalSpy spy_fundamentalComputeMethodChange(this, &DescriptorMatcherWidgetImp::fundamentalComputeMethodChange);
  QSignalSpy spy_essentialComputeMethodChange(this, &DescriptorMatcherWidgetImp::essentialComputeMethodChange);
  QSignalSpy spy_maxItersChange(this, &DescriptorMatcherWidgetImp::maxItersChange);
  QSignalSpy spy_gmsScaleChange(this, &DescriptorMatcherWidgetImp::gmsScaleChange);
  QSignalSpy spy_gmsRotationChange(this, &DescriptorMatcherWidgetImp::gmsRotationChange);
  QSignalSpy spy_gmsThresholdChange(this, &DescriptorMatcherWidgetImp::gmsThresholdChange);

  this->setMatchingMethod("FLANN");
  this->setNormType("NORM_HAMMING");
  this->setRatio(.25);
  this->setDistance(.25);
  this->setConfidence(.25);
  this->setCrossMatching(false);
  this->setGeometricTest("Essential Matrix");
  this->setHomographyComputeMethod("RHO");
  this->setFundamentalComputeMethod("LMedS");
  this->setEssentialComputeMethod("RANSAC");
  this->setMaxIters(3000);
  this->setGmsScale(true);
  this->setGmsRotation(true);
  this->setGmsThreshold(5.0);

  this->reset();

  QCOMPARE(spy_detectorMethodChange.count(), 0);
  QCOMPARE(spy_detectorTypeChange.count(), 0);
  QCOMPARE(spy_ratioChange.count(), 0);
  QCOMPARE(spy_distanceChange.count(), 0);
  QCOMPARE(spy_confidenceChange.count(), 0);
  QCOMPARE(spy_crossMatchingChange.count(), 0);
  QCOMPARE(spy_geometricTestChange.count(), 0);
  QCOMPARE(spy_homographyComputeMethodChange.count(), 0);
  QCOMPARE(spy_fundamentalComputeMethodChange.count(), 0);
  QCOMPARE(spy_essentialComputeMethodChange.count(), 0);
  QCOMPARE(spy_maxItersChange.count(), 0);
  QCOMPARE(spy_gmsScaleChange.count(), 0);
  QCOMPARE(spy_gmsRotationChange.count(), 0);
  QCOMPARE(spy_gmsThresholdChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_matchingMethodChange()
{
  QSignalSpy spy_detectorMethodChange(this, &DescriptorMatcherWidgetImp::matchingMethodChange);

  this->mMatchingMethod->setCurrentText("FLANN");

  QCOMPARE(spy_detectorMethodChange.count(), 1);

  QList<QVariant> args = spy_detectorMethodChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "FLANN");

  this->mMatchingMethod->setCurrentText("FLANN");
  QCOMPARE(spy_detectorMethodChange.count(), 0);

  this->setMatchingMethod("Brute-Force");
  QCOMPARE(spy_detectorMethodChange.count(), 0);

//  QCOMPARE(mNormType->isVisible(), true);
//  this->mMatchingMethod->setCurrentText("FLANN");
//  QCOMPARE(mNormType->isVisible(), false);
}

void TestDescriptorMatcherWidgetSignals::test_normTypeChange()
{
  QSignalSpy spy_detectorTypeChange(this, &DescriptorMatcherWidgetImp::normTypeChange);

  this->mNormType->setCurrentText("NORM_L2");

  QCOMPARE(spy_detectorTypeChange.count(), 1);

  QList<QVariant> args = spy_detectorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "NORM_L2");

  this->mNormType->setCurrentText("NORM_L2");
  QCOMPARE(spy_detectorTypeChange.count(), 0);

  this->setNormType("NORM_HAMMING");
  QCOMPARE(spy_detectorTypeChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_ratioChange()
{
  QSignalSpy spy_ratioChange(this, &DescriptorMatcherWidgetImp::ratioChange);

  this->mRatio->setValue(0.5);

  QCOMPARE(spy_ratioChange.count(), 1);

  QList<QVariant> args = spy_ratioChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setRatio(.25);
  QCOMPARE(spy_ratioChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_geometricTestChange()
{
  QSignalSpy spy_geometricTestChange(this, &DescriptorMatcherWidgetImp::geometricTestChange);

  this->mGeometricTest->setCurrentText("Homography Matrix");

  QCOMPARE(spy_geometricTestChange.count(), 1);

  QList<QVariant> args = spy_geometricTestChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "Homography Matrix");

  this->mGeometricTest->setCurrentText("Homography Matrix");
  QCOMPARE(spy_geometricTestChange.count(), 0);

  this->setGeometricTest("Fundamental Matrix");
  QCOMPARE(spy_geometricTestChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_homographyComputeMethodChange()
{
  QSignalSpy spy_homographyComputeMethodChange(this, &DescriptorMatcherWidgetImp::homographyComputeMethodChange);

  this->mHComputeMethod->setCurrentText("All Points");

  QCOMPARE(spy_homographyComputeMethodChange.count(), 1);

  QList<QVariant> args = spy_homographyComputeMethodChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "All Points");

  this->mHComputeMethod->setCurrentText("All Points");
  QCOMPARE(spy_homographyComputeMethodChange.count(), 0);

  this->setHomographyComputeMethod("RHO");
  QCOMPARE(spy_homographyComputeMethodChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_fundamentalComputeMethodChange()
{
  QSignalSpy spy_fundamentalComputeMethodChange(this, &DescriptorMatcherWidgetImp::fundamentalComputeMethodChange);

  this->mFComputeMethod->setCurrentText("7-point algorithm");

  QCOMPARE(spy_fundamentalComputeMethodChange.count(), 1);

  QList<QVariant> args = spy_fundamentalComputeMethodChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "7-point algorithm");

  this->mFComputeMethod->setCurrentText("7-point algorithm");
  QCOMPARE(spy_fundamentalComputeMethodChange.count(), 0);

  this->setFundamentalComputeMethod("LMedS");
  QCOMPARE(spy_fundamentalComputeMethodChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_essentialComputeMethodChange()
{
  QSignalSpy spy_essentialComputeMethodChange(this, &DescriptorMatcherWidgetImp::essentialComputeMethodChange);

  this->mEComputeMethod->setCurrentText("LMedS");

  QCOMPARE(spy_essentialComputeMethodChange.count(), 1);

  QList<QVariant> args = spy_essentialComputeMethodChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "LMedS");

  this->mEComputeMethod->setCurrentText("7-point algorithm");
  QCOMPARE(spy_essentialComputeMethodChange.count(), 0);

  this->setEssentialComputeMethod("RANSAC");
  QCOMPARE(spy_essentialComputeMethodChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_distanceChange()
{
  QSignalSpy spy_distanceChange(this, &DescriptorMatcherWidgetImp::distanceChange);

  this->mDistance->setValue(0.5);

  QCOMPARE(spy_distanceChange.count(), 1);

  QList<QVariant> args = spy_distanceChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setDistance(.25);
  QCOMPARE(spy_distanceChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_confidenceChange()
{
  QSignalSpy spy_confidenceChange(this, &DescriptorMatcherWidgetImp::confidenceChange);

  this->mConfidence->setValue(0.5);

  QCOMPARE(spy_confidenceChange.count(), 1);

  QList<QVariant> args = spy_confidenceChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setConfidence(.25);
  QCOMPARE(spy_confidenceChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_crossMatchingChange()
{
  QSignalSpy spy_crossMatchingChange(this, &DescriptorMatcherWidgetImp::crossMatchingChange);

  QTest::mouseClick(mCrossMatching, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_crossMatchingChange.count(), 1);

  QList<QVariant> args = spy_crossMatchingChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setCrossMatching(false);
  QCOMPARE(spy_crossMatchingChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_maxItersChange()
{
  QSignalSpy spy_maxItersChange(this, &DescriptorMatcherWidgetImp::maxItersChange);

  this->mMaxIters->setValue(5000);

  QCOMPARE(spy_maxItersChange.count(), 1);

  QList<QVariant> args = spy_maxItersChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5000);

  this->setMaxIters(2000);
  QCOMPARE(spy_maxItersChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_update()
{
  this->show();

  this->setMatchingMethod("FLANN");
  QCOMPARE(false, this->mGroupBoxBFParameters->isVisible());

  this->setMatchingMethod("Brute-Force");
  QCOMPARE(true, this->mGroupBoxBFParameters->isVisible());

  this->setGeometricTest("Homography Matrix");
  QCOMPARE(true, this->mHComputeMethod->isVisible());
  QCOMPARE(true, this->mHComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mFComputeMethod->isVisible());
  QCOMPARE(false, this->mFComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mEComputeMethod->isVisible());
  QCOMPARE(false, this->mEComputeMethodLabel->isVisible());
  QCOMPARE(true, this->mConfidence->isVisible());
  QCOMPARE(true, this->mConfidenceLabel->isVisible());
  this->setHomographyComputeMethod("All Points");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
  QCOMPARE(false, this->mMaxIters->isVisible());
  QCOMPARE(false, this->mMaxItersLabel->isVisible());
  this->setHomographyComputeMethod("RANSAC");
  QCOMPARE(true, this->mDistance->isVisible());
  QCOMPARE(true, this->mDistanceLabel->isVisible());
  QCOMPARE(true, this->mMaxIters->isVisible());
  QCOMPARE(true, this->mMaxItersLabel->isVisible());
  this->setHomographyComputeMethod("LMedS");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
  QCOMPARE(false, this->mMaxIters->isVisible());
  QCOMPARE(false, this->mMaxItersLabel->isVisible());
  this->setHomographyComputeMethod("RHO");
  QCOMPARE(true, this->mDistance->isVisible());
  QCOMPARE(true, this->mDistanceLabel->isVisible());
  QCOMPARE(false, this->mMaxIters->isVisible());
  QCOMPARE(false, this->mMaxItersLabel->isVisible());

  this->setGeometricTest("Fundamental Matrix");
  QCOMPARE(false, this->mHComputeMethod->isVisible());
  QCOMPARE(false, this->mHComputeMethodLabel->isVisible());
  QCOMPARE(true, this->mFComputeMethod->isVisible());
  QCOMPARE(true, this->mFComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mEComputeMethod->isVisible());
  QCOMPARE(false, this->mEComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mMaxIters->isVisible());
  QCOMPARE(false, this->mMaxItersLabel->isVisible());
  this->setFundamentalComputeMethod("7-point algorithm");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
  QCOMPARE(false, this->mConfidence->isVisible());
  QCOMPARE(false, this->mConfidenceLabel->isVisible());
  this->setFundamentalComputeMethod("8-point algorithm");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
  QCOMPARE(false, this->mConfidence->isVisible());
  QCOMPARE(false, this->mConfidenceLabel->isVisible());
  this->setFundamentalComputeMethod("RANSAC");
  QCOMPARE(true, this->mDistance->isVisible());
  QCOMPARE(true, this->mDistanceLabel->isVisible());
  QCOMPARE(true, this->mConfidence->isVisible());
  QCOMPARE(true, this->mConfidenceLabel->isVisible());
  this->setFundamentalComputeMethod("LMedS");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
  QCOMPARE(true, this->mConfidence->isVisible());
  QCOMPARE(true, this->mConfidenceLabel->isVisible());

  QSKIP("Por ahora no se usa la matriz esencial");
  this->setGeometricTest("Essential Matrix");
  QCOMPARE(false, this->mHComputeMethod->isVisible());
  QCOMPARE(false, this->mHComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mFComputeMethod->isVisible());
  QCOMPARE(false, this->mFComputeMethodLabel->isVisible());
  QCOMPARE(true, this->mEComputeMethod->isVisible());
  QCOMPARE(true, this->mEComputeMethodLabel->isVisible());
  QCOMPARE(false, this->mMaxIters->isVisible());
  QCOMPARE(false, this->mMaxItersLabel->isVisible());
  QCOMPARE(true, this->mConfidence->isVisible());
  QCOMPARE(true, this->mConfidenceLabel->isVisible());
  this->setEssentialComputeMethod("RANSAC");
  QCOMPARE(true, this->mDistance->isVisible());
  QCOMPARE(true, this->mDistanceLabel->isVisible());
  this->setEssentialComputeMethod("LMedS");
  QCOMPARE(false, this->mDistance->isVisible());
  QCOMPARE(false, this->mDistanceLabel->isVisible());
}

void TestDescriptorMatcherWidgetSignals::test_gmsRotationChange()
{
  QSignalSpy spy_gmsRotationChange(this, &DescriptorMatcherWidgetImp::gmsRotationChange);

  QTest::mouseClick(mRotationGMS, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_gmsRotationChange.count(), 1);

  QList<QVariant> args = spy_gmsRotationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setGmsRotation(true);
  QCOMPARE(spy_gmsRotationChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_gmsScaleChange()
{
  QSignalSpy spy_gmsScaleChange(this, &DescriptorMatcherWidgetImp::gmsScaleChange);

  QTest::mouseClick(mScaleGMS, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_gmsScaleChange.count(), 1);

  QList<QVariant> args = spy_gmsScaleChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setGmsScale(true);
  QCOMPARE(spy_gmsScaleChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::test_gmsThresholdChange()
{
  QSignalSpy spy_gmsThresholdChange(this, &DescriptorMatcherWidgetImp::gmsThresholdChange);

  this->mThresholdGMS->setValue(5.0);

  QCOMPARE(spy_gmsThresholdChange.count(), 1);

  QList<QVariant> args = spy_gmsThresholdChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 5.0);

  this->setGmsThreshold(2.0);
  QCOMPARE(spy_gmsThresholdChange.count(), 0);
}


QTEST_MAIN(TestDescriptorMatcherWidgetSignals)

#include "tst_descriptormatcherwidgetsignals.moc"
