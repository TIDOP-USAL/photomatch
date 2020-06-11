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


#ifndef PHOTOMATCH_PREPROCESS_PRESENTER_H
#define PHOTOMATCH_PREPROCESS_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include "photomatch/ui/preprocess/Preprocess.h"

class MultiProcess;

namespace photomatch
{

class PreprocessView;
class ProjectModel;
class SettingsModel;
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
class Preprocess;
class ImageProcess;


class PreprocessPresenterImp
  : public PreprocessPresenter
{
  Q_OBJECT

public:

  PreprocessPresenterImp(PreprocessView *view,
                         ProjectModel *projectModel,
                         SettingsModel *settingsModel);
  ~PreprocessPresenterImp() override;

private:

  void setPreprocessProperties(Preprocess *preprocess);
  void setAcebsfProperties(Preprocess *preprocess);
  void setClaheProperties(Preprocess *preprocess);
  void setCmbfheProperties(Preprocess *preprocess);
  void setDheProperties(Preprocess *preprocess);
  void setFaheProperties(Preprocess *preprocess);
  void setHmClaheProperties(Preprocess *preprocess);
  void setLcebsescsProperties(Preprocess *preprocess);
  void setMsrcpProperties(Preprocess *preprocess);
  void setNoshpProperties(Preprocess *preprocess);
  void setPoheProperties(Preprocess *preprocess);
  void setRswheProperties(Preprocess *preprocess);
  void setWallisProperties(Preprocess *preprocess);
  std::shared_ptr<ImageProcess> preprocess(const QString &preprocess);
  QString fileOut(const QString &fileIn);

// PhotoMatchModel interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

// PreprocessPresenter interface

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

  PreprocessView *mView;
  ProjectModel *mProjectModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;

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
