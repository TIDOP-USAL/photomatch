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


#include "d2net.h"

#include <tidop/core/messages.h>
#include <tidop/core/task.h>
#include <tidop/core/app.h>
#include <tidop/core/exception.h>

namespace photomatch
{


D2NetProperties::D2NetProperties()
  : mMultiscale(false)
{
}

D2NetProperties::D2NetProperties(const D2NetProperties &d2NetProperties)
  : D2Net(d2NetProperties),
    mMultiscale(d2NetProperties.mMultiscale)
{
}

bool D2NetProperties::multiscale() const
{
  return mMultiscale;
}

void D2NetProperties::setMultiscale(bool multiscale)
{
  mMultiscale = multiscale;
}

void D2NetProperties::reset()
{
  mMultiscale = false;
}

QString D2NetProperties::name() const
{
  return QString("D2Net");
}



/*----------------------------------------------------------------*/


D2NetDetectorDescriptor::D2NetDetectorDescriptor()
{

}

D2NetDetectorDescriptor::D2NetDetectorDescriptor(const D2NetDetectorDescriptor &d2NetDetectorDescriptor)
  : D2NetProperties(d2NetDetectorDescriptor),
    FeatureExtractorPython(d2NetDetectorDescriptor)
{

}

D2NetDetectorDescriptor::D2NetDetectorDescriptor(bool multiscale)
{
  setMultiscale(multiscale);
}

void D2NetDetectorDescriptor::extract(const QString &imagePath, 
                                      const QString &featuresPath)
{
  try {
    
    tl::Path app_path = tl::App::instance().path();
    
    std::string cmd;
    cmd.append("\"");
    cmd.append(app_path.parentPath().toString());
    cmd.append("\\PhotoMatch CMD.bat\" python \"");
    cmd.append(app_path.parentPath().toString());
    cmd.append("\\scripts\\D2netFeat.py\" ");
    cmd.append(" --image \"").append(imagePath.toStdString()).append("\" ");
    tl::Path features_path(featuresPath.toStdWString());
    features_path.replaceExtension(".xml");
    cmd.append(" --features \"").append(features_path.toString()).append("\"");
    tl::Process process(cmd);
    
    process.run();
    
    TL_ASSERT(process.status() == tl::Process::Status::finalized, "Feature extractor error");
  
  } catch(...) {
    TL_THROW_EXCEPTION_WITH_NESTED("");
  }
}

void D2NetDetectorDescriptor::reset()
{
  reset();
}


} // namespace photomatch
