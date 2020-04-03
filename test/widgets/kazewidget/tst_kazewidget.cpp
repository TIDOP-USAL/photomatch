#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/KazeWidget.h"

using namespace photomatch;

class TestKazeWidget : public QObject
{
  Q_OBJECT

public:

  TestKazeWidget();
  ~TestKazeWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_extendedDescriptor_data();
  void test_extendedDescriptor();
  void test_upright_data();
  void test_upright();
  void test_threshold_data();
  void test_threshold();
  void test_octaves_data();
  void test_octaves();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_diffusivity_data();
  void test_diffusivity();

private:

  KazeWidget *mKazeWidget;

};

TestKazeWidget::TestKazeWidget()
{
  mKazeWidget = new KazeWidgetImp();
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
  /// Check default values
  QCOMPARE(false, mKazeWidget->extendedDescriptor());
  QCOMPARE(false, mKazeWidget->uprightDescriptor());
  QCOMPARE(0.001, mKazeWidget->threshold());
  QCOMPARE(4, mKazeWidget->octaves());
  QCOMPARE(4, mKazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mKazeWidget->diffusivity());
}

void TestKazeWidget::cleanupTestCase()
{
  mKazeWidget->setThreshold(50.);
  mKazeWidget->setOctaves(2);
  mKazeWidget->setOctaveLayers(5);
  mKazeWidget->setExtendedDescriptor(true);
  mKazeWidget->setUprightDescriptor(true);
  mKazeWidget->setDiffusivity("DIFF_PM_G1");

  mKazeWidget->reset();

  QCOMPARE(false, mKazeWidget->extendedDescriptor());
  QCOMPARE(false, mKazeWidget->uprightDescriptor());
  QCOMPARE(0.001, mKazeWidget->threshold());
  QCOMPARE(4, mKazeWidget->octaves());
  QCOMPARE(4, mKazeWidget->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mKazeWidget->diffusivity());
}

void TestKazeWidget::test_windowTitle()
{
  QCOMPARE("KAZE", mKazeWidget->windowTitle());
}

void TestKazeWidget::test_extendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeWidget::test_extendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeWidget->setExtendedDescriptor(value);
  QCOMPARE(result, mKazeWidget->extendedDescriptor());
}

void TestKazeWidget::test_upright_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeWidget::test_upright()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeWidget->setUprightDescriptor(value);
  QCOMPARE(result, mKazeWidget->uprightDescriptor());
}

void TestKazeWidget::test_threshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 100. << 99.99;
}

void TestKazeWidget::test_threshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mKazeWidget->setThreshold(value);
  QCOMPARE(result, mKazeWidget->threshold());
}

void TestKazeWidget::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestKazeWidget::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeWidget->setOctaves(value);
  QCOMPARE(result, mKazeWidget->octaves());
}

void TestKazeWidget::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestKazeWidget::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeWidget->setOctaveLayers(value);
  QCOMPARE(result, mKazeWidget->octaveLayers());
}

void TestKazeWidget::test_diffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestKazeWidget::test_diffusivity()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mKazeWidget->setDiffusivity(value);
  QCOMPARE(result, mKazeWidget->diffusivity());
}


QTEST_MAIN(TestKazeWidget)

#include "tst_kazewidget.moc"
