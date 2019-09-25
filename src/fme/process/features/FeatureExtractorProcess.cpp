#include "FeatureExtractorProcess.h"

#include <tidop/core/messages.h>

#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace fme
{

FeatureExtractor::FeatureExtractor(const QString &img, const QString &features,
                                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor)
  : ProcessConcurrent(),
    mImage(img),
    mFeatures(features),
    mKeypointDetector(keypointDetector),
    mDescriptorExtractor(descriptorExtractor)
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
  QByteArray ba = mImage.toLocal8Bit();
  const char *img_file = ba.data();
  cv::Mat img = cv::imread(img_file, cv::IMREAD_IGNORE_ORIENTATION);

  if (img.empty()) return;

  if (mKeypointDetector == nullptr) return;

  msgInfo("Searching Keypoints for image %s", img_file);
  tl::Chrono chrono;
  chrono.run();
  std::vector<cv::KeyPoint> key_points;
  bool _error = mKeypointDetector->detect(img, key_points);
  if (_error){
    emit error(0, "Keypoint Detector error");
    return;
  }
  uint64_t time = chrono.stop();
  msgInfo("%i Keypoints detected in image %s [Time: %f seconds]", key_points.size(), img_file, time/1000.);



  if (mDescriptorExtractor == nullptr) return;

  msgInfo("Computing keypoints descriptors for image %s", img_file);
  chrono.reset();
  chrono.run();
  cv::Mat descriptors;
  _error = mDescriptorExtractor->extract(img, key_points, descriptors);
  if (_error){
    emit error(0, "Keypoint Descriptor error");
    return;
  }
  time = chrono.stop();
  msgInfo("Descriptors computed for image %s [Time: %f seconds]", img_file, time/1000.);

  cv::Mat out;
  cv::drawKeypoints(img, key_points, out, cv::Scalar(0,255,0), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  QFileInfo fileInfo(mFeatures);
  QString imgKeypoints = fileInfo.path();
  imgKeypoints.append("\\").append(fileInfo.completeBaseName());
  ba = imgKeypoints.toLocal8Bit();
  const char *ckp = ba.data();
  cv::imwrite(ckp, out);

  featuresWrite(mFeatures, key_points, descriptors);
  ba = mFeatures.toLocal8Bit();
  const char *cfeat = ba.data();
  msgInfo("Write features at: %s", cfeat);
  emit featuresExtracted(mFeatures);
  emit statusChangedNext();
}

} // namespace fme
