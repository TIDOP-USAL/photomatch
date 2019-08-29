#include <QtTest>

#include "fme/core/project.h"
#include "fme/core/settings.h"


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
                       "        <Session active=\"true\">"
                       "            <Name>session001</Name>"
                       "            <Description>Session 1</Description>"
                       "            <Preprocess>"
                       "                <Clahe>"
                       "                    <ClipLimit>50</ClipLimit>"
                       "                    <GridSize>"
                       "                        <Width>10</Width>"
                       "                        <Height>10</Height>"
                       "                    </GridSize>"
                       "                </Clahe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session002</Name>"
                       "            <Description>Session 2</Description>"
                       "            <Preprocess>"
                       "                <Cmbfhe>"
                       "                    <BlockSize>"
                       "                        <Width>7</Width>"
                       "                        <Height>7</Height>"
                       "                    </BlockSize>"
                       "                </Cmbfhe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session003</Name>"
                       "            <Description>Session 3</Description>"
                       "            <Preprocess>"
                       "                <Dhe>"
                       "                    <X>2</X>"
                       "                </Dhe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session004</Name>"
                       "            <Description>Session 4</Description>"
                       "            <Preprocess>"
                       "                <Fahe>"
                       "                    <BlockSize>"
                       "                        <Width>9</Width>"
                       "                        <Height>9</Height>"
                       "                    </BlockSize>"
                       "                </Fahe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session005</Name>"
                       "            <Description>Session 5</Description>"
                       "            <Preprocess>"
                       "                <Hmclahe>"
                       "                    <BlockSize>"
                       "                        <Width>15</Width>"
                       "                        <Height>15</Height>"
                       "                    </BlockSize>"
                       "                    <L>0.04</L>"
                       "                    <Phi>0.6</Phi>"
                       "                </Hmclahe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session006</Name>"
                       "            <Description>Session 6</Description>"
                       "            <Preprocess>"
                       "                <LceBsescs>"
                       "                    <BlockSize>"
                       "                        <Width>31</Width>"
                       "                        <Height>31</Height>"
                       "                    </BlockSize>"
                       "                </LceBsescs>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session007</Name>"
                       "            <Description>Session 7</Description>"
                       "            <Preprocess>"
                       "                <Msrcp>"
                       "                    <SmallScale>12</SmallScale>"
                       "                    <MidScale>105</MidScale>"
                       "                    <LargeScale>210</LargeScale>"
                       "                </Msrcp>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session008</Name>"
                       "            <Description>Session 8</Description>"
                       "            <Preprocess>"
                       "                <Noshp>"
                       "                    <BlockSize>"
                       "                        <Width>125</Width>"
                       "                        <Height>125</Height>"
                       "                    </BlockSize>"
                       "                </Noshp>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session009</Name>"
                       "            <Description>Session 9</Description>"
                       "            <Preprocess>"
                       "                <Pohe>"
                       "                    <BlockSize>"
                       "                        <Width>125</Width>"
                       "                        <Height>125</Height>"
                       "                    </BlockSize>"
                       "                </Pohe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session010</Name>"
                       "            <Description>Session 10</Description>"
                       "            <Preprocess>"
                       "                <Rswhe>"
                       "                    <HistogramDivisions>4</HistogramDivisions>"
                       "                    <HistogramCut>0</HistogramCut>"
                       "                </Rswhe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session011</Name>"
                       "            <Description>Session 11</Description>"
                       "            <Preprocess>"
                       "                 <Wallis>"
                       "                     <Contrast>1</Contrast>"
                       "                     <Brightness>0.2</Brightness>"
                       "                     <ImposedAverage>41</ImposedAverage>"
                       "                     <ImposedLocalStdDev>127</ImposedLocalStdDev>"
                       "                     <KernelSize>50</KernelSize>"
                       "                 </Wallis>"
                       "            </Preprocess>"
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
//                    while (xmlReader.readNextStartElement()) {

//                      std::shared_ptr<Preprocess> preprocess;

//                      if (xmlReader.name() == "Clahe") {

