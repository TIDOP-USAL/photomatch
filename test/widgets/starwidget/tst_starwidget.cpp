#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/StarWidget.h"

using namespace photomatch;

class TestStarWidget : public QObject
{
  Q_OBJECT

public:
  TestStarWidget();
  ~TestStarWidget();

private slots:

  void testDefaultConstructor();
  void test_windowTitle();
  void test_maxSize_data();
  void test_maxSize();
  void test_responseThreshold_data();
  void test_responseThreshold();
  void test_lineThresholdProjected_data();
  void test_lineThresholdProjected();
  void test_lineThresholdBinarized_data();
  void test_lineThresholdBinarized();
  void test_suppressNonmaxSize_data();
  void test_suppressNonmaxSize();
  void test_reset();

private:

  IStarWidget *mStarWidget;
};

TestStarWidget::TestStarWidget()
  : mStarWidget(new StarWidget)
{
}

TestStarWidget::~TestStarWidget()
{
  if (mStarWidget){
    delete mStarWidget;
    mStarWidget = nullptr;
  }
}

void TestStarWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(45, mStarWidget->maxSize());
  QCOMPARE(30, mStarWidget->responseThreshold());
  QCOMPARE(10, mStarWidget->lineThresholdProjected());
  QCOMPARE(8, mStarWidget->lineThresholdBinarized());
  QCOMPARE(5, mStarWidget->suppressNonmaxSize());
}

void TestStarWidget::test_windowTitle()
{
  QCOMPARE("STAR", mStarWidget->windowTitle());
}

void TestStarWidget::test_maxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestStarWidget::test_maxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarWidget->setMaxSize(value);
  QCOMPARE(result, mStarWidget->maxSize());
}

void TestStarWidget::test_responseThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestStarWidget::test_responseThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarWidget->setResponseThreshold(value);
  QCOMPARE(result, mStarWidget->responseThreshold());
}

void TestStarWidget::test_lineThresholdProjected_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestStarWidget::test_lineThresholdProjected()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarWidget->setLineThresholdProjected(value);
  QCOMPARE(result, mStarWidget->lineThresholdProjected());
}

void TestStarWidget::test_lineThresholdBinarized_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestStarWidget::test_lineThresholdBinarized()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarWidget->setLineThresholdBinarized(value);
  QCOMPARE(result, mStarWidget->lineThresholdBinarized());
}

void TestStarWidget::test_suppressNonmaxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestStarWidget::test_suppressNonmaxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mStarWidget->setSuppressNonmaxSize(value);
  QCOMPARE(result, mStarWidget->suppressNonmaxSize());
}

void TestStarWidget::test_reset()
{
  mStarWidget->setMaxSize(35);
  mStarWidget->setResponseThreshold(20);
  mStarWidget->setLineThresholdProjected(20);
  mStarWidget->setLineThresholdBinarized(10);
  mStarWidget->setSuppressNonmaxSize(20);

  mStarWidget->reset();

  /// Check default values
  QCOMPARE(45, mStarWidget->maxSize());
  QCOMPARE(30, mStarWidget->responseThreshold());
  QCOMPARE(10, mStarWidget->lineThresholdProjected());
  QCOMPARE(8, mStarWidget->lineThresholdBinarized());
  QCOMPARE(5, mStarWidget->suppressNonmaxSize());
}

QTEST_MAIN(TestStarWidget)

#include "tst_starwidget.moc"
