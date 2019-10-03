#ifndef FME_CURVES_VIEWER_PRESENTER_H
#define FME_CURVES_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "fme/ui/mvp.h"

namespace fme
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

} // namespace fme

#endif // FME_CURVES_VIEWER_PRESENTER_H
