#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/DaisyWidget.h"

using namespace fme;

class TestDaisyWidget : public QObject
{
  Q_OBJECT

public:
  TestDaisyWidget();
  ~TestDaisyWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void testRadius_data();
  void testRadius();
  void testQRadius_data();
  void testQRadius();
  void testQTheta_data();
  void testQTheta();
  void testQHist_data();
  void testQHist();
  void testNorm_data();
  void testNorm();
  void testInterpolation_data();
  void testInterpolation();
  void testUseOrientation_data();
  void testUseOrientation();
  void testReset();

private:

  IDaisyWidget *mDaisyWidget;
};

TestDaisyWidget::TestDaisyWidget()
  : mDaisyWidget(new DaisyWidget)
{

}

TestDaisyWidget::~TestDaisyWidget()
{
  if (mDaisyWidget){
    delete mDaisyWidget;
    mDaisyWidget = nullptr;
  }
}

void TestDaisyWidget::initTestCase()
{

}

void TestDaisyWidget::cleanupTestCase()
{

}

void TestDaisyWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(15., mDaisyWidget->radius());
  QCOMPARE(3, mDaisyWidget->qRadius());
  QCOMPARE(8, mDaisyWidget->qTheta());
  QCOMPARE(8, mDaisyWidget->qHist());
  QCOMPARE("NRM_NONE", mDaisyWidget->norm());
  QCOMPARE(true, mDaisyWidget->interpolation());
  QCOMPARE(false, mDaisyWidget->useOrientation());
}

void TestDaisyWidget::test_windowTitle()
{
  QCOMPARE("DAISY", mDaisyWidget->windowTitle());
}

void TestDaisyWidget::testRadius_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestDaisyWidget::testRadius()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDaisyWidget->setRadius(value);
  QCOMPARE(result, mDaisyWidget->radius());
}

void TestDaisyWidget::testQRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::testQRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQRadius(value);
  QCOMPARE(result, mDaisyWidget->qRadius());
}

void TestDaisyWidget::testQTheta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::testQTheta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQTheta(value);
  QCOMPARE(result, mDaisyWidget->qTheta());
}

void TestDaisyWidget::testQHist_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::testQHist()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQHist(value);
  QCOMPARE(result, mDaisyWidget->qHist());
}

void TestDaisyWidget::testNorm_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("NRM_NONE") << "NRM_NONE" << "NRM_NONE";
  QTest::newRow("NRM_PARTIAL") << "NRM_PARTIAL" << "NRM_PARTIAL";
  QTest::newRow("NRM_FULL") << "NRM_FULL" << "NRM_FULL";
  QTest::newRow("NRM_SIFT") << "NRM_SIFT" << "NRM_SIFT";
  QTest::newRow("BAD_VALUE") << "BAD_VALUE" << "NRM_SIFT";
}

void TestDaisyWidget::testNorm()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDaisyWidget->setNorm(value);
  QCOMPARE(result, mDaisyWidget->norm());
}

void TestDaisyWidget::testInterpolation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyWidget::testInterpolation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyWidget->setInterpolation(value);
  QCOMPARE(result, mDaisyWidget->interpolation());
}

void TestDaisyWidget::testUseOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyWidget::testUseOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyWidget->setUseOrientation(value);
  QCOMPARE(result, mDaisyWidget->useOrientation());
}

void TestDaisyWidget::testReset()
{
  mDaisyWidget->setRadius(30.);
  mDaisyWidget->setQRadius(5);
  mDaisyWidget->setQTheta(4);
  mDaisyWidget->setQHist(4);
  mDaisyWidget->setNorm("NRM_FULL");
  mDaisyWidget->setInterpolation(false);
  mDaisyWidget->setUseOrientation(true);

  mDaisyWidget->reset();

  /// Check default values
  QCOMPARE(15., mDaisyWidget->radius());
  QCOMPARE(3, mDaisyWidget->qRadius());
  QCOMPARE(8, mDaisyWidget->qTheta());
  QCOMPARE(8, mDaisyWidget->qHist());
  QCOMPARE("NRM_NONE", mDaisyWidget->norm());
  QCOMPARE(true, mDaisyWidget->interpolation());
  QCOMPARE(false, mDaisyWidget->useOrientation());
}


QTEST_MAIN(TestDaisyWidget)

#include "tst_daisywidget.moc"
