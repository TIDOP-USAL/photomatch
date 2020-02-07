#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/AgastWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestAgastWidgetSignals : public AgastWidgetImp
{
  Q_OBJECT

public:

  TestAgastWidgetSignals();
  ~TestAgastWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_thresholdChange();
  void test_nonmaxSuppressionChange();
  void test_detectorTypeChange();

};

TestAgastWidgetSignals::TestAgastWidgetSignals()
  : AgastWidgetImp()
{

}

TestAgastWidgetSignals::~TestAgastWidgetSignals()
{

}

void TestAgastWidgetSignals::initTestCase()
{
}

void TestAgastWidgetSignals::cleanupTestCase()
{
  QSignalSpy spyThreshold(this, &AgastWidgetImp::thresholdChange);
  QSignalSpy spyNonmaxSuppressionChange(this, &AgastWidgetImp::nonmaxSuppressionChange);
  QSignalSpy spyDetectorTypeChange(this, &AgastWidgetImp::detectorTypeChange);

  this->setThreshold(25);
  this->setNonmaxSuppression(false);
  this->setDetectorType("AGAST_5_8");

  this->reset();

  QCOMPARE(spyThreshold.count(), 0);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}

void TestAgastWidgetSignals::test_thresholdChange()
{
  QSignalSpy spyThreshold(this, &AgastWidgetImp::thresholdChange);

  this->mThreshold->setValue(50);

  QCOMPARE(spyThreshold.count(), 1);

  QList<QVariant> args = spyThreshold.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setThreshold(25);
  QCOMPARE(spyThreshold.count(), 0);
}

void TestAgastWidgetSignals::test_nonmaxSuppressionChange()
{
  QSignalSpy spyNonmaxSuppressionChange(this, &AgastWidgetImp::nonmaxSuppressionChange);

  QTest::mouseClick(mNonmaxSuppression, Qt::MouseButton::LeftButton);

  QCOMPARE(spyNonmaxSuppressionChange.count(), 1);

  QList<QVariant> args = spyNonmaxSuppressionChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setNonmaxSuppression(false);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
}

void TestAgastWidgetSignals::test_detectorTypeChange()
{
  QSignalSpy spyDetectorTypeChange(this, &AgastWidgetImp::detectorTypeChange);

  this->mDetectorType->setCurrentText("AGAST_7_12d");

  QCOMPARE(spyDetectorTypeChange.count(), 1);

  QList<QVariant> args = spyDetectorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "AGAST_7_12d");

  this->mDetectorType->setCurrentText("AGAST_7_12d");
  QCOMPARE(spyDetectorTypeChange.count(), 0);

  this->setDetectorType("AGAST_5_8");
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}



QTEST_MAIN(TestAgastWidgetSignals)

#include "tst_agastwidgetsignals.moc"
