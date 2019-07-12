#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/ClaheWidget.h"

using namespace fme;

class TestClaheWidget : public QObject
{
  Q_OBJECT

public:

  TestClaheWidget();
  ~TestClaheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void test_clipLimit_data();
  void test_clipLimit();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

private:

  IClaheWidget *mClaheWidget;
};

TestClaheWidget::TestClaheWidget()
  : mClaheWidget(new ClaheWidget)
{

}

TestClaheWidget::~TestClaheWidget()
{
  if (mClaheWidget){
    delete mClaheWidget;
    mClaheWidget = nullptr;
  }
}

void TestClaheWidget::initTestCase()
{

}

void TestClaheWidget::cleanupTestCase()
{

}

void TestClaheWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(40.0, mClaheWidget->clipLimit());
  QCOMPARE(QSize(8, 8), mClaheWidget->tileGridSize());
}

void TestClaheWidget::test_windowTitle()
{
  QCOMPARE("CLAHE", mClaheWidget->windowTitle());
}

void TestClaheWidget::test_clipLimit_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("50.") << 5. << 5.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestClaheWidget::test_clipLimit()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mClaheWidget->setClipLimit(value);
  QCOMPARE(result, mClaheWidget->clipLimit());
}

void TestClaheWidget::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(101, 50) << QSize(100, 50);
  QTest::newRow("Out of range value y") << QSize(50, 101) << QSize(50, 100);
}

void TestClaheWidget::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mClaheWidget->setTilesGridSize(value);
  QCOMPARE(result, mClaheWidget->tileGridSize());
}

void TestClaheWidget::test_reset()
{
  mClaheWidget->setClipLimit(50.);
  mClaheWidget->setTilesGridSize(QSize(5, 5));

  mClaheWidget->reset();

  QCOMPARE(40.0, mClaheWidget->clipLimit());
  QCOMPARE(QSize(8, 8), mClaheWidget->tileGridSize());
}


QTEST_MAIN(TestClaheWidget)

#include "tst_clahewidget.moc"
