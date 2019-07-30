#ifndef FME_FEATURE_EXTRACTOR_MODEL_H
#define FME_FEATURE_EXTRACTOR_MODEL_H

namespace fme
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

} // namespace fme

#endif // FME_FEATURE_EXTRACTOR_MODEL_H
