#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/KeypointsFilterWidget.h"

using namespace photomatch;

class TestKeypointsFilterWidget : public QObject
{
  Q_OBJECT

public:
  TestKeypointsFilterWidget();
  ~TestKeypointsFilterWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_nPoints_data();
  void test_nPoints();
  void test_minSize_data();
  void test_minSize();
  void test_maxSize_data();
  void test_maxSize();
  void test_isActiveFilterBest();
  void test_isActiveFilterSize();
  void test_isActiveRemoveDuplicated();

private:

  KeypointsFilterWidget *mKeypointsFilterWidget;
};

TestKeypointsFilterWidget::TestKeypointsFilterWidget()
  : mKeypointsFilterWidget(new KeypointsFilterWidgetImp)
{

}

TestKeypointsFilterWidget::~TestKeypointsFilterWidget()
{
  if (mKeypointsFilterWidget){
    delete mKeypointsFilterWidget;
    mKeypointsFilterWidget = nullptr;
  }
}

void TestKeypointsFilterWidget::initTestCase()
{
  QCOMPARE(false, mKeypointsFilterWidget->isActiveFilterBest());
  QCOMPARE(false, mKeypointsFilterWidget->isActiveFilterSize());
  QCOMPARE(false, mKeypointsFilterWidget->isActiveRemoveDuplicated());
  QCOMPARE(10000, mKeypointsFilterWidget->nPoints());
  QCOMPARE(0., mKeypointsFilterWidget->minSize());
  QCOMPARE(50., mKeypointsFilterWidget->maxSize());
}

void TestKeypointsFilterWidget::cleanupTestCase()
{
  mKeypointsFilterWidget->setMaxSize(50.);
  mKeypointsFilterWidget->setMinSize(0.5);
  mKeypointsFilterWidget->setNPoints(500);
  mKeypointsFilterWidget->setActiveFilterBest(true);
  mKeypointsFilterWidget->setActiveFilterSize(true);
  mKeypointsFilterWidget->setActiveRemoveDuplicated(true);

  mKeypointsFilterWidget->reset();

  QCOMPARE(false, mKeypointsFilterWidget->isActiveFilterBest());
  QCOMPARE(false, mKeypointsFilterWidget->isActiveFilterSize());
  QCOMPARE(false, mKeypointsFilterWidget->isActiveRemoveDuplicated());
  QCOMPARE(10000, mKeypointsFilterWidget->nPoints());
  QCOMPARE(0., mKeypointsFilterWidget->minSize());
  QCOMPARE(50., mKeypointsFilterWidget->maxSize());
}

void TestKeypointsFilterWidget::test_windowTitle()
{
  QCOMPARE("Keypoints Filter", mKeypointsFilterWidget->windowTitle());
}

void TestKeypointsFilterWidget::test_nPoints_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("1000") << 1000 << 1000;
  QTest::newRow("1") << 1 << 1;
}

void TestKeypointsFilterWidget::test_nPoints()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKeypointsFilterWidget->setNPoints(value);
  QCOMPARE(result, mKeypointsFilterWidget->nPoints());
}

void TestKeypointsFilterWidget::test_minSize_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("50.") << 50. << 50.;
}

void TestKeypointsFilterWidget::test_minSize()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mKeypointsFilterWidget->setMinSize(value);
  QCOMPARE(result, mKeypointsFilterWidget->minSize());
}

void TestKeypointsFilterWidget::test_maxSize_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("50.") << 50. << 50.;
  QTest::newRow("100.") << 100. << 100.;
  QTest::newRow("500.") << 500. << 500.;
}

void TestKeypointsFilterWidget::test_maxSize()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mKeypointsFilterWidget->setMaxSize(value);
  QCOMPARE(result, mKeypointsFilterWidget->maxSize());
}

void TestKeypointsFilterWidget::test_isActiveFilterBest()
{
  mKeypointsFilterWidget->setActiveFilterBest(true);
  QCOMPARE(true, mKeypointsFilterWidget->isActiveFilterBest());
}

void TestKeypointsFilterWidget::test_isActiveFilterSize()
{
  mKeypointsFilterWidget->setActiveFilterSize(true);
  QCOMPARE(true, mKeypointsFilterWidget->isActiveFilterSize());
}

void TestKeypointsFilterWidget::test_isActiveRemoveDuplicated()
{
  mKeypointsFilterWidget->setActiveRemoveDuplicated(true);
  QCOMPARE(true, mKeypointsFilterWidget->isActiveRemoveDuplicated());
}


QTEST_MAIN(TestKeypointsFilterWidget)

#include "tst_keypointsfilterwidget.moc"
