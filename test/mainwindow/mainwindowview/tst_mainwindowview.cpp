#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class TestMainWindowView : public QObject
{
  Q_OBJECT

public:
  TestMainWindowView();
  ~TestMainWindowView();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_case1();

};

TestMainWindowView::TestMainWindowView()
{

}

TestMainWindowView::~TestMainWindowView()
{

}

void TestMainWindowView::initTestCase()
{

}

void TestMainWindowView::cleanupTestCase()
{

}

void TestMainWindowView::test_case1()
{

}

QTEST_MAIN(TestMainWindowView)

#include "tst_mainwindowview.moc"
