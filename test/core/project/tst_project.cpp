#include <QtTest>

#include "fme/core/project.h"

using namespace fme;

class ProjectRWFake
  : public IProjectRW
{

public:

  ProjectRWFake()
  {
    mProjectFileText = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                       "<FME version=\"1.0\">"
                       "    <General>"
                       "        <Name>prj001</Name>"
                       "        <ProjectFolder>C:/Users/User01/Documents/fme/Projects/prj001</ProjectFolder>"
                       "        <Description>Project example</Description>"
                       "    </General>"
                       "    <Images>"
                       "        <Image>"
                       "            <File>C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png</File>"
                       "            <LongitudeExif>0.5</LongitudeExif>"
                       "            <LatitudeExif>2.3</LatitudeExif>"
                       "            <AltitudeExif>10.2</AltitudeExif>"
                       "        </Image>"
                       "        <Image>"
                       "            <File>C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png</File>"
                       "            <LongitudeExif>0.51</LongitudeExif>"
                       "            <LatitudeExif>2.3</LatitudeExif>"
                       "            <AltitudeExif>10.1</AltitudeExif>"
                       "        </Image>"
                       "    </Images>"
                       "    <Sessions>"
                       "        <Session>"
                       "            <Name>session001</Name>"
                       "            <Description>Session 1</Description>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session002</Name>"
                       "            <Description>Session 2</Description>"
                       "        </Session>"
                       "    </Sessions>"
                       "</FME>";
  }

  ~ProjectRWFake() override {}

  // IProjectIO interface
public:

  bool read(const QString &file, IProject &prj) override
  {

    QXmlStreamReader xmlReader;
    xmlReader.addData(mProjectFileText);

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
    return false;
  }

  bool write(const QString &file, const IProject &prj) const override
  {
//    QFileInfo file_info(file);
//    QString tmpfile = file_info.path().append(file_info.baseName()).append(".bak");
//    std::ifstream  src(file.toStdString().c_str(), std::ios::binary);
//    std::ofstream  dst(tmpfile.toStdString().c_str(), std::ios::binary);
//    dst << src.rdbuf();
//    src.close();
//    dst.close();

//    QFile output(file);
//    output.open(QFile::WriteOnly);
//    QXmlStreamWriter stream(&output);
//    stream.setAutoFormatting(true);
//    stream.writeStartDocument();

//    stream.writeStartElement("FME");
//    {

//      stream.writeAttribute("version", prj.version());

//      /// General

//      stream.writeStartElement("General");
//      {
//        stream.writeTextElement("Name", prj.name());
//        stream.writeTextElement("ProjectFolder", prj.projectFolder());
//        stream.writeTextElement("Description", prj.description());
//      }
//      stream.writeEndElement(); // General

//      /// Imagenes
//      stream.writeStartElement("Images");
//      {
//        for (auto it = prj.imageBegin(); it != prj.imageEnd(); it++){
//          stream.writeStartElement("Image");
//          {
//            stream.writeTextElement("File", (*it)->path());
//            stream.writeTextElement("LongitudeExif", QString::number((*it)->longitudeExif()));
//            stream.writeTextElement("LatitudeExif", QString::number((*it)->latitudeExif()));
//            stream.writeTextElement("AltitudeExif", QString::number((*it)->altitudeExif()));
//          }
//          stream.writeEndElement(); // Image
//        }
//      }
//      stream.writeEndElement();  // Images
//    }
//    stream.writeEndElement(); // Fme

    return false;
  }

  bool checkOldVersion(const QString &file) const override
  {
//    std::lock_guard<std::mutex> lck(ProjectIO::sMutex);
    bool bUpdateVersion = false;
//    QFile input(file);
//    if (input.open(QIODevice::ReadOnly)) {
//      QXmlStreamReader xmlReader;
//      xmlReader.setDevice(&input);

//      if (xmlReader.readNextStartElement()) {
//        if (xmlReader.name() == "FME") {
//          QString version = "0";
//          for (auto &attr : xmlReader.attributes()) {
//            if (attr.name().compare(QString("version")) == 0) {
//              version = attr.value().toString();
//              break;
//            }
//          }
//          if (version.compare(FME_PROJECT_FILE_VERSION) < 0) {
//            // Es una versión mas antigua
//            bUpdateVersion = true;
//          }
//        } else
//          xmlReader.raiseError(QObject::tr("Incorrect file"));
//      }
//    }
    return bUpdateVersion;
  }

  void oldVersionBak(const QString &file) const override
  {

  }

protected:

  QString mProjectFileText;
};

class TestProject : public QObject
{
  Q_OBJECT

public:

  TestProject();
  ~TestProject();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_name_data();
  void test_name();
  void test_description_data();
  void test_description();
//  void test_path_data();
//  void test_path();
  void test_projectFolder_data();
  void test_projectFolder();
  void test_findImage();
  void test_findImageId_data();
  void test_findImageId();
  void test_imageIterator();
  void test_addImage_deleteImage();
  void test_addSession_deleteSession();
  void test_findSession();
  void test_findSessionId_data();
  void test_findSessionId();
  void test_sessionIterator();
  void test_currentSession();
  void test_clear();

protected:

  IProjectRW *mProjectIOFake;
  IProject *mProject;
  IProject *mProjectXml;
};

TestProject::TestProject()
  : mProjectIOFake(new ProjectRWFake),
    mProject(new Project),
    mProjectXml(new Project)
{

}

TestProject::~TestProject()
{
  if (mProjectIOFake){
    delete mProjectIOFake;
    mProjectIOFake = nullptr;
  }

  if (mProject){
    delete mProject;
    mProject = nullptr;
  }

  if (mProjectXml){
    delete mProjectXml;
    mProjectXml = nullptr;
  }
}

