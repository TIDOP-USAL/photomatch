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

class IAcebsfWidget;
class IClaheWidget;
class ICmbfheWidget;
class IDecolorWidget;
class IDheWidget;
class IFaheWidget;
class IHmclaheWidget;
class ILceBsescsWidget;
class IMsrcpWidget;
class INoshpWidget;
class IPoheWidget;
class IRswheWidget;
class IWallisWidget;
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

  IAcebsfWidget *mACEBSF;
  IClaheWidget *mCLAHE;
  ICmbfheWidget *mCMBFHE;
  IDecolorWidget *mDecolor;
  IDheWidget *mDHE;
  IFaheWidget *mFAHE;
  IHmclaheWidget *mHMCLAHE;
  ILceBsescsWidget *mLCEBSESCS;
  IMsrcpWidget *mMSRCP;
  INoshpWidget *mNOSHP;
  IPoheWidget *mPOHE;
  IRswheWidget *mRSWHE;
  IWallisWidget *mWallis;

  MultiProcess *mMultiProcess;

  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_PREPROCESS_PRESENTER_H
