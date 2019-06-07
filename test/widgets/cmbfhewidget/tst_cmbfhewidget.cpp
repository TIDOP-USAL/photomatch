#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/CmbfheWidget.h"

using namespace fme;

class TestCmbfheWidget : public QObject
{
  Q_OBJECT

public:

  TestCmbfheWidget();
  ~TestCmbfheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

private:

  ICmbfheWidget *mCmbfheWidget;
};

TestCmbfheWidget::TestCmbfheWidget()
  : mCmbfheWidget(new CmbfheWidget)
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

}

void TestCmbfheWidget::cleanupTestCase()
{

}

void TestCmbfheWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(QSize(11, 11), mCmbfheWidget->blockSize());
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

void TestCmbfheWidget::test_reset()
{
  mCmbfheWidget->setBlockSize(QSize(5, 5));

  mCmbfheWidget->reset();

  QCOMPARE(QSize(11, 11), mCmbfheWidget->blockSize());
}


QTEST_MAIN(TestCmbfheWidget)

#include "tst_cmbfhewidget.moc"
