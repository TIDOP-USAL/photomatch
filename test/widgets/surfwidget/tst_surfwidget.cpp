#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/SurfWidget.h"

using namespace fme;

class TestSurfWidget : public QObject
{
  Q_OBJECT

public:
  TestSurfWidget();
  ~TestSurfWidget();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void testHessianThreshold_data();
  void testHessianThreshold();
  void testOctaves_data();
  void testOctaves();
  void testOctaveLayers_data();
  void testOctaveLayers();
  void testExtendedDescriptor_data();
  void testExtendedDescriptor();
  void testRotatedFeatures_data();
  void testRotatedFeatures();
  void testReset();

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

void TestSurfWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(100, mSurfWidget->hessianThreshold());
  QCOMPARE(4, mSurfWidget->octaves());
  QCOMPARE(3, mSurfWidget->octaveLayers());
  QCOMPARE(false, mSurfWidget->extendedDescriptor());
  QCOMPARE(false, mSurfWidget->rotatedFeatures());
}

void TestSurfWidget::test_windowTitle()
{
  QCOMPARE("SURF", mSurfWidget->windowTitle());
}

void TestSurfWidget::testHessianThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("50") << 50 << 50;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("200") << 200 << 200;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestSurfWidget::testHessianThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setHessianThreshold(value);
  QCOMPARE(result, mSurfWidget->hessianThreshold());
}

void TestSurfWidget::testOctaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSurfWidget::testOctaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setOctaves(value);
  QCOMPARE(result, mSurfWidget->octaves());
}

void TestSurfWidget::testOctaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSurfWidget::testOctaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSurfWidget->setOctaveLayers(value);
  QCOMPARE(result, mSurfWidget->octaveLayers());
}

void TestSurfWidget::testExtendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfWidget::testExtendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mSurfWidget->setExtendedDescriptor(value);
  QCOMPARE(result, mSurfWidget->extendedDescriptor());
}

void TestSurfWidget::testRotatedFeatures_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestSurfWidget::testRotatedFeatures()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mSurfWidget->setRotatedFeatures(value);
  QCOMPARE(result, mSurfWidget->rotatedFeatures());
}

void TestSurfWidget::testReset()
{
  mSurfWidget->setHessianThreshold(50.);
  mSurfWidget->setOctaves(2);
  mSurfWidget->setOctaveLayers(5);
  mSurfWidget->setExtendedDescriptor(true);
  mSurfWidget->setRotatedFeatures(true);

  mSurfWidget->reset();

  QCOMPARE(100, mSurfWidget->hessianThreshold());
  QCOMPARE(4, mSurfWidget->octaves());
  QCOMPARE(3, mSurfWidget->octaveLayers());
  QCOMPARE(false, mSurfWidget->extendedDescriptor());
  QCOMPARE(false, mSurfWidget->rotatedFeatures());
}

QTEST_MAIN(TestSurfWidget)

#include "tst_surfwidget.moc"
