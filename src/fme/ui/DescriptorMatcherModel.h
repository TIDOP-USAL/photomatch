#ifndef FME_DESCRIPTOR_MATCHER_MODEL_H
#define FME_DESCRIPTOR_MATCHER_MODEL_H

namespace fme
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

} // namespace fme

#endif // FME_DESCRIPTOR_MATCHER_MODEL_H
