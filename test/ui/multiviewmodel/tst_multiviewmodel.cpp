#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/multiview/MultiViewModel.h"


using namespace photomatch;


class TestMultiViewModel
  : public QObject
{
  Q_OBJECT

public:

  TestMultiViewModel();
  ~TestMultiViewModel();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void test_constructor();
  void test_sessions();
  void test_sessionName();
  void test_activeSession();
  void test_sessionChange();
  void test_imageFiles();
  void test_dialogButtonBox();
  void test_clear();

private:

  MultiViewModel *mMultiViewModel;
};

TestMultiViewModel::TestMultiViewModel()
{
}

TestMultiViewModel::~TestMultiViewModel()
{

}

void TestMultiViewModel::initTestCase()
{

}

void TestMultiViewModel::cleanupTestCase()
{

}

void TestMultiViewModel::test_constructor()
{

}

void TestMultiViewModel::test_sessions()
{

}

void TestMultiViewModel::test_sessionName()
{
  
}

void TestMultiViewModel::test_activeSession()
{

}

void TestMultiViewModel::test_sessionChange()
{

}



void TestMultiViewModel::test_clear()
{

}

QTEST_MAIN(TestMultiViewModel)

#include "tst_multiviewmodel.moc"
