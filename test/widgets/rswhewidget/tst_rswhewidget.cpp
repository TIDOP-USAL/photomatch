#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/RswheWidget.h"

using namespace photomatch;

class TestRswheWidget : public QObject
{
  Q_OBJECT

public:
  TestRswheWidget();
  ~TestRswheWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_histogramDivisions_data();
  void test_histogramDivisions();
  void test_histogramCut_data();
  void test_histogramCut();

private:

  RswheWidget *mRswheWidget;
};

TestRswheWidget::TestRswheWidget()
  : mRswheWidget(new RswheWidgetImp)
{

}

TestRswheWidget::~TestRswheWidget()
{
  if (mRswheWidget){
    delete mRswheWidget;
    mRswheWidget = nullptr;
  }
}

void TestRswheWidget::initTestCase()
{
  QCOMPARE(2, mRswheWidget->histogramDivisions());
  QCOMPARE(RswheWidget::HistogramCut::by_mean, mRswheWidget->histogramCut());
}

void TestRswheWidget::cleanupTestCase()
{
  mRswheWidget->setHistogramDivisions(3);
  mRswheWidget->setHistogramCut(RswheWidget::HistogramCut::by_median);

  mRswheWidget->reset();

  QCOMPARE(2, mRswheWidget->histogramDivisions());
  QCOMPARE(RswheWidget::HistogramCut::by_mean, mRswheWidget->histogramCut());
}

void TestRswheWidget::test_windowTitle()
{
  QCOMPARE("RSWHE", mRswheWidget->windowTitle());
}

void TestRswheWidget::test_histogramDivisions_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 257 << 256;
}

void TestRswheWidget::test_histogramDivisions()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mRswheWidget->setHistogramDivisions(value);
  QCOMPARE(result, mRswheWidget->histogramDivisions());
}

void TestRswheWidget::test_histogramCut_data()
{
  QTest::addColumn<RswheWidget::HistogramCut>("value");
  QTest::addColumn<RswheWidget::HistogramCut>("result");

  QTest::newRow("by_mean") << RswheWidget::HistogramCut::by_mean << RswheWidget::HistogramCut::by_mean;
  QTest::newRow("by_median") << RswheWidget::HistogramCut::by_median << RswheWidget::HistogramCut::by_median;
}

void TestRswheWidget::test_histogramCut()
{
  QFETCH(RswheWidget::HistogramCut, value);
  QFETCH(RswheWidget::HistogramCut, result);

  mRswheWidget->setHistogramCut(value);
  QCOMPARE(result, mRswheWidget->histogramCut());
}


QTEST_MAIN(TestRswheWidget)

#include "tst_rswhewidget.moc"
