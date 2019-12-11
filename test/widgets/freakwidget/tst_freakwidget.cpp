#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/FreakWidget.h"

using namespace photomatch;

class TestFreakWidget : public QObject
{
  Q_OBJECT

public:

  TestFreakWidget();
  ~TestFreakWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_windowTitle();
  void test_orientationNormalized_data();
  void test_orientationNormalized();
  void test_scaleNormalized_data();
  void test_scaleNormalized();
  void test_patternScale_data();
  void test_patternScale();
  void test_octaves_data();
  void test_octaves();
  void test_reset();

protected:

  IFreakWidget *mFreakWidget;
};

TestFreakWidget::TestFreakWidget()
  : mFreakWidget(new FreakWidget)
{

}

TestFreakWidget::~TestFreakWidget()
{
  if (mFreakWidget){
    delete mFreakWidget;
    mFreakWidget = nullptr;
  }
}

void TestFreakWidget::initTestCase()
{

}

void TestFreakWidget::cleanupTestCase()
{

}

void TestFreakWidget::test_constructor()
{
  QCOMPARE(true, mFreakWidget->orientationNormalized());
  QCOMPARE(true, mFreakWidget->scaleNormalized());
  QCOMPARE(22., mFreakWidget->patternScale());
  QCOMPARE(4, mFreakWidget->octaves());
}

void TestFreakWidget::test_windowTitle()
{
  QCOMPARE("FREAK", mFreakWidget->windowTitle());
}

void TestFreakWidget::test_orientationNormalized_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestFreakWidget::test_orientationNormalized()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFreakWidget->setOrientationNormalized(value);
  QCOMPARE(result, mFreakWidget->orientationNormalized());
}

void TestFreakWidget::test_scaleNormalized_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestFreakWidget::test_scaleNormalized()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mFreakWidget->setScaleNormalized(value);
  QCOMPARE(result, mFreakWidget->scaleNormalized());
}

void TestFreakWidget::test_patternScale_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("5.0") << 5.0 << 5.0;
  QTest::newRow("10.0") << 10.0 << 10.0;
  QTest::newRow("20.0") << 20.0 << 20.0;
  QTest::newRow("Out of range value") << 1000.1 << 1000.0;
}

void TestFreakWidget::test_patternScale()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mFreakWidget->setPatternScale(value);
  QCOMPARE(result, mFreakWidget->patternScale());
}

void TestFreakWidget::test_octaves_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
  QTest::newRow("4") << 4 << 4;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestFreakWidget::test_octaves()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mFreakWidget->setOctaves(value);
  QCOMPARE(result, mFreakWidget->octaves());
}

void TestFreakWidget::test_reset()
{
  mFreakWidget->setOrientationNormalized(false);
  mFreakWidget->setScaleNormalized(false);
  mFreakWidget->setPatternScale(35.);
  mFreakWidget->setOctaves(8);

  mFreakWidget->reset();

  QCOMPARE(true, mFreakWidget->orientationNormalized());
  QCOMPARE(true, mFreakWidget->scaleNormalized());
  QCOMPARE(22., mFreakWidget->patternScale());
  QCOMPARE(4, mFreakWidget->octaves());
}

QTEST_MAIN(TestFreakWidget)

#include "tst_freakwidget.moc"
