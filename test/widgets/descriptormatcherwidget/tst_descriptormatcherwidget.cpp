#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/DescriptorMatcherWidget.h"

using namespace fme;

class TestDescriptorMatcherWidget : public QObject
{
  Q_OBJECT

public:
  TestDescriptorMatcherWidget();
  ~TestDescriptorMatcherWidget();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_windowTitle();
  void test_descriptorMatcher_data();
  void test_descriptorMatcher();
  void test_normType_data();
  void test_normType();
  void test_ratio_data();
  void test_ratio();
  void test_distance_data();
  void test_distance();
  void test_confidence_data();
  void test_confidence();
  void test_crossMatching_data();
  void test_crossMatching();
  void test_geometricTest_data();
  void test_geometricTest();
  void test_homographyMatrixMethod_data();
  void test_homographyMatrixMethod();
  void test_fundamentalMatrixMethod_data();
  void test_fundamentalMatrixMethod();
  void test_essentialMatrixMethod_data();
  void test_essentialMatrixMethod();
  void test_maxIters_data();
  void test_maxIters();
  void test_reset();

private:

  IDescriptorMatcherWidget *mDescriptorMatcherWidget;

};

TestDescriptorMatcherWidget::TestDescriptorMatcherWidget()
  : mDescriptorMatcherWidget(new DescriptorMatcherWidget)
{

}

TestDescriptorMatcherWidget::~TestDescriptorMatcherWidget()
{
  if (mDescriptorMatcherWidget){
    delete mDescriptorMatcherWidget;
    mDescriptorMatcherWidget = nullptr;
  }
}

void TestDescriptorMatcherWidget::initTestCase()
{

}

void TestDescriptorMatcherWidget::cleanupTestCase()
{

}

void TestDescriptorMatcherWidget::test_defaultConstructor()
{
  /// Check default values
  DescriptorMatcherWidget descriptorMatcherWidget;
  QCOMPARE("Brute-Force", descriptorMatcherWidget.matchingMethod());
  QCOMPARE("NORM_L1", descriptorMatcherWidget.normType());
  QCOMPARE(0.8, descriptorMatcherWidget.ratio());
  QCOMPARE("Homography Matrix", descriptorMatcherWidget.geometricTest());
  QCOMPARE("RANSAC", descriptorMatcherWidget.homographyComputeMethod());
  QCOMPARE("RANSAC", descriptorMatcherWidget.fundamentalComputeMethod());
  QCOMPARE("RANSAC", descriptorMatcherWidget.essentialComputeMethod());
  QCOMPARE(0.7, descriptorMatcherWidget.distance());
  QCOMPARE(0.999, descriptorMatcherWidget.confidence());
  QCOMPARE(2000, descriptorMatcherWidget.maxIters());
  QCOMPARE(true, descriptorMatcherWidget.crossMatching());
}

void TestDescriptorMatcherWidget::test_windowTitle()
{
  QCOMPARE("Descriptor Matcher", mDescriptorMatcherWidget->windowTitle());
}

void TestDescriptorMatcherWidget::test_descriptorMatcher_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Brute-Force") << "Brute-Force" << "Brute-Force";
  QTest::newRow("FLANN") << "FLANN" << "FLANN";
  QTest::newRow("bad_value") << "bad_value" << "FLANN";
}

void TestDescriptorMatcherWidget::test_descriptorMatcher()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setMatchingMethod(value);
  QCOMPARE(result, mDescriptorMatcherWidget->matchingMethod());
}

void TestDescriptorMatcherWidget::test_normType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("NORM_L1") << "NORM_L1" << "NORM_L1";
  QTest::newRow("NORM_L2") << "NORM_L2" << "NORM_L2";
  QTest::newRow("NORM_HAMMING") << "NORM_HAMMING" << "NORM_HAMMING";
  QTest::newRow("NORM_HAMMING2") << "NORM_HAMMING2" << "NORM_HAMMING2";
  QTest::newRow("bad_value") << "bad_value" << "NORM_HAMMING2";
}

void TestDescriptorMatcherWidget::test_normType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setNormType(value);
  QCOMPARE(result, mDescriptorMatcherWidget->normType());
}

void TestDescriptorMatcherWidget::test_ratio_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.7") << 0.7 << 0.7;
  QTest::newRow("0.3") << 0.3 << 0.3;
  QTest::newRow("5.") << 5. << 5.;
  ///TODO: Ver límites máximo y mínimo.
  QTest::newRow("Out of range value") << -1. << .001;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestDescriptorMatcherWidget::test_ratio()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setRatio(value);
  QCOMPARE(result, mDescriptorMatcherWidget->ratio());
}

void TestDescriptorMatcherWidget::test_distance_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.7") << 0.7 << 0.7;
  QTest::newRow("0.3") << 0.3 << 0.3;
  QTest::newRow("5.") << 5. << 5.;
  ///TODO: Ver límites máximo y mínimo.
  QTest::newRow("Out of range value") << -1. << .001;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestDescriptorMatcherWidget::test_distance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setDistance(value);
  QCOMPARE(result, mDescriptorMatcherWidget->distance());
}

