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

#include "mvp.h"

class MultiProcess;

namespace photomatch
{

class IPreprocessView;
//class IPreprocessModel;
class IProjectModel;
class ISettingsModel;
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
                      //IPreprocessModel *model,
                      IProjectModel *projectModel,
                      ISettingsModel *settingsModel);
  ~PreprocessPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

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
  //IPreprocessModel *mModel;  /// Por ahora es una clase vacia
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
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
