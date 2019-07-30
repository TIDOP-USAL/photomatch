#ifndef FME_FEATURE_EXTRACTOR_PROCESS_H
#define FME_FEATURE_EXTRACTOR_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/features/features.h"

namespace fme
{

class KeypointDetector;
class DescriptorExtractor;

class FME_EXPORT FeatureExtractor
  : public ProcessConcurrent
{

public:

  FeatureExtractor(const QString &img,
                   const QString &features,
                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor);


  QString image() const;
  void setImage(const QString &image);
  QString features() const;
  void setFeatures(const QString &features);

  std::shared_ptr<KeypointDetector> keypointDetector() const;
  std::shared_ptr<DescriptorExtractor> descriptorExtractor() const;

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImage;
  QString mFeatures;
  std::shared_ptr<KeypointDetector> mKeypointDetector;
  std::shared_ptr<DescriptorExtractor> mDescriptorExtractor;

};


} // namespace fme

#endif // FME_FEATURE_EXTRACTOR_PROCESS_H
