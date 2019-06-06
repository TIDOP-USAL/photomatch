#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/LatchWidget.h"

using namespace fme;

class TestLatchWidget : public QObject
{
  Q_OBJECT

public:

  TestLatchWidget();
  ~TestLatchWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_bytes_data();
  void test_bytes();
  void test_rotationInvariance_data();
  void test_rotationInvariance();
  void test_halfSsdSize_data();
  void test_halfSsdSize();
  void test_reset();

private:

  ILatchWidget *mLatchWidget;

};

TestLatchWidget::TestLatchWidget()
  : mLatchWidget(new LatchWidget)
{

}

TestLatchWidget::~TestLatchWidget()
{
  if (mLatchWidget){
    delete mLatchWidget;
    mLatchWidget = nullptr;
  }
}

void TestLatchWidget::initTestCase()
{

}

void TestLatchWidget::cleanupTestCase()
{

}

void TestLatchWidget::testDefaultConstructor()
{
  QCOMPARE("32", mLatchWidget->bytes());
  QCOMPARE(true, mLatchWidget->rotationInvariance());
  QCOMPARE(3, mLatchWidget->halfSsdSize());
}

void TestLatchWidget::test_bytes_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("1") << "1" << "1";
  QTest::newRow("2") << "2" << "2";
  QTest::newRow("4") << "4" << "4";
  QTest::newRow("8") << "8" << "8";
  QTest::newRow("16") << "16" << "16";
  QTest::newRow("32") << "32" << "32";
  QTest::newRow("64") << "64" << "64";
  QTest::newRow("bad_value") << "128" << "64";

}

void TestLatchWidget::test_bytes()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mLatchWidget->setBytes(value);
  QCOMPARE(result, mLatchWidget->bytes());
}

void TestLatchWidget::test_rotationInvariance_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestLatchWidget::test_rotationInvariance()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mLatchWidget->setRotationInvariance(value);
  QCOMPARE(result, mLatchWidget->rotationInvariance());
}

void TestLatchWidget::test_halfSsdSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("100") << 100 << 100;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestLatchWidget::test_halfSsdSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mLatchWidget->setHalfSsdSize(value);
  QCOMPARE(result, mLatchWidget->halfSsdSize());
}

void TestLatchWidget::test_reset()
{
  mLatchWidget->setBytes("4");
  mLatchWidget->setRotationInvariance(false);
  mLatchWidget->setHalfSsdSize(5);

  mLatchWidget->reset();

  QCOMPARE("32", mLatchWidget->bytes());
  QCOMPARE(true, mLatchWidget->rotationInvariance());
  QCOMPARE(3, mLatchWidget->halfSsdSize());
}

QTEST_MAIN(TestLatchWidget)

#include "tst_latchwidget.moc"
