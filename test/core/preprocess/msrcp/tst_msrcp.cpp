#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/preprocess/msrcp.h"

using namespace fme;

class TestMsrcp
  : public QObject
{
  Q_OBJECT

public:

  TestMsrcp();
  ~TestMsrcp();

private slots:

  void testDefaultConstructor();
  void test_type();
  void test_smallScale_data();
  void test_smallScale();
  void test_midScale_data();
  void test_midScale();
  void test_largeScale_data();
  void test_largeScale();
  void test_reset();

private:

  MsrcpPreprocess *mMsrcpPreprocess;
};

TestMsrcp::TestMsrcp()
  : mMsrcpPreprocess(new MsrcpPreprocess)
{

}

TestMsrcp::~TestMsrcp()
{
  if (mMsrcpPreprocess){
    delete mMsrcpPreprocess;
    mMsrcpPreprocess = nullptr;
  }
}

void TestMsrcp::testDefaultConstructor()
{
  MsrcpPreprocess msrcpPreprocess;
  QCOMPARE(10., msrcpPreprocess.smallScale());
  QCOMPARE(100., msrcpPreprocess.midScale());
  QCOMPARE(220., msrcpPreprocess.largeScale());
}

void TestMsrcp::test_type()
{
  QCOMPARE(Preprocess::Type::msrcp, mMsrcpPreprocess->type());
}

void TestMsrcp::test_smallScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
}

void TestMsrcp::test_smallScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpPreprocess->setSmallScale(value);
  QCOMPARE(result, mMsrcpPreprocess->smallScale());
}

void TestMsrcp::test_midScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("100.0") << 100.0 << 100.0;
}

void TestMsrcp::test_midScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpPreprocess->setMidScale(value);
  QCOMPARE(result, mMsrcpPreprocess->midScale());
}

void TestMsrcp::test_largeScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("220.0") << 220.0 << 220.0;
  QTest::newRow("100.0") << 250.0 << 250.0;
}

void TestMsrcp::test_largeScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mMsrcpPreprocess->setLargeScale(value);
  QCOMPARE(result, mMsrcpPreprocess->largeScale());
}

void TestMsrcp::test_reset()
{
  mMsrcpPreprocess->setSmallScale(15.);
  mMsrcpPreprocess->setMidScale(150.);
  mMsrcpPreprocess->setLargeScale(250.);

  mMsrcpPreprocess->reset();

  QCOMPARE(10., mMsrcpPreprocess->smallScale());
  QCOMPARE(100., mMsrcpPreprocess->midScale());
  QCOMPARE(220., mMsrcpPreprocess->largeScale());
}


QTEST_MAIN(TestMsrcp)

#include "tst_msrcp.moc"
