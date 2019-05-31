#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/DescriptorMatcherWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace fme;

class TestDescriptorMatcherWidgetSignals : public DescriptorMatcherWidget
{
  Q_OBJECT

public:
  TestDescriptorMatcherWidgetSignals();
  ~TestDescriptorMatcherWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testMatchingMethodChange();
  void testNormTypeChange();
  void testRatioChange();
  void testDistanceChange();
  void testConfidenceChange();
  void testCrossMatchingChange();
  void testReset();
};

TestDescriptorMatcherWidgetSignals::TestDescriptorMatcherWidgetSignals()
  : DescriptorMatcherWidget()
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

}

void TestDescriptorMatcherWidgetSignals::testMatchingMethodChange()
{
  QSignalSpy spyDetectorMethodChange(this, &DescriptorMatcherWidget::matchingMethodChange);

  this->mMatchingMethod->setCurrentText("FLANN");

  QCOMPARE(spyDetectorMethodChange.count(), 1);

  QList<QVariant> args = spyDetectorMethodChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "FLANN");

  this->mMatchingMethod->setCurrentText("FLANN");
  QCOMPARE(spyDetectorMethodChange.count(), 0);

  this->setMatchingMethod("Brute-Force");
  QCOMPARE(spyDetectorMethodChange.count(), 0);

//  QCOMPARE(mNormType->isVisible(), true);
//  this->mMatchingMethod->setCurrentText("FLANN");
//  QCOMPARE(mNormType->isVisible(), false);
}

void TestDescriptorMatcherWidgetSignals::testNormTypeChange()
{
  QSignalSpy spyDetectorTypeChange(this, &DescriptorMatcherWidget::normTypeChange);

  this->mNormType->setCurrentText("NORM_L2");

  QCOMPARE(spyDetectorTypeChange.count(), 1);

  QList<QVariant> args = spyDetectorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "NORM_L2");

  this->mNormType->setCurrentText("NORM_L2");
  QCOMPARE(spyDetectorTypeChange.count(), 0);

  this->setNormType("NORM_HAMMING");
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::testRatioChange()
{
  QSignalSpy spyRatioChange(this, &DescriptorMatcherWidget::ratioChange);

  this->mRatio->setValue(0.5);

  QCOMPARE(spyRatioChange.count(), 1);

  QList<QVariant> args = spyRatioChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setRatio(.25);
  QCOMPARE(spyRatioChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::testDistanceChange()
{
  QSignalSpy spyDistanceChange(this, &DescriptorMatcherWidget::distanceChange);

  this->mDistance->setValue(0.5);

  QCOMPARE(spyDistanceChange.count(), 1);

  QList<QVariant> args = spyDistanceChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setDistance(.25);
  QCOMPARE(spyDistanceChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::testConfidenceChange()
{
  QSignalSpy spyConfidenceChange(this, &DescriptorMatcherWidget::confidenceChange);

  this->mConfidence->setValue(0.5);

  QCOMPARE(spyConfidenceChange.count(), 1);

  QList<QVariant> args = spyConfidenceChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setConfidence(.25);
  QCOMPARE(spyConfidenceChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::testCrossMatchingChange()
{
  QSignalSpy spyCrossMatchingChange(this, &DescriptorMatcherWidget::crossMatchingChange);

  QTest::mouseClick(mCrossMatching, Qt::MouseButton::LeftButton);

  QCOMPARE(spyCrossMatchingChange.count(), 1);

  QList<QVariant> args = spyCrossMatchingChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setCrossMatching(false);
  QCOMPARE(spyCrossMatchingChange.count(), 0);
}

void TestDescriptorMatcherWidgetSignals::testReset()
{
  QSignalSpy spyDetectorMethodChange(this, &DescriptorMatcherWidget::matchingMethodChange);
  QSignalSpy spyDetectorTypeChange(this, &DescriptorMatcherWidget::normTypeChange);
  QSignalSpy spyRatioChange(this, &DescriptorMatcherWidget::ratioChange);;
  QSignalSpy spyDistanceChange(this, &DescriptorMatcherWidget::distanceChange);
  QSignalSpy spyConfidenceChange(this, &DescriptorMatcherWidget::confidenceChange);
  QSignalSpy spyCrossMatchingChange(this, &DescriptorMatcherWidget::crossMatchingChange);

  this->setMatchingMethod("FLANN");
  this->setNormType("NORM_HAMMING");
  this->setRatio(.25);
  this->setDistance(.25);
  this->setConfidence(.25);
  this->setCrossMatching(false);

  this->reset();

  QCOMPARE(spyDetectorMethodChange.count(), 0);
  QCOMPARE(spyDetectorTypeChange.count(), 0);
  QCOMPARE(spyRatioChange.count(), 0);
  QCOMPARE(spyDistanceChange.count(), 0);
  QCOMPARE(spyConfidenceChange.count(), 0);
  QCOMPARE(spyCrossMatchingChange.count(), 0);
}


QTEST_MAIN(TestDescriptorMatcherWidgetSignals)

#include "tst_descriptormatcherwidgetsignals.moc"
