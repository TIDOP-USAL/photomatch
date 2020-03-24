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


#ifndef PHOTOMATCH_REPEATABILITY_VIEW_H
#define PHOTOMATCH_REPEATABILITY_VIEW_H

#include "photomatch/ui/Repeatability.h"

class QDialogButtonBox;
class QTreeWidget;
class QTreeWidgetItem;

namespace photomatch
{

class RepeatabilityViewImp
  : public RepeatabilityView
{

  Q_OBJECT

public:

  RepeatabilityViewImp(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~RepeatabilityViewImp() override;

private slots:

  void onTreeWidgetSessionsItemSelectionChanged();

// IRepeatabilityView interface

  void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  void setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int>> &repeatability) override;

// IDialogView interface

private:

  virtual void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  QTreeWidget *mTreeWidgetSessions;
  QTreeWidget *mTreeWidget;
};

} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_VIEW_H
