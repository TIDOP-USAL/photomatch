#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/OrbWidget.h"

using namespace fme;

class TestOrbWidget : public QObject
{
  Q_OBJECT

public:

  TestOrbWidget();
  ~TestOrbWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testFeaturesNumber_data();
  void testFeaturesNumber();
  void testScaleFactor();
  void testLevelsNumber();
  void testEdgeThreshold();
  void testWTA_K();
  void testScoreType();
  void testPatchSize();
  void testFastThreshold();
  void testReset();

private:

  IOrbWidget *mOrbWidget;
};

TestOrbWidget::TestOrbWidget()
{

}

TestOrbWidget::~TestOrbWidget()
{

}

void TestOrbWidget::initTestCase()
{
  mOrbWidget = new OrbWidget();
}

void TestOrbWidget::cleanupTestCase()
{
  if (mOrbWidget){
    delete mOrbWidget;
    mOrbWidget = nullptr;
  }
}

void TestOrbWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(5000, mOrbWidget->featuresNumber());
  QCOMPARE(1.2, mOrbWidget->scaleFactor());
  QCOMPARE(8, mOrbWidget->levelsNumber());
  QCOMPARE(31, mOrbWidget->edgeThreshold());
  QCOMPARE(2, mOrbWidget->wta_k());
  QCOMPARE("Harris", mOrbWidget->scoreType());
  QCOMPARE(31, mOrbWidget->patchSize());
  QCOMPARE(20, mOrbWidget->fastThreshold());
}

void TestOrbWidget::testFeaturesNumber_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("20000") << 20000 << 20000;
  QTest::newRow("Out of range value") << 50001 << 50000;
}

void TestOrbWidget::testFeaturesNumber()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mOrbWidget->setFeaturesNumber(value);
  QCOMPARE(result, mOrbWidget->featuresNumber());
}

void TestOrbWidget::testScaleFactor()
{
  mOrbWidget->setScaleFactor(1.5);
  QCOMPARE(1.5, mOrbWidget->scaleFactor());

  /// Out of range value
  mOrbWidget->setScaleFactor(120.);
  QCOMPARE(100., mOrbWidget->scaleFactor());

  mOrbWidget->setScaleFactor(0.5);
  QCOMPARE(1., mOrbWidget->scaleFactor());
}

void TestOrbWidget::testLevelsNumber()
{
  mOrbWidget->setLevelsNumber(4);
  QCOMPARE(4, mOrbWidget->levelsNumber());

  /// Out of range value
  mOrbWidget->setLevelsNumber(120);
  QCOMPARE(100, mOrbWidget->levelsNumber());
}

void TestOrbWidget::testEdgeThreshold()
{
  mOrbWidget->setEdgeThreshold(11);
  QCOMPARE(11, mOrbWidget->edgeThreshold());

  /// Out of range value
  mOrbWidget->setEdgeThreshold(120);
  QCOMPARE(100, mOrbWidget->edgeThreshold());
}

void TestOrbWidget::testWTA_K()
{
  mOrbWidget->setWTA_K(3);
  QCOMPARE(3, mOrbWidget->wta_k());

  /// Out of range value
  mOrbWidget->setWTA_K(1);
  QCOMPARE(2, mOrbWidget->wta_k());

  mOrbWidget->setWTA_K(5);
  QCOMPARE(4, mOrbWidget->wta_k());
}

void TestOrbWidget::testScoreType()
{
  mOrbWidget->setScoreType("FAST");
  QCOMPARE("FAST", mOrbWidget->scoreType());

  /// invalid value
  mOrbWidget->setScoreType("invalid");
  QCOMPARE("FAST", mOrbWidget->scoreType());

}

void TestOrbWidget::testPatchSize()
{
  mOrbWidget->setPatchSize(3);
  QCOMPARE(3, mOrbWidget->patchSize());

  /// Out of range value
  mOrbWidget->setPatchSize(120);
  QCOMPARE(100, mOrbWidget->patchSize());
}

void TestOrbWidget::testFastThreshold()
{
  mOrbWidget->setFastThreshold(3);
  QCOMPARE(3, mOrbWidget->fastThreshold());

  /// Out of range value
  mOrbWidget->setFastThreshold(120);
  QCOMPARE(100, mOrbWidget->fastThreshold());
}

void TestOrbWidget::testReset()
{
  mOrbWidget->setFeaturesNumber(10000);
  mOrbWidget->setScaleFactor(1.5);
  mOrbWidget->setLevelsNumber(4);
  mOrbWidget->setEdgeThreshold(11);
  mOrbWidget->setWTA_K(3);
  mOrbWidget->setScoreType("FAST");
  mOrbWidget->setPatchSize(3);
  mOrbWidget->setFastThreshold(3);

  mOrbWidget->reset();

  QCOMPARE(5000, mOrbWidget->featuresNumber());
  QCOMPARE(1.2, mOrbWidget->scaleFactor());
  QCOMPARE(8, mOrbWidget->levelsNumber());
  QCOMPARE(31, mOrbWidget->edgeThreshold());
  QCOMPARE(2, mOrbWidget->wta_k());
  QCOMPARE("Harris", mOrbWidget->scoreType());
  QCOMPARE(31, mOrbWidget->patchSize());
  QCOMPARE(20, mOrbWidget->fastThreshold());

}

QTEST_MAIN(TestOrbWidget)

#include "tst_orbwidget.moc"