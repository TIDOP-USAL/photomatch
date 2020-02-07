#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/BriefWidget.h"

using namespace photomatch;

class TestBriefWidget : public QObject
{
  Q_OBJECT

public:

  TestBriefWidget();
  ~TestBriefWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_bytes_data();
  void test_bytes();
  void test_useOrientation_data();
  void test_useOrientation();

private:

  BriefWidget *mBriefWidget;
};

TestBriefWidget::TestBriefWidget()
  : mBriefWidget(new BriefWidgetImp)
{

}

TestBriefWidget::~TestBriefWidget()
{
  if (mBriefWidget){
    delete mBriefWidget;
    mBriefWidget = nullptr;
  }
}

void TestBriefWidget::initTestCase()
{
  QCOMPARE("32", mBriefWidget->bytes());
  QCOMPARE(false, mBriefWidget->useOrientation());
}

void TestBriefWidget::cleanupTestCase()
{
  mBriefWidget->setBytes("16");
  mBriefWidget->setUseOrientation(true);

  mBriefWidget->reset();

  QCOMPARE("32", mBriefWidget->bytes());
  QCOMPARE(false, mBriefWidget->useOrientation());
}

void TestBriefWidget::test_windowTitle()
{
  QCOMPARE("BRIEF", mBriefWidget->windowTitle());
}

void TestBriefWidget::test_bytes_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("16") << "16" << "16";
  QTest::newRow("32") << "32" << "32";
  QTest::newRow("64") << "64" << "64";
  QTest::newRow("bad_value") << "bad_value" << "64";

}

void TestBriefWidget::test_bytes()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mBriefWidget->setBytes(value);
  QCOMPARE(result, mBriefWidget->bytes());
}

void TestBriefWidget::test_useOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestBriefWidget::test_useOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mBriefWidget->setUseOrientation(value);
  QCOMPARE(result, mBriefWidget->useOrientation());
}


QTEST_MAIN(TestBriefWidget)

#include "tst_briefwidget.moc"
