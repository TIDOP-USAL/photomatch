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


#ifndef PHOTOMATCH_IMAGE_PREPROCESS_H
#define PHOTOMATCH_IMAGE_PREPROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/preprocess/preprocess.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT ImagePreprocess
  : public ProcessConcurrent
{

  Q_OBJECT
    
public:

  ImagePreprocess(const QString &img,
                  const QString &imgPreprocess,
                  const std::shared_ptr<ImageProcess> &preprocess,
                  int maxSize = -1);

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

  void setMaxImageSize(int size);

  std::shared_ptr<ImageProcess> preprocess() const;

signals:

  void preprocessed(QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImgInput;
  QString mImgOutput;
  std::shared_ptr<ImageProcess> mPreprocess;
  int mMaxSize;
};


} // namespace photomatch

#endif // PHOTOMATCH_IMAGE_PREPROCESS_H
