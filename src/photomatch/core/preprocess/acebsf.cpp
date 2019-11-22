#include "acebsf.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


AcebsfProperties::AcebsfProperties()
  : IAcebsf(),
    mBlockSize(8, 8),
    mL(0.03),
    mK1(10.),
    mK2(0.5)
{

}

AcebsfProperties::AcebsfProperties(const AcebsfProperties &acebsfProperties)
  : IAcebsf(),
    mBlockSize(acebsfProperties.mBlockSize),
    mL(acebsfProperties.mL),
    mK1(acebsfProperties.mK1),
    mK2(acebsfProperties.mK2)
{
}

AcebsfProperties::AcebsfProperties(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT
  : IAcebsf(),
    mBlockSize(std::move(acebsfProperties.mBlockSize)),
    mL(acebsfProperties.mL),
    mK1(acebsfProperties.mK1),
    mK2(acebsfProperties.mK2)
{
  acebsfProperties.mL = 0.;
  acebsfProperties.mK1 = 0.;
  acebsfProperties.mK2 = 0.;
}

AcebsfProperties &AcebsfProperties::operator=(const AcebsfProperties &acebsfProperties)
{
  if (this != &acebsfProperties) {  
    mBlockSize = acebsfProperties.mBlockSize;
    mL = acebsfProperties.mL;
    mK1 = acebsfProperties.mK1;
    mK2 = acebsfProperties.mK2;
  }
  return *this;
}

AcebsfProperties &AcebsfProperties::operator=(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT
{
  if (this != &acebsfProperties) {  
    mBlockSize = std::move(acebsfProperties.mBlockSize);
    mL = std::move(acebsfProperties.mL);
    mK1 = std::move(acebsfProperties.mK1);
    mK2 = std::move(acebsfProperties.mK2);
  }
  return *this;
}

QSize AcebsfProperties::blockSize() const
{
  return mBlockSize;
}

void AcebsfProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double AcebsfProperties::l() const
{
  return mL;
}

void AcebsfProperties::setL(double l)
{
  mL = l;
}

double AcebsfProperties::k1() const
{
  return mK1;
}

void AcebsfProperties::setK1(double k1)
{
  mK1 = k1;
}

double AcebsfProperties::k2() const
{
  return mK2;
}

void AcebsfProperties::setK2(double k2)
{
  mK2 = k2;
}

void AcebsfProperties::reset()
{
  mBlockSize = QSize(8, 8);
  mL = 0.03;
  mK1 = 10.;
  mK2 = 0.5;
}


/*----------------------------------------------------------------*/


AcebsfPreprocess::AcebsfPreprocess()
  : AcebsfProperties(),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(const AcebsfPreprocess &acebsfPreprocess)
  : AcebsfProperties(acebsfPreprocess),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(AcebsfPreprocess &&acebsfPreprocess) PHOTOMATCH_NOEXCEPT
  : AcebsfProperties(std::forward<AcebsfProperties>(acebsfPreprocess)),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(const QSize &blockSize,
                                   double l, double k1, double k2)
  : AcebsfProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
  setL(l);
  setK1(k1);
  setK2(k2);
}

AcebsfPreprocess::~AcebsfPreprocess()
{

}

bool AcebsfPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat temp;
    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    pixkit::enhancement::local::Lal2014(temp, imgOut,
                                        cv::Size(AcebsfProperties::blockSize().width(),
                                                 AcebsfProperties::blockSize().height()),
                                        static_cast<float>(AcebsfProperties::l()),
                                        static_cast<float>(AcebsfProperties::k1()),
                                        static_cast<float>(AcebsfProperties::k2()));

  } catch (cv::Exception &e) {
    msgError("ACEBSF Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

QString AcebsfProperties::name() const
{
  return QString("ACEBSF");
}

} // namespace photomatch



