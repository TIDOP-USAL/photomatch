#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/lce_bsescs.h"

using namespace photomatch;

class TestLceBsescs
  : public QObject
{
  Q_OBJECT

public:

  TestLceBsescs();
  ~TestLceBsescs();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructors();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();

private:

  LceBsescsPreprocess *mLceBsescsPreprocess;
};

TestLceBsescs::TestLceBsescs()
  : mLceBsescsPreprocess(new LceBsescsPreprocess)
{

}

TestLceBsescs::~TestLceBsescs()
{
  if (mLceBsescsPreprocess){
    delete mLceBsescsPreprocess;
    mLceBsescsPreprocess = nullptr;
  }
}

void TestLceBsescs::initTestCase()
{
  QCOMPARE(QSize(33, 33), mLceBsescsPreprocess->blockSize());
}

void TestLceBsescs::cleanupTestCase()
{
  mLceBsescsPreprocess->setBlockSize(QSize(5, 5));

  mLceBsescsPreprocess->reset();

  QCOMPARE(QSize(33, 33), mLceBsescsPreprocess->blockSize());
}

void TestLceBsescs::test_constructors()
{
  LceBsescsPreprocess lceBsescsPreprocess;
  QCOMPARE(QSize(33, 33), lceBsescsPreprocess.blockSize());

  LceBsescsPreprocess copy(lceBsescsPreprocess);
  QCOMPARE(QSize(33, 33), copy.blockSize());

  LceBsescsPreprocess move(std::move(LceBsescsPreprocess(QSize(11, 11))));
  QCOMPARE(QSize(11, 11), move.blockSize());
}

void TestLceBsescs::test_type()
{
  QCOMPARE(Acebsf::Type::lce_bsescs, mLceBsescsPreprocess->type());
}

void TestLceBsescs::test_name()
{
  QCOMPARE(QString("LCE_BSESCS"), mLceBsescsPreprocess->name());
}

void TestLceBsescs::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestLceBsescs::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mLceBsescsPreprocess->setBlockSize(value);
  QCOMPARE(result, mLceBsescsPreprocess->blockSize());
}


QTEST_MAIN(TestLceBsescs)

#include "tst_lce_bsescs.moc"
