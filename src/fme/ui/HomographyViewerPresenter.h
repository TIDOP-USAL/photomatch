#ifndef FME_HOMOGRAPHY_VIEWER_PRESENTER_H
#define FME_HOMOGRAPHY_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "fme/ui/mvp.h"

namespace fme
{

class IHomographyViewerView;
class IHomographyViewerModel;
class Help;


class IHomographyViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IHomographyViewerPresenter(){}
  virtual ~IHomographyViewerPresenter() {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void homography(const QString &imageLeft, const QString &imageRight) = 0;

};

class HomographyViewerPresenter
  : public IHomographyViewerPresenter
{

  Q_OBJECT

public:

  HomographyViewerPresenter(IHomographyViewerView *view,
                            IHomographyViewerModel *model);
  ~HomographyViewerPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

// IHomographyViewerPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void homography(const QString &imageLeft, const QString &imageRight) override;

private:

  IHomographyViewerView *mView;
  IHomographyViewerModel *mModel;
  std::shared_ptr<Help> mHelp;
};

} // namespace fme

#endif // FME_HOMOGRAPHY_VIEWER_PRESENTER_H
