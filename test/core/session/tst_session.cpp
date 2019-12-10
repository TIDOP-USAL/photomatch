#include <QtTest>

#include "photomatch/core/session.h"
#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/matcher.h"

using namespace photomatch;


class TestSession : public QObject
{
  Q_OBJECT

public:

  TestSession();
  ~TestSession();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_constructor();
  void test_name_data();
  void test_name();
  void test_description_data();
  void test_description();
  void test_maxImageSize_data();
  void test_maxImageSize();
  void test_fullImageSize();
  void test_preprocess();
  void test_detector();
  void test_descriptor();
  void test_matcher();
  void test_robustMatcherRefinement();
  void test_preprocessImages();
  void test_features();
  void test_matches();
  void test_clear();

protected:

  ISession *mSession;
};

TestSession::TestSession()
  : mSession(new Session)
{

}

TestSession::~TestSession()
{
  if (mSession) {
    delete mSession;
    mSession = nullptr;
  }
}

void TestSession::initTestCase()
{
  
}

void TestSession::cleanupTestCase()
{

}

void TestSession::test_constructor()
{
  Session session;
  QCOMPARE(QString(), session.name());
  QCOMPARE(QString(), session.description());
  QCOMPARE(2000, session.maxImageSize());
  QCOMPARE(false, session.fullImageSize());
  QCOMPARE(nullptr, session.preprocess());
  QCOMPARE(nullptr, session.detector());
  QCOMPARE(nullptr, session.descriptor());
  QCOMPARE(nullptr, session.matcher());
  QCOMPARE(nullptr, session.robustMatcherRefinement());
  QCOMPARE(std::vector<QString>(), session.preprocessImages());
  QCOMPARE(std::vector<QString>(), session.features());
}

void TestSession::test_name_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Session01") << "Session01" << "Session01";
  QTest::newRow("Session02") << "Session02" << "Session02";
}

void TestSession::test_name()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSession->setName(value);
  QCOMPARE(result, mSession->name());
}

void TestSession::test_description_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Description1") << "Descripción de la sesión 1" << "Descripción de la sesión 1";
  QTest::newRow("Description2") << "Descripción de la sesión 2" << "Descripción de la sesión 2";
}

void TestSession::test_description()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSession->setDescription(value);
  QCOMPARE(result, mSession->description());
}

void TestSession::test_maxImageSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("2000") << 2000 << 2000;
  QTest::newRow("2500") << 2500 << 2500;
  QTest::newRow("3000") << 3000 << 3000;
}

void TestSession::test_maxImageSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSession->setMaxImageSize(value);
  QCOMPARE(result, mSession->maxImageSize());
}

void TestSession::test_fullImageSize()
{
  mSession->setFullImageSize(true);
  QCOMPARE(true, mSession->fullImageSize());
  mSession->setFullImageSize(false);
  QCOMPARE(false, mSession->fullImageSize());
}

void TestSession::test_preprocess()
{
  std::shared_ptr<Preprocess> preprocess(new AcebsfProperties());
  mSession->setPreprocess(preprocess);

  std::shared_ptr<Preprocess> preprocess2 = mSession->preprocess();
  QCOMPARE(QString("ACEBSF"), preprocess2->name());
}

void TestSession::test_detector()
{
  std::shared_ptr<Feature> detector(new AgastProperties());
  mSession->setDetector(detector);

  std::shared_ptr<Feature> detector2 = mSession->detector();
  QCOMPARE(QString("AGAST"), detector2->name());
}

void TestSession::test_descriptor()
{
  std::shared_ptr<Feature> descriptor(new BriefProperties());
  mSession->setDescriptor(descriptor);

  std::shared_ptr<Feature> descriptor2 = mSession->descriptor();
  QCOMPARE(QString("BRIEF"), descriptor2->name());
}

void TestSession::test_matcher()
{
  std::shared_ptr<Match> matcher(new BruteForceMatcher());
  mSession->setMatcher(matcher);

  std::shared_ptr<Match> matcher2 = mSession->matcher();
  QCOMPARE(QString("Brute Force Matching"), matcher2->name());
}

void TestSession::test_robustMatcherRefinement()
{
  std::shared_ptr<IRobustMatcherRefinement> robustMatcherRefinement(new RobustMatcherProperties());
  robustMatcherRefinement->setGeometricTest(IRobustMatcherRefinement::GeometricTest::homography);
  mSession->setRobustMatcherRefinement(robustMatcherRefinement);

  QCOMPARE(IRobustMatcherRefinement::GeometricTest::homography, mSession->robustMatcherRefinement()->geometricTest());
}

void TestSession::test_preprocessImages()
{
  mSession->addPreprocessImage("c://image01.jpg");
  mSession->addPreprocessImage("c://image02.jpg");
  mSession->addPreprocessImage("c://image03.jpg");
  QCOMPARE(3, mSession->preprocessImages().size());
  mSession->deletePreprocessImage("c://image02.jpg");
  QCOMPARE(2, mSession->preprocessImages().size());
  QCOMPARE("c://image03.jpg", mSession->preprocessImage("image03"));
  mSession->deletePreprocessImages();
  QCOMPARE(0, mSession->preprocessImages().size());
}

void TestSession::test_features()
{
  mSession->addFeatures("c://image01.xml");
  mSession->addFeatures("c://image02.xml");
  mSession->addFeatures("c://image03.xml");
  QCOMPARE(3, mSession->features().size());
  mSession->deleteFeatures("c://image02.xml");
  QCOMPARE(2, mSession->features().size());
  QCOMPARE("c://image03.xml", mSession->features("image03"));
  mSession->deleteFeatures();
  QCOMPARE(0, mSession->features().size());
}

void TestSession::test_matches()
{
  mSession->addMatches("image01", "image02", "c://image01_image02.xml");
  mSession->addMatches("image01", "image03", "c://image01_image03.xml");
  mSession->addMatches("image02", "image03", "c://image02_image03.xml");
  QCOMPARE(2, mSession->matches("image01").size());
  mSession->deleteMatches("image01", "image03", "c://image01_image03.xml");
  QCOMPARE(1, mSession->matches("image01").size());
}

void TestSession::test_clear()
{
  mSession->setName("Session03");
  mSession->setDescription("Descripción de la sesión 3");
  mSession->setMaxImageSize(3000);
  mSession->setFullImageSize(true);

  mSession->clear();
  
  QCOMPARE(QString(), mSession->name());
  QCOMPARE(QString(), mSession->description());
  QCOMPARE(2000, mSession->maxImageSize());
  QCOMPARE(false, mSession->fullImageSize());
}

QTEST_APPLESS_MAIN(TestSession)

#include "tst_session.moc"
