#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/DheWidget.h"

using namespace fme;

class TestDheWidget : public QObject
{
  Q_OBJECT

public:
  TestDheWidget();
  ~TestDheWidget();

private slots:

  void testDefaultConstructor();
  void test_x_data();
  void test_x();
  void test_reset();

private:

  IDheWidget *mDheWidget;
};

TestDheWidget::TestDheWidget()
  : mDheWidget(new DheWidget)
{

}

TestDheWidget::~TestDheWidget()
{
  if (mDheWidget){
    delete mDheWidget;
    mDheWidget = nullptr;
  }
}

void TestDheWidget::testDefaultConstructor()
{
  QCOMPARE(1, mDheWidget->x());
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

void TestDheWidget::test_reset()
{
  mDheWidget->setX(3);

  mDheWidget->reset();

  QCOMPARE(1, mDheWidget->x());
}

QTEST_MAIN(TestDheWidget)

#include "tst_dhewidget.moc"
