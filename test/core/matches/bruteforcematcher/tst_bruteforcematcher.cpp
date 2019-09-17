#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/features/matcher.h"

using namespace fme;

class TestBruteForceMatcher 
  : public QObject
{
  Q_OBJECT

public:

  TestBruteForceMatcher();
  ~TestBruteForceMatcher();

private slots:

  void test_defaultConstructor();
  void test_type();
  void test_name();
  void test_normType_data();
  void test_normType();
  void test_reset();

private:

  BruteForceMatcher *mBruteForceMatcher;
};

TestBruteForceMatcher::TestBruteForceMatcher()
  : mBruteForceMatcher(new BruteForceMatcher)
{

}

TestBruteForceMatcher::~TestBruteForceMatcher()
{
  if (mBruteForceMatcher){
    delete mBruteForceMatcher;
    mBruteForceMatcher = nullptr;
  }
}

void TestBruteForceMatcher::test_defaultConstructor()
{
  BruteForceMatcher bruteForceMatcher;
  QCOMPARE(BruteForceMatcherProperties::Norm::l2, bruteForceMatcher.normType());

}

void TestBruteForceMatcher::test_type()
{
  QCOMPARE(Match::Type::brute_force, mBruteForceMatcher->type());
}

void TestBruteForceMatcher::test_name()
{
  QCOMPARE(QString("Brute Force Matching"), mBruteForceMatcher->name());
}

void TestBruteForceMatcher::test_normType_data()
{
  QTest::addColumn<BruteForceMatcherProperties::Norm>("value");
  QTest::addColumn<BruteForceMatcherProperties::Norm>("result");

  QTest::newRow("IBruteForceMatcher::Norm::l1") << IBruteForceMatcher::Norm::l1 << IBruteForceMatcher::Norm::l1;
  QTest::newRow("IBruteForceMatcher::Norm::l2") << IBruteForceMatcher::Norm::l2 << IBruteForceMatcher::Norm::l2;
  QTest::newRow("IBruteForceMatcher::Norm::hamming") << IBruteForceMatcher::Norm::hamming << IBruteForceMatcher::Norm::hamming;
  QTest::newRow("IBruteForceMatcher::Norm::hamming2") << IBruteForceMatcher::Norm::hamming2 << IBruteForceMatcher::Norm::hamming2;
}

void TestBruteForceMatcher::test_normType()
{
  QFETCH(BruteForceMatcherProperties::Norm, value);
  QFETCH(BruteForceMatcherProperties::Norm, result);

  mBruteForceMatcher->setNormType(value);
  QCOMPARE(result, mBruteForceMatcher->normType());
}

void TestBruteForceMatcher::test_reset()
{
  mBruteForceMatcher->setNormType(IBruteForceMatcher::Norm::hamming2);

  mBruteForceMatcher->reset();

  QCOMPARE(IBruteForceMatcher::Norm::l2, mBruteForceMatcher->normType());
}


QTEST_MAIN(TestBruteForceMatcher)

#include "tst_bruteforcematcher.moc"
