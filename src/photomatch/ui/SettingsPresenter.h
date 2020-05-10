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


#ifndef PHOTOMATCH_SETTINGS_PRESENTER_H
#define PHOTOMATCH_SETTINGS_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include <opencv2/core.hpp>

#include "photomatch/ui/Settings.h"

namespace photomatch
{

class SettingsView;
class SettingsModel;
class HelpDialog;

/* Image preprocess */
class AcebsfWidget;
class ClaheWidget;
class CmbfheWidget;
class DheWidget;
class FaheWidget;
class HmclaheWidget;
class LceBsescsWidget;
class MsrcpWidget;
class NoshpWidget;
class PoheWidget;
class RswheWidget;
class WallisWidget;

/* Feature detector/extractor */
class AgastWidget;
class AkazeWidget;
class BoostWidget;
class BriefWidget;
class BriskWidget;
class DaisyWidget;
class FastWidget;
class FreakWidget;
class GfttWidget;
class HogWidget;
class KazeWidget;
class LatchWidget;
class MsdWidget;
class MserWidget;
class OrbWidget;
class SiftWidget;
class StarWidget;
class SurfWidget;
class VggWidget;

class DescriptorMatcherWidget;



class SettingsPresenterImp
  : public SettingsPresenter
{
  Q_OBJECT

public:

  SettingsPresenterImp(SettingsView *view,
                       SettingsModel *model);
  ~SettingsPresenterImp() override;

public slots:

  void openViewSettings() override;
  void openQualityControlSettings() override;
  void openToolSettings() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

// SettingsPresenter interface

private slots:

  void setLanguage(const QString &language) override;
  void save() override;
  void discart() override;

protected:

  SettingsView *mView;
  SettingsModel *mModel;
  HelpDialog *mHelp;

  /* Image preprocess */

  AcebsfWidget *mACEBSF;
  ClaheWidget *mCLAHE;
  CmbfheWidget *mCMBFHE;
  DheWidget *mDHE;
  FaheWidget *mFAHE;
  HmclaheWidget *mHMCLAHE;
  LceBsescsWidget *mLCEBSESCS;
  MsrcpWidget *mMSRCP;
  NoshpWidget *mNOSHP;
  PoheWidget *mPOHE;
  RswheWidget *mRSWHE;
  WallisWidget *mWallis;

  /* Feature detector/extractor */

  AgastWidget *mAgast;
  AkazeWidget *mAkaze;
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  BoostWidget *mBoost;
#endif
  BriefWidget *mBrief;
  BriskWidget *mBrisk;
  DaisyWidget *mDaisy;
  FastWidget *mFast;
  FreakWidget *mFreak;
  GfttWidget *mGftt;
  HogWidget *mHog;
  KazeWidget *mKaze;
  LatchWidget *mLatch;
  MsdWidget *mMsd;
  MserWidget *mMser;
  OrbWidget *mOrb;
#ifdef OPENCV_ENABLE_NONFREE
  SiftWidget *mSift;
#endif
  StarWidget *mStar;
#ifdef OPENCV_ENABLE_NONFREE
  SurfWidget *mSurf;
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  VggWidget *mVgg;
#endif
  DescriptorMatcherWidget *mMatcher;

  std::map<QString, QString> mLang;

};

} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_PRESENTER_H
