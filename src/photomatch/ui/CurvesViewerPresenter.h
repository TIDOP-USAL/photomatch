#ifndef PHOTOMATCH_CURVES_VIEWER_PRESENTER_H
#define PHOTOMATCH_CURVES_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ICurvesViewerView;
class ICurvesViewerModel;
class Help;

class ICurvesViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  ICurvesViewerPresenter() : IPresenter() {}
  virtual ~ICurvesViewerPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void drawCurve(const QString &session, const QString &detector, const QString &descriptor) = 0;
  virtual void deleteCurve(const QString &session) = 0;
};

class CurvesViewerPresenter
  : public ICurvesViewerPresenter
{

  Q_OBJECT

public:

  CurvesViewerPresenter(ICurvesViewerView *view,
                        ICurvesViewerModel *model);
  ~CurvesViewerPresenter() override {}

//ICurvesViewerPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void drawCurve(const QString &session, const QString &detector, const QString &descriptor) override;
  void deleteCurve(const QString &session) override;


// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

private:

  ICurvesViewerView *mView;
  ICurvesViewerModel *mModel;
  std::shared_ptr<Help> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_PRESENTER_H
