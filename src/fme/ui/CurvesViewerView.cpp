#include "CurvesViewerView.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QTreeWidget>
#include <QtCharts>
#include <QHBoxLayout>

namespace fme
{


CurvesViewerView::CurvesViewerView(QWidget *parent, Qt::WindowFlags f)
  : ICurvesViewerView(parent, f)
{
  init();

  //connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  //connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetSessions, SIGNAL(itemChanged(QTreeWidgetItem *,int)), this, SLOT(onTreeWidgetSessionsItemChanged(QTreeWidgetItem *,int)));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

CurvesViewerView::~CurvesViewerView()
{
  if (mChart){
    delete mChart;
    mChart = nullptr;
  }
}

void CurvesViewerView::onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item, int column)
{
  bool checked = item->checkState(column);
  if (checked) {
    QString session = item->text(0);
    QString detector = mComboBoxLeftImage->currentText();
    QString descriptor = mComboBoxRightImage->currentText();
    emit drawCurve(session, detector, descriptor);
  }
}

void CurvesViewerView::addSession(const QString &session, const QString &detector, const QString &descriptor)
{
  QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions);
  item->setText(0, session);
  item->setText(1, detector);
  item->setText(2, descriptor);
  item->setCheckState(0, Qt::Unchecked);
  mTreeWidgetSessions->addTopLevelItem(item);
}

QString CurvesViewerView::leftImage() const
{
  return mComboBoxLeftImage->currentText();
}

void CurvesViewerView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
}

QString CurvesViewerView::rightImage() const
{
  return mComboBoxRightImage->currentText();
}

void CurvesViewerView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
}

void CurvesViewerView::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList){
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerView::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList){
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerView::setCurve(const QString &session, const std::vector<QPointF> &curve)
{
  QLineSeries *series = new QLineSeries(this);

  for (size_t i = 0; i < curve.size(); i++){
    series->append(curve[i]);
  }

  series->setName(session);
  mChart->addSeries(series);
  series->attachAxis(mAxisX);
  series->attachAxis(mAxisY);
}

void CurvesViewerView::init()
{
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  QLabel *labelImage1 = new QLabel(tr("Left Image:"), this);
  gridLayout->addWidget(labelImage1, 0, 0, 1, 1);

  mComboBoxLeftImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxLeftImage, 0, 1, 1, 1);

  QLabel *labelImage2 = new QLabel(tr("Right Image:"), this);
  gridLayout->addWidget(labelImage2, 0, 2, 1, 1);

  mComboBoxRightImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxRightImage, 0, 3, 1, 1);

  QHBoxLayout *hBoxLayout = new QHBoxLayout();

  mTreeWidgetSessions = new QTreeWidget(this);
  QTreeWidgetItem *qtreewidgetitem = new QTreeWidgetItem();
  qtreewidgetitem->setText(0, tr("Session"));
  qtreewidgetitem->setText(1, tr("Detector"));
  qtreewidgetitem->setText(2, tr("Descriptor"));
  mTreeWidgetSessions->setHeaderItem(qtreewidgetitem);
  mTreeWidgetSessions->setMaximumWidth(250);
  //gridLayout->addWidget(mTreeWidgetSessions, 1, 0, 1, 1);
  hBoxLayout->addWidget(mTreeWidgetSessions);

  ///TODO: calcular la curva y cargar en mChart
//  QLineSeries *series = new QLineSeries(this);
//  series->append(0, 6);
//  series->append(2, 4);
//  series->append(3, 8);
//  series->append(7, 4);
//  series->append(10, 5);
//////      *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
//  series->setName("Session 1");

  mChart = new QtCharts::QChart();
  //mChart->legend()->hide();
  //mChart->addSeries(series);
  //mChart->createDefaultAxes();

  mAxisX = new QValueAxis(this);
  //axisX->setTickCount(10);
  mAxisX->setRange(0,1);
  mChart->addAxis(mAxisX, Qt::AlignBottom);
  mAxisY = new QValueAxis(this);
  mAxisY->setRange(0,1);
  mChart->addAxis(mAxisY, Qt::AlignLeft);

  QChartView *chartView = new QChartView(mChart);
  chartView->setRenderHint(QPainter::Antialiasing);
  hBoxLayout->addWidget(chartView);
  //gridLayout->addWidget(chartView, 1, 1, 1, 3);
  gridLayout->addLayout(hBoxLayout, 1, 0, 1, 4);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 2, 0, 1, 4);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  update();
}

void CurvesViewerView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void CurvesViewerView::update()
{
}

/*----------------------------------------------------------------*/


ROCCurvesViewer::ROCCurvesViewer(QWidget *parent, Qt::WindowFlags f)
  : CurvesViewerView(parent, f)
{
  init();
}

ROCCurvesViewer::~ROCCurvesViewer()
{}

void ROCCurvesViewer::init()
{
  this->setWindowTitle(tr("ROC Curves Viewer"));
  this->mChart->setTitle("ROC Curves");
  this->mAxisX->setTitleText(tr("Recall"));
  this->mAxisY->setTitleText(tr("False Positive Rate"));
}

//void ROCCurvesViewer::clear()
//{
//}

//void ROCCurvesViewer::update()
//{
//}


///*----------------------------------------------------------------*/


PRCurvesViewer::PRCurvesViewer(QWidget *parent, Qt::WindowFlags f)
  : CurvesViewerView(parent, f)
{
  init();
}

PRCurvesViewer::~PRCurvesViewer()
{}

void PRCurvesViewer::init()
{
  this->setWindowTitle(tr("PR Curves Viewer"));
  this->mChart->setTitle("PR Curves");
  this->mAxisX->setTitleText(tr("Precision"));
  this->mAxisY->setTitleText(tr("Recall"));
}


//void PRCurvesViewer::clear()
//{
//}

//void PRCurvesViewer::update()
//{
//}

} // namespace fme
