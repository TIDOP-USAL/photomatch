#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/rswhe.h"

using namespace photomatch;

class TestRswhe
  : public QObject
{
  Q_OBJECT

public:

  TestRswhe();
  ~TestRswhe();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructors();
  void test_type();
  void test_name();
  void test_histogramDivisions_data();
  void test_histogramDivisions();
  void test_histogramCut_data();
  void test_histogramCut();

private:

  RswhePreprocess *mRswhePreprocess;
};

TestRswhe::TestRswhe()
  : mRswhePreprocess(new RswhePreprocess)
{

}

TestRswhe::~TestRswhe()
{
  if (mRswhePreprocess){
    delete mRswhePreprocess;
    mRswhePreprocess = nullptr;
  }
}

void TestRswhe::initTestCase()
{
  QCOMPARE(2, mRswhePreprocess->histogramDivisions());
  QCOMPARE(Rswhe::HistogramCut::by_mean, mRswhePreprocess->histogramCut());
}

void TestRswhe::cleanupTestCase()
{
  mRswhePreprocess->setHistogramDivisions(3);
  mRswhePreprocess->setHistogramCut(Rswhe::HistogramCut::by_median);

  mRswhePreprocess->reset();

  QCOMPARE(2, mRswhePreprocess->histogramDivisions());
  QCOMPARE(Rswhe::HistogramCut::by_mean, mRswhePreprocess->histogramCut());
}

void TestRswhe::test_constructors()
{
  RswhePreprocess rswhePreprocess;
  QCOMPARE(2, rswhePreprocess.histogramDivisions());
  QCOMPARE(Rswhe::HistogramCut::by_mean, rswhePreprocess.histogramCut());
}

void TestRswhe::test_type()
{
  QCOMPARE(Preprocess::Type::rswhe, mRswhePreprocess->type());
}

void TestRswhe::test_name()
{
  QCOMPARE(QString("RSWHE"), mRswhePreprocess->name());
}

void TestRswhe::test_histogramDivisions_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("10") << 10 << 10;
}

void TestRswhe::test_histogramDivisions()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mRswhePreprocess->setHistogramDivisions(value);
  QCOMPARE(result, mRswhePreprocess->histogramDivisions());
}

void TestRswhe::test_histogramCut_data()
{
  QTest::addColumn<Rswhe::HistogramCut>("value");
  QTest::addColumn<Rswhe::HistogramCut>("result");

  QTest::newRow("by_mean") << Rswhe::HistogramCut::by_mean << Rswhe::HistogramCut::by_mean;
  QTest::newRow("by_median") << Rswhe::HistogramCut::by_median << Rswhe::HistogramCut::by_median;
}

void TestRswhe::test_histogramCut()
{
  QFETCH(Rswhe::HistogramCut, value);
  QFETCH(Rswhe::HistogramCut, result);

  mRswhePreprocess->setHistogramCut(value);
  QCOMPARE(result, mRswhePreprocess->histogramCut());
}


QTEST_MAIN(TestRswhe)

#include "tst_rswhe.moc"
