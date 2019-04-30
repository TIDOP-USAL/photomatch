#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/MsdWidget.h"

using namespace fme;

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
  void testThresholdSaliency_data();
  void testThresholdSaliency();
  void testPathRadius_data();
  void testPathRadius();
  void testKNN_data();
  void testKNN();
  void testAreaRadius_data();
  void testAreaRadius();
  void testScaleFactor_data();
  void testScaleFactor();
  void testNMSRadius_data();
  void testNMSRadius();
  void testNScales_data();
  void testNScales();
  void tstNMSScaleR_data();
  void tstNMSScaleR();
  void tstComputeOrientations_data();
  void tstComputeOrientations();
  void tstAffineMSD_data();
  void tstAffineMSD();
  void tstTilts_data();
  void tstTilts();
  void testReset();

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

void TestMsdWidget::testThresholdSaliency_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("100") << 100. << 100.;
  QTest::newRow("default") << 250. << 250.;
  QTest::newRow("2000") << 2000. << 2000.;
  QTest::newRow("Out of range value") << 2001. << 2000.;
}

void TestMsdWidget::testThresholdSaliency()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsdWidget->setThresholdSaliency(value);
  QCOMPARE(result, mMsdWidget->thresholdSaliency());
}

void TestMsdWidget::testPathRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 3 << 3;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::testPathRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setPathRadius(value);
  QCOMPARE(result, mMsdWidget->pathRadius());
}

void TestMsdWidget::testKNN_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 4 << 4;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::testKNN()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setKNN(value);
  QCOMPARE(result, mMsdWidget->knn());
}

void TestMsdWidget::testAreaRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::testAreaRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setAreaRadius(value);
  QCOMPARE(result, mMsdWidget->areaRadius());
}

void TestMsdWidget::testScaleFactor_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5") << 5. << 5.;
  QTest::newRow("default") << 1.25 << 1.25;
  QTest::newRow("10") << 10. << 10.;
  QTest::newRow("Out of range value") << 10.1 << 10.;
}

void TestMsdWidget::testScaleFactor()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsdWidget->setScaleFactor(value);
  QCOMPARE(result, mMsdWidget->scaleFactor());
}

void TestMsdWidget::testNMSRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::testNMSRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNMSRadius(value);
  QCOMPARE(result, mMsdWidget->NMSRadius());
}

void TestMsdWidget::testNScales_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << -1 << -1;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
  QTest::newRow("Out of range value 2") << -2 << -1;
}

void TestMsdWidget::testNScales()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNScales(value);
  QCOMPARE(result, mMsdWidget->nScales());
}

void TestMsdWidget::tstNMSScaleR_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("default") << 0 << 0;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
  QTest::newRow("Out of range value 2") << -1 << 0;
}

void TestMsdWidget::tstNMSScaleR()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setNMSScaleR(value);
  QCOMPARE(result, mMsdWidget->NMSScaleR());
}

void TestMsdWidget::tstComputeOrientations_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestMsdWidget::tstComputeOrientations()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mMsdWidget->setComputeOrientations(value);
  QCOMPARE(result, mMsdWidget->computeOrientations());
}

void TestMsdWidget::tstAffineMSD_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestMsdWidget::tstAffineMSD()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mMsdWidget->setAffineMSD(value);
  QCOMPARE(result, mMsdWidget->affineMSD());
}

void TestMsdWidget::tstTilts_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("5") << 5 << 5;
  QTest::newRow("default") << 3 << 3;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 11 << 10;
}

void TestMsdWidget::tstTilts()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mMsdWidget->setTilts(value);
  QCOMPARE(result, mMsdWidget->tilts());
}

void TestMsdWidget::testReset()
{
  mMsdWidget->setThresholdSaliency(200);
  mMsdWidget->setPathRadius(4);
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
