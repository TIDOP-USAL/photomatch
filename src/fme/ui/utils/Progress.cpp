#include "Progress.h"

namespace fme
{

Progress::Progress()
{}

Progress::~Progress()
{}

void Progress::setRange(int min, int max)
{
  emit rangeChange(min, max);
}

void Progress::setValue(int value)
{
  emit valueChange(value);
}

} // namespace fme


