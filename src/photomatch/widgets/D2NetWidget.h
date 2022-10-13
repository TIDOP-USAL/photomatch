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


#ifndef PHOTOMATCH_D2_NET_WIDGET_H
#define PHOTOMATCH_D2_NET_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QCheckBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT D2NetWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  D2NetWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~D2NetWidget() = default;

  virtual bool multiscale() const = 0;

signals:

  void multiscaleChange(bool);

public slots:

  virtual void setMultiscale(bool multiscale) = 0;

};



class PHOTOMATCH_EXPORT D2NetWidgetImp
  : public D2NetWidget
{
  Q_OBJECT

public:

  D2NetWidgetImp(QWidget *parent = nullptr);
  ~D2NetWidgetImp() override;

// D2NetWidget interface

  bool multiscale() const override;
  
public slots:

  void setMultiscale(bool multiscale) override;

// PhotoMatchWidget interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void reset() override;

protected slots:

  void update() override;
  void retranslate() override;

protected:

  QGroupBox *mGroupBox;
  QCheckBox *mCheckBoxMultiscale;

};

} // namespace photomatch

#endif // PHOTOMATCH_D2_NET_WIDGET_H
