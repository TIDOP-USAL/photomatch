#ifndef PHOTOMATCH_MATCH_VIEWER_MODEL_H
#define PHOTOMATCH_MATCH_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

/*!
 * \brief The IMatchViewerModel class
 */
class IMatchViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IMatchViewerModel() {}
  virtual ~IMatchViewerModel() {}

  virtual QString sessionName() const = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> loadMatches(const QString &imgName1, const QString &imgName2) const = 0;
  virtual void deleteMatch(const QString &imgName1, const QString &imgName2, int query_id, int train_id) = 0;

public slots:

};


class MatchViewerModel
  : public IMatchViewerModel
{

  Q_OBJECT

public:

  MatchViewerModel(IProjectModel *mProjectModel);


// IModel interface

private:

  void init() override;

// IMatchViewerModel interface

public:

  QString sessionName() const override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float> > loadMatches(const QString &imgName1, const QString &imgName2) const override;
  void deleteMatch(const QString &imgName1, const QString &imgName2, int query_id, int train_id) override;

protected:

  IProjectModel *mProjectModel;
};

} // namespace photomatch

#endif // PHOTOMATCH_MATCH_VIEWER_MODEL_H
