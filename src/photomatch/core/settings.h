#ifndef PHOTOMATCH_SETTINGS_H
#define PHOTOMATCH_SETTINGS_H

#include "photomatch/photomatch_global.h"

#include <QString>
#include <QStringList>
#include <QSize>

class QSettings;
class QPen;
class QBrush;

namespace photomatch
{

class IAcebsf;
class IClahe;
class ICmbfhe;
class IDecolor;
class IDhe;
class IFahe;
class IHmclahe;
class ILceBsescs;
class IMsrcp;
class INoshp;
class IPohe;
class IRswhe;
class IWallis;
class IAgast;
class IAkaze;
class IBoost;
class IBrief;
class IBrisk;
class IDaisy;
class IFast;
class IFreak;
class IGftt;
class IHog;
class IKaze;
class ILatch;
class ILucid;
class IMsd;
class IMser;
class IOrb;
class ISift;
class IStar;
class ISurf;
class IVgg;
class IFlannMatcher;
class IBruteForceMatcher;
class IRobustMatcherRefinement;

/*----------------------------------------------------------------*/

/*!
 * \brief Settings interface
 */
class PHOTOMATCH_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief Current language
   * \return Current language
   */
  virtual QString language() const = 0;

  /*!
   * \brief Set the language
   * \param[in] language GUI language
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Recent history projects
   * \return List of recent projects
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Add a project to the history
   * \param[in] project Project path
   */
  virtual void addToHistory(const QString &project) = 0;

  /*!
   * \brief Clear the history of recent projects
   */
  virtual void clearHistory() = 0;

  /*!
   * \brief Maximum history size
   * \return Maximum history size
   */
  virtual int historyMaxSize() const = 0;

  /*!
   * \brief Set the size number of history items
   * \param[in] maxSize History size
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  /*!
   * \brief Image viewer Background color
   * \return Hex value
   */
  virtual QString imageViewerBGcolor() const = 0;

  /*!
   * \brief Set Image Viewer background color
   * \param bgColor Hex value
   */
  virtual void setImageViewerBGcolor(const QString &bgColor) = 0;

  /*!
   * \brief Keypoints format
   * \return "Binary", "XML" or "YML"
   */
  virtual QString keypointsFormat() const = 0;

  /*!
   * \brief Set Keypoints format
   * \param[in] format Supported formats: "Binary", "XML" or "YML"
   */
  virtual void setKeypointsFormat(const QString &format) = 0;

  /*!
   * \brief Matches format
   * \return "Binary", "XML" or "YML"
   */
  virtual QString matchesFormat() const = 0;

  /*!
   * \brief Set Matches format
   * \param[in] format Supported formats: "Binary", "XML" or "YML"
   */
  virtual void setMatchesFormat(const QString &format) = 0;

  virtual bool useCuda() const = 0;
  virtual void setUseCuda(bool active) = 0;

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
  virtual IBoost *boost() = 0;
  virtual const IBoost *boost() const = 0;
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
  virtual IVgg *vgg() = 0;
  virtual const IVgg *vgg() const = 0;

  virtual QString matchMethod() const = 0;
  virtual void setMatchMethod(const QString &matchingMethod) = 0;
  virtual IFlannMatcher *flannMatcher() = 0;
  virtual const IFlannMatcher *flannMatcher() const = 0;
  virtual IBruteForceMatcher *bruteForceMatcher() = 0;
  virtual const IBruteForceMatcher *bruteForceMatcher() const = 0;
  virtual IRobustMatcherRefinement *robustMatcherRefinement() = 0;
  virtual const IRobustMatcherRefinement *robustMatcherRefinement() const = 0;

//  /// Styles
//  virtual QPen *penKeypoints() = 0;
//  virtual const QPen *penKeypoints() const = 0;
//  virtual int sizeKeypoints() const = 0;
//  virtual QPen *penMatchesPoints() = 0;
//  virtual const QPen *penMatchesPoints() const = 0;
//  virtual int sizeMatchesPoints() const = 0;
//  virtual QPen *penMatchesLines() = 0;
//  virtual const QPen *penMatchesLines() const = 0;

  virtual QString keypointsViewerBGColor() const = 0;
  virtual void setKeypointsViewerBGColor(const QString &color) = 0;
  virtual int keypointsViewerMarkerType() const = 0;
  virtual void setKeypointsViewerMarkerType(int type) = 0;
  virtual int keypointsViewerMarkerSize() const = 0;
  virtual void setKeypointsViewerMarkerSize(int size) = 0;
  virtual int keypointsViewerMarkerWidth() const = 0;
  virtual void setKeypointsViewerMarkerWidth(int width) = 0;
  virtual QString keypointsViewerMarkerColor() const = 0;
  virtual void setKeypointsViewerMarkerColor(const QString &color) = 0;

  virtual QString matchesViewerBGColor() const = 0;
  virtual void setMatchesViewerBGColor(const QString &color) = 0;
  virtual int matchesViewerMarkerType() const = 0;
  virtual void setMatchesViewerMarkerType(int type) = 0;
  virtual int matchesViewerMarkerSize() const = 0;
  virtual void setMatchesViewerMarkerSize(int size) = 0;
  virtual int matchesViewerMarkerWidth() const = 0;
  virtual void setMatchesViewerMarkerWidth(int width) = 0;
  virtual QString matchesViewerMarkerColor() const = 0;
  virtual void setMatchesViewerMarkerColor(const QString &color) = 0;
  virtual QString matchesViewerLineColor() const = 0;
  virtual void setMatchesViewerLineColor(const QString &color) = 0;
  virtual int matchesViewerLineWidth() const = 0;
  virtual void setMatchesViewerLineWidth(int width) = 0;

