#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/pohe.h"

using namespace photomatch;

class TestPohe
  : public QObject
{
  Q_OBJECT

public:

  TestPohe();
  ~TestPohe();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructors();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();

private:

  PohePreprocess *mPohePreprocess;
};

TestPohe::TestPohe()
  : mPohePreprocess(new PohePreprocess)
{

}

TestPohe::~TestPohe()
{
  if (mPohePreprocess){
    delete mPohePreprocess;
    mPohePreprocess = nullptr;
  }
}

void TestPohe::initTestCase()
{
  QCOMPARE(QSize(127, 127), mPohePreprocess->blockSize());
}

void TestPohe::cleanupTestCase()
{
  mPohePreprocess->setBlockSize(QSize(5, 5));

  mPohePreprocess->reset();

  QCOMPARE(QSize(127, 127), mPohePreprocess->blockSize());
}

void TestPohe::test_constructors()
{
  PohePreprocess pohePreprocess;
  QCOMPARE(QSize(127, 127), pohePreprocess.blockSize());

  pohePreprocess.setBlockSize(QSize(100, 100));
  /// Copy constructor
  PohePreprocess copy(pohePreprocess);
  QCOMPARE(QSize(100, 100), copy.blockSize());

  PohePreprocess move(PohePreprocess(QSize(100, 100)));
  QCOMPARE(QSize(100, 100), move.blockSize());
}

void TestPohe::test_type()
{
  QCOMPARE(Preprocess::Type::pohe, mPohePreprocess->type());
}

void TestPohe::test_name()
{
  QCOMPARE(QString("POHE"), mPohePreprocess->name());
}

void TestPohe::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestPohe::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mPohePreprocess->setBlockSize(value);
  QCOMPARE(result, mPohePreprocess->blockSize());
}


QTEST_MAIN(TestPohe)

#include "tst_pohe.moc"
