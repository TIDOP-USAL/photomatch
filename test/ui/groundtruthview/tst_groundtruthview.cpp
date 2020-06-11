#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/groundtruth/GroundTruthView.h"


#include <QListWidget>

using namespace photomatch;

class TestGroundTruthView
  : public GroundTruthViewImp
{
  Q_OBJECT

public:

  TestGroundTruthView();
  ~TestGroundTruthView();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_windowTitle();
  void test_leftImage();
  void test_rightImage();

private:

  std::vector<QString> images_left;
  std::vector<QString> images_right;
};

TestGroundTruthView::TestGroundTruthView()
  : GroundTruthViewImp()
{
  QApplication::setActiveWindow(this);
}

TestGroundTruthView::~TestGroundTruthView()
{
}

void TestGroundTruthView::initTestCase()
{
  images_left.push_back("C:\\photomatch\\images\\005_005_147000214.tif");
  images_left.push_back("C:\\photomatch\\images\\005_006_147000213.tif");
  images_left.push_back("C:\\photomatch\\images\\005_007_147000212.tif");
  images_left.push_back("C:\\photomatch\\images\\006_005_148000187.tif");
  images_left.push_back("C:\\photomatch\\images\\006_006_148000188.tif");
  images_left.push_back("C:\\photomatch\\images\\006_007_148000189.tif");
  images_left.push_back("C:\\photomatch\\images\\007_005_147000178.tif");
  images_left.push_back("C:\\photomatch\\images\\007_006_147000177.tif");
  images_left.push_back("C:\\photomatch\\images\\007_007_147000176.tif");

  images_right = images_left;
  images_right.erase(images_right.begin(), images_right.begin()+1);

  this->setLeftImageList(images_left);
  this->setLeftImage(QFileInfo(images_left[0]).baseName());
  this->setRightImageList(images_right);
  this->setRightImage(images_right[0]);
}

void TestGroundTruthView::cleanupTestCase()
{
  this->clear();
}

void TestGroundTruthView::test_windowTitle()
{
  QCOMPARE("Ground Truth Editor", this->windowTitle());
}

void TestGroundTruthView::test_leftImage()
{
  QCOMPARE("005_005_147000214", this->leftImage());
}

void TestGroundTruthView::test_rightImage()
{
  QCOMPARE("005_006_147000213", this->rightImage());
}


QTEST_MAIN(TestGroundTruthView)

#include "tst_groundtruthview.moc"
