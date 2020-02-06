#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/latch.h"

using namespace photomatch;

class TestLatchDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestLatchDescriptor();
  ~TestLatchDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_bytes_data();
  void test_bytes();
  void test_rotationInvariance_data();
  void test_rotationInvariance();
  void test_halfSsdSize_data();
  void test_halfSsdSize();

private:

  LatchDescriptor *mLatchDescriptor;
};

TestLatchDescriptor::TestLatchDescriptor()
  : mLatchDescriptor(new LatchDescriptor)
{

}

TestLatchDescriptor::~TestLatchDescriptor()
{
  if (mLatchDescriptor){
    delete mLatchDescriptor;
    mLatchDescriptor = nullptr;
  }
}

void TestLatchDescriptor::initTestCase()
{
  QCOMPARE("32", mLatchDescriptor->bytes());
  QCOMPARE(true, mLatchDescriptor->rotationInvariance());
  QCOMPARE(3, mLatchDescriptor->halfSsdSize());
}

void TestLatchDescriptor::cleanupTestCase()
{
  mLatchDescriptor->setBytes("4");
  mLatchDescriptor->setRotationInvariance(false);
  mLatchDescriptor->setHalfSsdSize(5);

  mLatchDescriptor->reset();

  QCOMPARE("32", mLatchDescriptor->bytes());
  QCOMPARE(true, mLatchDescriptor->rotationInvariance());
  QCOMPARE(3, mLatchDescriptor->halfSsdSize());
}

void TestLatchDescriptor::test_defaultConstructor()
{
  /// Check default values
  LatchDescriptor latchDescriptor;
  QCOMPARE("32", latchDescriptor.bytes());
  QCOMPARE(true, latchDescriptor.rotationInvariance());
  QCOMPARE(3, latchDescriptor.halfSsdSize());
}

void TestLatchDescriptor::test_constructor()
{
  LatchDescriptor latchDescriptor("16", false, 2);
  QCOMPARE("16", latchDescriptor.bytes());
  QCOMPARE(false, latchDescriptor.rotationInvariance());
  QCOMPARE(2, latchDescriptor.halfSsdSize());
}

void TestLatchDescriptor::test_copy_constructor()
{
  LatchDescriptor latchDescriptor("16", false, 2);
  LatchDescriptor c(latchDescriptor);
  QCOMPARE("16", c.bytes());
  QCOMPARE(false, c.rotationInvariance());
  QCOMPARE(2, c.halfSsdSize());
}

void TestLatchDescriptor::test_type()
{
  QCOMPARE(LatchDescriptor::Type::latch, mLatchDescriptor->type());
}

void TestLatchDescriptor::test_name()
{
  QCOMPARE("LATCH", mLatchDescriptor->name());
}

void TestLatchDescriptor::test_bytes_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("1") << "1" << "1";
  QTest::newRow("2") << "2" << "2";
  QTest::newRow("4") << "4" << "4";
  QTest::newRow("8") << "8" << "8";
  QTest::newRow("16") << "16" << "16";
  QTest::newRow("32") << "32" << "32";
  QTest::newRow("64") << "64" << "64";
  QTest::newRow("bad_value") << "128" << "64";

}

void TestLatchDescriptor::test_bytes()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mLatchDescriptor->setBytes(value);
  QCOMPARE(result, mLatchDescriptor->bytes());
}

void TestLatchDescriptor::test_rotationInvariance_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestLatchDescriptor::test_rotationInvariance()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mLatchDescriptor->setRotationInvariance(value);
  QCOMPARE(result, mLatchDescriptor->rotationInvariance());
}

void TestLatchDescriptor::test_halfSsdSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestLatchDescriptor::test_halfSsdSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLatchDescriptor->setHalfSsdSize(value);
  QCOMPARE(result, mLatchDescriptor->halfSsdSize());
}


QTEST_APPLESS_MAIN(TestLatchDescriptor)

#include "tst_latchdescriptor.moc"
