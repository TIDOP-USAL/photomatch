#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/acebsf.h"

using namespace photomatch;

class TestAcebsf 
  : public QObject
{
  Q_OBJECT

public:

  TestAcebsf();
  ~TestAcebsf();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_copyConstructor();
  void test_moveConstructor();
  void test_type();
  void test_name();
  void test_blockSize_data();
  void test_blockSize();
  void test_l_data();
  void test_l();
  void test_k1_data();
  void test_k1();
  void test_k2_data();
  void test_k2();

private:

  AcebsfPreprocess *mAcebsfPreprocess;
};

TestAcebsf::TestAcebsf()
  : mAcebsfPreprocess(new AcebsfPreprocess)
{

}

TestAcebsf::~TestAcebsf()
{
  if (mAcebsfPreprocess){
    delete mAcebsfPreprocess;
    mAcebsfPreprocess = nullptr;
  }
}

void TestAcebsf::initTestCase()
{
  QCOMPARE(QSize(8, 8), mAcebsfPreprocess->blockSize());
  QCOMPARE(0.03, mAcebsfPreprocess->l());
  QCOMPARE(10., mAcebsfPreprocess->k1());
  QCOMPARE(0.5, mAcebsfPreprocess->k2());
}

void TestAcebsf::cleanupTestCase()
{
  mAcebsfPreprocess->setBlockSize(QSize(5, 5));
  mAcebsfPreprocess->setL(0.05);
  mAcebsfPreprocess->setK1(5.);
  mAcebsfPreprocess->setK2(0.6);

  mAcebsfPreprocess->reset();

  QCOMPARE(QSize(8, 8), mAcebsfPreprocess->blockSize());
  QCOMPARE(0.03, mAcebsfPreprocess->l());
  QCOMPARE(10., mAcebsfPreprocess->k1());
  QCOMPARE(0.5, mAcebsfPreprocess->k2());
}

void TestAcebsf::test_copyConstructor()
{
  AcebsfPreprocess acebsfPreprocess(QSize(8, 8), 0.03, 10., 0.5);
  AcebsfPreprocess copy(acebsfPreprocess);
  QCOMPARE(QSize(8, 8), copy.blockSize());
  QCOMPARE(0.03, copy.l());
  QCOMPARE(10., copy.k1());
  QCOMPARE(0.5, copy.k2());
}

void TestAcebsf::test_moveConstructor()
{
  AcebsfPreprocess move(AcebsfPreprocess(QSize(8, 8), 0.03, 10., 0.5));
  QCOMPARE(QSize(8, 8), move.blockSize());
  QCOMPARE(0.03, move.l());
  QCOMPARE(10., move.k1());
  QCOMPARE(0.5, move.k2());
}

void TestAcebsf::test_type()
{
  QCOMPARE(Preprocess::Type::acebsf, mAcebsfPreprocess->type());
}

void TestAcebsf::test_name()
{
  QCOMPARE(QString("ACEBSF"), mAcebsfPreprocess->name());
}

void TestAcebsf::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestAcebsf::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mAcebsfPreprocess->setBlockSize(value);
  QCOMPARE(result, mAcebsfPreprocess->blockSize());
}

void TestAcebsf::test_l_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.1") << .1 << .1;
  QTest::newRow("0.2") << .2 << .2;
}

void TestAcebsf::test_l()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfPreprocess->setL(value);
  QCOMPARE(result, mAcebsfPreprocess->l());
}

void TestAcebsf::test_k1_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
}

void TestAcebsf::test_k1()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfPreprocess->setK1(value);
  QCOMPARE(result, mAcebsfPreprocess->k1());
}

void TestAcebsf::test_k2_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.1") << .1 << .1;
  QTest::newRow("0.2") << .2 << .2;
}

void TestAcebsf::test_k2()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mAcebsfPreprocess->setK2(value);
  QCOMPARE(result, mAcebsfPreprocess->k2());
}


QTEST_MAIN(TestAcebsf)

#include "tst_acebsf.moc"
