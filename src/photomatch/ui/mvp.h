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


#ifndef PHOTOMATCH_MVP_H
#define PHOTOMATCH_MVP_H

#include <memory>

#include <QObject>
#include <QDialog>
#include <QEvent>

namespace photomatch
{

class HelpDialog;


class IWidgetView
  : public QWidget
{

  Q_OBJECT

public:

  IWidgetView(QWidget *parent)
    : QWidget(parent)
  {
  }

  virtual ~IWidgetView() override {}

private:

  /*!
   * \brief Widget Initialization
   */
  virtual void init() = 0;

public slots:

  /*!
   * \brief Clear the widget
   */
  virtual void clear() = 0;

private slots:

  virtual void update() = 0;
  virtual void retranslate() = 0;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override
  {
    if (event->type() == QEvent::LanguageChange){
      retranslate();
    }
  }

};


class PhotoMatchDialogView
  : public QDialog
{
  Q_OBJECT

public:

  PhotoMatchDialogView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
    : QDialog(parent, f)
  {
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    Qt::WindowFlags flags = windowFlags();
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
  }

  virtual ~PhotoMatchDialogView() override = default;

private:

  /*!
   * \brief Dialog initialization UI
   */
  virtual void initUI() = 0;

  /*!
   * \brief Signal and slots initialization
   */
  virtual void initSignalAndSlots() = 0;

signals:

  void help();
  void restore();

public slots:

  /*!
   * \brief Clear dialog
   */
  virtual void clear() = 0;

private slots:

  virtual void update() = 0;

  virtual void retranslate() = 0;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override
  {
    if (event->type() == QEvent::LanguageChange){
      retranslate();
    }
  }
};



class PhotoMatchModel
  : public QObject
{

  Q_OBJECT

public:

  PhotoMatchModel(QObject *parent = nullptr) : QObject(parent){}
  virtual ~PhotoMatchModel(){}

private:

  /*!
   * \brief Class Initialization
   */
  virtual void init() = 0;

};


class PhotoMatchPresenter
  : public QObject
{
  Q_OBJECT

public:

  PhotoMatchPresenter() : QObject(){}
  virtual ~PhotoMatchPresenter() = default;

public slots:

 /*!
  * \brief Show help
  */
  virtual void help() = 0;

 /*!
  * \brief Open
  */
  virtual void open() = 0;

  /*!
   * \brief Set Help
   * \param[in] help
   */
  virtual void setHelp(HelpDialog *help) = 0;

private:

  /*!
   * \brief Class Initialization
   */
  virtual void init() = 0;

  /*!
   * \brief Signal and slots initialization
   */
  virtual void initSignalAndSlots() = 0;
};

} // namespace photomatch

#endif // PHOTOMATCH_MVP_H