void TestProject::initTestCase()
{
  mProjectIOFake->read("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml", *mProjectXml);
}

void TestProject::cleanupTestCase()
{

}

void TestProject::testConstructor()
{
  QCOMPARE(QString(), mProject->name());
  QCOMPARE(QString(), mProject->description());
  QCOMPARE(QString(), mProject->projectFolder());
  QCOMPARE(QString("1.0"), mProject->version());
  QCOMPARE(0, mProject->imagesCount());

  QCOMPARE(QString("prj001"), mProjectXml->name());
  QCOMPARE(QString("Project example"), mProjectXml->description());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001"), mProjectXml->projectFolder());
  QCOMPARE(QString("1.0"), mProjectXml->version());
  QCOMPARE(2, mProjectXml->imagesCount());
}

void TestProject::test_name_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Proj01") << "Proj01" << "Proj01";
  QTest::newRow("Proj02") << "Proj02" << "Proj02";

}

void TestProject::test_name()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mProject->setName(value);
  QCOMPARE(result, mProject->name());
}

void TestProject::test_description_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Description1") << "Descripción del proyecto 1" << "Descripción del proyecto 1";
  QTest::newRow("Description2") << "Descripción del proyecto 2" << "Descripción del proyecto 2";
}

void TestProject::test_description()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mProject->setDescription(value);
  QCOMPARE(result, mProject->description());
}

void TestProject::test_projectFolder_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Folder_prj_01") << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001" << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001";
  QTest::newRow("Folder_prj_02") << "C:/Users/User01/Documents/fme/Projects/prj002" << "C:/Users/User01/Documents/fme/Projects/prj002";
}

void TestProject::test_projectFolder()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mProject->setProjectFolder(value);
  QCOMPARE(result, mProject->projectFolder());
}

void TestProject::test_findImage()
{
  std::shared_ptr<Image> img = mProjectXml->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png");
  QCOMPARE("img001", img->name());
  QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png", img->path());
  QCOMPARE(0.5, img->longitudeExif());
  QCOMPARE(2.3, img->latitudeExif());
  QCOMPARE(10.2, img->altitudeExif());

  std::shared_ptr<Image> img2 = mProjectXml->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png");
  QCOMPARE("img002", img2->name());
  QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png", img2->path());
  QCOMPARE(0.51, img2->longitudeExif());
  QCOMPARE(2.3, img2->latitudeExif());
  QCOMPARE(10.1, img2->altitudeExif());
}

void TestProject::test_findImageId_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<size_t>("result");

  QTest::newRow("img001") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png" << size_t{0};
  QTest::newRow("img002") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png" << size_t{1};
  QTest::newRow("img003") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png" << std::numeric_limits<size_t>().max();
}

void TestProject::test_findImageId()
{
  QFETCH(QString, value);
  QFETCH(size_t, result);

  QCOMPARE(result, mProjectXml->findImageId(value));
}

void TestProject::test_imageIterator()
{
  std::shared_ptr<Image> img;
  int i = 0;
  for (auto it = mProjectXml->imageBegin(); it != mProjectXml->imageEnd(); it++, i++){

    if (i == 0){
      QCOMPARE("img001", (*it)->name());
      QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png", (*it)->path());
      QCOMPARE(0.5, (*it)->longitudeExif());
      QCOMPARE(2.3, (*it)->latitudeExif());
      QCOMPARE(10.2, (*it)->altitudeExif());
    } else {
      QCOMPARE("img002", (*it)->name());
      QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png", (*it)->path());
      QCOMPARE(0.51, (*it)->longitudeExif());
      QCOMPARE(2.3, (*it)->latitudeExif());
      QCOMPARE(10.1, (*it)->altitudeExif());
    }
  }
}

void TestProject::test_addImage_deleteImage()
{
  std::shared_ptr<Image> img(new Image("C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png"));

  mProjectXml->addImage(img);

  QCOMPARE(3, mProjectXml->imagesCount());

  mProjectXml->deleteImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png");
  QCOMPARE(2, mProjectXml->imagesCount());
}

void TestProject::test_addSession_deleteSession()
{
  mProjectXml->addSession("SessionSIFT", "Sesión SIFT");
  mProjectXml->deleteSession("SessionSIFT");
}

void TestProject::test_findSession()
{
  std::shared_ptr<Session> session1 = mProjectXml->findSession("session001");
  QCOMPARE("session001", session1->name());
  QCOMPARE("Session 1", session1->description());

  std::shared_ptr<Session> session2 = mProjectXml->findSession("session002");
  QCOMPARE("session002", session2->name());
  QCOMPARE("Session 2", session2->description());
}

void TestProject::test_findSessionId_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<size_t>("result");

  QTest::newRow("session001") << "session001" << size_t{0};
  QTest::newRow("session002") << "session002" << size_t{1};
  QTest::newRow("session003") << "session003" << std::numeric_limits<size_t>().max();
}

void TestProject::test_findSessionId()
{
  QFETCH(QString, value);
  QFETCH(size_t, result);

  QCOMPARE(result, mProjectXml->findSessionId(value));
}

void TestProject::test_sessionIterator()
{
  std::shared_ptr<Session> session;
  int i = 0;
  for (auto it = mProjectXml->sessionBegin(); it != mProjectXml->sessionEnd(); it++, i++){

    if (i == 0){
      QCOMPARE("session001", (*it)->name());
      QCOMPARE("Session 1", (*it)->description());
    } else {
      QCOMPARE("session002", (*it)->name());
      QCOMPARE("Session 2", (*it)->description());
    }
  }
}

void TestProject::test_currentSession()
{
  ///TODO: completar
}

void TestProject::test_clear()
{

}

QTEST_APPLESS_MAIN(TestProject)

#include "tst_project.moc"
