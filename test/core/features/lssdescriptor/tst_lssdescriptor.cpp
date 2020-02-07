#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/lss.h"

using namespace photomatch;

class TestLssDescriptor : public QObject
{
  Q_OBJECT

public:

  TestLssDescriptor();
  ~TestLssDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_type();
  void test_name();

private:

  LssDescriptor *mLssDescriptor;
};

TestLssDescriptor::TestLssDescriptor()
  : mLssDescriptor(new LssDescriptor)
{

}

TestLssDescriptor::~TestLssDescriptor()
{
  if (mLssDescriptor){
    delete mLssDescriptor;
    mLssDescriptor = nullptr;
  }
}

void TestLssDescriptor::initTestCase()
{

}

void TestLssDescriptor::cleanupTestCase()
{

}

void TestLssDescriptor::test_defaultConstructor()
{

}

void TestLssDescriptor::test_type()
{
  QCOMPARE(LssDescriptor::Type::lss, mLssDescriptor->type());
}

void TestLssDescriptor::test_name()
{
  QCOMPARE("LSS", mLssDescriptor->name());
}


QTEST_APPLESS_MAIN(TestLssDescriptor)

#include "tst_lssdescriptor.moc"
