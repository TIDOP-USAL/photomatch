#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/fahe.h"

using namespace fme;

class TestFahe 
  : public QObject
{
  Q_OBJECT

public:

  TestFahe();
  ~TestFahe();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

private:

  FahePreprocess *mFahePreprocess;
};

TestFahe::TestFahe()
  : mFahePreprocess(new FahePreprocess)
{

}

TestFahe::~TestFahe()
{
  if (mFahePreprocess){
    delete mFahePreprocess;
    mFahePreprocess = nullptr;
  }
}

void TestFahe::testDefaultConstructor()
{
  FahePreprocess fahePreprocess;
  QCOMPARE(QSize(11, 11), fahePreprocess.blockSize());
}

void TestFahe::test_type()
{
  QCOMPARE(Preprocess::Type::fahe, mFahePreprocess->type());
}

void TestFahe::test_name()
{
  QCOMPARE(QString("FAHE"), mFahePreprocess->name());
}

void TestFahe::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestFahe::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mFahePreprocess->setBlockSize(value);
  QCOMPARE(result, mFahePreprocess->blockSize());
}

void TestFahe::test_reset()
{
  mFahePreprocess->setBlockSize(QSize(5, 5));

  mFahePreprocess->reset();

  QCOMPARE(QSize(11, 11), mFahePreprocess->blockSize());
}

QTEST_MAIN(TestFahe)

#include "tst_fahe.moc"