  virtual QString groundTruthEditorBGColor() const = 0;
  virtual void setGroundTruthEditorBGColor(const QString &bgColor) = 0;
  virtual int groundTruthEditorMarkerSize() const = 0;
  virtual void setGroundTruthEditorMarkerSize(int size) = 0;
  virtual int groundTruthEditorMarkerWidth() const = 0;
  virtual void setGroundTruthEditorMarkerWidth(int width) = 0;
  virtual QString groundTruthEditorMarkerColor() const = 0;
  virtual void setGroundTruthEditorMarkerColor(const QString &color) = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Settings read and write interface
 */
class PHOTOMATCH_EXPORT ISettingsRW
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
class PHOTOMATCH_EXPORT Settings
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

  QString imageViewerBGcolor() const override;
  void setImageViewerBGcolor(const QString &bgColor) override;

  QString keypointsFormat() const override;
  void setKeypointsFormat(const QString &format) override;
  QString matchesFormat() const override;
  void setMatchesFormat(const QString &format) override;

  bool useCuda() const override;
  void setUseCuda(bool active) override;

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
  IBoost *boost() override;
  const IBoost *boost() const override;
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
  virtual IVgg *vgg() override;
  virtual const IVgg *vgg() const override;

  QString matchMethod() const override;
  void setMatchMethod(const QString &matchingMethod) override;
  IFlannMatcher *flannMatcher() override;
  const IFlannMatcher *flannMatcher() const override;
  IBruteForceMatcher *bruteForceMatcher() override;
  const IBruteForceMatcher *bruteForceMatcher() const override;
  IRobustMatcherRefinement *robustMatcherRefinement() override;
  const IRobustMatcherRefinement *robustMatcherRefinement() const override;

//  QPen *penKeypoints() override;
//  const QPen *penKeypoints() const override;
//  int sizeKeypoints() const override;
//  QPen *penMatchesPoints() override;
//  const QPen *penMatchesPoints() const override;
//  int sizeMatchesPoints() const override;
//  QPen *penMatchesLines() override;
//  const QPen *penMatchesLines() const override;


  QString keypointsViewerBGColor() const override;
  void setKeypointsViewerBGColor(const QString &color) override;
  int keypointsViewerMarkerType() const override;
  void setKeypointsViewerMarkerType(int type) override;
  int keypointsViewerMarkerSize() const override;
  void setKeypointsViewerMarkerSize(int size) override;
  int keypointsViewerMarkerWidth() const override;
  void setKeypointsViewerMarkerWidth(int width) override;
  QString keypointsViewerMarkerColor() const override;
  void setKeypointsViewerMarkerColor(const QString &color) override;

  QString matchesViewerBGColor() const override;
  void setMatchesViewerBGColor(const QString &color) override;
  int matchesViewerMarkerType() const override;
  void setMatchesViewerMarkerType(int type) override;
  int matchesViewerMarkerSize() const override;
  void setMatchesViewerMarkerSize(int size) override;
  int matchesViewerMarkerWidth() const override;
  void setMatchesViewerMarkerWidth(int width) override;
  QString matchesViewerMarkerColor() const override;
  void setMatchesViewerMarkerColor(const QString &color) override;
  QString matchesViewerLineColor() const override;
  void setMatchesViewerLineColor(const QString &color) override;
  int matchesViewerLineWidth() const override;
  void setMatchesViewerLineWidth(int width) override;

  QString groundTruthEditorBGColor() const override;
  void setGroundTruthEditorBGColor(const QString &bgColor) override;
  int groundTruthEditorMarkerSize() const override;
  void setGroundTruthEditorMarkerSize(int size) override;
  int groundTruthEditorMarkerWidth() const override;
  void setGroundTruthEditorMarkerWidth(int width) override;
  QString groundTruthEditorMarkerColor() const override;
  void setGroundTruthEditorMarkerColor(const QString &color) override;

  void reset() override;

protected:

  QString mLanguage;
  int mHistoyMaxSize;
  QStringList mHistory;

  QString mImageViewerBGcolor;

  QString mKeypointsFormat;
  QString mMatchesFormat;
  bool mUseCuda;

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
  IBoost *mBoost;
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
  IVgg *mVgg;

  QString mMatchMethod;
  IFlannMatcher *mFlannMatcher;
  IBruteForceMatcher *mBruteForceMatcher;
  IRobustMatcherRefinement *mRobustMatcherRefinement;

  QString mKeypointViewerBGColor;
  int mKeypointsViewerMarkerType;
  int mKeypointViewerMarkerSize;
  int mKeypointViewerMarkerWidth;
  QString mKeypointViewerMarkerColor;

  QString mMatchesViewerBGColor;
  int mMatchesViewerMarkerType;
  QString mMatchesViewerMarkerColor;
  int mMatchesViewerMarkerSize;
  int mMatchesViewerMarkerWidth;
  QString mMatchesViewerLineColor;
  int mMatchesViewerLineWidth;

  QString mGroundTruthEditorBGColor;
  QString mGroundTruthEditorMarkerColor;
  int mGroundTruthEditorMarkerSize;
  int mGroundTruthEditorMarkerWidth;

//  QPen *mPenKeypoints;
//  int mSizeKeypoints;
//  QPen *mPenMatchesPoints;
//  int mSizeMatchesPoints;
//  QPen *mPenMatchesLines;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The SettingsRW class
 */
class PHOTOMATCH_EXPORT SettingsRW
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

} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_H
