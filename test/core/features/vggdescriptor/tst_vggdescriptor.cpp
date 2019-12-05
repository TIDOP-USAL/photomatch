#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/vgg.h"

using namespace photomatch;

class TestVggDescriptor
  : public QObject
{
  Q_OBJECT

public:

  TestVggDescriptor();
  ~TestVggDescriptor();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_defaultConstructor();
  void test_constructor();
  void test_copy_constructor();
  void test_type();
  void test_name();
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
  void test_reset();

private:

  VggDescriptor *mVggDescriptor;
};

TestVggDescriptor::TestVggDescriptor()
  : mVggDescriptor(new VggDescriptor)
{

}

TestVggDescriptor::~TestVggDescriptor()
{
  if (mVggDescriptor){
    delete mVggDescriptor;
    mVggDescriptor = nullptr;
  }
}

void TestVggDescriptor::initTestCase()
{

}

void TestVggDescriptor::cleanupTestCase()
{

}

void TestVggDescriptor::test_defaultConstructor()
{
  /// Check default values
  VggDescriptor vggDescriptor;
  QCOMPARE("VGG_120", vggDescriptor.descriptorType());
  QCOMPARE(6.25, vggDescriptor.scaleFactor());
  QCOMPARE(1.4, vggDescriptor.sigma());
  QCOMPARE(false, vggDescriptor.useNormalizeDescriptor());
  QCOMPARE(true, vggDescriptor.useNormalizeImage());
  QCOMPARE(true, vggDescriptor.useScaleOrientation());
}

void TestVggDescriptor::test_constructor()
{
  VggDescriptor vggDescriptor("VGG_80", 6.75, 1.6, true, false, false);
  QCOMPARE("VGG_80", vggDescriptor.descriptorType());
  QCOMPARE(6.75, vggDescriptor.scaleFactor());
  QCOMPARE(1.6, vggDescriptor.sigma());
  QCOMPARE(true, vggDescriptor.useNormalizeDescriptor());
  QCOMPARE(false, vggDescriptor.useNormalizeImage());
  QCOMPARE(false, vggDescriptor.useScaleOrientation());
}

void TestVggDescriptor::test_copy_constructor()
{
  VggDescriptor vggDescriptor("VGG_80", 6.75, 1.6, true, false, false);
  VggDescriptor c(vggDescriptor);
  QCOMPARE("VGG_80", c.descriptorType());
  QCOMPARE(6.75, c.scaleFactor());
  QCOMPARE(1.6, c.sigma());
  QCOMPARE(true, c.useNormalizeDescriptor());
  QCOMPARE(false, c.useNormalizeImage());
  QCOMPARE(false, c.useScaleOrientation());
}

void TestVggDescriptor::test_type()
{
  QCOMPARE(VggDescriptor::Type::vgg, mVggDescriptor->type());
}

void TestVggDescriptor::test_name()
{
  QCOMPARE("VGG", mVggDescriptor->name());
}

void TestVggDescriptor::test_descriptorType_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("VGG_120") << "VGG_120" << "VGG_120";
  QTest::newRow("VGG_80") << "VGG_80" << "VGG_80";
  QTest::newRow("VGG_64") << "VGG_64" << "VGG_64";
  QTest::newRow("VGG_48") << "VGG_48" << "VGG_48";
}

void TestVggDescriptor::test_descriptorType()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mVggDescriptor->setDescriptorType(value);
  QCOMPARE(result, mVggDescriptor->descriptorType());
}

void TestVggDescriptor::test_scaleFactor_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("6.75") << 6.75 << 6.75;
  QTest::newRow("6.25") << 6.25 << 6.25;
  QTest::newRow("5.00") << 5.00 << 5.00;
  QTest::newRow("0.75") << 0.75 << 0.75;
  QTest::newRow("1.50") << 1.50 << 1.50;
}

void TestVggDescriptor::test_scaleFactor()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mVggDescriptor->setScaleFactor(value);
  QCOMPARE(result, mVggDescriptor->scaleFactor());
}

void TestVggDescriptor::test_sigma_data()
{
  QTest::addColumn<double>("value");
  QTest::addColumn<double>("result");

  QTest::newRow("1.5") << 1.5 << 1.5;
  QTest::newRow("1.7") << 1.7 << 1.7;
}

void TestVggDescriptor::test_sigma()
{
  QFETCH(double, value);
  QFETCH(double, result);

  mVggDescriptor->setSigma(value);
  QCOMPARE(result, mVggDescriptor->sigma());
}

void TestVggDescriptor::test_useNormalizeDescriptor_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggDescriptor::test_useNormalizeDescriptor()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggDescriptor->setUseNormalizeDescriptor(value);
  QCOMPARE(result, mVggDescriptor->useNormalizeDescriptor());
}

void TestVggDescriptor::test_useNormalizeImage_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggDescriptor::test_useNormalizeImage()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggDescriptor->setUseNormalizeImage(value);
  QCOMPARE(result, mVggDescriptor->useNormalizeImage());
}

void TestVggDescriptor::test_useScaleOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestVggDescriptor::test_useScaleOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mVggDescriptor->setUseScaleOrientation(value);
  QCOMPARE(result, mVggDescriptor->useScaleOrientation());
}

void TestVggDescriptor::test_reset()
{
  mVggDescriptor->setDescriptorType("16");
  mVggDescriptor->setScaleFactor(6.75);
  mVggDescriptor->setSigma(1.5);
  mVggDescriptor->setUseNormalizeDescriptor(true);
  mVggDescriptor->setUseNormalizeImage(false);
  mVggDescriptor->setUseScaleOrientation(false);

  mVggDescriptor->reset();

  QCOMPARE("VGG_120", mVggDescriptor->descriptorType());
  QCOMPARE(6.25, mVggDescriptor->scaleFactor());
  QCOMPARE(1.4, mVggDescriptor->sigma());
  QCOMPARE(false, mVggDescriptor->useNormalizeDescriptor());
  QCOMPARE(true, mVggDescriptor->useNormalizeImage());
  QCOMPARE(true, mVggDescriptor->useScaleOrientation());
}

QTEST_APPLESS_MAIN(TestVggDescriptor)

#include "tst_vggdescriptor.moc"
