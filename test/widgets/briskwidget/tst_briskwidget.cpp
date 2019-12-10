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
  void test_constructor();
  void test_windowTitle();
  void testThreshold_data();
  void testThreshold();
  void testOctaves_data();
  void testOctaves();
  void testPatternScale_data();
  void testPatternScale();
  void testReset();

private:

  IBriskWidget *mBriskWidget;

};

TestBriskWidget::TestBriskWidget()
  : mBriskWidget(new BriskWidget)
{

}

TestBriskWidget::~TestBriskWidget()
{
  delete mBriskWidget;
}

void TestBriskWidget::initTestCase()
{

}

void TestBriskWidget::cleanupTestCase()
{

}

void TestBriskWidget::test_constructor()
{
  QCOMPARE(30, mBriskWidget->threshold());
  QCOMPARE(3, mBriskWidget->octaves());
  QCOMPARE(1.0, mBriskWidget->patternScale());
}

void TestBriskWidget::test_windowTitle()
{
  QCOMPARE("BRISK", mBriskWidget->windowTitle());
}

void TestBriskWidget::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestBriskWidget::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskWidget->setThreshold(value);
  QCOMPARE(result, mBriskWidget->threshold());
}

void TestBriskWidget::testOctaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestBriskWidget::testOctaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskWidget->setOctaves(value);
  QCOMPARE(result, mBriskWidget->octaves());
}

void TestBriskWidget::testPatternScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("2") << 2. << 2.;
  QTest::newRow("8") << 8. << 8.;
  QTest::newRow("Out of range value") << 10001. << 10000.;
}

void TestBriskWidget::testPatternScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mBriskWidget->setPatternScale(value);
  QCOMPARE(result, mBriskWidget->patternScale());
}

void TestBriskWidget::testReset()
{
  mBriskWidget->setThreshold(50);
  mBriskWidget->setOctaves(4);
  mBriskWidget->setPatternScale(2.0);

  mBriskWidget->reset();

  QCOMPARE(30, mBriskWidget->threshold());
  QCOMPARE(3, mBriskWidget->octaves());
  QCOMPARE(1.0, mBriskWidget->patternScale());
}


QTEST_MAIN(TestBriskWidget)

#include "tst_briskwidget.moc"
