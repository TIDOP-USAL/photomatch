#ifndef PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H
#define PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT PassPointsGroupingProcess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  PassPointsGroupingProcess(const std::list<std::tuple<QString,QString,QString>> &pairs,
                            const QString &passPointsFile);

  std::list<std::tuple<QString, QString, QString>> pairs() const;
  void setPairs(const std::list<std::tuple<QString, QString, QString>> &pairs);

  QString passPointsFile() const;
  void setPassPointsFile(const QString &passPointsFile);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  std::list<std::tuple<QString,QString,QString>> mPairs;
  QString mPassPointsFile;
};

} // namespace photomatch

#endif // PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H
