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



#ifndef PHOTOMATCH_PROGRESS_H
#define PHOTOMATCH_PROGRESS_H

#include <QObject>

namespace photomatch
{


class ProgressHandler
  : public QObject
{
  Q_OBJECT

public:

  ProgressHandler(QObject *parent = nullptr);
  ~ProgressHandler() override;

  int min() const;
  int max() const;
  int value() const;

signals:

  void rangeChange(int, int);
  void valueChange(int);
  void initialized();
  void finished();
  void titleChange(QString);
  void descriptionChange(QString);

public slots:

  void setRange(int min, int max);
  void setValue(int value);
  void next();
  void init();
  void finish();
  void setTitle(const QString &title);
  void setDescription(const QString &description);

protected:

  int mMin;
  int mMax;
  int mValue;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROGRESS_H
