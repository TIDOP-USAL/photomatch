#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/lucid.h"

using namespace photomatch;

class TestLucidDescriptor : public QObject
{
  Q_OBJECT

public:

  TestLucidDescriptor();
  ~TestLucidDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_type();
  void test_name();
  void test_lucidKernel_data();
  void test_lucidKernel();
  void test_blurKernel_data();
  void test_blurKernel();
  void test_reset();

private:

  LucidDescriptor *mLucidDescriptor;
};

TestLucidDescriptor::TestLucidDescriptor()
  : mLucidDescriptor(new LucidDescriptor)
{

}

TestLucidDescriptor::~TestLucidDescriptor()
{
  if (mLucidDescriptor){
    delete mLucidDescriptor;
    mLucidDescriptor = nullptr;
  }
}

void TestLucidDescriptor::initTestCase()
{

}

void TestLucidDescriptor::cleanupTestCase()
{

}

void TestLucidDescriptor::test_defaultConstructor()
{
  /// Check default values
  LucidDescriptor lucidDescriptor;
  QCOMPARE(1, lucidDescriptor.lucidKernel());
  QCOMPARE(2, lucidDescriptor.blurKernel());
}

void TestLucidDescriptor::test_constructor()
{
  LucidDescriptor lucidDescriptor(3, 3);
  QCOMPARE(3, lucidDescriptor.lucidKernel());
  QCOMPARE(3, lucidDescriptor.blurKernel());
}

void TestLucidDescriptor::test_type()
{
  QCOMPARE(LucidDescriptor::Type::lucid, mLucidDescriptor->type());
}

void TestLucidDescriptor::test_name()
{
  QCOMPARE("LUCID", mLucidDescriptor->name());
}

void TestLucidDescriptor::test_lucidKernel_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestLucidDescriptor::test_lucidKernel()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLucidDescriptor->setLucidKernel(value);
  QCOMPARE(result, mLucidDescriptor->lucidKernel());
}

void TestLucidDescriptor::test_blurKernel_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestLucidDescriptor::test_blurKernel()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLucidDescriptor->setBlurKernel(value);
  QCOMPARE(result, mLucidDescriptor->blurKernel());
}

void TestLucidDescriptor::test_reset()
{
  mLucidDescriptor->setLucidKernel(3);
  mLucidDescriptor->setBlurKernel(3);

  mLucidDescriptor->reset();

  QCOMPARE(1, mLucidDescriptor->lucidKernel());
  QCOMPARE(2, mLucidDescriptor->blurKernel());
}

QTEST_APPLESS_MAIN(TestLucidDescriptor)

#include "tst_luciddescriptor.moc"
