#include <QtTest>

#include "fme/process/ImagePreprocessing/CmbfheProcess.h"

using namespace fme;

class TestCmbfheProcess : public QObject
{
  Q_OBJECT

public:

  TestCmbfheProcess();
  ~TestCmbfheProcess();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_blockSize();
  void test_imgInput();
  void test_imgOutput();
  void test_reset();
  
protected:

  CmbfheProcess *mCmbfheProcess;
};

TestCmbfheProcess::TestCmbfheProcess()
  : mCmbfheProcess(new CmbfheProcess)
{
}

TestCmbfheProcess::~TestCmbfheProcess()
{
  if (mCmbfheProcess){
    delete mCmbfheProcess;
  }
}

void TestCmbfheProcess::initTestCase()
{

}

void TestCmbfheProcess::cleanupTestCase()
{

}

void TestCmbfheProcess::testConstructor()
{
  CmbfheProcess def;
  QCOMPARE(QSize(11, 11), def.blockSize());
  QCOMPARE("", def.imgInput());
  QCOMPARE("", def.imgOutput());
  
  CmbfheProcess par("file_in.jpg", "file_out.jpg", QSize(5, 5));
  QCOMPARE(QSize(5, 5), par.blockSize());
  QCOMPARE("file_in.jpg", par.imgInput());
  QCOMPARE("file_out.jpg", par.imgOutput());
}

void TestCmbfheProcess::test_blockSize()
{
  mCmbfheProcess->setBlockSize(QSize(15, 15));
  QCOMPARE(QSize(15, 15), mCmbfheProcess->blockSize());
}

void TestCmbfheProcess::test_imgInput()
{
  mCmbfheProcess->setImgInput("c:\\img_in.jpg");
  QCOMPARE("c:\\img_in.jpg", mCmbfheProcess->imgInput());
}

void TestCmbfheProcess::test_imgOutput()
{
  mCmbfheProcess->setImgOutput("c:\\img_out.jpg");
  QCOMPARE("c:\\img_out.jpg", mCmbfheProcess->imgOutput());
}
  
void TestCmbfheProcess::test_reset()
{
  mCmbfheProcess->setBlockSize(QSize(15, 15));
  mCmbfheProcess->setImgInput("c:\\img_in.jpg");
  mCmbfheProcess->setImgOutput("c:\\img_out.jpg");
  
  mCmbfheProcess->reset();
  
  QCOMPARE(QSize(11, 11), mCmbfheProcess->blockSize());
  QCOMPARE("", mCmbfheProcess->imgInput());
  QCOMPARE("", mCmbfheProcess->imgOutput());
}


QTEST_MAIN(TestCmbfheProcess)

#include "tst_cmbfheprocess.moc"
