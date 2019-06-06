#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/LceBsescsWidget.h"

using namespace fme;

class TestLceBsescsWidget : public QObject
{
  Q_OBJECT

public:

  TestLceBsescsWidget();
  ~TestLceBsescsWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testTilesGridSize_data();
  void testTilesGridSize();
  void testReset();

private:

  ILceBsescsWidget *mLceBsescsWidget;
};

TestLceBsescsWidget::TestLceBsescsWidget()
  : mLceBsescsWidget(new LceBsescsWidget)
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

}

void TestLceBsescsWidget::cleanupTestCase()
{

}

void TestLceBsescsWidget::testDefaultConstructor()
{
  /// Check default values
  LceBsescsWidget lceBsescsWidget;
  QCOMPARE(QSize(33, 33), lceBsescsWidget.blockSize());
}


void TestLceBsescsWidget::testTilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(101, 50) << QSize(100, 50);
  QTest::newRow("Out of range value y") << QSize(50, 101) << QSize(50, 100);
}

void TestLceBsescsWidget::testTilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mLceBsescsWidget->setBlockSize(value);
  QCOMPARE(result, mLceBsescsWidget->blockSize());
}

void TestLceBsescsWidget::testReset()
{
  mLceBsescsWidget->setBlockSize(QSize(5, 5));

  mLceBsescsWidget->reset();

  QCOMPARE(QSize(33, 33), mLceBsescsWidget->blockSize());
}


QTEST_MAIN(TestLceBsescsWidget)

#include "tst_lcebsescswidget.moc"
