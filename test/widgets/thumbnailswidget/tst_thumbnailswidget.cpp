#include <QtTest>
#include <QCoreApplication>

#include "photomatch/widgets/ThumbnailsWidget.h"

using namespace photomatch;

class TestThumbnailsWidget : public QObject
{
  Q_OBJECT

public:
  TestThumbnailsWidget();
  ~TestThumbnailsWidget();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();

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

void TestThumbnailsWidget::test_windowTitle()
{
  QCOMPARE("Thumbnails", mThumbnailsWidget->windowTitle());
}

QTEST_MAIN(TestThumbnailsWidget)

#include "tst_thumbnailswidget.moc"
