#ifndef FME_PREPROCESS_PRESENTER_H
#define FME_PREPROCESS_PRESENTER_H

#include "fme/fme_global.h"

#include <QObject>

#include "mvp.h"

class MultiProcess;

namespace fme
{

class IPreprocessView;
class IPreprocessModel;
class IProjectModel;
class ISettingsModel;

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
class IProgressDialog;

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

  virtual void setProgressDialog(IProgressDialog *progressDialog) = 0;

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

private:

  void init() override;

// IPreprocessPresenter interface

public slots:

  void setProgressDialog(IProgressDialog *progressDialog) override;

private slots:

  void run() override;
  void setCurrentPreprocess(const QString &preprocess) override;

  void onError(int code, const QString &msg);
  void onFinished();
  void onImagePreprocessed(const QString &image);

protected:

  IPreprocessView *mView;
  IPreprocessModel *mModel;
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;

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

  IProgressDialog *mProgressDialog;
};

} // namespace fme

#endif // FME_PREPROCESS_PRESENTER_H
