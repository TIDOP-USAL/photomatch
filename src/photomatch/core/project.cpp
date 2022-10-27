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


#include "project.h"

#include "photomatch/core/settings.h"

#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/asift.h"
#include "photomatch/core/features/boost.h"
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/d2net.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/lss.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/flann.h"
#include "photomatch/core/features/bfmatch.h"
#include "photomatch/core/features/robustmatch.h"
#include "photomatch/core/features/gsm.h"
#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/preprocess/clahe.h"
#include "photomatch/core/preprocess/cmbfhe.h"
#include "photomatch/core/preprocess/decolor.h"
#include "photomatch/core/preprocess/dhe.h"
#include "photomatch/core/preprocess/fahe.h"
#include "photomatch/core/preprocess/hmclahe.h"
#include "photomatch/core/preprocess/lce_bsescs.h"
#include "photomatch/core/preprocess/msrcp.h"
#include "photomatch/core/preprocess/noshp.h"
#include "photomatch/core/preprocess/pohe.h"
#include "photomatch/core/preprocess/rswhe.h"
#include "photomatch/core/preprocess/wallis.h"

#include <tidop/core/messages.h>

#include <QFile>
#include <QFileInfo>
#include <QXmlStreamWriter>

#include <iostream>
#include <fstream>

#define PHOTOMATCH_PROJECT_FILE_VERSION "1.0"

