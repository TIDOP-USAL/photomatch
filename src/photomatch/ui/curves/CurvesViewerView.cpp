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
#include <QApplication>
#include <QDoubleSpinBox>

namespace photomatch
{


CurvesViewerViewImp::CurvesViewerViewImp(QWidget *parent,
                                         Qt::WindowFlags f)
  : CurvesViewerView(parent, f)
{
  this->initUI();
  this->initSignalAndSlots();
}

CurvesViewerViewImp::~CurvesViewerViewImp()
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
}

void CurvesViewerViewImp::initUI()
{
  this->setObjectName(QString("CurvesViewerView"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mTreeWidgetSessions = new QTreeWidget(this);
  QTreeWidgetItem *qtreewidgetitem = new QTreeWidgetItem();
  qtreewidgetitem->setText(0, "");
  qtreewidgetitem->setText(1, "");
  qtreewidgetitem->setText(2, "");
  mTreeWidgetSessions->setHeaderItem(qtreewidgetitem);
  mTreeWidgetSessions->setMaximumWidth(250);
  gridLayout->addWidget(mTreeWidgetSessions, 0, 0, 4, 1);

  mLabelLeftImage = new QLabel(this);
  gridLayout->addWidget(mLabelLeftImage, 0, 1, 1, 1);

  mComboBoxLeftImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxLeftImage, 0, 2, 1, 1);

  mLabelRightImage = new QLabel(this);
  gridLayout->addWidget(mLabelRightImage, 1, 1, 1, 1);

  mComboBoxRightImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxRightImage, 1, 2, 1, 1);

  mLabelErrorThreshold = new QLabel(this);
  gridLayout->addWidget(mLabelErrorThreshold, 2, 1, 1, 1);

  mDoubleSpinBoxErrorThreshold = new QDoubleSpinBox(this);
  gridLayout->addWidget(mDoubleSpinBoxErrorThreshold, 2, 2, 1, 1);


  mChart = new QtCharts::QChart();
  mAxisX = new QValueAxis(mChart);
  mAxisX->setRange(0,1);
  mChart->addAxis(mAxisX, Qt::AlignBottom);
  mAxisY = new QValueAxis(mChart);
  mAxisY->setRange(0,1);
  mChart->addAxis(mAxisY, Qt::AlignLeft);
  mChart->legend()->setAlignment(Qt::AlignRight);

  QChartView *chartView = new QChartView(mChart);
  chartView->setRenderHint(QPainter::Antialiasing);
  gridLayout->addWidget(chartView, 3, 1, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 4, 0, 1, 3);

  this->update();
  this->retranslate();
}

void CurvesViewerViewImp::initSignalAndSlots()
{
  connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetSessions, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(onTreeWidgetSessionsItemChanged(QTreeWidgetItem *, int)));

  connect(mButtonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help), SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

void CurvesViewerViewImp::clear()
{
  QSignalBlocker blocker1(mComboBoxLeftImage);
  QSignalBlocker blocker2(mComboBoxRightImage);
  QSignalBlocker blocker3(mTreeWidgetSessions);
  QSignalBlocker blocker4(mDoubleSpinBoxErrorThreshold);

  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
  mTreeWidgetSessions->clear();
  mDoubleSpinBoxErrorThreshold->setValue(2.);
}

void CurvesViewerViewImp::update()
{
}

void CurvesViewerViewImp::retranslate()
{
  mLabelLeftImage->setText(QApplication::translate("CurvesViewerView", "Left Image:", nullptr));
  mLabelRightImage->setText(QApplication::translate("CurvesViewerView", "Right Image:", nullptr));
  QTreeWidgetItem *qtreewidgetitem = mTreeWidgetSessions->headerItem();
  qtreewidgetitem->setText(0, QApplication::translate("CurvesViewerView", "Session"));
  qtreewidgetitem->setText(1, QApplication::translate("CurvesViewerView", "Detector"));
  qtreewidgetitem->setText(2, QApplication::translate("CurvesViewerView", "Descriptor"));
  mLabelErrorThreshold->setText(QApplication::translate("CurvesViewerView", "Error threshold:", nullptr));
  mButtonBox->button(QDialogButtonBox::Close)->setText(QApplication::translate("CurvesViewerView", "Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("CurvesViewerView", "Help"));
}

void CurvesViewerViewImp::addSession(const QString &session,
                                     const QString &detector,
                                     const QString &descriptor)
{
  if (QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions)){
    item->setText(0, session);
    item->setText(1, detector);
    item->setText(2, descriptor);
    item->setCheckState(0, Qt::Unchecked);
    mTreeWidgetSessions->addTopLevelItem(item);
  }
}

bool CurvesViewerViewImp::isSessionActive(const QString &session) const
{
  for (int i = 0; i < mTreeWidgetSessions->topLevelItemCount(); i++){
    if (QTreeWidgetItem *item = mTreeWidgetSessions->topLevelItem(i)){
      if (item->text(0).compare(session) == 0){
        return item->checkState(0);
      }
    }
  }
  return false;
}

QString CurvesViewerViewImp::leftImage() const
{
  return mComboBoxLeftImage->currentText();
}

void CurvesViewerViewImp::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
}

