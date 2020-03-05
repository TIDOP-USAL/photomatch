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


#ifndef PHOTOMATCH_BRIEF_WIDGET_H
#define PHOTOMATCH_BRIEF_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QCheckBox;
class QComboBox;

namespace photomatch
{

/*!
 * \brief Interface for BRIEF Widgets
 *
 * Michael Calonder, Vincent Lepetit, Christoph Strecha, and Pascal Fua.
 * Brief: Binary robust independent elementary features. In Computer
 * Vision–ECCV 2010, pages 778–792. Springer, 2010
 * https://www.cs.ubc.ca/~lowe/525/papers/calonder_eccv10.pdf
 */
class PHOTOMATCH_EXPORT BriefWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  BriefWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~BriefWidget() = default;

  /*!
   * \brief Legth of the descriptor in bytes
   * Valid values are: 16, 32 (default) or 64
   * \return Legth of the descriptor
   */
  virtual QString bytes() const = 0;

  /*!
   * \brief useOrientation
   * \return
   */
  virtual bool useOrientation() const = 0;

signals:

  void bytesChange(QString);
  void useOrientationChange(bool);

public slots:

  /*!
   * \brief Set the legth of the descriptor in bytes
   * \param[in] bytes
   */
  virtual void setBytes(const QString &bytes) = 0;

  /*!
   * \brief setUseOrientation
   * \param[in] useOrientation
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

};

class PHOTOMATCH_EXPORT BriefWidgetImp
  : public BriefWidget
{
  Q_OBJECT

public:

  BriefWidgetImp(QWidget *parent = nullptr);
  ~BriefWidgetImp() override;

// IBriefWidget interface

public:

  QString bytes() const override;
  bool useOrientation() const override;

public slots:

  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;

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

  QComboBox *mBytes;
  QCheckBox *mUseOrientation;

};

} // namespace photomatch

#endif // PHOTOMATCH_BRIEF_WIDGET_H
