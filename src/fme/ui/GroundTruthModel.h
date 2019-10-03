#ifndef FME_GROUND_TRUTH_MODEL_H
#define FME_GROUND_TRUTH_MODEL_H

#include <memory>

#include "fme/ui/mvp.h"

namespace fme
{

class IProjectModel;

class IGroundTruthModel
  : public IModel
{

  Q_OBJECT

public:

  IGroundTruthModel(){}
  virtual ~IGroundTruthModel() override {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;

public slots:

  virtual size_t addPoint(const QString &image, const QPointF &pt) = 0;
  virtual void addCorrespondence(const QString &image1, size_t idPt1, const QString &image2, size_t idPt2) = 0;

};


class GroundTruthModel
  : public IGroundTruthModel
{

  Q_OBJECT

public:

  GroundTruthModel(IProjectModel *mProjectModel);
  ~GroundTruthModel() override {}

// IModel interface

private:

  void init() override;

// IGroundTruthModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;

public slots:

  size_t addPoint(const QString &image, const QPointF &pt) override;
  void addCorrespondence(const QString &image1, size_t idPt1, const QString &image2, size_t idPt2) override;

protected:

  IProjectModel *mProjectModel;
  std::map<QString, std::vector<QPointF>> mPoints;
  std::map<QString, std::map<QString, std::vector<std::pair<size_t, size_t>>>> mControlPointsCorrespondences;

};


} // namespace fme

#endif // FME_GROUND_TRUTH_MODEL_H
