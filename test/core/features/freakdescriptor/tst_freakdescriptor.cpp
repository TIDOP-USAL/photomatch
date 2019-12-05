#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/freak.h"

using namespace photomatch;

class TestFreakDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestFreakDescriptor();
  ~TestFreakDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_orientationNormalized_data();
  void test_orientationNormalized();
  void test_scaleNormalized_data();
  void test_scaleNormalized();
  void test_patternScale_data();
  void test_patternScale();
  void test_octaves_data();
  void test_octaves();
  void test_reset();

private:

  FreakDescriptor *mFreakDescriptor;
};

TestFreakDescriptor::TestFreakDescriptor()
  : mFreakDescriptor(new FreakDescriptor)
{

}

TestFreakDescriptor::~TestFreakDescriptor()
{
  if (mFreakDescriptor){
    delete mFreakDescriptor;
    mFreakDescriptor = nullptr;
  }
}

void TestFreakDescriptor::initTestCase()
{

}

void TestFreakDescriptor::cleanupTestCase()
{

}

void TestFreakDescriptor::test_defaultConstructor()
{
  /// Check default values
  FreakDescriptor freakDescriptor;
  QCOMPARE(true, freakDescriptor.orientationNormalized());
  QCOMPARE(true, freakDescriptor.scaleNormalized());
  QCOMPARE(22., freakDescriptor.patternScale());
  QCOMPARE(4, freakDescriptor.octaves());
}

void TestFreakDescriptor::test_constructor()
{
  FreakDescriptor freakDescriptor(false, false, 11., 8);
  QCOMPARE(false, freakDescriptor.orientationNormalized());
  QCOMPARE(false, freakDescriptor.scaleNormalized());
  QCOMPARE(11., freakDescriptor.patternScale());
  QCOMPARE(8, freakDescriptor.octaves());
}

void TestFreakDescriptor::test_copy_constructor()
{
  FreakDescriptor freakDescriptor(false, false, 11., 8);
  FreakDescriptor copy(freakDescriptor);
  QCOMPARE(false, copy.orientationNormalized());
  QCOMPARE(false, copy.scaleNormalized());
  QCOMPARE(11., copy.patternScale());
  QCOMPARE(8, copy.octaves());
}

void TestFreakDescriptor::test_type()
{
  QCOMPARE(FreakDescriptor::Type::freak, mFreakDescriptor->type());
}

void TestFreakDescriptor::test_name()
{
  QCOMPARE("FREAK", mFreakDescriptor->name());
}

void TestFreakDescriptor::test_orientationNormalized_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestFreakDescriptor::test_orientationNormalized()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFreakDescriptor->setOrientationNormalized(value);
  QCOMPARE(result, mFreakDescriptor->orientationNormalized());
}

void TestFreakDescriptor::test_scaleNormalized_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestFreakDescriptor::test_scaleNormalized()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFreakDescriptor->setScaleNormalized(value);
  QCOMPARE(result, mFreakDescriptor->scaleNormalized());
}

void TestFreakDescriptor::test_patternScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
}

void TestFreakDescriptor::test_patternScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mFreakDescriptor->setPatternScale(value);
  QCOMPARE(result, mFreakDescriptor->patternScale());
}

void TestFreakDescriptor::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("4") << 4 << 4;
}

void TestFreakDescriptor::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mFreakDescriptor->setOctaves(value);
  QCOMPARE(result, mFreakDescriptor->octaves());
}

void TestFreakDescriptor::test_reset()
{
  mFreakDescriptor->setOrientationNormalized(false);
  mFreakDescriptor->setScaleNormalized(false);
  mFreakDescriptor->setPatternScale(35.);
  mFreakDescriptor->setOctaves(8);

  mFreakDescriptor->reset();

  QCOMPARE(true, mFreakDescriptor->orientationNormalized());
  QCOMPARE(true, mFreakDescriptor->scaleNormalized());
  QCOMPARE(22., mFreakDescriptor->patternScale());
  QCOMPARE(4, mFreakDescriptor->octaves());
}


QTEST_APPLESS_MAIN(TestFreakDescriptor)

#include "tst_freakdescriptor.moc"
