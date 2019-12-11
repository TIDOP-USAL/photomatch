#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/HmclaheWidget.h"

using namespace photomatch;

class TestHmclaheWidget : public QObject
{
  Q_OBJECT

public:
  TestHmclaheWidget();
  ~TestHmclaheWidget();

private slots:

  void test_constructor();
  void test_windowTitle();
  void test_blockSize_data();
  void test_blockSize();
  void test_l_data();
  void test_l();
  void test_phi_data();
  void test_phi();
  void test_reset();

private:

  IHmclaheWidget *mHmclaheWidget;
};

TestHmclaheWidget::TestHmclaheWidget()
  : mHmclaheWidget(new HmclaheWidget)
{

}

TestHmclaheWidget::~TestHmclaheWidget()
{
  if (mHmclaheWidget){
    delete mHmclaheWidget;
    mHmclaheWidget = nullptr;
  }
}

void TestHmclaheWidget::test_constructor()
{
  HmclaheWidget hmclaheWidget;
  QCOMPARE(QSize(17, 17), hmclaheWidget.blockSize());
  QCOMPARE(0.03, hmclaheWidget.l());
  QCOMPARE(0.5, hmclaheWidget.phi());
}

void TestHmclaheWidget::test_windowTitle()
{
  QCOMPARE("HMCLAHE", mHmclaheWidget->windowTitle());
}

void TestHmclaheWidget::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
  QTest::newRow("Out of range value x") << QSize(1001, 50) << QSize(1000, 50);
  QTest::newRow("Out of range value y") << QSize(50, 1001) << QSize(50, 1000);
}

void TestHmclaheWidget::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHmclaheWidget->setBlockSize(value);
  QCOMPARE(result, mHmclaheWidget->blockSize());
}

void TestHmclaheWidget::test_l_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.01") << 0.01 << 0.01;
  QTest::newRow("0.05") << 0.05 << 0.05;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestHmclaheWidget::test_l()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mHmclaheWidget->setL(value);
  QCOMPARE(result, mHmclaheWidget->l());
}

void TestHmclaheWidget::test_phi_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.01") << 0.01 << 0.01;
  QTest::newRow("0.05") << 0.05 << 0.05;
  QTest::newRow("0.9") << 0.9 << 0.9;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestHmclaheWidget::test_phi()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mHmclaheWidget->setPhi(value);
  QCOMPARE(result, mHmclaheWidget->phi());
}

void TestHmclaheWidget::test_reset()
{
  mHmclaheWidget->setBlockSize(QSize(5, 5));
  mHmclaheWidget->setL(0.05);
  mHmclaheWidget->setPhi(.8);

  mHmclaheWidget->reset();

  QCOMPARE(QSize(17, 17), mHmclaheWidget->blockSize());
  QCOMPARE(0.03, mHmclaheWidget->l());
  QCOMPARE(0.5, mHmclaheWidget->phi());
}


QTEST_MAIN(TestHmclaheWidget)

#include "tst_hmclahewidget.moc"
