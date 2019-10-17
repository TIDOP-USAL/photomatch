#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/pohe.h"

using namespace fme;

class TestPohe
  : public QObject
{
  Q_OBJECT

public:

  TestPohe();
  ~TestPohe();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

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

void TestPohe::testDefaultConstructor()
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

void TestPohe::test_reset()
{
  mPohePreprocess->setBlockSize(QSize(5, 5));

  mPohePreprocess->reset();

  QCOMPARE(QSize(127, 127), mPohePreprocess->blockSize());
}


QTEST_MAIN(TestPohe)

#include "tst_pohe.moc"
