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


#include "MainWindowView.h"
#include "MainWindowModel.h"
#include "MainWindowPresenter.h"

#include <QApplication>

#include "photomatch/photomatch_global.h"

#ifdef HAVE_VLD
#include "vld.h"
#endif

using namespace photomatch;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindowView view;
  MainWindowModel model;
  MainWindowPresenter presenter(&view, &model);
  presenter.open();

  bool r = a.exec();

  return r;
}
