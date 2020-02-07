#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/BriskWidget.h"

using namespace photomatch;

class TestBriskWidget : public QObject
{
    Q_OBJECT

public:

  TestBriskWidget();
  ~TestBriskWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_threshold_data();
  void test_threshold();
  void test_octaves_data();
  void test_octaves();
  void test_patternScale_data();
  void test_patternScale();

private:

  BriskWidget *mBriskWidget;

};

TestBriskWidget::TestBriskWidget()
  : mBriskWidget(new BriskWidgetImp)
{

}

TestBriskWidget::~TestBriskWidget()
{
  delete mBriskWidget;
}

void TestBriskWidget::initTestCase()
{
  QCOMPARE(30, mBriskWidget->threshold());
  QCOMPARE(3, mBriskWidget->octaves());
  QCOMPARE(1.0, mBriskWidget->patternScale());
}

void TestBriskWidget::cleanupTestCase()
{
  mBriskWidget->setThreshold(50);
  mBriskWidget->setOctaves(4);
  mBriskWidget->setPatternScale(2.0);

  mBriskWidget->reset();

  QCOMPARE(30, mBriskWidget->threshold());
  QCOMPARE(3, mBriskWidget->octaves());
  QCOMPARE(1.0, mBriskWidget->patternScale());
}

void TestBriskWidget::test_windowTitle()
{
  QCOMPARE("BRISK", mBriskWidget->windowTitle());
}

void TestBriskWidget::test_threshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestBriskWidget::test_threshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskWidget->setThreshold(value);
  QCOMPARE(result, mBriskWidget->threshold());
}

void TestBriskWidget::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestBriskWidget::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskWidget->setOctaves(value);
  QCOMPARE(result, mBriskWidget->octaves());
}

void TestBriskWidget::test_patternScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("2") << 2. << 2.;
  QTest::newRow("8") << 8. << 8.;
  QTest::newRow("Out of range value") << 10001. << 10000.;
}

void TestBriskWidget::test_patternScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mBriskWidget->setPatternScale(value);
  QCOMPARE(result, mBriskWidget->patternScale());
}



QTEST_MAIN(TestBriskWidget)

#include "tst_briskwidget.moc"
