/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "surf.h"

#include <tidop/core/messages.h>


namespace photomatch
{


SurfProperties::SurfProperties()
  : Surf(),
    mHessianThreshold(100),
    mOctaves(4),
    mOctaveLayers(3),
    mExtendedDescriptor(false),
    mUpright(false)
{
}

SurfProperties::SurfProperties(const SurfProperties &surfProperties)
  : Surf(),
    mHessianThreshold(surfProperties.mHessianThreshold),
    mOctaves(surfProperties.octaves()),
    mOctaveLayers(surfProperties.mOctaveLayers),
    mExtendedDescriptor(surfProperties.mExtendedDescriptor),
    mUpright(surfProperties.mUpright)
{
}

SurfProperties::~SurfProperties()
{
}

double SurfProperties::hessianThreshold() const
{
  return mHessianThreshold;
}

void SurfProperties::setHessianThreshold(double hessianThreshold)
{
  mHessianThreshold = hessianThreshold;
}

int SurfProperties::octaves() const
{
  return mOctaves;
}

void SurfProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

int SurfProperties::octaveLayers() const
{
  return mOctaveLayers;
}

void SurfProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

bool SurfProperties::extendedDescriptor() const
{
  return mExtendedDescriptor;
}

void SurfProperties::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor = extendedDescriptor;
}

bool SurfProperties::upright() const
{
  return mUpright;
}

void SurfProperties::setUpright(bool upright)
{
  mUpright = upright;
}

void SurfProperties::reset()
{
  mHessianThreshold = 100;
  mOctaves = 4;
  mOctaveLayers = 3;
  mExtendedDescriptor = false;
  mUpright = false;
}

QString SurfProperties::name() const
{
  return QString("SURF");
}


/*----------------------------------------------------------------*/

#ifdef OPENCV_ENABLE_NONFREE

SurfDetectorDescriptor::SurfDetectorDescriptor()
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor()
{
  mSurf = cv::xfeatures2d::SURF::create(SurfProperties::hessianThreshold(),
                                        SurfProperties::octaves(),
                                        SurfProperties::octaveLayers(),
                                        SurfProperties::extendedDescriptor(),
                                        SurfProperties::upright());
}

SurfDetectorDescriptor::SurfDetectorDescriptor(const SurfDetectorDescriptor &surfDetectorDescriptor)
  : SurfProperties(surfDetectorDescriptor),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(surfDetectorDescriptor.mSurf)
{
}

