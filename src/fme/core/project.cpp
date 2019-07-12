#include "project.h"

#include <QFile>
#include <QFileInfo>
#include <QXmlStreamWriter>

#include <iostream>
#include <fstream>

#define FME_PROJECT_FILE_VERSION "1.0"

namespace fme
{

Project::Project()
  : IProject(),
    mName(""),
    mDescription(""),
    mProjectFolder(""),
    mVersion(FME_PROJECT_FILE_VERSION),
    mCurrentSession(-1)
{
}

QString Project::name() const
{
  return mName;
}

void Project::setName(const QString &name)
{
  mName = name;
}

QString Project::description() const
{
  return mDescription;
}

void Project::setDescription(const QString &description)
{
  mDescription = description;
}

QString Project::projectFolder() const
{
  return mProjectFolder;
}

void Project::setProjectFolder(const QString &dir)
{
  mProjectFolder = dir;
}


QString Project::version() const
{
  return mVersion;
}

void Project::addImage(const std::shared_ptr<Image> &img)
{
  std::shared_ptr<Image> image = findImage(img->path());
  if (image != nullptr) {
    QByteArray ba = img->path().toLocal8Bit();
    /// TODO: mensajes de la aplicación
    //msgWarning("Image %s already in the project", ba.data());
  } else {
    mImages.push_back(img);
  }
}

void Project::deleteImage(const QString &img)
{
  deleteImage(findImageId(img));
}

void Project::deleteImage(size_t imgId)
{
  if (imgId != std::numeric_limits<size_t>().max()){
    mImages.erase(mImages.begin()+ static_cast<long long>(imgId));
  }
}

std::shared_ptr<Image> Project::findImage(const QString &path)
{
  for (auto &image : mImages) {
    if (image->path().compare(path) == 0) {
      return image;
    }
  }
  return nullptr;
}

const std::shared_ptr<Image> Project::findImage(const QString &path) const
{
  for (auto &image : mImages) {
    if (image->path().compare(path) == 0) {
      return image;
    }
  }
  return nullptr;
}

size_t Project::findImageId(const QString &path)
{
  for (size_t i = 0; i < mImages.size(); i++){
    if (mImages[i]->path().compare(path) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

size_t Project::findImageId(const QString &path) const
{
  for (size_t i = 0; i < mImages.size(); i++){
    if (mImages[i]->path().compare(path) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

IProject::image_iterator Project::imageBegin()
{
  return mImages.begin();
}

IProject::image_const_iterator Project::imageBegin() const
{
  return mImages.cbegin();
}

IProject::image_iterator Project::imageEnd()
{
  return mImages.end();
}

IProject::image_const_iterator Project::imageEnd() const
{
  return mImages.cend();
}

size_t Project::imagesCount() const
{
  return mImages.size();
}

void Project::addSession(const QString &name, const QString &description)
{
  std::shared_ptr<Session> session(new Session(name, description));
  addSession(session);
}

void Project::addSession(const std::shared_ptr<Session> &session)
{
  std::shared_ptr<Session> _session = findSession(session->name());
  if (_session != nullptr) {
    QByteArray ba = session->name().toLocal8Bit();
    /// TODO: mensajes de la aplicación
    //msgWarning("Image %s already in the project", ba.data());
  } else {
    mSessions.push_back(session);
    /// Se establece como sesión activa
    mCurrentSession = static_cast<int>(mSessions.size()) - 1;
  }
}

void Project::deleteSession(const QString &sessionName)
{
  deleteSession(findSessionId(sessionName));
}

void Project::deleteSession(size_t sessionId)
{
  if (sessionId != std::numeric_limits<size_t>().max()){
    if (mCurrentSession == static_cast<int>(sessionId)){
      mCurrentSession = mSessions.size() == 1 ? -1 : static_cast<int>(mSessions.size()) - 1;
    }
    mSessions.erase(mSessions.begin()+ static_cast<long long>(sessionId));
  }
}

std::shared_ptr<Session> Project::findSession(const QString &sessionName)
{
  for (auto &session : mSessions) {
    if (session->name().compare(sessionName) == 0) {
      return session;
    }
  }
  return nullptr;
}

const std::shared_ptr<Session> Project::findSession(const QString &sessionName) const
{
  for (auto &session : mSessions) {
    if (session->name().compare(sessionName) == 0) {
      return session;
    }
  }
  return nullptr;
}

size_t Project::findSessionId(const QString &sessionName)
{
  for (size_t i = 0; i < mSessions.size(); i++){
    if (mSessions[i]->name().compare(sessionName) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

size_t Project::findSessionId(const QString &sessionName) const
{
  for (size_t i = 0; i < mSessions.size(); i++){
    if (mSessions[i]->name().compare(sessionName) == 0) {
      return i;
    }
  }
  return std::numeric_limits<size_t>().max();
}

IProject::session_iterator Project::sessionBegin()
{
  return mSessions.begin();
}

IProject::session_const_iterator Project::sessionBegin() const
{
  return mSessions.cbegin();
}

IProject::session_iterator Project::sessionEnd()
{
  return mSessions.end();
}

IProject::session_const_iterator Project::sessionEnd() const
{
  return mSessions.cend();
}

size_t Project::sessionCount() const
{
  return mSessions.size();
}

std::shared_ptr<Session> Project::currentSession()
{
  session_iterator it = mSessions.begin() + mCurrentSession;
  return (*it);
}

const std::shared_ptr<Session> Project::currentSession() const
{
  session_const_iterator it = mSessions.begin() + mCurrentSession;
  return (*it);
}

void Project::setCurrentSession(const QString &sessionName)
{
  size_t id = this->findSessionId(sessionName);
  if (id != std::numeric_limits<size_t>().max()){
    mCurrentSession = static_cast<int>(id);
  }
}

void Project::clear()
{
  mName = "";
  mDescription = "";
  mProjectFolder = "";
  mVersion = FME_PROJECT_FILE_VERSION;
  mImages.resize(0);
  mSessions.resize(0);
  mCurrentSession = -1;
}



std::mutex ProjectRW::sMutex;

ProjectRW::ProjectRW()
 : IProjectRW()
{

}

bool ProjectRW::read(const QString &file, IProject &prj)
{
  std::lock_guard<std::mutex> lck(ProjectRW::sMutex);

  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&input);

    if (xmlReader.readNextStartElement()) {
      if (xmlReader.name() == "FME") {
        while (xmlReader.readNextStartElement()) {
          if (xmlReader.name() == "General") {
            while (xmlReader.readNextStartElement()) {
              if (xmlReader.name() == "Name") {
                prj.setName(xmlReader.readElementText());
              } else if (xmlReader.name() == "ProjectFolder") {
                prj.setProjectFolder(xmlReader.readElementText());
              } else if (xmlReader.name() == "Description") {
                prj.setDescription(xmlReader.readElementText());
              } else
                xmlReader.skipCurrentElement();
            }
          } else if (xmlReader.name() == "Images") {

            while (xmlReader.readNextStartElement()) {

              if (xmlReader.name() == "Image") {
                std::shared_ptr<Image> photo(new Image);
                while (xmlReader.readNextStartElement()) {
                  if (xmlReader.name() == "File") {
                    photo->setPath(xmlReader.readElementText());
                  } else if (xmlReader.name() == "LongitudeExif") {
                    photo->setLongitudeExif(xmlReader.readElementText().toDouble());
                  } else if (xmlReader.name() == "LatitudeExif") {
                    photo->setLatitudeExif(xmlReader.readElementText().toDouble());
                  } else if (xmlReader.name() == "AltitudeExif") {
                    photo->setAltitudeExif(xmlReader.readElementText().toDouble());
                  } else
                    xmlReader.skipCurrentElement();
                }
                prj.addImage(photo);
              } else
                xmlReader.skipCurrentElement();
            }
          } else if (xmlReader.name() == "Sessions") {
            while (xmlReader.readNextStartElement()) {

              if (xmlReader.name() == "Session") {
                std::shared_ptr<Session> session(new Session);
                while (xmlReader.readNextStartElement()) {
                  if (xmlReader.name() == "Name") {
                    session->setName(xmlReader.readElementText());
                  } else if (xmlReader.name() == "Description") {
                    session->setDescription(xmlReader.readElementText());
                  } else
                    xmlReader.skipCurrentElement();
                }
                prj.addSession(session);
              } else
                xmlReader.skipCurrentElement();
            }
          }
        }
      } else {
        xmlReader.raiseError(QObject::tr("Incorrect project file"));
        return true;
      }
    }
  }
  return false;
}

bool ProjectRW::write(const QString &file, const IProject &prj) const
{
  QFileInfo file_info(file);
  QString tmpfile = file_info.path().append(file_info.baseName()).append(".bak");
  std::ifstream  src(file.toStdString().c_str(), std::ios::binary);
  std::ofstream  dst(tmpfile.toStdString().c_str(), std::ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();

  std::lock_guard<std::mutex> lck(ProjectRW::sMutex);

  QFile output(file);
  output.open(QFile::WriteOnly);
  QXmlStreamWriter stream(&output);
  stream.setAutoFormatting(true);
  stream.writeStartDocument();

  stream.writeStartElement("FME");
  {

    stream.writeAttribute("version", prj.version());

    /// General

    stream.writeStartElement("General");
    {
      stream.writeTextElement("Name", prj.name());
      stream.writeTextElement("ProjectFolder", prj.projectFolder());
      stream.writeTextElement("Description", prj.description());
    }
    stream.writeEndElement(); // General

    /// Imagenes
    stream.writeStartElement("Images");
    {
      for (auto it = prj.imageBegin(); it != prj.imageEnd(); it++){
        stream.writeStartElement("Image");
        {
          stream.writeTextElement("File", (*it)->path());
          stream.writeTextElement("LongitudeExif", QString::number((*it)->longitudeExif()));
          stream.writeTextElement("LatitudeExif", QString::number((*it)->latitudeExif()));
          stream.writeTextElement("AltitudeExif", QString::number((*it)->altitudeExif()));
        }
        stream.writeEndElement(); // Image
      }
    }
    stream.writeEndElement();  // Images

    /// Sessions
    stream.writeStartElement("Sessions");
    {
      for (auto it = prj.sessionBegin(); it != prj.sessionEnd(); it++){
        stream.writeStartElement("Session");
        {
          stream.writeTextElement("Name", (*it)->name());
          stream.writeTextElement("Description", (*it)->description());
        }
        stream.writeEndElement(); // Session
      }
    }
    stream.writeEndElement();  // Sessions
  }



  stream.writeEndElement(); // Fme

  output.close();

  std::remove(tmpfile.toStdString().c_str());

  return false;
}

bool ProjectRW::checkOldVersion(const QString &file) const
{
  std::lock_guard<std::mutex> lck(ProjectRW::sMutex);
  bool bUpdateVersion = false;
  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&input);

    if (xmlReader.readNextStartElement()) {
      if (xmlReader.name() == "FME") {
        QString version = "0";
        for (auto &attr : xmlReader.attributes()) {
          if (attr.name().compare(QString("version")) == 0) {
            version = attr.value().toString();
            break;
          }
        }
        if (version.compare(FME_PROJECT_FILE_VERSION) < 0) {
          // Es una versión mas antigua
          bUpdateVersion = true;
        }
      } else
        xmlReader.raiseError(QObject::tr("Incorrect file"));
    }
  }
  return bUpdateVersion;
}

void ProjectRW::oldVersionBak(const QString &file) const
{
  // Versión antigua
  QString version = "0";
  QFile input(file);
  if (input.open(QIODevice::ReadOnly)) {
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&input);

    if (xmlReader.readNextStartElement()) {
      if (xmlReader.name() == "FME") {
        for (auto &attr : xmlReader.attributes()) {
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

} // namespace fme






