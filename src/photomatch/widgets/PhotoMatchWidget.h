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


#ifndef PHOTOMATCH_WIDGET_H
#define PHOTOMATCH_WIDGET_H

#include "photomatch/photomatch_global.h"

#include <QWidget>

namespace photomatch
{

class PHOTOMATCH_EXPORT PhotoMatchWidget
  : public QWidget
{

public:

  PhotoMatchWidget(QWidget *parent = nullptr) : QWidget(parent){}
  ~PhotoMatchWidget() = default;

protected slots:

  virtual void update() = 0;
  virtual void retranslate() = 0;

public slots:

  /*!
   * \brief Reset to initial status
   */
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

} // namespace photomatch

#endif // PHOTOMATCH_WIDGET_H
