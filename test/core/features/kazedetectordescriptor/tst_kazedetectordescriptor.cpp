#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/kaze.h"

using namespace photomatch;

class TestKazeDetectorDescriptor
  : public QObject
{
  Q_OBJECT

public:
  TestKazeDetectorDescriptor();
  ~TestKazeDetectorDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_type();
  void test_name();
  void test_extendedDescriptor_data();
  void test_extendedDescriptor();
  void test_upright_data();
  void test_upright();
  void test_threshold_data();
  void test_threshold();
  void test_octaves_data();
  void test_octaves();
  void test_octaveLayers_data();
  void test_octaveLayers();
  void test_diffusivity_data();
  void test_diffusivity();
  void test_reset();

private:

  KazeDetectorDescriptor *mKazeDetectorDescriptor;

};

TestKazeDetectorDescriptor::TestKazeDetectorDescriptor()
{
  mKazeDetectorDescriptor = new KazeDetectorDescriptor();
}

TestKazeDetectorDescriptor::~TestKazeDetectorDescriptor()
{
  if (mKazeDetectorDescriptor){
    delete mKazeDetectorDescriptor;
    mKazeDetectorDescriptor = nullptr;
  }
}

void TestKazeDetectorDescriptor::initTestCase()
{

}

void TestKazeDetectorDescriptor::cleanupTestCase()
{

}

void TestKazeDetectorDescriptor::test_defaultConstructor()
{
  /// Check default values
  KazeDetectorDescriptor kazeDetectorDescriptor;
  QCOMPARE(false, kazeDetectorDescriptor.extendedDescriptor());
  QCOMPARE(false, kazeDetectorDescriptor.upright());
  QCOMPARE(0.001, kazeDetectorDescriptor.threshold());
  QCOMPARE(4, kazeDetectorDescriptor.octaves());
  QCOMPARE(4, kazeDetectorDescriptor.octaveLayers());
  QCOMPARE("DIFF_PM_G2", kazeDetectorDescriptor.diffusivity());
}

void TestKazeDetectorDescriptor::test_constructor()
{
  KazeDetectorDescriptor kazeDetectorDescriptor(true, true, 0.05, 8, 3, "DIFF_PM_G1");
  QCOMPARE(true, kazeDetectorDescriptor.extendedDescriptor());
  QCOMPARE(true, kazeDetectorDescriptor.upright());
  QCOMPARE(0.05, kazeDetectorDescriptor.threshold());
  QCOMPARE(8, kazeDetectorDescriptor.octaves());
  QCOMPARE(3, kazeDetectorDescriptor.octaveLayers());
  QCOMPARE("DIFF_PM_G1", kazeDetectorDescriptor.diffusivity());
}

void TestKazeDetectorDescriptor::test_type()
{
  QCOMPARE(KazeDetectorDescriptor::Type::kaze, mKazeDetectorDescriptor->type());
}

void TestKazeDetectorDescriptor::test_name()
{
  QCOMPARE("KAZE", mKazeDetectorDescriptor->name());
}

void TestKazeDetectorDescriptor::test_extendedDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeDetectorDescriptor::test_extendedDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeDetectorDescriptor->setExtendedDescriptor(value);
  QCOMPARE(result, mKazeDetectorDescriptor->extendedDescriptor());
}

void TestKazeDetectorDescriptor::test_upright_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestKazeDetectorDescriptor::test_upright()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mKazeDetectorDescriptor->setUpright(value);
  QCOMPARE(result, mKazeDetectorDescriptor->upright());
}

void TestKazeDetectorDescriptor::test_threshold_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
}

void TestKazeDetectorDescriptor::test_threshold()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mKazeDetectorDescriptor->setThreshold(value);
  QCOMPARE(result, mKazeDetectorDescriptor->threshold());
}

void TestKazeDetectorDescriptor::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("4") << 4 << 4;
  QTest::newRow("8") << 8 << 8;
}

void TestKazeDetectorDescriptor::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeDetectorDescriptor->setOctaves(value);
  QCOMPARE(result, mKazeDetectorDescriptor->octaves());
}

void TestKazeDetectorDescriptor::test_octaveLayers_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("3") << 3 << 3;
  QTest::newRow("8") << 8 << 8;
}

void TestKazeDetectorDescriptor::test_octaveLayers()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mKazeDetectorDescriptor->setOctaveLayers(value);
  QCOMPARE(result, mKazeDetectorDescriptor->octaveLayers());
}

void TestKazeDetectorDescriptor::test_diffusivity_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
}

void TestKazeDetectorDescriptor::test_diffusivity()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << "DIFF_PM_G1";
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << "DIFF_PM_G2";
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << "DIFF_WEICKERT";
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << "DIFF_CHARBONNIER";
  QTest::newRow("bad_value") << "bad_value" << "DIFF_CHARBONNIER";
}

void TestKazeDetectorDescriptor::test_reset()
{
  mKazeDetectorDescriptor->setThreshold(50.);
  mKazeDetectorDescriptor->setOctaves(2);
  mKazeDetectorDescriptor->setOctaveLayers(5);
  mKazeDetectorDescriptor->setExtendedDescriptor(true);
  mKazeDetectorDescriptor->setUpright(true);
  mKazeDetectorDescriptor->setDiffusivity("DIFF_PM_G1");

  mKazeDetectorDescriptor->reset();

  QCOMPARE(false, mKazeDetectorDescriptor->extendedDescriptor());
  QCOMPARE(false, mKazeDetectorDescriptor->upright());
  QCOMPARE(0.001, mKazeDetectorDescriptor->threshold());
  QCOMPARE(4, mKazeDetectorDescriptor->octaves());
  QCOMPARE(4, mKazeDetectorDescriptor->octaveLayers());
  QCOMPARE("DIFF_PM_G2", mKazeDetectorDescriptor->diffusivity());
}

QTEST_APPLESS_MAIN(TestKazeDetectorDescriptor)

#include "tst_kazedetectordescriptor.moc"
