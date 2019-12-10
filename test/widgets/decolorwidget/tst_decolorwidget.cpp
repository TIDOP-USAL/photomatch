#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/DecolorWidget.h"

using namespace photomatch;

class TestDecolorWidget : public QObject
{
  Q_OBJECT

public:
  TestDecolorWidget();
  ~TestDecolorWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();

private:

  IDecolorWidget *mDecolorWidget;
};

TestDecolorWidget::TestDecolorWidget()
  : mDecolorWidget(new DecolorWidget)
{

}

TestDecolorWidget::~TestDecolorWidget()
{
  if (mDecolorWidget){
    delete mDecolorWidget;
    mDecolorWidget = nullptr;
  }
}

void TestDecolorWidget::initTestCase()
{

}

void TestDecolorWidget::cleanupTestCase()
{

}

void TestDecolorWidget::test_windowTitle()
{
  QCOMPARE("Decolorization", mDecolorWidget->windowTitle());
}


QTEST_MAIN(TestDecolorWidget)

#include "tst_decolorwidget.moc"
