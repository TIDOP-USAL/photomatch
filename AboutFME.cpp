#include "AboutFME.h"
#include "ui_AboutFME.h"
#include <QVBoxLayout>
#include "DependencyInfoWidget.h"
#include "MainWindowFME.h"
AboutFME::AboutFME(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutFME)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("About FME"));
    setStyleSheet("background-color:white;");
    setMinimumSize(700,550);
    setMaximumSize(700,550);

    //About FME
    QVBoxLayout *mainFrameLayout = new QVBoxLayout();
    QFrame *logoFrame = new QFrame();
    QHBoxLayout *logoFrameLayout = new QHBoxLayout();

    QLabel *lbLogoFME = new QLabel();
    QPixmap pix(":/FMELogo.png");
    lbLogoFME->setPixmap(pix.scaledToHeight(150,Qt::SmoothTransformation));
    lbLogoFME->setStyleSheet("background:transparent;");
    logoFrameLayout->addStretch();
    logoFrameLayout->addWidget(lbLogoFME);
    logoFrameLayout->addStretch();

    logoFrame->setLayout(logoFrameLayout);
    mainFrameLayout->addWidget(logoFrame);

    QFrame *infoFMEFrame = new QFrame();
    QVBoxLayout *infoFMEFrameLayout = new QVBoxLayout();
    QTextEdit *textArea= new QTextEdit();
    textArea->setFrameStyle(QFrame::NoFrame);
    textArea->setReadOnly(true);
    textArea->setText("<h2>FME (Feature Matching Evaluation)v " + QString( MAINWINDOWFME_VERSION) +" build number "+
                                                                      QString(MAINWINDOWFME_BUILD_NUMBER)  +
                                                                      QString(MAINWINDOWFME_RELEASE_TYPE) + "</h2>"
                          "<font size=\"4\">An open source tool for the evaluation of differente feature detector,descriptor and matching algoritms.<br><strong>License:</strong> GPL v3</font>"
                          );

    infoFMEFrameLayout->addWidget(textArea);

    QFrame *authorsDependenciesFrame = new QFrame();
    QGridLayout *authorsDependenciesFrameLayout = new QGridLayout();
    authorsDependenciesFrameLayout->setContentsMargins(0,0,0,0);

    QLabel *authorsLabel= new QLabel("<h2>Authors</h2>");
    authorsDependenciesFrameLayout->addWidget(authorsLabel,0,0);

    QFrame *authorsFrame = new QFrame();
    QGridLayout *authorsFrameLayout = new QGridLayout();
    authorsFrameLayout->setContentsMargins(0,0,0,0);

    QLabel *lbLogoUSAL = new QLabel();
    QPixmap pixUsal(":/Tidop_en.png");
    lbLogoUSAL->setPixmap(pixUsal);
    lbLogoUSAL->setStyleSheet("background:transparent;");


    authorsFrameLayout->addWidget(lbLogoUSAL,0,1);

    QLabel *usalAuthors = new QLabel("<strong>  Luis L&#0243;pez Fern&#0225;ndez</strong><br/>luisloez89@usal.es<br/>"
                                     "<strong>  Manuel Gesto</strong><br/>mgesto@usal.es<br/>"
                            "<strong>  Diego Gonz&#0225;lez Aguilera</strong><br/>daguilera@usal.es<br/>"
                                     "<strong>  Pablo Rodr&#0237;guez Gonz&#0225;lvez</strong><br/>pablorgsf@usal.es");




    authorsFrameLayout->addWidget(usalAuthors,1,1, Qt::AlignTop);

    authorsFrame->setLayout(authorsFrameLayout);
    authorsDependenciesFrameLayout->addWidget(authorsFrame,1,0);

    authorsDependenciesFrame->setLayout(authorsDependenciesFrameLayout);
    infoFMEFrameLayout->addWidget(authorsDependenciesFrame);
    infoFMEFrame->setLayout(infoFMEFrameLayout);

    mainFrameLayout->addWidget(infoFMEFrame);

    //Dependencies

    QFrame *infoToolsFrame = new QFrame();
    QVBoxLayout *infoToolsFrameLayout = new QVBoxLayout();

    authorsDependenciesFrameLayout->addWidget(new QLabel("<h2>Dependencies</h2>"),0,1);

    QTabWidget *tabWidgetTools = new QTabWidget;
//    tabWidgetTools->setMaximumWidth(350);
//    tabWidgetTools->setTabPosition(QTabWidget::South);
    tabWidgetTools->addTab(new DependencyInfoWidget("BSD","OpenCV (Open Source Computer Vision) is a library of programming functions mainly aimed at real-time computer vision","http://opencv.org/"), "OpenCV");
//    tabWidgetTools->addTab(new DependencyInfoWidget("BSD","The Point Cloud Library (or PCL) is a large scale, open project for 2D/3D image and point cloud processing. The PCL framework contains numerous state-of-the art algorithms including filtering, feature estimation, surface reconstruction, registration, model fitting and segmentation. These algorithms can be used, for example, to filter outliers from noisy data, stitch 3D point clouds together, segment relevant parts of a scene, extract keypoints and compute descriptors to recognize objects in the world based on their geometric appearance, and create surfaces from point clouds and visualize them -- to name a few.","https://www.http://pointclouds.org/"), "PCL");



//    tabWidgetTools->addTab(new DependencyInfoWidget("GPL v3","CGAL is a software project that provides easy access to efficient and reliable geometric algorithms in the form of a C++ library. CGAL is used in various areas needing geometric computation, such as geographic information systems, computer aided design, molecular biology, medical imaging, computer graphics, and robotics.","http://www.cgal.org/index.html"), "CGAL");

//    tabWidgetTools->addTab(new DependencyInfoWidget("MIT","A simple experimental utility to estimate the solar potential of building roof surface(s) from a 3D city model stored in CityGML.","https://github.com/tudelft3d/Solar3Dcity"), "Solar3DCity");

//    tabWidgetTools->addTab(new DependencyInfoWidget("Free for research and non-commercial use","Photogrammetric Surface Reconstruction from Imagery. SURE is a software solution for multi-view stereo, which enables the derivation of dense point clouds from a given set of images and its orientations. Up to one 3D point per pixel is extracted, which enables a high resolution of details. It is based on libtsgm, which implements the core functionality for image rectification, dense matching and multi-view triangulation, and provides a C/C++ API.","http://www.ifp.uni-stuttgart.de/publications/software/sure/index.en.html"), "SURE");


    infoToolsFrame->setLayout(infoToolsFrameLayout);
    authorsDependenciesFrameLayout->addWidget(tabWidgetTools,1,1);


    setLayout(mainFrameLayout);
}

AboutFME::~AboutFME()
{
    delete ui;
}
