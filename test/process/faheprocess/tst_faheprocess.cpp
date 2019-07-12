#include <QtTest>

#include "fme/process/ImagePreprocessing/FaheProcess.h"

using namespace fme;

class TestFaheProcess : public QObject
{
  Q_OBJECT

public:

  TestFaheProcess();
  ~TestFaheProcess();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_blockSize();
  void test_imgInput();
  void test_imgOutput();

protected:

  FaheProcess *mFaheProcess;
};

TestFaheProcess::TestFaheProcess()
  : mFaheProcess(new FaheProcess)
{
}

TestFaheProcess::~TestFaheProcess()
{
  if (mFaheProcess){
    delete mFaheProcess;
  }
}

void TestFaheProcess::initTestCase()
{

}

void TestFaheProcess::cleanupTestCase()
{

}

void TestFaheProcess::testConstructor()
{
  FaheProcess def;
  QCOMPARE(QSize(11, 11), def.blockSize());
  QCOMPARE("", def.imgInput());
  QCOMPARE("", def.imgOutput());

  FaheProcess par("file_in.jpg", "file_out.jpg", QSize(5, 5));
  QCOMPARE(QSize(5, 5), par.blockSize());
  QCOMPARE("file_in.jpg", par.imgInput());
  QCOMPARE("file_out.jpg", par.imgOutput());
}

void TestFaheProcess::test_blockSize()
{
  mFaheProcess->setBlockSize(QSize(15, 15));
  QCOMPARE(QSize(15, 15), mFaheProcess->blockSize());
}

void TestFaheProcess::test_imgInput()
{
  mFaheProcess->setImgInput("c:\\img_in.jpg");
  QCOMPARE("c:\\img_in.jpg", mFaheProcess->imgInput());
}

void TestFaheProcess::test_imgOutput()
{
  mFaheProcess->setImgOutput("c:\\img_out.jpg");
  QCOMPARE("c:\\img_out.jpg", mFaheProcess->imgOutput());
}




QTEST_MAIN(TestFaheProcess)

#include "tst_faheprocess.moc"
