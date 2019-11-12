#ifndef PHOTOMATCH_SETTINGS_PRESENTER_H
#define PHOTOMATCH_SETTINGS_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include <opencv2/core.hpp>

#include "mvp.h"

namespace photomatch
{

class ISettingsView;
class ISettingsModel;

/* Image preprocess */
class IAcebsfWidget;
class IClaheWidget;
class ICmbfheWidget;
class IDheWidget;
class IFaheWidget;
class IHmclaheWidget;
class ILceBsescsWidget;
class IMsrcpWidget;
class INoshpWidget;
class IPoheWidget;
class IRswheWidget;
class IWallisWidget;

/* Feature detector/extractor */
class IAgastWidget;
class IAkazeWidget;
class IBoostWidget;
class IBriefWidget;
class IBriskWidget;
class IDaisyWidget;
class IFastWidget;
class IFreakWidget;
class IGfttWidget;
class IHogWidget;
class IKazeWidget;
class ILatchWidget;
class ILucidWidget;
class IMsdWidget;
class IMserWidget;
class IOrbWidget;
class ISiftWidget;
class IStarWidget;
class ISurfWidget;

class IDescriptorMatcherWidget;

class ISettingsPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  ISettingsPresenter() {}
  virtual ~ISettingsPresenter(){}

  virtual void openPage(int page) = 0;

signals:

private slots:

  /*!
   * \brief Establece el idioma de la aplicación
   * \param[in] language
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief save
   */
  virtual void save() = 0;

  /*!
   * \brief discart
   */
  virtual void discart() = 0;
};

class SettingsPresenter
  : public ISettingsPresenter
{
  Q_OBJECT

public:

  SettingsPresenter(ISettingsView *view, ISettingsModel *model);
  ~SettingsPresenter() override;

  void openPage(int page) override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

// ISettingsPresenter interface

private slots:

  void setLanguage(const QString &language) override;
  void save() override;
  void discart() override;

protected:

  ISettingsView *mView;
  ISettingsModel *mModel;

  /* Image preprocess */

  IAcebsfWidget *mACEBSF;
  IClaheWidget *mCLAHE;
  ICmbfheWidget *mCMBFHE;
  IDheWidget *mDHE;
  IFaheWidget *mFAHE;
  IHmclaheWidget *mHMCLAHE;
  ILceBsescsWidget *mLCEBSESCS;
  IMsrcpWidget *mMSRCP;
  INoshpWidget *mNOSHP;
  IPoheWidget *mPOHE;
  IRswheWidget *mRSWHE;
  IWallisWidget *mWallis;

  /* Feature detector/extractor */

  IAgastWidget *mAgast;
  IAkazeWidget *mAkaze;
#if CV_VERSION_MAJOR >= 3
#  if CV_VERSION_MINOR > 2
  IBoostWidget *mBoost;
#  endif
#endif
  IBriefWidget *mBrief;
  IBriskWidget *mBrisk;
  IDaisyWidget *mDaisy;
  IFastWidget *mFast;
  IFreakWidget *mFreak;
  IGfttWidget *mGftt;
  IHogWidget *mHog;
  IKazeWidget *mKaze;
  ILatchWidget *mLatch;
  ILucidWidget *mLucid;
  IMsdWidget *mMsd;
  IMserWidget *mMser;
  IOrbWidget *mOrb;
#ifdef OPENCV_ENABLE_NONFREE
  ISiftWidget *mSift;
#endif
  IStarWidget *mStar;
#ifdef OPENCV_ENABLE_NONFREE
  ISurfWidget *mSurf;
#endif

  IDescriptorMatcherWidget *mMatcher;

  std::map<QString, QString> mLang;

};

} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_PRESENTER_H
