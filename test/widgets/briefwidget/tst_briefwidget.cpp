#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/BriefWidget.h"

using namespace fme;

class TestBriefWidget : public QObject
{
  Q_OBJECT

public:
  TestBriefWidget();
  ~TestBriefWidget();

private slots:

  void testDefaultConstructor();
  void testBytes_data();
  void testBytes();
  void testUseOrientation_data();
  void testUseOrientation();
  void testReset();

private:

  IBriefWidget *mBriefWidget;
};

TestBriefWidget::TestBriefWidget()
  : mBriefWidget(new BriefWidget)
{

}

TestBriefWidget::~TestBriefWidget()
{
  if (mBriefWidget){
    delete mBriefWidget;
    mBriefWidget = nullptr;
  }
}

void TestBriefWidget::testDefaultConstructor()
{
  BriefWidget brief;
  /// Check default values
  QCOMPARE("32", brief.bytes());
  QCOMPARE(false, brief.useOrientation());
}

void TestBriefWidget::testBytes_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("16") << "16" << "16";
  QTest::newRow("32") << "32" << "32";
  QTest::newRow("64") << "64" << "64";
  QTest::newRow("bad_value") << "bad_value" << "64";

}

void TestBriefWidget::testBytes()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mBriefWidget->setBytes(value);
  QCOMPARE(result, mBriefWidget->bytes());
}

void TestBriefWidget::testUseOrientation_data()
{
  QTest::addColumn<bool>("value");
  QTest::addColumn<bool>("result");

  QTest::newRow("false") << false << false;
  QTest::newRow("true") << true << true;
}

void TestBriefWidget::testUseOrientation()
{
  QFETCH(bool, value);
  QFETCH(bool, result);

  mBriefWidget->setUseOrientation(value);
  QCOMPARE(result, mBriefWidget->useOrientation());
}

void TestBriefWidget::testReset()
{
  mBriefWidget->setBytes("16");
  mBriefWidget->setUseOrientation(true);

  mBriefWidget->reset();

  QCOMPARE("32", mBriefWidget->bytes());
  QCOMPARE(false, mBriefWidget->useOrientation());
}

QTEST_MAIN(TestBriefWidget)

#include "tst_briefwidget.moc"
