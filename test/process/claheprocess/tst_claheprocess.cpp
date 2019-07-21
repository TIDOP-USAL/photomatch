#include <QtTest>

#include "fme/process/ImagePreprocessing/ClaheProcess.h"

using namespace fme;

class TestClaheProcess : public QObject
{
  Q_OBJECT

public:

  TestClaheProcess();
  ~TestClaheProcess();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_tilesGridSize();
  void test_imgInput();
  void test_imgOutput();
  void test_clipLimit();
  void test_reset();
  
protected:

  ClaheProcess *mClaheProcess;
};

TestClaheProcess::TestClaheProcess()
  : mClaheProcess(new ClaheProcess)
{
}

TestClaheProcess::~TestClaheProcess()
{
  if (mClaheProcess){
    delete mClaheProcess;
  }
}

void TestClaheProcess::initTestCase()
{

}

void TestClaheProcess::cleanupTestCase()
{

}

void TestClaheProcess::testConstructor()
{
  ClaheProcess def;
  QCOMPARE(QSize(8, 8), def.tilesGridSize());
  QCOMPARE("", def.imgInput());
  QCOMPARE("", def.imgOutput());
  QCOMPARE(40., def.clipLimit());
  
  ClaheProcess par("file_in.jpg", "file_out.jpg", 20., QSize(5, 5));
  QCOMPARE(QSize(5, 5), par.tilesGridSize());
  QCOMPARE("file_in.jpg", par.imgInput());
  QCOMPARE("file_out.jpg", par.imgOutput());
  QCOMPARE(20., par.clipLimit());
}

void TestClaheProcess::test_tilesGridSize()
{
  mClaheProcess->setTilesGridSize(QSize(15, 15));
  QCOMPARE(QSize(15, 15), mClaheProcess->tilesGridSize());
}

void TestClaheProcess::test_imgInput()
{
  mClaheProcess->setImgInput("c:\\img_in.jpg");
  QCOMPARE("c:\\img_in.jpg", mClaheProcess->imgInput());
}

void TestClaheProcess::test_imgOutput()
{
  mClaheProcess->setImgOutput("c:\\img_out.jpg");
  QCOMPARE("c:\\img_out.jpg", mClaheProcess->imgOutput());
}

void TestClaheProcess::test_clipLimit()
{
  mClaheProcess->setClipLimit(30);
  QCOMPARE(30., mClaheProcess->clipLimit());
}

  
void TestClaheProcess::test_reset()
{
  mClaheProcess->setTilesGridSize(QSize(15, 15));
  mClaheProcess->setImgInput("c:\\img_in.jpg");
  mClaheProcess->setImgOutput("c:\\img_out.jpg");
  mClaheProcess->setClipLimit(30.0);
  
  mClaheProcess->reset();
  
  QCOMPARE(QSize(8, 8), mClaheProcess->tilesGridSize());
  QCOMPARE("", mClaheProcess->imgInput());
  QCOMPARE("", mClaheProcess->imgOutput());
  QCOMPARE(40.0, mClaheProcess->clipLimit());
}


QTEST_MAIN(TestClaheProcess)

#include "tst_claheprocess.moc"
