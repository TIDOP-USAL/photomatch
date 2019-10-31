#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/MsdWidget.h"

using namespace photomatch;

class TestMsdWidget : public QObject
{
  Q_OBJECT

public:
  TestMsdWidget();
  ~TestMsdWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void test_thresholdSaliency_data();
  void test_thresholdSaliency();
  void test_pathRadius_data();
  void test_pathRadius();
  void test_knn_data();
  void test_knn();
  void test_areaRadius_data();
  void test_areaRadius();
  void test_scaleFactor_data();
  void test_scaleFactor();
  void test_NMSRadius_data();
  void test_NMSRadius();
  void test_nScales_data();
  void test_nScales();
  void test_nmsScaleR_data();
  void test_nmsScaleR();
  void test_computeOrientations_data();
  void test_computeOrientations();
  void test_affineMSD_data();
  void test_affineMSD();
  void test_tilts_data();
  void test_tilts();
  void test_Reset();

protected:

  IMsdWidget *mMsdWidget;

};

TestMsdWidget::TestMsdWidget()
  : mMsdWidget(new MsdWidget)
{

}

TestMsdWidget::~TestMsdWidget()
{
  delete mMsdWidget;
  mMsdWidget = nullptr;
}

void TestMsdWidget::initTestCase()
{

}

void TestMsdWidget::cleanupTestCase()
{

}

void TestMsdWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(250, mMsdWidget->thresholdSaliency());
  QCOMPARE(3, mMsdWidget->pathRadius());
  QCOMPARE(4, mMsdWidget->knn());
  QCOMPARE(5, mMsdWidget->areaRadius());
  QCOMPARE(1.25, mMsdWidget->scaleFactor());
  QCOMPARE(5, mMsdWidget->NMSRadius());
  QCOMPARE(-1, mMsdWidget->nScales());
  QCOMPARE(0, mMsdWidget->NMSScaleR());
  QCOMPARE(false, mMsdWidget->computeOrientations());
  QCOMPARE(false, mMsdWidget->affineMSD());
  QCOMPARE(3, mMsdWidget->tilts());
}

void TestMsdWidget::test_windowTitle()
{
  QCOMPARE("MSD", mMsdWidget->windowTitle());
}

void TestMsdWidget::test_thresholdSaliency_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 100. << 100.;
  QTest::newRow("default") << 250. << 250.;
  QTest::newRow("2000") << 2000. << 2000.;
  QTest::newRow("Out of range value") << 2001. << 2000.;
}

void TestMsdWidget::test_thresholdSaliency()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsdWidget->setThresholdSaliency(value);
  QCOMPARE(result, mMsdWidget->thresholdSaliency());
}

void TestMsdWidget::test_pathRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 3 << 3;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::test_pathRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setPatchRadius(value);
  QCOMPARE(result, mMsdWidget->pathRadius());
}

void TestMsdWidget::test_knn_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 4 << 4;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::test_knn()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setKNN(value);
  QCOMPARE(result, mMsdWidget->knn());
}

void TestMsdWidget::test_areaRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::test_areaRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setAreaRadius(value);
  QCOMPARE(result, mMsdWidget->areaRadius());
}

void TestMsdWidget::test_scaleFactor_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5") << 5. << 5.;
  QTest::newRow("default") << 1.25 << 1.25;
  QTest::newRow("10") << 10. << 10.;
  QTest::newRow("Out of range value") << 10.1 << 10.;
}

void TestMsdWidget::test_scaleFactor()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsdWidget->setScaleFactor(value);
  QCOMPARE(result, mMsdWidget->scaleFactor());
}

void TestMsdWidget::test_NMSRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::test_NMSRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNMSRadius(value);
  QCOMPARE(result, mMsdWidget->NMSRadius());
}

void TestMsdWidget::test_nScales_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << -1 << -1;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
  QTest::newRow("Out of range value 2") << -2 << -1;
}

void TestMsdWidget::test_nScales()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNScales(value);
  QCOMPARE(result, mMsdWidget->nScales());
}

void TestMsdWidget::test_nmsScaleR_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 0 << 0;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
  QTest::newRow("Out of range value 2") << -1 << 0;
}

void TestMsdWidget::test_nmsScaleR()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNMSScaleR(value);
  QCOMPARE(result, mMsdWidget->NMSScaleR());
}

void TestMsdWidget::test_computeOrientations_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestMsdWidget::test_computeOrientations()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mMsdWidget->setComputeOrientations(value);
  QCOMPARE(result, mMsdWidget->computeOrientations());
}

void TestMsdWidget::test_affineMSD_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestMsdWidget::test_affineMSD()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mMsdWidget->setAffineMSD(value);
  QCOMPARE(result, mMsdWidget->affineMSD());
}

void TestMsdWidget::test_tilts_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 3 << 3;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::test_tilts()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setTilts(value);
  QCOMPARE(result, mMsdWidget->tilts());
}

void TestMsdWidget::test_Reset()
{
  mMsdWidget->setThresholdSaliency(200);
  mMsdWidget->setPatchRadius(4);
  mMsdWidget->setKNN(5);
  mMsdWidget->setAreaRadius(3);
  mMsdWidget->setScaleFactor(1.5);
  mMsdWidget->setNMSRadius(4);
  mMsdWidget->setNScales(3);
  mMsdWidget->setNMSScaleR(1);
  mMsdWidget->setComputeOrientations(true);
  mMsdWidget->setAffineMSD(true);
  mMsdWidget->setTilts(4);

  mMsdWidget->reset();

  QCOMPARE(250, mMsdWidget->thresholdSaliency());
  QCOMPARE(3, mMsdWidget->pathRadius());
  QCOMPARE(4, mMsdWidget->knn());
  QCOMPARE(5, mMsdWidget->areaRadius());
  QCOMPARE(1.25, mMsdWidget->scaleFactor());
  QCOMPARE(5, mMsdWidget->NMSRadius());
  QCOMPARE(-1, mMsdWidget->nScales());
  QCOMPARE(0, mMsdWidget->NMSScaleR());
  QCOMPARE(false, mMsdWidget->computeOrientations());
  QCOMPARE(false, mMsdWidget->affineMSD());
  QCOMPARE(3, mMsdWidget->tilts());
}

QTEST_MAIN(TestMsdWidget)

#include "tst_msdwidget.moc"
