#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/RswheWidget.h"

using namespace fme;

class TestRswheWidget : public QObject
{
  Q_OBJECT

public:
  TestRswheWidget();
  ~TestRswheWidget();

private slots:

  void testDefaultConstructor();
  void test_windowTitle();
  void test_histogramDivisions_data();
  void test_histogramDivisions();
  void test_histogramCut_data();
  void test_histogramCut();
  void test_reset();

private:

  IRswheWidget *mRswheWidget;
};

TestRswheWidget::TestRswheWidget()
  : mRswheWidget(new RswheWidget)
{

}

TestRswheWidget::~TestRswheWidget()
{
  if (mRswheWidget){
    delete mRswheWidget;
    mRswheWidget = nullptr;
  }
}

void TestRswheWidget::testDefaultConstructor()
{
  QCOMPARE(2, mRswheWidget->histogramDivisions());
  QCOMPARE(IRswheWidget::HistogramCut::by_mean, mRswheWidget->histogramCut());
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
  QTest::addColumn<IRswheWidget::HistogramCut>("value");
  QTest::addColumn<IRswheWidget::HistogramCut>("result");

  QTest::newRow("by_mean") << IRswheWidget::HistogramCut::by_mean << IRswheWidget::HistogramCut::by_mean;
  QTest::newRow("by_median") << IRswheWidget::HistogramCut::by_median << IRswheWidget::HistogramCut::by_median;
}

void TestRswheWidget::test_histogramCut()
{
  QFETCH(IRswheWidget::HistogramCut, value);
  QFETCH(IRswheWidget::HistogramCut, result);

  mRswheWidget->setHistogramCut(value);
  QCOMPARE(result, mRswheWidget->histogramCut());
}

void TestRswheWidget::test_reset()
{
  mRswheWidget->setHistogramDivisions(3);
  mRswheWidget->setHistogramCut(IRswheWidget::HistogramCut::by_median);

  mRswheWidget->reset();

  QCOMPARE(2, mRswheWidget->histogramDivisions());
  QCOMPARE(IRswheWidget::HistogramCut::by_mean, mRswheWidget->histogramCut());
}

QTEST_MAIN(TestRswheWidget)

#include "tst_rswhewidget.moc"
