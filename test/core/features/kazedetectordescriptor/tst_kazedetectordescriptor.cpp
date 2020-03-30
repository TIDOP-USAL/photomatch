#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/kaze.h"

using namespace photomatch;

class TestKazeDetectorDescriptor
  : public QObject,
    public KazeDetectorDescriptor
{
  Q_OBJECT

public:
  TestKazeDetectorDescriptor();
  ~TestKazeDetectorDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_copy_constructor();
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
  void test_diffusivity2_data();
  void test_diffusivity2();

};

TestKazeDetectorDescriptor::TestKazeDetectorDescriptor()
  : KazeDetectorDescriptor()
{
}

TestKazeDetectorDescriptor::~TestKazeDetectorDescriptor()
{
}

void TestKazeDetectorDescriptor::initTestCase()
{
  QCOMPARE(false, this->extendedDescriptor());
  QCOMPARE(false, this->upright());
  QCOMPARE(0.001, this->threshold());
  QCOMPARE(4, this->octaves());
  QCOMPARE(4, this->octaveLayers());
  QCOMPARE("DIFF_PM_G2", this->diffusivity());
}

void TestKazeDetectorDescriptor::cleanupTestCase()
{
  this->setThreshold(50.);
  this->setOctaves(2);
  this->setOctaveLayers(5);
  this->setExtendedDescriptor(true);
  this->setUpright(true);
  this->setDiffusivity("DIFF_PM_G1");

  this->reset();

  QCOMPARE(false, this->extendedDescriptor());
  QCOMPARE(false, this->mKaze->getExtended());
  QCOMPARE(false, this->upright());
  QCOMPARE(false, this->mKaze->getUpright());
  QCOMPARE(0.001, this->threshold());
  //QCOMPARE(0.001, this->mKaze->getThreshold());
  QCOMPARE(4, this->octaves());
  QCOMPARE(4, this->mKaze->getNOctaves());
  QCOMPARE(4, this->octaveLayers());
  QCOMPARE(4, this->mKaze->getNOctaveLayers());
  QCOMPARE("DIFF_PM_G2", this->diffusivity());
  QCOMPARE(1, this->mKaze->getDiffusivity());
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

void TestKazeDetectorDescriptor::test_copy_constructor()
{
  KazeDetectorDescriptor kazeDetectorDescriptor(true, true, 0.05, 8, 3, "DIFF_PM_G1");
  KazeDetectorDescriptor c(kazeDetectorDescriptor);
  QCOMPARE(true, c.extendedDescriptor());
  QCOMPARE(true, c.upright());
  QCOMPARE(0.05, c.threshold());
  QCOMPARE(8, c.octaves());
  QCOMPARE(3, c.octaveLayers());
  QCOMPARE("DIFF_PM_G1", c.diffusivity());
}

void TestKazeDetectorDescriptor::test_type()
{
  QCOMPARE(KazeDetectorDescriptor::Type::kaze, this->type());
}

void TestKazeDetectorDescriptor::test_name()
{
  QCOMPARE("KAZE", this->name());
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

  this->setExtendedDescriptor(value);
  QCOMPARE(result, this->extendedDescriptor());
  QCOMPARE(result, this->mKaze->getExtended());
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

  this->setUpright(value);
  QCOMPARE(result, this->upright());
  QCOMPARE(result, this->mKaze->getUpright());
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

  this->setThreshold(value);
  QCOMPARE(result, this->threshold());
  QCOMPARE(result, this->mKaze->getThreshold());
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

  this->setOctaves(value);
  QCOMPARE(result, this->octaves());
  QCOMPARE(result, this->mKaze->getNOctaves());
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

  this->setOctaveLayers(value);
  QCOMPARE(result, this->octaveLayers());
  QCOMPARE(result, this->mKaze->getNOctaveLayers());
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
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setDiffusivity(value);
  QCOMPARE(result, this->diffusivity());
}

void TestKazeDetectorDescriptor::test_diffusivity2_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("DIFF_PM_G1") << "DIFF_PM_G1" << 0;
  QTest::newRow("DIFF_PM_G2") << "DIFF_PM_G2" << 1;
  QTest::newRow("DIFF_WEICKERT") << "DIFF_WEICKERT" << 2;
  QTest::newRow("DIFF_CHARBONNIER") << "DIFF_CHARBONNIER" << 3;
}

void TestKazeDetectorDescriptor::test_diffusivity2()
{
  QFETCH(QString, value);
  QFETCH(int, result);

  this->setDiffusivity(value);
  QCOMPARE(result, this->mKaze->getDiffusivity());
}


QTEST_APPLESS_MAIN(TestKazeDetectorDescriptor)

#include "tst_kazedetectordescriptor.moc"
