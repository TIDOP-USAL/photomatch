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


#include "FeatureExtractorProcess.h"

#include <tidop/core/messages.h>
#include <tidop/core/exception.h>

#include "photomatch/core/features/featio.h"

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace photomatch
{

FeatureExtractor::FeatureExtractor(const QString &image,
                                   const QString &features,
                                   double imageScale,
                                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor,
                                   const std::list<std::shared_ptr<KeyPointsFilterProcess>> &keyPointsFiltersProcess)
  : ProcessConcurrent(),
    mImage(image),
    mFeatures(features),
    mImageScale(imageScale),
    mKeypointDetector(keypointDetector),
    mDescriptorExtractor(descriptorExtractor),
    mKeyPointsFiltersProcess(keyPointsFiltersProcess)
{
}

QString FeatureExtractor::image() const
{
  return mImage;
}

void FeatureExtractor::setImage(const QString &image)
{
  mImage = image;
}

QString FeatureExtractor::features() const
{
  return mFeatures;
}

void FeatureExtractor::setFeatures(const QString &features)
{
  mFeatures = features;
}

void FeatureExtractor::setScale(double scale)
{
  mImageScale = scale;
}

std::shared_ptr<DescriptorExtractor> FeatureExtractor::descriptorExtractor() const
{
  return mDescriptorExtractor;
}

std::shared_ptr<KeypointDetector> FeatureExtractor::keypointDetector() const
{
  return mKeypointDetector;
}

void FeatureExtractor::run()
{

  try {

    QByteArray ba = mImage.toLocal8Bit();
    const char *img_file = ba.data();

    if (!QFileInfo::exists(mImage)) TL_THROW_ERROR("Image doesn't exist: %s", img_file);

    cv::Mat img = cv::imread(img_file, cv::IMREAD_IGNORE_ORIENTATION);
    if (img.empty()) TL_THROW_ERROR("Could not load image: %s", img_file);

    if (mKeypointDetector == nullptr) {
      emit error(0, "Keypoint Detector error");
      TL_THROW_ERROR("Keypoint Detector error");
    }

    msgInfo("Searching Keypoints for image %s", img_file);

    tl::Chrono chrono;
    chrono.run();

    std::vector<cv::KeyPoint> key_points = mKeypointDetector->detect(img);

    uint64_t time = chrono.stop();
    msgInfo("%i Keypoints detected in image %s [Time: %f seconds]", key_points.size(), img_file, time / 1000.);

    /// Filtrado de puntos
    for (auto &filter : mKeyPointsFiltersProcess) {
      key_points = filter->filter(key_points);
    }

    if (mDescriptorExtractor == nullptr) {
      emit error(0, "Descriptor Extractor Error");
      TL_THROW_ERROR("Descriptor Extractor error");
    }

    msgInfo("Computing keypoints descriptors for image %s", img_file);

    chrono.reset();
    chrono.run();

    cv::Mat descriptors = mDescriptorExtractor->extract(img, key_points);

    time = chrono.stop();
    msgInfo("Descriptors computed for image %s [Time: %f seconds]", img_file, time / 1000.);

    for (size_t i = 0; i < key_points.size(); i++) {
      key_points[i].pt *= mImageScale;
      key_points[i].size *= static_cast<float>(mImageScale);
    }

    std::unique_ptr<FeaturesWriter> writer = FeaturesWriterFactory::createWriter(mFeatures);
    writer->setKeyPoints(key_points);
    writer->setDescriptors(descriptors);
    writer->write();

    ba = mFeatures.toLocal8Bit();
    const char *cfeat = ba.data();
    msgInfo("Write features at: %s", cfeat);
    emit featuresExtracted(mFeatures);
    emit statusChangedNext();

  } catch (const std::exception &e) {
    tl::MessageManager::release(e.what(), tl::MessageLevel::msg_error);
  } catch (...) {
    msgError("Feature Extractor unknow exception");
  }

}

} // namespace photomatch
