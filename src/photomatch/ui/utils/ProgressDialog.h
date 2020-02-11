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


#ifndef PHOTOMATCH_PROGRESS_DIALOG_H
#define PHOTOMATCH_PROGRESS_DIALOG_H

#include <QDialog>
#include <QTextEdit>

#include "photomatch/process/Process.h"

namespace Ui
{
  class ProgressDialog;
}

namespace photomatch
{

class IProgressDialog
  : public QDialog
{
  Q_OBJECT

public:

  explicit IProgressDialog(QWidget *parent = nullptr) : QDialog(parent){}
  virtual ~IProgressDialog() = default;

public slots:

  virtual void setRange(int min, int max) = 0;
  virtual void setValue(int value) = 0;
  virtual void setInitialized() = 0;
  virtual void setFinished() = 0;
  virtual void setTitle(QString text) = 0;
  virtual void setStatusText(QString text) = 0;

protected slots:

  virtual void onMinimized() = 0;

signals:

  void cancel();

};

class ProgressDialog
  : public IProgressDialog
{
  Q_OBJECT

public:

  explicit ProgressDialog(QWidget *parent = nullptr);
  ~ProgressDialog()  override;

public slots:

  void setRange(int min, int max) override;
  void setValue(int value) override;
  void setInitialized() override;
  void setFinished() override;
  void setTitle(QString title) override;
  void setStatusText(QString text) override;

protected slots:

  void onMinimized() override;

private slots:

  void on_pushButton_clicked();

private:

  Ui::ProgressDialog *ui;
  Process *mProcess;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROGRESS_DIALOG_H
