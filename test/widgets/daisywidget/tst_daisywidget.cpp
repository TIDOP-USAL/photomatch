#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DaisyWidget.h"

using namespace photomatch;

class TestDaisyWidget : public QObject
{
  Q_OBJECT

public:
  TestDaisyWidget();
  ~TestDaisyWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
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

private:

  DaisyWidget *mDaisyWidget;
};

TestDaisyWidget::TestDaisyWidget()
  : mDaisyWidget(new DaisyWidgetImp)
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
  /// Check default values
  QCOMPARE(15., mDaisyWidget->radius());
  QCOMPARE(3, mDaisyWidget->qRadius());
  QCOMPARE(8, mDaisyWidget->qTheta());
  QCOMPARE(8, mDaisyWidget->qHist());
  QCOMPARE("NRM_NONE", mDaisyWidget->norm());
  QCOMPARE(true, mDaisyWidget->interpolation());
  QCOMPARE(false, mDaisyWidget->useOrientation());
}

void TestDaisyWidget::cleanupTestCase()
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

void TestDaisyWidget::test_windowTitle()
{
  QCOMPARE("DAISY", mDaisyWidget->windowTitle());
}

void TestDaisyWidget::test_radius_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 101. << 100.;
}

void TestDaisyWidget::test_radius()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mDaisyWidget->setRadius(value);
  QCOMPARE(result, mDaisyWidget->radius());
}

void TestDaisyWidget::test_qRadius_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::test_qRadius()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQRadius(value);
  QCOMPARE(result, mDaisyWidget->qRadius());
}

void TestDaisyWidget::test_qTheta_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("500") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::test_qTheta()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQTheta(value);
  QCOMPARE(result, mDaisyWidget->qTheta());
}

void TestDaisyWidget::test_qHist_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("50") << 50 << 50;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestDaisyWidget::test_qHist()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDaisyWidget->setQHist(value);
  QCOMPARE(result, mDaisyWidget->qHist());
}

void TestDaisyWidget::test_norm_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("NRM_NONE") << "NRM_NONE" << "NRM_NONE";
  QTest::newRow("NRM_PARTIAL") << "NRM_PARTIAL" << "NRM_PARTIAL";
  QTest::newRow("NRM_FULL") << "NRM_FULL" << "NRM_FULL";
  QTest::newRow("NRM_SIFT") << "NRM_SIFT" << "NRM_SIFT";
  QTest::newRow("BAD_VALUE") << "BAD_VALUE" << "NRM_SIFT";
}

void TestDaisyWidget::test_norm()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mDaisyWidget->setNorm(value);
  QCOMPARE(result, mDaisyWidget->norm());
}

void TestDaisyWidget::test_interpolation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyWidget::test_interpolation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyWidget->setInterpolation(value);
  QCOMPARE(result, mDaisyWidget->interpolation());
}

void TestDaisyWidget::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestDaisyWidget::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mDaisyWidget->setUseOrientation(value);
  QCOMPARE(result, mDaisyWidget->useOrientation());
}



QTEST_MAIN(TestDaisyWidget)

#include "tst_daisywidget.moc"
