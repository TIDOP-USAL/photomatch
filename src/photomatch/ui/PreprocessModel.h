#ifndef PHOTOMATCH_PREPROCESS_MODEL_H
#define PHOTOMATCH_PREPROCESS_MODEL_H

namespace photomatch
{

class IPreprocessModel
{

public:

  IPreprocessModel(){}

};


class PreprocessModel
  : public IPreprocessModel
{
public:
  PreprocessModel();
};

} // namespace photomatch

#endif // PHOTOMATCH_PREPROCESS_MODEL_H
