#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/exportfeat/ExportFeaturesModel.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/image.h"
#include "photomatch/core/session.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>

using namespace photomatch;


class ProjectRWFake
  : public ProjectRW
{

public:

  ProjectRWFake()
  {
    mProjectFileText = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                       "<PhotoMatch version=\"1.0\">"
                       "    <General>"
                       "        <Name>prj001</Name>"
                       "        <ProjectFolder>C:/Users/User01/Documents/photomatch/Projects/prj001</ProjectFolder>"
                       "        <Description>Project example</Description>"
                       "    </General>"
                       "    <Images>"
                       "        <Image>"
                       "            <File>C:/Users/User01/Documents/photomatch/Projects/prj001/images/img001.png</File>"
                       "            <LongitudeExif>0.5</LongitudeExif>"
                       "            <LatitudeExif>2.3</LatitudeExif>"
                       "            <AltitudeExif>10.2</AltitudeExif>"
                       "        </Image>"
                       "        <Image>"
                       "            <File>C:/Users/User01/Documents/photomatch/Projects/prj001/images/img002.png</File>"
                       "            <LongitudeExif>0.51</LongitudeExif>"
                       "            <LatitudeExif>2.3</LatitudeExif>"
                       "            <AltitudeExif>10.1</AltitudeExif>"
                       "        </Image>"
                       "    </Images>"
                       "    <GroundTruth>C:/Users/User01/Documents/photomatch/Projects/prj001/GroundTruth.txt</GroundTruth>"
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
                       "</PhotoMatch>";
  }

  ~ProjectRWFake() override {}

  // IProjectIO interface
public:

  bool read(const QString &file, IProject &prj) override
  {

    QXmlStreamReader stream;
    stream.addData(mProjectFileText);

    if (stream.readNextStartElement()) {
      if (stream.name() == "PhotoMatch") {
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
          } else if (stream.name() == "GroundTruth") {
            prj.setGroundTruth(stream.readElementText());
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

//                      if (stream.name() == "Acebsf") {
//                        std::shared_ptr<IAcebsf> acebsf = std::make_shared<AcebsfProperties>();
//                        readACEBSF(&stream, acebsf.get());
//                        session->setPreprocess(acebsf);
//                      } else if (stream.name() == "Clahe") {
//                        std::shared_ptr<IClahe> clahe = std::make_shared<ClaheProperties>();
//                        readCLAHE(&stream, clahe.get());
//                        session->setPreprocess(clahe);
//                      } else if (stream.name() == "Cmbfhe") {
//                        std::shared_ptr<ICmbfhe> cmbfhe(new CmbfheProperties);
//                        readCMBFHE(&stream, cmbfhe.get());
//                        session->setPreprocess(cmbfhe);
//                      } else if (stream.name() == "Dhe") {
//                        std::shared_ptr<IDhe> dhe = std::make_shared<DheProperties>();
//                        readDHE(&stream, dhe.get());
//                        session->setPreprocess(dhe);
//                      } else if (stream.name() == "Fahe") {
//                        std::shared_ptr<IFahe> fahe(new FaheProperties);
//                        readFAHE(&stream, fahe.get());
//                        session->setPreprocess(fahe);
//                      } else if (stream.name() == "Hmclahe") {
//                        std::shared_ptr<IHmclahe> hmclahe(new HmclaheProperties);
//                        readHMCLAHE(&stream, hmclahe.get());
//                        session->setPreprocess(hmclahe);
//                      } else if (stream.name() == "LceBsescs") {
//                        std::shared_ptr<ILceBsescs> lceBsescs(new LceBsescsProperties);
//                        readLCEBSESCS(&stream, lceBsescs.get());
//                        session->setPreprocess(lceBsescs);
//                      } else if (stream.name() == "Msrcp") {
//                        std::shared_ptr<IMsrcp> msrcp = std::make_shared<MsrcpProperties>();
//                        readMSRCP(&stream, msrcp.get());
//                        session->setPreprocess(msrcp);
//                      } else if (stream.name() == "Noshp") {
//                        std::shared_ptr<INoshp> noshp(new NoshpProperties);
//                        readNOSHP(&stream, noshp.get());
//                        session->setPreprocess(noshp);
//                      } else if (stream.name() == "Pohe") {
//                        std::shared_ptr<IPohe> pohe(new PoheProperties);
//                        readPOHE(&stream, pohe.get());
//                        session->setPreprocess(pohe);
//                      } else if (stream.name() == "Rswhe") {
//                        std::shared_ptr<IRswhe> rswhe = std::make_shared<RswheProperties>();
//                        readRSWHE(&stream, rswhe.get());
//                        session->setPreprocess(rswhe);
//                      } else if (stream.name() == "Wallis") {
//                        std::shared_ptr<IWallis> wallis = std::make_shared<WallisProperties>();
//                        readWALLIS(&stream, wallis.get());
//                        session->setPreprocess(wallis);
//                      } else
                        stream.skipCurrentElement();
                    }
                  } else if (stream.name() == "FeatureDetector") {
                    while (stream.readNextStartElement()){
//                      if (stream.name() == "AGAST") {
//                        std::shared_ptr<IAgast> agast = std::make_shared<AgastProperties>();
//                        readAGAST(&stream, agast.get());
//                        session->setDetector(agast);
//                      } else if (stream.name() == "AKAZE") {
//                        std::shared_ptr<IAkaze> akaze = std::make_shared<AkazeProperties>();
//                        readAKAZE(&stream, akaze.get());
//                        session->setDetector(akaze);
//                      } else if (stream.name() == "BRISK") {
//                        std::shared_ptr<IBrisk> brisk = std::make_shared<BriskProperties>();
//                        readBRISK(&stream, brisk.get());
//                        session->setDetector(brisk);
//                      } else if (stream.name() == "FAST") {
//                        std::shared_ptr<IFast> fast = std::make_shared<FastProperties>();
//                        readFAST(&stream, fast.get());
//                        session->setDetector(fast);
//                      } else if (stream.name() == "GFTT") {
//                        std::shared_ptr<IGftt> gftt = std::make_shared<GfttProperties>();
//                        readGFTT(&stream, gftt.get());
//                        session->setDetector(gftt);
//                      } else if (stream.name() == "KAZE") {
//                        std::shared_ptr<IKaze> kaze = std::make_shared<KazeProperties>();
//                        readKAZE(&stream, kaze.get());
//                        session->setDetector(kaze);
//                      } else if (stream.name() == "MSD") {
//                        std::shared_ptr<IMsd> msd = std::make_shared<MsdProperties>();
//                        readMSD(&stream, msd.get());
//                        session->setDetector(msd);
//                      } else if (stream.name() == "MSER") {
//                        std::shared_ptr<IMser> mser = std::make_shared<MserProperties>();
//                        readMSER(&stream, mser.get());
//                        session->setDetector(mser);
//                      } else if (stream.name() == "ORB") {
//                        std::shared_ptr<IOrb> orb = std::make_shared<OrbProperties>();
//                        readORB(&stream, orb.get());
//                        session->setDetector(orb);
//                      } else if (stream.name() == "SIFT") {
//                        std::shared_ptr<ISift> sift = std::make_shared<SiftProperties>();
//                        readSIFT(&stream, sift.get());
//                        session->setDetector(sift);
//                      } else if (stream.name() == "STAR") {
//                        std::shared_ptr<IStar> star = std::make_shared<StarProperties>();
//                        readSTAR(&stream, star.get());
//                        session->setDetector(star);
//                      } else if (stream.name() == "SURF") {
//                        std::shared_ptr<ISurf> surf = std::make_shared<SurfProperties>();
//                        readSURF(&stream, surf.get());
//                        session->setDetector(surf);
//                      } else
                      stream.skipCurrentElement();
                    }
                  } else if (stream.name() == "FeatureDescriptor") {
                    while (stream.readNextStartElement()){
//                      if (stream.name() == "AKAZE") {
//                        std::shared_ptr<IAkaze> akaze = std::make_shared<AkazeProperties>();
//                        readAKAZE(&stream, akaze.get());
//                        session->setDescriptor(akaze);
//                      } else if (stream.name() == "BRIEF") {
//                        std::shared_ptr<IBrief> brief = std::make_shared<BriefProperties>();
//                        readBRIEF(&stream, brief.get());
//                        session->setDescriptor(brief);
//                      } else if (stream.name() == "BRISK") {
//                        std::shared_ptr<IBrisk> brisk = std::make_shared<BriskProperties>();
//                        readBRISK(&stream, brisk.get());
//                        session->setDescriptor(brisk);
//                      } else if (stream.name() == "DAISY") {
//                        std::shared_ptr<IDaisy> daisy = std::make_shared<DaisyProperties>();
//                        readDAISY(&stream, daisy.get());
//                        session->setDescriptor(daisy);
//                      } else if (stream.name() == "FREAK") {
//                        std::shared_ptr<IFreak> freak = std::make_shared<FreakProperties>();
//                        readFREAK(&stream, freak.get());
//                        session->setDescriptor(freak);
//                      } else if (stream.name() == "HOG") {
//                        std::shared_ptr<IHog> hog = std::make_shared<HogProperties>();
//                        readHOG(&stream, hog.get());
//                        session->setDescriptor(hog);
//                      } else if (stream.name() == "KAZE") {
//                        std::shared_ptr<IKaze> kaze = std::make_shared<KazeProperties>();
//                        readKAZE(&stream, kaze.get());
//                        session->setDescriptor(kaze);
//                      } else if (stream.name() == "LATCH") {
//                        std::shared_ptr<ILatch> latch = std::make_shared<LatchProperties>();
//                        readLATCH(&stream, latch.get());
//                        session->setDescriptor(latch);
//                      } else if (stream.name() == "LUCID") {
//                        std::shared_ptr<ILucid> lucid = std::make_shared<LucidProperties>();
//                        readLUCID(&stream, lucid.get());
//                        session->setDescriptor(lucid);
//                      } else if (stream.name() == "ORB") {
//                        std::shared_ptr<IOrb> orb = std::make_shared<OrbProperties>();
//                        readORB(&stream, orb.get());
//                        session->setDescriptor(orb);
//                      } else if (stream.name() == "SIFT") {
//                        std::shared_ptr<ISift> sift = std::make_shared<SiftProperties>();
//                        readSIFT(&stream, sift.get());
//                        session->setDescriptor(sift);
//                      } else if (stream.name() == "SURF") {
//                        std::shared_ptr<ISurf> surf = std::make_shared<SurfProperties>();
//                        readSURF(&stream, surf.get());
//                        session->setDescriptor(surf);
//                      } else
                      stream.skipCurrentElement();
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

//    stream.writeStartElement("PhotoMatch");
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
//    stream.writeEndElement(); // PhotoMatch

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
//        if (xmlReader.name() == "PhotoMatch") {
//          QString version = "0";
//          for (auto &attr : xmlReader.attributes()) {
//            if (attr.name().compare(QString("version")) == 0) {
//              version = attr.value().toString();
//              break;
//            }
//          }
//          if (version.compare(PHOTOMATCH_PROJECT_FILE_VERSION) < 0) {
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




class TestExportFeaturesModel
  : public QObject
{
  Q_OBJECT

public:

  TestExportFeaturesModel();
  ~TestExportFeaturesModel();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void test_constructor();
  void test_sessions();
  void test_sessionName();
  void test_activeSession();
  void test_sessionChange();
  void test_formats();
  void test_currentFormat_data();
  void test_currentFormat();
  void test_formatChange();
  void test_exportFiles();
  void test_exportPath_data();
  void test_exportPath();
  void test_exportPath_keyClick();
  void test_exportAll();
  void test_imageFiles();
  void test_dialogButtonBox();
  void test_clear();

private:

  ExportFeaturesModel *mExportFeaturesModel;
  IProjectRW *mProjectIOFake;
  IProject *mProject;
  IProjectModel *mProjectModel;
};

TestExportFeaturesModel::TestExportFeaturesModel()
  : mProjectIOFake(new ProjectRWFake),
    mProject(new Project),
    mProjectModel(new ProjectModel(mProjectIOFake, mProject))
{
  mExportFeaturesModel = new ExportFeaturesModel(mProjectModel);
}

TestExportFeaturesModel::~TestExportFeaturesModel()
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

  if (mExportFeaturesModel){
    delete mExportFeaturesModel;
    mExportFeaturesModel = nullptr;
  }
}

void TestExportFeaturesModel::initTestCase()
{
  mProjectModel->load("C:/Users/User01/Documents/photomatch/Projects/prj001/prj001.xml");
}

void TestExportFeaturesModel::cleanupTestCase()
{

}

void TestExportFeaturesModel::test_constructor()
{

  QCOMPARE(11, mExportFeaturesModel->sessions().size());
  QCOMPARE("session001", mExportFeaturesModel->sessions().at(0));
  QCOMPARE("session002", mExportFeaturesModel->sessions().at(1));
  QCOMPARE("session003", mExportFeaturesModel->sessions().at(2));
  QCOMPARE("session004", mExportFeaturesModel->sessions().at(3));
  QCOMPARE("session001", mExportFeaturesModel->sessionName());
  QCOMPARE("OpenCV XML", mExportFeaturesModel->formats().at(0));
  QCOMPARE("OpenCV YML", mExportFeaturesModel->formats().at(1));
  QCOMPARE("Plain text", mExportFeaturesModel->formats().at(2));

//  QCOMPARE(QStringList(), ExportFeaturesModel.exportFiles());
//  QCOMPARE(QString(), ExportFeaturesModel.exportPath());
//  QCOMPARE(true, ExportFeaturesModel.exportAll());

//  QCOMPARE(QString("OpenCV XML"), this->format());
//  QCOMPARE(QString("OpenCV XML"), this->mComboBoxFormat->currentText());
//  QCOMPARE(5, this->exportFiles().size());
//  QCOMPARE(5, this->mListWidgetfeatures->selectedItems().size());
//  QCOMPARE(QString(), this->exportPath());
//  QCOMPARE(QString(), this->mLineEditExportPath->text());
//  QCOMPARE(true, this->exportAll());
//  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());
}

void TestExportFeaturesModel::test_sessions()
{
//  QCOMPARE(3, this->mComboBoxSession->count());
//  QCOMPARE("Session01", this->mComboBoxSession->itemText(0));
//  QCOMPARE("Session02", this->mComboBoxSession->itemText(1));
  //  QCOMPARE("Session03", this->mComboBoxSession->itemText(2));
}

void TestExportFeaturesModel::test_sessionName()
{
  mExportFeaturesModel->sessionName();
}

void TestExportFeaturesModel::test_activeSession()
{
//  QFETCH(QString, value);
//  QFETCH(QString, result);

//  this->setActiveSession(value);
//  QCOMPARE(result, this->mComboBoxSession->currentText());
}

void TestExportFeaturesModel::test_sessionChange()
{
//  QSignalSpy spy_sessionChange(this, &ExportFeaturesModel::sessionChange);

//  this->mComboBoxSession->setCurrentText("Session02");

//  QCOMPARE(spy_sessionChange.count(), 1);

//  QList<QVariant> args = spy_sessionChange.takeFirst();
//  QCOMPARE(args.at(0).toString(), "Session02");

//  this->setActiveSession("Session03");
//  QCOMPARE(spy_sessionChange.count(), 0);
}

void TestExportFeaturesModel::test_formats()
{
//  QCOMPARE(3, this->mComboBoxFormat->count());
//  QCOMPARE("OpenCV XML", this->mComboBoxFormat->itemText(0));
//  QCOMPARE("OpenCV YML", this->mComboBoxFormat->itemText(1));
//  QCOMPARE("Plain text", this->mComboBoxFormat->itemText(2));
}

void TestExportFeaturesModel::test_currentFormat_data()
{
//  QTest::addColumn<QString>("value");
//  QTest::addColumn<QString>("result");

//  QTest::newRow("OpenCV XML") << "OpenCV XML" << "OpenCV XML";
//  QTest::newRow("OpenCV YML") << "OpenCV YML" << "OpenCV YML";
//  QTest::newRow("Plain text") << "Plain text" << "Plain text";
}

void TestExportFeaturesModel::test_currentFormat()
{
//  QFETCH(QString, value);
//  QFETCH(QString, result);

//  this->setCurrentFormat(value);
//  QCOMPARE(result, this->format());
//  QCOMPARE(result, this->mComboBoxFormat->currentText());
}

void TestExportFeaturesModel::test_formatChange()
{
//  QSignalSpy spy_formatChange(this, &ExportFeaturesModel::formatChange);

//  this->mComboBoxFormat->setCurrentText("OpenCV YML");

//  QCOMPARE(spy_formatChange.count(), 1);

//  QList<QVariant> args = spy_formatChange.takeFirst();
//  QCOMPARE(args.at(0).toString(), "OpenCV YML");

//  this->setCurrentFormat("OpenCV XML");
//  QCOMPARE(spy_formatChange.count(), 0);
}

void TestExportFeaturesModel::test_exportFiles()
{
//  QCOMPARE(5, this->exportFiles().size());

//  this->setExportAll(false);

//  QCOMPARE(5, this->exportFiles().size());

//  mListWidgetfeatures->clearSelection();

//  QCOMPARE(0, this->exportFiles().size());

//  mListWidgetfeatures->item(0)->setSelected(true);

//  QCOMPARE(1, this->exportFiles().size());

//  this->setExportAll(true);

//  QCOMPARE(5, this->exportFiles().size());


}

void TestExportFeaturesModel::test_exportPath_data()
{
//  QTest::addColumn<QString>("value");
//  QTest::addColumn<QString>("result");

//  QTest::newRow("C:/Users/Tido/Documents/photomatch/Projects")
//             << "C:/Users/Tido/Documents/photomatch/Projects"
//             << "C:/Users/Tido/Documents/photomatch/Projects";
//  QTest::newRow("C:/Users/user1/Documents/photomatch/Projects")
//             << "C:/Users/user1/Documents/photomatch/Projects"
//             << "C:/Users/user1/Documents/photomatch/Projects";

}

void TestExportFeaturesModel::test_exportPath()
{
//  QFETCH(QString, value);
//  QFETCH(QString, result);

//  this->setExportPath(value);
//  QCOMPARE(result, this->exportPath());
}

void TestExportFeaturesModel::test_exportPath_keyClick()
{
//  /// Simulación de entrada por teclado

//  QString exportPath = this->exportPath();

//  QTest::keyClick(this->mLineEditExportPath, '_');
//  QCOMPARE(this->exportPath(), exportPath.append("_"));

//  this->mLineEditExportPath->clear();
//  QTest::keyClicks(this->mLineEditExportPath, "C:/Users/user1/Documents/photomatch/Projects");
//  QCOMPARE(this->exportPath(), QString("C:/Users/user1/Documents/photomatch/Projects"));

}

void TestExportFeaturesModel::test_exportAll()
{
//  this->setExportAll(false);
//  QCOMPARE(false, this->exportAll());
//  QCOMPARE(false, this->mCheckBoxExportAll->isChecked());

//  this->setExportAll(true);
//  QCOMPARE(true, this->exportAll());
//  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());
}

void TestExportFeaturesModel::test_imageFiles()
{

}

void TestExportFeaturesModel::test_dialogButtonBox()
{

//  QSignalSpy spy_rejected(this, &ExportFeaturesModel::rejected);
//  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
//  QCOMPARE(spy_rejected.count(), 1);

//  mButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
//  QSignalSpy spy_accepted(this, &ExportFeaturesModel::accepted);
//  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Ok), Qt::LeftButton);
//  QCOMPARE(spy_accepted.count(), 1);

//  QSignalSpy spy_help(this, &ExportFeaturesModel::help);
//  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
//  QCOMPARE(spy_help.count(), 1);
}

void TestExportFeaturesModel::test_clear()
{
//  this->clear();

//  QCOMPARE(QString(), this->format());
//  QCOMPARE(QString(), this->mComboBoxFormat->currentText());
//  QCOMPARE(0, this->exportFiles().size());
//  QCOMPARE(0, this->mListWidgetfeatures->selectedItems().size());
//  QCOMPARE(QString(), this->exportPath());
//  QCOMPARE(QString(), this->mLineEditExportPath->text());
//  QCOMPARE(true, this->exportAll());
//  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());

//  /// Recupero la configuración ya que se llama a test_clear antes de finalizar todos los test
//  this->setSessions(sessions);
//  this->setFormats(formats);
//  this->setImageFiles(images);
}

QTEST_MAIN(TestExportFeaturesModel)

#include "tst_exportfeaturesmodel.moc"
