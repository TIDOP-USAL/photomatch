#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/noshp.h"

using namespace photomatch;

class TestNoshp
  : public QObject
{
  Q_OBJECT

public:

  TestNoshp();
  ~TestNoshp();

private slots:

  void test_constructors();
  void test_type();
  void test_name();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

private:

  NoshpPreprocess *mNoshpPreprocess;
};

TestNoshp::TestNoshp()
  : mNoshpPreprocess(new NoshpPreprocess)
{

}

TestNoshp::~TestNoshp()
{
  if (mNoshpPreprocess){
    delete mNoshpPreprocess;
    mNoshpPreprocess = nullptr;
  }
}

void TestNoshp::test_constructors()
{
  NoshpPreprocess noshpPreprocess;
  QCOMPARE(QSize(127, 127), noshpPreprocess.blockSize());

  noshpPreprocess.setBlockSize(QSize(100, 100));
  /// Copy constructor
  NoshpPreprocess copy(noshpPreprocess);
  QCOMPARE(QSize(100, 100), copy.blockSize());

  NoshpPreprocess move(NoshpPreprocess(QSize(100, 100)));
  QCOMPARE(QSize(100, 100), move.blockSize());
}

void TestNoshp::test_type()
{
  QCOMPARE(Preprocess::Type::noshp, mNoshpPreprocess->type());
}

void TestNoshp::test_name()
{
  QCOMPARE(QString("NOSHP"), mNoshpPreprocess->name());
}

void TestNoshp::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestNoshp::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mNoshpPreprocess->setBlockSize(value);
  QCOMPARE(result, mNoshpPreprocess->blockSize());
}

void TestNoshp::test_reset()
{
  mNoshpPreprocess->setBlockSize(QSize(5, 5));

  mNoshpPreprocess->reset();

  QCOMPARE(QSize(127, 127), mNoshpPreprocess->blockSize());
}


QTEST_MAIN(TestNoshp)

#include "tst_noshp.moc"
