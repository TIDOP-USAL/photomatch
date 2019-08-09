#include "hog.h"

#include <opencv2/imgproc.hpp>

namespace fme
{


HogProperties::HogProperties()
  : IHog(),
    mWinSize(16, 16),
    mBlockSize(4, 4),
    mBlockStride(2, 2),
    mCellSize(2, 2),
    mNbins(9),
    mDerivAperture(1)
{}

HogProperties::~HogProperties()
{

}

QSize HogProperties::winSize() const
{
  return mWinSize;
}

QSize HogProperties::blockSize() const
{
  return mBlockSize;
}

QSize HogProperties::blockStride() const
{
  return mBlockStride;
}

QSize HogProperties::cellSize() const
{
  return mCellSize;
}

int HogProperties::nbins() const
{
  return mNbins;
}

int HogProperties::derivAperture() const
{
  return mDerivAperture;
}

void HogProperties::setWinSize(const QSize &winSize)
{
  mWinSize = winSize;
}

void HogProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void HogProperties::setBlockStride(const QSize &blockStride)
{
  mBlockStride = blockStride;
}

void HogProperties::setCellSize(const QSize &cellSize)
{
  mCellSize = cellSize;
}

void HogProperties::setNbins(int nbins)
{
  mNbins = nbins;
}

void HogProperties::setDerivAperture(int derivAperture)
{
  mDerivAperture = derivAperture;
}

void HogProperties::reset()
{
  mWinSize = QSize(16, 16);
  mBlockSize = QSize(4, 4); //QSize(16,16);
  mBlockStride = QSize(2, 2); //QSize(8,8);
  mCellSize = QSize(2, 2);  //QSize(8,8);
  mNbins = 9;
  mDerivAperture = 1;
}


/*----------------------------------------------------------------*/


HogDescriptor::HogDescriptor()
  : HogProperties(),
    DescriptorExtractor()
{
  update();
}

HogDescriptor::HogDescriptor(QSize winSize,
                             QSize blockSize,
                             QSize blockStride,
                             QSize cellSize,
                             int nbins,
                             int derivAperture)
  : HogProperties(),
    DescriptorExtractor()
{
  HogProperties::setWinSize(winSize);
  HogProperties::setBlockSize(blockSize);
  HogProperties::setBlockStride(blockStride);
  HogProperties::setCellSize(cellSize);
  HogProperties::setNbins(nbins);
  HogProperties::setDerivAperture(derivAperture);
  update();
}

HogDescriptor::~HogDescriptor()
{

}

void HogDescriptor::update()
{
  cv::Size win_size(HogProperties::winSize().width(), HogProperties::winSize().height());
  cv::Size block_size(HogProperties::blockSize().width(), HogProperties::blockSize().height());
  cv::Size block_stride(HogProperties::blockStride().width(), HogProperties::blockStride().height());
  cv::Size cell_size(HogProperties::cellSize().width(), HogProperties::cellSize().height());

  mHOG = std::make_shared<cv::HOGDescriptor>(win_size, block_size, block_stride,
                                             cell_size, HogProperties::nbins(),
                                             HogProperties::derivAperture());
}

void HogDescriptor::normalizepatch(const cv::Mat &gray, const cv::KeyPoint &keypoint, cv::Mat &output)
{

  cv::Point center = keypoint.pt;

  cv::Size outsize(HogProperties::winSize().width(), HogProperties::winSize().height());
  output = cv::Mat::zeros(outsize, CV_8UC1);
  cv::Size maskenter;
  maskenter.height = cvRound(keypoint.size);
  maskenter.width = cvRound(keypoint.size);

  cv::Mat input;
  // Rotation and scale comes from the left corner, that is the center.
  cv::getRectSubPix(gray, maskenter, center, input);


  cv::Point2f pt;

  // here there are a problem with the center, it depends on the value it´s not a trivial thing.
      // solved
  if ((input.cols % 4) == 1) {
    pt.x = cvRound(input.cols / 2.0);
    pt.y = cvRound(input.rows / 2.0);
  } else if ((input.cols % 4) == 0) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  } else if ((input.cols % 4) == 2) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  } else if ((input.cols % 4) == 3) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  }
  // to calculate the scale, is the size of the keypoint between
  // the scale is related to the diagonal of both pathces
 // float scale = 1.0f*std::sqrt((maskenter.height*maskenter.height)+(maskenter.height*maskenter.height))/std::sqrt((outsize.height*outsize.height)+(outsize.height*outsize.height));

  cv::Mat transform = cv::getRotationMatrix2D(pt, static_cast<double>(keypoint.angle), 1.0);
  cv::Mat source1;

  //ROTATE
  cv::warpAffine(input, source1, transform, input.size(), cv::INTER_LINEAR + cv::WARP_INVERSE_MAP, cv::BORDER_REPLICATE);//+cv::WARP_INVERSE_MAP


    // works best in 2 steps instead of one.
  if (outsize.height != input.cols) cv::resize(source1, output, outsize);
  else source1.copyTo(output);
}

cv::Mat HogDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;

  cv::Size win_size(HogProperties::winSize().width(), HogProperties::winSize().height());

  std::vector<float> hogdescriptor;
  std::vector<cv::Point> p_c;
  cv::Point punto_central;
  punto_central.x = win_size.width / 2;
  punto_central.y = win_size.height / 2;
  p_c.push_back(punto_central);

  int size = static_cast<int>(keyPoints.size());
  descriptors = cv::Mat(size, static_cast<int>(mHOG->getDescriptorSize()), CV_32FC1);

  for (int i = 0; i < size; i++) {
    std::vector<float> hogdescriptor_aux;
    cv::Mat patch;
    normalizepatch(img, keyPoints[static_cast<size_t>(i)], patch);
    mHOG->compute(patch, hogdescriptor_aux);
    for (size_t j = 0; j < hogdescriptor_aux.size(); j++)
      descriptors.at<float>(i, static_cast<int>(j)) = hogdescriptor_aux[j];
  }
  //emit newStdData("HOG key-point description finished for image " + mLeftImageName);

  return descriptors;
}

void fme::HogDescriptor::setWinSize(const QSize &winSize)
{
  HogProperties::setWinSize(winSize);
  update();
}

void HogDescriptor::setBlockSize(const QSize &blockSize)
{
  HogProperties::setBlockSize(blockSize);
  update();
}

void HogDescriptor::setBlockStride(const QSize &blockStride)
{
  HogProperties::setBlockStride(blockStride);
  update();
}

void HogDescriptor::setCellSize(const QSize &cellSize)
{
  HogProperties::setCellSize(cellSize);
  update();
}

void HogDescriptor::setNbins(int nbins)
{
  HogProperties::setNbins(nbins);
  update();
}

void HogDescriptor::setDerivAperture(int derivAperture)
{
  HogProperties::setDerivAperture(derivAperture);
  update();
}

void HogDescriptor::reset()
{
  HogProperties::reset();
  update();
}


/*----------------------------------------------------------------*/

} // namespace fme
