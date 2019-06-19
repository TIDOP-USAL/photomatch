#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/FastWidget.h"

using namespace fme;

class TestFastWidget : public QObject
{
  Q_OBJECT

public:

  TestFastWidget();
  ~TestFastWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void testThreshold_data();
  void testThreshold();
  void testNonmaxSuppression_data();
  void testNonmaxSuppression();
  void testDetectorType_data();
  void testDetectorType();
  void testReset();

private:

  IFastWidget *mFastWidget;
};

TestFastWidget::TestFastWidget()
  : mFastWidget(new FastWidget)
{

}

TestFastWidget::~TestFastWidget()
{
  if (mFastWidget){
    delete mFastWidget;
    mFastWidget = nullptr;
  }
}

void TestFastWidget::initTestCase()
{

}

void TestFastWidget::cleanupTestCase()
{

}

void TestFastWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(10, mFastWidget->threshold());
  QCOMPARE("TYPE_9_16", mFastWidget->detectorType());
  QCOMPARE(true, mFastWidget->nonmaxSuppression());
}

void TestFastWidget::test_windowTitle()
{
  QCOMPARE("FAST", mFastWidget->windowTitle());
}

void TestFastWidget::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestFastWidget::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mFastWidget->setThreshold(value);
  QCOMPARE(result, mFastWidget->threshold());
}

void TestFastWidget::testNonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestFastWidget::testNonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFastWidget->setNonmaxSuppression(value);
  QCOMPARE(result, mFastWidget->nonmaxSuppression());
}

void TestFastWidget::testDetectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << "TYPE_5_8";
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << "TYPE_7_12";
  QTest::newRow("TYPE_7_12") << "TYPE_9_16" << "TYPE_9_16";
  QTest::newRow("bad_value") << "bad_value" << "TYPE_9_16";
}

void TestFastWidget::testDetectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mFastWidget->setDetectorType(value);
  QCOMPARE(result, mFastWidget->detectorType());
}

void TestFastWidget::testReset()
{
  mFastWidget->setThreshold(3);
  mFastWidget->setDetectorType("TYPE_7_12");
  mFastWidget->setNonmaxSuppression(false);

  mFastWidget->reset();

  QCOMPARE(10, mFastWidget->threshold());
  QCOMPARE("TYPE_9_16", mFastWidget->detectorType());
  QCOMPARE(true, mFastWidget->nonmaxSuppression());
}

QTEST_MAIN(TestFastWidget)

#include "tst_fastwidget.moc"
