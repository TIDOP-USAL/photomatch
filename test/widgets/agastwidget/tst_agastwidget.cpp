#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/AgastWidget.h"

using namespace fme;

class TestAgastWidget : public QObject
{
  Q_OBJECT

public:

  TestAgastWidget();
  ~TestAgastWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void testThreshold_data();
  void testThreshold();
  void testNonmaxSuppression_data();
  void testNonmaxSuppression();
  void testDetectorType_data();
  void testDetectorType();
  void testReset();

private:

  IAgastWidget *mAgastWidget;
};

TestAgastWidget::TestAgastWidget()
  : mAgastWidget(new AgastWidget)
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

}

void TestAgastWidget::cleanupTestCase()
{

}

void TestAgastWidget::testDefaultConstructor()
{
  /// Check default values
  QCOMPARE(10, mAgastWidget->threshold());
  QCOMPARE("OAST_9_16", mAgastWidget->detectorType());
  QCOMPARE(true, mAgastWidget->nonmaxSuppression());
}

void TestAgastWidget::testThreshold_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("11") << 11 << 11;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestAgastWidget::testThreshold()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mAgastWidget->setThreshold(value);
  QCOMPARE(result, mAgastWidget->threshold());
}

void TestAgastWidget::testNonmaxSuppression_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("true") << true << true;
  QTest::newRow("false") << false << false;
}

void TestAgastWidget::testNonmaxSuppression()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mAgastWidget->setNonmaxSuppression(value);
  QCOMPARE(result, mAgastWidget->nonmaxSuppression());
}

void TestAgastWidget::testDetectorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("AGAST_5_8") << "AGAST_5_8" << "AGAST_5_8";
  QTest::newRow("AGAST_7_12d") << "AGAST_7_12d" << "AGAST_7_12d";
  QTest::newRow("AGAST_7_12s") << "AGAST_7_12s" << "AGAST_7_12s";
  QTest::newRow("OAST_9_16") << "OAST_9_16" << "OAST_9_16";
  QTest::newRow("bad_value") << "bad_value" << "OAST_9_16";
}

void TestAgastWidget::testDetectorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mAgastWidget->setDetectorType(value);
  QCOMPARE(result, mAgastWidget->detectorType());
}

void TestAgastWidget::testReset()
{
  mAgastWidget->setThreshold(3);
  mAgastWidget->setDetectorType("AGAST_7_12s");
  mAgastWidget->setNonmaxSuppression(false);

  mAgastWidget->reset();

  QCOMPARE(10, mAgastWidget->threshold());
  QCOMPARE("OAST_9_16", mAgastWidget->detectorType());
  QCOMPARE(true, mAgastWidget->nonmaxSuppression());
}

QTEST_MAIN(TestAgastWidget)

#include "tst_agastwidget.moc"
