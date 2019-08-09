#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>
#include <QStringList>
#include <QSize>

#include "fme/core/features/features.h"
#include "fme/core/preprocess/preprocess.h"


class QSettings;

namespace fme
{

/*----------------------------------------------------------------*/

/*!
 * \brief Settings interface
 */
class FME_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief Idioma actual
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief Establece el idioma del programa
   * \param[in] language Idioma
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Historial del proyectos recientes
   * \return Listado con los proyectos recientes
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Añade un proyecto al historial
   * \param[in] project Fichero de proyecto
   */
  virtual void addToHistory(const QString &project) = 0;

  /*!
   * \brief Borra el historial de proyectos recientes
   */
  virtual void clearHistory() = 0;

  /*!
   * \brief Tamaño máximo del historial
   * \return
   */
  virtual int historyMaxSize() const = 0;

  /*!
   * \brief Establece el tamaño máximo de elementos del historial
   * \param[in] maxSize Tamaño máximo del historial
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  virtual IAcebsf *acebsf() = 0;
  virtual const IAcebsf *acebsf() const = 0;
  virtual IClahe *clahe() = 0;
  virtual const IClahe *clahe() const = 0;
  virtual ICmbfhe *cmbfhe() = 0;
  virtual const ICmbfhe *cmbfhe() const = 0;
  virtual IDhe *dhe() = 0;
  virtual const IDhe *dhe() const = 0;
  virtual IFahe *fahe() = 0;
  virtual const IFahe *fahe() const = 0;
  virtual IHmclahe *hmclahe() = 0;
  virtual const IHmclahe *hmclahe() const = 0;
  virtual ILceBsescs *lceBsescs() = 0;
  virtual const ILceBsescs *lceBsescs() const = 0;
  virtual IMsrcp *msrcp() = 0;
  virtual const IMsrcp *msrcp() const = 0;
  virtual INoshp *noshp() = 0;
  virtual const INoshp *noshp() const = 0;
  virtual IPohe *pohe() = 0;
  virtual const IPohe *pohe() const = 0;
  virtual IRswhe *rswhe() = 0;
  virtual const IRswhe *rswhe() const = 0;
  virtual IWallis *wallis() = 0;
  virtual const IWallis *wallis() const = 0;


  virtual IAgast *agast() = 0;
  virtual const IAgast *agast() const = 0;
  virtual IAkaze *akaze() = 0;
  virtual const IAkaze *akaze() const = 0;
  virtual IBrief *brief() = 0;
  virtual const IBrief *brief() const = 0;
  virtual IBrisk *brisk() = 0;
  virtual const IBrisk *brisk() const = 0;
  virtual IDaisy *daisy() = 0;
  virtual const IDaisy *daisy() const = 0;
  virtual IFast *fast() = 0;
  virtual const IFast *fast() const = 0;
  virtual IFreak *freak() = 0;
  virtual const IFreak *freak() const = 0;
  virtual IGftt *gftt() = 0;
  virtual const IGftt *gftt() const = 0;
  virtual IHog *hog() = 0;
  virtual const IHog *hog() const = 0;
  virtual IKaze *kaze() = 0;
  virtual const IKaze *kaze() const = 0;
  virtual ILatch *latch() = 0;
  virtual const ILatch *latch() const = 0;
  virtual ILucid *lucid() = 0;
  virtual const ILucid *lucid() const = 0;
  virtual IMsd *msd() = 0;
  virtual const IMsd *msd() const = 0;
  virtual IMser *mser() = 0;
  virtual const IMser *mser() const = 0;
  virtual IOrb *orb() = 0;
  virtual const IOrb *orb() const = 0;
  virtual ISift *sift() = 0;
  virtual const ISift *sift() const = 0;
  virtual IStar *star() = 0;
  virtual const IStar *star() const = 0;
  virtual ISurf *surf() = 0;
  virtual const ISurf *surf() const = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Settings read and write interface
 */
class FME_EXPORT ISettingsRW
{

public:

  ISettingsRW() {}
  virtual ~ISettingsRW() = default;

  /*!
   * \brief read
   * \return
   */
  virtual void read(ISettings &settings) = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write(const ISettings &settings) = 0;

