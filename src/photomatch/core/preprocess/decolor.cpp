#include "decolor.h"

#include <opencv2/photo.hpp>

namespace photomatch
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
  return QString("Decolorization");
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

bool DecolorPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, imgOut, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(imgOut);
    }

  } catch (cv::Exception &e) {
    msgError("Decolor image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


} // namespace photomatch
