#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/WallisWidget.h"

#include <QSpinBox>

using namespace fme;

class TestWallisWidgetSignals : public WallisWidget
{
  Q_OBJECT

public:
  TestWallisWidgetSignals();
  ~TestWallisWidgetSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testContrast();
  void testBrightnessChange();
  void testImposedAverageChange();
  void testImposedLocalStdDevChange();
  void testKernelSizeChange();
  void testReset();
};

TestWallisWidgetSignals::TestWallisWidgetSignals()
  : WallisWidget()
{

}

TestWallisWidgetSignals::~TestWallisWidgetSignals()
{

}

void TestWallisWidgetSignals::initTestCase()
{

}

void TestWallisWidgetSignals::cleanupTestCase()
{

}

void TestWallisWidgetSignals::testContrast()
{
  QSignalSpy spyContrast(this, &WallisWidget::contrastChange);

  this->mContrast->setValue(0.5);

  QCOMPARE(spyContrast.count(), 1);

  QList<QVariant> args = spyContrast.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setContrast(0.3);
  QCOMPARE(spyContrast.count(), 0);
}

void TestWallisWidgetSignals::testBrightnessChange()
{
  QSignalSpy spyBrightnessChange(this, &WallisWidget::brightnessChange);

  this->mBrightness->setValue(0.5);

  QCOMPARE(spyBrightnessChange.count(), 1);

  QList<QVariant> args = spyBrightnessChange.takeFirst();
  QCOMPARE(args.at(0).toDouble(), 0.5);

  this->setBrightness(0.3);
  QCOMPARE(spyBrightnessChange.count(), 0);
}

void TestWallisWidgetSignals::testImposedAverageChange()
{
  QSignalSpy spyImposedAverageChange(this, &WallisWidget::imposedAverageChange);

  this->mImposedAverage->setValue(25);

  QCOMPARE(spyImposedAverageChange.count(), 1);

  QList<QVariant> args = spyImposedAverageChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 25);

  this->setImposedAverage(30);
  QCOMPARE(spyImposedAverageChange.count(), 0);
}

void TestWallisWidgetSignals::testImposedLocalStdDevChange()
{
  QSignalSpy spyImposedLocalStdDevChange(this, &WallisWidget::imposedLocalStdDevChange);

  this->mImposedLocalStdDev->setValue(25);

  QCOMPARE(spyImposedLocalStdDevChange.count(), 1);

  QList<QVariant> args = spyImposedLocalStdDevChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 25);

  this->setImposedLocalStdDev(30);
  QCOMPARE(spyImposedLocalStdDevChange.count(), 0);
}

void TestWallisWidgetSignals::testKernelSizeChange()
{
  QSignalSpy spyLocalStdDevChange(this, &WallisWidget::kernelSizeChange);

  this->mKernelSize->setValue(25);

  QCOMPARE(spyLocalStdDevChange.count(), 1);

  QList<QVariant> args = spyLocalStdDevChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 25);

  this->setKernelSize(30);
  QCOMPARE(spyLocalStdDevChange.count(), 0);
}

void TestWallisWidgetSignals::testReset()
{
  QSignalSpy spyContrast(this, &WallisWidget::contrastChange);
  QSignalSpy spyBrightnessChange(this, &WallisWidget::brightnessChange);
  QSignalSpy spyImposedAverageChange(this, &WallisWidget::imposedAverageChange);
  QSignalSpy spyImposedLocalStdDevChange(this, &WallisWidget::imposedLocalStdDevChange);
  QSignalSpy spyLocalStdDevChange(this, &WallisWidget::kernelSizeChange);

  this->setContrast(0.3);
  this->setBrightness(0.3);
  this->setImposedAverage(30);
  this->setImposedLocalStdDev(30);
  this->setKernelSize(30);

  this->reset();

  QCOMPARE(spyContrast.count(), 0);
  QCOMPARE(spyBrightnessChange.count(), 0);
  QCOMPARE(spyImposedAverageChange.count(), 0);
  QCOMPARE(spyImposedLocalStdDevChange.count(), 0);
  QCOMPARE(spyLocalStdDevChange.count(), 0);
}


QTEST_MAIN(TestWallisWidgetSignals)

#include "tst_walliswidgetsignals.moc"
