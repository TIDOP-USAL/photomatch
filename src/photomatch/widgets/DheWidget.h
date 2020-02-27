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


#ifndef PHOTOMATCH_DHE_WIDGET_H
#define PHOTOMATCH_DHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;

namespace photomatch
{

class DheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  DheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~DheWidget() = default;

  virtual int x() const = 0;

signals:

  void xChange(int);

public slots:

  virtual void setX(int x) = 0;

};

class DheWidgetImp
  : public DheWidget
{
  Q_OBJECT

public:

  DheWidgetImp(QWidget *parent = nullptr);
  ~DheWidgetImp() override;

// IDheWidget interface

public:

  int x() const override;

public slots:

  void setX(int x) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void initUI() override;
  void initSignalAndSlots() override;

protected:

  QSpinBox *mX;
};

} // namespace photomatch

#endif // PHOTOMATCH_DHE_WIDGET_H
