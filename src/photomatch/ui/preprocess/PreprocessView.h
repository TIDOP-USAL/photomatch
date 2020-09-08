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

#include "photomatch/ui/preprocess/Preprocess.h"

class QGridLayout;
class QComboBox;
class QDialogButtonBox;
class QSpinBox;
class QCheckBox;
class QLabel;

namespace photomatch
{

class PreprocessViewImp
  : public PreprocessView
{

  Q_OBJECT

public:

  PreprocessViewImp(QWidget *parent = nullptr);
  ~PreprocessViewImp() override;

protected slots:

// PreprocessView interface

public:

  void setSessionName(const QString &name) override;
  void addPreprocess(QWidget *preprocess) override;
  QString currentPreprocess() const override;
  void setCurrentPreprocess(const QString &preprocess) override;
  int maxImageSize() const override;
  void setMaxImageSize(int imageSize) override;
  void setFullImageSize(bool fullImageSize) override;
  bool fullImageSize() const override;

protected slots:

  void onCheckBoxFullImageChange();

// PhotoMatchDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QGridLayout *mGridLayoutPreprocess;
  QLabel *mLabelPreprocess;
  QComboBox *mComboBoxPreprocess;
  QCheckBox *mCheckBoxFullImage;
  QLabel *mLabelMaxImageSize;
  QSpinBox *mSpinBoxMaxImageSize;
  QDialogButtonBox *mButtonBox;
  QString mCurrentPreprocess;

};

} // namespace photomatch

#endif // PHOTOMATCH_PREPROCESS_VIEW_H
