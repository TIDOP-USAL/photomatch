#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/NoshpWidget.h"

using namespace photomatch;

class TestNoshpWidget : public QObject
{
  Q_OBJECT

public:

  TestNoshpWidget();
  ~TestNoshpWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_blockSize_data();
  void test_blockSize();

private:

  NoshpWidget *mNoshpWidget;
};

TestNoshpWidget::TestNoshpWidget()
  : mNoshpWidget(new NoshpWidgetImp)
{

}

TestNoshpWidget::~TestNoshpWidget()
{
  if (mNoshpWidget){
    delete mNoshpWidget;
    mNoshpWidget = nullptr;
  }
}

void TestNoshpWidget::initTestCase()
{
  /// Check default values
  QCOMPARE(QSize(127, 127), mNoshpWidget->blockSize());
}

void TestNoshpWidget::cleanupTestCase()
{
  mNoshpWidget->setBlockSize(QSize(5, 5));

  mNoshpWidget->reset();

  QCOMPARE(QSize(127, 127), mNoshpWidget->blockSize());
}

void TestNoshpWidget::test_windowTitle()
{
  QCOMPARE("NOSHP", mNoshpWidget->windowTitle());
}

void TestNoshpWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(1001, 50) << QSize(1000, 50);
  QTest::newRow("Out of range value y") << QSize(50, 1001) << QSize(50, 1000);
}

void TestNoshpWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mNoshpWidget->setBlockSize(value);
  QCOMPARE(result, mNoshpWidget->blockSize());
}

QTEST_MAIN(TestNoshpWidget)

#include "tst_noshpwidget.moc"
