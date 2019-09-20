#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/lss.h"

using namespace fme;

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
  void test_reset();

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
  /// Check default values
  //LssDescriptor lssDescriptor;
}

void TestLssDescriptor::test_type()
{
  QCOMPARE(LssDescriptor::Type::lss, mLssDescriptor->type());
}

void TestLssDescriptor::test_name()
{
  QCOMPARE("LSS", mLssDescriptor->name());
}

void TestLssDescriptor::test_reset()
{

}

QTEST_APPLESS_MAIN(TestLssDescriptor)

#include "tst_lssdescriptor.moc"
