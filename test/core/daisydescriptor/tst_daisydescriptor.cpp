#include <QtTest>
#include <QCoreApplication>

#include "fme/core/features/daisy.h"

using namespace fme;

class TestDaisyDescriptor : public QObject
{
  Q_OBJECT

public:

  TestDaisyDescriptor();
  ~TestDaisyDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_type();
  void test_radius_data();
  void test_radius();
  void test_qRadius_data();
  void test_qRadius();
  void test_qTheta_data();
  void test_qTheta();
  void test_qHist_data();
  void test_qHist();
  void test_norm_data();
  void test_norm();
  void test_interpolation_data();
  void test_interpolation();
  void test_useOrientation_data();
  void test_useOrientation();
  void test_reset();

private:

  DaisyDescriptor *mDaisyDescriptor;
};

TestDaisyDescriptor::TestDaisyDescriptor()
  : mDaisyDescriptor(new DaisyDescriptor)
{

}

TestDaisyDescriptor::~TestDaisyDescriptor()
{
  if (mDaisyDescriptor){
    delete mDaisyDescriptor;
    mDaisyDescriptor = nullptr;
  }
}

void TestDaisyDescriptor::initTestCase()
{

}

void TestDaisyDescriptor::cleanupTestCase()
{

}

void TestDaisyDescriptor::testDefaultConstructor()
{
  /// Check default values
  DaisyDescriptor daisyDescriptor;
  QCOMPARE(15., daisyDescriptor.radius());
  QCOMPARE(3, daisyDescriptor.qRadius());
  QCOMPARE(8, daisyDescriptor.qTheta());
  QCOMPARE(8, daisyDescriptor.qHist());
  QCOMPARE("NRM_NONE", daisyDescriptor.norm());
  QCOMPARE(true, daisyDescriptor.interpolation());
  QCOMPARE(false, daisyDescriptor.useOrientation());
}

void TestDaisyDescriptor::test_type()
{
  QCOMPARE(DaisyDescriptor::Type::daisy, mDaisyDescriptor->type());
}

void TestDaisyDescriptor::test_radius_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
}

void TestDaisyDescriptor::test_radius()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDaisyDescriptor->setRadius(value);
  QCOMPARE(result, mDaisyDescriptor->radius());
}

void TestDaisyDescriptor::test_qRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
}

void TestDaisyDescriptor::test_qRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyDescriptor->setQRadius(value);
  QCOMPARE(result, mDaisyDescriptor->qRadius());
}

void TestDaisyDescriptor::test_qTheta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 50 << 50;
}

void TestDaisyDescriptor::test_qTheta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyDescriptor->setQTheta(value);
  QCOMPARE(result, mDaisyDescriptor->qTheta());
}

void TestDaisyDescriptor::test_qHist_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
}

void TestDaisyDescriptor::test_qHist()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyDescriptor->setQHist(value);
  QCOMPARE(result, mDaisyDescriptor->qHist());
}

void TestDaisyDescriptor::test_norm_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("NRM_NONE") << "NRM_NONE" << "NRM_NONE";
  QTest::newRow("NRM_PARTIAL") << "NRM_PARTIAL" << "NRM_PARTIAL";
  QTest::newRow("NRM_FULL") << "NRM_FULL" << "NRM_FULL";
  QTest::newRow("NRM_SIFT") << "NRM_SIFT" << "NRM_SIFT";
}

void TestDaisyDescriptor::test_norm()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDaisyDescriptor->setNorm(value);
  QCOMPARE(result, mDaisyDescriptor->norm());
}

void TestDaisyDescriptor::test_interpolation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyDescriptor::test_interpolation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyDescriptor->setInterpolation(value);
  QCOMPARE(result, mDaisyDescriptor->interpolation());
}

void TestDaisyDescriptor::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyDescriptor::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyDescriptor->setUseOrientation(value);
  QCOMPARE(result, mDaisyDescriptor->useOrientation());
}

void TestDaisyDescriptor::test_reset()
{
  mDaisyDescriptor->setRadius(30.);
  mDaisyDescriptor->setQRadius(5);
  mDaisyDescriptor->setQTheta(4);
  mDaisyDescriptor->setQHist(4);
  mDaisyDescriptor->setNorm("NRM_FULL");
  mDaisyDescriptor->setInterpolation(false);
  mDaisyDescriptor->setUseOrientation(true);

  mDaisyDescriptor->reset();

  /// Check default values
  QCOMPARE(15., mDaisyDescriptor->radius());
  QCOMPARE(3, mDaisyDescriptor->qRadius());
  QCOMPARE(8, mDaisyDescriptor->qTheta());
  QCOMPARE(8, mDaisyDescriptor->qHist());
  QCOMPARE("NRM_NONE", mDaisyDescriptor->norm());
  QCOMPARE(true, mDaisyDescriptor->interpolation());
  QCOMPARE(false, mDaisyDescriptor->useOrientation());
}

QTEST_APPLESS_MAIN(TestDaisyDescriptor)

#include "tst_daisydescriptor.moc"
