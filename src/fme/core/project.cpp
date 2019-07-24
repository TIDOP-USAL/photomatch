#include "project.h"

#include "preprocess.h"

#include "fme/core/settings.h"

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

//size_t Project::findImageId(const QString &path)
//{
//  for (size_t i = 0; i < mImages.size(); i++){
//    if (mImages[i]->path().compare(path) == 0) {
//      return i;
//    }
//  }
//  return std::numeric_limits<size_t>().max();
//}

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

                bool bActive = false;
                for (auto &attr : xmlReader.attributes()) {
                  if (attr.name().compare(QString("active")) == 0) {
                    QString value = attr.value().toString();
                    if (value.compare("1") == 0 || value.compare("true") == 0){
                      bActive = true;
                    }
                    break;
                  }
                }

                while (xmlReader.readNextStartElement()) {
                  if (xmlReader.name() == "Name") {
                    session->setName(xmlReader.readElementText());
                  } else if (xmlReader.name() == "Description") {
                    session->setDescription(xmlReader.readElementText());
                  } else if (xmlReader.name() == "Preprocess") {
                    while (xmlReader.readNextStartElement()) {

                      if (xmlReader.name() == "Clahe") {

                        std::shared_ptr<Clahe> clahe = std::make_shared<Clahe>();
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "ClipLimit") {
                            clahe->setClipLimit(xmlReader.readElementText().toDouble());
                          } else if (xmlReader.name() == "GridSize") {
                            QSize gridSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                gridSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                gridSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            clahe->setTilesGridSize(gridSize);
                          } else
                            xmlReader.skipCurrentElement();

                        }
                        session->setPreprocess(clahe);

                      } else if (xmlReader.name() == "Cmbfhe") {

                        std::shared_ptr<Cmbfhe> cmbfhe(new Cmbfhe);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            cmbfhe->setBlockSize(blockSize);
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(cmbfhe);

                      } else if (xmlReader.name() == "Dhe") {

                        std::shared_ptr<Dhe> dhe = std::make_shared<Dhe>();
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "X") {
                            dhe->setX(xmlReader.readElementText().toInt());
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(dhe);

                      } else if (xmlReader.name() == "Fahe") {

                        std::shared_ptr<Fahe> fahe(new Fahe);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            fahe->setBlockSize(blockSize);
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(fahe);

                      } else if (xmlReader.name() == "Hmclahe") {

                        std::shared_ptr<Hmclahe> hmclahe(new Hmclahe);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            hmclahe->setBlockSize(blockSize);
                          } else if (xmlReader.name() == "L") {
                            hmclahe->setL(xmlReader.readElementText().toDouble());
                          } else if (xmlReader.name() == "Phi") {
                            hmclahe->setPhi(xmlReader.readElementText().toDouble());
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(hmclahe);

                      } else if (xmlReader.name() == "LceBsescs") {

                        std::shared_ptr<LceBsescs> lceBsescs(new LceBsescs);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            lceBsescs->setBlockSize(blockSize);
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(lceBsescs);

                      } else if (xmlReader.name() == "Msrcp") {

                        std::shared_ptr<Msrcp> msrcp = std::make_shared<Msrcp>();
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "SmallScale") {
                            msrcp->setSmallScale(xmlReader.readElementText().toInt());
                          } else if (xmlReader.name() == "MidScale") {
                            msrcp->setMidScale(xmlReader.readElementText().toInt());
                          } else if (xmlReader.name() == "LargeScale") {
                            msrcp->setLargeScale(xmlReader.readElementText().toInt());
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(msrcp);

                      } else if (xmlReader.name() == "Noshp") {

                        std::shared_ptr<Noshp> noshp(new Noshp);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            noshp->setBlockSize(blockSize);
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(noshp);
                      } else if (xmlReader.name() == "Pohe") {

                        std::shared_ptr<Pohe> pohe(new Pohe);
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "BlockSize") {
                            QSize blockSize;
                            while (xmlReader.readNextStartElement()) {
                              if (xmlReader.name() == "Width") {
                                blockSize.setWidth(xmlReader.readElementText().toInt());
                              } else if (xmlReader.name() == "Height") {
                                blockSize.setHeight(xmlReader.readElementText().toInt());
                              } else
                                xmlReader.skipCurrentElement();
                            }
                            pohe->setBlockSize(blockSize);
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(pohe);

                      } else if (xmlReader.name() == "Rswhe") {

                        std::shared_ptr<Rswhe> rswhe = std::make_shared<Rswhe>();
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "HistogramDivisions") {
                            rswhe->setHistogramDivisions(xmlReader.readElementText().toInt());
                          } else if (xmlReader.name() == "HistogramCut") {
                            rswhe->setHistogramCut(static_cast<IRswhe::HistogramCut>(xmlReader.readElementText().toInt()));
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(rswhe);

                      } else if (xmlReader.name() == "Wallis") {

                        std::shared_ptr<Wallis> wallis = std::make_shared<Wallis>();
                        while (xmlReader.readNextStartElement()) {
                          if (xmlReader.name() == "Contrast") {
                            wallis->setContrast(xmlReader.readElementText().toDouble());
                          } else if (xmlReader.name() == "Brightness") {
                            wallis->setBrightness(xmlReader.readElementText().toDouble());
                          } else if (xmlReader.name() == "ImposedAverage") {
                            wallis->setImposedAverage(xmlReader.readElementText().toInt());
                          } else if (xmlReader.name() == "ImposedLocalStdDev") {
                            wallis->setImposedLocalStdDev(xmlReader.readElementText().toInt());
                          } else if (xmlReader.name() == "KernelSize") {
                            wallis->setKernelSize(xmlReader.readElementText().toInt());
                          } else
                            xmlReader.skipCurrentElement();
                        }
                        session->setPreprocess(wallis);

                      } else
                        xmlReader.skipCurrentElement();
                    }
                  } else
                    xmlReader.skipCurrentElement();
                }

                prj.addSession(session);

                if (bActive)
                  prj.setCurrentSession(session->name());

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
          if (prj.currentSession()->name().compare((*it)->name()) == 0){
            stream.writeAttribute("active", "true");
          }

          stream.writeTextElement("Name", (*it)->name());
          stream.writeTextElement("Description", (*it)->description());

          Preprocess *preprocess = (*it)->preprocess().get();
          if (preprocess){
            stream.writeStartElement("Preprocess");

            if (preprocess->type() == Preprocess::Type::clahe){

              IClahe *clahe = dynamic_cast<IClahe *>(preprocess);
              stream.writeStartElement("Clahe");
              {
                stream.writeTextElement("ClipLimit", QString::number(clahe->clipLimit()));
                stream.writeStartElement("GridSize");
                stream.writeTextElement("Width", QString::number(clahe->tilesGridSize().width()));
                stream.writeTextElement("Height", QString::number(clahe->tilesGridSize().height()));
                stream.writeEndElement(); // GridSize
              }
              stream.writeEndElement(); // Clahe

            } else if (preprocess->type() == Preprocess::Type::cmbfhe){

              ICmbfhe *cmbfhe = dynamic_cast<ICmbfhe *>(preprocess);
              stream.writeStartElement("Cmbfhe");
              {
                stream.writeStartElement("blockSize");
                stream.writeTextElement("Width", QString::number(cmbfhe->blockSize().width()));
                stream.writeTextElement("Height", QString::number(cmbfhe->blockSize().height()));
                stream.writeEndElement(); // BlockSize
              }
              stream.writeEndElement(); // Cmbfhe

            } else if (preprocess->type() == Preprocess::Type::dhe){

              IDhe *dhe = dynamic_cast<IDhe *>(preprocess);
              stream.writeStartElement("Dhe");
              {
                stream.writeTextElement("X", QString::number(dhe->x()));
              }
              stream.writeEndElement(); // Dhe

            } else if (preprocess->type() == Preprocess::Type::fahe){

              IFahe *fahe = dynamic_cast<IFahe *>(preprocess);
              stream.writeStartElement("Fahe");
              {
                stream.writeStartElement("BlockSize");
                stream.writeTextElement("Width", QString::number(fahe->blockSize().width()));
                stream.writeTextElement("Height", QString::number(fahe->blockSize().height()));
                stream.writeEndElement(); // BlockSize
              }
              stream.writeEndElement(); // Fahe

            } else if (preprocess->type() == Preprocess::Type::hmclahe){

              IHmclahe *hmclahe = dynamic_cast<IHmclahe *>(preprocess);
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

            } else if (preprocess->type() == Preprocess::Type::lce_bsescs){

              ILceBsescs *lceBsescs = dynamic_cast<ILceBsescs *>(preprocess);
              stream.writeStartElement("LceBsescs");
              {
                stream.writeStartElement("blockSize");
                stream.writeTextElement("Width", QString::number(lceBsescs->blockSize().width()));
                stream.writeTextElement("Height", QString::number(lceBsescs->blockSize().height()));
                stream.writeEndElement(); // BlockSize
              }
              stream.writeEndElement(); // LceBsescs

            } else if (preprocess->type() == Preprocess::Type::msrcp){

              IMsrcp *msrcp = dynamic_cast<IMsrcp *>(preprocess);
              stream.writeStartElement("Msrcp");
              {
                stream.writeTextElement("SmallScale", QString::number(msrcp->smallScale()));
                stream.writeTextElement("MidScale", QString::number(msrcp->midScale()));
                stream.writeTextElement("LargeScale", QString::number(msrcp->largeScale()));
              }
              stream.writeEndElement(); // Msrcp

            } else if (preprocess->type() == Preprocess::Type::noshp){

              INoshp *noshp = dynamic_cast<INoshp *>(preprocess);
              stream.writeStartElement("Noshp");
              {
                stream.writeStartElement("blockSize");
                stream.writeTextElement("Width", QString::number(noshp->blockSize().width()));
                stream.writeTextElement("Height", QString::number(noshp->blockSize().height()));
                stream.writeEndElement(); // BlockSize
              }
              stream.writeEndElement(); // Noshp

            } else if (preprocess->type() == Preprocess::Type::pohe){

              IPohe *pohe = dynamic_cast<IPohe *>(preprocess);
              stream.writeStartElement("Pohe");
              {
                stream.writeStartElement("blockSize");
                stream.writeTextElement("Width", QString::number(pohe->blockSize().width()));
                stream.writeTextElement("Height", QString::number(pohe->blockSize().height()));
                stream.writeEndElement(); // BlockSize
              }
              stream.writeEndElement(); // Pohe

            } else if (preprocess->type() == Preprocess::Type::rswhe){

              IRswhe *rswhe = dynamic_cast<IRswhe *>(preprocess);
              stream.writeStartElement("Rswhe");
              {
                stream.writeTextElement("HistogramDivisions", QString::number(rswhe->histogramDivisions()));
                stream.writeTextElement("HistogramCut", QString::number(static_cast<int>(rswhe->histogramCut())));
              }
              stream.writeEndElement(); // Rswhe

            } else if (preprocess->type() == Preprocess::Type::wallis){

              IWallis *wallis = dynamic_cast<IWallis *>(preprocess);
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

            stream.writeEndElement(); // Preprocess
          }

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