namespace photomatch
{

ProjectImp::ProjectImp()
  : Project(),
    mName(""),
    mDescription(""),
    mProjectFolder(""),
    mVersion(PHOTOMATCH_PROJECT_FILE_VERSION),
    mGroundTruth(""),
    mCurrentSession(-1)
{
}

QString ProjectImp::name() const
{
  return mName;
}

void ProjectImp::setName(const QString &name)
{
  mName = name;
}

QString ProjectImp::description() const
{
  return mDescription;
}

void ProjectImp::setDescription(const QString &description)
{
  mDescription = description;
}

QString ProjectImp::projectFolder() const
{
  return mProjectFolder;
}

void ProjectImp::setProjectFolder(const QString &dir)
{
  mProjectFolder = dir;
}


QString ProjectImp::version() const
{
  return mVersion;
}

QString ProjectImp::groundTruth() const
{
  return mGroundTruth;
}

void ProjectImp::setGroundTruth(const QString &groundTruth)
{
  mGroundTruth = groundTruth;
}

void ProjectImp::addImage(const std::shared_ptr<Image> &img)
{
  std::shared_ptr<Image> image = findImage(img->path());
  if (image != nullptr) {
    QByteArray ba = img->path().toLocal8Bit();
    msgWarning("Image %s already in the project", ba.data());
  } else {
    mImages.push_back(img);
  }
}

void ProjectImp::deleteImage(const QString &img)
{
  deleteImage(findImageId(img));
}

void ProjectImp::deleteImage(size_t imgId)
{
  if (imgId != std::numeric_limits<size_t>::max()){
    mImages.erase(mImages.begin()+ static_cast<long long>(imgId));
  }
}

std::shared_ptr<Image> ProjectImp::findImage(const QString &path)
{
  for (auto &image : mImages) {
    if (image->path().compare(path) == 0) {
      return image;
    }
  }
  return nullptr;
}

const std::shared_ptr<Image> ProjectImp::findImage(const QString &path) const
{
  for (auto &image : mImages) {
    if (image->path().compare(path) == 0) {
      return image;
    }
  }
  return nullptr;
}

std::shared_ptr<Image> ProjectImp::findImageById(size_t id)
{
  return mImages[id];
}

const std::shared_ptr<Image> ProjectImp::findImageById(size_t id) const
{
  return mImages[id];
}

std::shared_ptr<Image> ProjectImp::findImageByName(const QString &imgName)
{
  for (auto &image : mImages) {
    if (image->name().compare(imgName) == 0) {
      return image;
    }
  }
  return nullptr;
}

const std::shared_ptr<Image> ProjectImp::findImageByName(const QString &imgName) const
{
  for (auto &image : mImages) {
    if (image->name().compare(imgName) == 0) {
      return image;
    }
  }
  return nullptr;
}

size_t ProjectImp::findImageId(const QString &path) const
{
  for (size_t i = 0; i < mImages.size(); i++){
    if (mImages[i]->path().compare(path) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

Project::image_iterator ProjectImp::imageBegin()
{
  return mImages.begin();
}

Project::image_const_iterator ProjectImp::imageBegin() const
{
  return mImages.cbegin();
}

Project::image_iterator ProjectImp::imageEnd()
{
  return mImages.end();
}

Project::image_const_iterator ProjectImp::imageEnd() const
{
  return mImages.cend();
}

size_t ProjectImp::imagesCount() const
{
  return mImages.size();
}

void ProjectImp::addSession(const QString &name, 
                            const QString &description)
{
  std::shared_ptr<Session> session(new SessionImp(name, description));
  addSession(session);
}

void ProjectImp::addSession(const std::shared_ptr<Session> &session)
{
  std::shared_ptr<Session> _session = findSession(session->name());
  if (_session != nullptr) {
    QByteArray ba = session->name().toLocal8Bit();
    /// TODO: mensajes de la aplicación
    //msgWarning("Image %s already in the project", ba.data());
  } else {
    mSessions.push_back(session);
  }
}

void ProjectImp::deleteSession(const QString &sessionName)
{
  deleteSession(findSessionId(sessionName));
}

void ProjectImp::deleteSession(size_t sessionId)
{
  if (sessionId != std::numeric_limits<size_t>().max()){
    if (mCurrentSession == static_cast<int>(sessionId)){
      mCurrentSession = mSessions.size() == 1 ? -1 : static_cast<int>(mSessions.size()) - 1;
    }
    mSessions.erase(mSessions.begin()+ static_cast<long long>(sessionId));
  }
}

std::shared_ptr<Session> ProjectImp::findSession(const QString &sessionName)
{
  for (auto &session : mSessions) {
    if (session->name().compare(sessionName) == 0) {
      return session;
    }
  }
  return nullptr;
}

const std::shared_ptr<Session> ProjectImp::findSession(const QString &sessionName) const
{
  for (auto &session : mSessions) {
    if (session->name().compare(sessionName) == 0) {
      return session;
    }
  }
  return nullptr;
}

size_t ProjectImp::findSessionId(const QString &sessionName)
{
  for (size_t i = 0; i < mSessions.size(); i++){
    if (mSessions[i]->name().compare(sessionName) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

size_t ProjectImp::findSessionId(const QString &sessionName) const
{
  for (size_t i = 0; i < mSessions.size(); i++){
    if (mSessions[i]->name().compare(sessionName) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

Project::session_iterator ProjectImp::sessionBegin()
{
  return mSessions.begin();
}

Project::session_const_iterator ProjectImp::sessionBegin() const
{
  return mSessions.cbegin();
}

Project::session_iterator ProjectImp::sessionEnd()
{
  return mSessions.end();
}

Project::session_const_iterator ProjectImp::sessionEnd() const
{
  return mSessions.cend();
}

size_t ProjectImp::sessionCount() const
{
  return mSessions.size();
}

std::shared_ptr<Session> ProjectImp::currentSession()
{
  if (mCurrentSession < 0){
    return nullptr;
  } else {
    session_iterator it = mSessions.begin() + mCurrentSession;
    return (*it);
  }
}

const std::shared_ptr<Session> ProjectImp::currentSession() const
{
  session_const_iterator it = mSessions.begin() + mCurrentSession;
  return (*it);
}

void ProjectImp::setCurrentSession(const QString &sessionName)
{
  size_t id = this->findSessionId(sessionName);
  if (id != std::numeric_limits<size_t>().max()){
    mCurrentSession = static_cast<int>(id);
  }
}

void ProjectImp::clear()
{
  mName = "";
  mDescription = "";
  mProjectFolder = "";
  mVersion = PHOTOMATCH_PROJECT_FILE_VERSION;
  mGroundTruth = "";
  mImages.resize(0);
  mSessions.resize(0);
  mCurrentSession = -1;
}



std::mutex ProjectControllerImp::sMutex;

ProjectControllerImp::ProjectControllerImp()
 : ProjectController()
{

}


bool ProjectControllerImp::read(const QString &file, Project &prj)
{
  std::lock_guard<std::mutex> lck(ProjectControllerImp::sMutex);

  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "PhotoMatch") {
        while (stream.readNextStartElement()) {
          if (stream.name() == "General") {
            readGeneral(stream, prj);
          } else if (stream.name() == "Images") {
            readImages(stream, prj);
          } else if (stream.name() == "GroundTruth") {
            readGroundTruth(stream, prj);
          } else if (stream.name() == "Sessions") {
            readSessions(stream, prj);
          }
        }
      } else {
        stream.raiseError(QObject::tr("Incorrect project file"));
        return true;
      }
    }
  }
  return false;
}

bool ProjectControllerImp::write(const QString &file, 
                                 const Project &prj) const
{
  std::lock_guard<std::mutex> lck(ProjectControllerImp::sMutex);

  bool err = false;
  QFileInfo file_info(file);
  QString tmpfile = file_info.path().append(file_info.baseName()).append(".bak");

  try {

    std::ifstream  src(file.toStdString().c_str(), std::ios::binary);
    std::ofstream  dst(tmpfile.toStdString().c_str(), std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    QFile output(file);
    if (output.open(QFile::WriteOnly)){
      QXmlStreamWriter stream(&output);
      stream.setAutoFormatting(true);
      stream.writeStartDocument();

      stream.writeStartElement("PhotoMatch");
      {
        writeVersion(stream, prj.version());
        writeGeneral(stream, prj);
        writeImages(stream, prj);
        writeGroundTruth(stream, prj.groundTruth());
        writeSessions(stream, prj);
      }

      stream.writeEndElement(); // PhotoMatch

      output.close();
    } else{
      err = true;
    }

  } catch (std::exception &e) {
    msgError(e.what());

    std::ifstream  src(tmpfile.toStdString().c_str(), std::ios::binary);
    std::ofstream  dst(file.toStdString().c_str(), std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    err = true;
  }

  std::remove(tmpfile.toStdString().c_str());

  return err;
}

bool ProjectControllerImp::checkOldVersion(const QString &file) const
{
  std::lock_guard<std::mutex> lck(ProjectControllerImp::sMutex);
  bool bUpdateVersion = false;
  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "PhotoMatch") {
        QString version = "0";
        for (auto &attr : stream.attributes()) {
          if (attr.name().compare(QString("version")) == 0) {
            version = attr.value().toString();
            break;
          }
        }
        if (version.compare(PHOTOMATCH_PROJECT_FILE_VERSION) < 0) {
          // Es una versión mas antigua
          bUpdateVersion = true;
        }
      } else
        stream.raiseError(QObject::tr("Incorrect file"));
    }
  }
  return bUpdateVersion;
}

void ProjectControllerImp::oldVersionBak(const QString &file) const
{
  // Versión antigua
  QString version = "0";
  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "PhotoMatch") {
        for (auto &attr : stream.attributes()) {
          if (attr.name().compare(QString("version")) == 0) {
            version = attr.value().toString();
            break;
          }
        }
      }
    }
  }

  QFileInfo file_info(file);
  QString tmpfile = file_info.path().append(file_info.baseName()).append("_v").append(version).append(".bak");
  std::ifstream  src(file.toStdString().c_str(), std::ios::binary);
  std::ofstream  dst(tmpfile.toStdString().c_str(), std::ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();
}

void ProjectControllerImp::readGeneral(QXmlStreamReader &stream, Project &prj)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Name") {
      prj.setName(stream.readElementText());
    } else if (stream.name() == "ProjectFolder") {
      prj.setProjectFolder(stream.readElementText());
    } else if (stream.name() == "Description") {
      prj.setDescription(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readImages(QXmlStreamReader &stream, Project &prj)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Image") {
      prj.addImage(readImage(stream));
    } else
      stream.skipCurrentElement();
  }
}

std::shared_ptr<Image> ProjectControllerImp::readImage(QXmlStreamReader &stream)
{
  std::shared_ptr<Image> photo(new Image);
  while (stream.readNextStartElement()) {
    if (stream.name() == "File") {
      photo->setPath(stream.readElementText());
    } else if (stream.name() == "LongitudeExif") {
      photo->setLongitudeExif(readDouble(stream));
    } else if (stream.name() == "LatitudeExif") {
      photo->setLatitudeExif(readDouble(stream));
    } else if (stream.name() == "AltitudeExif") {
      photo->setAltitudeExif(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
  return photo;
}

void ProjectControllerImp::readGroundTruth(QXmlStreamReader &stream, Project &prj)
{
  prj.setGroundTruth(stream.readElementText());
}

bool ProjectControllerImp::readActiveSession(QXmlStreamReader &stream)
{
  bool bActive = false;
  for (auto &attr : stream.attributes()) {
    if (attr.name().compare(QString("active")) == 0) {
      QString value = attr.value().toString();
      if (value.compare("1") == 0 || value.compare("true") == 0){
        bActive = true;
      }
      break;
    }
  }
  return bActive;
}

void ProjectControllerImp::readSessions(QXmlStreamReader &stream, Project &prj)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Session") {

      bool bActive = readActiveSession(stream);

      std::shared_ptr<Session> session = readSession(stream);
      prj.addSession(session);

      if (bActive)
        prj.setCurrentSession(session->name());

    } else
      stream.skipCurrentElement();
  }
}




std::shared_ptr<Session> ProjectControllerImp::readSession(QXmlStreamReader &stream)
{
  std::shared_ptr<Session> session(new SessionImp);

  while (stream.readNextStartElement()) {
    if (stream.name() == "Name") {
      readSessionName(stream, session.get());
    } else if (stream.name() == "Description") {
      readSessionDescription(stream, session.get());
    } else if (stream.name() == "MaxImageSize") {
      readSessionMaxImageSize(stream, session.get());
    } else if (stream.name() == "Preprocess") {
      while (stream.readNextStartElement()) {
        readPreprocess(stream, session.get());
      }
    } else if (stream.name() == "Features") {
      readFeatures(stream, session.get());
    } else if (stream.name() == "Matches") {
      readMatches(stream, session.get());
    } else
      stream.skipCurrentElement();
  }

  return session;
}

void ProjectControllerImp::readSessionName(QXmlStreamReader &stream, Session *session)
{
  session->setName(stream.readElementText());
}

void ProjectControllerImp::readSessionDescription(QXmlStreamReader &stream, Session *session)
{
  session->setDescription(stream.readElementText());
}

void ProjectControllerImp::readSessionMaxImageSize(QXmlStreamReader &stream, Session *session)
{
  session->setMaxImageSize(readInt(stream));
}

void ProjectControllerImp::readPreprocess(QXmlStreamReader &stream, Session *session)
{
  if (stream.name() == "Acebsf") {
    std::shared_ptr<Acebsf> acebsf = std::make_shared<AcebsfProperties>();
    readACEBSF(stream, acebsf.get());
    session->setPreprocess(acebsf);
  } else if (stream.name() == "Clahe") {
    std::shared_ptr<Clahe> clahe = std::make_shared<ClaheProperties>();
    readCLAHE(stream, clahe.get());
    session->setPreprocess(clahe);
  } else if (stream.name() == "Cmbfhe") {
    std::shared_ptr<Cmbfhe> cmbfhe(new CmbfheProperties);
    readCMBFHE(stream, cmbfhe.get());
    session->setPreprocess(cmbfhe);
  } else if (stream.name() == "Decolor") {
    std::shared_ptr<Decolor> decolor = std::make_shared<DecolorProperties>();
    session->setPreprocess(decolor);
    stream.skipCurrentElement();
  } else if (stream.name() == "Dhe") {
    std::shared_ptr<Dhe> dhe = std::make_shared<DheProperties>();
    readDHE(stream, dhe.get());
    session->setPreprocess(dhe);
  } else if (stream.name() == "Fahe") {
    std::shared_ptr<Fahe> fahe(new FaheProperties);
    readFAHE(stream, fahe.get());
    session->setPreprocess(fahe);
  } else if (stream.name() == "Hmclahe") {
    std::shared_ptr<Hmclahe> hmclahe(new HmclaheProperties);
    readHMCLAHE(stream, hmclahe.get());
    session->setPreprocess(hmclahe);
  } else if (stream.name() == "LceBsescs") {
    std::shared_ptr<LceBsescs> lceBsescs(new LceBsescsProperties);
    readLCEBSESCS(stream, lceBsescs.get());
    session->setPreprocess(lceBsescs);
  } else if (stream.name() == "Msrcp") {
    std::shared_ptr<Msrcp> msrcp = std::make_shared<MsrcpProperties>();
    readMSRCP(stream, msrcp.get());
    session->setPreprocess(msrcp);
  } else if (stream.name() == "Noshp") {
    std::shared_ptr<Noshp> noshp(new NoshpProperties);
    readNOSHP(stream, noshp.get());
    session->setPreprocess(noshp);
  } else if (stream.name() == "Pohe") {
    std::shared_ptr<Pohe> pohe(new PoheProperties);
    readPOHE(stream, pohe.get());
    session->setPreprocess(pohe);
  } else if (stream.name() == "Rswhe") {
    std::shared_ptr<Rswhe> rswhe = std::make_shared<RswheProperties>();
    readRSWHE(stream, rswhe.get());
    session->setPreprocess(rswhe);
  } else if (stream.name() == "Wallis") {
    std::shared_ptr<Wallis> wallis = std::make_shared<WallisProperties>();
    readWALLIS(stream, wallis.get());
    session->setPreprocess(wallis);
  } else if (stream.name() == "PreprocessedImages") {
    while (stream.readNextStartElement()) {
      if (stream.name() == "PreprocessedImage") {
        session->addPreprocessImage(stream.readElementText());
      } else
        stream.skipCurrentElement();
    }
  } else
    stream.skipCurrentElement();
}

void ProjectControllerImp::readFeatures(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()){
    if (stream.name() == "Detector") {
      readFeaturesDetector(stream, session);
    } else if (stream.name() == "Descriptor") {
      readFeaturesDescriptor(stream, session);
    } else if (stream.name() == "Files") {
      readFeaturesFiles(stream, session);
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFeaturesDetector(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()){
    if (stream.name() == "AGAST") {
      std::shared_ptr<Agast> agast = std::make_shared<AgastProperties>();
      readAGAST(stream, agast.get());
      session->setDetector(agast);
    } else if (stream.name() == "AKAZE") {
      std::shared_ptr<Akaze> akaze = std::make_shared<AkazeProperties>();
      readAKAZE(stream, akaze.get());
      session->setDetector(akaze);
    } else if(stream.name() == "ASIFT") {
      std::shared_ptr<ASift> asift = std::make_shared<ASiftProperties>();
      readASIFT(stream, asift.get());
      session->setDetector(asift);
    } else if (stream.name() == "BRISK") {
      std::shared_ptr<Brisk> brisk = std::make_shared<BriskProperties>();
      readBRISK(stream, brisk.get());
      session->setDetector(brisk);
    } else if (stream.name() == "D2NET") {
      std::shared_ptr<D2Net> d2net = std::make_shared<D2NetProperties>();
      readD2NET(stream, d2net.get());
      session->setDetector(d2net);
    } else if (stream.name() == "FAST") {
      std::shared_ptr<Fast> fast = std::make_shared<FastProperties>();
      readFAST(stream, fast.get());
      session->setDetector(fast);
    } else if (stream.name() == "GFTT") {
      std::shared_ptr<Gftt> gftt = std::make_shared<GfttProperties>();
      readGFTT(stream, gftt.get());
      session->setDetector(gftt);
    } else if (stream.name() == "KAZE") {
      std::shared_ptr<Kaze> kaze = std::make_shared<KazeProperties>();
      readKAZE(stream, kaze.get());
      session->setDetector(kaze);
    } else if (stream.name() == "MSD") {
      std::shared_ptr<Msd> msd = std::make_shared<MsdProperties>();
      readMSD(stream, msd.get());
      session->setDetector(msd);
    } else if (stream.name() == "MSER") {
      std::shared_ptr<Mser> mser = std::make_shared<MserProperties>();
      readMSER(stream, mser.get());
      session->setDetector(mser);
    } else if (stream.name() == "ORB") {
      std::shared_ptr<Orb> orb = std::make_shared<OrbProperties>();
      readORB(stream, orb.get());
      session->setDetector(orb);
    } else if (stream.name() == "SIFT") {
      std::shared_ptr<Sift> sift = std::make_shared<SiftProperties>();
      readSIFT(stream, sift.get());
      session->setDetector(sift);
    } else if (stream.name() == "STAR") {
      std::shared_ptr<Star> star = std::make_shared<StarProperties>();
      readSTAR(stream, star.get());
      session->setDetector(star);
    } else if (stream.name() == "SURF") {
      std::shared_ptr<Surf> surf = std::make_shared<SurfProperties>();
      readSURF(stream, surf.get());
      session->setDetector(surf);
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFeaturesDescriptor(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()){
    if (stream.name() == "AKAZE") {
      std::shared_ptr<Akaze> akaze = std::make_shared<AkazeProperties>();
      readAKAZE(stream, akaze.get());
      session->setDescriptor(akaze);
    } else if(stream.name() == "ASIFT") {
      std::shared_ptr<ASift> asift = std::make_shared<ASiftProperties>();
      readASIFT(stream, asift.get());
      session->setDescriptor(asift);
    } else if (stream.name() == "BRIEF") {
      std::shared_ptr<Brief> brief = std::make_shared<BriefProperties>();
      readBRIEF(stream, brief.get());
      session->setDescriptor(brief);
    } else if (stream.name() == "BRISK") {
      std::shared_ptr<Brisk> brisk = std::make_shared<BriskProperties>();
      readBRISK(stream, brisk.get());
      session->setDescriptor(brisk);
    } else if(stream.name() == "D2NET") {
      std::shared_ptr<D2Net> d2net = std::make_shared<D2NetProperties>();
      readD2NET(stream, d2net.get());
      session->setDescriptor(d2net);
    } else if (stream.name() == "DAISY") {
      std::shared_ptr<Daisy> daisy = std::make_shared<DaisyProperties>();
      readDAISY(stream, daisy.get());
      session->setDescriptor(daisy);
    } else if (stream.name() == "FREAK") {
      std::shared_ptr<Freak> freak = std::make_shared<FreakProperties>();
      readFREAK(stream, freak.get());
      session->setDescriptor(freak);
    } else if (stream.name() == "HOG") {
      std::shared_ptr<Hog> hog = std::make_shared<HogProperties>();
      readHOG(stream, hog.get());
      session->setDescriptor(hog);
    } else if (stream.name() == "KAZE") {
      std::shared_ptr<Kaze> kaze = std::make_shared<KazeProperties>();
      readKAZE(stream, kaze.get());
      session->setDescriptor(kaze);
    } else if (stream.name() == "LATCH") {
      std::shared_ptr<Latch> latch = std::make_shared<LatchProperties>();
      readLATCH(stream, latch.get());
      session->setDescriptor(latch);
    } else if (stream.name() == "LUCID") {
      std::shared_ptr<Lucid> lucid = std::make_shared<LucidProperties>();
      readLUCID(stream, lucid.get());
      session->setDescriptor(lucid);
    } else if (stream.name() == "LSS") {
      std::shared_ptr<Lss> lss = std::make_shared<LssProperties>();
      session->setDescriptor(lss);
      stream.skipCurrentElement();
    } else if (stream.name() == "ORB") {
      std::shared_ptr<Orb> orb = std::make_shared<OrbProperties>();
      readORB(stream, orb.get());
      session->setDescriptor(orb);
    } else if (stream.name() == "SIFT") {
      std::shared_ptr<Sift> sift = std::make_shared<SiftProperties>();
      readSIFT(stream, sift.get());
      session->setDescriptor(sift);
    } else if (stream.name() == "SURF") {
      std::shared_ptr<Surf> surf = std::make_shared<SurfProperties>();
      readSURF(stream, surf.get());
      session->setDescriptor(surf);
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFeaturesFiles(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "FeatFile") {
      session->addFeatures(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readMatches(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "MatchingMethod") {
      readMatchingMethod(stream, session);
    } else if (stream.name() == "MatchingStrategy") {
      readMatchingStrategy(stream, session);
    } else if (stream.name() == "Images") {
      readMatchesImages(stream, session);
    } else if (stream.name() == "PassPoints") {
      readPassPoints(stream, session);
    } else
      stream.skipCurrentElement();

  }
}

void ProjectControllerImp::readMatchingMethod(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BruteForceMatcher") {
      readBruteForceMatching(stream, session);
    } else if (stream.name() == "Flann") {
      readFlannMatcher(stream, session);
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readBruteForceMatching(QXmlStreamReader &stream, Session *session)
{
  std::shared_ptr<BruteForceMatcher> brute_force = std::make_shared<BruteForceMatcherProperties>();

  while (stream.readNextStartElement()) {
    if (stream.name() == "NORM") {
      brute_force->setNormType(readBruteForceMatchingNormType(stream));
    } else
      stream.skipCurrentElement();
  }
  session->setMatchingMethod(brute_force);
}

BruteForceMatcher::Norm ProjectControllerImp::readBruteForceMatchingNormType(QXmlStreamReader &stream)
{
  QString normType = stream.readElementText();
  BruteForceMatcher::Norm norm = BruteForceMatcherProperties::Norm::l2;
  if (normType.compare("NORM_L1") == 0) {
    norm = BruteForceMatcherProperties::Norm::l1;
  } else if (normType.compare("NORM_L2") == 0) {
    norm = BruteForceMatcherProperties::Norm::l2;
  } else if (normType.compare("NORM_HAMMING") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming;
  } else if (normType.compare("NORM_HAMMING2") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming2;
  }
  return norm;
}

void ProjectControllerImp::readFlannMatcher(QXmlStreamReader &stream, Session *session)
{
  std::shared_ptr<FlannMatcher> flann = std::make_shared<FlannMatcherProperties>();

  while (stream.readNextStartElement()) {
    if (stream.name() == "Index") {
      QString normType = stream.readElementText();
      FlannMatcherProperties::Index index = FlannMatcherProperties::Index::kdtree;
      if (normType.compare("KDTree") == 0) {
        index = FlannMatcherProperties::Index::kdtree;
      } else if (normType.compare("LSH") == 0) {
        index = FlannMatcherProperties::Index::lsh;
      }
      flann->setIndex(index);
    } else
      stream.skipCurrentElement();
  }
  session->setMatchingMethod(flann);
}

void ProjectControllerImp::readMatchingStrategy(QXmlStreamReader &stream, Session *session)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "RobustMatcher") {
      readRobustMatching(stream, session);
    } else if (stream.name() == "GMS") {
      readGms(stream, session);
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readRobustMatching(QXmlStreamReader &stream, Session *session)
{
  std::shared_ptr<RobustMatcher> robustMatcher = std::make_shared<RobustMatchingProperties>();
  while (stream.readNextStartElement()) {
    if (stream.name() == "Ratio") {
      robustMatcher->setRatio(readDouble(stream));
    } else if (stream.name() == "CrossCheck") {
      robustMatcher->setCrossCheck(readBoolean(stream));
    } else if (stream.name() == "GeometricTest") {
      readRobustMatchingGeometricTest(stream, robustMatcher.get());
    } else {
      stream.skipCurrentElement();
    }
  }
  session->setMatchingStrategy(robustMatcher);
}

void ProjectControllerImp::readRobustMatchingGeometricTest(QXmlStreamReader &stream,
                                                           RobustMatcher *robustMatcher)
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "HomographyMatrix") {
      readRobustMatchingGeometricTestHomographyMatrix(stream, robustMatcher);
    } else if (stream.name() == "FundamentalMatrix") {
      readRobustMatchingGeometricTestFundamentalMatrix(stream, robustMatcher);
    } else if (stream.name() == "EssentialMatrix") {
      readRobustMatchingGeometricTestEssentialMatrix(stream, robustMatcher);
    } else {
      stream.skipCurrentElement();
    }
  }
}

void ProjectControllerImp::readRobustMatchingGeometricTestHomographyMatrix(QXmlStreamReader &stream, 
                                                                           RobustMatcher *robustMatcher)
{
  std::shared_ptr<tl::GeometricTest> geometric_test;

  QString type;
  for(auto &attr : stream.attributes()) {
    if(attr.name().compare(QString("Type")) == 0) {
      type = attr.value().toString();
      break;
    }
  }

  if (type == "all_points") {
    tl::AllPointsTestProperties properties = readAllPoints(stream);;
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::homography_all_points, &properties);
  } else if (type == "ransac") {
    tl::RANSACTestProperties properties = readRANSAC(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::homography_ransac, &properties);
  } else if (type == "lmeds") {
    tl::LMedsTestProperties properties = readLMeds(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::homography_lmeds, &properties);
  } else if (type == "rho") {
    tl::RHOTestProperties properties = readRho(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::homography_rho, &properties);
  } else if (type == "usac") {
    tl::UsacTestProperties properties = readUSAC(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::homography_usac, &properties);
  }

  robustMatcher->setGeometricTest(geometric_test);
}

tl::AllPointsTestProperties ProjectControllerImp::readAllPoints(QXmlStreamReader &stream)
{
  tl::AllPointsTestProperties properties;

  while(stream.readNextStartElement()) {
    if(stream.name() == "Confidence") {
      properties.confidence = readDouble(stream);
    } else {
      stream.skipCurrentElement();
    }
  }

  return properties;
}

tl::RANSACTestProperties ProjectControllerImp::readRANSAC(QXmlStreamReader &stream)
{
  tl::RANSACTestProperties properties;

  while(stream.readNextStartElement()) {
    if(stream.name() == "Confidence") {
      properties.confidence = readDouble(stream);
    } else if(stream.name() == "Iterations") {
      properties.iterations = readInt(stream);
    } else if(stream.name() == "Distance") {
      properties.distance = readInt(stream);
    } else {
      stream.skipCurrentElement();
    }
  }

  return properties;
}

tl::RHOTestProperties ProjectControllerImp::readRho(QXmlStreamReader &stream)
{
  tl::RHOTestProperties properties;

  while(stream.readNextStartElement()) {
    if(stream.name() == "Confidence") {
      properties.confidence = readDouble(stream);
    } else if(stream.name() == "Distance") {
      properties.distance = readInt(stream);
    } else {
      stream.skipCurrentElement();
    }
  }

  return properties;
}

tl::UsacTestProperties ProjectControllerImp::readUSAC(QXmlStreamReader &stream)
{
  tl::UsacTestProperties properties;

  while(stream.readNextStartElement()) {
    if(stream.name() == "Confidence") {
      properties.confidence = readDouble(stream);
    } else if(stream.name() == "IsParallel") {
      properties.isParallel = readBoolean(stream);
    } else if(stream.name() == "Iterations") {
      properties.loIterations = readInt(stream);
    } else if(stream.name() == "SampleSize") {
      properties.loSampleSize = readInt(stream);
    } else if(stream.name() == "MaxIters") {
      properties.maxIterations = readInt(stream);
    } else {
      stream.skipCurrentElement();
    }
  }
  ///TODO: Añadir el resto de parámetros
  
  return properties;
}

tl::LMedsTestProperties ProjectControllerImp::readLMeds(QXmlStreamReader &stream)
{
  tl::LMedsTestProperties properties;

  while(stream.readNextStartElement()) {
    if(stream.name() == "Confidence") {
      properties.confidence = readDouble(stream);
    } else if(stream.name() == "Iterations") {
      properties.iterations = readInt(stream);
    } else {
      stream.skipCurrentElement();
    }
  }

  return properties;
}

//RobustMatcher::HomographyComputeMethod ProjectControllerImp::readRobustMatchingGeometricTestHomographyMatrixComputeMethod(QXmlStreamReader &stream)
//{
//  QString computeMethod = stream.readElementText();
//  RobustMatcher::HomographyComputeMethod homographyComputeMethod = RobustMatcher::HomographyComputeMethod::ransac;
//  if (computeMethod.compare("All Points") == 0){
//    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::all_points;
//  } else if (computeMethod.compare("RANSAC") == 0){
//    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::ransac;
//  } else if (computeMethod.compare("LMedS") == 0){
//    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::lmeds;
//  } else if (computeMethod.compare("RHO") == 0){
//    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::rho;
//  }
//  return homographyComputeMethod;
//}

void ProjectControllerImp::readRobustMatchingGeometricTestFundamentalMatrix(QXmlStreamReader &stream, RobustMatcher *robustMatcher)
{
  std::shared_ptr<tl::GeometricTest> geometric_test;

  QString type;
  for(auto &attr : stream.attributes()) {
    if(attr.name().compare(QString("Type")) == 0) {
      type = attr.value().toString();
      break;
    }
  }

  if(type == "seven_points") {
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::fundamental_seven_points);
  } else if(type == "eight_points") {
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::fundamental_eight_points);
  } else if(type == "ransac") {
    tl::RANSACTestProperties properties = readRANSAC(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::fundamental_ransac, &properties);
  } else if(type == "lmeds") {
    tl::LMedsTestProperties properties = readLMeds(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::fundamental_lmeds, &properties);
  } else if(type == "usac") {
    tl::UsacTestProperties properties = readUSAC(stream);
    geometric_test = tl::GeometricTestFactory::create(tl::GeometricTest::Type::fundamental_usac, &properties);
  }

  robustMatcher->setGeometricTest(geometric_test);
}

//RobustMatcher::FundamentalComputeMethod ProjectControllerImp::readRobustMatchingGeometricTestFundamentalMatrixComputeMethod(QXmlStreamReader &stream)
//{
//  QString computeMethod = stream.readElementText();
//  RobustMatcher::FundamentalComputeMethod fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::ransac;
//  if (computeMethod.compare("LMedS") == 0){
//    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::lmeds;
//  } else if (computeMethod.compare("RANSAC") == 0){
//    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::ransac;
//  } else if (computeMethod.compare("7-point algorithm") == 0){
//    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::algorithm_7_point;
//  } else if (computeMethod.compare("8-point algorithm") == 0){
//    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::algorithm_8_point;
//  }
//  return fundamentalComputeMethod;
//}

void ProjectControllerImp::readRobustMatchingGeometricTestEssentialMatrix(QXmlStreamReader &stream, RobustMatcher *robustMatcher)
{
  //robustMatcher->setGeometricTest(RobustMatcher::GeometricTest::essential);
  //while (stream.readNextStartElement()) {
  //  if (stream.name() == "ComputeMethod") {
  //    robustMatcher->setEssentialComputeMethod(readRobustMatchingGeometricTestEssentialMatrixComputeMethod(stream));
  //  } else if (stream.name() == "Distance") {
  //    robustMatcher->setDistance(readDouble(stream));
  //  } else if (stream.name() == "MaxIter") {
  //    robustMatcher->setMaxIters(readInt(stream));
  //  } else if (stream.name() == "Confidence") {
  //    robustMatcher->setConfidence(readDouble(stream));
  //  } else {
  //    stream.skipCurrentElement();
  //  }
  //}
}

//RobustMatcher::EssentialComputeMethod ProjectControllerImp::readRobustMatchingGeometricTestEssentialMatrixComputeMethod(QXmlStreamReader &stream)
//{
//  QString computeMethod = stream.readElementText();
//  RobustMatcher::EssentialComputeMethod essentialComputeMethod = RobustMatcher::EssentialComputeMethod::ransac;
//  if (computeMethod.compare("RANSAC") == 0){
//    essentialComputeMethod = RobustMatcher::EssentialComputeMethod::ransac;
//  } else if (computeMethod.compare("LMedS") == 0){
//    essentialComputeMethod = RobustMatcher::EssentialComputeMethod::lmeds;
//  }
//  return essentialComputeMethod;
//}

void ProjectControllerImp::readGms(QXmlStreamReader &stream, Session *session)
{
  std::shared_ptr<Gms> gms = std::make_shared<GmsProperties>();
  while (stream.readNextStartElement()) {
    if (stream.name() == "Scale") {
      gms->setScale(readBoolean(stream));
    } else if (stream.name() == "Rotation") {
      gms->setRotation(readBoolean(stream));
    } else if (stream.name() == "GeometricTest") {
      gms->setThreshold(readDouble(stream));
    } else {
      stream.skipCurrentElement();
    }
  }
  session->setMatchingStrategy(gms);
}

void ProjectControllerImp::readMatchesImages(QXmlStreamReader &stream, Session *session)
{
  QString img1;
  QString img2;
  QString file;

  while (stream.readNextStartElement()) {
    if (stream.name() == "Image") {
      while (stream.readNextStartElement()) {
        if (stream.name() == "Name") {
          img1 = stream.readElementText();
        } else if (stream.name() == "Pairs") {
          while (stream.readNextStartElement()) {
            if (stream.name() == "Pair") {
              while (stream.readNextStartElement()) {
                if (stream.name() == "Name") {
                  img2 = stream.readElementText();
                } else if (stream.name() == "File") {
                  file = stream.readElementText();
                } else
                  stream.skipCurrentElement();
              }
              session->addMatches(img1, img2, file);
            } else
              stream.skipCurrentElement();
          }
        } else
          stream.skipCurrentElement();
      }
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readPassPoints(QXmlStreamReader &stream, Session *session)
{
  QString passPointFile = stream.readElementText();
  session->setPassPoints(passPointFile);
}

void ProjectControllerImp::readACEBSF(QXmlStreamReader &stream, Acebsf *acebsf) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      acebsf->setBlockSize(readSize(stream));
    } else if (stream.name() == "L") {
      acebsf->setL(readDouble(stream));
    } else if (stream.name() == "K1") {
      acebsf->setK1(readDouble(stream));
    } else if (stream.name() == "K2") {
      acebsf->setK2(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readCLAHE(QXmlStreamReader &stream, Clahe *clahe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "ClipLimit") {
      clahe->setClipLimit(readDouble(stream));
    } else if (stream.name() == "GridSize") {
      clahe->setTilesGridSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readCMBFHE(QXmlStreamReader &stream, Cmbfhe *cmbfhe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      cmbfhe->setBlockSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readDHE(QXmlStreamReader &stream, Dhe *dhe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "X") {
      dhe->setX(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFAHE(QXmlStreamReader &stream, Fahe *fahe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      fahe->setBlockSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readHMCLAHE(QXmlStreamReader &stream, Hmclahe *hmclahe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      hmclahe->setBlockSize(readSize(stream));
    } else if (stream.name() == "L") {
      hmclahe->setL(readDouble(stream));
    } else if (stream.name() == "Phi") {
      hmclahe->setPhi(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readLCEBSESCS(QXmlStreamReader &stream, LceBsescs *lceBsescs) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      lceBsescs->setBlockSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readMSRCP(QXmlStreamReader &stream, Msrcp *msrcp) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "SmallScale") {
      msrcp->setSmallScale(readInt(stream));
    } else if (stream.name() == "MidScale") {
      msrcp->setMidScale(readInt(stream));
    } else if (stream.name() == "LargeScale") {
      msrcp->setLargeScale(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readNOSHP(QXmlStreamReader &stream, Noshp *noshp) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      noshp->setBlockSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readPOHE(QXmlStreamReader &stream, Pohe *pohe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "BlockSize") {
      pohe->setBlockSize(readSize(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readRSWHE(QXmlStreamReader &stream, Rswhe *rswhe) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "HistogramDivisions") {
      rswhe->setHistogramDivisions(readInt(stream));
    } else if (stream.name() == "HistogramCut") {
      rswhe->setHistogramCut(static_cast<Rswhe::HistogramCut>(readInt(stream)));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readWALLIS(QXmlStreamReader &stream, Wallis *wallis) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Contrast") {
      wallis->setContrast(readDouble(stream));
    } else if (stream.name() == "Brightness") {
      wallis->setBrightness(readDouble(stream));
    } else if (stream.name() == "ImposedAverage") {
      wallis->setImposedAverage(readInt(stream));
    } else if (stream.name() == "ImposedLocalStdDev") {
      wallis->setImposedLocalStdDev(readInt(stream));
    } else if (stream.name() == "KernelSize") {
      wallis->setKernelSize(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readAGAST(QXmlStreamReader &stream, Agast *agast) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Threshold") {
      agast->setThreshold(readInt(stream));
    } else if (stream.name() == "Brightness") {
      agast->setNonmaxSuppression(readBoolean(stream));
    } else if (stream.name() == "ImposedAverage") {
      agast->setDetectorType(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readAKAZE(QXmlStreamReader &stream, Akaze *akaze) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "DescriptorType") {
      akaze->setDescriptorType(stream.readElementText());
    } else if (stream.name() == "DescriptorSize") {
      akaze->setDescriptorSize(readInt(stream));
    } else if (stream.name() == "DescriptorChannels") {
      akaze->setDescriptorChannels(readInt(stream));
    } else if (stream.name() == "Threshold") {
      akaze->setThreshold(readDouble(stream));
    } else if (stream.name() == "Octaves") {
      akaze->setOctaves(readInt(stream));
    } else if (stream.name() == "OctaveLayers") {
      akaze->setOctaveLayers(readInt(stream));
    } else if (stream.name() == "Diffusivity") {
      akaze->setDiffusivity(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readASIFT(QXmlStreamReader &stream, ASift *asift) const
{
  while(stream.readNextStartElement()) {
    if(stream.name() == "FeaturesNumber") {
      asift->setFeaturesNumber(readInt(stream));
    } else if(stream.name() == "OctaveLayers") {
      asift->setOctaveLayers(readInt(stream));
    } else if(stream.name() == "ContrastThreshold") {
      asift->setContrastThreshold(readDouble(stream));
    } else if(stream.name() == "EdgeThreshold") {
      asift->setEdgeThreshold(readDouble(stream));
    } else if(stream.name() == "Sigma") {
      asift->setSigma(readDouble(stream));
    } else if(stream.name() == "MinTilt") {
      asift->setMinTilt(readInt(stream));
    } else if(stream.name() == "MaxTilt") {
      asift->setMaxTilt(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readBOOST(QXmlStreamReader &stream, Boost *boost) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "DescriptorType") {
      boost->setDescriptorType(stream.readElementText());
    } else if (stream.name() == "UseOrientation") {
      boost->setUseOrientation(readBoolean(stream));
    } else if (stream.name() == "ScaleFactor") {
      boost->setScaleFactor(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readBRIEF(QXmlStreamReader &stream, Brief *brief) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Bytes") {
      brief->setBytes(stream.readElementText());
    } else if (stream.name() == "UseOrientation") {
      brief->setUseOrientation(readBoolean(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readBRISK(QXmlStreamReader &stream, Brisk *brisk) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Threshold") {
      brisk->setThreshold(readInt(stream));
    } else if (stream.name() == "Octaves") {
      brisk->setOctaves(readInt(stream));
    } else if (stream.name() == "PatternScale") {
      brisk->setPatternScale(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readD2NET(QXmlStreamReader &stream, D2Net *d2net) const
{
  while(stream.readNextStartElement()) {
    if(stream.name() == "Multiscale") {
      d2net->setMultiscale(readBoolean(stream));
    }  else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readDAISY(QXmlStreamReader &stream, Daisy *daisy) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Radius") {
      daisy->setRadius(readDouble(stream));
    } else if (stream.name() == "QRadius") {
      daisy->setQRadius(readInt(stream));
    } else if (stream.name() == "QTheta") {
      daisy->setQTheta(readInt(stream));
    } else if (stream.name() == "QHist") {
      daisy->setQHist(readInt(stream));
    } else if (stream.name() == "Norm") {
      daisy->setNorm(stream.readElementText());
    } else if (stream.name() == "Interpolation") {
      daisy->setInterpolation(readBoolean(stream));
    } else if (stream.name() == "UseOrientation") {
      daisy->setUseOrientation(readBoolean(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFAST(QXmlStreamReader &stream, Fast *fast) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Threshold") {
      fast->setThreshold(readInt(stream));
    } else if (stream.name() == "NonmaxSuppression") {
      fast->setNonmaxSuppression(readBoolean(stream));
    } else if (stream.name() == "DetectorType") {
      fast->setDetectorType(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readFREAK(QXmlStreamReader &stream, Freak *freak) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "OrientationNormalized") {
      freak->setOrientationNormalized(readBoolean(stream));
    } else if (stream.name() == "ScaleNormalized") {
      freak->setScaleNormalized(readBoolean(stream));
    } else if (stream.name() == "PatternScale") {
      freak->setPatternScale(readDouble(stream));
    } else if (stream.name() == "Octaves") {
      freak->setOctaves(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readGFTT(QXmlStreamReader &stream, Gftt *gftt) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "MaxFeatures") {
      gftt->setMaxFeatures(readInt(stream));
    } else if (stream.name() == "QualityLevel") {
      gftt->setQualityLevel(readDouble(stream));
    } else if (stream.name() == "Threshold") {
      gftt->setMinDistance(readDouble(stream));
    } else if (stream.name() == "BlockSize") {
      gftt->setBlockSize(readInt(stream));
    } else if (stream.name() == "HarrisDetector") {
      gftt->setHarrisDetector(readBoolean(stream));
    } else if (stream.name() == "K") {
      gftt->setK(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}



void ProjectControllerImp::readHOG(QXmlStreamReader &stream, Hog *hog) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "WinSize") {
      hog->setWinSize(readSize(stream));
    } else if (stream.name() == "BlockSize") {
      hog->setBlockSize(readSize(stream));
    } else if (stream.name() == "BlockStride") {
      hog->setBlockStride(readSize(stream));
    } else if (stream.name() == "CellSize") {
      hog->setCellSize(readSize(stream));
    } else if (stream.name() == "Nbins") {
      hog->setNbins(readInt(stream));
    } else if (stream.name() == "DerivAperture") {
      hog->setDerivAperture(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readKAZE(QXmlStreamReader &stream, Kaze *kaze) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "ExtendedDescriptor") {
      kaze->setExtendedDescriptor(readBoolean(stream));
    } else if (stream.name() == "Upright") {
      kaze->setUprightDescriptor(readBoolean(stream));
    } else if (stream.name() == "Threshold") {
      kaze->setThreshold(readDouble(stream));
    } else if (stream.name() == "Octaves") {
      kaze->setOctaves(readInt(stream));
    } else if (stream.name() == "OctaveLayers") {
      kaze->setOctaveLayers(readInt(stream));
    } else if (stream.name() == "Diffusivity") {
      kaze->setDiffusivity(stream.readElementText());
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readLATCH(QXmlStreamReader &stream, Latch *latch) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Bytes") {
      latch->setBytes(stream.readElementText());
    } else if (stream.name() == "RotationInvariance") {
      latch->setRotationInvariance(readBoolean(stream));
    } else if (stream.name() == "HalfSsdSize") {
      latch->setHalfSsdSize(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readLUCID(QXmlStreamReader &stream, Lucid *lucid) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "LucidKernel") {
      lucid->setLucidKernel(readInt(stream));
    } else if (stream.name() == "BlurKernel") {
      lucid->setBlurKernel(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readMSD(QXmlStreamReader &stream, Msd *msd) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "ThresholdSaliency") {
      msd->setThresholdSaliency(readDouble(stream));
    } else if (stream.name() == "PatchRadius") {
      msd->setPatchRadius(readInt(stream));
    } else if (stream.name() == "Knn") {
      msd->setKNN(readInt(stream));
    } else if (stream.name() == "SearchAreaRadius") {
      msd->setSearchAreaRadius(readInt(stream));
    } else if (stream.name() == "ScaleFactor") {
      msd->setScaleFactor(readDouble(stream));
    } else if (stream.name() == "NMSRadius") {
      msd->setNMSRadius(readInt(stream));
    } else if (stream.name() == "NScales") {
      msd->setNScales(readInt(stream));
    } else if (stream.name() == "NMSScaleRadius") {
      msd->setNMSScaleRadius(readInt(stream));
    } else if (stream.name() == "ComputeOrientation") {
      msd->setComputeOrientation(readBoolean(stream));
    } else if (stream.name() == "AffineMSD") {
      msd->setAffineMSD(readBoolean(stream));
    } else if (stream.name() == "AffineTilts") {
      msd->setAffineTilts(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readMSER(QXmlStreamReader &stream, Mser *mser) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "Delta") {
      mser->setDelta(readInt(stream));
    } else if (stream.name() == "MinArea") {
      mser->setMinArea(readInt(stream));
    } else if (stream.name() == "MaxArea") {
      mser->setMaxArea(readInt(stream));
    } else if (stream.name() == "MaxVariation") {
      mser->setMaxVariation(readDouble(stream));
    } else if (stream.name() == "MinDiversity") {
      mser->setMinDiversity(readDouble(stream));
    } else if (stream.name() == "MaxEvolution") {
      mser->setMaxEvolution(readInt(stream));
    } else if (stream.name() == "AreaThreshold") {
      mser->setAreaThreshold(readInt(stream));
    } else if (stream.name() == "MinMargin") {
      mser->setMinMargin(readDouble(stream));
    } else if (stream.name() == "EdgeBlurSize") {
      mser->setEdgeBlurSize(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readORB(QXmlStreamReader &stream, Orb *orb) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "FeaturesNumber") {
      orb->setFeaturesNumber(readInt(stream));
    } else if (stream.name() == "ScaleFactor") {
      orb->setScaleFactor(readDouble(stream));
    } else if (stream.name() == "LevelsNumber") {
      orb->setLevelsNumber(readInt(stream));
    } else if (stream.name() == "EdgeThreshold") {
      orb->setEdgeThreshold(readInt(stream));
    } else if (stream.name() == "Wta_k") {
      orb->setWTA_K(readInt(stream));
    } else if (stream.name() == "ScoreType") {
      orb->setScoreType(stream.readElementText());
    } else if (stream.name() == "PatchSize") {
      orb->setPatchSize(readInt(stream));
    } else if (stream.name() == "FastThreshold") {
      orb->setFastThreshold(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readSIFT(QXmlStreamReader &stream, Sift *sift) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "FeaturesNumber") {
      sift->setFeaturesNumber(readInt(stream));
    } else if (stream.name() == "OctaveLayers") {
      sift->setOctaveLayers(readInt(stream));
    } else if (stream.name() == "ContrastThreshold") {
      sift->setContrastThreshold(readDouble(stream));
    } else if (stream.name() == "EdgeThreshold") {
      sift->setEdgeThreshold(readDouble(stream));
    } else if (stream.name() == "Sigma") {
      sift->setSigma(readDouble(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readSTAR(QXmlStreamReader &stream, Star *star) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "MaxSize") {
      star->setMaxSize(readInt(stream));
    } else if (stream.name() == "ResponseThreshold") {
      star->setResponseThreshold(readInt(stream));
    } else if (stream.name() == "LineThresholdProjected") {
      star->setLineThresholdProjected(readInt(stream));
    } else if (stream.name() == "LineThresholdBinarized") {
      star->setLineThresholdBinarized(readInt(stream));
    } else if (stream.name() == "SuppressNonmaxSize") {
      star->setSuppressNonmaxSize(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readSURF(QXmlStreamReader &stream, Surf *surf) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "HessianThreshold") {
      surf->setHessianThreshold(readDouble(stream));
    } else if (stream.name() == "Octaves") {
      surf->setOctaves(readInt(stream));
    } else if (stream.name() == "OctaveLayers") {
      surf->setOctaveLayers(readInt(stream));
    } else if (stream.name() == "ExtendedDescriptor") {
      surf->setExtendedDescriptor(readBoolean(stream));
    } else if (stream.name() == "RotatedFeatures") {
      surf->setUpright(readBoolean(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::readVGG(QXmlStreamReader &stream, Vgg *vgg) const
{
  while (stream.readNextStartElement()) {
    if (stream.name() == "DescriptorType") {
      vgg->setDescriptorType(stream.readElementText());
    } else if (stream.name() == "ScaleFactor") {
      vgg->setScaleFactor(readDouble(stream));
    } else if (stream.name() == "Sigma") {
      vgg->setSigma(readDouble(stream));
    } else if (stream.name() == "UseNormalizeDescriptor") {
      vgg->setUseNormalizeDescriptor(readBoolean(stream));
    } else if (stream.name() == "UseNormalizeImage") {
      vgg->setUseNormalizeImage(readBoolean(stream));
    } else if (stream.name() == "UseScaleOrientation") {
      vgg->setUseScaleOrientation(readBoolean(stream));
    } else
      stream.skipCurrentElement();
  }
}

void ProjectControllerImp::writeVersion(QXmlStreamWriter &stream, const QString &version) const
{
  stream.writeAttribute("version", version);
}

void ProjectControllerImp::writeGeneral(QXmlStreamWriter &stream, const Project &prj) const
{
  stream.writeStartElement("General");
  {
    stream.writeTextElement("Name", prj.name());
    stream.writeTextElement("ProjectFolder", prj.projectFolder());
    stream.writeTextElement("Description", prj.description());
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeImages(QXmlStreamWriter &stream, const Project &prj) const
{
  stream.writeStartElement("Images");
  {
    for (auto it = prj.imageBegin(); it != prj.imageEnd(); it++){
      writeImage(stream, (*it).get());
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeImage(QXmlStreamWriter &stream, const Image *image) const
{
  stream.writeStartElement("Image");
  {
    stream.writeTextElement("File", image->path());
    stream.writeTextElement("LongitudeExif", QString::number(image->longitudeExif()));
    stream.writeTextElement("LatitudeExif", QString::number(image->latitudeExif()));
    stream.writeTextElement("AltitudeExif", QString::number(image->altitudeExif()));
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeGroundTruth(QXmlStreamWriter &stream, const QString &groundTruth) const
{
  stream.writeTextElement("GroundTruth", groundTruth);
}

void ProjectControllerImp::writeSessions(QXmlStreamWriter &stream, const Project &prj) const
{
  stream.writeStartElement("Sessions");
  {
    for (auto it = prj.sessionBegin(); it != prj.sessionEnd(); it++){
      Session *session = (*it).get();
      bool bSessionActive = prj.currentSession()->name().compare(session->name()) == 0;
      writeSession(stream, session, bSessionActive);
    }
  }
  stream.writeEndElement();
}


void ProjectControllerImp::writeSession(QXmlStreamWriter &stream, Session *session, bool activeSession) const
{
  stream.writeStartElement("Session");
  {

    if (activeSession){
      stream.writeAttribute("active", "true");
    }

    writeSessionName(stream, session->name());
    writeSessionDescription(stream, session->description());
    writeSessionMaxImageSize(stream, session->maxImageSize());
    writePreprocess(stream, session);
    writeFeatures(stream, session);
    writeMatches(stream, session);
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeSessionName(QXmlStreamWriter &stream, const QString &name) const
{
  stream.writeTextElement("Name", name);
}

void ProjectControllerImp::writeSessionDescription(QXmlStreamWriter &stream, const QString &description) const
{
  stream.writeTextElement("Description", description);
}

void ProjectControllerImp::writeSessionMaxImageSize(QXmlStreamWriter &stream, int maxImageSize) const
{
  stream.writeTextElement("MaxImageSize", QString::number(maxImageSize));
}

void ProjectControllerImp::writePreprocess(QXmlStreamWriter &stream, Session *session) const
{
  if (Preprocess *preprocess = session->preprocess().get()){
    stream.writeStartElement("Preprocess");

    writePreprocessMethod(stream, preprocess);
    writePreprocessedImages(stream, session->preprocessImages());

    stream.writeEndElement();
  }
}

void ProjectControllerImp::writePreprocessMethod(QXmlStreamWriter &stream, Preprocess *preprocess) const
{
  if (preprocess->type() == Preprocess::Type::acebsf){
    writeACEBSF(stream, dynamic_cast<Acebsf *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::clahe){
    writeCLAHE(stream, dynamic_cast<Clahe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::cmbfhe){
    writeCMBFHE(stream, dynamic_cast<Cmbfhe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::decolor){
    writeDecolor(stream, dynamic_cast<Decolor *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::dhe){
    writeDHE(stream, dynamic_cast<Dhe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::fahe){
    writeFAHE(stream, dynamic_cast<Fahe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::hmclahe){
    writeHMCLAHE(stream, dynamic_cast<Hmclahe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::lce_bsescs){
    writeLCEBSESCS(stream, dynamic_cast<LceBsescs *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::msrcp){
    writeMSRCP(stream, dynamic_cast<Msrcp *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::noshp){
    writeNOSHP(stream, dynamic_cast<Noshp *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::pohe){
    writePOHE(stream, dynamic_cast<Pohe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::rswhe){
    writeRSWHE(stream, dynamic_cast<Rswhe *>(preprocess));
  } else if (preprocess->type() == Preprocess::Type::wallis){
    writeWALLIS(stream, dynamic_cast<Wallis *>(preprocess));
  }
}

void ProjectControllerImp::writePreprocessedImages(QXmlStreamWriter &stream, const std::vector<QString> &preprocessImages) const
{
  stream.writeStartElement("PreprocessedImages");
  {
    for (auto preprocess_image : preprocessImages){
      stream.writeTextElement("PreprocessedImage", preprocess_image);
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeFeatures(QXmlStreamWriter &stream, Session *session) const
{
  stream.writeStartElement("Features");
  {
    writeFeatureDetector(stream, session->detector().get());
    writeFeatureExtractor(stream, session->descriptor().get());
    writeFeaturesFiles(stream, session->features());
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeFeatureDetector(QXmlStreamWriter &stream, Feature *detector) const
{
  if (detector){
    stream.writeStartElement("Detector");

    if (detector->type() == Feature::Type::agast){
      writeAGAST(stream, dynamic_cast<Agast *>(detector));
    } else if (detector->type() == Feature::Type::akaze){
      writeAKAZE(stream, dynamic_cast<Akaze *>(detector));
    } else if(detector->type() == Feature::Type::asift) {
      writeASIFT(stream, dynamic_cast<ASift *>(detector));
    } else if (detector->type() == Feature::Type::brisk){
      writeBRISK(stream, dynamic_cast<Brisk *>(detector));
    } else if(detector->type() == Feature::Type::d2net) {
      writeD2NET(stream, dynamic_cast<D2Net *>(detector));
    } else if(detector->type() == Feature::Type::fast) {
      writeFAST(stream, dynamic_cast<Fast *>(detector));
    } else if (detector->type() == Feature::Type::gftt){
      writeGFTT(stream, dynamic_cast<Gftt *>(detector));
    } else if (detector->type() == Feature::Type::kaze){
      writeKAZE(stream, dynamic_cast<Kaze *>(detector));
    } else if (detector->type() == Feature::Type::msd){
      writeMSD(stream, dynamic_cast<Msd *>(detector));
    } else if (detector->type() == Feature::Type::mser){
      writeMSER(stream, dynamic_cast<Mser *>(detector));
    } else if (detector->type() == Feature::Type::orb){
      writeORB(stream, dynamic_cast<Orb *>(detector));
    } else if (detector->type() == Feature::Type::sift){
      writeSIFT(stream, dynamic_cast<Sift *>(detector));
    } else if (detector->type() == Feature::Type::star){
      writeSTAR(stream, dynamic_cast<Star *>(detector));
    } else if (detector->type() == Feature::Type::surf){
      writeSURF(stream, dynamic_cast<Surf *>(detector));
    }

    stream.writeEndElement(); // Detector
  }
}

void ProjectControllerImp::writeFeatureExtractor(QXmlStreamWriter &stream, Feature *descriptor) const
{
  if (descriptor){
    stream.writeStartElement("Descriptor");

    if (descriptor->type() == Feature::Type::akaze){
      writeAKAZE(stream, dynamic_cast<Akaze *>(descriptor));
    } else if(descriptor->type() == Feature::Type::asift) {
      writeASIFT(stream, dynamic_cast<ASift *>(descriptor));
    } else if (descriptor->type() == Feature::Type::brief){
      writeBRIEF(stream, dynamic_cast<Brief *>(descriptor));
    } else if (descriptor->type() == Feature::Type::brisk){
      writeBRISK(stream, dynamic_cast<Brisk *>(descriptor));
    } else if (descriptor->type() == Feature::Type::daisy){
      writeDAISY(stream, dynamic_cast<Daisy *>(descriptor));
    } else if (descriptor->type() == Feature::Type::d2net) {
      writeD2NET(stream, dynamic_cast<D2Net *>(descriptor));
    } else if (descriptor->type() == Feature::Type::freak){
      writeFREAK(stream, dynamic_cast<Freak *>(descriptor));
    } else if (descriptor->type() == Feature::Type::hog){
      writeHOG(stream, dynamic_cast<Hog *>(descriptor));
    } else if (descriptor->type() == Feature::Type::kaze){
      writeKAZE(stream, dynamic_cast<Kaze *>(descriptor));
    } else if (descriptor->type() == Feature::Type::latch){
      writeLATCH(stream, dynamic_cast<Latch *>(descriptor));
    } else if (descriptor->type() == Feature::Type::lucid){
      writeLUCID(stream, dynamic_cast<Lucid *>(descriptor));
    } else if (descriptor->type() == Feature::Type::lss){
      writeLSS(stream, dynamic_cast<Lss *>(descriptor));
    }else if (descriptor->type() == Feature::Type::orb){
      writeORB(stream, dynamic_cast<Orb *>(descriptor));
    } else if (descriptor->type() == Feature::Type::sift){
      writeSIFT(stream, dynamic_cast<Sift *>(descriptor));
    } else if (descriptor->type() == Feature::Type::surf){
      writeSURF(stream, dynamic_cast<Surf *>(descriptor));
    }

    stream.writeEndElement(); // Descriptor
  }
}

void ProjectControllerImp::writeFeaturesFiles(QXmlStreamWriter &stream, const std::vector<QString> &features) const
{
  stream.writeStartElement("Files");
  {
    for (auto &feat_file : features){
      stream.writeTextElement("FeatFile", feat_file);
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeMatches(QXmlStreamWriter &stream, Session *session) const
{
  stream.writeStartElement("Matches");
  {
    writeMatchingMethod(stream, session->matchingMethod().get());
    writeMatchingStrategy(stream, session->matchingStrategy().get());
    writeMatchingImages(stream, session->matches());

    stream.writeTextElement("PassPoints", session->passPoints());

  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeMatchingMethod(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const
{
  stream.writeStartElement("MatchingMethod");
  {
    if (matchingMethod && matchingMethod->type() == MatchingMethod::Type::flann){
      writeFlann(stream, matchingMethod);
    } else if (matchingMethod && matchingMethod->type() == MatchingMethod::Type::brute_force){
      writeBruteForceMatching(stream, matchingMethod);
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeFlann(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const
{
  stream.writeStartElement("Flann");
  FlannMatcher *flann = dynamic_cast<FlannMatcher *>(matchingMethod);
  FlannMatcherProperties::Index index = flann->index();
  QString s_index = "KDTree";
  if (index == FlannMatcherProperties::Index::kdtree) {
    s_index = "KDTree";
  } else if (index == FlannMatcherProperties::Index::lsh) {
    s_index = "LSH";
  }
  stream.writeTextElement("Index", s_index);
  stream.writeEndElement();
}

void ProjectControllerImp::writeBruteForceMatching(QXmlStreamWriter &stream, MatchingMethod *matchingMethod) const
{
  stream.writeStartElement("BruteForceMatcher");
  BruteForceMatcher *bf = dynamic_cast<BruteForceMatcher *>(matchingMethod);
  BruteForceMatcher::Norm norm = bf->normType();
  QString s_norm = "NORM_L2";
  if (norm == BruteForceMatcherProperties::Norm::l1) {
    s_norm = "NORM_L1";
  } else if (norm == BruteForceMatcherProperties::Norm::l2) {
    s_norm = "NORM_L2";
  } else if (norm == BruteForceMatcherProperties::Norm::hamming) {
    s_norm = "NORM_HAMMING";
  } else if (norm == BruteForceMatcherProperties::Norm::hamming2) {
    s_norm = "NORM_HAMMING2";
  }
  stream.writeTextElement("NORM", s_norm);
  stream.writeEndElement();
}

void ProjectControllerImp::writeMatchingStrategy(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const
{
  stream.writeStartElement("MatchingStrategy");
  {
    if (matchingStrategy && matchingStrategy->strategy() == MatchingStrategy::Strategy::robust_matching){
      writeRobustMatching(stream, matchingStrategy);
    } else if (matchingStrategy && matchingStrategy->strategy() == MatchingStrategy::Strategy::gms){
      writeGms(stream, matchingStrategy);
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeRobustMatching(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const
{
  stream.writeStartElement("RobustMatcher");
  {
    RobustMatcher *robustMatcher = dynamic_cast<RobustMatcher *>(matchingStrategy);
    writeRobustMatchingRatio(stream, robustMatcher);
    writeRobustMatchingCrossCheck(stream, robustMatcher);
    writeRobustMatchingGeometricTest(stream, robustMatcher); // GeometricTest
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeRobustMatchingCrossCheck(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const
{
  stream.writeTextElement("CrossCheck", robustMatcher->crossCheck() ? "true" : "false");
}

void ProjectControllerImp::writeRobustMatchingRatio(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const
{
  stream.writeTextElement("Ratio", QString::number(robustMatcher->ratio()));
}

void ProjectControllerImp::writeRobustMatchingGeometricTest(QXmlStreamWriter &stream,
                                                            RobustMatcher *robustMatcher) const
{
  stream.writeStartElement("GeometricTest");
  {
    tl::GeometricTest::Type type = robustMatcher->geometricTest()->type();
    if (type == tl::GeometricTest::Type::homography_all_points ||
        type == tl::GeometricTest::Type::homography_ransac ||
        type == tl::GeometricTest::Type::homography_lmeds ||
        type == tl::GeometricTest::Type::homography_rho ||
        type == tl::GeometricTest::Type::homography_usac) {
      writeRobustMatchingGeometricTestHomographyMatrix(stream, robustMatcher);
    } else if(type == tl::GeometricTest::Type::fundamental_seven_points ||
              type == tl::GeometricTest::Type::fundamental_eight_points ||
              type == tl::GeometricTest::Type::fundamental_ransac ||
              type == tl::GeometricTest::Type::fundamental_lmeds ||
              type == tl::GeometricTest::Type::fundamental_usac) {
      writeRobustMatchingGeometricTestFundamentalMatrix(stream, robustMatcher);
    } else {
      writeRobustMatchingGeometricTestEssentialMatrix(stream, robustMatcher);
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeRobustMatchingGeometricTestHomographyMatrix(QXmlStreamWriter &stream, 
                                                                            RobustMatcher *robustMatcher) const
{
  stream.writeStartElement("HomographyMatrix");
  {
    QString type;
    std::shared_ptr<tl::GeometricTest> geometric_test = robustMatcher->geometricTest();
    tl::GeometricTest::Type test_type = geometric_test->type();
    switch(test_type) {
      case tl::GeometricTest::Type::homography_all_points:
        type = "all_points";
        break;
      case tl::GeometricTest::Type::homography_ransac:
        type = "ransac";
        break;
      case tl::GeometricTest::Type::homography_lmeds:
        type = "lmeds";
        break;
      case tl::GeometricTest::Type::homography_rho:
        type = "rho";
        break;
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR > 4))
      case tl::GeometricTest::Type::homography_usac:
        type = "usac";
        break;
#endif
      default:
        break;
    }

    stream.writeAttribute("Type", type);

    if(test_type == tl::GeometricTest::Type::homography_all_points) {
      const tl::AllPointsTestProperties *properties = static_cast<const tl::AllPointsTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Confidence", QString::number(properties->confidence));
    } else if(test_type == tl::GeometricTest::Type::homography_ransac) {
      const tl::RANSACTestProperties *ransac_test_properties = static_cast<const tl::RANSACTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Distance", QString::number(ransac_test_properties->distance));
      stream.writeTextElement("Confidence", QString::number(ransac_test_properties->confidence));
      stream.writeTextElement("Iterations", QString::number(ransac_test_properties->iterations));
    } else if(test_type == tl::GeometricTest::Type::homography_lmeds) {
      const tl::LMedsTestProperties *lmeds_test_properties = static_cast<const tl::LMedsTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Confidence", QString::number(lmeds_test_properties->confidence));
      stream.writeTextElement("Iterations", QString::number(lmeds_test_properties->iterations));
    } else if(test_type == tl::GeometricTest::Type::homography_rho) {
      const tl::RHOTestProperties *rho_test_properties = static_cast<const tl::RHOTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Distance", QString::number(rho_test_properties->distance));
      stream.writeTextElement("Confidence", QString::number(rho_test_properties->confidence));
    }
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR > 4))
    else if(test_type == tl::GeometricTest::Type::homography_usac) {
      const tl::UsacTestProperties *usac_test_properties = static_cast<const tl::UsacTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Confidence", QString::number(usac_test_properties->confidence));
      stream.writeTextElement("IsParallel", usac_test_properties->isParallel ? "true" : "false");
      stream.writeTextElement("Iterations", QString::number(usac_test_properties->loIterations));
      //BOOST_CHECK_EQUAL(cv::LocalOptimMethod::LOCAL_OPTIM_INNER_LO, usac_test_properties->loMethod);
      stream.writeTextElement("SampleSize", QString::number(usac_test_properties->loSampleSize));
      stream.writeTextElement("MaxIters", QString::number(usac_test_properties->maxIterations));
      //BOOST_CHECK_EQUAL(cv::NeighborSearchMethod::NEIGH_GRID, usac_test_properties->neighborsSearch);
      //BOOST_CHECK_EQUAL(0, usac_test_properties->randomGeneratorState);
      //BOOST_CHECK_EQUAL(cv::SamplingMethod::SAMPLING_UNIFORM, usac_test_properties->sampler);
      //BOOST_CHECK_EQUAL(cv::ScoreMethod::SCORE_METHOD_MSAC, usac_test_properties->score);
      //BOOST_CHECK_EQUAL(1.5, usac_test_properties->threshold);
    }
#endif

  }

  stream.writeEndElement();
}

void ProjectControllerImp::writeRobustMatchingGeometricTestFundamentalMatrix(QXmlStreamWriter &stream,
                                                                             RobustMatcher *robustMatcher) const
{
  stream.writeStartElement("FundamentalMatrix");
  {
    QString type;
    std::shared_ptr<tl::GeometricTest> geometric_test = robustMatcher->geometricTest();
    tl::GeometricTest::Type test_type = geometric_test->type();
    switch(test_type) {
      case tl::GeometricTest::Type::fundamental_seven_points:
        type = "seven_points";
        break;
      case tl::GeometricTest::Type::fundamental_eight_points:
        type = "eight_points";
        break;
      case tl::GeometricTest::Type::fundamental_ransac:
        type = "ransac";
        break;
      case tl::GeometricTest::Type::fundamental_lmeds:
        type = "lmeds";
        break;
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR > 4))
      case tl::GeometricTest::Type::fundamental_usac:
        type = "usac";
        break;
#endif
      default:
        break;
    }

    stream.writeAttribute("Type", type);

    if (test_type == tl::GeometricTest::Type::fundamental_ransac) {
      const tl::RANSACTestProperties *ransac_test_properties = static_cast<const tl::RANSACTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Distance", QString::number(ransac_test_properties->distance));
      stream.writeTextElement("Confidence", QString::number(ransac_test_properties->confidence));
      stream.writeTextElement("Iterations", QString::number(ransac_test_properties->iterations));
    } else if (test_type == tl::GeometricTest::Type::fundamental_lmeds) {
      const tl::LMedsTestProperties *lmeds_test_properties = static_cast<const tl::LMedsTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Confidence", QString::number(lmeds_test_properties->confidence));
      stream.writeTextElement("Iterations", QString::number(lmeds_test_properties->iterations));
    }
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR > 4))
    else if (test_type == tl::GeometricTest::Type::fundamental_usac) {
      const tl::UsacTestProperties *usac_test_properties = static_cast<const tl::UsacTestProperties *>(geometric_test->properties());
      stream.writeTextElement("Confidence", QString::number(usac_test_properties->confidence));
      stream.writeTextElement("IsParallel", usac_test_properties->isParallel ? "true" : "false");
      stream.writeTextElement("Iterations", QString::number(usac_test_properties->loIterations));
      //BOOST_CHECK_EQUAL(cv::LocalOptimMethod::LOCAL_OPTIM_INNER_LO, usac_test_properties->loMethod);
      stream.writeTextElement("SampleSize", QString::number(usac_test_properties->loSampleSize));
      stream.writeTextElement("MaxIters", QString::number(usac_test_properties->maxIterations));
      //BOOST_CHECK_EQUAL(cv::NeighborSearchMethod::NEIGH_GRID, usac_test_properties->neighborsSearch);
      //BOOST_CHECK_EQUAL(0, usac_test_properties->randomGeneratorState);
      //BOOST_CHECK_EQUAL(cv::SamplingMethod::SAMPLING_UNIFORM, usac_test_properties->sampler);
      //BOOST_CHECK_EQUAL(cv::ScoreMethod::SCORE_METHOD_MSAC, usac_test_properties->score);
      //BOOST_CHECK_EQUAL(1.5, usac_test_properties->threshold);
    }
#endif

  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeRobustMatchingGeometricTestEssentialMatrix(QXmlStreamWriter &stream, RobustMatcher *robustMatcher) const
{
  stream.writeStartElement("EssentialMatrix");
  {
    //RobustMatcher::EssentialComputeMethod ecm = robustMatcher->essentialComputeMethod();
    //if (ecm == RobustMatcher::EssentialComputeMethod::ransac){
    //  stream.writeTextElement("ComputeMethod", "RANSAC");
    //  stream.writeTextElement("Distance", QString::number(robustMatcher->distance()));
    //} else if (ecm == RobustMatcher::EssentialComputeMethod::lmeds){
    //  stream.writeTextElement("ComputeMethod", "LMedS");
    //}
    //stream.writeTextElement("Confidence", QString::number(robustMatcher->confidence()));
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeGms(QXmlStreamWriter &stream, MatchingStrategy *matchingStrategy) const
{
  stream.writeStartElement("GMS");
  {
    Gms *gms = dynamic_cast<Gms *>(matchingStrategy);
    stream.writeTextElement("Scale", gms->scale() ? "true" : "false");
    stream.writeTextElement("Rotation", gms->rotation() ? "true" : "false");
    stream.writeTextElement("Ratio", QString::number(gms->threshold()));
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeMatchingImages(QXmlStreamWriter &stream, const std::map<QString, std::vector<std::pair<QString, QString> > > &matches) const
{
  stream.writeStartElement("Images");
  {
    for (auto &matches : matches){

      stream.writeStartElement("Image");
      {
        stream.writeTextElement("Name", matches.first);

        stream.writeStartElement("Pairs");
        {
          for (size_t i = 0; i < matches.second.size(); i++){

            stream.writeStartElement("Pair");
            {
              stream.writeTextElement("Name", matches.second[i].first);
              stream.writeTextElement("File", matches.second[i].second);
            }
            stream.writeEndElement();  // Pair
          }
        }
        stream.writeEndElement();  // Pairs

      }
      stream.writeEndElement();  // Image
    }
  }
  stream.writeEndElement();
}

void ProjectControllerImp::writeACEBSF(QXmlStreamWriter &stream, Acebsf *acebsf) const
{
  stream.writeStartElement("Acebsf");
  {
    stream.writeStartElement("BlockSize");
    stream.writeTextElement("Width", QString::number(acebsf->blockSize().width()));
    stream.writeTextElement("Height", QString::number(acebsf->blockSize().height()));
    stream.writeEndElement(); // BlockSize
    stream.writeTextElement("L", QString::number(acebsf->l()));
    stream.writeTextElement("K1", QString::number(acebsf->k1()));
    stream.writeTextElement("K2", QString::number(acebsf->k2()));
  }
  stream.writeEndElement(); // Acebsf
}

void ProjectControllerImp::writeCLAHE(QXmlStreamWriter &stream, Clahe *clahe) const
{
  stream.writeStartElement("Clahe");
  {
    stream.writeTextElement("ClipLimit", QString::number(clahe->clipLimit()));
    stream.writeStartElement("GridSize");
    stream.writeTextElement("Width", QString::number(clahe->tilesGridSize().width()));
    stream.writeTextElement("Height", QString::number(clahe->tilesGridSize().height()));
    stream.writeEndElement(); // GridSize
  }
  stream.writeEndElement(); // Clahe
}

void ProjectControllerImp::writeCMBFHE(QXmlStreamWriter &stream, Cmbfhe *cmbfhe) const
{
  stream.writeStartElement("Cmbfhe");
  {
    stream.writeStartElement("blockSize");
    stream.writeTextElement("Width", QString::number(cmbfhe->blockSize().width()));
    stream.writeTextElement("Height", QString::number(cmbfhe->blockSize().height()));
    stream.writeEndElement(); // BlockSize
  }
  stream.writeEndElement(); // Cmbfhe
}

void ProjectControllerImp::writeDecolor(QXmlStreamWriter &stream, Decolor *decolor) const
{
  Q_UNUSED(decolor)
  stream.writeStartElement("Decolor");
  stream.writeEndElement(); // Decolor
}

void ProjectControllerImp::writeDHE(QXmlStreamWriter &stream, Dhe *dhe) const
{
  stream.writeStartElement("Dhe");
  {
    stream.writeTextElement("X", QString::number(dhe->x()));
  }
  stream.writeEndElement(); // Dhe
}

void ProjectControllerImp::writeFAHE(QXmlStreamWriter &stream, Fahe *fahe) const
{
  stream.writeStartElement("Fahe");
  {
    stream.writeStartElement("BlockSize");
    stream.writeTextElement("Width", QString::number(fahe->blockSize().width()));
    stream.writeTextElement("Height", QString::number(fahe->blockSize().height()));
    stream.writeEndElement(); // BlockSize
  }
  stream.writeEndElement(); // Fahe
}

void ProjectControllerImp::writeHMCLAHE(QXmlStreamWriter &stream, Hmclahe *hmclahe) const
{
  stream.writeStartElement("Hmclahe");
  {
    stream.writeStartElement("blockSize");
    stream.writeTextElement("Width", QString::number(hmclahe->blockSize().width()));
    stream.writeTextElement("Height", QString::number(hmclahe->blockSize().height()));
    stream.writeEndElement(); // BlockSize
    stream.writeTextElement("L", QString::number(hmclahe->l()));
    stream.writeTextElement("Phi", QString::number(hmclahe->phi()));
  }
  stream.writeEndElement(); // Hmclahe
}

void ProjectControllerImp::writeLCEBSESCS(QXmlStreamWriter &stream, LceBsescs *lceBsescs) const
{
  stream.writeStartElement("LceBsescs");
  {
    stream.writeStartElement("blockSize");
    stream.writeTextElement("Width", QString::number(lceBsescs->blockSize().width()));
    stream.writeTextElement("Height", QString::number(lceBsescs->blockSize().height()));
    stream.writeEndElement(); // BlockSize
  }
  stream.writeEndElement(); // LceBsescs
}

void ProjectControllerImp::writeMSRCP(QXmlStreamWriter &stream, Msrcp *msrcp) const
{
  stream.writeStartElement("Msrcp");
  {
    stream.writeTextElement("SmallScale", QString::number(msrcp->smallScale()));
    stream.writeTextElement("MidScale", QString::number(msrcp->midScale()));
    stream.writeTextElement("LargeScale", QString::number(msrcp->largeScale()));
  }
  stream.writeEndElement(); // Msrcp
}

void ProjectControllerImp::writeNOSHP(QXmlStreamWriter &stream, Noshp *noshp) const
{
  stream.writeStartElement("Noshp");
  {
    stream.writeStartElement("blockSize");
    stream.writeTextElement("Width", QString::number(noshp->blockSize().width()));
    stream.writeTextElement("Height", QString::number(noshp->blockSize().height()));
    stream.writeEndElement(); // BlockSize
  }
  stream.writeEndElement(); // Noshp
}

void ProjectControllerImp::writePOHE(QXmlStreamWriter &stream, Pohe *pohe) const
{
  stream.writeStartElement("Pohe");
  {
    stream.writeStartElement("blockSize");
    stream.writeTextElement("Width", QString::number(pohe->blockSize().width()));
    stream.writeTextElement("Height", QString::number(pohe->blockSize().height()));
    stream.writeEndElement(); // BlockSize
  }
  stream.writeEndElement(); // Pohe
}

void ProjectControllerImp::writeRSWHE(QXmlStreamWriter &stream, Rswhe *rswhe) const
{
  stream.writeStartElement("Rswhe");
  {
    stream.writeTextElement("HistogramDivisions", QString::number(rswhe->histogramDivisions()));
    stream.writeTextElement("HistogramCut", QString::number(static_cast<int>(rswhe->histogramCut())));
  }
  stream.writeEndElement(); // Rswhe
}

void ProjectControllerImp::writeWALLIS(QXmlStreamWriter &stream, Wallis *wallis) const
{
  stream.writeStartElement("Wallis");
  {
    stream.writeTextElement("Contrast", QString::number(wallis->contrast()));
    stream.writeTextElement("Brightness", QString::number(wallis->brightness()));
    stream.writeTextElement("ImposedAverage", QString::number(wallis->imposedAverage()));
    stream.writeTextElement("ImposedLocalStdDev", QString::number(wallis->imposedLocalStdDev()));
    stream.writeTextElement("KernelSize", QString::number(wallis->kernelSize()));
  }
  stream.writeEndElement(); // Wallis
}

void ProjectControllerImp::writeAGAST(QXmlStreamWriter &stream, Agast *agast) const
{
  stream.writeStartElement("AGAST");
  {
    stream.writeTextElement("Threshold", QString::number(agast->threshold()));
    stream.writeTextElement("NonmaxSuppression", agast->nonmaxSuppression() ? "true" : "false");
    stream.writeTextElement("DetectorType", agast->detectorType());
  }
  stream.writeEndElement(); // AGAST
}

void ProjectControllerImp::writeAKAZE(QXmlStreamWriter &stream, Akaze *akaze) const
{
  stream.writeStartElement("AKAZE");
  {
    stream.writeTextElement("DescriptorType", akaze->descriptorType());
    stream.writeTextElement("DescriptorSize", QString::number(akaze->descriptorSize()));
    stream.writeTextElement("DescriptorChannels", QString::number(akaze->descriptorChannels()));
    stream.writeTextElement("Threshold", QString::number(akaze->threshold()));
    stream.writeTextElement("Octaves", QString::number(akaze->octaves()));
    stream.writeTextElement("OctaveLayers", QString::number(akaze->octaveLayers()));
    stream.writeTextElement("Diffusivity", akaze->diffusivity());
  }
  stream.writeEndElement(); // AKAZE
}

void ProjectControllerImp::writeASIFT(QXmlStreamWriter &stream, ASift *asift) const
{
  stream.writeStartElement("ASIFT");
  {
    stream.writeTextElement("FeaturesNumber", QString::number(asift->featuresNumber()));
    stream.writeTextElement("OctaveLayers", QString::number(asift->octaveLayers()));
    stream.writeTextElement("ContrastThreshold", QString::number(asift->contrastThreshold()));
    stream.writeTextElement("EdgeThreshold", QString::number(asift->edgeThreshold()));
    stream.writeTextElement("Sigma", QString::number(asift->sigma()));
    stream.writeTextElement("MinTilt", QString::number(asift->minTilt()));
    stream.writeTextElement("MaxTilt", QString::number(asift->maxTilt()));
  }
  stream.writeEndElement(); // SIFT
}

void ProjectControllerImp::writeBOOST(QXmlStreamWriter &stream, Boost *boost) const
{
  stream.writeStartElement("BOOST");
  {
    stream.writeTextElement("DescriptorType", boost->descriptorType());
    stream.writeTextElement("UseOrientation", boost->useOrientation()? "true" : "false");
    stream.writeTextElement("ScaleFactor", QString::number(boost->scaleFactor()));
  }
  stream.writeEndElement(); // BOOST
}

void ProjectControllerImp::writeBRIEF(QXmlStreamWriter &stream, Brief *brief) const
{
  stream.writeStartElement("BRIEF");
  {
    stream.writeTextElement("Bytes", brief->bytes());
    stream.writeTextElement("UseOrientation", brief->useOrientation() ? "true" : "false");
  }
  stream.writeEndElement(); // BRIEF
}

void ProjectControllerImp::writeBRISK(QXmlStreamWriter &stream, Brisk *brisk) const
{
  stream.writeStartElement("BRISK");
  {
    stream.writeTextElement("Threshold", QString::number(brisk->threshold()));
    stream.writeTextElement("Octaves", QString::number(brisk->octaves()));
    stream.writeTextElement("PatternScale", QString::number(brisk->patternScale()));
  }
  stream.writeEndElement(); // BRISK
}

void ProjectControllerImp::writeD2NET(QXmlStreamWriter &stream, D2Net *d2net) const
{
  stream.writeStartElement("D2NET");
  {
    stream.writeTextElement("Multiscale", d2net->multiscale() ? "true" : "false");
  }
  stream.writeEndElement(); // BRIEF
}

void ProjectControllerImp::writeDAISY(QXmlStreamWriter &stream, Daisy *daisy) const
{
  stream.writeStartElement("DAISY");
  {
    stream.writeTextElement("Radius", QString::number(daisy->radius()));
    stream.writeTextElement("QRadius", QString::number(daisy->qRadius()));
    stream.writeTextElement("QTheta", QString::number(daisy->qTheta()));
    stream.writeTextElement("QHist", QString::number(daisy->qHist()));
    stream.writeTextElement("Norm", daisy->norm());
    stream.writeTextElement("Interpolation", daisy->interpolation() ? "true" : "false");
    stream.writeTextElement("UseOrientation", daisy->useOrientation() ? "true" : "false");
  }
  stream.writeEndElement(); // DAISY
}

void ProjectControllerImp::writeFAST(QXmlStreamWriter &stream, Fast *fast) const
{
  stream.writeStartElement("FAST");
  {
    stream.writeTextElement("Threshold", QString::number(fast->threshold()));
    stream.writeTextElement("NonmaxSuppression", fast->nonmaxSuppression() ? "true" : "false");
    stream.writeTextElement("DetectorType", fast->detectorType());
  }
  stream.writeEndElement(); // FAST
}

void ProjectControllerImp::writeFREAK(QXmlStreamWriter &stream, Freak *freak) const
{
  stream.writeStartElement("FREAK");
  {
    stream.writeTextElement("OrientationNormalized", freak->orientationNormalized() ? "true" : "false");
    stream.writeTextElement("ScaleNormalized", freak->scaleNormalized() ? "true" : "false");
    stream.writeTextElement("PatternScale", QString::number(freak->patternScale()));
    stream.writeTextElement("Octaves", QString::number(freak->octaves()));
  }
  stream.writeEndElement(); // FREAK
}

void ProjectControllerImp::writeGFTT(QXmlStreamWriter &stream, Gftt *gftt) const
{
  stream.writeStartElement("GFTT");
  {
    stream.writeTextElement("MaxFeatures", QString::number(gftt->maxFeatures()));
    stream.writeTextElement("QualityLevel", QString::number(gftt->qualityLevel()));
    stream.writeTextElement("MinDistance", QString::number(gftt->minDistance()));
    stream.writeTextElement("BlockSize", QString::number(gftt->blockSize()));
    stream.writeTextElement("HarrisDetector", gftt->harrisDetector() ? "true" : "false");
    stream.writeTextElement("K", QString::number(gftt->k()));
  }
  stream.writeEndElement(); // GFTT
}

void ProjectControllerImp::writeHOG(QXmlStreamWriter &stream, Hog *hog) const
{
  stream.writeStartElement("HOG");
  {
    stream.writeStartElement("WinSize");
    stream.writeTextElement("Width", QString::number(hog->winSize().width()));
    stream.writeTextElement("Height", QString::number(hog->winSize().height()));
    stream.writeEndElement(); // WinSize
    stream.writeStartElement("BlockSize");
    stream.writeTextElement("Width", QString::number(hog->blockSize().width()));
    stream.writeTextElement("Height", QString::number(hog->blockSize().height()));
    stream.writeEndElement(); // BlockSize
    stream.writeStartElement("BlockStride");
    stream.writeTextElement("Width", QString::number(hog->blockStride().width()));
    stream.writeTextElement("Height", QString::number(hog->blockStride().height()));
    stream.writeEndElement(); // BlockStride
    stream.writeStartElement("CellSize");
    stream.writeTextElement("Width", QString::number(hog->cellSize().width()));
    stream.writeTextElement("Height", QString::number(hog->cellSize().height()));
    stream.writeEndElement(); // CellSize
    stream.writeTextElement("Nbins", QString::number(hog->nbins()));
    stream.writeTextElement("DerivAperture", QString::number(hog->derivAperture()));
  }
  stream.writeEndElement(); // HOG
}

void ProjectControllerImp::writeKAZE(QXmlStreamWriter &stream, Kaze *kaze) const
{
  stream.writeStartElement("KAZE");
  {
    stream.writeTextElement("ExtendedDescriptor", kaze->extendedDescriptor() ? "true" : "false");
    stream.writeTextElement("Upright", kaze->uprightDescriptor() ? "true" : "false");
    stream.writeTextElement("Threshold", QString::number(kaze->threshold()));
    stream.writeTextElement("Octaves", QString::number(kaze->octaves()));
    stream.writeTextElement("OctaveLayers", QString::number(kaze->octaveLayers()));
    stream.writeTextElement("Diffusivity", kaze->diffusivity());
  }
  stream.writeEndElement(); // KAZE
}

void ProjectControllerImp::writeLATCH(QXmlStreamWriter &stream, Latch *latch) const
{
  stream.writeStartElement("LATCH");
  {
    stream.writeTextElement("Bytes", latch->bytes());
    stream.writeTextElement("RotationInvariance", latch->rotationInvariance() ? "true" : "false");
    stream.writeTextElement("HalfSsdSize", QString::number(latch->halfSsdSize()));
  }
  stream.writeEndElement(); // LATCH
}

void ProjectControllerImp::writeLUCID(QXmlStreamWriter &stream, Lucid *lucid) const
{
  stream.writeStartElement("LUCID");
  {
    stream.writeTextElement("LucidKernel", QString::number(lucid->lucidKernel()));
    stream.writeTextElement("BlurKernel", QString::number(lucid->blurKernel()));
  }
  stream.writeEndElement(); // LUCID
}

void ProjectControllerImp::writeLSS(QXmlStreamWriter &stream, Lss *lss) const
{
  Q_UNUSED(lss)
  stream.writeStartElement("LSS");
  stream.writeEndElement(); // LSS
}

void ProjectControllerImp::writeMSD(QXmlStreamWriter &stream, Msd *msd) const
{
  stream.writeStartElement("MSD");
  {
    stream.writeTextElement("ThresholdSaliency", QString::number(msd->thresholdSaliency()));
    stream.writeTextElement("PatchRadius", QString::number(msd->patchRadius()));
    stream.writeTextElement("Knn", QString::number(msd->knn()));
    stream.writeTextElement("SearchAreaRadius", QString::number(msd->searchAreaRadius()));
    stream.writeTextElement("ScaleFactor", QString::number(msd->scaleFactor()));
    stream.writeTextElement("NMSRadius", QString::number(msd->NMSRadius()));
    stream.writeTextElement("NScales", QString::number(msd->nScales()));
    stream.writeTextElement("NMSScaleRadius", QString::number(msd->NMSScaleRadius()));
    stream.writeTextElement("ComputeOrientation", msd->computeOrientation() ? "true" : "false");
    stream.writeTextElement("AffineMSD", msd->affineMSD() ? "true" : "false");
    stream.writeTextElement("AffineTilts", QString::number(msd->affineTilts()));
  }
  stream.writeEndElement(); // MSD
}

void ProjectControllerImp::writeMSER(QXmlStreamWriter &stream, Mser *mser) const
{
  stream.writeStartElement("MSER");
  {
    stream.writeTextElement("Delta", QString::number(mser->delta()));
    stream.writeTextElement("MinArea", QString::number(mser->minArea()));
    stream.writeTextElement("MaxArea", QString::number(mser->maxArea()));
    stream.writeTextElement("MaxVariation", QString::number(mser->maxVariation()));
    stream.writeTextElement("MinDiversity", QString::number(mser->minDiversity()));
    stream.writeTextElement("MaxEvolution", QString::number(mser->maxEvolution()));
    stream.writeTextElement("AreaThreshold", QString::number(mser->areaThreshold()));
    stream.writeTextElement("MinMargin", QString::number(mser->minMargin()));
    stream.writeTextElement("EdgeBlurSize", QString::number(mser->edgeBlurSize()));
  }
  stream.writeEndElement(); // MSER
}

void ProjectControllerImp::writeORB(QXmlStreamWriter &stream, Orb *orb) const
{
  stream.writeStartElement("ORB");
  {
    stream.writeTextElement("FeaturesNumber", QString::number(orb->featuresNumber()));
    stream.writeTextElement("ScaleFactor", QString::number(orb->scaleFactor()));
    stream.writeTextElement("LevelsNumber", QString::number(orb->levelsNumber()));
    stream.writeTextElement("EdgeThreshold", QString::number(orb->edgeThreshold()));
    stream.writeTextElement("Wta_k", QString::number(orb->wta_k()));
    stream.writeTextElement("ScoreType", orb->scoreType());
    stream.writeTextElement("PatchSize", QString::number(orb->patchSize()));
    stream.writeTextElement("FastThreshold", QString::number(orb->fastThreshold()));
  }
  stream.writeEndElement(); // ORB
}

void ProjectControllerImp::writeSIFT(QXmlStreamWriter &stream, Sift *sift) const
{
  stream.writeStartElement("SIFT");
  {
    stream.writeTextElement("FeaturesNumber", QString::number(sift->featuresNumber()));
    stream.writeTextElement("OctaveLayers", QString::number(sift->octaveLayers()));
    stream.writeTextElement("ContrastThreshold", QString::number(sift->contrastThreshold()));
    stream.writeTextElement("EdgeThreshold", QString::number(sift->edgeThreshold()));
    stream.writeTextElement("Sigma", QString::number(sift->sigma()));
  }
  stream.writeEndElement(); // SIFT
}

void ProjectControllerImp::writeSTAR(QXmlStreamWriter &stream, Star *star) const
{
  stream.writeStartElement("STAR");
  {
    stream.writeTextElement("MaxSize", QString::number(star->maxSize()));
    stream.writeTextElement("ResponseThreshold", QString::number(star->responseThreshold()));
    stream.writeTextElement("LineThresholdProjected", QString::number(star->lineThresholdProjected()));
    stream.writeTextElement("LineThresholdBinarized", QString::number(star->lineThresholdBinarized()));
    stream.writeTextElement("SuppressNonmaxSize", QString::number(star->suppressNonmaxSize()));
  }
  stream.writeEndElement(); // STAR
}

void ProjectControllerImp::writeSURF(QXmlStreamWriter &stream, Surf *surf) const
{
  stream.writeStartElement("SURF");
  {
    stream.writeTextElement("HessianThreshold", QString::number(surf->hessianThreshold()));
    stream.writeTextElement("Octaves", QString::number(surf->octaves()));
    stream.writeTextElement("OctaveLayers", QString::number(surf->octaveLayers()));
    stream.writeTextElement("ExtendedDescriptor", surf->extendedDescriptor() ? "true" : "false");
    stream.writeTextElement("RotatedFeatures", surf->upright() ? "true" : "false");
  }
  stream.writeEndElement(); // SURF
}

void ProjectControllerImp::writeVGG(QXmlStreamWriter &stream, Vgg *vgg) const
{
  stream.writeStartElement("VGG");
  {
    stream.writeTextElement("DescriptorType", vgg->descriptorType());
    stream.writeTextElement("ScaleFactor", QString::number(vgg->scaleFactor()));
    stream.writeTextElement("Sigma", QString::number(vgg->sigma()));
    stream.writeTextElement("UseNormalizeDescriptor", vgg->useNormalizeDescriptor() ? "true" : "false");
    stream.writeTextElement("UseNormalizeImage", vgg->useNormalizeImage() ? "true" : "false");
    stream.writeTextElement("UseScaleOrientation", vgg->useScaleOrientation() ? "true" : "false");
  }
  stream.writeEndElement(); // VGG
}

QSize ProjectControllerImp::readSize(QXmlStreamReader &stream) const
{
  QSize blockSize;
  while (stream.readNextStartElement()) {
    if (stream.name() == "Width") {
      blockSize.setWidth(readInt(stream));
    } else if (stream.name() == "Height") {
      blockSize.setHeight(readInt(stream));
    } else
      stream.skipCurrentElement();
  }
  return blockSize;
}

int ProjectControllerImp::readInt(QXmlStreamReader &stream) const
{
  return stream.readElementText().toInt();
}

double ProjectControllerImp::readDouble(QXmlStreamReader &stream) const
{
  return stream.readElementText().toDouble();
}

bool ProjectControllerImp::readBoolean(QXmlStreamReader &stream) const
{
  return stream.readElementText().compare("true") == 0 ? true : false;
}

} // namespace photomatch






