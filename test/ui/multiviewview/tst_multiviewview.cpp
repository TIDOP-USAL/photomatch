#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/multiview/MultiViewView.h"

//#include <QPushButton>
//#include <QDialogButtonBox>
#include <QListWidget>
//#include <QComboBox>
//#include <QLineEdit>
//#include <QCheckBox>

using namespace photomatch;

class TestMultiViewView
  : public MultiViewView
{
  Q_OBJECT

public:

  TestMultiViewView();
  ~TestMultiViewView();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_constructor();
  void test_setSessionName();
  void test_setPassPointIds();
  void test_idChange();
  void test_images();
  void test_clear();

private:

};

TestMultiViewView::TestMultiViewView()
  : MultiViewView()
{
  QApplication::setActiveWindow(this);
}

TestMultiViewView::~TestMultiViewView()
{
}

void TestMultiViewView::initTestCase()
{
  std::vector<size_t> ids;
  for (size_t i = 0; i < 10; i++){
    ids.push_back(i);
  }
  this->setPassPointIds(ids);
}

void TestMultiViewView::cleanupTestCase()
{
  this->clear();

  QCOMPARE(0, this->mListWidgetIds->count());
}

void TestMultiViewView::test_windowTitle()
{
  QCOMPARE("Multi-view Pass Points", this->windowTitle());
}

void TestMultiViewView::test_constructor()
{
}

void TestMultiViewView::test_setSessionName()
{
  this->setSessionName("Session 01");
  QCOMPARE("Multi-view Pass Points Session 01", this->windowTitle());
  this->clear();
}

void TestMultiViewView::test_setPassPointIds()
{
//  std::vector<size_t> ids;
//  for (size_t i = 0; i < 10; i++){
//    ids.push_back(i);
//  }
//  this->setPassPointIds(ids);
  QCOMPARE(10, this->mListWidgetIds->count());
  for (size_t i = 0; i < 10; i++){
    QCOMPARE(i, this->mListWidgetIds->item(i)->text().toInt());
  }

  this->addPassPointIds(20);
  QCOMPARE(11, this->mListWidgetIds->count());
  QCOMPARE(20, this->mListWidgetIds->item(10)->text().toInt());

  std::vector<size_t> ids;
  for (size_t i = 0; i < 10; i++){
    ids.push_back(i);
  }
  this->setPassPointIds(ids);
  QCOMPARE(10, this->mListWidgetIds->count());
}

void TestMultiViewView::test_idChange()
{
  QSignalSpy spy_idChange(this, &TestMultiViewView::idChange);

  this->mListWidgetIds->setCurrentRow(2);
  QCOMPARE(spy_idChange.count(), 1);
}

void TestMultiViewView::test_images()
{
  QStringList images;
  images.push_back("C:/images/image1.jpg");
  images.push_back("C:/images/image2.jpg");
  this->setImages(images);

}

void TestMultiViewView::test_clear()
{
//  std::vector<size_t> ids;
//  for (size_t i = 0; i < 10; i++){
//    ids.push_back(i);
//  }
//  this->setPassPointIds(ids);

//  this->clear();

//  QCOMPARE(0, this->mListWidgetIds->count());
}

QTEST_MAIN(TestMultiViewView)

#include "tst_multiviewview.moc"
