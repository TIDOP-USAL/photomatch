#ifndef FME_MATCHING_PROCESS_H
#define FME_MATCHING_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/features/matcher.h"

namespace fme
{

class FME_EXPORT MatchingProcess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  MatchingProcess(const QString &queryDescriptors,
                  const QString &trainDescriptors,
                  const QString &matches,
                  const std::shared_ptr<DescriptorMatcher> &descriptorMatcher);

  QString queryDescriptors() const;
  void setQueryDescriptors(const QString &descriptors);
  QString trainDescriptors() const;
  void setTrainDescriptors(const QString &descriptors);
  QString matches() const;
  void setMatches(const QString &matches);
  std::shared_ptr<DescriptorMatcher> descriptorMatcher() const;

signals:

  void matchCompute(QString, QString, QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mQueryDescriptors;
  QString mTrainDescriptors;
  QString mMatches;
  std::shared_ptr<DescriptorMatcher> mDescriptorMatcher;

};

} // namespace fme

#endif // FME_MATCHING_PROCESS_H
