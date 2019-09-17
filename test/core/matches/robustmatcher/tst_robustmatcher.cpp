#include <QtTest>
#include <QCoreApplication>

#include "fme/fme_global.h"
#include "fme/core/features/matcher.h"

using namespace fme;

class TestRobustMatcher 
  : public QObject
{
  Q_OBJECT

public:

  TestRobustMatcher();
  ~TestRobustMatcher();

private slots:

  void test_defaultConstructor();
  void test_constructor();
  void test_ratio_data();
  void test_ratio();
  void test_crossCheck_data();
  void test_crossCheck();
  void test_geometricTest_data();
  void test_geometricTest();
  void test_homographyComputeMethod_data();
  void test_homographyComputeMethod();
  void test_fundamentalComputeMethod_data();
  void test_fundamentalComputeMethod();
  void test_essentialComputeMethod_data();
  void test_essentialComputeMethod();
  void test_distance_data();
  void test_distance();
  void test_confidence_data();
  void test_confidence();
  void test_maxIter_data();
  void test_maxIter();
  void test_reset();

private:

  std::shared_ptr<DescriptorMatcher> descriptorMatcher;
  RobustMatching *mRobustMatcher;
};

TestRobustMatcher::TestRobustMatcher()
  : descriptorMatcher(new FlannMatcher()),
    mRobustMatcher(new RobustMatching(descriptorMatcher))
{

}

TestRobustMatcher::~TestRobustMatcher()
{
  if (mRobustMatcher){
    delete mRobustMatcher;
    mRobustMatcher = nullptr;
  }
}

void TestRobustMatcher::test_defaultConstructor()
{
  std::shared_ptr<DescriptorMatcher> descriptorMatcher(new FlannMatcher());
  RobustMatching robustMatcher(descriptorMatcher);
  QCOMPARE(0.8, robustMatcher.ratio());
  QCOMPARE(true, robustMatcher.crossCheck());
  QCOMPARE(RobustMatcherProperties::GeometricTest::homography, robustMatcher.geometricTest());
  QCOMPARE(RobustMatcherProperties::HomographyComputeMethod::ransac, robustMatcher.homographyComputeMethod());
  QCOMPARE(RobustMatcherProperties::FundamentalComputeMethod::ransac, robustMatcher.fundamentalComputeMethod());
  QCOMPARE(RobustMatcherProperties::EssentialComputeMethod::ransac, robustMatcher.essentialComputeMethod());
  QCOMPARE(0.7, robustMatcher.distance());
  QCOMPARE(0.999, robustMatcher.confidence());
  QCOMPARE(2000, robustMatcher.maxIter());
}

void TestRobustMatcher::test_constructor()
{
  std::shared_ptr<DescriptorMatcher> descriptorMatcher(new FlannMatcher());
  RobustMatching robustMatcher(descriptorMatcher, 0.9, false,
                               RobustMatcherProperties::GeometricTest::fundamental,
                               RobustMatcherProperties::HomographyComputeMethod::lmeds,
                               RobustMatcherProperties::FundamentalComputeMethod::algorithm_7_point,
                               RobustMatcherProperties::EssentialComputeMethod::lmeds,
                               0.9, 0.995, 3000);
  QCOMPARE(0.9, robustMatcher.ratio());
  QCOMPARE(false, robustMatcher.crossCheck());
  QCOMPARE(RobustMatcherProperties::GeometricTest::fundamental, robustMatcher.geometricTest());
  QCOMPARE(RobustMatcherProperties::HomographyComputeMethod::lmeds, robustMatcher.homographyComputeMethod());
  QCOMPARE(RobustMatcherProperties::FundamentalComputeMethod::algorithm_7_point, robustMatcher.fundamentalComputeMethod());
  QCOMPARE(RobustMatcherProperties::EssentialComputeMethod::lmeds, robustMatcher.essentialComputeMethod());
  QCOMPARE(0.9, robustMatcher.distance());
  QCOMPARE(0.995, robustMatcher.confidence());
  QCOMPARE(3000, robustMatcher.maxIter());
}

