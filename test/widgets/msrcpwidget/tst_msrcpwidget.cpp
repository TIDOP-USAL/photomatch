#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/MsrcpWidget.h"

using namespace fme;

class TestMsrcpWidget : public QObject
{
  Q_OBJECT

public:
  TestMsrcpWidget();
  ~TestMsrcpWidget();

private slots:

  void testDefaultConstructor();
  void test_windowTitle();
  void test_smallScale_data();
  void test_smallScale();
  void test_midScale_data();
  void test_midScale();
  void test_largeScale_data();
  void test_largeScale();
  void test_reset();

private:

  IMsrcpWidget *mMsrcpWidget;
};

TestMsrcpWidget::TestMsrcpWidget()
  : mMsrcpWidget(new MsrcpWidget)
{

}

TestMsrcpWidget::~TestMsrcpWidget()
{
  if (mMsrcpWidget){
    delete mMsrcpWidget;
    mMsrcpWidget = nullptr;
  }
}

void TestMsrcpWidget::testDefaultConstructor()
{
  QCOMPARE(10., mMsrcpWidget->smallScale());
  QCOMPARE(100., mMsrcpWidget->midScale());
  QCOMPARE(220., mMsrcpWidget->largeScale());
}

void TestMsrcpWidget::test_windowTitle()
{
  QCOMPARE("MSRCP", mMsrcpWidget->windowTitle());
}

void TestMsrcpWidget::test_smallScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("Out of range value") << 20.0 << 19.99;
}

void TestMsrcpWidget::test_smallScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpWidget->setSmallScale(value);
  QCOMPARE(result, mMsrcpWidget->smallScale());
}

void TestMsrcpWidget::test_midScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("100.0") << 100.0 << 100.0;
  QTest::newRow("Out of range value 1") << 19.99 << 20.;
  QTest::newRow("Out of range value 2") << 200.0 << 199.99;
}

void TestMsrcpWidget::test_midScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpWidget->setMidScale(value);
  QCOMPARE(result, mMsrcpWidget->midScale());
}

void TestMsrcpWidget::test_largeScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("220.0") << 220.0 << 220.0;
  QTest::newRow("100.0") << 250.0 << 250.0;
  QTest::newRow("Out of range value 1") << 199.99 << 200.;
  QTest::newRow("Out of range value 2") << 257.0 << 256.;
}

void TestMsrcpWidget::test_largeScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpWidget->setLargeScale(value);
  QCOMPARE(result, mMsrcpWidget->largeScale());
}

void TestMsrcpWidget::test_reset()
{
  mMsrcpWidget->setSmallScale(15.);
  mMsrcpWidget->setMidScale(150.);
  mMsrcpWidget->setLargeScale(250.);

  mMsrcpWidget->reset();

  QCOMPARE(10., mMsrcpWidget->smallScale());
  QCOMPARE(100., mMsrcpWidget->midScale());
  QCOMPARE(220., mMsrcpWidget->largeScale());
}


QTEST_MAIN(TestMsrcpWidget)

#include "tst_msrcpwidget.moc"
