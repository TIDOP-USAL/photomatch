#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/cmbfhe.h"

using namespace fme;

class TestCmbfhe
  : public QObject
{
  Q_OBJECT

public:

  TestCmbfhe();
  ~TestCmbfhe();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

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

void TestCmbfhe::testDefaultConstructor()
{
  CmbfhePreprocess cmbfhePreprocess;


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

void TestCmbfhe::test_reset()
{
  mCmbfhePreprocess->setBlockSize(QSize(5, 5));

  mCmbfhePreprocess->reset();

  QCOMPARE(QSize(11, 11), mCmbfhePreprocess->blockSize());
}

QTEST_MAIN(TestCmbfhe)

#include "tst_cmbfhe.moc"