void TestDescriptorMatcherWidget::test_confidence_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.1") << 0.1 << 0.1;
  QTest::newRow("0.3") << 0.3 << 0.3;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << -0.5 << 0.;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestDescriptorMatcherWidget::test_confidence()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setConfidence(value);
  QCOMPARE(result, mDescriptorMatcherWidget->confidence());
}

void TestDescriptorMatcherWidget::test_crossMatching_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDescriptorMatcherWidget::test_geometricTest_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Homography Matrix") << "Homography Matrix" << "Homography Matrix";
  QTest::newRow("Fundamental Matrix") << "Fundamental Matrix" << "Fundamental Matrix";
  QTest::newRow("Essential Matrix") << "Essential Matrix" << "Essential Matrix";
  QTest::newRow("bad_value") << "bad_value" << "Essential Matrix";
}

void TestDescriptorMatcherWidget::test_geometricTest()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setGeometricTest(value);
  QCOMPARE(result, mDescriptorMatcherWidget->geometricTest());
}

void TestDescriptorMatcherWidget::test_homographyMatrixMethod_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("All Points") << "All Points" << "All Points";
  QTest::newRow("RANSAC") << "RANSAC" << "RANSAC";
  QTest::newRow("LMedS") << "LMedS" << "LMedS";
  QTest::newRow("RHO") << "RHO" << "RHO";
  QTest::newRow("bad_value") << "bad_value" << "RHO";
}

void TestDescriptorMatcherWidget::test_homographyMatrixMethod()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setHomographyComputeMethod(value);
  QCOMPARE(result, mDescriptorMatcherWidget->homographyComputeMethod());
}

void TestDescriptorMatcherWidget::test_fundamentalMatrixMethod_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("7-point algorithm") << "7-point algorithm" << "7-point algorithm";
  QTest::newRow("8-point algorithm") << "8-point algorithm" << "8-point algorithm";
  QTest::newRow("RANSAC") << "RANSAC" << "RANSAC";
  QTest::newRow("LMedS") << "LMedS" << "LMedS";
  QTest::newRow("bad_value") << "bad_value" << "LMedS";
}

void TestDescriptorMatcherWidget::test_fundamentalMatrixMethod()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setFundamentalComputeMethod(value);
  QCOMPARE(result, mDescriptorMatcherWidget->fundamentalComputeMethod());
}

void TestDescriptorMatcherWidget::test_essentialMatrixMethod_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("RANSAC") << "RANSAC" << "RANSAC";
  QTest::newRow("LMedS") << "LMedS" << "LMedS";
  QTest::newRow("bad_value") << "bad_value" << "LMedS";
}

void TestDescriptorMatcherWidget::test_essentialMatrixMethod()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setEssentialComputeMethod(value);
  QCOMPARE(result, mDescriptorMatcherWidget->essentialComputeMethod());
}

void TestDescriptorMatcherWidget::test_maxIters_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("1000") << 1000 << 1000;
  QTest::newRow("500") << 500 << 500;
  QTest::newRow("Out of range value") << 10001 << 10000;
}

void TestDescriptorMatcherWidget::test_maxIters()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDescriptorMatcherWidget->setMaxIters(value);
  QCOMPARE(result, mDescriptorMatcherWidget->maxIters());
}

void TestDescriptorMatcherWidget::test_crossMatching()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDescriptorMatcherWidget->setCrossMatching(value);
  QCOMPARE(result, mDescriptorMatcherWidget->crossMatching());
}

void TestDescriptorMatcherWidget::test_reset()
{
  mDescriptorMatcherWidget->setMatchingMethod("FLANN");
  mDescriptorMatcherWidget->setNormType("NORM_L2");
  mDescriptorMatcherWidget->setRatio(0.5);
  mDescriptorMatcherWidget->setGeometricTest("Fundamental Matrix");
  mDescriptorMatcherWidget->setHomographyComputeMethod("All Points");
  mDescriptorMatcherWidget->setFundamentalComputeMethod("LMedS");
  mDescriptorMatcherWidget->setEssentialComputeMethod("LMedS");
  mDescriptorMatcherWidget->setDistance(0.3);
  mDescriptorMatcherWidget->setConfidence(0.2);
  mDescriptorMatcherWidget->setCrossMatching(false);

  mDescriptorMatcherWidget->reset();

  /// Check default values
  QCOMPARE("Brute-Force", mDescriptorMatcherWidget->matchingMethod());
  QCOMPARE("NORM_L1", mDescriptorMatcherWidget->normType());
  QCOMPARE(0.8, mDescriptorMatcherWidget->ratio());
  QCOMPARE("Homography Matrix", mDescriptorMatcherWidget->geometricTest());
  QCOMPARE("RANSAC", mDescriptorMatcherWidget->homographyComputeMethod());
  QCOMPARE("RANSAC", mDescriptorMatcherWidget->fundamentalComputeMethod());
  QCOMPARE("RANSAC", mDescriptorMatcherWidget->essentialComputeMethod());
  QCOMPARE(0.7, mDescriptorMatcherWidget->distance());
  QCOMPARE(0.999, mDescriptorMatcherWidget->confidence());
  QCOMPARE(2000, mDescriptorMatcherWidget->maxIters());
  QCOMPARE(true, mDescriptorMatcherWidget->crossMatching());
}

QTEST_MAIN(TestDescriptorMatcherWidget)

#include "tst_descriptormatcherwidget.moc"
