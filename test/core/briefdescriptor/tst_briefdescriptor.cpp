#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/brief.h"

using namespace fme;

class TestBriefDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestBriefDescriptor();
  ~TestBriefDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void test_bytes_data();
  void test_bytes();
  void test_useOrientation_data();
  void test_useOrientation();
  void test_reset();

private:

  BriefDescriptor *mBriefDescriptor;
};

TestBriefDescriptor::TestBriefDescriptor()
  : mBriefDescriptor(new BriefDescriptor)
{

}

TestBriefDescriptor::~TestBriefDescriptor()
{
  if (mBriefDescriptor){
    delete mBriefDescriptor;
    mBriefDescriptor = nullptr;
  }
}

void TestBriefDescriptor::initTestCase()
{

}

void TestBriefDescriptor::cleanupTestCase()
{

}

void TestBriefDescriptor::testDefaultConstructor()
{
  /// Check default values
  BriefDescriptor briefDescriptor;
  QCOMPARE("32", briefDescriptor.bytes());
  QCOMPARE(false, briefDescriptor.useOrientation());
}

void TestBriefDescriptor::test_type()
{
  QCOMPARE(BriefDescriptor::Type::brief, mBriefDescriptor->type());
}

void TestBriefDescriptor::test_bytes_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("16") << "16" << "16";
  QTest::newRow("32") << "32" << "32";
  QTest::newRow("64") << "64" << "64";
  QTest::newRow("128") << "128" << "64";

}

void TestBriefDescriptor::test_bytes()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mBriefDescriptor->setBytes(value);
  QCOMPARE(result, mBriefDescriptor->bytes());
}

void TestBriefDescriptor::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestBriefDescriptor::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mBriefDescriptor->setUseOrientation(value);
  QCOMPARE(result, mBriefDescriptor->useOrientation());
}

void TestBriefDescriptor::test_reset()
{
  mBriefDescriptor->setBytes("16");
  mBriefDescriptor->setUseOrientation(true);

  mBriefDescriptor->reset();

  QCOMPARE("32", mBriefDescriptor->bytes());
  QCOMPARE(false, mBriefDescriptor->useOrientation());
}

QTEST_APPLESS_MAIN(TestBriefDescriptor)

#include "tst_briefdescriptor.moc"
