#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/VggWidget.h"

using namespace photomatch;

class TestVggWidget : public QObject
{
  Q_OBJECT

public:

  TestVggWidget();
  ~TestVggWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_descriptorType_data();
  void test_descriptorType();
  void test_scaleFactor_data();
  void test_scaleFactor();
  void test_sigma_data();
  void test_sigma();
  void test_useNormalizeDescriptor_data();
  void test_useNormalizeDescriptor();
  void test_useNormalizeImage_data();
  void test_useNormalizeImage();
  void test_useScaleOrientation_data();
  void test_useScaleOrientation();

private:

  VggWidget *mVggWidget;
};

TestVggWidget::TestVggWidget()
  : mVggWidget(new VggWidgetImp)
{

}

TestVggWidget::~TestVggWidget()
{
  if (mVggWidget){
    delete mVggWidget;
    mVggWidget = nullptr;
  }
}

void TestVggWidget::initTestCase()
{
  /// Check default values
  QCOMPARE("VGG_120", mVggWidget->descriptorType());
  QCOMPARE(6.25, mVggWidget->scaleFactor());
  QCOMPARE(1.4, mVggWidget->sigma());
  QCOMPARE(false, mVggWidget->useNormalizeDescriptor());
  QCOMPARE(true, mVggWidget->useNormalizeImage());
  QCOMPARE(true, mVggWidget->useScaleOrientation());
}

void TestVggWidget::cleanupTestCase()
{
  mVggWidget->setDescriptorType("BGM");
  mVggWidget->setScaleFactor(6.75);
  mVggWidget->setSigma(1.5);
  mVggWidget->setUseNormalizeDescriptor(true);
  mVggWidget->setUseNormalizeImage(false);
  mVggWidget->setUseScaleOrientation(false);

  mVggWidget->reset();

  QCOMPARE("VGG_120", mVggWidget->descriptorType());
  QCOMPARE(6.25, mVggWidget->scaleFactor());
  QCOMPARE(1.4, mVggWidget->sigma());
  QCOMPARE(false, mVggWidget->useNormalizeDescriptor());
  QCOMPARE(true, mVggWidget->useNormalizeImage());
  QCOMPARE(true, mVggWidget->useScaleOrientation());
}

void TestVggWidget::test_windowTitle()
{
  QCOMPARE("VGG", mVggWidget->windowTitle());
}

void TestVggWidget::test_descriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("VGG_120") << "VGG_120" << "VGG_120";
  QTest::newRow("VGG_80") << "VGG_80" << "VGG_80";
  QTest::newRow("VGG_64") << "VGG_64" << "VGG_64";
  QTest::newRow("VGG_48") << "VGG_48" << "VGG_48";
}

void TestVggWidget::test_descriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mVggWidget->setDescriptorType(value);
  QCOMPARE(result, mVggWidget->descriptorType());
}

void TestVggWidget::test_scaleFactor_data()
{
    QTest::addColumn<double>("value");
    QTest::addColumn<double>("result");

    QTest::newRow("6.75") << 6.75 << 6.75;
    QTest::newRow("6.25") << 6.25 << 6.25;
    QTest::newRow("5.00") << 5.00 << 5.00;
    QTest::newRow("0.75") << 0.75 << 0.75;
    QTest::newRow("1.50") << 1.50 << 1.50;
}

void TestVggWidget::test_scaleFactor()
{
    QFETCH(double, value);
    QFETCH(double, result);

    mVggWidget->setScaleFactor(value);
    QCOMPARE(result, mVggWidget->scaleFactor());
}

void TestVggWidget::test_sigma_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("1.5") << 1.5 << 1.5;
  QTest::newRow("1.7") << 1.7 << 1.7;
}

void TestVggWidget::test_sigma()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mVggWidget->setSigma(value);
  QCOMPARE(result, mVggWidget->sigma());
}

void TestVggWidget::test_useNormalizeDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggWidget::test_useNormalizeDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggWidget->setUseNormalizeDescriptor(value);
  QCOMPARE(result, mVggWidget->useNormalizeDescriptor());
}

void TestVggWidget::test_useNormalizeImage_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggWidget::test_useNormalizeImage()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggWidget->setUseNormalizeImage(value);
  QCOMPARE(result, mVggWidget->useNormalizeImage());
}

void TestVggWidget::test_useScaleOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggWidget::test_useScaleOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggWidget->setUseScaleOrientation(value);
  QCOMPARE(result, mVggWidget->useScaleOrientation());
}


QTEST_MAIN(TestVggWidget)

#include "tst_vggwidget.moc"
