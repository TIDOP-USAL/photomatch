#include <QtTest>
#include <QCoreApplication>

#include "photomatch/core/features/groundtruth.h"

using namespace photomatch;

class GroundTruthFake
  : public GroundTruth
{

public:

  GroundTruthFake() {}


  // GroundTruth interface

public:

  void read(const QString &gtFile) override
  {

    std::istringstream  ifs(mGTFile);

    std::string line;

    while (std::getline(ifs, line)) {

      QStringList list = QString(line.c_str()).split(";");
      if (list.size() == 6){
        std::shared_ptr<HomologusPoints> homologus = this->findPair(list[0], list[1]);
        QPointF pt_query;
        QPointF pt_train;
        if (homologus != nullptr){
          pt_query = QPointF(list[2].toDouble(), list[3].toDouble());
          pt_train = QPointF(list[4].toDouble(), list[5].toDouble());
        } else {
          homologus = this->findPair(list[1], list[0]);
          if (homologus != nullptr){
            pt_query = QPointF(list[4].toDouble(), list[5].toDouble());
            pt_train = QPointF(list[2].toDouble(), list[3].toDouble());
            homologus->addPoints(pt_query, pt_train);
          } else {
            homologus = std::make_shared<HomologusPoints>(list[0], list[1]);
            mHomologusPoints.push_back(homologus);
            pt_query = QPointF(list[2].toDouble(), list[3].toDouble());
            pt_train = QPointF(list[4].toDouble(), list[5].toDouble());
          }
        }

        homologus->addPoints(pt_query, pt_train);
      }

    }
  }

protected:

  std::string mGTFile = "005_005_147000214;005_006_147000213;2276.94;3586.31;2096.43;5294.68\n"
                    "005_005_147000214;005_006_147000213;1494.52;4057.71;1210.06;5884.34\n"
                    "005_005_147000214;005_006_147000213;4664.62;3725.57;4767.65;5489.22\n"
                    "005_005_147000214;005_006_147000213;4433.99;971.398;4497.41;2102.29\n"
                    "005_005_147000214;005_006_147000213;937.226;802.915;675.335;1874.46\n"
                    "005_005_147000214;005_006_147000213;3421.42;3514.49;3376.71;5212.27\n"
                    "005_005_147000214;005_006_147000213;3421.42;3514.49;3376.71;5212.27\n"
                    "005_005_147000214;005_006_147000213;7334.76;3341.71;7752.75;5043.43\n"
                    "005_005_147000214;005_006_147000213;7334.76;3341.71;7752.75;5043.43\n"
                    "005_005_147000214;005_006_147000213;7275.18;1197.29;7618.3;2401.95\n"
                    "005_005_147000214;005_006_147000213;7275.18;1197.29;7618.3;2401.95\n"
                    "005_005_147000214;005_006_147000213;3268.91;2817.98;3210.62;4344.49\n"
                    "005_005_147000214;005_007_147000212;937.552;802.929;431.274;3182.37\n"
                    "005_005_147000214;005_007_147000212;942.392;665.027;445.547;2982.3\n"
                    "005_005_147000214;005_007_147000212;715.334;44.9071;214.255;2092.09\n"
                    "005_005_147000214;005_007_147000212;1492.87;58.8975;1133.82;2120.78\n"
                    "005_005_147000214;005_007_147000212;4070.67;215.713;4198.56;2386.03\n"
                    "005_005_147000214;005_007_147000212;5007.42;426.09;5323.25;2685.53\n"
                    "005_005_147000214;005_007_147000212;7286.03;32.0083;8037.66;2151.53\n"
                    "005_005_147000214;005_007_147000212;6625.41;1625.62;7347.28;4475.21\n"
                    "005_005_147000214;005_007_147000212;6873.55;2317.75;7702.67;5538.04\n"
                    "005_005_147000214;005_007_147000212;5769.2;1991.92;6314.81;5037.15\n"
                    "005_006_147000213;005_007_147000212;6870.26;1197.08;7244.62;2379.75\n"
                    "005_006_147000213;005_007_147000212;7444.2;2390.01;7919.63;3831.56\n"
                    "005_006_147000213;005_007_147000212;7196.27;3834.09;7698.48;5643.19\n"
                    "005_006_147000213;005_007_147000212;5865.75;4052.23;6204.6;5914.63\n"
                    "005_006_147000213;005_007_147000212;4273.56;3916.02;4411.47;5723.34\n"
                    "005_006_147000213;005_007_147000212;2889.91;3851.09;2859.22;5634.21\n"
                    "005_006_147000213;005_007_147000212;486.519;3740.57;173.771;5487.01\n"
                    "005_006_147000213;005_007_147000212;2365.77;2927.42;2281.19;4478.54\n"
                    "005_006_147000213;005_007_147000212;2778.79;2693.45;2741.28;4191.19\n"
                    "005_006_147000213;005_007_147000212;2690.65;3104.81;2641.42;4701.7\n"
                    "005_006_147000213;005_007_147000212;4151.38;2003.55;4261.12;3349.73\n"
                    "005_006_147000213;005_007_147000212;4105.89;1193.62;4205.09;2371.6\n"
                    "005_006_147000213;005_007_147000212;3194.39;758.281;3207.17;1840.13\n"
                    "005_005_147000214;006_005_148000187;946.504;742.393;2457.57;807.152\n"
                    "005_005_147000214;006_005_148000187;921.09;1319.58;2502.23;1384.12\n"
                    "005_005_147000214;006_005_148000187;2386.85;1666.26;4023.2;1751.12\n"
                    "005_005_147000214;006_005_148000187;2698.68;1499.87;4317.24;1587.15\n"
                    "005_005_147000214;006_005_148000187;4217.38;959.15;5781.5;1063.28\n"
                    "005_005_147000214;006_005_148000187;5702.84;699.558;7240.79;821.151\n"
                    "005_005_147000214;006_005_148000187;6001.51;1486.84;7645.74;1613.99\n"
                    "005_005_147000214;006_005_148000187;5659.89;2556.91;7448.43;2684.95\n"
                    "005_005_147000214;006_005_148000187;5035.33;3090.13;6895.42;3212.43\n"
                    "005_005_147000214;006_005_148000187;4779.59;2712.03;6582.84;2829.12\n"
                    "005_005_147000214;006_005_148000187;4978.03;4079.67;6946.37;4207.26\n"
                    "005_005_147000214;006_005_148000187;3384.42;3708.21;5287.57;3814.23\n"
                    "005_005_147000214;006_005_148000187;3058.02;3479.33;4930.53;3580.85\n"
                    "005_005_147000214;006_005_148000187;1528.68;4252.88;3504.65;4339.06\n"
                    "005_005_147000214;006_005_148000187;652.539;4959.93;2736.93;5043.34\n"
                    "005_005_147000214;006_005_148000187;659.473;2567.26;2391.99;2634.08\n"
                    "005_005_147000214;006_005_148000187;738.366;2024.85;2404.88;2089.66\n"
                    "005_005_147000214;006_005_148000187;3032.54;2566.52;4790.42;2661.77\n";
};




