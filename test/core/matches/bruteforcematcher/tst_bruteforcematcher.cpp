#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/features/matcher.h"

using namespace photomatch;

class TestBruteForceMatcher 
  : public QObject
{
  Q_OBJECT

public:

  TestBruteForceMatcher();
  ~TestBruteForceMatcher();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_type();
  void test_name();
  void test_normType_data();
  void test_normType();

private:

  BruteForceMatcherImp *mBruteForceMatcher;
};

TestBruteForceMatcher::TestBruteForceMatcher()
  : mBruteForceMatcher(new BruteForceMatcherImp)
{

}

TestBruteForceMatcher::~TestBruteForceMatcher()
{
  if (mBruteForceMatcher){
    delete mBruteForceMatcher;
    mBruteForceMatcher = nullptr;
  }
}

void TestBruteForceMatcher::initTestCase()
{
  QCOMPARE(BruteForceMatcher::Norm::l2, mBruteForceMatcher->normType());
}

void TestBruteForceMatcher::cleanupTestCase()
{
  mBruteForceMatcher->setNormType(BruteForceMatcher::Norm::hamming2);

  mBruteForceMatcher->reset();

  QCOMPARE(BruteForceMatcher::Norm::l2, mBruteForceMatcher->normType());
}

void TestBruteForceMatcher::test_type()
{
  QCOMPARE(MatchingMethod::Type::brute_force, mBruteForceMatcher->type());
}

void TestBruteForceMatcher::test_name()
{
  QCOMPARE(QString("Brute Force Matching"), mBruteForceMatcher->name());
}

void TestBruteForceMatcher::test_normType_data()
{
  QTest::addColumn<BruteForceMatcherProperties::Norm>("value");
  QTest::addColumn<BruteForceMatcherProperties::Norm>("result");

  QTest::newRow("IBruteForceMatcher::Norm::l1") << BruteForceMatcher::Norm::l1 << BruteForceMatcher::Norm::l1;
  QTest::newRow("IBruteForceMatcher::Norm::l2") << BruteForceMatcher::Norm::l2 << BruteForceMatcher::Norm::l2;
  QTest::newRow("IBruteForceMatcher::Norm::hamming") << BruteForceMatcher::Norm::hamming << BruteForceMatcher::Norm::hamming;
  QTest::newRow("IBruteForceMatcher::Norm::hamming2") << BruteForceMatcher::Norm::hamming2 << BruteForceMatcher::Norm::hamming2;
}

void TestBruteForceMatcher::test_normType()
{
  QFETCH(BruteForceMatcherProperties::Norm, value);
  QFETCH(BruteForceMatcherProperties::Norm, result);

  mBruteForceMatcher->setNormType(value);
  QCOMPARE(result, mBruteForceMatcher->normType());
}


QTEST_MAIN(TestBruteForceMatcher)

#include "tst_bruteforcematcher.moc"
