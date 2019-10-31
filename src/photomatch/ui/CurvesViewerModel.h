#ifndef PHOTOMATCH_CURVES_VIEWER_MODEL_H
#define PHOTOMATCH_CURVES_VIEWER_MODEL_H

#include <memory>

#include <QPointF>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class ICurvesViewerModel
  : public IModel
{

  Q_OBJECT

public:

  ICurvesViewerModel(){}
  virtual ~ICurvesViewerModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const = 0;
  virtual double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const = 0;

};


class CurvesViewerModel
  : public ICurvesViewerModel
{

  Q_OBJECT

public:

  CurvesViewerModel(IProjectModel *projectModel);
  virtual ~CurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
};




class ROCCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  ROCCurvesViewerModel(IProjectModel *projectModel);
  ~ROCCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;
};



class PRCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  PRCurvesViewerModel(IProjectModel *projectModel);
  ~PRCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;

};


class DETCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  DETCurvesViewerModel(IProjectModel *projectModel);
  ~DETCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;
};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_MODEL_H
