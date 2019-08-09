#include "project.h"

#include "fme/core/settings.h"

#include "fme/core/features/agast.h"
#include "fme/core/features/akaze.h"
#include "fme/core/features/brief.h"
#include "fme/core/features/brisk.h"
#include "fme/core/features/daisy.h"
#include "fme/core/features/fast.h"
#include "fme/core/features/freak.h"
#include "fme/core/features/gftt.h"
#include "fme/core/features/hog.h"
#include "fme/core/features/latch.h"
#include "fme/core/features/lucid.h"
#include "fme/core/features/msd.h"
#include "fme/core/features/mser.h"
#include "fme/core/features/kaze.h"
#include "fme/core/features/orb.h"
#include "fme/core/features/sift.h"
#include "fme/core/features/star.h"
#include "fme/core/features/surf.h"

#include "fme/core/preprocess/acebsf.h"
#include "fme/core/preprocess/clahe.h"
#include "fme/core/preprocess/cmbfhe.h"
#include "fme/core/preprocess/dhe.h"
#include "fme/core/preprocess/fahe.h"
#include "fme/core/preprocess/hmclahe.h"
#include "fme/core/preprocess/lce_bsescs.h"
#include "fme/core/preprocess/msrcp.h"
#include "fme/core/preprocess/noshp.h"
#include "fme/core/preprocess/pohe.h"
#include "fme/core/preprocess/rswhe.h"
#include "fme/core/preprocess/wallis.h"

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
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "FME") {
        while (stream.readNextStartElement()) {
          if (stream.name() == "General") {
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
          } else if (stream.name() == "Images") {

            while (stream.readNextStartElement()) {

              if (stream.name() == "Image") {
                std::shared_ptr<Image> photo(new Image);
                while (stream.readNextStartElement()) {
                  if (stream.name() == "File") {
                    photo->setPath(stream.readElementText());
                  } else if (stream.name() == "LongitudeExif") {
                    photo->setLongitudeExif(stream.readElementText().toDouble());
                  } else if (stream.name() == "LatitudeExif") {
                    photo->setLatitudeExif(stream.readElementText().toDouble());
                  } else if (stream.name() == "AltitudeExif") {
                    photo->setAltitudeExif(stream.readElementText().toDouble());
                  } else
                    stream.skipCurrentElement();
                }
                prj.addImage(photo);
              } else
                stream.skipCurrentElement();
            }
          } else if (stream.name() == "Sessions") {
            while (stream.readNextStartElement()) {

              if (stream.name() == "Session") {

                std::shared_ptr<Session> session(new Session);

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

                while (stream.readNextStartElement()) {
                  if (stream.name() == "Name") {
                    session->setName(stream.readElementText());
                  } else if (stream.name() == "Description") {
                    session->setDescription(stream.readElementText());
                  } else if (stream.name() == "Preprocess") {
                    while (stream.readNextStartElement()) {

                      if (stream.name() == "Clahe") {
                        std::shared_ptr<IAcebsf> acebsf = std::make_shared<AcebsfProperties>();
                        readACEBSF(&stream, acebsf.get());
                        session->setPreprocess(acebsf);
                      } else if (stream.name() == "Clahe") {
                        std::shared_ptr<IClahe> clahe = std::make_shared<ClaheProperties>();
                        readCLAHE(&stream, clahe.get());
                        session->setPreprocess(clahe);
                      } else if (stream.name() == "Cmbfhe") {
                        std::shared_ptr<ICmbfhe> cmbfhe(new CmbfheProperties);
                        readCMBFHE(&stream, cmbfhe.get());
                        session->setPreprocess(cmbfhe);
                      } else if (stream.name() == "Dhe") {
                        std::shared_ptr<IDhe> dhe = std::make_shared<DheProperties>();
                        readDHE(&stream, dhe.get());
                        session->setPreprocess(dhe);
                      } else if (stream.name() == "Fahe") {
                        std::shared_ptr<IFahe> fahe(new FaheProperties);
                        readFAHE(&stream, fahe.get());
                        session->setPreprocess(fahe);
                      } else if (stream.name() == "Hmclahe") {
                        std::shared_ptr<IHmclahe> hmclahe(new HmclaheProperties);
                        readHMCLAHE(&stream, hmclahe.get());
                        session->setPreprocess(hmclahe);
                      } else if (stream.name() == "LceBsescs") {
                        std::shared_ptr<ILceBsescs> lceBsescs(new LceBsescsProperties);
                        readLCEBSESCS(&stream, lceBsescs.get());
                        session->setPreprocess(lceBsescs);
                      } else if (stream.name() == "Msrcp") {
                        std::shared_ptr<IMsrcp> msrcp = std::make_shared<MsrcpProperties>();
                        readMSRCP(&stream, msrcp.get());
                        session->setPreprocess(msrcp);
                      } else if (stream.name() == "Noshp") {
                        std::shared_ptr<INoshp> noshp(new NoshpProperties);
                        readNOSHP(&stream, noshp.get());
                        session->setPreprocess(noshp);
                      } else if (stream.name() == "Pohe") {
                        std::shared_ptr<IPohe> pohe(new PoheProperties);
                        readPOHE(&stream, pohe.get());
                        session->setPreprocess(pohe);
                      } else if (stream.name() == "Rswhe") {
                        std::shared_ptr<IRswhe> rswhe = std::make_shared<RswheProperties>();
                        readRSWHE(&stream, rswhe.get());
                        session->setPreprocess(rswhe);
                      } else if (stream.name() == "Wallis") {
                        std::shared_ptr<IWallis> wallis = std::make_shared<WallisProperties>();
                        readWALLIS(&stream, wallis.get());
                        session->setPreprocess(wallis);
                      } else
                        stream.skipCurrentElement();
                    }
                  } else if (stream.name() == "FeatureDetector") {
                    while (stream.readNextStartElement()){
                      if (stream.name() == "AGAST") {
                        std::shared_ptr<IAgast> agast = std::make_shared<AgastProperties>();
                        readAGAST(&stream, agast.get());
                        session->setDetector(agast);
                      } else if (stream.name() == "AKAZE") {
                        std::shared_ptr<IAkaze> akaze = std::make_shared<AkazeProperties>();
                        readAKAZE(&stream, akaze.get());
                        session->setDetector(akaze);
                      } else if (stream.name() == "BRISK") {
                        std::shared_ptr<IBrisk> brisk = std::make_shared<BriskProperties>();
                        readBRISK(&stream, brisk.get());
                        session->setDetector(brisk);
                      } else if (stream.name() == "FAST") {
                        std::shared_ptr<IFast> fast = std::make_shared<FastProperties>();
                        readFAST(&stream, fast.get());
                        session->setDetector(fast);
                      } else if (stream.name() == "GFTT") {
                        std::shared_ptr<IGftt> gftt = std::make_shared<GfttProperties>();
                        readGFTT(&stream, gftt.get());
                        session->setDetector(gftt);
                      } else if (stream.name() == "KAZE") {
                        std::shared_ptr<IKaze> kaze = std::make_shared<KazeProperties>();
                        readKAZE(&stream, kaze.get());
                        session->setDetector(kaze);
                      } else if (stream.name() == "MSD") {
                        std::shared_ptr<IMsd> msd = std::make_shared<MsdProperties>();
                        readMSD(&stream, msd.get());
                        session->setDetector(msd);
                      } else if (stream.name() == "MSER") {
                        std::shared_ptr<IMser> mser = std::make_shared<MserProperties>();
                        readMSER(&stream, mser.get());
                        session->setDetector(mser);
                      } else if (stream.name() == "ORB") {
                        std::shared_ptr<IOrb> orb = std::make_shared<OrbProperties>();
                        readORB(&stream, orb.get());
                        session->setDetector(orb);
                      } else if (stream.name() == "SIFT") {
                        std::shared_ptr<ISift> sift = std::make_shared<SiftProperties>();
                        readSIFT(&stream, sift.get());
                        session->setDetector(sift);
                      } else if (stream.name() == "STAR") {
                        std::shared_ptr<IStar> star = std::make_shared<StarProperties>();
                        readSTAR(&stream, star.get());
                        session->setDetector(star);
                      } else if (stream.name() == "SURF") {
                        std::shared_ptr<ISurf> surf = std::make_shared<SurfProperties>();
                        readSURF(&stream, surf.get());
                        session->setDetector(surf);
                      }
                    }
                  } else if (stream.name() == "FeatureDescriptor") {
                    while (stream.readNextStartElement()){

                    }
                  } else
                    stream.skipCurrentElement();
                }

                prj.addSession(session);

                if (bActive)
                  prj.setCurrentSession(session->name());

              } else
                stream.skipCurrentElement();
            }
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

            if (preprocess->type() == Preprocess::Type::acebsf){
              writeACEBSF(&stream, dynamic_cast<IAcebsf *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::clahe){
              writeCLAHE(&stream, dynamic_cast<IClahe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::cmbfhe){
              writeCMBFHE(&stream, dynamic_cast<ICmbfhe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::dhe){
              writeDHE(&stream, dynamic_cast<IDhe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::fahe){
              writeFAHE(&stream, dynamic_cast<IFahe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::hmclahe){
              writeHMCLAHE(&stream, dynamic_cast<IHmclahe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::lce_bsescs){
              writeLCEBSESCS(&stream, dynamic_cast<ILceBsescs *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::msrcp){
              writeMSRCP(&stream, dynamic_cast<IMsrcp *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::noshp){
              writeNOSHP(&stream, dynamic_cast<INoshp *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::pohe){
              writePOHE(&stream, dynamic_cast<IPohe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::rswhe){
              writeRSWHE(&stream, dynamic_cast<IRswhe *>(preprocess));
            } else if (preprocess->type() == Preprocess::Type::wallis){
              writeWALLIS(&stream, dynamic_cast<IWallis *>(preprocess));
            }

            stream.writeEndElement(); // Preprocess
          }


          if (Feature *detector = (*it)->detector().get()){
            stream.writeStartElement("FeatureDetector");

            if (detector->type() == Feature::Type::agast){
              writeAGAST(&stream, dynamic_cast<IAgast *>(detector));
            } else if (detector->type() == Feature::Type::akaze){
              IAkaze *akaze = dynamic_cast<IAkaze *>(detector);
              writeAKAZE(&stream, akaze);
            } else if (detector->type() == Feature::Type::brisk){
              IBrisk *brisk = dynamic_cast<IBrisk *>(detector);
              writeBRISK(&stream, brisk);
            } else if (detector->type() == Feature::Type::fast){
              IFast *fast = dynamic_cast<IFast *>(detector);
              writeFAST(&stream, fast);
            } else if (detector->type() == Feature::Type::gftt){
              IGftt *gftt = dynamic_cast<IGftt *>(detector);
              writeGFTT(&stream, gftt);
            } else if (detector->type() == Feature::Type::kaze){
              IKaze *kaze = dynamic_cast<IKaze *>(detector);
              writeKAZE(&stream, kaze);
            } else if (detector->type() == Feature::Type::msd){
              IMsd *msd = dynamic_cast<IMsd *>(detector);
              writeMSD(&stream, msd);
            } else if (detector->type() == Feature::Type::mser){
              IMser *mser = dynamic_cast<IMser *>(detector);
              writeMSER(&stream, mser);
            } else if (detector->type() == Feature::Type::orb){
              IOrb *orb = dynamic_cast<IOrb *>(detector);
              writeORB(&stream, orb);
            } else if (detector->type() == Feature::Type::sift){
              ISift *sift = dynamic_cast<ISift *>(detector);
              writeSIFT(&stream, sift);
            } else if (detector->type() == Feature::Type::star){
              IStar *star = dynamic_cast<IStar *>(detector);
              writeSTAR(&stream, star);
            } else if (detector->type() == Feature::Type::surf){
              ISurf *surf = dynamic_cast<ISurf *>(detector);
              writeSURF(&stream, surf);

            }

            stream.writeEndElement(); // FeatureDetector
          }


          if (Feature *descriptor = (*it)->descriptor().get()){
            stream.writeStartElement("FeatureDescriptor");

            if (descriptor->type() == Feature::Type::akaze){
              IAkaze *akaze = dynamic_cast<IAkaze *>(descriptor);
              writeAKAZE(&stream, akaze);
            } else if (descriptor->type() == Feature::Type::brief){
              IBrief *brief = dynamic_cast<IBrief *>(descriptor);
              writeBRIEF(&stream, brief);
            } else if (descriptor->type() == Feature::Type::brisk){
              IBrisk *brisk = dynamic_cast<IBrisk *>(descriptor);
              writeBRISK(&stream, brisk);
            } else if (descriptor->type() == Feature::Type::daisy){
              IDaisy *daisy = dynamic_cast<IDaisy *>(descriptor);
              writeDAISY(&stream, daisy);
            } else if (descriptor->type() == Feature::Type::freak){
              IFreak *freak = dynamic_cast<IFreak *>(descriptor);
              writeFREAK(&stream, freak);
            } else if (descriptor->type() == Feature::Type::hog){
              IHog *hog = dynamic_cast<IHog *>(descriptor);
              writeHOG(&stream, hog);
            } else if (descriptor->type() == Feature::Type::kaze){
              IKaze *kaze = dynamic_cast<IKaze *>(descriptor);
              writeKAZE(&stream, kaze);
            } else if (descriptor->type() == Feature::Type::latch){
              ILatch *latch = dynamic_cast<ILatch *>(descriptor);
              writeLATCH(&stream, latch);
            } else if (descriptor->type() == Feature::Type::lucid){
              ILucid *lucid = dynamic_cast<ILucid *>(descriptor);
              writeLUCID(&stream, lucid);
            } else if (descriptor->type() == Feature::Type::orb){
              IOrb *orb = dynamic_cast<IOrb *>(descriptor);
              writeORB(&stream, orb);
            } else if (descriptor->type() == Feature::Type::sift){
              ISift *sift = dynamic_cast<ISift *>(descriptor);
              writeSIFT(&stream, sift);
            } else if (descriptor->type() == Feature::Type::surf){
              ISurf *surf = dynamic_cast<ISurf *>(descriptor);
              writeSURF(&stream, surf);
            }

            stream.writeEndElement(); // FeatureDescriptor
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
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "FME") {
        QString version = "0";
        for (auto &attr : stream.attributes()) {
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
        stream.raiseError(QObject::tr("Incorrect file"));
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
    QXmlStreamReader stream;
    stream.setDevice(&input);

    if (stream.readNextStartElement()) {
      if (stream.name() == "FME") {
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

void ProjectRW::readACEBSF(QXmlStreamReader *stream, IAcebsf *acebsf) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      acebsf->setBlockSize(blockSize);
    } else if (stream->name() == "L") {
      acebsf->setL(stream->readElementText().toDouble());
    } else if (stream->name() == "K1") {
      acebsf->setK1(stream->readElementText().toDouble());
    } else if (stream->name() == "K2") {
      acebsf->setK2(stream->readElementText().toDouble());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readCLAHE(QXmlStreamReader *stream, IClahe *clahe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "ClipLimit") {
      clahe->setClipLimit(stream->readElementText().toDouble());
    } else if (stream->name() == "GridSize") {
      QSize gridSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          gridSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          gridSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      clahe->setTilesGridSize(gridSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readCMBFHE(QXmlStreamReader *stream, ICmbfhe *cmbfhe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      cmbfhe->setBlockSize(blockSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readDHE(QXmlStreamReader *stream, IDhe *dhe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "X") {
      dhe->setX(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readFAHE(QXmlStreamReader *stream, IFahe *fahe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      fahe->setBlockSize(blockSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readHMCLAHE(QXmlStreamReader *stream, IHmclahe *hmclahe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      hmclahe->setBlockSize(blockSize);
    } else if (stream->name() == "L") {
      hmclahe->setL(stream->readElementText().toDouble());
    } else if (stream->name() == "Phi") {
      hmclahe->setPhi(stream->readElementText().toDouble());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readLCEBSESCS(QXmlStreamReader *stream, ILceBsescs *lceBsescs) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      lceBsescs->setBlockSize(blockSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readMSRCP(QXmlStreamReader *stream, IMsrcp *msrcp) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "SmallScale") {
      msrcp->setSmallScale(stream->readElementText().toInt());
    } else if (stream->name() == "MidScale") {
      msrcp->setMidScale(stream->readElementText().toInt());
    } else if (stream->name() == "LargeScale") {
      msrcp->setLargeScale(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readNOSHP(QXmlStreamReader *stream, INoshp *noshp) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      noshp->setBlockSize(blockSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readPOHE(QXmlStreamReader *stream, IPohe *pohe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      pohe->setBlockSize(blockSize);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readRSWHE(QXmlStreamReader *stream, IRswhe *rswhe) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "HistogramDivisions") {
      rswhe->setHistogramDivisions(stream->readElementText().toInt());
    } else if (stream->name() == "HistogramCut") {
      rswhe->setHistogramCut(static_cast<IRswhe::HistogramCut>(stream->readElementText().toInt()));
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readWALLIS(QXmlStreamReader *stream, IWallis *wallis) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Contrast") {
      wallis->setContrast(stream->readElementText().toDouble());
    } else if (stream->name() == "Brightness") {
      wallis->setBrightness(stream->readElementText().toDouble());
    } else if (stream->name() == "ImposedAverage") {
      wallis->setImposedAverage(stream->readElementText().toInt());
    } else if (stream->name() == "ImposedLocalStdDev") {
      wallis->setImposedLocalStdDev(stream->readElementText().toInt());
    } else if (stream->name() == "KernelSize") {
      wallis->setKernelSize(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readAGAST(QXmlStreamReader *stream, IAgast *agast) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Threshold") {
      agast->setThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "Brightness") {
      agast->setNonmaxSuppression(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "ImposedAverage") {
      agast->setDetectorType(stream->readElementText());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readAKAZE(QXmlStreamReader *stream, IAkaze *akaze) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "DescriptorType") {
      akaze->setDescriptorType(stream->readElementText());
    } else if (stream->name() == "DescriptorSize") {
      akaze->setDescriptorSize(stream->readElementText().toInt());
    } else if (stream->name() == "DescriptorChannels") {
      akaze->setDescriptorChannels(stream->readElementText().toInt());
    } else if (stream->name() == "Threshold") {
      akaze->setThreshold(stream->readElementText().toDouble());
    } else if (stream->name() == "Octaves") {
      akaze->setOctaves(stream->readElementText().toInt());
    } else if (stream->name() == "OctaveLayers") {
      akaze->setOctaveLayers(stream->readElementText().toInt());
    } else if (stream->name() == "Diffusivity") {
      akaze->setDiffusivity(stream->readElementText());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readBRIEF(QXmlStreamReader *stream, IBrief *brief) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Bytes") {
      brief->setBytes(stream->readElementText());
    } else if (stream->name() == "UseOrientation") {
      brief->setUseOrientation(stream->readElementText().compare("true") == 0 ? true : false);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readBRISK(QXmlStreamReader *stream, IBrisk *brisk) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Threshold") {
      brisk->setThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "Octaves") {
      brisk->setOctaves(stream->readElementText().toInt());
    } else if (stream->name() == "PatternScale") {
      brisk->setPatternScale(stream->readElementText().toDouble());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readDAISY(QXmlStreamReader *stream, IDaisy *daisy) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Radius") {
      daisy->setRadius(stream->readElementText().toDouble());
    } else if (stream->name() == "QRadius") {
      daisy->setQRadius(stream->readElementText().toInt());
    } else if (stream->name() == "QTheta") {
      daisy->setQTheta(stream->readElementText().toInt());
    } else if (stream->name() == "QHist") {
      daisy->setQHist(stream->readElementText().toInt());
    } else if (stream->name() == "Norm") {
      daisy->setNorm(stream->readElementText());
    } else if (stream->name() == "Interpolation") {
      daisy->setInterpolation(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "UseOrientation") {
      daisy->setUseOrientation(stream->readElementText().compare("true") == 0 ? true : false);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readFAST(QXmlStreamReader *stream, IFast *fast) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Threshold") {
      fast->setThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "NonmaxSuppression") {
      fast->setNonmaxSuppression(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "DetectorType") {
      fast->setDetectorType(stream->readElementText());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readFREAK(QXmlStreamReader *stream, IFreak *freak) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "OrientationNormalized") {
      freak->setOrientationNormalized(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "ScaleNormalized") {
      freak->setScaleNormalized(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "PatternScale") {
      freak->setPatternScale(stream->readElementText().toDouble());
    } else if (stream->name() == "Octaves") {
      freak->setOctaves(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readGFTT(QXmlStreamReader *stream, IGftt *gftt) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "MaxFeatures") {
      gftt->setMaxFeatures(stream->readElementText().toInt());
    } else if (stream->name() == "QualityLevel") {
      gftt->setQualityLevel(stream->readElementText().toDouble());
    } else if (stream->name() == "Threshold") {
      gftt->setMinDistance(stream->readElementText().toDouble());
    } else if (stream->name() == "BlockSize") {
      gftt->setBlockSize(stream->readElementText().toInt());
    } else if (stream->name() == "HarrisDetector") {
      gftt->setHarrisDetector(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "K") {
      gftt->setK(stream->readElementText().toDouble());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readHOG(QXmlStreamReader *stream, IHog *hog) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "WinSize") {
      QSize winSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          winSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          winSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      hog->setWinSize(winSize);
    } else if (stream->name() == "BlockSize") {
      QSize blockSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      hog->setBlockSize(blockSize);
    } else if (stream->name() == "BlockStride") {
      QSize blockStride;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          blockStride.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          blockStride.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      hog->setBlockStride(blockStride);
    } else if (stream->name() == "CellSize") {
      QSize cellSize;
      while (stream->readNextStartElement()) {
        if (stream->name() == "Width") {
          cellSize.setWidth(stream->readElementText().toInt());
        } else if (stream->name() == "Height") {
          cellSize.setHeight(stream->readElementText().toInt());
        } else
          stream->skipCurrentElement();
      }
      hog->setCellSize(cellSize);
    } else if (stream->name() == "Nbins") {
      hog->setNbins(stream->readElementText().toInt());
    } else if (stream->name() == "DerivAperture") {
      hog->setDerivAperture(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readKAZE(QXmlStreamReader *stream, IKaze *kaze) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "ExtendedDescriptor") {
      kaze->setExtendedDescriptor(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "Upright") {
      kaze->setUpright(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "Threshold") {
      kaze->setThreshold(stream->readElementText().toDouble());
    } else if (stream->name() == "Octaves") {
      kaze->setOctaves(stream->readElementText().toInt());
    } else if (stream->name() == "OctaveLayers") {
      kaze->setOctaveLayers(stream->readElementText().toInt());
    } else if (stream->name() == "Diffusivity") {
      kaze->setDiffusivity(stream->readElementText());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readLATCH(QXmlStreamReader *stream, ILatch *latch) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Bytes") {
      latch->setBytes(stream->readElementText());
    } else if (stream->name() == "RotationInvariance") {
      latch->setRotationInvariance(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "HalfSsdSize") {
      latch->setHalfSsdSize(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readLUCID(QXmlStreamReader *stream, ILucid *lucid) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "LucidKernel") {
      lucid->setLucidKernel(stream->readElementText().toInt());
    } else if (stream->name() == "BlurKernel") {
      lucid->setBlurKernel(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readMSD(QXmlStreamReader *stream, IMsd *msd) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "ThresholdSaliency") {
      msd->setThresholdSaliency(stream->readElementText().toDouble());
    } else if (stream->name() == "PatchRadius") {
      msd->setPatchRadius(stream->readElementText().toInt());
    } else if (stream->name() == "Knn") {
      msd->setKNN(stream->readElementText().toInt());
    } else if (stream->name() == "SearchAreaRadius") {
      msd->setSearchAreaRadius(stream->readElementText().toInt());
    } else if (stream->name() == "ScaleFactor") {
      msd->setScaleFactor(stream->readElementText().toDouble());
    } else if (stream->name() == "NMSRadius") {
      msd->setNMSRadius(stream->readElementText().toInt());
    } else if (stream->name() == "NScales") {
      msd->setNScales(stream->readElementText().toInt());
    } else if (stream->name() == "NMSScaleRadius") {
      msd->setNMSScaleRadius(stream->readElementText().toInt());
    } else if (stream->name() == "ComputeOrientation") {
      msd->setComputeOrientation(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "AffineMSD") {
      msd->setAffineMSD(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "AffineTilts") {
      msd->setAffineTilts(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readMSER(QXmlStreamReader *stream, IMser *mser) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "Delta") {
      mser->setDelta(stream->readElementText().toInt());
    } else if (stream->name() == "MinArea") {
      mser->setMinArea(stream->readElementText().toInt());
    } else if (stream->name() == "MaxArea") {
      mser->setMaxArea(stream->readElementText().toInt());
    } else if (stream->name() == "MaxVariation") {
      mser->setMaxVariation(stream->readElementText().toDouble());
    } else if (stream->name() == "MinDiversity") {
      mser->setMinDiversity(stream->readElementText().toDouble());
    } else if (stream->name() == "MaxEvolution") {
      mser->setMaxEvolution(stream->readElementText().toInt());
    } else if (stream->name() == "AreaThreshold") {
      mser->setAreaThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "MinMargin") {
      mser->setMinMargin(stream->readElementText().toDouble());
    } else if (stream->name() == "EdgeBlurSize") {
      mser->setEdgeBlurSize(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readORB(QXmlStreamReader *stream, IOrb *orb) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "FeaturesNumber") {
      orb->setFeaturesNumber(stream->readElementText().toInt());
    } else if (stream->name() == "ScaleFactor") {
      orb->setScaleFactor(stream->readElementText().toDouble());
    } else if (stream->name() == "LevelsNumber") {
      orb->setLevelsNumber(stream->readElementText().toInt());
    } else if (stream->name() == "EdgeThreshold") {
      orb->setEdgeThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "Wta_k") {
      orb->setWTA_K(stream->readElementText().toInt());
    } else if (stream->name() == "ScoreType") {
      orb->setScoreType(stream->readElementText());
    } else if (stream->name() == "PatchSize") {
      orb->setPatchSize(stream->readElementText().toInt());
    } else if (stream->name() == "FastThreshold") {
      orb->setFastThreshold(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readSIFT(QXmlStreamReader *stream, ISift *sift) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "FeaturesNumber") {
      sift->setFeaturesNumber(stream->readElementText().toInt());
    } else if (stream->name() == "OctaveLayers") {
      sift->setOctaveLayers(stream->readElementText().toInt());
    } else if (stream->name() == "ContrastThreshold") {
      sift->setContrastThreshold(stream->readElementText().toDouble());
    } else if (stream->name() == "EdgeThreshold") {
      sift->setEdgeThreshold(stream->readElementText().toDouble());
    } else if (stream->name() == "Sigma") {
      sift->setSigma(stream->readElementText().toDouble());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readSTAR(QXmlStreamReader *stream, IStar *star) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "MaxSize") {
      star->setMaxSize(stream->readElementText().toInt());
    } else if (stream->name() == "ResponseThreshold") {
      star->setResponseThreshold(stream->readElementText().toInt());
    } else if (stream->name() == "LineThresholdProjected") {
      star->setLineThresholdProjected(stream->readElementText().toInt());
    } else if (stream->name() == "LineThresholdBinarized") {
      star->setLineThresholdBinarized(stream->readElementText().toInt());
    } else if (stream->name() == "SuppressNonmaxSize") {
      star->setSuppressNonmaxSize(stream->readElementText().toInt());
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::readSURF(QXmlStreamReader *stream, ISurf *surf) const
{
  while (stream->readNextStartElement()) {
    if (stream->name() == "HessianThreshold") {
      surf->setHessianThreshold(stream->readElementText().toDouble());
    } else if (stream->name() == "Octaves") {
      surf->setOctaves(stream->readElementText().toInt());
    } else if (stream->name() == "OctaveLayers") {
      surf->setOctaveLayers(stream->readElementText().toInt());
    } else if (stream->name() == "ExtendedDescriptor") {
      surf->setExtendedDescriptor(stream->readElementText().compare("true") == 0 ? true : false);
    } else if (stream->name() == "RotatedFeatures") {
      surf->setRotatedFeatures(stream->readElementText().compare("true") == 0 ? true : false);
    } else
      stream->skipCurrentElement();
  }
}

void ProjectRW::writeACEBSF(QXmlStreamWriter *stream, IAcebsf *acebsf) const
{
  stream->writeStartElement("Acebsf");
  {
    stream->writeStartElement("BlockSize");
    stream->writeTextElement("Width", QString::number(acebsf->blockSize().width()));
    stream->writeTextElement("Height", QString::number(acebsf->blockSize().height()));
    stream->writeEndElement(); // BlockSize
    stream->writeTextElement("L", QString::number(acebsf->l()));
    stream->writeTextElement("K1", QString::number(acebsf->k1()));
    stream->writeTextElement("K2", QString::number(acebsf->k2()));

  }
  stream->writeEndElement(); // Acebsf
}

void ProjectRW::writeCLAHE(QXmlStreamWriter *stream, IClahe *clahe) const
{
  stream->writeStartElement("Clahe");
  {
    stream->writeTextElement("ClipLimit", QString::number(clahe->clipLimit()));
    stream->writeStartElement("GridSize");
    stream->writeTextElement("Width", QString::number(clahe->tilesGridSize().width()));
    stream->writeTextElement("Height", QString::number(clahe->tilesGridSize().height()));
    stream->writeEndElement(); // GridSize
  }
  stream->writeEndElement(); // Clahe
}

void ProjectRW::writeCMBFHE(QXmlStreamWriter *stream, ICmbfhe *cmbfhe) const
{
  stream->writeStartElement("Cmbfhe");
  {
    stream->writeStartElement("blockSize");
    stream->writeTextElement("Width", QString::number(cmbfhe->blockSize().width()));
    stream->writeTextElement("Height", QString::number(cmbfhe->blockSize().height()));
    stream->writeEndElement(); // BlockSize
  }
  stream->writeEndElement(); // Cmbfhe
}

void ProjectRW::writeDHE(QXmlStreamWriter *stream, IDhe *dhe) const
{
  stream->writeStartElement("Dhe");
  {
    stream->writeTextElement("X", QString::number(dhe->x()));
  }
  stream->writeEndElement(); // Dhe
}

void ProjectRW::writeFAHE(QXmlStreamWriter *stream, IFahe *fahe) const
{
  stream->writeStartElement("Fahe");
  {
    stream->writeStartElement("BlockSize");
    stream->writeTextElement("Width", QString::number(fahe->blockSize().width()));
    stream->writeTextElement("Height", QString::number(fahe->blockSize().height()));
    stream->writeEndElement(); // BlockSize
  }
  stream->writeEndElement(); // Fahe
}

void ProjectRW::writeHMCLAHE(QXmlStreamWriter *stream, IHmclahe *hmclahe) const
{
  stream->writeStartElement("Hmclahe");
  {
    stream->writeStartElement("blockSize");
    stream->writeTextElement("Width", QString::number(hmclahe->blockSize().width()));
    stream->writeTextElement("Height", QString::number(hmclahe->blockSize().height()));
    stream->writeEndElement(); // BlockSize
    stream->writeTextElement("L", QString::number(hmclahe->l()));
    stream->writeTextElement("Phi", QString::number(hmclahe->phi()));
  }
  stream->writeEndElement(); // Hmclahe
}

void ProjectRW::writeLCEBSESCS(QXmlStreamWriter *stream, ILceBsescs *lceBsescs) const
{
  stream->writeStartElement("LceBsescs");
  {
    stream->writeStartElement("blockSize");
    stream->writeTextElement("Width", QString::number(lceBsescs->blockSize().width()));
    stream->writeTextElement("Height", QString::number(lceBsescs->blockSize().height()));
    stream->writeEndElement(); // BlockSize
  }
  stream->writeEndElement(); // LceBsescs
}

void ProjectRW::writeMSRCP(QXmlStreamWriter *stream, IMsrcp *msrcp) const
{
  stream->writeStartElement("Msrcp");
  {
    stream->writeTextElement("SmallScale", QString::number(msrcp->smallScale()));
    stream->writeTextElement("MidScale", QString::number(msrcp->midScale()));
    stream->writeTextElement("LargeScale", QString::number(msrcp->largeScale()));
  }
  stream->writeEndElement(); // Msrcp
}

void ProjectRW::writeNOSHP(QXmlStreamWriter *stream, INoshp *noshp) const
{
  stream->writeStartElement("Noshp");
  {
    stream->writeStartElement("blockSize");
    stream->writeTextElement("Width", QString::number(noshp->blockSize().width()));
    stream->writeTextElement("Height", QString::number(noshp->blockSize().height()));
    stream->writeEndElement(); // BlockSize
  }
  stream->writeEndElement(); // Noshp
}

void ProjectRW::writePOHE(QXmlStreamWriter *stream, IPohe *pohe) const
{
  stream->writeStartElement("Pohe");
  {
    stream->writeStartElement("blockSize");
    stream->writeTextElement("Width", QString::number(pohe->blockSize().width()));
    stream->writeTextElement("Height", QString::number(pohe->blockSize().height()));
    stream->writeEndElement(); // BlockSize
  }
  stream->writeEndElement(); // Pohe
}

void ProjectRW::writeRSWHE(QXmlStreamWriter *stream, IRswhe *rswhe) const
{
  stream->writeStartElement("Rswhe");
  {
    stream->writeTextElement("HistogramDivisions", QString::number(rswhe->histogramDivisions()));
    stream->writeTextElement("HistogramCut", QString::number(static_cast<int>(rswhe->histogramCut())));
  }
  stream->writeEndElement(); // Rswhe
}

void ProjectRW::writeWALLIS(QXmlStreamWriter *stream, IWallis *wallis) const
{
  stream->writeStartElement("Wallis");
  {
    stream->writeTextElement("Contrast", QString::number(wallis->contrast()));
    stream->writeTextElement("Brightness", QString::number(wallis->brightness()));
    stream->writeTextElement("ImposedAverage", QString::number(wallis->imposedAverage()));
    stream->writeTextElement("ImposedLocalStdDev", QString::number(wallis->imposedLocalStdDev()));
    stream->writeTextElement("KernelSize", QString::number(wallis->kernelSize()));
  }
  stream->writeEndElement(); // Wallis
}

void ProjectRW::writeAGAST(QXmlStreamWriter *stream, IAgast *agast) const
{
  stream->writeStartElement("AGAST");
  {
    stream->writeTextElement("Threshold", QString::number(agast->threshold()));
    stream->writeTextElement("NonmaxSuppression", agast->nonmaxSuppression() ? "true" : "false");
    stream->writeTextElement("DetectorType", agast->detectorType());
  }
  stream->writeEndElement(); // AGAST
}

void ProjectRW::writeAKAZE(QXmlStreamWriter *stream, IAkaze *akaze) const
{
  stream->writeStartElement("AKAZE");
  {
    stream->writeTextElement("DescriptorType", akaze->descriptorType());
    stream->writeTextElement("DescriptorSize", QString::number(akaze->descriptorSize()));
    stream->writeTextElement("DescriptorChannels", QString::number(akaze->descriptorChannels()));
    stream->writeTextElement("Threshold", QString::number(akaze->threshold()));
    stream->writeTextElement("Octaves", QString::number(akaze->octaves()));
    stream->writeTextElement("OctaveLayers", QString::number(akaze->octaveLayers()));
    stream->writeTextElement("Diffusivity", akaze->diffusivity());
  }
  stream->writeEndElement(); // AKAZE
}

void ProjectRW::writeBRIEF(QXmlStreamWriter *stream, IBrief *brief) const
{
  stream->writeStartElement("BRIEF");
  {
    stream->writeTextElement("Bytes", brief->bytes());
    stream->writeTextElement("UseOrientation", brief->useOrientation() ? "true" : "false");
  }
  stream->writeEndElement(); // BRIEF
}

void ProjectRW::writeBRISK(QXmlStreamWriter *stream, IBrisk *brisk) const
{
  stream->writeStartElement("BRISK");
  {
    stream->writeTextElement("Threshold", QString::number(brisk->threshold()));
    stream->writeTextElement("Octaves", QString::number(brisk->octaves()));
    stream->writeTextElement("PatternScale", QString::number(brisk->patternScale()));
  }
  stream->writeEndElement(); // BRISK
}

void ProjectRW::writeDAISY(QXmlStreamWriter *stream, IDaisy *daisy) const
{
  stream->writeStartElement("DAISY");
  {
    stream->writeTextElement("Radius", QString::number(daisy->radius()));
    stream->writeTextElement("QRadius", QString::number(daisy->qRadius()));
    stream->writeTextElement("QTheta", QString::number(daisy->qTheta()));
    stream->writeTextElement("QHist", QString::number(daisy->qHist()));
    stream->writeTextElement("Norm", daisy->norm());
    stream->writeTextElement("Interpolation", daisy->interpolation() ? "true" : "false");
    stream->writeTextElement("UseOrientation", daisy->useOrientation() ? "true" : "false");
  }
  stream->writeEndElement(); // DAISY
}

void ProjectRW::writeFAST(QXmlStreamWriter *stream, IFast *fast) const
{
  stream->writeStartElement("FAST");
  {
    stream->writeTextElement("Threshold", QString::number(fast->threshold()));
    stream->writeTextElement("NonmaxSuppression", fast->nonmaxSuppression() ? "true" : "false");
    stream->writeTextElement("DetectorType", fast->detectorType());
  }
  stream->writeEndElement(); // FAST
}

void ProjectRW::writeFREAK(QXmlStreamWriter *stream, IFreak *freak) const
{
  stream->writeStartElement("FREAK");
  {
    stream->writeTextElement("OrientationNormalized", freak->orientationNormalized() ? "true" : "false");
    stream->writeTextElement("ScaleNormalized", freak->scaleNormalized() ? "true" : "false");
    stream->writeTextElement("PatternScale", QString::number(freak->patternScale()));
    stream->writeTextElement("Octaves", QString::number(freak->octaves()));
  }
  stream->writeEndElement(); // FREAK
}

void ProjectRW::writeGFTT(QXmlStreamWriter *stream, IGftt *gftt) const
{
  stream->writeStartElement("GFTT");
  {
    stream->writeTextElement("MaxFeatures", QString::number(gftt->maxFeatures()));
    stream->writeTextElement("QualityLevel", QString::number(gftt->qualityLevel()));
    stream->writeTextElement("MinDistance", QString::number(gftt->minDistance()));
    stream->writeTextElement("BlockSize", QString::number(gftt->blockSize()));
    stream->writeTextElement("HarrisDetector", gftt->harrisDetector() ? "true" : "false");
    stream->writeTextElement("K", QString::number(gftt->k()));
  }
  stream->writeEndElement(); // GFTT
}

void ProjectRW::writeHOG(QXmlStreamWriter *stream, IHog *hog) const
{
  stream->writeStartElement("HOG");
  {
    stream->writeStartElement("WinSize");
    stream->writeTextElement("Width", QString::number(hog->winSize().width()));
    stream->writeTextElement("Height", QString::number(hog->winSize().height()));
    stream->writeEndElement(); // WinSize
    stream->writeStartElement("BlockSize");
    stream->writeTextElement("Width", QString::number(hog->blockSize().width()));
    stream->writeTextElement("Height", QString::number(hog->blockSize().height()));
    stream->writeEndElement(); // BlockSize
    stream->writeStartElement("BlockStride");
    stream->writeTextElement("Width", QString::number(hog->blockStride().width()));
    stream->writeTextElement("Height", QString::number(hog->blockStride().height()));
    stream->writeEndElement(); // BlockStride
    stream->writeStartElement("CellSize");
    stream->writeTextElement("Width", QString::number(hog->cellSize().width()));
    stream->writeTextElement("Height", QString::number(hog->cellSize().height()));
    stream->writeEndElement(); // CellSize
    stream->writeTextElement("Nbins", QString::number(hog->nbins()));
    stream->writeTextElement("DerivAperture", QString::number(hog->derivAperture()));
  }
  stream->writeEndElement(); // HOG
}

void ProjectRW::writeKAZE(QXmlStreamWriter *stream, IKaze *kaze) const
{
  stream->writeStartElement("KAZE");
  {
    stream->writeTextElement("ExtendedDescriptor", kaze->extendedDescriptor() ? "true" : "false");
    stream->writeTextElement("Upright", kaze->upright() ? "true" : "false");
    stream->writeTextElement("Threshold", QString::number(kaze->threshold()));
    stream->writeTextElement("Octaves", QString::number(kaze->octaves()));
    stream->writeTextElement("OctaveLayers", QString::number(kaze->octaveLayers()));
    stream->writeTextElement("Diffusivity", kaze->diffusivity());
  }
  stream->writeEndElement(); // KAZE
}

void ProjectRW::writeLATCH(QXmlStreamWriter *stream, ILatch *latch) const
{
  stream->writeStartElement("LATCH");
  {
    stream->writeTextElement("Bytes", latch->bytes());
    stream->writeTextElement("RotationInvariance", latch->rotationInvariance() ? "true" : "false");
    stream->writeTextElement("HalfSsdSize", QString::number(latch->halfSsdSize()));
  }
  stream->writeEndElement(); // LATCH
}

void ProjectRW::writeLUCID(QXmlStreamWriter *stream, ILucid *lucid) const
{
  stream->writeStartElement("LUCID");
  {
    stream->writeTextElement("LucidKernel", QString::number(lucid->lucidKernel()));
    stream->writeTextElement("BlurKernel", QString::number(lucid->blurKernel()));
  }
  stream->writeEndElement(); // LUCID
}

void ProjectRW::writeMSD(QXmlStreamWriter *stream, IMsd *msd) const
{
  stream->writeStartElement("MSD");
  {
    stream->writeTextElement("ThresholdSaliency", QString::number(msd->thresholdSaliency()));
    stream->writeTextElement("PatchRadius", QString::number(msd->patchRadius()));
    stream->writeTextElement("Knn", QString::number(msd->knn()));
    stream->writeTextElement("SearchAreaRadius", QString::number(msd->searchAreaRadius()));
    stream->writeTextElement("ScaleFactor", QString::number(msd->scaleFactor()));
    stream->writeTextElement("NMSRadius", QString::number(msd->NMSRadius()));
    stream->writeTextElement("NScales", QString::number(msd->nScales()));
    stream->writeTextElement("NMSScaleRadius", QString::number(msd->NMSScaleRadius()));
    stream->writeTextElement("ComputeOrientation", msd->computeOrientation() ? "true" : "false");
    stream->writeTextElement("AffineMSD", msd->affineMSD() ? "true" : "false");
    stream->writeTextElement("AffineTilts", QString::number(msd->affineTilts()));
  }
  stream->writeEndElement(); // MSD
}

void ProjectRW::writeMSER(QXmlStreamWriter *stream, IMser *mser) const
{
  stream->writeStartElement("MSER");
  {
    stream->writeTextElement("Delta", QString::number(mser->delta()));
    stream->writeTextElement("MinArea", QString::number(mser->minArea()));
    stream->writeTextElement("MaxArea", QString::number(mser->maxArea()));
    stream->writeTextElement("MaxVariation", QString::number(mser->maxVariation()));
    stream->writeTextElement("MinDiversity", QString::number(mser->minDiversity()));
    stream->writeTextElement("MaxEvolution", QString::number(mser->maxEvolution()));
    stream->writeTextElement("AreaThreshold", QString::number(mser->areaThreshold()));
    stream->writeTextElement("MinMargin", QString::number(mser->minMargin()));
    stream->writeTextElement("EdgeBlurSize", QString::number(mser->edgeBlurSize()));
  }
  stream->writeEndElement(); // MSER
}

void ProjectRW::writeORB(QXmlStreamWriter *stream, IOrb *orb) const
{
  stream->writeStartElement("ORB");
  {
    stream->writeTextElement("FeaturesNumber", QString::number(orb->featuresNumber()));
    stream->writeTextElement("ScaleFactor", QString::number(orb->scaleFactor()));
    stream->writeTextElement("LevelsNumber", QString::number(orb->levelsNumber()));
    stream->writeTextElement("EdgeThreshold", QString::number(orb->edgeThreshold()));
    stream->writeTextElement("Wta_k", QString::number(orb->wta_k()));
    stream->writeTextElement("ScoreType", orb->scoreType());
    stream->writeTextElement("PatchSize", QString::number(orb->patchSize()));
    stream->writeTextElement("FastThreshold", QString::number(orb->fastThreshold()));
  }
  stream->writeEndElement(); // ORB
}

void ProjectRW::writeSIFT(QXmlStreamWriter *stream, ISift *sift) const
{
  stream->writeStartElement("SIFT");
  {
    stream->writeTextElement("FeaturesNumber", QString::number(sift->featuresNumber()));
    stream->writeTextElement("OctaveLayers", QString::number(sift->octaveLayers()));
    stream->writeTextElement("ContrastThreshold", QString::number(sift->contrastThreshold()));
    stream->writeTextElement("EdgeThreshold", QString::number(sift->edgeThreshold()));
    stream->writeTextElement("Sigma", QString::number(sift->sigma()));
  }
  stream->writeEndElement(); // SIFT
}

void ProjectRW::writeSTAR(QXmlStreamWriter *stream, IStar *star) const
{
  stream->writeStartElement("STAR");
  {
    stream->writeTextElement("MaxSize", QString::number(star->maxSize()));
    stream->writeTextElement("ResponseThreshold", QString::number(star->responseThreshold()));
    stream->writeTextElement("LineThresholdProjected", QString::number(star->lineThresholdProjected()));
    stream->writeTextElement("LineThresholdBinarized", QString::number(star->lineThresholdBinarized()));
    stream->writeTextElement("SuppressNonmaxSize", QString::number(star->suppressNonmaxSize()));
  }
  stream->writeEndElement(); // STAR
}

void ProjectRW::writeSURF(QXmlStreamWriter *stream, ISurf *surf) const
{
  stream->writeStartElement("SURF");
  {
    stream->writeTextElement("HessianThreshold", QString::number(surf->hessianThreshold()));
    stream->writeTextElement("Octaves", QString::number(surf->octaves()));
    stream->writeTextElement("OctaveLayers", QString::number(surf->octaveLayers()));
    stream->writeTextElement("ExtendedDescriptor", surf->extendedDescriptor() ? "true" : "false");
    stream->writeTextElement("RotatedFeatures", surf->rotatedFeatures() ? "true" : "false");
  }
  stream->writeEndElement(); // SURF
}

} // namespace fme






