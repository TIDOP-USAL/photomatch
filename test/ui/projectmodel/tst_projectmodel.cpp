#include <QtTest>

#include "fme/core/project.h"
#include "fme/ui/ProjectModel.h"

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

    return false;
  }

  bool checkOldVersion(const QString &file) const override
  {
    bool bUpdateVersion = false;
    return bUpdateVersion;
  }

  void oldVersionBak(const QString &file) const override
  {

  }

protected:

  QString mProjectFileText;
};




class TestProjectModel : public QObject
{
  Q_OBJECT

public:

  TestProjectModel();
  ~TestProjectModel();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();
  void test_name_data();
  void test_name();
  void test_description_data();
  void test_description();
  void test_projectFolder_data();
  void test_projectFolder();
  void test_findImage();
  void test_findImageId_data();
  void test_findImageId();
  void test_imageIterator();
  void test_addImage_deleteImage();
  void test_addImages_deleteImages();
  void test_addSession_deleteSession();
  void test_findSession();
  void test_findSessionId_data();
  void test_findSessionId();
  void test_sessionIterator();
  void test_z_clear();

protected:

  IProjectRW *mProjectIOFake;
  IProject *mProject;
  IProjectModel *mProjectModel;
};

TestProjectModel::TestProjectModel()
  : mProjectIOFake(new ProjectRWFake),
    mProject(new Project),
    mProjectModel(new ProjectModel(mProjectIOFake, mProject))
{

}

TestProjectModel::~TestProjectModel()
{
  if (mProjectIOFake) {
    delete mProjectIOFake;
    mProjectIOFake =nullptr;
  }

  if (mProject){
    delete mProject;
    mProject = nullptr;
  }

  if (mProjectModel) {
    delete mProjectModel;
    mProjectModel = nullptr;
  }
}

void TestProjectModel::initTestCase()
{
  /// reading simulation
  mProjectModel->load("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml");
}

void TestProjectModel::cleanupTestCase()
{

}

void TestProjectModel::testConstructor()
{
  ProjectRWFake *projectIOFake = new ProjectRWFake;
  Project *project = new Project;

  ProjectModel prj(projectIOFake, project);
  QCOMPARE(QString(), prj.name());
  QCOMPARE(QString(), prj.description());
  QCOMPARE(QString(), prj.projectFolder());
  QCOMPARE(QString("1.0"), prj.version());
  QCOMPARE(0, prj.imagesCount());
  QCOMPARE(0, prj.sessionCount());
  QCOMPARE(QString(), prj.path());
  QCOMPARE(false, prj.checkUnsavedChanges());
  //QCOMPARE(false, prj.checkOldVersion());

  delete projectIOFake;
  projectIOFake =nullptr;

  delete project;
  project = nullptr;

  QCOMPARE(QString("prj001"), mProjectModel->name());
  QCOMPARE(QString("Project example"), mProjectModel->description());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001"), mProjectModel->projectFolder());
  QCOMPARE(QString("1.0"), mProjectModel->version());
  QCOMPARE(2, mProjectModel->imagesCount());
  QCOMPARE(2, mProjectModel->sessionCount());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml"), mProjectModel->path());
  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
  //QCOMPARE(false, mProjectModel->checkOldVersion());

}

void TestProjectModel::test_name_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Proj01") << "Proj01" << "Proj01";
  QTest::newRow("Proj02") << "Proj02" << "Proj02";
}

void TestProjectModel::test_name()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
  mProjectModel->setName(value);
  QCOMPARE(true, mProjectModel->checkUnsavedChanges());
  QCOMPARE(result, mProjectModel->name());
  mProjectModel->save();
  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
}

void TestProjectModel::test_description_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Description1") << "Descripción del proyecto 1" << "Descripción del proyecto 1";
  QTest::newRow("Description2") << "Descripción del proyecto 2" << "Descripción del proyecto 2";
}

void TestProjectModel::test_description()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
  mProjectModel->setDescription(value);
  QCOMPARE(true, mProjectModel->checkUnsavedChanges());
  QCOMPARE(result, mProjectModel->description());
  mProjectModel->save();
}

void TestProjectModel::test_projectFolder_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Folder_prj_01") << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001" << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001";
  QTest::newRow("Folder_prj_02") << "C:/Users/User01/Documents/fme/Projects/prj002" << "C:/Users/User01/Documents/fme/Projects/prj002";
}

void TestProjectModel::test_projectFolder()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
  mProjectModel->setProjectFolder(value);
  QCOMPARE(true, mProjectModel->checkUnsavedChanges());
  QCOMPARE(result, mProjectModel->projectFolder());
  mProjectModel->save();
}

