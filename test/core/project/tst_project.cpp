#include <QtTest>

#include "fme/core/project.h"
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

using namespace fme;

class ProjectRWFake
  : public ProjectRW
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
                       "            <MaxImageSize>2000</MaxImageSize>"
                       "            <Preprocess>"
                       "                <Clahe>"
                       "                    <ClipLimit>50</ClipLimit>"
                       "                    <GridSize>"
                       "                        <Width>10</Width>"
                       "                        <Height>10</Height>"
                       "                    </GridSize>"
                       "                </Clahe>"
                       "            </Preprocess>"
                       "            <FeatureDetector>"
                       "                <SIFT>"
                       "                    <FeaturesNumber>5000</FeaturesNumber>"
                       "                    <OctaveLayers>3</OctaveLayers>"
                       "                    <ContrastThreshold>0.04</ContrastThreshold>"
                       "                    <EdgeThreshold>10</EdgeThreshold>"
                       "                    <Sigma>1.6</Sigma>"
                       "                </SIFT>"
                       "            </FeatureDetector>"
                       "            <FeatureDescriptor>"
                       "                <SIFT>"
                       "                    <FeaturesNumber>5000</FeaturesNumber>"
                       "                    <OctaveLayers>3</OctaveLayers>"
                       "                    <ContrastThreshold>0.04</ContrastThreshold>"
                       "                    <EdgeThreshold>10</EdgeThreshold>"
                       "                    <Sigma>1.6</Sigma>"
                       "                </SIFT>"
                       "            </FeatureDescriptor>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session002</Name>"
                       "            <Description>Session 2</Description>"
                       "            <MaxImageSize>3000</MaxImageSize>"
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
                       "            <MaxImageSize>2000</MaxImageSize>"
                       "            <Preprocess>"
                       "                <Dhe>"
                       "                    <X>2</X>"
                       "                </Dhe>"
                       "            </Preprocess>"
                       "        </Session>"
                       "        <Session>"
                       "            <Name>session004</Name>"
                       "            <Description>Session 4</Description>"
                       "            <MaxImageSize>2000</MaxImageSize>"
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
                       "            <MaxImageSize>2500</MaxImageSize>"
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
                       "            <MaxImageSize>-1</MaxImageSize>"
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
                       "            <MaxImageSize>2000</MaxImageSize>"
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
                       "            <MaxImageSize>2000</MaxImageSize>"
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
                       "            <MaxImageSize>-1</MaxImageSize>"
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
                       "            <MaxImageSize>2000</MaxImageSize>"
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
                       "            <MaxImageSize>2000</MaxImageSize>"
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

    QXmlStreamReader stream;
    stream.addData(mProjectFileText);

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
                  } else if (stream.name() == "MaxImageSize") {
                    session->setMaxImageSize(stream.readElementText().toInt());
                  } else if (stream.name() == "Preprocess") {
                    while (stream.readNextStartElement()) {

                      if (stream.name() == "Acebsf") {
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
                      if (stream.name() == "AKAZE") {
                        std::shared_ptr<IAkaze> akaze = std::make_shared<AkazeProperties>();
                        readAKAZE(&stream, akaze.get());
                        session->setDescriptor(akaze);
                      } else if (stream.name() == "BRIEF") {
                        std::shared_ptr<IBrief> brief = std::make_shared<BriefProperties>();
                        readBRIEF(&stream, brief.get());
                        session->setDescriptor(brief);
                      } else if (stream.name() == "BRISK") {
                        std::shared_ptr<IBrisk> brisk = std::make_shared<BriskProperties>();
                        readBRISK(&stream, brisk.get());
                        session->setDescriptor(brisk);
                      } else if (stream.name() == "DAISY") {
                        std::shared_ptr<IDaisy> daisy = std::make_shared<DaisyProperties>();
                        readDAISY(&stream, daisy.get());
                        session->setDescriptor(daisy);
                      } else if (stream.name() == "FREAK") {
                        std::shared_ptr<IFreak> freak = std::make_shared<FreakProperties>();
                        readFREAK(&stream, freak.get());
                        session->setDescriptor(freak);
                      } else if (stream.name() == "HOG") {
                        std::shared_ptr<IHog> hog = std::make_shared<HogProperties>();
                        readHOG(&stream, hog.get());
                        session->setDescriptor(hog);
                      } else if (stream.name() == "KAZE") {
                        std::shared_ptr<IKaze> kaze = std::make_shared<KazeProperties>();
                        readKAZE(&stream, kaze.get());
                        session->setDescriptor(kaze);
                      } else if (stream.name() == "LATCH") {
                        std::shared_ptr<ILatch> latch = std::make_shared<LatchProperties>();
                        readLATCH(&stream, latch.get());
                        session->setDescriptor(latch);
                      } else if (stream.name() == "LUCID") {
                        std::shared_ptr<ILucid> lucid = std::make_shared<LucidProperties>();
                        readLUCID(&stream, lucid.get());
                        session->setDescriptor(lucid);
                      } else if (stream.name() == "ORB") {
                        std::shared_ptr<IOrb> orb = std::make_shared<OrbProperties>();
                        readORB(&stream, orb.get());
                        session->setDescriptor(orb);
                      } else if (stream.name() == "SIFT") {
                        std::shared_ptr<ISift> sift = std::make_shared<SiftProperties>();
                        readSIFT(&stream, sift.get());
                        session->setDescriptor(sift);
                      } else if (stream.name() == "SURF") {
                        std::shared_ptr<ISurf> surf = std::make_shared<SurfProperties>();
                        readSURF(&stream, surf.get());
                        session->setDescriptor(surf);
                      }
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
  std::shared_ptr<Session> session1 = mProjectXml->findSession("session001");
  QCOMPARE("session001", session1->name());
  QCOMPARE("Session 1", session1->description());
  QCOMPARE(2000, session1->maxImageSize());
  QCOMPARE(false, session1->fullImageSize());
  Preprocess *preprocess1 = session1->preprocess().get();
  QCOMPARE(Preprocess::Type::clahe, preprocess1->type());
  IClahe *clahe = dynamic_cast<IClahe *>(preprocess1);
  QCOMPARE(50., clahe->clipLimit());
  QCOMPARE(QSize(10, 10), clahe->tilesGridSize());
  Feature *detector = session1->detector().get();
  QCOMPARE(Feature::Type::sift, detector->type());
  ISift *sift_detector = dynamic_cast<ISift *>(detector);
  QCOMPARE(5000, sift_detector->featuresNumber());
  QCOMPARE(3, sift_detector->octaveLayers());
  QCOMPARE(0.04, sift_detector->contrastThreshold());
  QCOMPARE(10, sift_detector->edgeThreshold());
  QCOMPARE(1.6, sift_detector->sigma());
  Feature *descriptor = session1->descriptor().get();
  ISift *sift_descriptor = dynamic_cast<ISift *>(descriptor);
  QCOMPARE(Feature::Type::sift, sift_descriptor->type());
  QCOMPARE(5000, sift_descriptor->featuresNumber());
  QCOMPARE(3, sift_descriptor->octaveLayers());
  QCOMPARE(0.04, sift_descriptor->contrastThreshold());
  QCOMPARE(10, sift_descriptor->edgeThreshold());
  QCOMPARE(1.6, sift_descriptor->sigma());

  std::shared_ptr<Session> session2 = mProjectXml->findSession("session002");
  QCOMPARE("session002", session2->name());
  QCOMPARE("Session 2", session2->description());
  QCOMPARE(3000, session2->maxImageSize());
  QCOMPARE(false, session2->fullImageSize());
  Preprocess *preprocess2 = session2->preprocess().get();
  QCOMPARE(Preprocess::Type::cmbfhe, preprocess2->type());
  ICmbfhe *cmbfhe = dynamic_cast<ICmbfhe *>(preprocess2);
  QCOMPARE(QSize(7, 7), cmbfhe->blockSize());

  std::shared_ptr<Session> session3 = mProjectXml->findSession("session003");
  QCOMPARE("session003", session3->name());
  QCOMPARE("Session 3", session3->description());
  QCOMPARE(2000, session3->maxImageSize());
  QCOMPARE(false, session3->fullImageSize());
  Preprocess *preprocess3 = session3->preprocess().get();
  QCOMPARE(Preprocess::Type::dhe, preprocess3->type());
  IDhe *dhe = dynamic_cast<IDhe *>(preprocess3);
  QCOMPARE(2, dhe->x());

  std::shared_ptr<Session> session4 = mProjectXml->findSession("session004");
  QCOMPARE("session004", session4->name());
  QCOMPARE("Session 4", session4->description());
  QCOMPARE(2000, session4->maxImageSize());
  QCOMPARE(false, session4->fullImageSize());
  Preprocess *preprocess4 = session4->preprocess().get();
  QCOMPARE(Preprocess::Type::fahe, preprocess4->type());
  IFahe *fahe = dynamic_cast<IFahe *>(preprocess4);
  QCOMPARE(QSize(9, 9), fahe->blockSize());

  std::shared_ptr<Session> session5 = mProjectXml->findSession("session005");
  QCOMPARE("session005", session5->name());
  QCOMPARE("Session 5", session5->description());
  QCOMPARE(2500, session5->maxImageSize());
  QCOMPARE(false, session5->fullImageSize());
  Preprocess *preprocess5 = session5->preprocess().get();
  QCOMPARE(Preprocess::Type::hmclahe, preprocess5->type());
  IHmclahe *hmclahe = dynamic_cast<IHmclahe *>(preprocess5);
  QCOMPARE(QSize(15, 15), hmclahe->blockSize());
  QCOMPARE(0.04, hmclahe->l());
  QCOMPARE(0.6, hmclahe->phi());

  std::shared_ptr<Session> session6 = mProjectXml->findSession("session006");
  QCOMPARE("session006", session6->name());
  QCOMPARE("Session 6", session6->description());
  QCOMPARE(-1, session6->maxImageSize());
  QCOMPARE(true, session6->fullImageSize());
  Preprocess *preprocess6 = session6->preprocess().get();
  QCOMPARE(Preprocess::Type::lce_bsescs, preprocess6->type());
  ILceBsescs *lce_bsescs = dynamic_cast<ILceBsescs *>(preprocess6);
  QCOMPARE(QSize(31, 31), lce_bsescs->blockSize());

  std::shared_ptr<Session> session7 = mProjectXml->findSession("session007");
  QCOMPARE("session007", session7->name());
  QCOMPARE("Session 7", session7->description());
  QCOMPARE(2000, session7->maxImageSize());
  QCOMPARE(false, session7->fullImageSize());
  Preprocess *preprocess7 = session7->preprocess().get();
  QCOMPARE(Preprocess::Type::msrcp, preprocess7->type());
  IMsrcp *msrcp = dynamic_cast<IMsrcp *>(preprocess7);
  QCOMPARE(12, msrcp->smallScale());
  QCOMPARE(105, msrcp->midScale());
  QCOMPARE(210, msrcp->largeScale());

  std::shared_ptr<Session> session8 = mProjectXml->findSession("session008");
  QCOMPARE("session008", session8->name());
  QCOMPARE("Session 8", session8->description());
  QCOMPARE(2000, session8->maxImageSize());
  QCOMPARE(false, session8->fullImageSize());
  Preprocess *preprocess8 = session8->preprocess().get();
  QCOMPARE(Preprocess::Type::noshp, preprocess8->type());
  INoshp *noshp = dynamic_cast<INoshp *>(preprocess8);
  QCOMPARE(QSize(125, 125), noshp->blockSize());

  std::shared_ptr<Session> session9 = mProjectXml->findSession("session009");
  QCOMPARE("session009", session9->name());
  QCOMPARE("Session 9", session9->description());
  QCOMPARE(-1, session9->maxImageSize());
  QCOMPARE(true, session9->fullImageSize());
  Preprocess *preprocess9 = session9->preprocess().get();
  QCOMPARE(Preprocess::Type::pohe, preprocess9->type());
  IPohe *pohe = dynamic_cast<IPohe *>(preprocess9);
  QCOMPARE(QSize(125, 125), pohe->blockSize());

  std::shared_ptr<Session> session10 = mProjectXml->findSession("session010");
  QCOMPARE("session010", session10->name());
  QCOMPARE("Session 10", session10->description());
  QCOMPARE(2000, session10->maxImageSize());
  QCOMPARE(false, session10->fullImageSize());
  Preprocess *preprocess10 = session10->preprocess().get();
  QCOMPARE(Preprocess::Type::rswhe, preprocess10->type());
  IRswhe *rswhe = dynamic_cast<IRswhe *>(preprocess10);
  QCOMPARE(IRswhe::HistogramCut::by_mean, rswhe->histogramCut());
  QCOMPARE(4, rswhe->histogramDivisions());

  std::shared_ptr<Session> session11 = mProjectXml->findSession("session011");
  QCOMPARE("session011", session11->name());
  QCOMPARE("Session 11", session11->description());
  QCOMPARE(2000, session11->maxImageSize());
  QCOMPARE(false, session11->fullImageSize());
  Preprocess *preprocess11 = session11->preprocess().get();
  QCOMPARE(Preprocess::Type::wallis, preprocess11->type());
  IWallis *wallis = dynamic_cast<IWallis *>(preprocess11);
  QCOMPARE(1., wallis->contrast());
  QCOMPARE(0.2, wallis->brightness());
  QCOMPARE(41, wallis->imposedAverage());
  QCOMPARE(127, wallis->imposedLocalStdDev());
  QCOMPARE(50, wallis->kernelSize());
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
