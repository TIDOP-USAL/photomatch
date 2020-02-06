#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/FastWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestFastWidgetSignals : public FastWidgetImp
{
  Q_OBJECT

public:

  TestFastWidgetSignals();
  ~TestFastWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_thresholdChange();
  void test_nonmaxSuppressionChange();
  void test_detectorTypeChange();

};

TestFastWidgetSignals::TestFastWidgetSignals()
  : FastWidgetImp()
{

}

TestFastWidgetSignals::~TestFastWidgetSignals()
{

}

void TestFastWidgetSignals::initTestCase()
{
}

void TestFastWidgetSignals::cleanupTestCase()
{
  QSignalSpy spyThreshold(this, &FastWidgetImp::thresholdChange);
  QSignalSpy spyNonmaxSuppressionChange(this, &FastWidgetImp::nonmaxSuppressionChange);
  QSignalSpy spyDetectorTypeChange(this, &FastWidgetImp::detectorTypeChange);

  this->setThreshold(25);
  this->setNonmaxSuppression(false);
  this->setDetectorType("TYPE_5_8");

  this->reset();

  QCOMPARE(spyThreshold.count(), 0);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}

void TestFastWidgetSignals::test_thresholdChange()
{
  QSignalSpy spyThreshold(this, &FastWidgetImp::thresholdChange);

  this->mThreshold->setValue(50);

  QCOMPARE(spyThreshold.count(), 1);

  QList<QVariant> args = spyThreshold.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setThreshold(25);
  QCOMPARE(spyThreshold.count(), 0);
}

void TestFastWidgetSignals::test_nonmaxSuppressionChange()
{
  QSignalSpy spyNonmaxSuppressionChange(this, &FastWidgetImp::nonmaxSuppressionChange);

  QTest::mouseClick(mNonmaxSuppression, Qt::MouseButton::LeftButton);

  QCOMPARE(spyNonmaxSuppressionChange.count(), 1);

  QList<QVariant> args = spyNonmaxSuppressionChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setNonmaxSuppression(false);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
}

void TestFastWidgetSignals::test_detectorTypeChange()
{
  QSignalSpy spyDetectorTypeChange(this, &FastWidgetImp::detectorTypeChange);

  this->mDetectorType->setCurrentText("TYPE_7_12");

  QCOMPARE(spyDetectorTypeChange.count(), 1);

  QList<QVariant> args = spyDetectorTypeChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "TYPE_7_12");

  this->mDetectorType->setCurrentText("TYPE_7_12");
  QCOMPARE(spyDetectorTypeChange.count(), 0);

  this->setDetectorType("TYPE_5_8");
  QCOMPARE(spyDetectorTypeChange.count(), 0);
}


QTEST_MAIN(TestFastWidgetSignals)

#include "tst_fastwidgetsignals.moc"
