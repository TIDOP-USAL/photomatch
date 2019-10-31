#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_MODEL_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_MODEL_H

namespace photomatch
{

class IFeatureExtractorModel
{

public:

  IFeatureExtractorModel(){}

};


class FeatureExtractorModel
  : public IFeatureExtractorModel
{
public:
  FeatureExtractorModel();
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_MODEL_H
