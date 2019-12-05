#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/boost.h"

using namespace photomatch;

class TestBoostDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestBoostDescriptor();
  ~TestBoostDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_descriptorType_data();
  void test_descriptorType();
  void test_scaleFactor_data();
  void test_scaleFactor();
  void test_useOrientation_data();
  void test_useOrientation();
  void test_reset();

private:

  BoostDescriptor *mBoostDescriptor;
};

TestBoostDescriptor::TestBoostDescriptor()
  : mBoostDescriptor(new BoostDescriptor)
{

}

TestBoostDescriptor::~TestBoostDescriptor()
{
  if (mBoostDescriptor){
    delete mBoostDescriptor;
    mBoostDescriptor = nullptr;
  }
}

void TestBoostDescriptor::initTestCase()
{

}

void TestBoostDescriptor::cleanupTestCase()
{

}

void TestBoostDescriptor::test_defaultConstructor()
{
  /// Check default values
  BoostDescriptor boostDescriptor;
  QCOMPARE("BINBOOST_256", boostDescriptor.descriptorType());
  QCOMPARE(true, boostDescriptor.useOrientation());
  QCOMPARE(6.25, boostDescriptor.scaleFactor());
}

void TestBoostDescriptor::test_constructor()
{
  /// Check default values
  BoostDescriptor boostDescriptor("BGM_BILINEAR", false, 5.00);
  QCOMPARE("BGM_BILINEAR", boostDescriptor.descriptorType());
  QCOMPARE(false, boostDescriptor.useOrientation());
  QCOMPARE(5.00, boostDescriptor.scaleFactor());
}

void TestBoostDescriptor::test_copy_constructor()
{
  BoostDescriptor obj("BGM_BILINEAR", false, 5.00);
  BoostDescriptor copy(obj);
  QCOMPARE("BGM_BILINEAR", copy.descriptorType());
  QCOMPARE(false, copy.useOrientation());
  QCOMPARE(5.00, copy.scaleFactor());
}

void TestBoostDescriptor::test_type()
{
  QCOMPARE(BoostDescriptor::Type::boost, mBoostDescriptor->type());
}

void TestBoostDescriptor::test_name()
{
    QCOMPARE("BOOST", mBoostDescriptor->name());
}

void TestBoostDescriptor::test_descriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("BGM") << "BGM" << "BGM";
  QTest::newRow("BGM_HARD") << "BGM_HARD" << "BGM_HARD";
  QTest::newRow("BGM_BILINEAR") << "BGM_BILINEAR" << "BGM_BILINEAR";
  QTest::newRow("LBGM") << "LBGM" << "LBGM";
  QTest::newRow("BINBOOST_64") << "BINBOOST_64" << "BINBOOST_64";
  QTest::newRow("BINBOOST_128") << "BINBOOST_128" << "BINBOOST_128";
  QTest::newRow("BINBOOST_256") << "BINBOOST_256" << "BINBOOST_256";
}

void TestBoostDescriptor::test_descriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mBoostDescriptor->setDescriptorType(value);
  QCOMPARE(result, mBoostDescriptor->descriptorType());
}

void TestBoostDescriptor::test_scaleFactor_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("result");

    QTest::newRow("6.75") << 6.75 << 6.75;
    QTest::newRow("6.25") << 6.25 << 6.25;
    QTest::newRow("5.00") << 5.00 << 5.00;
    QTest::newRow("0.75") << 0.75 << 0.75;
    QTest::newRow("1.50") << 1.50 << 1.50;
}

void TestBoostDescriptor::test_scaleFactor()
{
    QFETCH(double, value);
    QFETCH(double, result);

    mBoostDescriptor->setScaleFactor(value);
    QCOMPARE(result, mBoostDescriptor->scaleFactor());
}

void TestBoostDescriptor::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestBoostDescriptor::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mBoostDescriptor->setUseOrientation(value);
  QCOMPARE(result, mBoostDescriptor->useOrientation());
}

void TestBoostDescriptor::test_reset()
{
  mBoostDescriptor->setDescriptorType("BGM");
  mBoostDescriptor->setUseOrientation(false);
  mBoostDescriptor->setScaleFactor(6.75);

  mBoostDescriptor->reset();

  QCOMPARE("BINBOOST_256", mBoostDescriptor->descriptorType());
  QCOMPARE(true, mBoostDescriptor->useOrientation());
  QCOMPARE(6.25, mBoostDescriptor->scaleFactor());
}

QTEST_APPLESS_MAIN(TestBoostDescriptor)

#include "tst_boostdescriptor.moc"
