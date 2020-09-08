#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/features/flann.h"

using namespace photomatch;

class TestFlannMatcher 
  : public QObject
{
  Q_OBJECT

public:

  TestFlannMatcher();
  ~TestFlannMatcher();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_type();
  void test_name();
  void test_index();

private:

  FlannMatcherImp *mFlannMatcher;
};

TestFlannMatcher::TestFlannMatcher()
  : mFlannMatcher(new FlannMatcherImp)
{

}

TestFlannMatcher::~TestFlannMatcher()
{
  if (mFlannMatcher){
    delete mFlannMatcher;
    mFlannMatcher = nullptr;
    }
}

void TestFlannMatcher::initTestCase()
{
  QCOMPARE(FlannMatcherProperties::Index::kdtree, mFlannMatcher->index());
}

void TestFlannMatcher::cleanupTestCase()
{
  mFlannMatcher->reset();

  QCOMPARE(FlannMatcherProperties::Index::kdtree, mFlannMatcher->index());
}

void TestFlannMatcher::test_type()
{
  QCOMPARE(MatchingMethod::Type::flann, mFlannMatcher->type());
}

void TestFlannMatcher::test_name()
{
  QCOMPARE(QString("Flann Based Matching"), mFlannMatcher->name());
}

void TestFlannMatcher::test_index()
{
  mFlannMatcher->setIndex(FlannMatcherProperties::Index::lsh);
  QCOMPARE(FlannMatcherProperties::Index::lsh, mFlannMatcher->index());
}


QTEST_MAIN(TestFlannMatcher)

#include "tst_flannmatcher.moc"
