#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/OrbWidget.h"

using namespace photomatch;

class TestOrbWidget : public QObject
{
  Q_OBJECT

public:

  TestOrbWidget();
  ~TestOrbWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_windowTitle();
  void test_featuresNumber_data();
  void test_featuresNumber();
  void test_scaleFactor();
  void test_levelsNumber();
  void test_edgeThreshold();
  void test_wTA_K();
  void test_scoreType();
  void test_patchSize();
  void test_fastThreshold();
  void test_reset();

private:

  IOrbWidget *mOrbWidget;
};

TestOrbWidget::TestOrbWidget()
  : mOrbWidget(new OrbWidget())
{

}

TestOrbWidget::~TestOrbWidget()
{
  if (mOrbWidget){
    delete mOrbWidget;
    mOrbWidget = nullptr;
  }
}

void TestOrbWidget::initTestCase()
{
}

void TestOrbWidget::cleanupTestCase()
{

}

void TestOrbWidget::test_constructor()
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

void TestOrbWidget::test_windowTitle()
{
  QCOMPARE("ORB", mOrbWidget->windowTitle());
}

void TestOrbWidget::test_featuresNumber_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("20000") << 20000 << 20000;
  QTest::newRow("Out of range value") << 50001 << 50000;
}

void TestOrbWidget::test_featuresNumber()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mOrbWidget->setFeaturesNumber(value);
  QCOMPARE(result, mOrbWidget->featuresNumber());
}

void TestOrbWidget::test_scaleFactor()
{
  mOrbWidget->setScaleFactor(1.5);
  QCOMPARE(1.5, mOrbWidget->scaleFactor());

  /// Out of range value
  mOrbWidget->setScaleFactor(120.);
  QCOMPARE(100., mOrbWidget->scaleFactor());

  mOrbWidget->setScaleFactor(0.5);
  QCOMPARE(1., mOrbWidget->scaleFactor());
}

void TestOrbWidget::test_levelsNumber()
{
  mOrbWidget->setLevelsNumber(4);
  QCOMPARE(4, mOrbWidget->levelsNumber());

  /// Out of range value
  mOrbWidget->setLevelsNumber(120);
  QCOMPARE(100, mOrbWidget->levelsNumber());
}

void TestOrbWidget::test_edgeThreshold()
{
  mOrbWidget->setEdgeThreshold(11);
  QCOMPARE(11, mOrbWidget->edgeThreshold());

  /// Out of range value
  mOrbWidget->setEdgeThreshold(120);
  QCOMPARE(100, mOrbWidget->edgeThreshold());
}

void TestOrbWidget::test_wTA_K()
{
  mOrbWidget->setWTA_K(3);
  QCOMPARE(3, mOrbWidget->wta_k());

  /// Out of range value
  mOrbWidget->setWTA_K(1);
  QCOMPARE(2, mOrbWidget->wta_k());

  mOrbWidget->setWTA_K(5);
  QCOMPARE(4, mOrbWidget->wta_k());
}

void TestOrbWidget::test_scoreType()
{
  mOrbWidget->setScoreType("FAST");
  QCOMPARE("FAST", mOrbWidget->scoreType());

  /// invalid value
  mOrbWidget->setScoreType("invalid");
  QCOMPARE("FAST", mOrbWidget->scoreType());

}

void TestOrbWidget::test_patchSize()
{
  mOrbWidget->setPatchSize(3);
  QCOMPARE(3, mOrbWidget->patchSize());

  /// Out of range value
  mOrbWidget->setPatchSize(120);
  QCOMPARE(100, mOrbWidget->patchSize());
}

void TestOrbWidget::test_fastThreshold()
{
  mOrbWidget->setFastThreshold(3);
  QCOMPARE(3, mOrbWidget->fastThreshold());

  /// Out of range value
  mOrbWidget->setFastThreshold(120);
  QCOMPARE(100, mOrbWidget->fastThreshold());
}

void TestOrbWidget::test_reset()
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
