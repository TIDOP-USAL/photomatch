#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/cmbfhe.h"

using namespace photomatch;

class TestCmbfhe
  : public QObject
{
  Q_OBJECT

public:

  TestCmbfhe();
  ~TestCmbfhe();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructors();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();

private:

  CmbfhePreprocess *mCmbfhePreprocess;
};

TestCmbfhe::TestCmbfhe()
  : mCmbfhePreprocess(new CmbfhePreprocess)
{

}

TestCmbfhe::~TestCmbfhe()
{
  if (mCmbfhePreprocess){
    delete mCmbfhePreprocess;
    mCmbfhePreprocess = nullptr;
  }
}

void TestCmbfhe::initTestCase()
{
  QCOMPARE(QSize(11, 11), mCmbfhePreprocess->blockSize());
}

void TestCmbfhe::cleanupTestCase()
{
  mCmbfhePreprocess->setBlockSize(QSize(5, 5));

  mCmbfhePreprocess->reset();

  QCOMPARE(QSize(11, 11), mCmbfhePreprocess->blockSize());
}

void TestCmbfhe::test_constructors()
{
  CmbfhePreprocess cmbfhePreprocess;
  QCOMPARE(QSize(11, 11), cmbfhePreprocess.blockSize());

  CmbfhePreprocess cmbfhePreprocess2(QSize(6, 6));
  QCOMPARE(QSize(6, 6), cmbfhePreprocess2.blockSize());

  CmbfhePreprocess copy(cmbfhePreprocess2);
  QCOMPARE(QSize(6, 6), copy.blockSize());
}

void TestCmbfhe::test_type()
{
  QCOMPARE(Preprocess::Type::cmbfhe, mCmbfhePreprocess->type());
}

void TestCmbfhe::test_name()
{
  QCOMPARE(QString("CMBFHE"), mCmbfhePreprocess->name());
}

void TestCmbfhe::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestCmbfhe::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mCmbfhePreprocess->setBlockSize(value);
  QCOMPARE(result, mCmbfhePreprocess->blockSize());
}

QTEST_MAIN(TestCmbfhe)

#include "tst_cmbfhe.moc"
