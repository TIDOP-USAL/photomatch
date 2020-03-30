#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/clahe.h"


using namespace photomatch;

class TestClahe
  : public QObject,
    public ClahePreprocess
{
  Q_OBJECT

public:

  TestClahe();
  ~TestClahe();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_copyConstructor();
  void test_moveConstructor();
  void test_type();
  void test_name();
  void test_clipLimit_data();
  void test_clipLimit();
  void test_tilesGridSize_data();
  void test_tilesGridSize();
  void test_tilesGridSize2();

};

TestClahe::TestClahe()
  : ClahePreprocess()
{

}

TestClahe::~TestClahe()
{

}

void TestClahe::initTestCase()
{
  QCOMPARE(40.0, this->clipLimit());
  QCOMPARE(40.0, this->mCvClahe->getClipLimit());
  QCOMPARE(QSize(8, 8), this->tilesGridSize());
  QCOMPARE(cv::Size(8, 8), this->mCvClahe->getTilesGridSize());
}

void TestClahe::cleanupTestCase()
{
  this->setClipLimit(50.);
  this->setTilesGridSize(QSize(5, 5));

  this->reset();

  QCOMPARE(40.0, this->clipLimit());
  QCOMPARE(40.0, this->mCvClahe->getClipLimit());
  QCOMPARE(QSize(8, 8), this->tilesGridSize());
  QCOMPARE(cv::Size(8, 8), this->mCvClahe->getTilesGridSize());
}

void TestClahe::test_copyConstructor()
{
  ClahePreprocess clahePreprocess(60.0, QSize(6, 6));

  ClahePreprocess copy(clahePreprocess);
  QCOMPARE(60.0, copy.clipLimit());
  QCOMPARE(QSize(6, 6), copy.tilesGridSize());
}

void TestClahe::test_moveConstructor()
{
  ClahePreprocess move(ClahePreprocess(60.0, QSize(6, 6)));
  QCOMPARE(60.0, move.clipLimit());
  QCOMPARE(QSize(6, 6), move.tilesGridSize());
}

void TestClahe::test_type()
{
  QCOMPARE(Preprocess::Type::clahe, this->type());
}

void TestClahe::test_name()
{
  QCOMPARE(QString("CLAHE"), this->name());
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

  this->setClipLimit(value);
  QCOMPARE(result, this->clipLimit());
  QCOMPARE(result, this->mCvClahe->getClipLimit());
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

  this->setTilesGridSize(value);
  QCOMPARE(result, this->tilesGridSize());
}

void TestClahe::test_tilesGridSize2()
{
  this->setTilesGridSize(QSize(5, 5));
  QCOMPARE(QSize(5, 5), this->tilesGridSize());
  QCOMPARE(cv::Size(5, 5), this->mCvClahe->getTilesGridSize());
}



QTEST_MAIN(TestClahe)

#include "tst_clahe.moc"
