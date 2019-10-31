#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/hmclahe.h"

using namespace photomatch;

class TestHmclahe
  : public QObject
{
  Q_OBJECT

public:

  TestHmclahe();
  ~TestHmclahe();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_name();
  void test_blockSize_data();
  void test_blockSize();
  void test_l_data();
  void test_l();
  void test_phi_data();
  void test_phi();
  void test_reset();

private:

  HmclahePreprocess *mHmclahePreprocess;
};

TestHmclahe::TestHmclahe()
  : mHmclahePreprocess(new HmclahePreprocess)
{

}

TestHmclahe::~TestHmclahe()
{
  if (mHmclahePreprocess){
    delete mHmclahePreprocess;
    mHmclahePreprocess = nullptr;
  }
}

void TestHmclahe::testDefaultConstructor()
{
  HmclahePreprocess hmclahePreprocess;
  QCOMPARE(QSize(17, 17), hmclahePreprocess.blockSize());
  QCOMPARE(0.03, hmclahePreprocess.l());
  QCOMPARE(0.5, hmclahePreprocess.phi());

  /// Copy constructor
  HmclahePreprocess copy(hmclahePreprocess);
  QCOMPARE(QSize(17, 17), copy.blockSize());
  QCOMPARE(0.03, copy.l());
  QCOMPARE(0.5, copy.phi());

  /// Move contructor
  HmclahePreprocess move(std::move(HmclahePreprocess(QSize(8, 8), 0.03, 0.5)));
  QCOMPARE(QSize(8, 8), move.blockSize());
  QCOMPARE(0.03, move.l());
  QCOMPARE(0.5, move.phi());
}

void TestHmclahe::test_type()
{
  QCOMPARE(Preprocess::Type::hmclahe, mHmclahePreprocess->type());
}

void TestHmclahe::test_name()
{
  QCOMPARE(QString("HMCLAHE"), mHmclahePreprocess->name());
}

void TestHmclahe::test_blockSize_data()
{
  QTest::addColumn<QSize>("value");
  QTest::addColumn<QSize>("result");

  QTest::newRow("QSize(1,1)") << QSize(1,1) << QSize(1,1);
  QTest::newRow("QSize(50, 50)") << QSize(50, 50) << QSize(50, 50);
}

void TestHmclahe::test_blockSize()
{
  QFETCH(QSize, value);
  QFETCH(QSize, result);

  mHmclahePreprocess->setBlockSize(value);
  QCOMPARE(result, mHmclahePreprocess->blockSize());
}

void TestHmclahe::test_l_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.01") << 0.01 << 0.01;
  QTest::newRow("0.05") << 0.05 << 0.05;
  QTest::newRow("0.5") << 0.5 << 0.5;
}

void TestHmclahe::test_l()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mHmclahePreprocess->setL(value);
  QCOMPARE(result, mHmclahePreprocess->l());
}

void TestHmclahe::test_phi_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.01") << 0.01 << 0.01;
  QTest::newRow("0.05") << 0.05 << 0.05;
  QTest::newRow("0.9") << 0.9 << 0.9;
}

void TestHmclahe::test_phi()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mHmclahePreprocess->setPhi(value);
  QCOMPARE(result, mHmclahePreprocess->phi());
}

void TestHmclahe::test_reset()
{
  mHmclahePreprocess->setBlockSize(QSize(5, 5));
  mHmclahePreprocess->setL(0.05);
  mHmclahePreprocess->setPhi(.8);

  mHmclahePreprocess->reset();

  QCOMPARE(QSize(17, 17), mHmclahePreprocess->blockSize());
  QCOMPARE(0.03, mHmclahePreprocess->l());
  QCOMPARE(0.5, mHmclahePreprocess->phi());
}

QTEST_MAIN(TestHmclahe)

#include "tst_hmclahe.moc"
