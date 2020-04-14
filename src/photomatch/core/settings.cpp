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


#include "settings.h"

#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/boost.h"
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/vgg.h"
#include "photomatch/core/features/matcher.h"

#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/preprocess/clahe.h"
#include "photomatch/core/preprocess/cmbfhe.h"
#include "photomatch/core/preprocess/dhe.h"
#include "photomatch/core/preprocess/fahe.h"
#include "photomatch/core/preprocess/hmclahe.h"
#include "photomatch/core/preprocess/lce_bsescs.h"
#include "photomatch/core/preprocess/msrcp.h"
#include "photomatch/core/preprocess/noshp.h"
#include "photomatch/core/preprocess/pohe.h"
#include "photomatch/core/preprocess/rswhe.h"
#include "photomatch/core/preprocess/wallis.h"

#include <QSettings>
#include <QLocale>
#include <QFileInfo>
#include <QPen>

#include <memory>

namespace photomatch
{


SettingsImp::SettingsImp()
  : Settings(),
    mHistoyMaxSize(10),
    mImageViewerBGcolor("#dcdcdc"),
    mKeypointsFormat("XML"),
    mMatchesFormat("XML"),
    mUseCuda(false),
    mAcebsf(new AcebsfProperties),
    mClahe(new ClaheProperties),
    mCmbfhe(new CmbfheProperties),
    mDhe(new DheProperties),
    mFahe(new FaheProperties),
    mHmclahe(new HmclaheProperties),
    mLceBsescs(new LceBsescsProperties),
    mMsrcp(new MsrcpProperties),
    mNoshp(new NoshpProperties),
    mPohe(new PoheProperties),
    mRswhe(new RswheProperties),
    mWallis(new WallisProperties),
    mAgast(new AgastProperties),
    mAkaze(new AkazeProperties),
    mBoost(new BoostProperties),
    mBrief(new BriefProperties),
    mBrisk(new BriskProperties),
    mDaisy(new DaisyProperties),
    mFast(new FastProperties),
    mFreak(new FreakProperties),
    mGftt(new GfttProperties),
    mHog(new HogProperties),
    mKaze(new KazeProperties),
    mLatch(new LatchProperties),
    mLucid(new LucidProperties),
    mMsd(new MsdProperties),
    mMser(new MserProperties),
    mOrb(new OrbProperties),
    mSift(new SiftProperties),
    mStar(new StarProperties),
    mSurf(new SurfProperties),
    mVgg(new VggProperties),
    mMatchMethod("Flann Based Matching"),
    mMatchStrategy("Robust Matcher"),
    mFlannMatcher(new FlannMatcherProperties),
    mBruteForceMatcher(new BruteForceMatcherProperties),
    mRobustMatcher(new RobustMatchingProperties),
    mGms(new GmsProperties),
    mKeypointViewerBGColor("#dcdcdc"),
    mKeypointsViewerMarkerType(0),
    mKeypointViewerMarkerSize(20),
    mKeypointViewerMarkerWidth(2),
    mKeypointViewerMarkerColor("#00aa00"),
    mKeypointViewerSelectMarkerWidth(2),
    mKeypointViewerSelectMarkerColor("#e5097e"),
    mMatchesViewerBGColor("#dcdcdc"),
    mMatchesViewerMarkerType(1),
    mMatchesViewerMarkerColor("#00aa00"),
    mMatchesViewerMarkerSize(20),
    mMatchesViewerMarkerWidth(2),
    mMatchesViewerSelectMarkerWidth(2),
    mMatchesViewerSelectMarkerColor("#e5097e"),
    mMatchesViewerLineColor("#0000ff"),
    mMatchesViewerLineWidth(2),
    mGroundTruthEditorBGColor("#dcdcdc"),
    mGroundTruthEditorMarkerColor("#00aa00"),
    mGroundTruthEditorMarkerSize(20),
    mGroundTruthEditorMarkerWidth(2),
    mGroundTruthEditorSelectMarkerWidth(2),
    mGroundTruthEditorSelectMarkerColor("#e5097e"),
    mGroundTruthEditorMatrixAdjust("Fundamental Matrix")
{

  reset();
}

SettingsImp::~SettingsImp()
{
  if (mAcebsf){
    delete mAcebsf;
    mAcebsf = nullptr;
  }

  if (mClahe){
    delete mClahe;
    mClahe = nullptr;
  }

  if (mCmbfhe){
    delete mCmbfhe;
    mCmbfhe = nullptr;
  }

  if (mDhe){
    delete mDhe;
    mDhe = nullptr;
  }

  if (mFahe){
    delete mFahe;
    mFahe = nullptr;
  }

  if (mHmclahe){
    delete mHmclahe;
    mHmclahe = nullptr;
  }

  if (mLceBsescs){
    delete mLceBsescs;
    mLceBsescs = nullptr;
  }

  if (mMsrcp){
    delete mMsrcp;
    mMsrcp = nullptr;
  }

  if (mNoshp){
    delete mNoshp;
    mNoshp = nullptr;
  }

  if (mPohe){
    delete mPohe;
    mPohe = nullptr;
  }

  if (mRswhe){
    delete mRswhe;
    mRswhe = nullptr;
  }

  if (mWallis){
    delete mWallis;
    mWallis = nullptr;
  }

  if (mAgast){
    delete mAgast;
    mAgast = nullptr;
  }

  if (mAkaze){
    delete mAkaze;
    mAkaze = nullptr;
  }

  if (mBoost){
    delete mBoost;
    mBoost = nullptr;
  }

  if (mBrief){
    delete mBrief;
    mBrief = nullptr;
  }

  if (mBrisk){
    delete mBrisk;
    mBrisk = nullptr;
  }

  if (mDaisy){
    delete mDaisy;
    mDaisy = nullptr;
  }

  if (mFast){
    delete mFast;
    mFast = nullptr;
  }

  if (mFreak){
    delete mFreak;
    mFreak = nullptr;
  }

  if (mGftt){
    delete mGftt;
    mGftt = nullptr;
  }

  if (mHog){
    delete mHog;
    mHog = nullptr;
  }

  if (mKaze){
    delete mKaze;
    mKaze = nullptr;
  }

  if (mLatch){
    delete mLatch;
    mLatch = nullptr;
  }

  if (mLucid){
    delete mLucid;
    mLucid = nullptr;
  }

  if (mMsd){
    delete mMsd;
    mMsd = nullptr;
  }

  if (mMser){
    delete mMser;
    mMser = nullptr;
  }

  if (mOrb){
    delete mOrb;
    mOrb = nullptr;
  }

  if (mSift){
    delete mSift;
    mSift = nullptr;
  }

  if (mStar){
    delete mStar;
    mStar = nullptr;
  }

  if (mSurf){
    delete mSurf;
    mSurf = nullptr;
  }

  if (mVgg){
    delete mVgg;
    mVgg = nullptr;
  }

  if (mFlannMatcher){
    delete mFlannMatcher;
    mFlannMatcher = nullptr;
  }

  if (mBruteForceMatcher){
    delete mBruteForceMatcher;
    mBruteForceMatcher = nullptr;
  }

  if (mRobustMatcher){
    delete mRobustMatcher;
    mRobustMatcher = nullptr;
  }

  if (mGms){
    delete mGms;
    mGms = nullptr;
  }
}

QString SettingsImp::language() const
{
  return mLanguage;
}

void SettingsImp::setLanguage(const QString &language)
{
  mLanguage = language;
}

QStringList SettingsImp::history() const
{
  return mHistory;
}

void SettingsImp::addToHistory(const QString &project)
{
  mHistory.removeAll(project);
  mHistory.prepend(project);

  while (mHistory.size() > mHistoyMaxSize)
    mHistory.removeLast();
}

void SettingsImp::clearHistory()
{
  mHistory.clear();
}

int SettingsImp::historyMaxSize() const
{
  return mHistoyMaxSize;
}

void SettingsImp::setHistoryMaxSize(int maxSize)
{
  mHistoyMaxSize = maxSize;
}

QString SettingsImp::imageViewerBGcolor() const
{
  return mImageViewerBGcolor;
}

void SettingsImp::setImageViewerBGcolor(const QString &bgColor)
{
  mImageViewerBGcolor = bgColor;
}

QString SettingsImp::keypointsFormat() const
{
  return mKeypointsFormat;
}

void SettingsImp::setKeypointsFormat(const QString &format)
{
  mKeypointsFormat = format;
}

QString SettingsImp::matchesFormat() const
{
  return mMatchesFormat;
}

void SettingsImp::setMatchesFormat(const QString &format)
{
  mMatchesFormat = format;
}

bool SettingsImp::useCuda() const
{
  return mUseCuda;
}

void SettingsImp::setUseCuda(bool active)
{
  mUseCuda = active;
}

Acebsf *SettingsImp::acebsf()
{
  return mAcebsf;
}

const Acebsf *SettingsImp::acebsf() const
{
  return mAcebsf;
}

Clahe *SettingsImp::clahe()
{
  return mClahe;
}

const Clahe *SettingsImp::clahe() const
{
  return mClahe;
}

Cmbfhe *SettingsImp::cmbfhe()
{
  return mCmbfhe;
}

const Cmbfhe *SettingsImp::cmbfhe() const
{
  return mCmbfhe;
}

Dhe *SettingsImp::dhe()
{
  return mDhe;
}

const Dhe *SettingsImp::dhe() const
{
  return mDhe;
}

Fahe *SettingsImp::fahe()
{
  return mFahe;
}

const Fahe *SettingsImp::fahe() const
{
  return mFahe;
}

Hmclahe *SettingsImp::hmclahe()
{
  return mHmclahe;
}

const Hmclahe *SettingsImp::hmclahe() const
{
  return mHmclahe;
}

LceBsescs *SettingsImp::lceBsescs()
{
  return mLceBsescs;
}

const LceBsescs *SettingsImp::lceBsescs() const
{
  return mLceBsescs;
}

Msrcp *SettingsImp::msrcp()
{
  return mMsrcp;
}

const Msrcp *SettingsImp::msrcp() const
{
  return mMsrcp;
}

Noshp *SettingsImp::noshp()
{
  return mNoshp;
}

const Noshp *SettingsImp::noshp() const
{
  return mNoshp;
}

Pohe *SettingsImp::pohe()
{
  return mPohe;
}

const Pohe *SettingsImp::pohe() const
{
  return mPohe;
}

Rswhe *SettingsImp::rswhe()
{
  return mRswhe;
}

const Rswhe *SettingsImp::rswhe() const
{
  return mRswhe;
}

Wallis *SettingsImp::wallis()
{
  return mWallis;
}

const Wallis *SettingsImp::wallis() const
{
  return mWallis;
}

Agast *SettingsImp::agast()
{
  return mAgast;
}

const Agast *SettingsImp::agast() const
{
  return mAgast;
}

Akaze *SettingsImp::akaze()
{
  return mAkaze;
}

const Akaze *SettingsImp::akaze() const
{
  return mAkaze;
}

Boost *SettingsImp::boost()
{
  return mBoost;
}

const Boost *SettingsImp::boost() const
{
  return mBoost;
}

Brief *SettingsImp::brief()
{
  return mBrief;
}

const Brief *SettingsImp::brief() const
{
  return mBrief;
}

Brisk *SettingsImp::brisk()
{
  return mBrisk;
}

const Brisk *SettingsImp::brisk() const
{
  return mBrisk;
}

Daisy *SettingsImp::daisy()
{
  return mDaisy;
}

const Daisy *SettingsImp::daisy() const
{
  return mDaisy;
}

Fast *SettingsImp::fast()
{
  return mFast;
}

const Fast *SettingsImp::fast() const
{
  return mFast;
}

Freak *SettingsImp::freak()
{
  return mFreak;
}

const Freak *SettingsImp::freak() const
{
  return mFreak;
}

Gftt *SettingsImp::gftt()
{
  return mGftt;
}

const Gftt *SettingsImp::gftt() const
{
  return mGftt;
}

Hog *SettingsImp::hog()
{
  return mHog;
}

const Hog *SettingsImp::hog() const
{
  return mHog;
}

Kaze *SettingsImp::kaze()
{
  return mKaze;
}

const Kaze *SettingsImp::kaze() const
{
  return mKaze;
}

Latch *SettingsImp::latch()
{
  return mLatch;
}

const Latch *SettingsImp::latch() const
{
  return mLatch;
}

Lucid *SettingsImp::lucid()
{
  return mLucid;
}

const Lucid *SettingsImp::lucid() const
{
  return mLucid;
}

Msd *SettingsImp::msd()
{
  return mMsd;
}

const Msd *SettingsImp::msd() const
{
  return mMsd;
}

Mser *SettingsImp::mser()
{
  return mMser;
}

const Mser *SettingsImp::mser() const
{
  return mMser;
}

Orb *SettingsImp::orb()
{
  return mOrb;
}

const Orb *SettingsImp::orb() const
{
  return mOrb;
}

Sift *SettingsImp::sift()
{
  return mSift;
}

const Sift *SettingsImp::sift() const
{
  return mSift;
}

Star *SettingsImp::star()
{
  return mStar;
}

const Star *SettingsImp::star() const
{
  return mStar;
}

Surf *photomatch::SettingsImp::surf()
{
  return mSurf;
}

const Surf *SettingsImp::surf() const
{
  return mSurf;
}

Vgg *SettingsImp::vgg()
{
  return mVgg;
}

const Vgg *SettingsImp::vgg() const
{
  return mVgg;
}

QString SettingsImp::matchMethod() const
{
  return mMatchMethod;
}

void SettingsImp::setMatchMethod(const QString &matchingMethod)
{
  mMatchMethod = matchingMethod;
}

QString SettingsImp::matchStrategy() const
{
  return mMatchStrategy;
}

void SettingsImp::setMatchStrategy(const QString &matchingStrategy)
{
  mMatchStrategy = matchingStrategy;
}

FlannMatcher *SettingsImp::flannMatcher()
{
  return mFlannMatcher;
}

const FlannMatcher *SettingsImp::flannMatcher() const
{
  return mFlannMatcher;
}

BruteForceMatcher *SettingsImp::bruteForceMatcher()
{
  return mBruteForceMatcher;
}

const BruteForceMatcher *SettingsImp::bruteForceMatcher() const
{
  return mBruteForceMatcher;
}

RobustMatcher *SettingsImp::robustMatcher()
{
  return mRobustMatcher;
}

const RobustMatcher *SettingsImp::robustMatcher() const
{
  return mRobustMatcher;
}

Gms *SettingsImp::gms()
{
  return mGms;
}

const Gms *SettingsImp::gms() const
{
  return mGms;
}

QString SettingsImp::keypointsViewerBGColor() const
{
  return mKeypointViewerBGColor;
}

void SettingsImp::setKeypointsViewerBGColor(const QString &color)
{
  mKeypointViewerBGColor = color;
}

int SettingsImp::keypointsViewerMarkerType() const
{
  return mKeypointsViewerMarkerType;
}

void SettingsImp::setKeypointsViewerMarkerType(int type)
{
  mKeypointsViewerMarkerType = type;
}

int SettingsImp::keypointsViewerMarkerSize() const
{
  return mKeypointViewerMarkerSize;
}

void SettingsImp::setKeypointsViewerMarkerSize(int size)
{
  mKeypointViewerMarkerSize = size;
}

int SettingsImp::keypointsViewerMarkerWidth() const
{
  return mKeypointViewerMarkerWidth;
}

void SettingsImp::setKeypointsViewerMarkerWidth(int width)
{
  mKeypointViewerMarkerWidth = width;
}

QString SettingsImp::keypointsViewerMarkerColor() const
{
  return mKeypointViewerMarkerColor;
}

void SettingsImp::setKeypointsViewerMarkerColor(const QString &color)
{
  mKeypointViewerMarkerColor = color;
}

int SettingsImp::keypointsViewerSelectMarkerWidth() const
{
  return mKeypointViewerSelectMarkerWidth;
}

void SettingsImp::setKeypointsViewerSelectMarkerWidth(int width)
{
  mKeypointViewerSelectMarkerWidth = width;
}

QString SettingsImp::keypointsViewerSelectMarkerColor() const
{
  return mKeypointViewerSelectMarkerColor;
}

void SettingsImp::setKeypointsViewerSelectMarkerColor(const QString &color)
{
  mKeypointViewerSelectMarkerColor = color;
}

QString SettingsImp::matchesViewerBGColor() const
{
  return mMatchesViewerBGColor;
}

void SettingsImp::setMatchesViewerBGColor(const QString &color)
{
  mMatchesViewerBGColor = color;
}

int SettingsImp::matchesViewerMarkerType() const
{
  return mMatchesViewerMarkerType;
}

void SettingsImp::setMatchesViewerMarkerType(int type)
{
  mMatchesViewerMarkerType = type;
}

int SettingsImp::matchesViewerMarkerSize() const
{
  return mMatchesViewerMarkerSize;
}

void SettingsImp::setMatchesViewerMarkerSize(int size)
{
  mMatchesViewerMarkerSize = size;
}

int SettingsImp::matchesViewerMarkerWidth() const
{
  return mMatchesViewerMarkerWidth;
}

void SettingsImp::setMatchesViewerMarkerWidth(int width)
{
  mMatchesViewerMarkerWidth = width;
}

QString SettingsImp::matchesViewerMarkerColor() const
{
  return mMatchesViewerMarkerColor;
}

void SettingsImp::setMatchesViewerMarkerColor(const QString &color)
{
  mMatchesViewerMarkerColor = color;
}

int SettingsImp::matchesViewerSelectMarkerWidth() const
{
  return mMatchesViewerSelectMarkerWidth;
}

void SettingsImp::setMatchesViewerSelectMarkerWidth(int width)
{
  mMatchesViewerSelectMarkerWidth = width;
}

QString SettingsImp::matchesViewerSelectMarkerColor() const
{
  return mMatchesViewerSelectMarkerColor;
}

void SettingsImp::setMatchesViewerSelectMarkerColor(const QString &color)
{
  mMatchesViewerSelectMarkerColor = color;
}

QString SettingsImp::matchesViewerLineColor() const
{
  return mMatchesViewerLineColor;
}

void SettingsImp::setMatchesViewerLineColor(const QString &color)
{
  mMatchesViewerLineColor = color;
}

int SettingsImp::matchesViewerLineWidth() const
{
  return mMatchesViewerLineWidth;
}

void SettingsImp::setMatchesViewerLineWidth(int width)
{
  mMatchesViewerLineWidth = width;
}

QString SettingsImp::groundTruthEditorBGColor() const
{
  return mGroundTruthEditorBGColor;
}

void SettingsImp::setGroundTruthEditorBGColor(const QString &bgColor)
{
  mGroundTruthEditorBGColor = bgColor;
}

int SettingsImp::groundTruthEditorMarkerSize() const
{
  return mGroundTruthEditorMarkerSize;
}

void SettingsImp::setGroundTruthEditorMarkerSize(int size)
{
  mGroundTruthEditorMarkerSize = size;
}

int SettingsImp::groundTruthEditorMarkerWidth() const
{
  return mGroundTruthEditorMarkerWidth;
}

void SettingsImp::setGroundTruthEditorMarkerWidth(int width)
{
  mGroundTruthEditorMarkerWidth = width;
}

QString SettingsImp::groundTruthEditorMarkerColor() const
{
  return mGroundTruthEditorMarkerColor;
}

void SettingsImp::setGroundTruthEditorMarkerColor(const QString &color)
{
  mGroundTruthEditorMarkerColor = color;
}

int SettingsImp::groundTruthEditorSelectMarkerWidth() const
{
  return mGroundTruthEditorSelectMarkerWidth;
}

void SettingsImp::setGroundTruthEditorSelectMarkerWidth(int width)
{
  mGroundTruthEditorSelectMarkerWidth = width;
}

QString SettingsImp::groundTruthEditorSelectMarkerColor() const
{
  return mGroundTruthEditorSelectMarkerColor;
}

void SettingsImp::setGroundTruthEditorSelectMarkerColor(const QString &color)
{
  mGroundTruthEditorSelectMarkerColor = color;
}

QString SettingsImp::groundTruthEditorMatrixAdjust() const
{
  return mGroundTruthEditorMatrixAdjust;
}

void SettingsImp::setGroundTruthEditorMatrixAdjust(const QString &matrix)
{
  mGroundTruthEditorMatrixAdjust = matrix;
}

void SettingsImp::reset()
{
  mLanguage = "en";

  mHistoyMaxSize = 10;
  mHistory.clear();

  mImageViewerBGcolor = "#dcdcdc";

  mKeypointsFormat = "XML";
  mMatchesFormat = "XML";
  mUseCuda = false;

  mAcebsf->reset();
  mClahe->reset();
  mCmbfhe->reset();
  mDhe->reset();
  mFahe->reset();
  mHmclahe->reset();
  mLceBsescs->reset();
  mMsrcp->reset();
  mNoshp->reset();
  mPohe->reset();
  mRswhe->reset();
  mWallis->reset();

  mAgast->reset();
  mAkaze->reset();
  mBoost->reset();
  mBrief->reset();
  mBrisk->reset();
  mDaisy->reset();
  mFast->reset();
  mFreak->reset();
  mGftt->reset();
  mHog->reset();
  mKaze->reset();
  mLatch->reset();
  mLucid->reset();
  mMsd->reset();
  mMser->reset();
  mOrb->reset();
  mSift->reset();
  mStar->reset();
  mSurf->reset();
  mVgg->reset();

  mMatchMethod = "Flann Based Matching";
  mMatchStrategy = "Robust Matcher";
  mFlannMatcher->reset();
  mBruteForceMatcher->reset();
  mRobustMatcher->reset();
  mGms->reset();

  mKeypointViewerBGColor = "#dcdcdc";
  mKeypointsViewerMarkerType = 0;
  mKeypointViewerMarkerSize = 20;
  mKeypointViewerMarkerWidth = 2;
  mKeypointViewerMarkerColor = "#00aa00";
  mKeypointViewerSelectMarkerWidth = 2;
  mKeypointViewerSelectMarkerColor = "#e5097e";
  mMatchesViewerBGColor = "#dcdcdc";
  mMatchesViewerMarkerType = 0;
  mMatchesViewerMarkerColor = "#00aa00";
  mMatchesViewerMarkerSize = 20;
  mMatchesViewerMarkerWidth = 2;
  mMatchesViewerSelectMarkerWidth = 2;
  mMatchesViewerSelectMarkerColor = "#e5097e";
  mMatchesViewerLineColor = "#0000ff";
  mMatchesViewerLineWidth = 2;
  mGroundTruthEditorBGColor = "#dcdcdc";
  mGroundTruthEditorMarkerColor = "#00aa00";
  mGroundTruthEditorMarkerSize = 20;
  mGroundTruthEditorMarkerWidth = 2;
  mGroundTruthEditorSelectMarkerWidth = 2;
  mGroundTruthEditorSelectMarkerColor = "#e5097e";
  mGroundTruthEditorMatrixAdjust = "Fundamental Matrix";
}


/*----------------------------------------------------------------*/


SettingsControllerImp::SettingsControllerImp()
  : SettingsController(),
    mSettingsController(nullptr)
{
  mSettingsController = new QSettings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "PhotoMatch");
}