void TestRobustMatcher::test_ratio_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("1.") << 1. << 1.;
  QTest::newRow("0.7") << 0.7 << 0.7;
}

void TestRobustMatcher::test_ratio()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mRobustMatcher->setRatio(value);
  QCOMPARE(result, mRobustMatcher->ratio());

}

void TestRobustMatcher::test_crossCheck_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestRobustMatcher::test_crossCheck()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mRobustMatcher->setCrossCheck(value);
  QCOMPARE(result, mRobustMatcher->crossCheck());
}

void TestRobustMatcher::test_geometricTest_data()
{
  QTest::addColumn<RobustMatcherProperties::GeometricTest>("value");
  QTest::addColumn<RobustMatcherProperties::GeometricTest>("result");

  QTest::newRow("essential") << RobustMatcherProperties::GeometricTest::essential << RobustMatcherProperties::GeometricTest::essential;
  QTest::newRow("homography") << RobustMatcherProperties::GeometricTest::homography << RobustMatcherProperties::GeometricTest::homography;
  QTest::newRow("fundamental") << RobustMatcherProperties::GeometricTest::fundamental << RobustMatcherProperties::GeometricTest::fundamental;
}

void TestRobustMatcher::test_geometricTest()
{
  QFETCH(RobustMatcherProperties::GeometricTest, value);
  QFETCH(RobustMatcherProperties::GeometricTest, result);

  mRobustMatcher->setGeometricTest(value);
  QCOMPARE(result, mRobustMatcher->geometricTest());
}

void TestRobustMatcher::test_homographyComputeMethod_data()
{
  QTest::addColumn<RobustMatcherProperties::HomographyComputeMethod>("value");
  QTest::addColumn<RobustMatcherProperties::HomographyComputeMethod>("result");

  QTest::newRow("all_points") << RobustMatcherProperties::HomographyComputeMethod::all_points << RobustMatcherProperties::HomographyComputeMethod::all_points;
  QTest::newRow("ransac") << RobustMatcherProperties::HomographyComputeMethod::ransac << RobustMatcherProperties::HomographyComputeMethod::ransac;
  QTest::newRow("lmeds") << RobustMatcherProperties::HomographyComputeMethod::lmeds << RobustMatcherProperties::HomographyComputeMethod::lmeds;
  QTest::newRow("rho") << RobustMatcherProperties::HomographyComputeMethod::rho << RobustMatcherProperties::HomographyComputeMethod::rho;
}

void TestRobustMatcher::test_homographyComputeMethod()
{
  QFETCH(RobustMatcherProperties::HomographyComputeMethod, value);
  QFETCH(RobustMatcherProperties::HomographyComputeMethod, result);

  mRobustMatcher->setHomographyComputeMethod(value);
  QCOMPARE(result, mRobustMatcher->homographyComputeMethod());
}

void TestRobustMatcher::test_fundamentalComputeMethod_data()
{
  QTest::addColumn<RobustMatcherProperties::FundamentalComputeMethod>("value");
  QTest::addColumn<RobustMatcherProperties::FundamentalComputeMethod>("result");

  QTest::newRow("algorithm_7_point") << RobustMatcherProperties::FundamentalComputeMethod::algorithm_7_point << RobustMatcherProperties::FundamentalComputeMethod::algorithm_7_point;
  QTest::newRow("algorithm_8_point") << RobustMatcherProperties::FundamentalComputeMethod::algorithm_8_point << RobustMatcherProperties::FundamentalComputeMethod::algorithm_8_point;
  QTest::newRow("ransac") << RobustMatcherProperties::FundamentalComputeMethod::ransac << RobustMatcherProperties::FundamentalComputeMethod::ransac;
  QTest::newRow("lmeds") << RobustMatcherProperties::FundamentalComputeMethod::lmeds << RobustMatcherProperties::FundamentalComputeMethod::lmeds;
}

