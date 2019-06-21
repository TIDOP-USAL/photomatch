#include "project.h"

#include <QFile>
#include <QFileInfo>
#include <QXmlStreamWriter>

#include <iostream>
#include <fstream>

#define FME_PROJECT_FILE_VERSION "1.0"

namespace fme
{

Project::Project(IProjectIO *projectIO)
  : IProject(),
    mName(""),
    mDescription(""),
    mPath(""),
    mProjectFolder(""),
    mVersion(FME_PROJECT_FILE_VERSION),
    bUnsavedChanges(false),
    mProjectIO(projectIO)
{
}

Project::Project(IProjectIO *projectIO, const QString &file)
  : IProject(),
    mName(""),
    mDescription(""),
    mPath("file"),
    mProjectFolder(""),
    mVersion(FME_PROJECT_FILE_VERSION),
    bUnsavedChanges(false),
    mProjectIO(projectIO)
{
  load(file);
}

QString Project::name() const
{
  return mName;
}

void Project::setName(const QString &name)
{
  mName = name;
  bUnsavedChanges = true;
}

QString Project::description() const
{
  return mDescription;
}

void Project::setDescription(const QString &description)
{
  mDescription = description;
  bUnsavedChanges = true;
}

QString Project::path() const
{
  return mPath;
}

QString Project::projectFolder() const
{
  return mProjectFolder;
}

void Project::setProjectFolder(const QString &dir)
{
  mProjectFolder = dir;
  bUnsavedChanges = true;
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
  bUnsavedChanges = true;
}

void Project::deleteImage(const QString &img)
{
  size_t id = findImageId(img);
  if (id != std::numeric_limits<size_t>().max()){
    mImages.erase(mImages.begin()+ static_cast<long long>(id));
    bUnsavedChanges = true;
  }
}

void Project::deleteImage(size_t imgId)
{
  if (imgId != std::numeric_limits<size_t>().max()){
    mImages.erase(mImages.begin()+ static_cast<long long>(imgId));
    bUnsavedChanges = true;
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

void Project::load(const QString &file)
{
  mPath = file;
  ///TODO: La lectura y escritura dificultará el testeo. Crear una interfaz ProjectIO para
  /// gestionar esa parte y poder crear una clase para la simulación de la lectura escritura
  /// en los test
  bool err = mProjectIO->read(file, *this);

  bUnsavedChanges = false;

}

void Project::save()
{
  saveAs(mPath);
}

void Project::saveAs(const QString &file)
{

  mPath = file;

  bool err = mProjectIO->write(file, *this);

  bUnsavedChanges = false;
}

bool Project::checkUnsavedChanges() const
{
  return bUnsavedChanges;
}

bool Project::checkOldVersion(const QString &file) const
{
  return false;
}

void Project::oldVersionBak(const QString &file) const
{
}

//bool Project::empty() const
//{
//}

void Project::clear()
{
  mName = "";
  mDescription = "";
  mPath = "";
  mProjectFolder = "";
  mVersion = FME_PROJECT_FILE_VERSION;
  mImages.resize(0);
  bUnsavedChanges = false;
}



std::mutex ProjectIO::sMutex;

ProjectIO::ProjectIO()
 : IProjectIO()
{

}

bool ProjectIO::read(const QString &file, IProject &prj)
{
  std::lock_guard<std::mutex> lck(ProjectIO::sMutex);

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

bool ProjectIO::write(const QString &file, const IProject &prj) const
{
  QFileInfo file_info(file);
  QString tmpfile = file_info.path().append(file_info.baseName()).append(".bak");
  std::ifstream  src(file.toStdString().c_str(), std::ios::binary);
  std::ofstream  dst(tmpfile.toStdString().c_str(), std::ios::binary);
  dst << src.rdbuf();
  src.close();
  dst.close();

  std::lock_guard<std::mutex> lck(ProjectIO::sMutex);

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
  }
  stream.writeEndElement(); // Graphos

  output.close();

  std::remove(tmpfile.toStdString().c_str());

  return false;
}

bool ProjectIO::checkOldVersion(const QString &file) const
{
  std::lock_guard<std::mutex> lck(ProjectIO::sMutex);
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

} // namespace fme






