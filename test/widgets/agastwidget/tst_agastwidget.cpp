#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/AgastWidget.h"

using namespace photomatch;

class TestAgastWidget : public QObject
{
  Q_OBJECT

public:

  TestAgastWidget();
  ~TestAgastWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_threshold_data();
  void test_threshold();
  void test_nonmaxSuppression_data();
  void test_nonmaxSuppression();
  void test_detectorType_data();
  void test_detectorType();

private:

  AgastWidget *mAgastWidget;
};

TestAgastWidget::TestAgastWidget()
  : mAgastWidget(new AgastWidgetImp)
{

}

TestAgastWidget::~TestAgastWidget()
{
  if (mAgastWidget){
    delete mAgastWidget;
    mAgastWidget = nullptr;
  }
}

void TestAgastWidget::initTestCase()
{
  QCOMPARE(10, mAgastWidget->threshold());
  QCOMPARE("OAST_9_16", mAgastWidget->detectorType());
  QCOMPARE(true, mAgastWidget->nonmaxSuppression());
}

void TestAgastWidget::cleanupTestCase()
{
  mAgastWidget->setThreshold(3);
  mAgastWidget->setDetectorType("AGAST_7_12s");
  mAgastWidget->setNonmaxSuppression(false);

  mAgastWidget->reset();

  QCOMPARE(10, mAgastWidget->threshold());
  QCOMPARE("OAST_9_16", mAgastWidget->detectorType());
  QCOMPARE(true, mAgastWidget->nonmaxSuppression());
}

void TestAgastWidget::test_windowTitle()
{
  QCOMPARE("AGAST", mAgastWidget->windowTitle());
}

void TestAgastWidget::test_threshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAgastWidget::test_threshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAgastWidget->setThreshold(value);
  QCOMPARE(result, mAgastWidget->threshold());
}

void TestAgastWidget::test_nonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestAgastWidget::test_nonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mAgastWidget->setNonmaxSuppression(value);
  QCOMPARE(result, mAgastWidget->nonmaxSuppression());
}

void TestAgastWidget::test_detectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << "AGAST_5_8";
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << "AGAST_7_12d";
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << "AGAST_7_12s";
  QTest::newRow("OAST_9_16") << "OAST_9_16" << "OAST_9_16";
  QTest::newRow("bad_value") << "bad_value" << "OAST_9_16";
}

void TestAgastWidget::test_detectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAgastWidget->setDetectorType(value);
  QCOMPARE(result, mAgastWidget->detectorType());
}

QTEST_MAIN(TestAgastWidget)

#include "tst_agastwidget.moc"
