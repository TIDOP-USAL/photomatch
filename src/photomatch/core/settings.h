/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/

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

class Acebsf;
class Clahe;
class Cmbfhe;
class Decolor;
class Dhe;
class Fahe;
class Hmclahe;
class LceBsescs;
class Msrcp;
class Noshp;
class Pohe;
class Rswhe;
class Wallis;
class Agast;
class Akaze;
class Boost;
class Brief;
class Brisk;
class Daisy;
class Fast;
class Freak;
class Gftt;
class Hog;
class Kaze;
class Latch;
class Lucid;
class Msd;
class Mser;
class Orb;
class Sift;
class Star;
class Surf;
class Vgg;
class FlannMatcher;
class BruteForceMatcher;
class RobustMatcher;
class Gms;

/*----------------------------------------------------------------*/

/*!
 * \brief Settings interface
 */
class PHOTOMATCH_EXPORT Settings
{

public:

  Settings() {}
  virtual ~Settings() = default;

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

  virtual Acebsf *acebsf() = 0;
  virtual const Acebsf *acebsf() const = 0;
  virtual Clahe *clahe() = 0;
  virtual const Clahe *clahe() const = 0;
  virtual Cmbfhe *cmbfhe() = 0;
  virtual const Cmbfhe *cmbfhe() const = 0;
  virtual Dhe *dhe() = 0;
  virtual const Dhe *dhe() const = 0;
  virtual Fahe *fahe() = 0;
  virtual const Fahe *fahe() const = 0;
  virtual Hmclahe *hmclahe() = 0;
  virtual const Hmclahe *hmclahe() const = 0;
  virtual LceBsescs *lceBsescs() = 0;
  virtual const LceBsescs *lceBsescs() const = 0;
  virtual Msrcp *msrcp() = 0;
  virtual const Msrcp *msrcp() const = 0;
  virtual Noshp *noshp() = 0;
  virtual const Noshp *noshp() const = 0;
  virtual Pohe *pohe() = 0;
  virtual const Pohe *pohe() const = 0;
  virtual Rswhe *rswhe() = 0;
  virtual const Rswhe *rswhe() const = 0;
  virtual Wallis *wallis() = 0;
  virtual const Wallis *wallis() const = 0;

  virtual Agast *agast() = 0;
  virtual const Agast *agast() const = 0;
  virtual Akaze *akaze() = 0;
  virtual const Akaze *akaze() const = 0;
  virtual Boost *boost() = 0;
  virtual const Boost *boost() const = 0;
  virtual Brief *brief() = 0;
  virtual const Brief *brief() const = 0;
  virtual Brisk *brisk() = 0;
  virtual const Brisk *brisk() const = 0;
  virtual Daisy *daisy() = 0;
  virtual const Daisy *daisy() const = 0;
  virtual Fast *fast() = 0;
  virtual const Fast *fast() const = 0;
  virtual Freak *freak() = 0;
  virtual const Freak *freak() const = 0;
  virtual Gftt *gftt() = 0;
  virtual const Gftt *gftt() const = 0;
  virtual Hog *hog() = 0;
  virtual const Hog *hog() const = 0;
  virtual Kaze *kaze() = 0;
  virtual const Kaze *kaze() const = 0;
  virtual Latch *latch() = 0;
  virtual const Latch *latch() const = 0;
  virtual Lucid *lucid() = 0;
  virtual const Lucid *lucid() const = 0;
  virtual Msd *msd() = 0;
  virtual const Msd *msd() const = 0;
  virtual Mser *mser() = 0;
  virtual const Mser *mser() const = 0;
  virtual Orb *orb() = 0;
  virtual const Orb *orb() const = 0;
  virtual Sift *sift() = 0;
  virtual const Sift *sift() const = 0;
  virtual Star *star() = 0;
  virtual const Star *star() const = 0;
  virtual Surf *surf() = 0;
  virtual const Surf *surf() const = 0;
  virtual Vgg *vgg() = 0;
  virtual const Vgg *vgg() const = 0;

