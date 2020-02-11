/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


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

namespace photomatch
{


CurvesViewerView::CurvesViewerView(QWidget *parent, Qt::WindowFlags f)
  : ICurvesViewerView(parent, f)
{
  init();

  connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetSessions, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(onTreeWidgetSessionsItemChanged(QTreeWidgetItem *, int)));

  connect(mButtonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help), SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

CurvesViewerView::~CurvesViewerView()
{
  QList<QAbstractSeries *> series = mChart->series();
  for (int i = 0; i < series.size(); i++) {
    if (QAbstractSeries *serie = series[i]){
      mChart->removeSeries(serie);
      delete serie;
      serie = nullptr;
    }
  }
  if (mChart) {
    delete mChart;
    mChart = nullptr;
  }

  if (mAxisX){
    delete mAxisX;
    mAxisX = nullptr;
  }

  if (mAxisY){
    delete mAxisY;
    mAxisY = nullptr;
  }
}

void CurvesViewerView::onComboBoxLeftImageIndexChanged(int idx)
{
  QString image_left(mComboBoxLeftImage->itemText(idx));
  emit leftImageChange(image_left);
  QString image_right(mComboBoxRightImage->itemText(idx));
  for (int i = 0; i < mTreeWidgetSessions->topLevelItemCount(); i++){
    if (QTreeWidgetItem *item = mTreeWidgetSessions->topLevelItem(i)){
      if (item->checkState(0)){
        QString session = item->text(0);
        emit deleteCurve(item->text(0));
        emit drawCurve(session, image_left, image_right);
      }
    }
  }
}

void CurvesViewerView::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemText(idx));
  QString image_left(mComboBoxLeftImage->currentText());
  emit rightImageChange(image_right);
  for (int i = 0; i < mTreeWidgetSessions->topLevelItemCount(); i++){
    if (QTreeWidgetItem *item = mTreeWidgetSessions->topLevelItem(i)){
      if (item->checkState(0)){
        QString session = item->text(0);
        emit deleteCurve(item->text(0));
        emit drawCurve(session, image_left, image_right);
      }
    }
  }
}

void CurvesViewerView::onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item, int column)
{
  if (item && item->checkState(column)) {
    QString session = item->text(0);
    QString image_left = mComboBoxLeftImage->currentText();
    QString image_right = mComboBoxRightImage->currentText();
    emit drawCurve(session, image_left, image_right);
  } else {
    emit deleteCurve(item->text(0));
  }
}

void CurvesViewerView::addSession(const QString &session, const QString &detector, const QString &descriptor)
{
  if (QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions)){
    item->setText(0, session);
    item->setText(1, detector);
    item->setText(2, descriptor);
    item->setCheckState(0, Qt::Unchecked);
    mTreeWidgetSessions->addTopLevelItem(item);
  }
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
  for (auto &image : leftImageList) {
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerView::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList) {
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerView::setCurve(const QString &title, const std::vector<QPointF> &curve)
{
  QLineSeries *series = new QLineSeries(this);

  for (size_t i = 0; i < curve.size(); i++) {
    series->append(curve[i]);
  }

  series->setName(title);
  mChart->addSeries(series);
  series->attachAxis(mAxisX);
  series->attachAxis(mAxisY);
}

void CurvesViewerView::eraseCurve(const QString &session)
{
  QList<QAbstractSeries *> series = mChart->series();
  for (int i = 0; i < series.size(); i++) {
    if (QAbstractSeries *serie = series[i]){
      QStringList list = serie->name().split(" [");
      if (list[0].compare(session) == 0) {
        mChart->removeSeries(serie);
        delete serie;
        serie = nullptr;
        break;
      }
    }
  }
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
  hBoxLayout->addWidget(mTreeWidgetSessions);


  mChart = new QtCharts::QChart();
  mAxisX = new QValueAxis(this);
  mAxisX->setRange(0,1);
  mChart->addAxis(mAxisX, Qt::AlignBottom);
  mAxisY = new QValueAxis(this);
  mAxisY->setRange(0,1);
  mChart->addAxis(mAxisY, Qt::AlignLeft);
  mChart->legend()->setAlignment(Qt::AlignRight);

  QChartView *chartView = new QChartView(mChart);
  chartView->setRenderHint(QPainter::Antialiasing);
  hBoxLayout->addWidget(chartView);
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
  QSignalBlocker blocker1(mComboBoxLeftImage);
  QSignalBlocker blocker2(mComboBoxRightImage);
  QSignalBlocker blocker3(mTreeWidgetSessions);

  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
  mTreeWidgetSessions->clear();
}

void CurvesViewerView::update()
{
}

void CurvesViewerView::retranslate()
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
  this->mAxisX->setTitleText(tr("False Positive Rate"));
  this->mAxisY->setTitleText(tr("True Positive Rate or Recall"));

  QLineSeries *series = new QLineSeries(this);
  series->append(0, 0);
  series->append(1, 1);
  QPen pen(QColor(0, 0, 255));
  pen.setStyle(Qt::PenStyle::DashLine);
  series->setPen(pen);
  mChart->addSeries(series);
  QLegend *legend = mChart->legend();
  QList<QLegendMarker *> legendMarker = legend->markers(series);
  legendMarker.at(0)->setVisible(false);

}


/*----------------------------------------------------------------*/


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
  this->mAxisX->setTitleText(tr("Recall"));
  this->mAxisY->setTitleText(tr("Precision"));

  QLineSeries *series = new QLineSeries(this);
  series->append(0, 1);
  series->append(1, 0);
  QPen pen(QColor(0, 0, 255));
  pen.setStyle(Qt::PenStyle::DashLine);
  series->setPen(pen);
  mChart->addSeries(series);
  QLegend *legend = mChart->legend();
  QList<QLegendMarker *> legendMarker = legend->markers(series);
  legendMarker.at(0)->setVisible(false);
}


/*----------------------------------------------------------------*/


DETCurvesViewer::DETCurvesViewer(QWidget *parent, Qt::WindowFlags f)
  : CurvesViewerView(parent, f)
{
  init();
}

DETCurvesViewer::~DETCurvesViewer()
{}

void DETCurvesViewer::init()
{
  this->setWindowTitle(tr("DET Curves Viewer"));
  this->mChart->setTitle("DET Curves");
  this->mAxisX->setTitleText(tr("False Positive Rate"));
  this->mAxisY->setTitleText(tr("False Negative Rate"));

  QLineSeries *series = new QLineSeries(this);
  series->append(0, 1);
  series->append(1, 0);
  QPen pen(QColor(0, 0, 255));
  pen.setStyle(Qt::PenStyle::DashLine);
  series->setPen(pen);
  mChart->addSeries(series);
  QLegend *legend = mChart->legend();
  QList<QLegendMarker *> legendMarker = legend->markers(series);
  legendMarker.at(0)->setVisible(false);
}
} // namespace photomatch
