#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/widgets/AcebsfWidget.h"

using namespace photomatch;

class TestAcebsfWidget : public QObject
{
  Q_OBJECT

public:
  TestAcebsfWidget();
  ~TestAcebsfWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_blockSize_data();
  void test_blockSize();
  void test_l_data();
  void test_l();
  void test_k1_data();
  void test_k1();
  void test_k2_data();
  void test_k2();

  /// TODO: void test_FocusOrder();
private:

  AcebsfWidget *mAcebsfWidget;
};

TestAcebsfWidget::TestAcebsfWidget()
  : mAcebsfWidget(new AcebsfWidgetImp)
{

}

TestAcebsfWidget::~TestAcebsfWidget()
{
  if (mAcebsfWidget){
    delete mAcebsfWidget;
    mAcebsfWidget = nullptr;
  }
}

void TestAcebsfWidget::initTestCase()
{
  QCOMPARE(QSize(8, 8), mAcebsfWidget->blockSize());
  QCOMPARE(0.03, mAcebsfWidget->l());
  QCOMPARE(10., mAcebsfWidget->k1());
  QCOMPARE(0.5, mAcebsfWidget->k2());
}

void TestAcebsfWidget::cleanupTestCase()
{
  mAcebsfWidget->setBlockSize(QSize(5, 5));
  mAcebsfWidget->setL(0.05);
  mAcebsfWidget->setK1(5.);
  mAcebsfWidget->setK2(0.6);


  mAcebsfWidget->reset();

  QCOMPARE(QSize(8, 8), mAcebsfWidget->blockSize());
  QCOMPARE(0.03, mAcebsfWidget->l());
  QCOMPARE(10., mAcebsfWidget->k1());
  QCOMPARE(0.5, mAcebsfWidget->k2());
}

void TestAcebsfWidget::test_windowTitle()
{
  QCOMPARE("ACEBSF", mAcebsfWidget->windowTitle());
}

void TestAcebsfWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(101, 50) << QSize(100, 50);
  QTest::newRow("Out of range value y") << QSize(50, 101) << QSize(50, 100);
}

void TestAcebsfWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mAcebsfWidget->setBlockSize(value);
  QCOMPARE(result, mAcebsfWidget->blockSize());
}

void TestAcebsfWidget::test_l_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.1") << .1 << .1;
  QTest::newRow("0.2") << .2 << .2;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestAcebsfWidget::test_l()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfWidget->setL(value);
  QCOMPARE(result, mAcebsfWidget->l());
}

void TestAcebsfWidget::test_k1_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestAcebsfWidget::test_k1()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfWidget->setK1(value);
  QCOMPARE(result, mAcebsfWidget->k1());
}

void TestAcebsfWidget::test_k2_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.1") << .1 << .1;
  QTest::newRow("0.2") << .2 << .2;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestAcebsfWidget::test_k2()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfWidget->setK2(value);
  QCOMPARE(result, mAcebsfWidget->k2());
}


QTEST_MAIN(TestAcebsfWidget)

#include "tst_acebsfwidget.moc"
