#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/CmbfheWidget.h"

using namespace photomatch;

class TestCmbfheWidget : public QObject
{
  Q_OBJECT

public:

  TestCmbfheWidget();
  ~TestCmbfheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_tilesGridSize_data();
  void test_tilesGridSize();

private:

  CmbfheWidget *mCmbfheWidget;
};

TestCmbfheWidget::TestCmbfheWidget()
  : mCmbfheWidget(new CmbfheWidgetImp)
{

}

TestCmbfheWidget::~TestCmbfheWidget()
{
  if (mCmbfheWidget){
    delete mCmbfheWidget;
    mCmbfheWidget = nullptr;
  }
}

void TestCmbfheWidget::initTestCase()
{
  /// Check default values
  QCOMPARE(QSize(11, 11), mCmbfheWidget->blockSize());
}

void TestCmbfheWidget::cleanupTestCase()
{
  mCmbfheWidget->setBlockSize(QSize(5, 5));

  mCmbfheWidget->reset();

  QCOMPARE(QSize(11, 11), mCmbfheWidget->blockSize());
}


void TestCmbfheWidget::test_windowTitle()
{
  QCOMPARE("CMBFHE", mCmbfheWidget->windowTitle());
}


void TestCmbfheWidget::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(1001, 50) << QSize(1000, 50);
  QTest::newRow("Out of range value y") << QSize(50, 1001) << QSize(50, 1000);
}

void TestCmbfheWidget::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mCmbfheWidget->setBlockSize(value);
  QCOMPARE(result, mCmbfheWidget->blockSize());
}



QTEST_MAIN(TestCmbfheWidget)

#include "tst_cmbfhewidget.moc"
