#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/FreakWidget.h"

#include <QSpinBox>
#include <QCheckBox>

using namespace photomatch;

class TestFreakWidgetSignals : public FreakWidget
{
  Q_OBJECT

public:
  TestFreakWidgetSignals();
  ~TestFreakWidgetSignals();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_orientationNormalizedChange();
  void test_scaleNormalizedChange();
  void test_patternScaleChange();
  void test_octavesChange();
  void test_reset();

};

TestFreakWidgetSignals::TestFreakWidgetSignals()
  : FreakWidget()
{

}

TestFreakWidgetSignals::~TestFreakWidgetSignals()
{

}

void TestFreakWidgetSignals::initTestCase()
{

}

void TestFreakWidgetSignals::cleanupTestCase()
{

}

void TestFreakWidgetSignals::test_orientationNormalizedChange()
{
  QSignalSpy spy_orientationNormalizedChange(this, &FreakWidget::orientationNormalizedChange);

  QTest::mouseClick(mOrientationNormalized, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_orientationNormalizedChange.count(), 1);

  QList<QVariant> args = spy_orientationNormalizedChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setOrientationNormalized(false);
  QCOMPARE(spy_orientationNormalizedChange.count(), 0);
}

void TestFreakWidgetSignals::test_scaleNormalizedChange()
{
  QSignalSpy spy_scaleNormalizedChange(this, &FreakWidget::scaleNormalizedChange);

  QTest::mouseClick(mScaleNormalized, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_scaleNormalizedChange.count(), 1);

  QList<QVariant> args = spy_scaleNormalizedChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), false);

  this->setScaleNormalized(false);
  QCOMPARE(spy_scaleNormalizedChange.count(), 0);
}

void TestFreakWidgetSignals::test_patternScaleChange()
{
  QSignalSpy spy_patternScaleChange(this, &FreakWidget::patternScaleChange);

  mPatternScale->setValue(25.);

  QCOMPARE(spy_patternScaleChange.count(), 1);

  QList<QVariant> args = spy_patternScaleChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 25.);

  this->setPatternScale(120.);
  QCOMPARE(spy_patternScaleChange.count(), 0);
}

void TestFreakWidgetSignals::test_octavesChange()
{
  QSignalSpy spy_octavesChange(this, &FreakWidget::octavesChange);

  mOctaves->setValue(8);

  QCOMPARE(spy_octavesChange.count(), 1);

  QList<QVariant> args = spy_octavesChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 8);

  this->setOctaves(4);
  QCOMPARE(spy_octavesChange.count(), 0);
}

void TestFreakWidgetSignals::test_reset()
{
  QSignalSpy spy_orientationNormalizedChange(this, &FreakWidget::orientationNormalizedChange);
  QSignalSpy spy_scaleNormalizedChange(this, &FreakWidget::scaleNormalizedChange);
  QSignalSpy spy_patternScaleChange(this, &FreakWidget::patternScaleChange);
  QSignalSpy spy_octavesChange(this, &FreakWidget::octavesChange);

  this->setOrientationNormalized(false);
  this->setScaleNormalized(false);
  this->setPatternScale(100.);
  this->setOctaves(3);

  this->reset();

  QCOMPARE(spy_orientationNormalizedChange.count(), 0);
  QCOMPARE(spy_scaleNormalizedChange.count(), 0);
  QCOMPARE(spy_patternScaleChange.count(), 0);
  QCOMPARE(spy_octavesChange.count(), 0);
}

QTEST_MAIN(TestFreakWidgetSignals)

#include "tst_freakwidgetsignals.moc"
