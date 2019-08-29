#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/acebsf.h"

using namespace fme;

class TestAcebsf 
  : public QObject
{
  Q_OBJECT

public:

  TestAcebsf();
  ~TestAcebsf();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_blockSize_data();
  void test_blockSize();
  void test_l_data();
  void test_l();
  void test_k1_data();
  void test_k1();
  void test_k2_data();
  void test_k2();
  void test_reset();

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

void TestAcebsf::testDefaultConstructor()
{
  AcebsfPreprocess acebsfPreprocess;
  QCOMPARE(QSize(8, 8), acebsfPreprocess.blockSize());
  QCOMPARE(0.03, acebsfPreprocess.l());
  QCOMPARE(10., acebsfPreprocess.k1());
  QCOMPARE(0.5, acebsfPreprocess.k2());

}

void TestAcebsf::test_type()
{
  QCOMPARE(IAcebsf::Type::acebsf, mAcebsfPreprocess->type());
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

void TestAcebsf::test_reset()
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


QTEST_MAIN(TestAcebsf)

#include "tst_acebsf.moc"
