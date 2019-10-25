#ifndef FME_GROUND_TRUTH_MODEL_H
#define FME_GROUND_TRUTH_MODEL_H

#include <memory>

#include "fme/ui/mvp.h"

namespace fme
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

public slots:

  void addHomologusPoints(const QString &image1, QPointF pt1, const QString &image2, QPointF pt2) override;

protected:

  IProjectModel *mProjectModel;
  GroundTruth *mGroundTruth;

};


} // namespace fme

#endif // FME_GROUND_TRUTH_MODEL_H
