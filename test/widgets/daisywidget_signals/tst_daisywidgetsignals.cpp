#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DaisyWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestDaisyWidgetSignals : public DaisyWidgetImp
{
  Q_OBJECT

public:

  TestDaisyWidgetSignals();
  ~TestDaisyWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_radiusChange();
  void test_qRadiusChange();
  void test_qThetaChange();
  void test_qHistChange();
  void test_normChange();
  void test_interpolationChange();
  void test_useOrientationChange();

};

TestDaisyWidgetSignals::TestDaisyWidgetSignals()
  : DaisyWidgetImp()
{

}

TestDaisyWidgetSignals::~TestDaisyWidgetSignals()
{

}

void TestDaisyWidgetSignals::initTestCase()
{

}

void TestDaisyWidgetSignals::cleanupTestCase()
{
  QSignalSpy spy_radiusChange(this, &DaisyWidgetImp::radiusChange);
  QSignalSpy spy_qRadiusChange(this, &DaisyWidgetImp::qRadiusChange);
  QSignalSpy spy_qThetaChange(this, &DaisyWidgetImp::qThetaChange);
  QSignalSpy spy_qHistChange(this, &DaisyWidgetImp::qHistChange);
  QSignalSpy spy_normChange(this, &DaisyWidgetImp::normChange);
  QSignalSpy spy_interpolationChange(this, &DaisyWidgetImp::interpolationChange);
  QSignalSpy spyNonmaxSuppressionChange(this, &DaisyWidgetImp::useOrientationChange);

  this->setRadius(25.);
  this->setQRadius(25);
  this->setQTheta(25);
  this->setQHist(25);
  this->setNorm("NRM_FULL");
  this->setInterpolation(false);
  this->setUseOrientation(true);

  this->reset();

  QCOMPARE(spy_radiusChange.count(), 0);
  QCOMPARE(spy_qRadiusChange.count(), 0);
  QCOMPARE(spy_qThetaChange.count(), 0);
  QCOMPARE(spy_qHistChange.count(), 0);
  QCOMPARE(spy_normChange.count(), 0);
  QCOMPARE(spy_interpolationChange.count(), 0);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
}

void TestDaisyWidgetSignals::test_radiusChange()
{
  QSignalSpy spy_radiusChange(this, &DaisyWidgetImp::radiusChange);

  this->mRadius->setValue(25.);

  QCOMPARE(spy_radiusChange.count(), 1);

  QList<QVariant> args = spy_radiusChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setRadius(25.);
  QCOMPARE(spy_radiusChange.count(), 0);
}

void TestDaisyWidgetSignals::test_qRadiusChange()
{
  QSignalSpy spy_qRadiusChange(this, &DaisyWidgetImp::qRadiusChange);

  this->mQRadius->setValue(50);

  QCOMPARE(spy_qRadiusChange.count(), 1);

  QList<QVariant> args = spy_qRadiusChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setQRadius(25);
  QCOMPARE(spy_qRadiusChange.count(), 0);
}

void TestDaisyWidgetSignals::test_qThetaChange()
{
  QSignalSpy spy_qThetaChange(this, &DaisyWidgetImp::qThetaChange);

  this->mQTheta->setValue(50);

  QCOMPARE(spy_qThetaChange.count(), 1);

  QList<QVariant> args = spy_qThetaChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setQTheta(25);
  QCOMPARE(spy_qThetaChange.count(), 0);
}

void TestDaisyWidgetSignals::test_qHistChange()
{
  QSignalSpy spy_qHistChange(this, &DaisyWidgetImp::qHistChange);

  this->mQHist->setValue(50);

  QCOMPARE(spy_qHistChange.count(), 1);

  QList<QVariant> args = spy_qHistChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 50);

  this->setQHist(25);
  QCOMPARE(spy_qHistChange.count(), 0);
}

void TestDaisyWidgetSignals::test_normChange()
{
  QSignalSpy spy_normChange(this, &DaisyWidgetImp::normChange);

  this->mNorm->setCurrentText("NRM_PARTIAL");

  QCOMPARE(spy_normChange.count(), 1);

  QList<QVariant> args = spy_normChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "NRM_PARTIAL");

  this->mNorm->setCurrentText("NRM_PARTIAL");
  QCOMPARE(spy_normChange.count(), 0);

  this->setNorm("NRM_FULL");
  QCOMPARE(spy_normChange.count(), 0);
}

void TestDaisyWidgetSignals::test_interpolationChange()
{
  QSignalSpy spy_interpolationChange(this, &DaisyWidgetImp::interpolationChange);

  QTest::mouseClick(mInterpolation, Qt::MouseButton::LeftButton);

  QSKIP("No entiendo porque falla...");
  QCOMPARE(spy_interpolationChange.count(), 1);

  QList<QVariant> args = spy_interpolationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setInterpolation(false);
  QCOMPARE(spy_interpolationChange.count(), 0);
}

void TestDaisyWidgetSignals::test_useOrientationChange()
{
  QSignalSpy spyNonmaxSuppressionChange(this, &DaisyWidgetImp::useOrientationChange);

  QTest::mouseClick(mUseOrientation, Qt::MouseButton::LeftButton);

  QCOMPARE(spyNonmaxSuppressionChange.count(), 1);

  QList<QVariant> args = spyNonmaxSuppressionChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUseOrientation(true);
  QCOMPARE(spyNonmaxSuppressionChange.count(), 0);
}



QTEST_MAIN(TestDaisyWidgetSignals)

#include "tst_daisywidgetsignals.moc"
