#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/BoostWidget.h"

using namespace photomatch;

class TestBoostWidget : public QObject
{
  Q_OBJECT

public:

  TestBoostWidget();
  ~TestBoostWidget();

private slots:

  void testDefaultConstructor();
  void test_windowTitle();
  void test_descriptorType_data();
  void test_descriptorType();
  void test_scaleFactor_data();
  void test_scaleFactor();
  void test_useOrientation_data();
  void test_useOrientation();
  void test_reset();

private:

  IBoostWidget *mBoostWidget;
};

TestBoostWidget::TestBoostWidget()
  : mBoostWidget(new BoostWidget)
{

}

TestBoostWidget::~TestBoostWidget()
{
  if (mBoostWidget){
    delete mBoostWidget;
    mBoostWidget = nullptr;
  }
}

void TestBoostWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE("BINBOOST_256", mBoostWidget->descriptorType());
  QCOMPARE(true, mBoostWidget->useOrientation());
  QCOMPARE(6.25, mBoostWidget->scaleFactor());
}

void TestBoostWidget::test_windowTitle()
{
  QCOMPARE("BOOST", mBoostWidget->windowTitle());
}

void TestBoostWidget::test_descriptorType_data()
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

void TestBoostWidget::test_descriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mBoostWidget->setDescriptorType(value);
  QCOMPARE(result, mBoostWidget->descriptorType());
}

void TestBoostWidget::test_scaleFactor_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("result");

    QTest::newRow("6.75") << 6.75 << 6.75;
    QTest::newRow("6.25") << 6.25 << 6.25;
    QTest::newRow("5.00") << 5.00 << 5.00;
    QTest::newRow("0.75") << 0.75 << 0.75;
    QTest::newRow("1.50") << 1.50 << 1.50;
}

void TestBoostWidget::test_scaleFactor()
{
    QFETCH(double, value);
    QFETCH(double, result);

    mBoostWidget->setScaleFactor(value);
    QCOMPARE(result, mBoostWidget->scaleFactor());
}


void TestBoostWidget::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestBoostWidget::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mBoostWidget->setUseOrientation(value);
  QCOMPARE(result, mBoostWidget->useOrientation());
}

void TestBoostWidget::test_reset()
{
  mBoostWidget->setDescriptorType("BGM");
  mBoostWidget->setUseOrientation(false);
  mBoostWidget->setScaleFactor(6.75);

  mBoostWidget->reset();

  QCOMPARE("BINBOOST_256", mBoostWidget->descriptorType());
  QCOMPARE(true, mBoostWidget->useOrientation());
  QCOMPARE(6.25, mBoostWidget->scaleFactor());
}

QTEST_MAIN(TestBoostWidget)

#include "tst_boostwidget.moc"
