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


#ifndef PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H
#define PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT PassPointsGroupingProcess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  PassPointsGroupingProcess(const std::list<std::tuple<QString,QString,QString>> &pairs,
                            const QString &passPointsFile);

  std::list<std::tuple<QString, QString, QString>> pairs() const;
  void setPairs(const std::list<std::tuple<QString, QString, QString>> &pairs);

  QString passPointsFile() const;
  void setPassPointsFile(const QString &passPointsFile);

signals:

  void writeFinished(QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  std::list<std::tuple<QString,QString,QString>> mPairs;
  QString mPassPointsFile;
};

} // namespace photomatch

#endif // PHOTOMATCH_PASS_POINTS_GROUPING_PROCESS_H
