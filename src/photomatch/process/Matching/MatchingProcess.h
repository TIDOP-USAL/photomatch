#ifndef PHOTOMATCH_MATCHING_PROCESS_H
#define PHOTOMATCH_MATCHING_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/features/matcher.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT MatchingProcess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  MatchingProcess(const QString &queryDescriptors,
                  const QString &trainDescriptors,
                  const QString &matches,
                  const std::shared_ptr<RobustMatching> &descriptorMatcher
                  );

  QString queryDescriptors() const;
  void setQueryDescriptors(const QString &descriptors);
  QString trainDescriptors() const;
  void setTrainDescriptors(const QString &descriptors);
  QString matches() const;
  void setMatches(const QString &matches);

signals:

  void matchCompute(QString, QString, QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mQueryDescriptors;
  QString mTrainDescriptors;
  QString mMatches;
  std::shared_ptr<RobustMatching> mDescriptorMatcher;

};

} // namespace photomatch

#endif // PHOTOMATCH_MATCHING_PROCESS_H
