#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/orb.h"

using namespace photomatch;

class TestOrbDetectorDescriptor
  : public QObject,
    public OrbDetectorDescriptor
{
  Q_OBJECT

public:
  TestOrbDetectorDescriptor();
  ~TestOrbDetectorDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
  void test_featuresNumber_data();
  void test_featuresNumber();
  void test_scaleFactor();
  void test_levelsNumber();
  void test_edgeThreshold();
  void test_firstLevel();
  void test_wTA_K();
  void test_scoreType();
  void test_patchSize();
  void test_fastThreshold();
  void test_reset();

};

TestOrbDetectorDescriptor::TestOrbDetectorDescriptor()
  : OrbDetectorDescriptor()
{
}

TestOrbDetectorDescriptor::~TestOrbDetectorDescriptor()
{
}

void TestOrbDetectorDescriptor::initTestCase()
{

}

void TestOrbDetectorDescriptor::cleanupTestCase()
{

}

void TestOrbDetectorDescriptor::test_defaultConstructor()
{
  /// Check default values
  OrbDetectorDescriptor orbDetectorDescriptor;
  QCOMPARE(5000, orbDetectorDescriptor.featuresNumber());
  QCOMPARE(1.2, orbDetectorDescriptor.scaleFactor());
  QCOMPARE(8, orbDetectorDescriptor.levelsNumber());
  QCOMPARE(31, orbDetectorDescriptor.edgeThreshold());
  QCOMPARE(2, orbDetectorDescriptor.wta_k());
  QCOMPARE("Harris", orbDetectorDescriptor.scoreType());
  QCOMPARE(31, orbDetectorDescriptor.patchSize());
  QCOMPARE(20, orbDetectorDescriptor.fastThreshold());
}

void TestOrbDetectorDescriptor::test_constructor()
{
  /// Check default values
  OrbDetectorDescriptor orbDetectorDescriptor(4000, 1.5, 6, 11, 2, "FAST", 11, 10);
  QCOMPARE(4000, orbDetectorDescriptor.featuresNumber());
  QCOMPARE(1.5, orbDetectorDescriptor.scaleFactor());
  QCOMPARE(6, orbDetectorDescriptor.levelsNumber());
  QCOMPARE(11, orbDetectorDescriptor.edgeThreshold());
  QCOMPARE(2, orbDetectorDescriptor.wta_k());
  QCOMPARE("FAST", orbDetectorDescriptor.scoreType());
  QCOMPARE(11, orbDetectorDescriptor.patchSize());
  QCOMPARE(10, orbDetectorDescriptor.fastThreshold());
}

void TestOrbDetectorDescriptor::test_copy_constructor()
{
  OrbDetectorDescriptor orbDetectorDescriptor(4000, 1.5, 6, 11, 2, "FAST", 11, 10);
  OrbDetectorDescriptor c(orbDetectorDescriptor);
  QCOMPARE(4000, c.featuresNumber());
  QCOMPARE(1.5, c.scaleFactor());
  QCOMPARE(6, c.levelsNumber());
  QCOMPARE(11, c.edgeThreshold());

  QCOMPARE(2, c.wta_k());
  QCOMPARE("FAST", c.scoreType());
  QCOMPARE(11, c.patchSize());
  QCOMPARE(10, c.fastThreshold());
}

void TestOrbDetectorDescriptor::test_type()
{
  QCOMPARE(OrbDetectorDescriptor::Type::orb, this->type());
}

void TestOrbDetectorDescriptor::test_name()
{
  QCOMPARE("ORB", this->name());
}

void TestOrbDetectorDescriptor::test_featuresNumber_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("500") << 500 << 500;
  QTest::newRow("10000") << 10000 << 10000;
  QTest::newRow("20000") << 20000 << 20000;
}

void TestOrbDetectorDescriptor::test_featuresNumber()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setFeaturesNumber(value);
  QCOMPARE(result, this->featuresNumber());
  QCOMPARE(result, this->mOrb->getMaxFeatures());
}

void TestOrbDetectorDescriptor::test_scaleFactor()
{
  this->setScaleFactor(1.5);
  QCOMPARE(1.5, this->scaleFactor());
  QCOMPARE(1.5, this->mOrb->getScaleFactor());
}

void TestOrbDetectorDescriptor::test_levelsNumber()
{
  this->setLevelsNumber(4);
  QCOMPARE(4, this->levelsNumber());
  QCOMPARE(4, this->mOrb->getNLevels());
}

void TestOrbDetectorDescriptor::test_edgeThreshold()
{
  this->setEdgeThreshold(11);
  QCOMPARE(11, this->edgeThreshold());
  QCOMPARE(11, this->mOrb->getEdgeThreshold());
}

void TestOrbDetectorDescriptor::test_firstLevel()
{
  this->setFirstLevel(2);
  QCOMPARE(2, this->firstLevel());
  QCOMPARE(2, this->mOrb->getFirstLevel());
}

void TestOrbDetectorDescriptor::test_wTA_K()
{
  this->setWTA_K(3);
  QCOMPARE(3, this->wta_k());
  QCOMPARE(3, this->mOrb->getWTA_K());
}

void TestOrbDetectorDescriptor::test_scoreType()
{
  this->setScoreType("FAST");
  QCOMPARE("FAST", this->scoreType());
  QCOMPARE(1, this->mOrb->getScoreType());
}

void TestOrbDetectorDescriptor::test_patchSize()
{
  this->setPatchSize(3);
  QCOMPARE(3, this->patchSize());
  QCOMPARE(3, this->mOrb->getPatchSize());
}

void TestOrbDetectorDescriptor::test_fastThreshold()
{
  this->setFastThreshold(3);
  QCOMPARE(3, this->fastThreshold());
  QCOMPARE(3, this->mOrb->getFastThreshold());
}

void TestOrbDetectorDescriptor::test_reset()
{
  this->setFeaturesNumber(10000);
  this->setScaleFactor(1.5);
  this->setLevelsNumber(4);
  this->setEdgeThreshold(11);
  this->setWTA_K(3);
  this->setScoreType("FAST");
  this->setPatchSize(3);
  this->setFastThreshold(3);

  this->reset();

  QCOMPARE(5000, this->featuresNumber());
  QCOMPARE(5000, this->mOrb->getMaxFeatures());
  QCOMPARE(1.2, this->scaleFactor());
  QCOMPARE(1.2, this->mOrb->getScaleFactor());
  QCOMPARE(8, this->levelsNumber());
  QCOMPARE(8, this->mOrb->getNLevels());
  QCOMPARE(31, this->edgeThreshold());
  QCOMPARE(31, this->mOrb->getEdgeThreshold());
  QCOMPARE(2, this->wta_k());
  QCOMPARE(2, this->mOrb->getWTA_K());
  QCOMPARE("Harris", this->scoreType());
  QCOMPARE(0, this->mOrb->getScoreType());
  QCOMPARE(31, this->patchSize());
  QCOMPARE(31, this->mOrb->getPatchSize());
  QCOMPARE(20, this->fastThreshold());
  QCOMPARE(20, this->mOrb->getFastThreshold());
}

QTEST_APPLESS_MAIN(TestOrbDetectorDescriptor)

#include "tst_orbdetectordescriptor.moc"