SettingsControllerImp::~SettingsControllerImp()
{
  if (mSettingsController){
    delete mSettingsController;
    mSettingsController = nullptr;
  }
}

void SettingsControllerImp::read(Settings &settings)
{
  QString lang = QLocale::system().name();
  lang.truncate(lang.lastIndexOf('_'));
  settings.setLanguage(mSettingsController->value("lang", lang).toString());

  settings.setHistoryMaxSize(mSettingsController->value("HISTORY/MaxSize", settings.historyMaxSize()).toInt());
  QStringList history = mSettingsController->value("HISTORY/RecentProjects", settings.history()).toStringList();
  settings.clearHistory();
  for(auto &prj : history){
    if (QFileInfo(prj).exists()){
      settings.addToHistory(prj);
    }
  }

  settings.setImageViewerBGcolor(mSettingsController->value("ImageViewer/BGColor", settings.imageViewerBGcolor()).toString());

  settings.setKeypointsFormat(mSettingsController->value("MATCH/KeypointsFormat", settings.keypointsFormat()).toString());
  settings.setMatchesFormat(mSettingsController->value("MATCH/MatchesFormat", settings.matchesFormat()).toString());

  settings.setUseCuda(mSettingsController->value("General/UseCuda", settings.useCuda()).toBool());

  /* CLAHE */
  settings.clahe()->setClipLimit(mSettingsController->value("CLAHE/ClipLimit", settings.clahe()->clipLimit()).toDouble());
  settings.clahe()->setTilesGridSize(mSettingsController->value("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize()).toSize());

  /* CMBFHE */
  settings.cmbfhe()->setBlockSize(mSettingsController->value("CMBFHE/BlockSize", settings.cmbfhe()->blockSize()).toSize());

  /* DHE */
  settings.dhe()->setX(mSettingsController->value("DHE/x", settings.dhe()->x()).toInt());

  /* FAHE */
  settings.fahe()->setBlockSize(mSettingsController->value("FAHE/BlockSize", settings.fahe()->blockSize()).toSize());

  /* HMCLAHE */
  settings.hmclahe()->setL(mSettingsController->value("HMCLAHE/L", settings.hmclahe()->l()).toDouble());
  settings.hmclahe()->setPhi(mSettingsController->value("HMCLAHE/Phi", settings.hmclahe()->phi()).toDouble());
  settings.hmclahe()->setBlockSize(mSettingsController->value("HMCLAHE/BlockSize", settings.hmclahe()->blockSize()).toSize());

  /* LCE_BSESCS */
  settings.lceBsescs()->setBlockSize(mSettingsController->value("LCE_BSESCS/BlockSize", settings.lceBsescs()->blockSize()).toSize());

  /* MSRCP */
  settings.msrcp()->setMidScale(mSettingsController->value("MSRCP/MidScale", settings.msrcp()->midScale()).toDouble());
  settings.msrcp()->setLargeScale(mSettingsController->value("MSRCP/LargeScale", settings.msrcp()->largeScale()).toDouble());
  settings.msrcp()->setSmallScale(mSettingsController->value("MSRCP/SmallScale", settings.msrcp()->smallScale()).toDouble());

  /* NOSHP */
  settings.noshp()->setBlockSize(mSettingsController->value("NOSHP/BlockSize", settings.noshp()->blockSize()).toSize());

  /* POHE */
  settings.pohe()->setBlockSize(mSettingsController->value("POHE/BlockSize", settings.pohe()->blockSize()).toSize());

  /* RSWHE */
  int histogramCutDef = static_cast<int>(settings.rswhe()->histogramCut());
  Rswhe::HistogramCut value = static_cast<Rswhe::HistogramCut>(mSettingsController->value("RSWHE/HistogramCut", histogramCutDef).toInt());
  settings.rswhe()->setHistogramCut(value);
  settings.rswhe()->setHistogramDivisions(mSettingsController->value("RSWHE/HistogramDivisions", settings.rswhe()->histogramDivisions()).toInt());

  /* WALLIS */
  settings.wallis()->setContrast(mSettingsController->value("WALLIS/Contrast", settings.wallis()->contrast()).toDouble());
  settings.wallis()->setBrightness(mSettingsController->value("WALLIS/Brightness", settings.wallis()->brightness()).toDouble());
  settings.wallis()->setImposedAverage(mSettingsController->value("WALLIS/ImposedAverage", settings.wallis()->imposedAverage()).toInt());
  settings.wallis()->setImposedLocalStdDev(mSettingsController->value("WALLIS/ImposedLocalStdDev", settings.wallis()->imposedLocalStdDev()).toInt());
  settings.wallis()->setKernelSize(mSettingsController->value("WALLIS/KernelSize", settings.wallis()->kernelSize()).toInt());

  /* AGAST */
  settings.agast()->setThreshold(mSettingsController->value("AGAST/Threshold", settings.agast()->threshold()).toInt());
  settings.agast()->setNonmaxSuppression(mSettingsController->value("AGAST/NonmaxSuppression", settings.agast()->nonmaxSuppression()).toBool());
  settings.agast()->setDetectorType(mSettingsController->value("AGAST/DetectorType", settings.agast()->detectorType()).toString());

  /* AKAZE */
  settings.akaze()->setOctaves(mSettingsController->value("AKAZE/Octaves", settings.akaze()->octaves()).toInt());
  settings.akaze()->setThreshold(mSettingsController->value("AKAZE/Threshold", settings.akaze()->threshold()).toDouble());
  settings.akaze()->setDiffusivity(mSettingsController->value("AKAZE/Diffusivity", settings.akaze()->diffusivity()).toString());
  settings.akaze()->setOctaveLayers(mSettingsController->value("AKAZE/OctaveLayers", settings.akaze()->octaveLayers()).toInt());
  settings.akaze()->setDescriptorSize(mSettingsController->value("AKAZE/DescriptorSize", settings.akaze()->descriptorSize()).toInt());
  settings.akaze()->setDescriptorType(mSettingsController->value("AKAZE/DescriptorType", settings.akaze()->descriptorType()).toString());
  settings.akaze()->setDescriptorChannels(mSettingsController->value("AKAZE/DescriptorChannels", settings.akaze()->descriptorChannels()).toInt());

  /* BOOST */
  settings.boost()->setDescriptorType(mSettingsController->value("BOOST/DescriptorType", settings.boost()->descriptorType()).toString());
  settings.boost()->setUseOrientation(mSettingsController->value("BOOST/UseOrientation", settings.boost()->useOrientation()).toBool());
  settings.boost()->setScaleFactor(mSettingsController->value("BOOST/ScaleFactor", settings.boost()->scaleFactor()).toDouble());

  /* BRIEF */
  settings.brief()->setBytes(mSettingsController->value("BRIEF/Bytes", settings.brief()->bytes()).toString());
  settings.brief()->setUseOrientation(mSettingsController->value("BRIEF/Orientation", settings.brief()->useOrientation()).toBool());

  /* BRISK */
  settings.brisk()->setOctaves(mSettingsController->value("BRISK/Octaves", settings.brisk()->octaves()).toInt());
  settings.brisk()->setThreshold(mSettingsController->value("BRISK/Threshold", settings.brisk()->threshold()).toInt());
  settings.brisk()->setPatternScale(mSettingsController->value("BRISK/PatternScale", settings.brisk()->patternScale()).toDouble());

  /* DAISY */
  settings.daisy()->setNorm(mSettingsController->value("DAISY/Norm", settings.daisy()->norm()).toString());
  settings.daisy()->setQHist(mSettingsController->value("DAISY/QHist", settings.daisy()->qHist()).toInt());
  settings.daisy()->setQTheta(mSettingsController->value("DAISY/QTheta", settings.daisy()->qTheta()).toInt());
  settings.daisy()->setRadius(mSettingsController->value("DAISY/Radius", settings.daisy()->radius()).toInt());
  settings.daisy()->setQRadius(mSettingsController->value("DAISY/QRadius", settings.daisy()->qRadius()).toInt());
  settings.daisy()->setInterpolation(mSettingsController->value("DAISY/Interpolation", settings.daisy()->interpolation()).toBool());
  settings.daisy()->setUseOrientation(mSettingsController->value("DAISY/UseOrientation", settings.daisy()->useOrientation()).toBool());

  /* FAST */
  settings.fast()->setThreshold(mSettingsController->value("FAST/Threshold", settings.fast()->threshold()).toInt());
  settings.fast()->setDetectorType(mSettingsController->value("FAST/DetectorType", settings.fast()->detectorType()).toString());
  settings.fast()->setNonmaxSuppression(mSettingsController->value("FAST/NonmaxSuppression", settings.fast()->nonmaxSuppression()).toBool());

  /* FREAK */
  settings.freak()->setOctaves(mSettingsController->value("FREAK/Octaves", settings.freak()->octaves()).toInt());
  settings.freak()->setPatternScale(mSettingsController->value("FREAK/PatternScale", settings.freak()->patternScale()).toDouble());
  settings.freak()->setScaleNormalized(mSettingsController->value("FREAK/ScaleNormalized", settings.freak()->scaleNormalized()).toBool());
  settings.freak()->setOrientationNormalized(mSettingsController->value("FREAK/OrientationNormalized", settings.freak()->orientationNormalized()).toBool());

  /* GFTT */
  settings.gftt()->setK(mSettingsController->value("GFTT/K", settings.gftt()->k()).toDouble());
  settings.gftt()->setBlockSize(mSettingsController->value("GFTT/BlockSize", settings.gftt()->blockSize()).toInt());
  settings.gftt()->setMaxFeatures(mSettingsController->value("GFTT/MaxFeatures", settings.gftt()->maxFeatures()).toInt());
  settings.gftt()->setMinDistance(mSettingsController->value("GFTT/MinDistance", settings.gftt()->minDistance()).toDouble());
  settings.gftt()->setQualityLevel(mSettingsController->value("GFTT/QualityLevel", settings.gftt()->qualityLevel()).toDouble());
  settings.gftt()->setHarrisDetector(mSettingsController->value("GFTT/HarrisDetector", settings.gftt()->harrisDetector()).toBool());

  /* HOG */
  settings.hog()->setNbins(mSettingsController->value("HOG/Nbins", settings.hog()->nbins()).toInt());
  settings.hog()->setWinSize(mSettingsController->value("HOG/WinSize", settings.hog()->winSize()).toSize());
  settings.hog()->setCellSize(mSettingsController->value("HOG/CellSize", settings.hog()->cellSize()).toSize());
  settings.hog()->setBlockSize(mSettingsController->value("HOG/BlockSize", settings.hog()->blockSize()).toSize());
  settings.hog()->setBlockStride(mSettingsController->value("HOG/BlockStride", settings.hog()->blockStride()).toSize());
  settings.hog()->setDerivAperture(mSettingsController->value("HOG/DerivAperture", settings.hog()->derivAperture()).toInt());

  /* KAZE */
  settings.kaze()->setOctaves(mSettingsController->value("KAZE/Octaves", settings.kaze()->octaves()).toInt());
  settings.kaze()->setUprightDescriptor(mSettingsController->value("KAZE/Upright", settings.kaze()->uprightDescriptor()).toBool());
  settings.kaze()->setThreshold(mSettingsController->value("KAZE/Threshold", settings.kaze()->threshold()).toDouble());
  settings.kaze()->setDiffusivity(mSettingsController->value("KAZE/Diffusivity", settings.kaze()->diffusivity()).toString());
  settings.kaze()->setOctaveLayers(mSettingsController->value("KAZE/OctaveLayers", settings.kaze()->octaveLayers()).toInt());
  settings.kaze()->setExtendedDescriptor(mSettingsController->value("KAZE/ExtendedDescriptor", settings.kaze()->extendedDescriptor()).toBool());

  /* LATCH */
  settings.latch()->setBytes(mSettingsController->value("LATCH/Bytes", settings.latch()->bytes()).toString());
  settings.latch()->setHalfSsdSize(mSettingsController->value("LATCH/HalfSsdSize", settings.latch()->halfSsdSize()).toInt());
  settings.latch()->setRotationInvariance(mSettingsController->value("LATCH/RotationInvariance", settings.latch()->rotationInvariance()).toBool());

  /* LUCID */
  settings.lucid()->setBlurKernel(mSettingsController->value("LUCID/BlurKernel", settings.lucid()->blurKernel()).toInt());
  settings.lucid()->setLucidKernel(mSettingsController->value("LUCID/LucidKernel", settings.lucid()->lucidKernel()).toInt());

  /* MSD */
  settings.msd()->setKNN(mSettingsController->value("MSD/KNN", settings.msd()->knn()).toInt());
  settings.msd()->setAffineTilts(mSettingsController->value("MSD/AffineTilts", settings.msd()->affineTilts()).toInt());
  settings.msd()->setNScales(mSettingsController->value("MSD/NScales", settings.msd()->nScales()).toInt());
  settings.msd()->setAffineMSD(mSettingsController->value("MSD/AffineMSD", settings.msd()->affineMSD()).toBool());
  settings.msd()->setNMSRadius(mSettingsController->value("MSD/NMSRadius", settings.msd()->NMSRadius()).toInt());
  settings.msd()->setNMSScaleRadius(mSettingsController->value("MSD/NMSScaleRadius", settings.msd()->NMSScaleRadius()).toInt());
  settings.msd()->setSearchAreaRadius(mSettingsController->value("MSD/AreaRadius", settings.msd()->searchAreaRadius()).toInt());
  settings.msd()->setPatchRadius(mSettingsController->value("MSD/PathRadius", settings.msd()->patchRadius()).toInt());
  settings.msd()->setScaleFactor(mSettingsController->value("MSD/ScaleFactor", settings.msd()->scaleFactor()).toDouble());
  settings.msd()->setThresholdSaliency(mSettingsController->value("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency()).toDouble());
  settings.msd()->setComputeOrientation(mSettingsController->value("MSD/ComputeOrientations", settings.msd()->computeOrientation()).toBool());

  /* MSER */
  settings.mser()->setDelta(mSettingsController->value("MSER/Delta", settings.mser()->delta()).toInt());
  settings.mser()->setMaxArea(mSettingsController->value("MSER/MaxArea", settings.mser()->maxArea()).toInt());
  settings.mser()->setMinArea(mSettingsController->value("MSER/MinArea", settings.mser()->minArea()).toInt());
  settings.mser()->setMinMargin(mSettingsController->value("MSER/MinMargin", settings.mser()->minMargin()).toInt());
  settings.mser()->setEdgeBlurSize(mSettingsController->value("MSER/EdgeBlurSize", settings.mser()->edgeBlurSize()).toInt());
  settings.mser()->setMaxEvolution(mSettingsController->value("MSER/MaxEvolution", settings.mser()->maxEvolution()).toInt());
  settings.mser()->setMaxVariation(mSettingsController->value("MSER/MaxVariation", settings.mser()->maxVariation()).toDouble());
  settings.mser()->setMinDiversity(mSettingsController->value("MSER/MinDiversity", settings.mser()->minDiversity()).toDouble());
  settings.mser()->setAreaThreshold(mSettingsController->value("MSER/AreaThreshold", settings.mser()->areaThreshold()).toDouble());

  /* ORB */
  settings.orb()->setWTA_K(mSettingsController->value("ORB/WTA_K", settings.orb()->wta_k()).toInt());
  settings.orb()->setPatchSize(mSettingsController->value("ORB/PatchSize", settings.orb()->patchSize()).toInt());
  settings.orb()->setScoreType(mSettingsController->value("ORB/ScoreType", settings.orb()->scoreType()).toString());
  settings.orb()->setScaleFactor(mSettingsController->value("ORB/ScaleFactor", settings.orb()->scaleFactor()).toDouble());
  settings.orb()->setLevelsNumber(mSettingsController->value("ORB/LevelsNumber", settings.orb()->levelsNumber()).toInt());
  settings.orb()->setEdgeThreshold(mSettingsController->value("ORB/EdgeThreshold", settings.orb()->edgeThreshold()).toInt());
  settings.orb()->setFastThreshold(mSettingsController->value("ORB/FastThreshold", settings.orb()->fastThreshold()).toInt());
  settings.orb()->setFeaturesNumber(mSettingsController->value("ORB/FeaturesNumber", settings.orb()->featuresNumber()).toInt());

  /* SIFT */
  settings.sift()->setSigma(mSettingsController->value("SIFT/Sigma", settings.sift()->sigma()).toDouble());
  settings.sift()->setOctaveLayers(mSettingsController->value("SIFT/OctaveLayers", settings.sift()->octaveLayers()).toInt());
  settings.sift()->setEdgeThreshold(mSettingsController->value("SIFT/EdgeThreshold", settings.sift()->edgeThreshold()).toDouble());
  settings.sift()->setFeaturesNumber(mSettingsController->value("SIFT/FeaturesNumber", settings.sift()->featuresNumber()).toInt());
  settings.sift()->setContrastThreshold(mSettingsController->value("SIFT/ContrastThreshold", settings.sift()->contrastThreshold()).toDouble());

  /* STAR */
  settings.star()->setMaxSize(mSettingsController->value("STAR/MaxSize", settings.star()->maxSize()).toInt());
  settings.star()->setResponseThreshold(mSettingsController->value("STAR/ResponseThreshold", settings.star()->responseThreshold()).toInt());
  settings.star()->setSuppressNonmaxSize(mSettingsController->value("STAR/SuppressNonmaxSize", settings.star()->suppressNonmaxSize()).toInt());
  settings.star()->setLineThresholdBinarized(mSettingsController->value("STAR/LineThresholdBinarized", settings.star()->lineThresholdBinarized()).toInt());
  settings.star()->setLineThresholdProjected(mSettingsController->value("STAR/LineThresholdProjected", settings.star()->lineThresholdProjected()).toInt());

  /* SURF */
  settings.surf()->setOctaves(mSettingsController->value("SURF/Octaves", settings.surf()->octaves()).toInt());
  settings.surf()->setOctaveLayers(mSettingsController->value("SURF/OctaveLayers", settings.surf()->octaveLayers()).toInt());
  settings.surf()->setUpright(mSettingsController->value("SURF/RotatedFeatures", settings.surf()->upright()).toBool());
  settings.surf()->setHessianThreshold(mSettingsController->value("SURF/HessianThreshold", settings.surf()->hessianThreshold()).toDouble());
  settings.surf()->setExtendedDescriptor(mSettingsController->value("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor()).toBool());

  /* VGG */
  settings.vgg()->setDescriptorType(mSettingsController->value("VGG/DescriptorType", settings.vgg()->descriptorType()).toString());
  settings.vgg()->setScaleFactor(mSettingsController->value("VGG/ScaleFactor", settings.vgg()->scaleFactor()).toDouble());
  settings.vgg()->setSigma(mSettingsController->value("VGG/Sigma", settings.vgg()->sigma()).toDouble());
  settings.vgg()->setUseNormalizeDescriptor(mSettingsController->value("VGG/UseNormalizeDescriptor", settings.vgg()->useNormalizeDescriptor()).toBool());
  settings.vgg()->setUseNormalizeImage(mSettingsController->value("VGG/UseNormalizeImage", settings.vgg()->useNormalizeImage()).toBool());
  settings.vgg()->setUseScaleOrientation(mSettingsController->value("VGG/UseScaleOrientation", settings.vgg()->useScaleOrientation()).toBool());

  /* Matching */
  settings.setMatchMethod(mSettingsController->value("MATCH/MatchMethod", settings.matchMethod()).toString());
  settings.setMatchStrategy(mSettingsController->value("MATCH/MatchStrategy", settings.matchStrategy()).toString());
  int normType = mSettingsController->value("MATCH/BFNormType", static_cast<int>(settings.bruteForceMatcher()->normType())).toInt();
  settings.bruteForceMatcher()->setNormType(static_cast<BruteForceMatcher::Norm>(normType));
  settings.robustMatcher()->setRatio(mSettingsController->value("MATCH/RefinementRatio", settings.robustMatcher()->ratio()).toDouble());
  settings.robustMatcher()->setDistance(mSettingsController->value("MATCH/RefinementDistance", settings.robustMatcher()->distance()).toDouble());
  settings.robustMatcher()->setConfidence(mSettingsController->value("MATCH/RefinementConfidence", settings.robustMatcher()->confidence()).toDouble());
  settings.robustMatcher()->setCrossCheck(mSettingsController->value("MATCH/RefinementCrossCheck", settings.robustMatcher()->crossCheck()).toBool());
  settings.robustMatcher()->setMaxIters(mSettingsController->value("MATCH/RefinementMaxIters", settings.robustMatcher()->maxIter()).toInt());
  int geometricTest = mSettingsController->value("MATCH/RefinementGeometricTest", static_cast<int>(settings.robustMatcher()->geometricTest())).toInt();
  settings.robustMatcher()->setGeometricTest(static_cast<RobustMatcher::GeometricTest>(geometricTest));
  int homographyComputeMethod = mSettingsController->value("MATCH/RefinementHomographyComputeMethod", static_cast<int>(settings.robustMatcher()->homographyComputeMethod())).toInt();
  settings.robustMatcher()->setHomographyComputeMethod(static_cast<RobustMatcher::HomographyComputeMethod>(homographyComputeMethod));
  int fundamentalComputeMethod = mSettingsController->value("MATCH/RefinementFundamentalComputeMethod", static_cast<int>(settings.robustMatcher()->fundamentalComputeMethod())).toInt();
  settings.robustMatcher()->setFundamentalComputeMethod(static_cast<RobustMatcher::FundamentalComputeMethod>(fundamentalComputeMethod));
  int essentialComputeMethod = mSettingsController->value("MATCH/RefinementEssentialComputeMethod", static_cast<int>(settings.robustMatcher()->essentialComputeMethod())).toInt();
  settings.robustMatcher()->setEssentialComputeMethod(static_cast<RobustMatcher::EssentialComputeMethod>(essentialComputeMethod));
  settings.gms()->setScale(mSettingsController->value("MATCH/GMS_Scale", settings.gms()->scale()).toBool());
  settings.gms()->setRotation(mSettingsController->value("MATCH/GMS_Rotation", settings.gms()->rotation()).toBool());
  settings.gms()->setThreshold(mSettingsController->value("MATCH/GMS_Threshold", settings.gms()->threshold()).toDouble());

  /* Keypoints Viewer */
  settings.setKeypointsViewerBGColor(mSettingsController->value("KeypointsViewer/BGColor", settings.keypointsViewerBGColor()).toString());
  settings.setKeypointsViewerMarkerType(mSettingsController->value("KeypointsViewer/Type",  settings.keypointsViewerMarkerType()).toInt());
  settings.setKeypointsViewerMarkerSize(mSettingsController->value("KeypointsViewer/MarkerSize", settings.keypointsViewerMarkerSize()).toInt());
  settings.setKeypointsViewerMarkerWidth(mSettingsController->value("KeypointsViewer/MarkerWidth", settings.keypointsViewerMarkerWidth()).toInt());
  settings.setKeypointsViewerMarkerColor(mSettingsController->value("KeypointsViewer/MarkerColor", settings.keypointsViewerMarkerColor()).toString());
  settings.setKeypointsViewerSelectMarkerWidth(mSettingsController->value("KeypointsViewer/SelectMarkerWidth", settings.keypointsViewerSelectMarkerWidth()).toInt());
  settings.setKeypointsViewerSelectMarkerColor(mSettingsController->value("KeypointsViewer/SelectMarkerColor", settings.keypointsViewerSelectMarkerColor()).toString());

  /* Matches Viewer */
  settings.setMatchesViewerBGColor(mSettingsController->value("MatchesViewer/BGColor", settings.matchesViewerBGColor()).toString());
  settings.setMatchesViewerMarkerType(mSettingsController->value("MatchesViewer/MarkerType",  settings.matchesViewerMarkerType()).toInt());
  settings.setMatchesViewerMarkerSize(mSettingsController->value("MatchesViewer/MarkerSize", settings.matchesViewerMarkerSize()).toInt());
  settings.setMatchesViewerMarkerWidth(mSettingsController->value("MatchesViewer/MarkerWidth", settings.matchesViewerMarkerWidth()).toInt());
  settings.setMatchesViewerMarkerColor(mSettingsController->value("MatchesViewer/MarkerColor", settings.matchesViewerMarkerColor()).toString());
  settings.setMatchesViewerSelectMarkerWidth(mSettingsController->value("MatchesViewer/SelectMarkerWidth", settings.matchesViewerSelectMarkerWidth()).toInt());
  settings.setMatchesViewerSelectMarkerColor(mSettingsController->value("MatchesViewer/SelectMarkerColor", settings.matchesViewerSelectMarkerColor()).toString());
  settings.setMatchesViewerLineColor(mSettingsController->value("MatchesViewer/LineColor", settings.matchesViewerLineColor()).toString());
  settings.setMatchesViewerLineWidth(mSettingsController->value("MatchesViewer/LineWidth", settings.matchesViewerLineWidth()).toInt());

  /* Ground Truth Editor */
  settings.setGroundTruthEditorBGColor(mSettingsController->value("GroundTruthEditor/BGColor", settings.groundTruthEditorBGColor()).toString());
  settings.setGroundTruthEditorMarkerSize(mSettingsController->value("GroundTruthEditor/MarkerSize", settings.groundTruthEditorMarkerSize()).toInt());
  settings.setGroundTruthEditorMarkerWidth(mSettingsController->value("GroundTruthEditor/MarkerWidth", settings.groundTruthEditorMarkerWidth()).toInt());
  settings.setGroundTruthEditorMarkerColor(mSettingsController->value("GroundTruthEditor/MarkerColor", settings.groundTruthEditorMarkerColor()).toString());
  settings.setGroundTruthEditorSelectMarkerWidth(mSettingsController->value("GroundTruthEditor/SelectMarkerWidth", settings.groundTruthEditorSelectMarkerWidth()).toInt());
  settings.setGroundTruthEditorSelectMarkerColor(mSettingsController->value("GroundTruthEditor/SelectMarkerColor", settings.groundTruthEditorSelectMarkerColor()).toString());
  settings.setGroundTruthEditorMatrixAdjust(mSettingsController->value("GroundTruthEditor/MatrixAdjust", settings.groundTruthEditorMatrixAdjust()).toString());
}

void SettingsControllerImp::write(const Settings &settings)
{
  mSettingsController->setValue("lang", settings.language());

  mSettingsController->setValue("HISTORY/MaxSize", settings.historyMaxSize());
  mSettingsController->setValue("HISTORY/RecentProjects", settings.history());

  mSettingsController->setValue("ImageViewer/BGColor", settings.imageViewerBGcolor());

  mSettingsController->setValue("MATCH/KeypointsFormat", settings.keypointsFormat());
  mSettingsController->setValue("MATCH/MatchFormat", settings.matchesFormat());

  mSettingsController->setValue("General/UseCuda", settings.useCuda());

  /* CLAHE */
  mSettingsController->setValue("CLAHE/ClipLimit", settings.clahe()->clipLimit());
  mSettingsController->setValue("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize());

  /* CMBFHE */
  mSettingsController->setValue("CMBFHE/BlockSize", settings.cmbfhe()->blockSize());

  /* DHE */
  mSettingsController->setValue("DHE/x", settings.dhe()->x());

  /* FAHE */
  mSettingsController->setValue("FAHE/BlockSize", settings.fahe()->blockSize());

  /* HMCLAHE */
  mSettingsController->setValue("HMCLAHE/L", settings.hmclahe()->l());
  mSettingsController->setValue("HMCLAHE/Phi", settings.hmclahe()->phi());
  mSettingsController->setValue("HMCLAHE/BlockSize", settings.hmclahe()->blockSize());

  /* LCE_BSESCS */
  mSettingsController->setValue("LCE_BSESCS/BlockSize", settings.lceBsescs()->blockSize());

  /* MSRCP */
  mSettingsController->setValue("MSRCP/MidScale", settings.msrcp()->midScale());
  mSettingsController->setValue("MSRCP/LargeScale", settings.msrcp()->largeScale());
  mSettingsController->setValue("MSRCP/SmallScale", settings.msrcp()->smallScale());

  /* NOSHP */
  mSettingsController->setValue("NOSHP/BlockSize", settings.noshp()->blockSize());

  /* POHE */
  mSettingsController->setValue("POHE/BlockSize", settings.pohe()->blockSize());

  /* RSWHE */
  mSettingsController->setValue("RSWHE/HistogramCut", static_cast<int>(settings.rswhe()->histogramCut()));
  mSettingsController->setValue("RSWHE/HistogramDivisions", settings.rswhe()->histogramDivisions());

  /* WALLIS */
  mSettingsController->setValue("WALLIS/Contrast", settings.wallis()->contrast());
  mSettingsController->setValue("WALLIS/Brightness", settings.wallis()->brightness());
  mSettingsController->setValue("WALLIS/ImposedAverage", settings.wallis()->imposedAverage());
  mSettingsController->setValue("WALLIS/ImposedLocalStdDev", settings.wallis()->imposedLocalStdDev());
  mSettingsController->setValue("WALLIS/KernelSize", settings.wallis()->kernelSize());


  /* AGAST */
  mSettingsController->setValue("AGAST/Threshold", settings.agast()->threshold());
  mSettingsController->setValue("AGAST/NonmaxSuppression", settings.agast()->nonmaxSuppression());
  mSettingsController->setValue("AGAST/DetectorType", settings.agast()->detectorType());

  /* AKAZE */
  mSettingsController->setValue("AKAZE/Octaves", settings.akaze()->octaves());
  mSettingsController->setValue("AKAZE/Threshold", settings.akaze()->threshold());
  mSettingsController->setValue("AKAZE/Diffusivity", settings.akaze()->diffusivity());
  mSettingsController->setValue("AKAZE/OctaveLayers", settings.akaze()->octaveLayers());
  mSettingsController->setValue("AKAZE/DescriptorSize", settings.akaze()->descriptorSize());
  mSettingsController->setValue("AKAZE/DescriptorType", settings.akaze()->descriptorType());
  mSettingsController->setValue("AKAZE/DescriptorChannels", settings.akaze()->descriptorChannels());

  /* BOOST */
  mSettingsController->setValue("BOOST/DescriptorType", settings.boost()->descriptorType());
  mSettingsController->setValue("BOOST/UseOrientation", settings.boost()->useOrientation());
  mSettingsController->setValue("BOOST/ScaleFactor", settings.boost()->scaleFactor());

  /* BRIEF */
  mSettingsController->setValue("BRIEF/Bytes", settings.brief()->bytes());
  mSettingsController->setValue("BRIEF/Orientation", settings.brief()->useOrientation());

  /* BRISK */
  mSettingsController->setValue("BRISK/Octaves", settings.brisk()->octaves());
  mSettingsController->setValue("BRISK/Threshold", settings.brisk()->threshold());
  mSettingsController->setValue("BRISK/PatternScale", settings.brisk()->patternScale());

  /* DAISY */
  mSettingsController->setValue("DAISY/Norm", settings.daisy()->norm());
  mSettingsController->setValue("DAISY/QHist", settings.daisy()->qHist());
  mSettingsController->setValue("DAISY/QTheta", settings.daisy()->qTheta());
  mSettingsController->setValue("DAISY/Radius", settings.daisy()->radius());
  mSettingsController->setValue("DAISY/QRadius", settings.daisy()->qRadius());
  mSettingsController->setValue("DAISY/Interpolation", settings.daisy()->interpolation());
  mSettingsController->setValue("DAISY/UseOrientation", settings.daisy()->useOrientation());

  /* FAST */
  mSettingsController->setValue("FAST/Threshold", settings.fast()->threshold());
  mSettingsController->setValue("FAST/DetectorType", settings.fast()->detectorType());
  mSettingsController->setValue("FAST/NonmaxSuppression", settings.fast()->nonmaxSuppression());

  /* FREAK */
  mSettingsController->setValue("FREAK/Octaves", settings.freak()->octaves());
  mSettingsController->setValue("FREAK/PatternScale", settings.freak()->patternScale());
  mSettingsController->setValue("FREAK/ScaleNormalized", settings.freak()->scaleNormalized());
  mSettingsController->setValue("FREAK/OrientationNormalized", settings.freak()->orientationNormalized());

  /* GFTT */
  mSettingsController->setValue("GFTT/K", settings.gftt()->k());
  mSettingsController->setValue("GFTT/BlockSize", settings.gftt()->blockSize());
  mSettingsController->setValue("GFTT/MaxFeatures", settings.gftt()->maxFeatures());
  mSettingsController->setValue("GFTT/MinDistance", settings.gftt()->minDistance());
  mSettingsController->setValue("GFTT/QualityLevel", settings.gftt()->qualityLevel());
  mSettingsController->setValue("GFTT/HarrisDetector", settings.gftt()->harrisDetector());

  /* HOG */
  mSettingsController->setValue("HOG/Nbins", settings.hog()->nbins());
  mSettingsController->setValue("HOG/WinSize", settings.hog()->winSize());
  mSettingsController->setValue("HOG/CellSize", settings.hog()->cellSize());
  mSettingsController->setValue("HOG/BlockSize", settings.hog()->blockSize());
  mSettingsController->setValue("HOG/BlockStride", settings.hog()->blockStride());
  mSettingsController->setValue("HOG/DerivAperture", settings.hog()->derivAperture());

  /* KAZE */
  mSettingsController->setValue("KAZE/Octaves", settings.kaze()->octaves());
  mSettingsController->setValue("KAZE/Upright", settings.kaze()->uprightDescriptor());
  mSettingsController->setValue("KAZE/Threshold", settings.kaze()->threshold());
  mSettingsController->setValue("KAZE/Diffusivity", settings.kaze()->diffusivity());
  mSettingsController->setValue("KAZE/OctaveLayers", settings.kaze()->octaveLayers());
  mSettingsController->setValue("KAZE/ExtendedDescriptor", settings.kaze()->extendedDescriptor());

  /* LATCH */
  mSettingsController->setValue("LATCH/Bytes", settings.latch()->bytes());
  mSettingsController->setValue("LATCH/HalfSsdSize", settings.latch()->halfSsdSize());
  mSettingsController->setValue("LATCH/RotationInvariance", settings.latch()->rotationInvariance());

  /* LUCID */
  mSettingsController->setValue("LUCID/BlurKernel", settings.lucid()->blurKernel());
  mSettingsController->setValue("LUCID/LucidKernel", settings.lucid()->lucidKernel());

  /* MSD */
  mSettingsController->setValue("MSD/KNN", settings.msd()->knn());
  mSettingsController->setValue("MSD/AfineTilts", settings.msd()->affineTilts());
  mSettingsController->setValue("MSD/NScales", settings.msd()->nScales());
  mSettingsController->setValue("MSD/AffineMSD", settings.msd()->affineMSD());
  mSettingsController->setValue("MSD/NMSRadius", settings.msd()->NMSRadius());
  mSettingsController->setValue("MSD/NMSScaleRadius", settings.msd()->NMSScaleRadius());
  mSettingsController->setValue("MSD/AreaRadius", settings.msd()->searchAreaRadius());
  mSettingsController->setValue("MSD/PathRadius", settings.msd()->patchRadius());
  mSettingsController->setValue("MSD/ScaleFactor", settings.msd()->scaleFactor());
  mSettingsController->setValue("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency());
  mSettingsController->setValue("MSD/ComputeOrientations", settings.msd()->computeOrientation());

  /* MSER */
  mSettingsController->setValue("MSER/Delta", settings.mser()->delta());
  mSettingsController->setValue("MSER/MaxArea", settings.mser()->maxArea());
  mSettingsController->setValue("MSER/MinArea", settings.mser()->minArea());
  mSettingsController->setValue("MSER/MinMargin", settings.mser()->minMargin());
  mSettingsController->setValue("MSER/EdgeBlurSize", settings.mser()->edgeBlurSize());
  mSettingsController->setValue("MSER/MaxEvolution", settings.mser()->maxEvolution());
  mSettingsController->setValue("MSER/MaxVariation", settings.mser()->maxVariation());
  mSettingsController->setValue("MSER/MinDiversity", settings.mser()->minDiversity());
  mSettingsController->setValue("MSER/AreaThreshold", settings.mser()->areaThreshold());

  /* ORB */
  mSettingsController->setValue("ORB/WTA_K", settings.orb()->wta_k());
  mSettingsController->setValue("ORB/PatchSize", settings.orb()->patchSize());
  mSettingsController->setValue("ORB/ScoreType", settings.orb()->scoreType());
  mSettingsController->setValue("ORB/ScaleFactor", settings.orb()->scaleFactor());
  mSettingsController->setValue("ORB/LevelsNumber", settings.orb()->levelsNumber());
  mSettingsController->setValue("ORB/EdgeThreshold", settings.orb()->edgeThreshold());
  mSettingsController->setValue("ORB/FastThreshold", settings.orb()->fastThreshold());
  mSettingsController->setValue("ORB/FeaturesNumber", settings.orb()->featuresNumber());

  /* SIFT */
  mSettingsController->setValue("SIFT/Sigma", settings.sift()->sigma());
  mSettingsController->setValue("SIFT/OctaveLayers", settings.sift()->octaveLayers());
  mSettingsController->setValue("SIFT/EdgeThreshold", settings.sift()->edgeThreshold());
  mSettingsController->setValue("SIFT/FeaturesNumber", settings.sift()->featuresNumber());
  mSettingsController->setValue("SIFT/ContrastThreshold", settings.sift()->contrastThreshold());

  /* STAR */
  mSettingsController->setValue("STAR/MaxSize", settings.star()->maxSize());
  mSettingsController->setValue("STAR/ResponseThreshold", settings.star()->responseThreshold());
  mSettingsController->setValue("STAR/SuppressNonmaxSize", settings.star()->suppressNonmaxSize());
  mSettingsController->setValue("STAR/LineThresholdBinarized", settings.star()->lineThresholdBinarized());
  mSettingsController->setValue("STAR/LineThresholdProjected", settings.star()->lineThresholdProjected());

  /* SURF */
  mSettingsController->setValue("SURF/Octaves", settings.surf()->octaves());
  mSettingsController->setValue("SURF/OctaveLayers", settings.surf()->octaveLayers());
  mSettingsController->setValue("SURF/RotatedFeatures", settings.surf()->upright());
  mSettingsController->setValue("SURF/HessianThreshold", settings.surf()->hessianThreshold());
  mSettingsController->setValue("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor());

  /* VGG */
  mSettingsController->setValue("VGG/DescriptorType", settings.vgg()->descriptorType());
  mSettingsController->setValue("VGG/ScaleFactor", settings.vgg()->scaleFactor());
  mSettingsController->setValue("VGG/Sigma", settings.vgg()->sigma());
  mSettingsController->setValue("VGG/UseNormalizeDescriptor", settings.vgg()->useNormalizeDescriptor());
  mSettingsController->setValue("VGG/UseNormalizeImage", settings.vgg()->useNormalizeImage());
  mSettingsController->setValue("VGG/UseScaleOrientation", settings.vgg()->useScaleOrientation());

  /* Matching */
  mSettingsController->setValue("MATCH/MatchMethod", settings.matchMethod());
  mSettingsController->setValue("MATCH/MatchStrategy", settings.matchStrategy());
  mSettingsController->setValue("MATCH/BFNormType", static_cast<int>(settings.bruteForceMatcher()->normType()));
  mSettingsController->setValue("MATCH/RefinementRatio", settings.robustMatcher()->ratio());
  mSettingsController->setValue("MATCH/RefinementDistance", settings.robustMatcher()->distance());
  mSettingsController->setValue("MATCH/RefinementConfidence", settings.robustMatcher()->confidence());
  mSettingsController->setValue("MATCH/RefinementCrossCheck", settings.robustMatcher()->crossCheck());
  mSettingsController->setValue("MATCH/RefinementMaxIters", settings.robustMatcher()->maxIter());
  mSettingsController->setValue("MATCH/RefinementGeometricTest", static_cast<int>(settings.robustMatcher()->geometricTest()));
  mSettingsController->setValue("MATCH/RefinementHomographyComputeMethod", static_cast<int>(settings.robustMatcher()->homographyComputeMethod()));
  mSettingsController->setValue("MATCH/RefinementFundamentalComputeMethod", static_cast<int>(settings.robustMatcher()->fundamentalComputeMethod()));
  mSettingsController->setValue("MATCH/RefinementEssentialComputeMethod", static_cast<int>(settings.robustMatcher()->essentialComputeMethod()));
  mSettingsController->setValue("MATCH/GMS_Scale", settings.gms()->scale());
  mSettingsController->setValue("MATCH/GMS_Rotation", settings.gms()->rotation());
  mSettingsController->setValue("MATCH/GMS_Threshold", settings.gms()->threshold());

  /* Keypoints Viewer */
  mSettingsController->setValue("KeypointsViewer/BGColor", settings.keypointsViewerBGColor());
  mSettingsController->setValue("KeypointsViewer/Type",  settings.keypointsViewerMarkerType());
  mSettingsController->setValue("KeypointsViewer/MarkerSize", settings.keypointsViewerMarkerSize());
  mSettingsController->setValue("KeypointsViewer/MarkerWidth", settings.keypointsViewerMarkerWidth());
  mSettingsController->setValue("KeypointsViewer/MarkerColor", settings.keypointsViewerMarkerColor());
  mSettingsController->setValue("KeypointsViewer/SelectMarkerWidth", settings.keypointsViewerSelectMarkerWidth());
  mSettingsController->setValue("KeypointsViewer/SelectMarkerColor", settings.keypointsViewerSelectMarkerColor());

  /* Matches Viewer */
  mSettingsController->setValue("MatchesViewer/BGColor", settings.matchesViewerBGColor());
  mSettingsController->setValue("MatchesViewer/MarkerType", settings.matchesViewerMarkerType());
  mSettingsController->setValue("MatchesViewer/MarkerSize", settings.matchesViewerMarkerSize());
  mSettingsController->setValue("MatchesViewer/MarkerWidth", settings.matchesViewerMarkerWidth());
  mSettingsController->setValue("MatchesViewer/MarkerColor", settings.matchesViewerMarkerColor());
  mSettingsController->setValue("MatchesViewer/SelectMarkerWidth", settings.matchesViewerSelectMarkerWidth());
  mSettingsController->setValue("MatchesViewer/SelectMarkerColor", settings.matchesViewerSelectMarkerColor());
  mSettingsController->setValue("MatchesViewer/LineColor", settings.matchesViewerLineColor());
  mSettingsController->setValue("MatchesViewer/LineWidth", settings.matchesViewerLineWidth());

  /* Ground Truth Editor */
  mSettingsController->setValue("GroundTruthEditor/BGColor", settings.groundTruthEditorBGColor());
  mSettingsController->setValue("GroundTruthEditor/MarkerSize", settings.groundTruthEditorMarkerSize());
  mSettingsController->setValue("GroundTruthEditor/MarkerWidth", settings.groundTruthEditorMarkerWidth());
  mSettingsController->setValue("GroundTruthEditor/MarkerColor", settings.groundTruthEditorMarkerColor());
  mSettingsController->setValue("GroundTruthEditor/SelectMarkerWidth", settings.groundTruthEditorSelectMarkerWidth());
  mSettingsController->setValue("GroundTruthEditor/SelectMarkerColor", settings.groundTruthEditorSelectMarkerColor());
  mSettingsController->setValue("GroundTruthEditor/MatrixAdjust", settings.groundTruthEditorMatrixAdjust());
}

void SettingsControllerImp::writeHistory(const Settings &settings)
{
  mSettingsController->setValue("HISTORY/RecentProjects", settings.history());
}


} // namespace photomatch
