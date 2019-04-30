#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/AgastWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace fme;

class TestAgastWidgetSignals : public AgastWidget
{
  Q_OBJECT

public:
  TestAgastWidgetSignals();
  ~TestAgastWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testThresholdChange();
  void testNonmaxSuppressionChange();
  void testDetectorTypeChange();
  void testReset();

};

TestAgastWidgetSignals::TestAgastWidgetSignals()
  : AgastWidget()
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

}

void TestAgastWidgetSignals::testThresholdChange()
{
  QSignalSpy spyThreshold(this, &AgastWidget::thresholdChange);

  this->mThreshold->setValue(50);

  QCOMPARE(spyThreshold.count(), 1);

  QList<QVariant> args = spyThreshold.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setThreshold(25);
  QCOMPARE(spyThreshold.count(), 0);
}

void TestAgastWidgetSignals::testNonmaxSuppressionChange()
{
  QSignalSpy spyNonmaxSuppressionChange(this, &AgastWidget::nonmaxSuppressionChange);

  QTest::mouseClick(mNonmaxSuppression, Qt::MouseButton::LeftButton);

  QCOMPARE(spyNonmaxSuppressionChange.count(), 1);

  QList<QVariant> args = spyNonmaxSuppressionChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setNonmaxSuppression(false);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
}

void TestAgastWidgetSignals::testDetectorTypeChange()
{
  QSignalSpy spyDetectorTypeChange(this, &AgastWidget::detectorTypeChange);

  this->mDetectorType->setCurrentText("AGAST_7_12d");

  QCOMPARE(spyDetectorTypeChange.count(), 1);

  QList<QVariant> args = spyDetectorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "AGAST_7_12d");

  this->mDetectorType->setCurrentText("AGAST_7_12d");
  QCOMPARE(spyDetectorTypeChange.count(), 0);

  this->setDetectorType("AGAST_5_8");
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}

void TestAgastWidgetSignals::testReset()
{
  QSignalSpy spyThreshold(this, &AgastWidget::thresholdChange);
  QSignalSpy spyNonmaxSuppressionChange(this, &AgastWidget::nonmaxSuppressionChange);
  QSignalSpy spyDetectorTypeChange(this, &AgastWidget::detectorTypeChange);

  this->setThreshold(25);
  this->setNonmaxSuppression(false);
  this->setDetectorType("AGAST_5_8");

  this->reset();

  QCOMPARE(spyThreshold.count(), 0);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}


QTEST_MAIN(TestAgastWidgetSignals)

#include "tst_agastwidgetsignals.moc"
