#include <QtTest>

#include "fme/core/project.h"

using namespace fme;

class ProjectIOFake
  : public IProjectIO
{

public:

  ProjectIOFake()
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
                       "</FME>";
  }

  ~ProjectIOFake() override {}

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
  void test_path_data();
  void test_path();
  void test_projectFolder_data();
  void test_projectFolder();
  void test_findImage();
  void test_findImageId_data();
  void test_findImageId();
  void test_imageIterator();
  void test_clear();

protected:

  ProjectIOFake* mProjectIOFake;
  Project *mProject;
  Project *mProjectImg;
  Project *mProjectXml;
};

TestProject::TestProject()
  : mProjectIOFake(new ProjectIOFake),
    mProject(new Project(mProjectIOFake)),
    mProjectImg(new Project(mProjectIOFake, "C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml")),
    mProjectXml(new Project(mProjectIOFake))
{

}

TestProject::~TestProject()
{
  if (mProject){
    delete mProject;
    mProject = nullptr;
  }
  if (mProjectImg){
    delete mProjectImg;
    mProjectImg = nullptr;
  }
  if (mProjectXml){
    delete mProjectXml;
    mProjectXml = nullptr;
  }
}

void TestProject::initTestCase()
{
//  mImage1 = std::make_shared<Image>("C:/Users/User01/Documents/fme/Projects/images/img001.png");
//  mImage1->setLongitudeExif(0.5);
//  mImage1->setLatitudeExif(2.3);
//  mImage1->setAltitudeExif(10.2);

//  mImage2 = std::make_shared<Image>("C:/Users/User01/Documents/fme/Projects/images/img002.png");
//  mImage2->setLongitudeExif(0.51);
//  mImage2->setLatitudeExif(2.3);
//  mImage2->setAltitudeExif(10.1);

//  mProjectImg->setName("PrjImages");
//  mProjectImg->setDescription("Project Images");
//  mProjectImg->addImage(mImage1);
//  mProjectImg->addImage(mImage2);

  mProjectXml->load("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml");
}

void TestProject::cleanupTestCase()
{

}

void TestProject::testConstructor()
{
  QCOMPARE(QString(), mProject->name());
  QCOMPARE(QString(), mProject->description());
  QCOMPARE(QString(), mProject->path());
  QCOMPARE(QString(), mProject->projectFolder());
  QCOMPARE(QString("1.0"), mProject->version());
  QCOMPARE(0, mProject->imagesCount());
  QCOMPARE(false, mProject->checkUnsavedChanges());

  QCOMPARE(QString("prj001"), mProjectImg->name());
  QCOMPARE(QString("Project example"), mProjectImg->description());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml"), mProjectImg->path());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001"), mProjectImg->projectFolder());
  QCOMPARE(QString("1.0"), mProjectImg->version());
  QCOMPARE(2, mProjectImg->imagesCount());
  QCOMPARE(false, mProjectImg->checkUnsavedChanges());  /// true porque se han añadido imagenes


  QCOMPARE(QString("prj001"), mProjectXml->name());
  QCOMPARE(QString("Project example"), mProjectXml->description());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001/prj001.xml"), mProjectXml->path());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001"), mProjectXml->projectFolder());
  QCOMPARE(QString("1.0"), mProjectXml->version());
  QCOMPARE(2, mProjectXml->imagesCount());
  QCOMPARE(false, mProjectXml->checkUnsavedChanges());  /// true porque se han añadido imagenes

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

  /// Proyecto no modificado. No hay cambios sin guardar
  QCOMPARE(false, mProject->checkUnsavedChanges());

  mProject->setName(value);
  QCOMPARE(result, mProject->name());

  /// Proyecto modificado. Hay cambios sin guardar
  QCOMPARE(true, mProject->checkUnsavedChanges());

  mProject->clear();  /// Se limpia el proyecto para poner bUnsavedChanges a false y chequear su activación para el resto de test
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

  /// Proyecto no modificado. No hay cambios sin guardar
  QCOMPARE(false, mProject->checkUnsavedChanges());

  mProject->setDescription(value);
  QCOMPARE(result, mProject->description());

  /// Proyecto modificado. Hay cambios sin guardar
  QCOMPARE(true, mProject->checkUnsavedChanges());

  mProject->clear();  /// Se limpia el proyecto para poner bUnsavedChanges a false y chequear su activación para el resto de test
}

void TestProject::test_path_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("project01")
             << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001\\prj001.xml"
             << "C:\\Users\\User01\\Documents\\fme\\Projects\\prj001\\prj001.xml";
  QTest::newRow("project02")
             << "C:/Users/User01/Documents/fme/Projects/prj002/prj002.xml"
             << "C:/Users/User01/Documents/fme/Projects/prj002/prj002.xml";
}

void TestProject::test_path()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mProject->saveAs(value);
  QCOMPARE(result, mProject->path());

  /// Proyecto guardado. No hay cambios sin guardar
  QCOMPARE(false, mProject->checkUnsavedChanges());
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

  /// Proyecto no modificado. No hay cambios sin guardar
  QCOMPARE(false, mProject->checkUnsavedChanges());

  mProject->setProjectFolder(value);
  QCOMPARE(result, mProject->projectFolder());

  /// Proyecto modificado. Hay cambios sin guardar
  QCOMPARE(true, mProject->checkUnsavedChanges());

  /// Se limpia el proyecto para poner bUnsavedChanges a
  /// false y chequear su activación para el resto de test
  mProject->clear();
}

void TestProject::test_findImage()
{
  std::shared_ptr<Image> img = mProjectImg->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png");
  QCOMPARE("img001", img->name());
  QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img001.png", img->path());
  //QCOMPARE(0.5, img->longitudeExif());
  QCOMPARE(2.3, img->latitudeExif());
  QCOMPARE(10.2, img->altitudeExif());

  std::shared_ptr<Image> img2 = mProjectImg->findImage("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png");
  QCOMPARE("img002", img2->name());
  QCOMPARE("C:/Users/User01/Documents/fme/Projects/prj001/images/img002.png", img2->path());
  //QCOMPARE(0.51, img2->longitudeExif());
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

  QCOMPARE(result, mProjectImg->findImageId(value));
}

void TestProject::test_imageIterator()
{
  std::shared_ptr<Image> img;
  int i = 0;
  for (auto it = mProjectImg->imageBegin(); it != mProjectImg->imageEnd(); it++, i++){

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

void TestProject::test_clear()
{

}

QTEST_APPLESS_MAIN(TestProject)

#include "tst_project.moc"
