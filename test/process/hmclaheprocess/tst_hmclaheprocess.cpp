#include <QtTest>

#include "fme/process/ImagePreprocessing/HmclaheProcess.h"

using namespace fme;

class TestHmclaheProcess : public QObject
{
  Q_OBJECT

public:

  TestHmclaheProcess();
  ~TestHmclaheProcess();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_blockSize();
  void test_imgInput();
  void test_imgOutput();
  void test_l();
  void test_phi();
  void test_reset();
  
protected:

  HmclaheProcess *mHmclaheProcess;
};

TestHmclaheProcess::TestHmclaheProcess()
  : mHmclaheProcess(new HmclaheProcess)
{
}

TestHmclaheProcess::~TestHmclaheProcess()
{
  if (mHmclaheProcess){
    delete mHmclaheProcess;
  }
}

void TestHmclaheProcess::initTestCase()
{

}

void TestHmclaheProcess::cleanupTestCase()
{

}

void TestHmclaheProcess::testConstructor()
{
  HmclaheProcess def;
  QCOMPARE(QSize(17, 17), def.blockSize());
  QCOMPARE("", def.imgInput());
  QCOMPARE("", def.imgOutput());
  QCOMPARE(0.03, def.l());
  QCOMPARE(0.5, def.phi());
  
  HmclaheProcess par("file_in.jpg", "file_out.jpg", QSize(5, 5), 0.05, 0.7);
  QCOMPARE(QSize(5, 5), par.blockSize());
  QCOMPARE("file_in.jpg", par.imgInput());
  QCOMPARE("file_out.jpg", par.imgOutput());
  QCOMPARE(0.05, par.l());
  QCOMPARE(0.7, par.phi());
}

void TestHmclaheProcess::test_blockSize()
{
  mHmclaheProcess->setBlockSize(QSize(15, 15));
  QCOMPARE(QSize(15, 15), mHmclaheProcess->blockSize());
}

void TestHmclaheProcess::test_imgInput()
{
  mHmclaheProcess->setImgInput("c:\\img_in.jpg");
  QCOMPARE("c:\\img_in.jpg", mHmclaheProcess->imgInput());
}

void TestHmclaheProcess::test_imgOutput()
{
  mHmclaheProcess->setImgOutput("c:\\img_out.jpg");
  QCOMPARE("c:\\img_out.jpg", mHmclaheProcess->imgOutput());
}

void TestHmclaheProcess::test_l()
{
  mHmclaheProcess->setL(0.06);
  QCOMPARE(0.06, mHmclaheProcess->l());
}

void TestHmclaheProcess::test_phi()
{
  mHmclaheProcess->setPhi(0.4);
  QCOMPARE(0.4, mHmclaheProcess->phi());
}
  
void TestHmclaheProcess::test_reset()
{
  mHmclaheProcess->setBlockSize(QSize(15, 15));
  mHmclaheProcess->setImgInput("c:\\img_in.jpg");
  mHmclaheProcess->setImgOutput("c:\\img_out.jpg");
  mHmclaheProcess->setL(0.06);
  mHmclaheProcess->setPhi(0.4);
  
  mHmclaheProcess->reset();
  
  QCOMPARE(QSize(17, 17), mHmclaheProcess->blockSize());
  QCOMPARE("", mHmclaheProcess->imgInput());
  QCOMPARE("", mHmclaheProcess->imgOutput());
  QCOMPARE(0.03, mHmclaheProcess->l());
  QCOMPARE(0.5, mHmclaheProcess->phi());
}


QTEST_MAIN(TestHmclaheProcess)

#include "tst_hmclaheprocess.moc"
