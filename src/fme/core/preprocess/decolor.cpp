#include "decolor.h"

#include <opencv2/photo.hpp>

namespace fme
{

DecolorProperties::DecolorProperties()
  : IDecolor()
{
}

void DecolorProperties::reset()
{
}

QString DecolorProperties::name() const
{
  return QString("Decolor");
}




/*----------------------------------------------------------------*/


DecolorPreprocess::DecolorPreprocess()
  : DecolorProperties(),
    ImageProcess()
{
}

DecolorPreprocess::~DecolorPreprocess()
{
}

void DecolorPreprocess::reset()
{

}

cv::Mat DecolorPreprocess::process(const cv::Mat &img)
{
  cv::Mat img_out;
  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img_out, color_boost);
    color_boost.release();
  } else {
    img.copyTo(img_out);
  }

  return img_out;
}


} // namespace fme