  virtual QString matchMethod() const = 0;
  virtual void setMatchMethod(const QString &matchingMethod) = 0;
  virtual QString matchStrategy() const = 0;
  virtual void setMatchStrategy(const QString &matchingStrategy) = 0;
  virtual FlannMatcher *flannMatcher() = 0;
  virtual const FlannMatcher *flannMatcher() const = 0;
  virtual BruteForceMatcher *bruteForceMatcher() = 0;
  virtual const BruteForceMatcher *bruteForceMatcher() const = 0;
  virtual RobustMatcher *robustMatcher() = 0;
  virtual const RobustMatcher *robustMatcher() const = 0;
  virtual Gms *gms() = 0;
  virtual const Gms *gms() const = 0;

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
  virtual int keypointsViewerSelectMarkerWidth() const = 0;
  virtual void setKeypointsViewerSelectMarkerWidth(int width) = 0;
  virtual QString keypointsViewerSelectMarkerColor() const = 0;
  virtual void setKeypointsViewerSelectMarkerColor(const QString &color) = 0;

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
  virtual int matchesViewerSelectMarkerWidth() const = 0;
  virtual void setMatchesViewerSelectMarkerWidth(int width) = 0;
  virtual QString matchesViewerSelectMarkerColor() const = 0;
  virtual void setMatchesViewerSelectMarkerColor(const QString &color) = 0;
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
  virtual int groundTruthEditorSelectMarkerWidth() const = 0;
  virtual void setGroundTruthEditorSelectMarkerWidth(int width) = 0;
  virtual QString groundTruthEditorSelectMarkerColor() const = 0;
  virtual void setGroundTruthEditorSelectMarkerColor(const QString &color) = 0;
  virtual QString groundTruthEditorMatrixAdjust() const = 0;
  virtual void setGroundTruthEditorMatrixAdjust(const QString &matrix) = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Settings read and write interface
 */
class PHOTOMATCH_EXPORT SettingsController
{

public:

  SettingsController() {}
  virtual ~SettingsController() = default;

  /*!
   * \brief read
   * \return
   */
  virtual void read(Settings &settings) = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write(const Settings &settings) = 0;

