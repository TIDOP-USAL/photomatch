#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/brisk.h"

using namespace fme;

class TestBriskDetectorDescriptor
  : public QObject
{
    Q_OBJECT

public:

  TestBriskDetectorDescriptor();
  ~TestBriskDetectorDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_type();
  void test_name();
  void testThreshold_data();
  void testThreshold();
  void testOctaves_data();
  void testOctaves();
  void testPatternScale_data();
  void testPatternScale();
  void testReset();

private:

  BriskDetectorDescriptor *mBriskDetectorDescriptor;

};

TestBriskDetectorDescriptor::TestBriskDetectorDescriptor()
  : mBriskDetectorDescriptor(new BriskDetectorDescriptor)
{

}

TestBriskDetectorDescriptor::~TestBriskDetectorDescriptor()
{
  delete mBriskDetectorDescriptor;
}

void TestBriskDetectorDescriptor::initTestCase()
{

}

void TestBriskDetectorDescriptor::cleanupTestCase()
{

}

void TestBriskDetectorDescriptor::test_defaultConstructor()
{
  BriskDetectorDescriptor briskDetectorDescriptor;
  QCOMPARE(30, briskDetectorDescriptor.threshold());
  QCOMPARE(3, briskDetectorDescriptor.octaves());
  QCOMPARE(1.0, briskDetectorDescriptor.patternScale());
}

void TestBriskDetectorDescriptor::test_constructor()
{
  BriskDetectorDescriptor briskDetectorDescriptor(15, 4, 2.);
  QCOMPARE(15, briskDetectorDescriptor.threshold());
  QCOMPARE(4, briskDetectorDescriptor.octaves());
  QCOMPARE(2.0, briskDetectorDescriptor.patternScale());
}

void TestBriskDetectorDescriptor::test_type()
{
  QCOMPARE(BriskDetectorDescriptor::Type::brisk, mBriskDetectorDescriptor->type());
}

void TestBriskDetectorDescriptor::test_name()
{
  QCOMPARE("BRISK", mBriskDetectorDescriptor->name());
}

void TestBriskDetectorDescriptor::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
}

void TestBriskDetectorDescriptor::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskDetectorDescriptor->setThreshold(value);
  QCOMPARE(result, mBriskDetectorDescriptor->threshold());
}

void TestBriskDetectorDescriptor::testOctaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
}

void TestBriskDetectorDescriptor::testOctaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mBriskDetectorDescriptor->setOctaves(value);
  QCOMPARE(result, mBriskDetectorDescriptor->octaves());
}

void TestBriskDetectorDescriptor::testPatternScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("2") << 2. << 2.;
  QTest::newRow("8") << 8. << 8.;
}

void TestBriskDetectorDescriptor::testPatternScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mBriskDetectorDescriptor->setPatternScale(value);
  QCOMPARE(result, mBriskDetectorDescriptor->patternScale());
}

void TestBriskDetectorDescriptor::testReset()
{
  mBriskDetectorDescriptor->setThreshold(50);
  mBriskDetectorDescriptor->setOctaves(4);
  mBriskDetectorDescriptor->setPatternScale(2.0);

  mBriskDetectorDescriptor->reset();

  QCOMPARE(30, mBriskDetectorDescriptor->threshold());
  QCOMPARE(3, mBriskDetectorDescriptor->octaves());
  QCOMPARE(1.0, mBriskDetectorDescriptor->patternScale());
}


QTEST_APPLESS_MAIN(TestBriskDetectorDescriptor)

#include "tst_briskdetectordescriptor.moc"
