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


#ifndef PHOTOMATCH_EVALUATION_VIEW_H
#define PHOTOMATCH_EVALUATION_VIEW_H

#include "photomatch/ui/evaluation/Evaluation.h"

class QDialogButtonBox;
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;
class QLabel;
class QTabWidget;
class QDoubleSpinBox;

namespace photomatch
{

class EvaluationViewImp
  : public EvaluationView
{

  Q_OBJECT

public:

  EvaluationViewImp(QWidget *parent = nullptr,
                      Qt::WindowFlags f = Qt::WindowFlags());
  ~EvaluationViewImp() override;

// EvaluationView interface

  void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  bool isSessionActive(const QString &session) const override;
  QString leftImage() const override;
  void setLeftImage(const QString &leftImage) override;
  QString rightImage() const override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setErrors(const QString &session, const Report &report) override;
  void removeErrors(const QString &session) override;
  void removeErrors() override;
  double errorThreshold() const override;

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

  QDialogButtonBox *mButtonBox;
  QLabel *mLabelLeftImage;
  QComboBox  *mComboBoxLeftImage;
  QLabel *mLabelRightImage;
  QComboBox  *mComboBoxRightImage;
  QLabel *mLabelErrorThreshold;
  QDoubleSpinBox *mDoubleSpinBoxErrorThreshold;
  QTreeWidget *mTreeWidgetSessions;
  QTabWidget *mTabWidget;
  QTreeWidget *mTreeWidgetErrors;
};


} // namespace photomatch

#endif // PHOTOMATCH_EVALUATION_VIEW_H
