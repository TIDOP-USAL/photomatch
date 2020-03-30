#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/msrcp.h"

using namespace photomatch;

class TestMsrcp
  : public QObject
{
  Q_OBJECT

public:

  TestMsrcp();
  ~TestMsrcp();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_copyConstructor();
  void test_moveConstructor();
  void test_type();
  void test_name();
  void test_smallScale_data();
  void test_smallScale();
  void test_midScale_data();
  void test_midScale();
  void test_largeScale_data();
  void test_largeScale();

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

void TestMsrcp::initTestCase()
{
  QCOMPARE(10., mMsrcpPreprocess->smallScale());
  QCOMPARE(100., mMsrcpPreprocess->midScale());
  QCOMPARE(220., mMsrcpPreprocess->largeScale());
}

void TestMsrcp::cleanupTestCase()
{
  mMsrcpPreprocess->setSmallScale(15.);
  mMsrcpPreprocess->setMidScale(150.);
  mMsrcpPreprocess->setLargeScale(250.);

  mMsrcpPreprocess->reset();

  QCOMPARE(10., mMsrcpPreprocess->smallScale());
  QCOMPARE(100., mMsrcpPreprocess->midScale());
  QCOMPARE(220., mMsrcpPreprocess->largeScale());
}

void TestMsrcp::test_copyConstructor()
{
  MsrcpPreprocess msrcpPreprocess(20., 120., 200.);
  MsrcpPreprocess copy(msrcpPreprocess);
  QCOMPARE(20., copy.smallScale());
  QCOMPARE(120., copy.midScale());
  QCOMPARE(200., copy.largeScale());
}

void TestMsrcp::test_moveConstructor()
{
  MsrcpPreprocess move(std::move(MsrcpPreprocess(20., 120., 200.)));
  QCOMPARE(20., move.smallScale());
  QCOMPARE(120., move.midScale());
  QCOMPARE(200., move.largeScale());
}

void TestMsrcp::test_type()
{
  QCOMPARE(Preprocess::Type::msrcp, mMsrcpPreprocess->type());
}

void TestMsrcp::test_name()
{
  QCOMPARE(QString("MSRCP"), mMsrcpPreprocess->name());
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



QTEST_MAIN(TestMsrcp)

#include "tst_msrcp.moc"
