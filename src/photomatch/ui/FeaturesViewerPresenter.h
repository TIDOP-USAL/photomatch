#ifndef PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H
#define PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IFeaturesViewerView;
class IFeaturesViewerModel;
class ISettingsModel;
class HelpDialog;


class IFeaturesViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IFeaturesViewerPresenter() {}
  virtual ~IFeaturesViewerPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;
  virtual void setImageActive(const QString &image) = 0;

protected slots:

  virtual void loadKeypoints(const QString &image) = 0;

};

class FeaturesViewerPresenter
  : public IFeaturesViewerPresenter
{

  Q_OBJECT

public:

  FeaturesViewerPresenter(IFeaturesViewerView *view,
                          IFeaturesViewerModel *model,
                          ISettingsModel *settingsModel);
  ~FeaturesViewerPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IFeaturesViewerPresenter interface

public slots:

  void setSession(const QString &session) override;
  void setImageActive(const QString &image) override;

protected slots:

  void loadKeypoints(const QString &image) override;

private:

  IFeaturesViewerView *mView;
  IFeaturesViewerModel *mModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H
