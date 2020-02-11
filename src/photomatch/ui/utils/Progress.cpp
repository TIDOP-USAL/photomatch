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



#include "Progress.h"

namespace photomatch
{

ProgressHandler::ProgressHandler(QObject *parent)
  : QObject(parent),
    mMin(0),
    mMax(1),
    mValue(0)
{

}

ProgressHandler::~ProgressHandler()
{

}

void ProgressHandler::setRange(int min, int max)
{
  mMin = min;
  mMax = max;
  emit rangeChange(min, max);
}

void ProgressHandler::setValue(int value)
{
  mValue = value;
  emit valueChange(value);
}

void ProgressHandler::onNextPosition()
{
  setValue(++mValue);
}

void ProgressHandler::onInit()
{
  emit initialized();
}

void ProgressHandler::onFinish()
{
  emit finished();
}

void ProgressHandler::setTitle(const QString &title)
{
  emit titleChange(title);
}

void ProgressHandler::setDescription(const QString &description)
{
  emit descriptionChange(description);
}


} // namespace photomatch


