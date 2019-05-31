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
  void testDefaultConstructor();
  void testDescriptorMatcher_data();
  void testDescriptorMatcher();
  void testNormType_data();
  void testNormType();
  void testUpdateNormTypes_data();
  void testUpdateNormTypes();
  void testRatio_data();
  void testRatio();
  void testDistance_data();
  void testDistance();
  void testConfidence_data();
  void testConfidence();
  void testCrossMatching();
  void testCrossMatching_data();
  void testReset();

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

void TestDescriptorMatcherWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE("Brute-Force", mDescriptorMatcherWidget->matchingMethod());
  QCOMPARE("NORM_L1", mDescriptorMatcherWidget->normType());
  QCOMPARE(0.7, mDescriptorMatcherWidget->distance());
  QCOMPARE(0.8, mDescriptorMatcherWidget->ratio());
  QCOMPARE(0.999, mDescriptorMatcherWidget->confidence());
  QCOMPARE(true, mDescriptorMatcherWidget->crossMatching());
}

void TestDescriptorMatcherWidget::testDescriptorMatcher_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Brute-Force") << "Brute-Force" << "Brute-Force";
  QTest::newRow("FLANN") << "FLANN" << "FLANN";
  QTest::newRow("bad_value") << "bad_value" << "FLANN";
}

void TestDescriptorMatcherWidget::testDescriptorMatcher()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setMatchingMethod(value);
  QCOMPARE(result, mDescriptorMatcherWidget->matchingMethod());
}

void TestDescriptorMatcherWidget::testNormType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("NORM_L1") << "NORM_L1" << "NORM_L1";
  QTest::newRow("NORM_L2") << "NORM_L2" << "NORM_L2";
  QTest::newRow("NORM_HAMMING") << "NORM_HAMMING" << "NORM_HAMMING";
  QTest::newRow("NORM_HAMMING2") << "NORM_HAMMING2" << "NORM_HAMMING2";
  QTest::newRow("bad_value") << "bad_value" << "NORM_HAMMING2";
}

void TestDescriptorMatcherWidget::testNormType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDescriptorMatcherWidget->setNormType(value);
  QCOMPARE(result, mDescriptorMatcherWidget->normType());
}

void TestDescriptorMatcherWidget::testUpdateNormTypes_data()
{

}

void TestDescriptorMatcherWidget::testUpdateNormTypes()
{

}

void TestDescriptorMatcherWidget::testRatio_data()
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

void TestDescriptorMatcherWidget::testRatio()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setRatio(value);
  QCOMPARE(result, mDescriptorMatcherWidget->ratio());
}

void TestDescriptorMatcherWidget::testDistance_data()
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

void TestDescriptorMatcherWidget::testDistance()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setDistance(value);
  QCOMPARE(result, mDescriptorMatcherWidget->distance());
}

void TestDescriptorMatcherWidget::testConfidence_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("0.1") << 0.1 << 0.1;
  QTest::newRow("0.3") << 0.3 << 0.3;
  QTest::newRow("0.5") << 0.5 << 0.5;
  QTest::newRow("Out of range value") << -0.5 << 0.;
  QTest::newRow("Out of range value") << 1.1 << 1.;
}

void TestDescriptorMatcherWidget::testConfidence()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDescriptorMatcherWidget->setConfidence(value);
  QCOMPARE(result, mDescriptorMatcherWidget->confidence());
}

void TestDescriptorMatcherWidget::testCrossMatching_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDescriptorMatcherWidget::testCrossMatching()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDescriptorMatcherWidget->setCrossMatching(value);
  QCOMPARE(result, mDescriptorMatcherWidget->crossMatching());
}

void TestDescriptorMatcherWidget::testReset()
{
  mDescriptorMatcherWidget->setMatchingMethod("FLANN");
  mDescriptorMatcherWidget->setNormType("NORM_L2");
  mDescriptorMatcherWidget->setRatio(0.5);
  mDescriptorMatcherWidget->setDistance(0.3);
  mDescriptorMatcherWidget->setConfidence(0.2);
  mDescriptorMatcherWidget->setCrossMatching(false);

  mDescriptorMatcherWidget->reset();

  /// Check default values
  QCOMPARE("Brute-Force", mDescriptorMatcherWidget->matchingMethod());
  QCOMPARE("NORM_L1", mDescriptorMatcherWidget->normType());
  QCOMPARE(0.7, mDescriptorMatcherWidget->distance());
  QCOMPARE(0.8, mDescriptorMatcherWidget->ratio());
  QCOMPARE(0.999, mDescriptorMatcherWidget->confidence());
  QCOMPARE(true, mDescriptorMatcherWidget->crossMatching());
}

QTEST_MAIN(TestDescriptorMatcherWidget)

#include "tst_descriptormatcherwidget.moc"
