#include <QtTest>
#include <QCoreApplication>

#include "fme/widgets/ThumbnailsWidget.h"

using namespace fme;

class TestThumbnailsWidget : public QObject
{
  Q_OBJECT

public:
  TestThumbnailsWidget();
  ~TestThumbnailsWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testDefaultConstructor();
  void test_windowTitle();
  void testReset();

private:

  ThumbnailsWidget *mThumbnailsWidget;

};

TestThumbnailsWidget::TestThumbnailsWidget()
{
  mThumbnailsWidget = new ThumbnailsWidget();
}

TestThumbnailsWidget::~TestThumbnailsWidget()
{
  if (mThumbnailsWidget){
    delete mThumbnailsWidget;
    mThumbnailsWidget = nullptr;
  }
}

void TestThumbnailsWidget::initTestCase()
{

}

void TestThumbnailsWidget::cleanupTestCase()
{

}

void TestThumbnailsWidget::testDefaultConstructor()
{
  ///// Check default values
}

void TestThumbnailsWidget::test_windowTitle()
{
  QCOMPARE("Thumbnails", mThumbnailsWidget->windowTitle());
}

void TestThumbnailsWidget::testReset()
{

  mThumbnailsWidget->reset();

}

QTEST_MAIN(TestThumbnailsWidget)

#include "tst_thumbnailswidget.moc"
