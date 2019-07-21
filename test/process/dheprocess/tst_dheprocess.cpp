#include <QtTest>

#include "fme/process/ImagePreprocessing/DheProcess.h"

using namespace fme;

class TestDheProcess : public QObject
{
  Q_OBJECT

public:

  TestDheProcess();
  ~TestDheProcess();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_imgInput();
  void test_imgOutput();
  void test_x();
  void test_reset();
  
protected:

  DheProcess *mDheProcess;
};

TestDheProcess::TestDheProcess()
  : mDheProcess(new DheProcess)
{
}

TestDheProcess::~TestDheProcess()
{
  if (mDheProcess){
    delete mDheProcess;
  }
}

void TestDheProcess::initTestCase()
{

}

void TestDheProcess::cleanupTestCase()
{

}

void TestDheProcess::testConstructor()
{
  DheProcess def;
  QCOMPARE("", def.imgInput());
  QCOMPARE("", def.imgOutput());
  QCOMPARE(1, def.x());
  
  DheProcess par("file_in.jpg", "file_out.jpg", 2);
  QCOMPARE("file_in.jpg", par.imgInput());
  QCOMPARE("file_out.jpg", par.imgOutput());
  QCOMPARE(2, par.x());
}

void TestDheProcess::test_imgInput()
{
  mDheProcess->setImgInput("c:\\img_in.jpg");
  QCOMPARE("c:\\img_in.jpg", mDheProcess->imgInput());
}

void TestDheProcess::test_imgOutput()
{
  mDheProcess->setImgOutput("c:\\img_out.jpg");
  QCOMPARE("c:\\img_out.jpg", mDheProcess->imgOutput());
}

void TestDheProcess::test_x()
{
  mDheProcess->setX(3);
  QCOMPARE(3, mDheProcess->x());
}

  
void TestDheProcess::test_reset()
{
  mDheProcess->setImgInput("c:\\img_in.jpg");
  mDheProcess->setImgOutput("c:\\img_out.jpg");
  mDheProcess->setX(3);
  
  mDheProcess->reset();
  
  QCOMPARE("", mDheProcess->imgInput());
  QCOMPARE("", mDheProcess->imgOutput());
  QCOMPARE(1, mDheProcess->x());
}


QTEST_MAIN(TestDheProcess)

#include "tst_dheprocess.moc"