void TestRobustMatcher::test_fundamentalComputeMethod()
{
  QFETCH(RobustMatcherProperties::FundamentalComputeMethod, value);
  QFETCH(RobustMatcherProperties::FundamentalComputeMethod, result);

  mRobustMatcher->setFundamentalComputeMethod(value);
  QCOMPARE(result, mRobustMatcher->fundamentalComputeMethod());
}

void TestRobustMatcher::test_essentialComputeMethod_data()
{
  QTest::addColumn<RobustMatcherProperties::EssentialComputeMethod>("value");
  QTest::addColumn<RobustMatcherProperties::EssentialComputeMethod>("result");

  QTest::newRow("ransac") << RobustMatcherProperties::EssentialComputeMethod::ransac << RobustMatcherProperties::EssentialComputeMethod::ransac;
  QTest::newRow("lmeds") << RobustMatcherProperties::EssentialComputeMethod::lmeds << RobustMatcherProperties::EssentialComputeMethod::lmeds;
}

void TestRobustMatcher::test_essentialComputeMethod()
{
  QFETCH(RobustMatcherProperties::EssentialComputeMethod, value);
  QFETCH(RobustMatcherProperties::EssentialComputeMethod, result);

  mRobustMatcher->setEssentialComputeMethod(value);
  QCOMPARE(result, mRobustMatcher->essentialComputeMethod());
}

void TestRobustMatcher::test_distance_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("0.7") << 0.7 << 0.7;
  QTest::newRow("3.") << 3. << 3.;
}

void TestRobustMatcher::test_distance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mRobustMatcher->setDistance(value);
  QCOMPARE(result, mRobustMatcher->distance());
}

void TestRobustMatcher::test_confidence_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.990") << 0.990 << 0.990;
  QTest::newRow("0.995") << 0.995 << 0.995;
  QTest::newRow("0.999") << 0.999 << 0.999;
}

void TestRobustMatcher::test_confidence()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mRobustMatcher->setConfidence(value);
  QCOMPARE(result, mRobustMatcher->confidence());
}

void TestRobustMatcher::test_maxIter_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1000") << 1000 << 1000;
  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("3000") << 3000 << 3000;
}

void TestRobustMatcher::test_maxIter()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mRobustMatcher->setMaxIters(value);
  QCOMPARE(result, mRobustMatcher->maxIter());
}

void TestRobustMatcher::test_reset()
{
  mRobustMatcher->setRatio(0.5);
  mRobustMatcher->setCrossCheck(false);
  mRobustMatcher->setGeometricTest(RobustMatcherProperties::GeometricTest::fundamental);
  mRobustMatcher->setHomographyComputeMethod(RobustMatcherProperties::HomographyComputeMethod::rho);
  mRobustMatcher->setFundamentalComputeMethod(RobustMatcherProperties::FundamentalComputeMethod::lmeds);
  mRobustMatcher->setEssentialComputeMethod(RobustMatcherProperties::EssentialComputeMethod::lmeds);
  mRobustMatcher->setDistance(3.);
  mRobustMatcher->setConfidence(0.995);
  mRobustMatcher->setMaxIters(3000);

  mRobustMatcher->reset();

  QCOMPARE(0.8, mRobustMatcher->ratio());
  QCOMPARE(true, mRobustMatcher->crossCheck());
  QCOMPARE(RobustMatcherProperties::GeometricTest::homography, mRobustMatcher->geometricTest());
  QCOMPARE(RobustMatcherProperties::HomographyComputeMethod::ransac, mRobustMatcher->homographyComputeMethod());
  QCOMPARE(RobustMatcherProperties::FundamentalComputeMethod::ransac, mRobustMatcher->fundamentalComputeMethod());
  QCOMPARE(RobustMatcherProperties::EssentialComputeMethod::ransac, mRobustMatcher->essentialComputeMethod());
  QCOMPARE(0.7, mRobustMatcher->distance());
  QCOMPARE(0.999, mRobustMatcher->confidence());
  QCOMPARE(2000, mRobustMatcher->maxIter());
}


QTEST_MAIN(TestRobustMatcher)

#include "tst_robustmatcher.moc"