  virtual void writeHistory(const Settings &settings) = 0;
};



/*----------------------------------------------------------------*/



/*!
 * \brief The Settings class
 */
class PHOTOMATCH_EXPORT SettingsImp
  : public Settings
{

public:

  SettingsImp();
  ~SettingsImp() override;

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

  Acebsf *acebsf() override;
  const Acebsf *acebsf() const override;
  Clahe *clahe() override;
  const Clahe *clahe() const override;
  Cmbfhe *cmbfhe() override;
  const Cmbfhe *cmbfhe() const override;
  Dhe *dhe() override;
  const Dhe *dhe() const override;
  Fahe *fahe() override;
  const Fahe *fahe() const override;
  Hmclahe *hmclahe() override;
  const Hmclahe *hmclahe() const override;
  LceBsescs *lceBsescs() override;
  const LceBsescs *lceBsescs() const override;
  Msrcp *msrcp() override;
  const Msrcp *msrcp() const override;
  Noshp *noshp() override;
  const Noshp *noshp() const override;
  Pohe *pohe() override;
  const Pohe *pohe() const override;
  Rswhe *rswhe() override;
  const Rswhe *rswhe() const override;
  Wallis *wallis() override;
  const Wallis *wallis() const override;

  Agast *agast() override;
  const Agast *agast() const override;
  Akaze *akaze() override;
  const Akaze *akaze() const override;
  Boost *boost() override;
  const Boost *boost() const override;
  Brief *brief() override;
  const Brief *brief() const override;
  Brisk *brisk() override;
  const Brisk *brisk() const override;
  Daisy *daisy() override;
  const Daisy *daisy() const override;
  Fast *fast() override;
  const Fast *fast() const override;
  Freak *freak() override;
  const Freak *freak() const override;
  Gftt *gftt() override;
  const Gftt *gftt() const override;
  Hog *hog() override;
  const Hog *hog() const override;
  Kaze *kaze() override;
  const Kaze *kaze() const override;
  Latch *latch() override;
  const Latch *latch() const override;
  Lucid *lucid() override;
  const Lucid *lucid() const override;
  Msd *msd() override;
  const Msd *msd() const override;
  Mser *mser() override;
  const Mser *mser() const override;
  Orb *orb() override;
  const Orb *orb() const override;
  Sift *sift() override;
  const Sift *sift() const override;
  Star *star() override;
  const Star *star() const override;
  Surf *surf() override;
  const Surf *surf() const override;
  Vgg *vgg() override;
  const Vgg *vgg() const override;

  QString matchMethod() const override;
  void setMatchMethod(const QString &matchingMethod) override;
  QString matchStrategy() const override;
  void setMatchStrategy(const QString &matchingStrategy) override;
  FlannMatcher *flannMatcher() override;
  const FlannMatcher *flannMatcher() const override;
  BruteForceMatcher *bruteForceMatcher() override;
  const BruteForceMatcher *bruteForceMatcher() const override;
  RobustMatcher *robustMatcher() override;
  const RobustMatcher *robustMatcher() const override;
  Gms *gms() override;
  const Gms *gms() const override;

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
  int keypointsViewerSelectMarkerWidth() const override;
  void setKeypointsViewerSelectMarkerWidth(int width) override;
  QString keypointsViewerSelectMarkerColor() const override;
  void setKeypointsViewerSelectMarkerColor(const QString &color) override;

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
  int matchesViewerSelectMarkerWidth() const override;
  void setMatchesViewerSelectMarkerWidth(int width) override;
  QString matchesViewerSelectMarkerColor() const override;
  void setMatchesViewerSelectMarkerColor(const QString &color) override;
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
  int groundTruthEditorSelectMarkerWidth() const override;
  void setGroundTruthEditorSelectMarkerWidth(int width) override;
  QString groundTruthEditorSelectMarkerColor() const override;
  void setGroundTruthEditorSelectMarkerColor(const QString &color) override;
  QString groundTruthEditorMatrixAdjust() const override;
  void setGroundTruthEditorMatrixAdjust(const QString &matrix) override;

  void reset() override;

protected:

  QString mLanguage;
  int mHistoyMaxSize;
  QStringList mHistory;

  QString mImageViewerBGcolor;

  QString mKeypointsFormat;
  QString mMatchesFormat;
  bool mUseCuda;

  Acebsf *mAcebsf;
  Clahe *mClahe;
  Cmbfhe *mCmbfhe;
  Dhe *mDhe;
  Fahe *mFahe;
  Hmclahe *mHmclahe;
  LceBsescs *mLceBsescs;
  Msrcp *mMsrcp;
  Noshp *mNoshp;
  Pohe *mPohe;
  Rswhe *mRswhe;
  Wallis *mWallis;

  Agast *mAgast;
  Akaze *mAkaze;
  Boost *mBoost;
  Brief *mBrief;
  Brisk *mBrisk;
  Daisy *mDaisy;
  Fast *mFast;
  Freak *mFreak;
  Gftt *mGftt;
  Hog *mHog;
  Kaze *mKaze;
  Latch *mLatch;
  Lucid *mLucid;
  Msd *mMsd;
  Mser *mMser;
  Orb *mOrb;
  Sift *mSift;
  Star *mStar;
  Surf *mSurf;
  Vgg *mVgg;

  QString mMatchMethod;
  QString mMatchStrategy;
  FlannMatcher *mFlannMatcher;
  BruteForceMatcher *mBruteForceMatcher;
  RobustMatcher *mRobustMatcher;
  Gms *mGms;

  QString mKeypointViewerBGColor;
  int mKeypointsViewerMarkerType;
  int mKeypointViewerMarkerSize;
  int mKeypointViewerMarkerWidth;
  QString mKeypointViewerMarkerColor;
  int mKeypointViewerSelectMarkerWidth;
  QString mKeypointViewerSelectMarkerColor;

  QString mMatchesViewerBGColor;
  int mMatchesViewerMarkerType;
  QString mMatchesViewerMarkerColor;
  int mMatchesViewerMarkerSize;
  int mMatchesViewerMarkerWidth;
  int mMatchesViewerSelectMarkerWidth;
  QString mMatchesViewerSelectMarkerColor;
  QString mMatchesViewerLineColor;
  int mMatchesViewerLineWidth;

  QString mGroundTruthEditorBGColor;
  QString mGroundTruthEditorMarkerColor;
  int mGroundTruthEditorMarkerSize;
  int mGroundTruthEditorMarkerWidth;
  int mGroundTruthEditorSelectMarkerWidth;
  QString mGroundTruthEditorSelectMarkerColor;
  QString mGroundTruthEditorMatrixAdjust;

};


/*----------------------------------------------------------------*/


/*!
 * \brief The SettingsRW class
 */
class PHOTOMATCH_EXPORT SettingsControllerImp
  : public SettingsController
{

public:

  explicit SettingsControllerImp();
  ~SettingsControllerImp() override;

// ISettingsRW interface

public:

  void read(Settings &settings) override;
  void write(const Settings &settings) override;
  void writeHistory(const Settings &settings) override;

protected:

  QSettings *mSettingsController;

};

} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_H
