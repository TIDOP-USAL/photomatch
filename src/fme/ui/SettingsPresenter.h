#ifndef FME_SETTINGS_PRESENTER_H
#define FME_SETTINGS_PRESENTER_H

#include "fme/fme_global.h"

#include <QObject>

#include "mvp.h"

namespace fme
{

class ISettingsView;
class ISettingsModel;

/* Image preprocess */
class IAcebsfWidget;
class ICLAHEWidget;
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

class ISettingsPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  ISettingsPresenter() {}
  virtual ~ISettingsPresenter(){}

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

  //IAcebsfWidget *mACEBS;
  //ICLAHEWidget *mCLAHE;
  //ICmbfheWidget *mCMBFHE;
  //IDheWidget *mDHE;
  IFaheWidget *mFAHE;
  //IHmclaheWidget *mHMCLAHE;
  //ILceBsescsWidget *mLCEBSESCS;
  //IMsrcpWidget *mMSRCP;
  //INoshpWidget *mNOSHP;
  //IPoheWidget *mPOHE;
  //IRswheWidget *mRSWHE;
  //IWallisWidget *mWallis;

  /* Feature detector/extractor */

  IAgastWidget *mAgast;
  IAkazeWidget *mAkaze;
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
  ISiftWidget *mSift;
  IStarWidget *mStar;
  ISurfWidget *mSurf;

  std::map<QString, QString> mLang;

};

} // namespace fme

#endif // FME_SETTINGS_PRESENTER_H
