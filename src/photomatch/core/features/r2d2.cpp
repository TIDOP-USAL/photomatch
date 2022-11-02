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


#include "r2d2.h"

#include <tidop/core/messages.h>
#include <tidop/core/task.h>
#include <tidop/core/app.h>
#include <tidop/core/exception.h>

namespace photomatch
{


R2D2Properties::R2D2Properties()
{
}

R2D2Properties::R2D2Properties(const R2D2Properties &r2D2Properties)
  : R2D2(r2D2Properties)
{
}

double R2D2Properties::scaleF() const
{
  return mScaleF;
}

void R2D2Properties::setScaleF(double scaleF)
{
  mScaleF = scaleF;
}

int R2D2Properties::minSize() const
{
  return mMinSize;
}

void R2D2Properties::setMinSize(int size)
{
  mMinSize = size;
}

int R2D2Properties::maxSize() const
{
  return mMaxSize;
}

void R2D2Properties::setMaxSize(int size)
{
  mMaxSize = size;
}

double R2D2Properties::minScale() const
{
  return mMinScale;
}

void R2D2Properties::setMinScale(double minScale)
{
  mMinScale = minScale;
}

double R2D2Properties::maxScale() const
{
  return mMaxScale;
}

void R2D2Properties::setMaxScale(double maxScale)
{
  mMaxScale = maxScale;
}

double R2D2Properties::reliabilityThreshold() const
{
  return mReliabilityThreshold;
}

void R2D2Properties::setReliabilityThreshold(double reliabilityThreshold)
{
  mReliabilityThreshold = reliabilityThreshold;
}

double R2D2Properties::repeatabilityThreshold() const
{
  return mRepeatabilityThreshold;
}

void R2D2Properties::setRepeatabilityThreshold(double repeatabilityThreshold)
{
  mRepeatabilityThreshold = repeatabilityThreshold;
}

void R2D2Properties::reset()
{
  mScaleF = pow(2,0.25);
  mMinSize = 256;
  mMaxSize = 1024;
  mMinScale = 0;
  mMaxScale = 1;
  mReliabilityThreshold = 0.7;
  mRepeatabilityThreshold = 0.7;
}

QString R2D2Properties::name() const
{
  return QString("R2D2");
}



/*----------------------------------------------------------------*/


R2D2DetectorDescriptor::R2D2DetectorDescriptor()
{

}

R2D2DetectorDescriptor::R2D2DetectorDescriptor(const R2D2DetectorDescriptor &r2D2DetectorDescriptor)
  : R2D2Properties(r2D2DetectorDescriptor),
    FeatureExtractorPython(r2D2DetectorDescriptor)
{

}

R2D2DetectorDescriptor::R2D2DetectorDescriptor(double scaleF,
                                               int minSize,
                                               int maxSize,
                                               double minScale,
                                               double maxScale,
                                               double reliabilityThreshold,
                                               double repeatabilityThreshold)
{
  setScaleF(scaleF);
  setMinSize(minSize);
  setMaxSize(maxSize);
  setMinScale(minScale);
  setMaxScale(maxScale);
  setReliabilityThreshold(reliabilityThreshold);
  setRepeatabilityThreshold(repeatabilityThreshold);
}

void R2D2DetectorDescriptor::extract(const QString &imagePath, 
                                     const QString &featuresPath)
{
  try {
    
    tl::Path app_path = tl::App::instance().path();

    std::string cmd;
    cmd.append("\"");
    cmd.append(app_path.parentPath().toString());
    cmd.append("\\PhotoMatch CMD.bat\" python \"");
    cmd.append(app_path.parentPath().toString());
    cmd.append("\\scripts\\R2D2Feat.py\" ");
    cmd.append(" --image \"").append(imagePath.toStdString()).append("\" ");
    tl::Path features_path(featuresPath.toStdWString());
    features_path.replaceExtension(".xml");
    cmd.append(" --features \"").append(features_path.toString()).append("\"");
    //cmd.append("--top-k 5000");
    cmd.append(" --scale-f ").append(std::to_string(scaleF()));
    cmd.append(" --min-size ").append(std::to_string(minSize()));
    cmd.append(" --max-size ").append(std::to_string(maxSize()));
    cmd.append(" --min-scale ").append(std::to_string(minScale()));
    cmd.append(" --max-scale ").append(std::to_string(maxScale()));
    cmd.append(" --reliability-thr ").append(std::to_string(reliabilityThreshold()));
    cmd.append(" --repeatability-thr ").append(std::to_string(repeatabilityThreshold()));
    // Si no se soporta cuda
    //cmd.append("--gpu -1");

    tl::Process process(cmd);
    
    process.run();
    
    TL_ASSERT(process.status() == tl::Process::Status::finalized, "Feature extractor error");
  
  } catch(...) {
    TL_THROW_EXCEPTION_WITH_NESTED("");
  }
}

void R2D2DetectorDescriptor::reset()
{
  reset();
}


} // namespace photomatch