SurfDetectorDescriptor::SurfDetectorDescriptor(double hessianThreshold,
                                               int octaves,
                                               int octaveLayers,
                                               bool extendedDescriptor,
                                               bool upright)
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(cv::xfeatures2d::SURF::create())
{
  setHessianThreshold(hessianThreshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setExtendedDescriptor(extendedDescriptor);
  setUpright(upright);
}

SurfDetectorDescriptor::~SurfDetectorDescriptor()
{

}

bool SurfDetectorDescriptor::detect(const cv::Mat &img,
                                    std::vector<cv::KeyPoint> &keyPoints,
                                    cv::InputArray &mask)
{

  try {
    mSurf->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("SURF Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool SurfDetectorDescriptor::extract(const cv::Mat &img,
                                     std::vector<cv::KeyPoint> &keyPoints,
                                     cv::Mat &descriptors)
{

  try {
    mSurf->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("SURF Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void SurfDetectorDescriptor::setHessianThreshold(double hessianThreshold)
{
  SurfProperties::setHessianThreshold(hessianThreshold);
  mSurf->setHessianThreshold(hessianThreshold);
}

void SurfDetectorDescriptor::setOctaves(int octaves)
{
  SurfProperties::setOctaves(octaves);
  mSurf->setNOctaves(octaves);
}

void SurfDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  SurfProperties::setOctaveLayers(octaveLayers);
  mSurf->setNOctaveLayers(octaveLayers);
}

void SurfDetectorDescriptor::setExtendedDescriptor(bool extendedDescriptor)
{
  SurfProperties::setExtendedDescriptor(extendedDescriptor);
  mSurf->setExtended(extendedDescriptor);
}

void SurfDetectorDescriptor::setUpright(bool rotatedFeatures)
{
  SurfProperties::setUpright(rotatedFeatures);
  mSurf->setUpright(rotatedFeatures);
}

void SurfDetectorDescriptor::reset()
{
  SurfProperties::reset();
  mSurf->setHessianThreshold(SurfProperties::hessianThreshold());
  mSurf->setNOctaves(SurfProperties::octaves());
  mSurf->setNOctaveLayers(SurfProperties::octaveLayers());
  mSurf->setExtended(SurfProperties::extendedDescriptor());
  mSurf->setUpright(SurfProperties::upright());

}



/*----------------------------------------------------------------*/


#ifdef HAVE_CUDA

SurfCudaDetectorDescriptor::SurfCudaDetectorDescriptor()
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(new cv::cuda::SURF_CUDA())
{
  mSurf->hessianThreshold = SurfProperties::hessianThreshold();
  mSurf->nOctaves = SurfProperties::octaves();
  mSurf->nOctaveLayers = SurfProperties::octaveLayers();
  mSurf->extended = SurfProperties::extendedDescriptor();
  mSurf->upright = SurfProperties::upright();
}

SurfCudaDetectorDescriptor::SurfCudaDetectorDescriptor(const SurfCudaDetectorDescriptor &surfDetectorDescriptor)
  : SurfProperties(surfDetectorDescriptor),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(new cv::cuda::SURF_CUDA())
{
  mSurf->hessianThreshold = SurfProperties::hessianThreshold();
  mSurf->nOctaves = SurfProperties::octaves();
  mSurf->nOctaveLayers = SurfProperties::octaveLayers();
  mSurf->extended = SurfProperties::extendedDescriptor();
  mSurf->upright = SurfProperties::upright();
}

SurfCudaDetectorDescriptor::SurfCudaDetectorDescriptor(double hessianThreshold,
                                                       int octaves,
                                                       int octaveLayers,
                                                       bool extendedDescriptor,
                                                       bool upright)
  : SurfProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mSurf(new cv::cuda::SURF_CUDA())
{
  setHessianThreshold(hessianThreshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setExtendedDescriptor(extendedDescriptor);
  setUpright(upright);
}

SurfCudaDetectorDescriptor::~SurfCudaDetectorDescriptor()
{

}

bool SurfCudaDetectorDescriptor::detect(const cv::Mat &img,
                                        std::vector<cv::KeyPoint> &keyPoints,
                                        cv::InputArray &mask)
{

  try {
    cv::cuda::GpuMat g_img(img);
    cv::cuda::GpuMat g_mask(mask);
    (*mSurf)(g_img, g_mask, keyPoints);
  } catch (cv::Exception &e) {
    msgError("SURF Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool SurfCudaDetectorDescriptor::extract(const cv::Mat &img,
                                         std::vector<cv::KeyPoint> &keyPoints,
                                         cv::Mat &descriptors)
{

  try {
    cv::cuda::GpuMat g_img(img);
    cv::cuda::GpuMat g_descriptors;
    (*mSurf)(g_img, cv::cuda::GpuMat(), keyPoints, g_descriptors, true);
    g_descriptors.download(descriptors);
  } catch (cv::Exception &e) {
    msgError("SURF Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void SurfCudaDetectorDescriptor::setHessianThreshold(double hessianThreshold)
{
  SurfProperties::setHessianThreshold(hessianThreshold);
  mSurf->hessianThreshold = hessianThreshold;
}

void SurfCudaDetectorDescriptor::setOctaves(int octaves)
{
  SurfProperties::setOctaves(octaves);
  mSurf->nOctaves = octaves;
}

void SurfCudaDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  SurfProperties::setOctaveLayers(octaveLayers);
  mSurf->nOctaveLayers = octaveLayers;
}

void SurfCudaDetectorDescriptor::setExtendedDescriptor(bool extendedDescriptor)
{
  SurfProperties::setExtendedDescriptor(extendedDescriptor);
  mSurf->extended = extendedDescriptor;
}

void SurfCudaDetectorDescriptor::setUpright(bool upright)
{
  SurfProperties::setUpright(upright);
  mSurf->upright = upright;
}

void SurfCudaDetectorDescriptor::reset()
{
  SurfProperties::reset();
  mSurf->hessianThreshold = SurfProperties::hessianThreshold();
  mSurf->nOctaves = SurfProperties::octaves();
  mSurf->nOctaveLayers = SurfProperties::octaveLayers();
  mSurf->extended = SurfProperties::extendedDescriptor();
  mSurf->upright = SurfProperties::upright();
}


#endif // HAVE_CUDA

#endif // OPENCV_ENABLE_NONFREE

} // namespace photomatch







