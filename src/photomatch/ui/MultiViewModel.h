#ifndef PHOTOMATCH_MULTIVIEW_MODEL_H
#define PHOTOMATCH_MULTIVIEW_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IMultiViewModel
  : public IModel
{

  Q_OBJECT

public:

  IMultiViewModel(){}
  virtual ~IMultiViewModel() override {}

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual void loadPassPoints() = 0;
  virtual std::vector<size_t> passPointIds() const = 0;
  virtual std::vector<std::pair<size_t, size_t>> passPointIdsAndSize() const = 0;
  virtual std::vector<std::pair<QString, QPointF>> images(size_t passPointId) const = 0;
};



class MultiViewModel
  : public IMultiViewModel
{

  Q_OBJECT

public:

  MultiViewModel(IProjectModel *mProjectModel);
  ~MultiViewModel() override;

// IMatchViewerModel interface

public:

  QString sessionName() const override;
  void setSessionName(const QString &session) override;
  void loadPassPoints() override;
  std::vector<size_t> passPointIds() const override;
  std::vector<std::pair<size_t, size_t>> passPointIdsAndSize() const override;
  std::vector<std::pair<QString, QPointF>> images(size_t passPointId) const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  std::vector<std::vector<std::pair<QString,int>>> mPassPoints;
  QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_MODEL_H
