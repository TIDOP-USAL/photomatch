#ifndef PHOTOMATCH_PREPROCESS_PRESENTER_H
#define PHOTOMATCH_PREPROCESS_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include "mvp.h"

class MultiProcess;

namespace photomatch
{

class IPreprocessView;
class IPreprocessModel;
class IProjectModel;
class ISettingsModel;
class HelpDialog;

class AcebsfWidget;
class ClaheWidget;
class CmbfheWidget;
class DecolorWidget;
class DheWidget;
class FaheWidget;
class HmclaheWidget;
class LceBsescsWidget;
class MsrcpWidget;
class NoshpWidget;
class PoheWidget;
class RswheWidget;
class WallisWidget;
class ProgressHandler;

class IPreprocessPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IPreprocessPresenter() {}
  virtual ~IPreprocessPresenter(){}

signals:

  void running();
  void imagePreprocessed(QString);
  void finished();

public slots:

  virtual void setProgressHandler(ProgressHandler *progressHandler) = 0;
  virtual void cancel() = 0;

private slots:

  virtual void run() = 0;
  virtual void setCurrentPreprocess(const QString &preprocess) = 0;

};


class PreprocessPresenter
  : public IPreprocessPresenter
{
  Q_OBJECT

public:

  PreprocessPresenter(IPreprocessView *view,
                      IPreprocessModel *model,
                      IProjectModel *projectModel,
                      ISettingsModel *settingsModel);
  ~PreprocessPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IPreprocessPresenter interface

public slots:

  void setProgressHandler(ProgressHandler *progressHandler) override;
  void cancel() override;

private slots:

  void run() override;
  void setCurrentPreprocess(const QString &preprocess) override;

  void onError(int code, const QString &msg);
  void onFinished();
  void onImagePreprocessed(const QString &image);

protected:

  IPreprocessView *mView;
  IPreprocessModel *mModel;  /// Por ahora es una clase vacia
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;

  AcebsfWidget *mACEBSF;
  ClaheWidget *mCLAHE;
  CmbfheWidget *mCMBFHE;
  DecolorWidget *mDecolor;
  DheWidget *mDHE;
  FaheWidget *mFAHE;
  HmclaheWidget *mHMCLAHE;
  LceBsescsWidget *mLCEBSESCS;
  MsrcpWidget *mMSRCP;
  NoshpWidget *mNOSHP;
  PoheWidget *mPOHE;
  RswheWidget *mRSWHE;
  WallisWidget *mWallis;

  MultiProcess *mMultiProcess;

  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_PREPROCESS_PRESENTER_H
