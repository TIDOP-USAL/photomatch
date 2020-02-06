#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/FastWidget.h"

using namespace photomatch;

class TestFastWidget : public QObject
{
  Q_OBJECT

public:

  TestFastWidget();
  ~TestFastWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_threshold_data();
  void test_threshold();
  void test_nonmaxSuppression_data();
  void test_nonmaxSuppression();
  void test_detectorType_data();
  void test_detectorType();

private:

  FastWidget *mFastWidget;
};

TestFastWidget::TestFastWidget()
  : mFastWidget(new FastWidgetImp)
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
  /// Check default values
  QCOMPARE(10, mFastWidget->threshold());
  QCOMPARE("TYPE_9_16", mFastWidget->detectorType());
  QCOMPARE(true, mFastWidget->nonmaxSuppression());
}

void TestFastWidget::cleanupTestCase()
{
  mFastWidget->setThreshold(3);
  mFastWidget->setDetectorType("TYPE_7_12");
  mFastWidget->setNonmaxSuppression(false);

  mFastWidget->reset();

  QCOMPARE(10, mFastWidget->threshold());
  QCOMPARE("TYPE_9_16", mFastWidget->detectorType());
  QCOMPARE(true, mFastWidget->nonmaxSuppression());
}

void TestFastWidget::test_windowTitle()
{
  QCOMPARE("FAST", mFastWidget->windowTitle());
}

void TestFastWidget::test_threshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestFastWidget::test_threshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mFastWidget->setThreshold(value);
  QCOMPARE(result, mFastWidget->threshold());
}

void TestFastWidget::test_nonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestFastWidget::test_nonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFastWidget->setNonmaxSuppression(value);
  QCOMPARE(result, mFastWidget->nonmaxSuppression());
}

void TestFastWidget::test_detectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("TYPE_5_8") << "TYPE_5_8" << "TYPE_5_8";
  QTest::newRow("TYPE_7_12") << "TYPE_7_12" << "TYPE_7_12";
  QTest::newRow("TYPE_7_12") << "TYPE_9_16" << "TYPE_9_16";
  QTest::newRow("bad_value") << "bad_value" << "TYPE_9_16";
}

void TestFastWidget::test_detectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mFastWidget->setDetectorType(value);
  QCOMPARE(result, mFastWidget->detectorType());
}


QTEST_MAIN(TestFastWidget)

#include "tst_fastwidget.moc"