void TestProjectModel::test_findImage()
{
  std::shared_ptr<Image> img = mProjectModel->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png");
  QCOMPARE("img001", img->name());
  QCOMPARE(0.5, img->longitudeExif());
  QCOMPARE(2.3, img->latitudeExif());
  QCOMPARE(10.2, img->altitudeExif());

  std::shared_ptr<Image> img2 = mProjectModel->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png");
  QCOMPARE("img002", img2->name());
  QCOMPARE(0.51, img2->longitudeExif());
  QCOMPARE(2.3, img2->latitudeExif());
  QCOMPARE(10.1, img2->altitudeExif());
}

void TestProjectModel::test_findImageId_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<size_t>("result");

  QTest::newRow("img001") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png" << size_t{0};
  QTest::newRow("img002") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png" << size_t{1};
  QTest::newRow("img003") << "C:/Users/User01/Documents/fme/Projects/prj001/images/img005.png" << std::numeric_limits<size_t>().max();
}

void TestProjectModel::test_findImageId()
{
  QFETCH(QString, value);
  QFETCH(size_t, result);

  QCOMPARE(result, mProjectModel->findImageId(value));
}

void TestProjectModel::test_imageIterator()
{
  std::shared_ptr<Image> img;
  int i = 0;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++, i++){

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

void TestProjectModel::test_addImage_deleteImage()
{
  std::shared_ptr<Image> img(new Image("C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png"));
  mProjectModel->addImage(img);

  QCOMPARE(3, mProjectModel->imagesCount());

  mProjectModel->deleteImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png");
  QCOMPARE(2, mProjectModel->imagesCount());
  mProjectModel->save();
}

void TestProjectModel::test_addImages_deleteImages()
{
  mProjectModel->addImages({"C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png",
                            "C:/Users/User01/Documents/fme/Projects/prj001/images/img004.png"});

  QCOMPARE(4, mProjectModel->imagesCount());

  mProjectModel->deleteImages({"C:/Users/User01/Documents/fme/Projects/prj001/images/img003.png",
                               "C:/Users/User01/Documents/fme/Projects/prj001/images/img004.png"});
  QCOMPARE(2, mProjectModel->imagesCount());
  mProjectModel->save();
}

void TestProjectModel::test_addSession_deleteSession()
{
  mProjectModel->addSession("Session01", "Sesión SIFT");
  mProjectModel->deleteSession("Session01");
  mProjectModel->save();
}

void TestProjectModel::test_findSession()
{
  std::shared_ptr<Session> session1 = mProjectModel->findSession("session001");
  QCOMPARE("session001", session1->name());
  QCOMPARE("Session 1", session1->description());

  std::shared_ptr<Session> session2 = mProjectModel->findSession("session002");
  QCOMPARE("session002", session2->name());
  QCOMPARE("Session 2", session2->description());
}

void TestProjectModel::test_findSessionId_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<size_t>("result");

  QTest::newRow("session001") << "session001" << size_t{0};
  QTest::newRow("session002") << "session002" << size_t{1};
  QTest::newRow("session003") << "session003" << std::numeric_limits<size_t>().max();
}

void TestProjectModel::test_findSessionId()
{
  QFETCH(QString, value);
  QFETCH(size_t, result);

  QCOMPARE(result, mProjectModel->findSessionId(value));
}

void TestProjectModel::test_sessionIterator()
{
  std::shared_ptr<Session> session;
  int i = 0;
  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++, i++){

    if (i == 0){
      QCOMPARE("session001", (*it)->name());
      QCOMPARE("Session 1", (*it)->description());
    } else {
      QCOMPARE("session002", (*it)->name());
      QCOMPARE("Session 2", (*it)->description());
    }
  }
}

/// _z para que lo ejecute al final...
void TestProjectModel::test_z_clear()
{
  mProjectModel->clear();

  QCOMPARE(QString(), mProjectModel->name());
  QCOMPARE(QString(), mProjectModel->description());
  QCOMPARE(QString(), mProjectModel->projectFolder());
  QCOMPARE(QString("1.0"), mProjectModel->version());
  QCOMPARE(0, mProjectModel->imagesCount());
  QCOMPARE(0, mProjectModel->sessionCount());
  QCOMPARE(QString(), mProjectModel->path());
  QCOMPARE(false, mProjectModel->checkUnsavedChanges());
}

QTEST_APPLESS_MAIN(TestProjectModel)

#include "tst_projectmodel.moc"
