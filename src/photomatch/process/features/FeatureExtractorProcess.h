#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/features/features.h"
#include "photomatch/core/features/keypointsfilter.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT FeatureExtractor
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  FeatureExtractor(const QString &img,
                   const QString &features,
                   double scale,
                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor,
                   const std::list<std::shared_ptr<KeyPointsFilterProcess>> &keyPointsFiltersProcess);


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
  std::list<std::shared_ptr<KeyPointsFilterProcess>> mKeyPointsFiltersProcess;
};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H
