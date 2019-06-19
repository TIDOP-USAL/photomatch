#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/LucidWidget.h"

using namespace fme;

class TestLucidWidget : public QObject
{
  Q_OBJECT

public:

  TestLucidWidget();
  ~TestLucidWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void test_lucidKernel_data();
  void test_lucidKernel();
  void test_blurKernel_data();
  void test_blurKernel();
  void test_reset();

private:

  ILucidWidget *mLucidWidget;
};

TestLucidWidget::TestLucidWidget()
  : mLucidWidget(new LucidWidget)
{

}

TestLucidWidget::~TestLucidWidget()
{
  if (mLucidWidget){
    delete mLucidWidget;
    mLucidWidget = nullptr;
  }
}

void TestLucidWidget::initTestCase()
{

}

void TestLucidWidget::cleanupTestCase()
{

}

void TestLucidWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(1, mLucidWidget->lucidKernel());
  QCOMPARE(2, mLucidWidget->blurKernel());
}

void TestLucidWidget::test_windowTitle()
{
  QCOMPARE("LUCID", mLucidWidget->windowTitle());
}

void TestLucidWidget::test_lucidKernel_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestLucidWidget::test_lucidKernel()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLucidWidget->setLucidKernel(value);
  QCOMPARE(result, mLucidWidget->lucidKernel());
}

void TestLucidWidget::test_blurKernel_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestLucidWidget::test_blurKernel()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLucidWidget->setBlurKernel(value);
  QCOMPARE(result, mLucidWidget->blurKernel());
}

void TestLucidWidget::test_reset()
{
  mLucidWidget->setLucidKernel(3);
  mLucidWidget->setBlurKernel(3);

  mLucidWidget->reset();

  QCOMPARE(1, mLucidWidget->lucidKernel());
  QCOMPARE(2, mLucidWidget->blurKernel());
}

QTEST_MAIN(TestLucidWidget)

#include "tst_lucidwidget.moc"
