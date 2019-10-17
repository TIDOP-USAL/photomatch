#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/clahe.h"

using namespace fme;

class TestClahe
  : public QObject
{
  Q_OBJECT

public:

  TestClahe();
  ~TestClahe();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_clipLimit_data();
  void test_clipLimit();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_reset();

private:

  ClahePreprocess *mClahePreprocess;
};

TestClahe::TestClahe()
  : mClahePreprocess(new ClahePreprocess)
{

}

TestClahe::~TestClahe()
{
  if (mClahePreprocess){
    delete mClahePreprocess;
    mClahePreprocess = nullptr;
  }
}

void TestClahe::testDefaultConstructor()
{
  ClahePreprocess clahePreprocess;
  QCOMPARE(40.0, clahePreprocess.clipLimit());
  QCOMPARE(QSize(8, 8), clahePreprocess.tilesGridSize());

  /// Copy constructor
  ClahePreprocess copy(clahePreprocess);
  QCOMPARE(40.0, copy.clipLimit());
  QCOMPARE(QSize(8, 8), copy.tilesGridSize());

  /// Move contructor
  ClahePreprocess move(ClahePreprocess(40.0, QSize(8, 8)));
  QCOMPARE(40.0, move.clipLimit());
  QCOMPARE(QSize(8, 8), move.tilesGridSize());
}

void TestClahe::test_type()
{
  QCOMPARE(Preprocess::Type::clahe, mClahePreprocess->type());
}

void TestClahe::test_name()
{
  QCOMPARE(QString("CLAHE"), mClahePreprocess->name());
}

void TestClahe::test_clipLimit_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.") << 0. << 0.;
  QTest::newRow("50.") << 5. << 5.;
  QTest::newRow("100.") << 100. << 100.;
}

void TestClahe::test_clipLimit()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mClahePreprocess->setClipLimit(value);
  QCOMPARE(result, mClahePreprocess->clipLimit());
}

void TestClahe::test_tilesGridSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestClahe::test_tilesGridSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mClahePreprocess->setTilesGridSize(value);
  QCOMPARE(result, mClahePreprocess->tilesGridSize());
}

void TestClahe::test_reset()
{
  mClahePreprocess->setClipLimit(50.);
  mClahePreprocess->setTilesGridSize(QSize(5, 5));

  mClahePreprocess->reset();

  QCOMPARE(40.0, mClahePreprocess->clipLimit());
  QCOMPARE(QSize(8, 8), mClahePreprocess->tilesGridSize());
}


QTEST_MAIN(TestClahe)

#include "tst_clahe.moc"