  virtual void writeHistory(const ISettings &settings) = 0;
};



/*----------------------------------------------------------------*/



/*!
 * \brief The Settings class
 */
class FME_EXPORT Settings
  : public ISettings
{

public:

  Settings();
  ~Settings() override;

// ISettings interface

public:

  QString language() const override;
  void setLanguage(const QString &language) override;

  QStringList history() const override;
  void addToHistory(const QString &project) override;
  void clearHistory() override;
  int historyMaxSize() const override;
  void setHistoryMaxSize(int maxSize) override;

  IAcebsf *acebsf() override;
  const IAcebsf *acebsf() const override;
  IClahe *clahe() override;
  const IClahe *clahe() const override;
  ICmbfhe *cmbfhe() override;
  const ICmbfhe *cmbfhe() const override;
  IDhe *dhe() override;
  const IDhe *dhe() const override;
  IFahe *fahe() override;
  const IFahe *fahe() const override;
  IHmclahe *hmclahe() override;
  const IHmclahe *hmclahe() const override;
  ILceBsescs *lceBsescs() override;
  const ILceBsescs *lceBsescs() const override;
  IMsrcp *msrcp() override;
  const IMsrcp *msrcp() const override;
  INoshp *noshp() override;
  const INoshp *noshp() const override;
  IPohe *pohe() override;
  const IPohe *pohe() const override;
  IRswhe *rswhe() override;
  const IRswhe *rswhe() const override;
  IWallis *wallis() override;
  const IWallis *wallis() const override;

  IAgast *agast() override;
  const IAgast *agast() const override;
  IAkaze *akaze() override;
  const IAkaze *akaze() const override;
  IBrief *brief() override;
  const IBrief *brief() const override;
  IBrisk *brisk() override;
  const IBrisk *brisk() const override;
  IDaisy *daisy() override;
  const IDaisy *daisy() const override;
  IFast *fast() override;
  const IFast *fast() const override;
  IFreak *freak() override;
  const IFreak *freak() const override;
  IGftt *gftt() override;
  const IGftt *gftt() const override;
  IHog *hog() override;
  const IHog *hog() const override;
  IKaze *kaze() override;
  const IKaze *kaze() const override;
  ILatch *latch() override;
  const ILatch *latch() const override;
  ILucid *lucid() override;
  const ILucid *lucid() const override;
  IMsd *msd() override;
  const IMsd *msd() const override;
  IMser *mser() override;
  const IMser *mser() const override;
  IOrb *orb() override;
  const IOrb *orb() const override;
  ISift *sift() override;
  const ISift *sift() const override;
  IStar *star() override;
  const IStar *star() const override;
  ISurf *surf() override;
  const ISurf *surf() const override;

  void reset() override;

protected:

  QString mLanguage;
  int mHistoyMaxSize;
  QStringList mHistory;

  IAcebsf *mAcebsf;
  IClahe *mClahe;
  ICmbfhe *mCmbfhe;
  IDhe *mDhe;
  IFahe *mFahe;
  IHmclahe *mHmclahe;
  ILceBsescs *mLceBsescs;
  IMsrcp *mMsrcp;
  INoshp *mNoshp;
  IPohe *mPohe;
  IRswhe *mRswhe;
  IWallis *mWallis;

  IAgast *mAgast;
  IAkaze *mAkaze;
  IBrief *mBrief;
  IBrisk *mBrisk;
  IDaisy *mDaisy;
  IFast *mFast;
  IFreak *mFreak;
  IGftt *mGftt;
  IHog *mHog;
  IKaze *mKaze;
  ILatch *mLatch;
  ILucid *mLucid;
  IMsd *mMsd;
  IMser *mMser;
  IOrb *mOrb;
  ISift *mSift;
  IStar *mStar;
  ISurf *mSurf;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The SettingsRW class
 */
class FME_EXPORT SettingsRW
  : public ISettingsRW
{

public:

  explicit SettingsRW();
  ~SettingsRW() override;

// ISettingsRW interface

public:

  void read(ISettings &settings) override;
  void write(const ISettings &settings) override;
  void writeHistory(const ISettings &settings) override;

protected:

  QSettings *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_H
