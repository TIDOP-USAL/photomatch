#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/SurfWidget.h"

using namespace photomatch;

class TestSurfWidget : public QObject
{
  Q_OBJECT

public:
  TestSurfWidget();
  ~TestSurfWidget();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_windowTitle();
  void test_hessianThreshold_data();
  void test_hessianThreshold();
  void test_octaves_data();
  void test_octaves();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_extendedDescriptor_data();
  void test_extendedDescriptor();
  void test_rotatedFeatures_data();
  void test_rotatedFeatures();
  void test_reset();

private:

  ISurfWidget *mSurfWidget;

};

TestSurfWidget::TestSurfWidget()
{
  mSurfWidget = new SurfWidget();
}

TestSurfWidget::~TestSurfWidget()
{
  if (mSurfWidget){
    delete mSurfWidget;
    mSurfWidget = nullptr;
  }
}

void TestSurfWidget::initTestCase()
{

}

void TestSurfWidget::cleanupTestCase()
{

}

void TestSurfWidget::test_constructor()
{
  /// Check default values
  QCOMPARE(100, mSurfWidget->hessianThreshold());
  QCOMPARE(4, mSurfWidget->octaves());
  QCOMPARE(3, mSurfWidget->octaveLayers());
  QCOMPARE(false, mSurfWidget->extendedDescriptor());
  QCOMPARE(false, mSurfWidget->upright());
}

void TestSurfWidget::test_windowTitle()
{
  QCOMPARE("SURF", mSurfWidget->windowTitle());
}

void TestSurfWidget::test_hessianThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("50") << 50 << 50;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("200") << 200 << 200;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestSurfWidget::test_hessianThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setHessianThreshold(value);
  QCOMPARE(result, mSurfWidget->hessianThreshold());
}

void TestSurfWidget::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSurfWidget::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setOctaves(value);
  QCOMPARE(result, mSurfWidget->octaves());
}

void TestSurfWidget::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSurfWidget::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setOctaveLayers(value);
  QCOMPARE(result, mSurfWidget->octaveLayers());
}

void TestSurfWidget::test_extendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfWidget::test_extendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mSurfWidget->setExtendedDescriptor(value);
  QCOMPARE(result, mSurfWidget->extendedDescriptor());
}

void TestSurfWidget::test_rotatedFeatures_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfWidget::test_rotatedFeatures()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mSurfWidget->seUpright(value);
  QCOMPARE(result, mSurfWidget->upright());
}

void TestSurfWidget::test_reset()
{
  mSurfWidget->setHessianThreshold(50.);
  mSurfWidget->setOctaves(2);
  mSurfWidget->setOctaveLayers(5);
  mSurfWidget->setExtendedDescriptor(true);
  mSurfWidget->seUpright(true);

  mSurfWidget->reset();

  QCOMPARE(100, mSurfWidget->hessianThreshold());
  QCOMPARE(4, mSurfWidget->octaves());
  QCOMPARE(3, mSurfWidget->octaveLayers());
  QCOMPARE(false, mSurfWidget->extendedDescriptor());
  QCOMPARE(false, mSurfWidget->upright());
}

QTEST_MAIN(TestSurfWidget)

#include "tst_surfwidget.moc"
