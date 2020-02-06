#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DheWidget.h"

using namespace photomatch;

class TestDheWidget : public QObject
{
  Q_OBJECT

public:
  TestDheWidget();
  ~TestDheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_x_data();
  void test_x();

private:

  DheWidget *mDheWidget;
};

TestDheWidget::TestDheWidget()
  : mDheWidget(new DheWidgetImp)
{

}

TestDheWidget::~TestDheWidget()
{
  if (mDheWidget){
    delete mDheWidget;
    mDheWidget = nullptr;
  }
}

void TestDheWidget::initTestCase()
{
  QCOMPARE(1, mDheWidget->x());
}

void TestDheWidget::cleanupTestCase()
{
  mDheWidget->setX(3);

  mDheWidget->reset();

  QCOMPARE(1, mDheWidget->x());
}

void TestDheWidget::test_windowTitle()
{
  QCOMPARE("DHE", mDheWidget->windowTitle());
}

void TestDheWidget::test_x_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("Out of range value") << 6 << 5;
}

void TestDheWidget::test_x()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDheWidget->setX(value);
  QCOMPARE(result, mDheWidget->x());
}


QTEST_MAIN(TestDheWidget)

#include "tst_dhewidget.moc"