class TestGroundTruth
  : public QObject
{
  Q_OBJECT

public:

  TestGroundTruth();
  ~TestGroundTruth();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_findPair();
  void test_pair();
  void test_queryPoints();
  void test_trainPoints();

private:

  GroundTruthFake *mGroundTruth;

};

TestGroundTruth::TestGroundTruth()
  : mGroundTruth(new GroundTruthFake)
{

}

TestGroundTruth::~TestGroundTruth()
{
}

void TestGroundTruth::initTestCase()
{
  mGroundTruth->read("...");
}

void TestGroundTruth::cleanupTestCase()
{

}

void TestGroundTruth::test_findPair()
{
  std::shared_ptr<HomologusPoints> h = mGroundTruth->findPair("005_005_147000214","005_006_147000213");
  QCOMPARE(12, h->size());
  QCOMPARE("005_005_147000214", h->idImg1());
  QCOMPARE("005_006_147000213", h->idImg2());
  QCOMPARE(2276.94, h->at(0).first.x());
  QCOMPARE(3586.31, h->at(0).first.y());
  QCOMPARE(2096.43, h->at(0).second.x());
  QCOMPARE(5294.68, h->at(0).second.y());

  std::shared_ptr<HomologusPoints> h_null = mGroundTruth->findPair("","");
  QCOMPARE(nullptr, h_null);
}

void TestGroundTruth::test_pair()
{
  std::shared_ptr<HomologusPoints> h = mGroundTruth->pair("005_005_147000214","005_006_147000213");
  QCOMPARE(12, h->size());
  QCOMPARE("005_005_147000214", h->idImg1());
  QCOMPARE("005_006_147000213", h->idImg2());
  QCOMPARE(2276.94, h->at(0).first.x());
  QCOMPARE(3586.31, h->at(0).first.y());
  QCOMPARE(2096.43, h->at(0).second.x());
  QCOMPARE(5294.68, h->at(0).second.y());

  //005_005_147000214;006_006_148000188;946.22;742.118;2298.68;1842.18
  std::shared_ptr<HomologusPoints> h_new = mGroundTruth->pair("005_005_147000214","006_006_148000188");
  QCOMPARE(0, h_new->size());
  QCOMPARE("005_005_147000214", h_new->idImg1());
  QCOMPARE("006_006_148000188", h_new->idImg2());
  h_new->addPoints(QPointF(946.22,742.118), QPointF(2298.68,1842.18));
  QCOMPARE(1, h_new->size());
  QCOMPARE(946.22, h_new->at(0).first.x());
  QCOMPARE(742.118, h_new->at(0).first.y());
  QCOMPARE(2298.68, h_new->at(0).second.x());
  QCOMPARE(1842.18, h_new->at(0).second.y());
}

void TestGroundTruth::test_queryPoints()
{
  std::shared_ptr<HomologusPoints> h = mGroundTruth->findPair("005_005_147000214","005_006_147000213");

  QCOMPARE(2276.94f, h->queryPoints().at(0).x);
  QCOMPARE(3586.31f, h->queryPoints().at(0).y);
  QCOMPARE(1494.52f, h->queryPoints().at(1).x);
  QCOMPARE(4057.71f, h->queryPoints().at(1).y);
  QCOMPARE(4664.62f, h->queryPoints().at(2).x);
  QCOMPARE(3725.57f, h->queryPoints().at(2).y);
}

void TestGroundTruth::test_trainPoints()
{
  std::shared_ptr<HomologusPoints> h = mGroundTruth->findPair("005_005_147000214","005_006_147000213");

  QCOMPARE(2096.43f, h->trainPoints().at(0).x);
  QCOMPARE(5294.68f, h->trainPoints().at(0).y);
  QCOMPARE(1210.06f, h->trainPoints().at(1).x);
  QCOMPARE(5884.34f, h->trainPoints().at(1).y);
  QCOMPARE(4767.65f, h->trainPoints().at(2).x);
  QCOMPARE(5489.22f, h->trainPoints().at(2).y);
}


QTEST_APPLESS_MAIN(TestGroundTruth)

#include "tst_groundtruth.moc"
