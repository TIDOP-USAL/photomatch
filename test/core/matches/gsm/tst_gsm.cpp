#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/features/matcher.h"

using namespace photomatch;

class TestGsm 
  : public QObject
{
  Q_OBJECT

public:

  TestGsm();
  ~TestGsm();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_rotation_data();
  void test_rotation();
  void test_scale_data();
  void test_scale();
  void test_threshold_data();
  void test_threshold();

private:

  std::shared_ptr<DescriptorMatcher> descriptorMatcher;
  GsmImp *mGsm;
};

TestGsm::TestGsm()
  : descriptorMatcher(new FlannMatcherImp()),
    mGsm(new GsmImp(descriptorMatcher))
{

}

TestGsm::~TestGsm()
{
  if (mGsm){
    delete mGsm;
    mGsm = nullptr;
  }
}

void TestGsm::initTestCase()
{
  QCOMPARE(true, mGsm->rotation());
  QCOMPARE(true, mGsm->scale());
  QCOMPARE(6.0, mGsm->threshold());
}

void TestGsm::cleanupTestCase()
{
  mGsm->reset();

  QCOMPARE(true, mGsm->rotation());
  QCOMPARE(true, mGsm->scale());
  QCOMPARE(6.0, mGsm->threshold());
}

void TestGsm::test_rotation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestGsm::test_rotation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mGsm->setRotation(value);
  QCOMPARE(result, mGsm->rotation());

}

void TestGsm::test_scale_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestGsm::test_scale()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mGsm->setScale(value);
  QCOMPARE(result, mGsm->scale());
}

void TestGsm::test_threshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.7") << 0.7 << 0.7;
  QTest::newRow("3.") << 3. << 3.;
}

void TestGsm::test_threshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mGsm->setThreshold(value);
  QCOMPARE(result, mGsm->threshold());
}


QTEST_MAIN(TestGsm)

#include "tst_gsm.moc"
