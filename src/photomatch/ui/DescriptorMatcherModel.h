#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_MODEL_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_MODEL_H

namespace photomatch
{

class IDescriptorMatcherModel
{

public:

  IDescriptorMatcherModel() {}
};


class DescriptorMatcherModel
  : public IDescriptorMatcherModel
{
public:
  DescriptorMatcherModel();
};

} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_MODEL_H
