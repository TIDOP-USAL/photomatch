#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/keypointsfilter.h"

using namespace photomatch;

class TestKeypointsFilter
  : public QObject
{
  Q_OBJECT

public:

  TestKeypointsFilter();
  ~TestKeypointsFilter();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_filterNBest();
  void test_filterBySize();
  void test_filterRemoveDuplicated();
  void test_reset();

private:

  KeyPointsFilterNBest mKeyPointsFilterNBest;
  KeyPointsFilterBySize mKeyPointsFilterBySize;
  KeyPointsFilterRemoveDuplicated mKeyPointsFilterRemoveDuplicated;
  std::vector<cv::KeyPoint> keypoints;
};

TestKeypointsFilter::TestKeypointsFilter()
{

}

TestKeypointsFilter::~TestKeypointsFilter()
{
}

void TestKeypointsFilter::initTestCase()
{
  keypoints.push_back(cv::KeyPoint(cv::Point2f(1405.86f,2094.69f), 85.848f, 259.581f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(792.945f, 2515.82f), 143.08f, 109.442f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(1689.71f, 174.784f), 81.76f, 295.687f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(2247.87f, 5092.51f), 85.848f, 65.0109f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6568.76f, 3151.57f), 77.672f, 312.921f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6585.2f, 4781.47f), 73.584f, 267.216f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6518.77f, 4769.17f), 89.936f, 105.809f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6712.73f, 5371.52f), 65.408f, 268.098f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(5678.36f, 3474.61f), 130.816f, 34.3421f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(5393.6f, 4197.39f), 85.848f, 98.8134f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6530.69f, 3085.86f), 85.848f, 337.088f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(3895.87f, 1950.06f), 85.848f, 26.4722f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(5780.63f, 5543.57f), 85.848f, 80.1563f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(6039.77f, 2337.13f), 61.32f, 203.272f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(3546.49f, 2758.58f), 273.896f, 56.4872f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(4452.33f, 2059.3f), 81.76f, 111.013f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(7395.98f, 6066.66f), 85.848f, 178.975f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(7853.72f, 5481.78f), 81.76f, 301.712f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(511.114f, 4369.56f), 85.848f, 284.296f));
  keypoints.push_back(cv::KeyPoint(cv::Point2f(511.114f, 4369.56f), 85.848f, 284.296f));
}

void TestKeypointsFilter::cleanupTestCase()
{

}

void TestKeypointsFilter::test_constructor()
{
  QCOMPARE(5000, mKeyPointsFilterNBest.nPoints());

  KeyPointsFilterNBest keyPointsFilterNBest(15);
  QCOMPARE(15, keyPointsFilterNBest.nPoints());

  QCOMPARE(0., mKeyPointsFilterBySize.minSize());
  QCOMPARE(TL_DOUBLE_MAX, mKeyPointsFilterBySize.maxSize());

  KeyPointsFilterBySize keyPointsFilterBySize(0.1, 100.);
  QCOMPARE(0.1, keyPointsFilterBySize.minSize());
  QCOMPARE(100., keyPointsFilterBySize.maxSize());
}

void TestKeypointsFilter::test_filterNBest()
{
  std::vector<cv::KeyPoint> filtered_keypoints;
  mKeyPointsFilterNBest.setNPoints(10);
  mKeyPointsFilterNBest.filter(keypoints, filtered_keypoints);
  QCOMPARE(10, filtered_keypoints.size());
}

void TestKeypointsFilter::test_filterBySize()
{
  std::vector<cv::KeyPoint> filtered_keypoints;
  mKeyPointsFilterBySize.setMinSize(70.);
  mKeyPointsFilterBySize.setMaxSize(100.);
  mKeyPointsFilterBySize.filter(keypoints, filtered_keypoints);
  QCOMPARE(15, filtered_keypoints.size());
}

void TestKeypointsFilter::test_filterRemoveDuplicated()
{

}

//void TestKeypointsFilter::test_halfSsdSize()
//{
//  QFETCH(int, value);
//  QFETCH(int, result);

//  mLatchDescriptor->setHalfSsdSize(value);
//  QCOMPARE(result, mLatchDescriptor->halfSsdSize());
//}

void TestKeypointsFilter::test_reset()
{
  mKeyPointsFilterNBest.setNPoints(10000);
  mKeyPointsFilterNBest.reset();
  QCOMPARE(5000, mKeyPointsFilterNBest.nPoints());

  mKeyPointsFilterBySize.setMinSize(0.5);
  mKeyPointsFilterBySize.setMaxSize(100.);
  mKeyPointsFilterBySize.reset();
  QCOMPARE(0., mKeyPointsFilterBySize.minSize());
  QCOMPARE(TL_DOUBLE_MAX, mKeyPointsFilterBySize.maxSize());
}

QTEST_APPLESS_MAIN(TestKeypointsFilter)

#include "tst_keypointsfilter.moc"
