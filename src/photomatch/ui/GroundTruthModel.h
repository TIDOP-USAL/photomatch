#ifndef PHOTOMATCH_GROUND_TRUTH_MODEL_H
#define PHOTOMATCH_GROUND_TRUTH_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;
class GroundTruth;

class IGroundTruthModel
  : public IModel
{

  Q_OBJECT

public:

  IGroundTruthModel(){}
  virtual ~IGroundTruthModel() override {}

  virtual void loadGroundTruth() = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::pair<QPointF, QPointF>> groundTruth(const QString &imgName1, const QString &imgName2) const = 0;
  virtual QTransform transform(const QString &imgName1, const QString &imgName2) const = 0;
  virtual void saveGroundTruth() = 0;
  virtual void setGroundTruth(const QString &file) = 0;
  virtual bool existGroundTruth() const = 0;
  virtual QString projectPath() const = 0;

public slots:

  virtual void addHomologusPoints(const QString &image1, QPointF pt1, const QString &image2, QPointF pt2) = 0;

};


class GroundTruthModel
  : public IGroundTruthModel
{

  Q_OBJECT

public:

  GroundTruthModel(IProjectModel *mProjectModel);
  ~GroundTruthModel() override;

// IModel interface

private:

  void init() override;

// IGroundTruthModel interface

public:

  void loadGroundTruth() override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::pair<QPointF, QPointF>> groundTruth(const QString &imgName1, const QString &imgName2) const override;
  QTransform transform(const QString &imgName1, const QString &imgName2) const override;
  void saveGroundTruth() override;
  void setGroundTruth(const QString &file) override;
  bool existGroundTruth() const override;
  QString projectPath() const override;

public slots:

  void addHomologusPoints(const QString &image1, QPointF pt1, const QString &image2, QPointF pt2) override;

protected:

  IProjectModel *mProjectModel;
  GroundTruth *mGroundTruth;

};


} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_MODEL_H
