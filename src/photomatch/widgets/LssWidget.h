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


#ifndef PHOTOMATCH_LSS_WIDGET_H
#define PHOTOMATCH_LSS_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for LSS Widgets class
 */
class PHOTOMATCH_EXPORT LssWidget
  : public PhotoMatchWidget
{

  Q_OBJECT

public:

  LssWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~LssWidget() = default;

};




class PHOTOMATCH_EXPORT LssWidgetImp
  : public LssWidget
{

Q_OBJECT

public:

  LssWidgetImp(QWidget *parent = nullptr);
  ~LssWidgetImp() override;

// PhotoMatchWidget interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void reset() override;

protected slots:

  void update() override;
  void retranslate() override;

};

} // namespace photomatch

#endif // PHOTOMATCH_LSS_WIDGET_H
