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


#ifndef PHOTOMATCH_PREPROCESS_VIEW_H
#define PHOTOMATCH_PREPROCESS_VIEW_H

#include "mvp.h"

class QGridLayout;
class QComboBox;
class QDialogButtonBox;
class QSpinBox;
class QCheckBox;

namespace photomatch
{

class IPreprocessView
  : public IDialogView
{

  Q_OBJECT

public:

  IPreprocessView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IPreprocessView(){}

  virtual void setSessionName(const QString &name) = 0;
  virtual void addPreprocess(QWidget *detector) = 0;
  virtual QString currentPreprocess() const = 0;
  virtual void setCurrentPreprocess(const QString &preprocess) = 0;
  virtual int maxImageSize() = 0;
  virtual void setMaxImageSize(int imageSize) = 0;
  virtual void setFullImageSize(bool fullImageSize) = 0;
  virtual bool fullImageSize() = 0;

signals:

  void preprocessChange(QString);
  void run();

};


class PreprocessView
  : public IPreprocessView
{

  Q_OBJECT

public:

  PreprocessView(QWidget *parent = nullptr);
  ~PreprocessView() override;

protected slots:

// IPreprocessView interface

public:

  void setSessionName(const QString &name) override;
  void addPreprocess(QWidget *preprocess) override;
  QString currentPreprocess() const override;
  void setCurrentPreprocess(const QString &preprocess) override;
  int maxImageSize() override;
  void setMaxImageSize(int imageSize) override;
  void setFullImageSize(bool fullImageSize) override;
  bool fullImageSize() override;

protected slots:

  void onCheckBoxFullImageChange();

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QGridLayout *mGridLayoutPreprocess;
  QComboBox *mComboBoxPreprocess;
  QCheckBox *mCheckBoxFullImage;
  QSpinBox *mSpinBoxMaxImageSize;
  QDialogButtonBox *mButtonBox;
  QString mCurrentPreprocess;


};

} // namespace photomatch

#endif // PHOTOMATCH_PREPROCESS_VIEW_H
