#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/PoheWidget.h"

using namespace photomatch;

class TestPoheWidget : public QObject
{
  Q_OBJECT

public:

  TestPoheWidget();
  ~TestPoheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_windowTitle();
  void test_blockSize_data();
  void test_blockSize();
  void test_reset();

private:

  IPoheWidget *mPoheWidget;
};

TestPoheWidget::TestPoheWidget()
  : mPoheWidget(new PoheWidget)
{

}

TestPoheWidget::~TestPoheWidget()
{
  if (mPoheWidget){
    delete mPoheWidget;
    mPoheWidget = nullptr;
  }
}

void TestPoheWidget::initTestCase()
{

}

void TestPoheWidget::cleanupTestCase()
{

}

void TestPoheWidget::test_constructor()
{
  /// Check default values
  QCOMPARE(QSize(127, 127), mPoheWidget->blockSize());
}

void TestPoheWidget::test_windowTitle()
{
  QCOMPARE("POHE", mPoheWidget->windowTitle());
}

void TestPoheWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(1001, 50) << QSize(1000, 50);
  QTest::newRow("Out of range value y") << QSize(50, 1001) << QSize(50, 1000);
}

void TestPoheWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mPoheWidget->setBlockSize(value);
  QCOMPARE(result, mPoheWidget->blockSize());
}

void TestPoheWidget::test_reset()
{
  mPoheWidget->setBlockSize(QSize(5, 5));

  mPoheWidget->reset();

  QCOMPARE(QSize(127, 127), mPoheWidget->blockSize());
}


QTEST_MAIN(TestPoheWidget)

#include "tst_pohewidget.moc"
