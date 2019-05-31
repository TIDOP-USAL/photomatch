#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/CLAHEWidget.h"

using namespace fme;

class TestCLAHEWidget : public QObject
{
  Q_OBJECT

public:

  TestCLAHEWidget();
  ~TestCLAHEWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testClipLimit_data();
  void testClipLimit();
  void testTilesGridSize_data();
  void testTilesGridSize();
  void testReset();

private:

  ICLAHEWidget *mCLAHEWidget;
};

TestCLAHEWidget::TestCLAHEWidget()
  : mCLAHEWidget(new CLAHEWidget)
{

}

TestCLAHEWidget::~TestCLAHEWidget()
{
  if (mCLAHEWidget){
    delete mCLAHEWidget;
    mCLAHEWidget = nullptr;
  }
}

void TestCLAHEWidget::initTestCase()
{

}

void TestCLAHEWidget::cleanupTestCase()
{

}

void TestCLAHEWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(40.0, mCLAHEWidget->clipLimit());
  QCOMPARE(QSize(8, 8), mCLAHEWidget->tileGridSize());
}

void TestCLAHEWidget::testClipLimit_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("50.") << 5. << 5.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestCLAHEWidget::testClipLimit()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mCLAHEWidget->setClipLimit(value);
  QCOMPARE(result, mCLAHEWidget->clipLimit());
}

void TestCLAHEWidget::testTilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(101, 50) << QSize(100, 50);
  QTest::newRow("Out of range value y") << QSize(50, 101) << QSize(50, 100);
}

void TestCLAHEWidget::testTilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mCLAHEWidget->setTilesGridSize(value);
  QCOMPARE(result, mCLAHEWidget->tileGridSize());
}

void TestCLAHEWidget::testReset()
{
  mCLAHEWidget->setClipLimit(50.);
  mCLAHEWidget->setTilesGridSize(QSize(5, 5));

  mCLAHEWidget->reset();

  QCOMPARE(40.0, mCLAHEWidget->clipLimit());
  QCOMPARE(QSize(8, 8), mCLAHEWidget->tileGridSize());
}


QTEST_MAIN(TestCLAHEWidget)

#include "tst_clahewidget.moc"
