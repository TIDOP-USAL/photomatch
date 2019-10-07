#ifndef FME_FEATURE_EXTRACTOR_PROCESS_H
#define FME_FEATURE_EXTRACTOR_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/features/features.h"

namespace fme
{

class FME_EXPORT FeatureExtractor
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  FeatureExtractor(const QString &img,
                   const QString &features,
                   double scale,
                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor);


  QString image() const;
  void setImage(const QString &image);
  QString features() const;
  void setFeatures(const QString &features);
  void setScale(double scale);

  std::shared_ptr<KeypointDetector> keypointDetector() const;
  std::shared_ptr<DescriptorExtractor> descriptorExtractor() const;

signals:

  void featuresExtracted(QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImage;
  QString mFeatures;
  double mScale;
  std::shared_ptr<KeypointDetector> mKeypointDetector;
  std::shared_ptr<DescriptorExtractor> mDescriptorExtractor;

};


} // namespace fme

#endif // FME_FEATURE_EXTRACTOR_PROCESS_H