QString CurvesViewerViewImp::rightImage() const
{
  return mComboBoxRightImage->currentText();
}

void CurvesViewerViewImp::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
}

void CurvesViewerViewImp::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList) {
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerViewImp::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList) {
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void CurvesViewerViewImp::setCurve(const QString &title, const std::vector<QPointF> &curve)
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

void CurvesViewerViewImp::eraseCurve(const QString &session)
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

void CurvesViewerViewImp::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemText(idx));
}

void CurvesViewerViewImp::onComboBoxRightImageIndexChanged(int idx)
{
  emit rightImageChange(mComboBoxRightImage->itemText(idx));
}

void CurvesViewerViewImp::onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item, int column)
{
  if (item == nullptr) return;

  if (item->checkState(column)) {
    emit activeSession(item->text(0));
  } else {
    emit disableSession(item->text(0));
  }
}

double CurvesViewerViewImp::errorThreshold() const
{
  return mDoubleSpinBoxErrorThreshold->value();
}

/*----------------------------------------------------------------*/


ROCCurvesViewer::ROCCurvesViewer(QWidget *parent,
                                 Qt::WindowFlags f)
  : CurvesViewerViewImp(parent, f)
{
  this->initUI();
}

ROCCurvesViewer::~ROCCurvesViewer()
{}

void ROCCurvesViewer::initUI()
{
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

  this->retranslate();
}


void ROCCurvesViewer::retranslate()
{
  this->setWindowTitle(QApplication::translate("CurvesViewerView", "ROC Curves Viewer"));
  mChart->setTitle(QApplication::translate("CurvesViewerView", "ROC Curves"));
  mAxisX->setTitleText(QApplication::translate("CurvesViewerView", "False Positive Rate"));
  mAxisY->setTitleText(QApplication::translate("CurvesViewerView", "True Positive Rate or Recall"));
}


/*----------------------------------------------------------------*/


PRCurvesViewer::PRCurvesViewer(QWidget *parent,
                               Qt::WindowFlags f)
  : CurvesViewerViewImp(parent, f)
{
  this->initUI();
}

PRCurvesViewer::~PRCurvesViewer()
{}

void PRCurvesViewer::initUI()
{
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

  this->retranslate();
}

void PRCurvesViewer::retranslate()
{
  this->setWindowTitle(QApplication::translate("CurvesViewerView", "PR Curves Viewer"));
  mChart->setTitle(QApplication::translate("CurvesViewerView", "PR Curves"));
  mAxisX->setTitleText(QApplication::translate("CurvesViewerView", "Recall"));
  mAxisY->setTitleText(QApplication::translate("CurvesViewerView", "Precision"));
}


/*----------------------------------------------------------------*/


DETCurvesViewer::DETCurvesViewer(QWidget *parent,
                                 Qt::WindowFlags f)
  : CurvesViewerViewImp(parent, f)
{
  this->initUI();
}

DETCurvesViewer::~DETCurvesViewer()
{}

void DETCurvesViewer::initUI()
{
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

  this->retranslate();
}

void DETCurvesViewer::retranslate()
{
  this->setWindowTitle(QApplication::translate("CurvesViewerView", "DET Curves Viewer"));
  mChart->setTitle(QApplication::translate("CurvesViewerView", "DET Curves"));
  mAxisX->setTitleText(QApplication::translate("CurvesViewerView", "False Positive Rate"));
  mAxisY->setTitleText(QApplication::translate("CurvesViewerView", "False Negative Rate"));
}

} // namespace photomatch