//                        std::shared_ptr<Clahe> clahe = std::make_shared<Clahe>();
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "ClipLimit") {
//                            clahe->setClipLimit(xmlReader.readElementText().toDouble());
//                          } else if (xmlReader.name() == "GridSize") {
//                            QSize gridSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                gridSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                gridSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            clahe->setTilesGridSize(gridSize);
//                          } else
//                            xmlReader.skipCurrentElement();

//                        }
//                        session->setPreprocess(clahe);

//                      } else if (xmlReader.name() == "Cmbfhe") {

//                        std::shared_ptr<Cmbfhe> cmbfhe(new Cmbfhe);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            cmbfhe->setBlockSize(blockSize);
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(cmbfhe);

//                      } else if (xmlReader.name() == "Dhe") {

//                        std::shared_ptr<Dhe> dhe = std::make_shared<Dhe>();
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "X") {
//                            dhe->setX(xmlReader.readElementText().toInt());
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(dhe);

//                      } else if (xmlReader.name() == "Fahe") {

//                        std::shared_ptr<Fahe> fahe(new Fahe);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            fahe->setBlockSize(blockSize);
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(fahe);

//                      } else if (xmlReader.name() == "Hmclahe") {

//                        std::shared_ptr<Hmclahe> hmclahe(new Hmclahe);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            hmclahe->setBlockSize(blockSize);
//                          } else if (xmlReader.name() == "L") {
//                            hmclahe->setL(xmlReader.readElementText().toDouble());
//                          } else if (xmlReader.name() == "Phi") {
//                            hmclahe->setPhi(xmlReader.readElementText().toDouble());
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(hmclahe);

//                      } else if (xmlReader.name() == "LceBsescs") {

//                        std::shared_ptr<LceBsescs> lceBsescs(new LceBsescs);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            lceBsescs->setBlockSize(blockSize);
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(lceBsescs);

//                      } else if (xmlReader.name() == "Msrcp") {

//                        std::shared_ptr<Msrcp> msrcp = std::make_shared<Msrcp>();
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "SmallScale") {
//                            msrcp->setSmallScale(xmlReader.readElementText().toInt());
//                          } else if (xmlReader.name() == "MidScale") {
//                            msrcp->setMidScale(xmlReader.readElementText().toInt());
//                          } else if (xmlReader.name() == "LargeScale") {
//                            msrcp->setLargeScale(xmlReader.readElementText().toInt());
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(msrcp);

//                      } else if (xmlReader.name() == "Noshp") {

//                        std::shared_ptr<Noshp> noshp(new Noshp);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            noshp->setBlockSize(blockSize);
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(noshp);

//                      } else if (xmlReader.name() == "Pohe") {

//                        std::shared_ptr<Pohe> pohe(new Pohe);
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "BlockSize") {
//                            QSize blockSize;
//                            while (xmlReader.readNextStartElement()) {
//                              if (xmlReader.name() == "Width") {
//                                blockSize.setWidth(xmlReader.readElementText().toInt());
//                              } else if (xmlReader.name() == "Height") {
//                                blockSize.setHeight(xmlReader.readElementText().toInt());
//                              } else
//                                xmlReader.skipCurrentElement();
//                            }
//                            pohe->setBlockSize(blockSize);
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(pohe);

//                      } else if (xmlReader.name() == "Rswhe") {

//                        std::shared_ptr<Rswhe> rswhe = std::make_shared<Rswhe>();
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "HistogramDivisions") {
//                            rswhe->setHistogramDivisions(xmlReader.readElementText().toInt());
//                          } else if (xmlReader.name() == "HistogramCut") {
//                            rswhe->setHistogramCut(static_cast<IRswhe::HistogramCut>(xmlReader.readElementText().toInt()));
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(rswhe);

//                      } else if (xmlReader.name() == "Wallis") {

//                        std::shared_ptr<Wallis> wallis = std::make_shared<Wallis>();
//                        while (xmlReader.readNextStartElement()) {
//                          if (xmlReader.name() == "Contrast") {
//                            wallis->setContrast(xmlReader.readElementText().toDouble());
//                          } else if (xmlReader.name() == "Brightness") {
//                            wallis->setBrightness(xmlReader.readElementText().toDouble());
//                          } else if (xmlReader.name() == "ImposedAverage") {
//                            wallis->setImposedAverage(xmlReader.readElementText().toInt());
//                          } else if (xmlReader.name() == "ImposedLocalStdDev") {
//                            wallis->setImposedLocalStdDev(xmlReader.readElementText().toInt());
//                          } else if (xmlReader.name() == "KernelSize") {
//                            wallis->setKernelSize(xmlReader.readElementText().toInt());
//                          } else
//                            xmlReader.skipCurrentElement();
//                        }
//                        session->setPreprocess(wallis);

//                      } else
//                        xmlReader.skipCurrentElement();

//                    }
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
  QCOMPARE(0, mProject->sessionCount());

  QCOMPARE(QString("prj001"), mProjectXml->name());
  QCOMPARE(QString("Project example"), mProjectXml->description());
  QCOMPARE(QString("C:/Users/User01/Documents/fme/Projects/prj001"), mProjectXml->projectFolder());
  QCOMPARE(QString("1.0"), mProjectXml->version());
  QCOMPARE(2, mProjectXml->imagesCount());
  QCOMPARE(11, mProjectXml->sessionCount());
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
//  std::shared_ptr<Session> session1 = mProjectXml->findSession("session001");
//  QCOMPARE("session001", session1->name());
//  QCOMPARE("Session 1", session1->description());
//  Preprocess *preprocess1 = session1->preprocess().get();
//  QCOMPARE(Preprocess::Type::clahe, preprocess1->type());
//  IClahe *clahe = dynamic_cast<IClahe *>(preprocess1);
//  QCOMPARE(50., clahe->clipLimit());
//  QCOMPARE(QSize(10, 10), clahe->tilesGridSize());

//  std::shared_ptr<Session> session2 = mProjectXml->findSession("session002");
//  QCOMPARE("session002", session2->name());
//  QCOMPARE("Session 2", session2->description());
//  Preprocess *preprocess2 = session2->preprocess().get();
//  QCOMPARE(Preprocess::Type::cmbfhe, preprocess2->type());
//  ICmbfhe *cmbfhe = dynamic_cast<ICmbfhe *>(preprocess2);
//  QCOMPARE(QSize(7, 7), cmbfhe->blockSize());

//  std::shared_ptr<Session> session3 = mProjectXml->findSession("session003");
//  QCOMPARE("session003", session3->name());
//  QCOMPARE("Session 3", session3->description());
//  Preprocess *preprocess3 = session3->preprocess().get();
//  QCOMPARE(Preprocess::Type::dhe, preprocess3->type());
//  IDhe *dhe = dynamic_cast<IDhe *>(preprocess3);
//  QCOMPARE(2, dhe->x());

//  std::shared_ptr<Session> session4 = mProjectXml->findSession("session004");
//  QCOMPARE("session004", session4->name());
//  QCOMPARE("Session 4", session4->description());
//  Preprocess *preprocess4 = session4->preprocess().get();
//  QCOMPARE(Preprocess::Type::fahe, preprocess4->type());
//  IFahe *fahe = dynamic_cast<IFahe *>(preprocess4);
//  QCOMPARE(QSize(9, 9), fahe->blockSize());

//  std::shared_ptr<Session> session5 = mProjectXml->findSession("session005");
//  QCOMPARE("session005", session5->name());
//  QCOMPARE("Session 5", session5->description());
//  Preprocess *preprocess5 = session5->preprocess().get();
//  QCOMPARE(Preprocess::Type::hmclahe, preprocess5->type());
//  IHmclahe *hmclahe = dynamic_cast<IHmclahe *>(preprocess5);
//  QCOMPARE(QSize(15, 15), hmclahe->blockSize());
//  QCOMPARE(0.04, hmclahe->l());
//  QCOMPARE(0.6, hmclahe->phi());

//  std::shared_ptr<Session> session6 = mProjectXml->findSession("session006");
//  QCOMPARE("session006", session6->name());
//  QCOMPARE("Session 6", session6->description());
//  Preprocess *preprocess6 = session6->preprocess().get();
//  QCOMPARE(Preprocess::Type::lce_bsescs, preprocess6->type());
//  ILceBsescs *lce_bsescs = dynamic_cast<LceBsescs *>(preprocess6);
//  QCOMPARE(QSize(31, 31), lce_bsescs->blockSize());

//  std::shared_ptr<Session> session7 = mProjectXml->findSession("session007");
//  QCOMPARE("session007", session7->name());
//  QCOMPARE("Session 7", session7->description());
//  Preprocess *preprocess7 = session7->preprocess().get();
//  QCOMPARE(Preprocess::Type::msrcp, preprocess7->type());
//  IMsrcp *msrcp = dynamic_cast<IMsrcp *>(preprocess7);
//  QCOMPARE(12, msrcp->smallScale());
//  QCOMPARE(105, msrcp->midScale());
//  QCOMPARE(210, msrcp->largeScale());

//  std::shared_ptr<Session> session8 = mProjectXml->findSession("session008");
//  QCOMPARE("session008", session8->name());
//  QCOMPARE("Session 8", session8->description());
//  Preprocess *preprocess8 = session8->preprocess().get();
//  QCOMPARE(Preprocess::Type::noshp, preprocess8->type());
//  INoshp *noshp = dynamic_cast<INoshp *>(preprocess8);
//  QCOMPARE(QSize(125, 125), noshp->blockSize());

//  std::shared_ptr<Session> session9 = mProjectXml->findSession("session009");
//  QCOMPARE("session009", session9->name());
//  QCOMPARE("Session 9", session9->description());
//  Preprocess *preprocess9 = session9->preprocess().get();
//  QCOMPARE(Preprocess::Type::pohe, preprocess9->type());
//  IPohe *pohe = dynamic_cast<IPohe *>(preprocess9);
//  QCOMPARE(QSize(125, 125), pohe->blockSize());

//  std::shared_ptr<Session> session10 = mProjectXml->findSession("session010");
//  QCOMPARE("session010", session10->name());
//  QCOMPARE("Session 10", session10->description());
//  Preprocess *preprocess10 = session10->preprocess().get();
//  QCOMPARE(Preprocess::Type::rswhe, preprocess10->type());
//  IRswhe *rswhe = dynamic_cast<IRswhe *>(preprocess10);
//  QCOMPARE(IRswhe::HistogramCut::by_mean, rswhe->histogramCut());
//  QCOMPARE(4, rswhe->histogramDivisions());

//  std::shared_ptr<Session> session11 = mProjectXml->findSession("session011");
//  QCOMPARE("session011", session11->name());
//  QCOMPARE("Session 11", session11->description());
//  Preprocess *preprocess11 = session11->preprocess().get();
//  QCOMPARE(Preprocess::Type::wallis, preprocess11->type());
//  IWallis *wallis = dynamic_cast<IWallis *>(preprocess11);
//  QCOMPARE(1., wallis->contrast());
//  QCOMPARE(0.2, wallis->brightness());
//  QCOMPARE(41, wallis->imposedAverage());
//  QCOMPARE(127, wallis->imposedLocalStdDev());
//  QCOMPARE(50, wallis->kernelSize());
}

void TestProject::test_findSessionId_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<size_t>("result");

  QTest::newRow("session001") << "session001" << size_t{0};
  QTest::newRow("session002") << "session002" << size_t{1};
  QTest::newRow("session003") << "session003" << size_t{2};
  QTest::newRow("session100") << "session100" << std::numeric_limits<size_t>().max();
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

    /// se comprueban unicamente las dos primeras sesiones
    if (i == 0){
      QCOMPARE("session001", (*it)->name());
      QCOMPARE("Session 1", (*it)->description());
    } else if (i == 1){
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
