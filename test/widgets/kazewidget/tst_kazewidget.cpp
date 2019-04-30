#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/KazeWidget.h"

using namespace fme;

class TestKazeWidget : public QObject
{
  Q_OBJECT

public:
  TestKazeWidget();
  ~TestKazeWidget();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testExtendedDescriptor_data();
  void testExtendedDescriptor();
  void testUpright_data();
  void testUpright();
  void testThreshold_data();
  void testThreshold();
  void testOctaves_data();
  void testOctaves();
  void testOctaveLayers_data();
  void testOctaveLayers();
  void testDiffusivity_data();
  void testDiffusivity();
  void testReset();

private:

  IKazeWidget *mKazeWidget;

};

TestKazeWidget::TestKazeWidget()
{
  mKazeWidget = new KazeWidget();
}

TestKazeWidget::~TestKazeWidget()
{
  if (mKazeWidget){
    delete mKazeWidget;
    mKazeWidget = nullptr;
  }
}

void TestKazeWidget::initTestCase()
{

}

void TestKazeWidget::cleanupTestCase()
{

}

void TestKazeWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(false, mKazeWidget->extendedDescriptor());
  QCOMPARE(false, mKazeWidget->upright());
  QCOMPARE(0.001, mKazeWidget->threshold());
  QCOMPARE(4, mKazeWidget->octaves());
  QCOMPARE(4, mKazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mKazeWidget->diffusivity());
}

void TestKazeWidget::testExtendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeWidget::testExtendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeWidget->setExtendedDescriptor(value);
  QCOMPARE(result, mKazeWidget->extendedDescriptor());
}

void TestKazeWidget::testUpright_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeWidget::testUpright()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeWidget->setUpright(value);
  QCOMPARE(result, mKazeWidget->upright());
}

void TestKazeWidget::testThreshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 100. << 99.99;
}

void TestKazeWidget::testThreshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mKazeWidget->setThreshold(value);
  QCOMPARE(result, mKazeWidget->threshold());
}

void TestKazeWidget::testOctaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestKazeWidget::testOctaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeWidget->setOctaves(value);
  QCOMPARE(result, mKazeWidget->octaves());
}

void TestKazeWidget::testOctaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestKazeWidget::testOctaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeWidget->setOctaveLayers(value);
  QCOMPARE(result, mKazeWidget->octaveLayers());
}

void TestKazeWidget::testDiffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestKazeWidget::testDiffusivity()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mKazeWidget->setDiffusivity(value);
  QCOMPARE(result, mKazeWidget->diffusivity());
}

void TestKazeWidget::testReset()
{
  mKazeWidget->setThreshold(50.);
  mKazeWidget->setOctaves(2);
  mKazeWidget->setOctaveLayers(5);
  mKazeWidget->setExtendedDescriptor(true);
  mKazeWidget->setUpright(true);
  mKazeWidget->setDiffusivity("DIFF_PM_G1");

  mKazeWidget->reset();

  QCOMPARE(false, mKazeWidget->extendedDescriptor());
  QCOMPARE(false, mKazeWidget->upright());
  QCOMPARE(0.001, mKazeWidget->threshold());
  QCOMPARE(4, mKazeWidget->octaves());
  QCOMPARE(4, mKazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mKazeWidget->diffusivity());
}

QTEST_MAIN(TestKazeWidget)

#include "tst_kazewidget.moc"
