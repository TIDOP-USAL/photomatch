#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/LceBsescsWidget.h"

using namespace photomatch;

class TestLceBsescsWidget : public QObject
{
  Q_OBJECT

public:

  TestLceBsescsWidget();
  ~TestLceBsescsWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_blockSize_data();
  void test_blockSize();

private:

  LceBsescsWidget *mLceBsescsWidget;
};

TestLceBsescsWidget::TestLceBsescsWidget()
  : mLceBsescsWidget(new LceBsescsWidgetImp)
{

}

TestLceBsescsWidget::~TestLceBsescsWidget()
{
  if (mLceBsescsWidget){
    delete mLceBsescsWidget;
    mLceBsescsWidget = nullptr;
  }
}

void TestLceBsescsWidget::initTestCase()
{
  /// Check default values
  QCOMPARE(QSize(33, 33), mLceBsescsWidget->blockSize());
}

void TestLceBsescsWidget::cleanupTestCase()
{
  mLceBsescsWidget->setBlockSize(QSize(5, 5));

  mLceBsescsWidget->reset();

  QCOMPARE(QSize(33, 33), mLceBsescsWidget->blockSize());
}

void TestLceBsescsWidget::test_windowTitle()
{
  QCOMPARE("LCE-BSESCS", mLceBsescsWidget->windowTitle());
}


void TestLceBsescsWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(101, 50) << QSize(100, 50);
  QTest::newRow("Out of range value y") << QSize(50, 101) << QSize(50, 100);
}

void TestLceBsescsWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mLceBsescsWidget->setBlockSize(value);
  QCOMPARE(result, mLceBsescsWidget->blockSize());
}



QTEST_MAIN(TestLceBsescsWidget)

#include "tst_lcebsescswidget.moc"
