#include "lss.h"

#include <tidop/core/messages.h>

namespace fme
{


LssProperties::LssProperties()
  : ILss()
{
}

LssProperties::~LssProperties()
{

}

void LssProperties::reset()
{
}

QString LssProperties::name() const
{
  return QString("LSS");
}

/*----------------------------------------------------------------*/


LssDescriptor::LssDescriptor()
  : LssProperties(),
    DescriptorExtractor(),
    mLSS(new LSS)
{
  update();
}

LssDescriptor::~LssDescriptor()
{

}

void LssDescriptor::update()
{
}

bool LssDescriptor::extract(const cv::Mat &img,
                            std::vector<cv::KeyPoint> &keyPoints,
                            cv::Mat &descriptors)
{

  try {

    cv::Mat cvImg;
    img.convertTo(cvImg, CV_32F);
    std::vector<cv::Mat_<float>> aux_des_left;

    std::vector<cv::KeyPoint> lss_key;

    for (size_t i = 0; i < keyPoints.size(); i++) {
      cv::Mat_<float> enter;
      int error = mLSS->compute(keyPoints[i].pt, cvImg, enter);
      if (error == 1) {
        aux_des_left.push_back(enter);
        lss_key.push_back(keyPoints[i]);
      }
    }

    cv::Mat tempDesc = cv::Mat(static_cast<int>(aux_des_left.size()), aux_des_left[0].rows*aux_des_left[0].cols, CV_32FC1);

    for (size_t i = 0; i < aux_des_left.size(); i++) {
      int i1 = 0;
      for (int j = 0; j < aux_des_left[i].cols; j++) {

        for (int k = 0; k < aux_des_left[i].rows; k++) {
          float aux = aux_des_left[i].at<float>(k, j);
          tempDesc.at<float>(static_cast<int>(i), i1) = aux;
          i1++;
        }

      }
    }

    descriptors = tempDesc;
    keyPoints = lss_key;

  } catch (cv::Exception &e) {
    msgError("LSS Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void LssDescriptor::reset()
{
  LssProperties::reset();
  update();
}


} // namespace fme
