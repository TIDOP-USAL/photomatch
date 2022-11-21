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


#include "EvaluationView.h"

#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/GraphicItem.h"

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
#include <QTabWidget>
#include <QDoubleSpinBox>

namespace photomatch
{


EvaluationViewImp::EvaluationViewImp(QWidget *parent,
                                     Qt::WindowFlags f)
  : EvaluationView(parent, f)
{
  this->initUI();
  this->initSignalAndSlots();
}

EvaluationViewImp::~EvaluationViewImp()
{

}

void EvaluationViewImp::initUI()
{
  this->setObjectName(QString("EvaluationView"));
  //this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
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
  gridLayout->addWidget(mTreeWidgetSessions, 0, 0, 5, 1);

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

  mTabWidget = new QTabWidget(this);
  gridLayout->addWidget(mTabWidget, 3, 1, 1, 2);
  //vBoxLayout->addWidget(mTabWidget);
  //mGraphicView = new GraphicViewerImp(this);
  //vBoxLayout->addWidget(mGraphicView);

  mTreeWidgetErrors = new QTreeWidget(this);
  mTreeWidgetErrors->setMaximumSize(QSize(16777215, 285));

  QTreeWidgetItem *qTreeWidgetItem = mTreeWidgetErrors->headerItem();
  qTreeWidgetItem->setText(0, tr(""));
  qTreeWidgetItem->setText(1, tr(""));
  qTreeWidgetItem->setText(2, tr(""));
  qTreeWidgetItem->setText(3, tr(""));
  qTreeWidgetItem->setText(4, tr(""));
  qTreeWidgetItem->setText(5, tr(""));
  qTreeWidgetItem->setText(6, tr(""));
  qTreeWidgetItem->setText(7, tr(""));

  mTreeWidgetErrors->setAlternatingRowColors(true);

  //vBoxLayout->addWidget(mTreeWidgetErrors);
  //hBoxLayout->addLayout(vBoxLayout);
  //gridLayout->addLayout(hBoxLayout, 1, 0, 1, 4);
  gridLayout->addWidget(mTreeWidgetErrors, 4, 1, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 5, 0, 1, 3);

  this->update();
  this->retranslate();
}

void EvaluationViewImp::initSignalAndSlots()
{
  connect(mComboBoxLeftImage, QOverload<int>::of(&QComboBox::currentIndexChanged), 
          [&](int idx) {
            emit leftImageChange(mComboBoxLeftImage->itemText(idx)); 
          });

  connect(mComboBoxRightImage, QOverload<int>::of(&QComboBox::currentIndexChanged),
          [&](int idx) {
            emit rightImageChange(mComboBoxRightImage->itemText(idx));
          });

  connect(mTreeWidgetSessions, &QTreeWidget::itemChanged, 
          [&](QTreeWidgetItem *item, int column) {
            if (item == nullptr) return;

            if (item->checkState(column)) {
              emit activeSession(item->text(0));
            } else {
              emit disableSession(item->text(0));
            }
          });

  connect(mDoubleSpinBoxErrorThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          [&](double value) {
            emit error_threshold_changed(value);
          });

  connect(mButtonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help), SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

void EvaluationViewImp::clear()
{
  QSignalBlocker blocker1(mComboBoxLeftImage);
  QSignalBlocker blocker2(mComboBoxRightImage);
  QSignalBlocker blocker3(mTreeWidgetSessions);
  QSignalBlocker blocker4(mDoubleSpinBoxErrorThreshold);

  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
  mTreeWidgetSessions->clear();
  mTabWidget->clear();
  mDoubleSpinBoxErrorThreshold->setValue(2.);
}

void EvaluationViewImp::update()
{
}

void EvaluationViewImp::retranslate()
{
  mLabelLeftImage->setText(QApplication::translate("EvaluationView", "Left Image:", nullptr));
  mLabelRightImage->setText(QApplication::translate("EvaluationView", "Right Image:", nullptr));
  mLabelErrorThreshold->setText(QApplication::translate("EvaluationView", "Error threshold:", nullptr));
  QTreeWidgetItem *qtreewidgetitem = mTreeWidgetSessions->headerItem();
  qtreewidgetitem->setText(0, QApplication::translate("EvaluationView", "Session"));
  qtreewidgetitem->setText(1, QApplication::translate("EvaluationView", "Detector"));
  qtreewidgetitem->setText(2, QApplication::translate("EvaluationView", "Descriptor"));
  QTreeWidgetItem *qtreewidgetitemError = mTreeWidgetErrors->headerItem();
  qtreewidgetitemError->setText(0, QApplication::translate("EvaluationView", "Session"));
  qtreewidgetitemError->setText(1, QApplication::translate("EvaluationView", "Total matches"));
  qtreewidgetitemError->setText(2, QApplication::translate("EvaluationView", "Average_error"));
  qtreewidgetitemError->setText(3, QApplication::translate("EvaluationView", "Max_error"));
  qtreewidgetitemError->setText(4, QApplication::translate("EvaluationView", "Pts below 5 px"));
  qtreewidgetitemError->setText(5, QApplication::translate("EvaluationView", "Pts below 10 px"));
  qtreewidgetitemError->setText(6, QApplication::translate("EvaluationView", "Pts below 20 px"));
  qtreewidgetitemError->setText(7, QApplication::translate("EvaluationView", "Pts below 30 px"));
  mButtonBox->button(QDialogButtonBox::Close)->setText(QApplication::translate("EvaluationView", "Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("EvaluationView", "Help"));
}

void EvaluationViewImp::addSession(const QString &session,
                                     const QString &detector,
                                     const QString &descriptor)
{
  QSignalBlocker blocker3(mTreeWidgetSessions);

  if (QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions)){
    item->setText(0, session);
    item->setText(1, detector);
    item->setText(2, descriptor);
    item->setCheckState(0, Qt::Unchecked);
    mTreeWidgetSessions->addTopLevelItem(item);
  }
}

bool EvaluationViewImp::isSessionActive(const QString &session) const
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

QString EvaluationViewImp::leftImage() const
{
  return mComboBoxLeftImage->currentText();
}

void EvaluationViewImp::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
}

QString EvaluationViewImp::rightImage() const
{
  return mComboBoxRightImage->currentText();
}

void EvaluationViewImp::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
}

void EvaluationViewImp::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList) {
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void EvaluationViewImp::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList) {
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void EvaluationViewImp::setErrors(const QString &session, const Report &report)
{
  QSignalBlocker blocker(mTreeWidgetErrors);

  QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
  treeWidgetItem->setText(0, session);
  treeWidgetItem->setText(1, QString::number(report.total_matches));
  treeWidgetItem->setText(2, QString::number(report.average_error));
  treeWidgetItem->setText(3, QString::number(report.max_error));
  treeWidgetItem->setText(4, QString::number(report.pts_below_5_px));
  treeWidgetItem->setText(5, QString::number(report.pts_below_10_px));
  treeWidgetItem->setText(6, QString::number(report.pts_below_20_px));
  treeWidgetItem->setText(7, QString::number(report.pts_below_30_px));
  mTreeWidgetErrors->addTopLevelItem(treeWidgetItem);

  GraphicViewerImp *graphicViewer = new GraphicViewerImp(this);
  graphicViewer->setImage(report.image);
  mTabWidget->addTab(graphicViewer, session);
  graphicViewer->zoomExtend();
}

void EvaluationViewImp::removeErrors(const QString &session)
{
  QSignalBlocker blocker(mTreeWidgetErrors);

  for (int i = 0; i < mTreeWidgetErrors->topLevelItemCount(); i++) {
    QTreeWidgetItem *item = mTreeWidgetErrors->topLevelItem(i);
    if (item->text(0).compare(session) == 0) {
      delete item;
      item = nullptr;
      break;
    }
  }

  // Borrar GraphicView
  for (int i = 0; i < mTabWidget->count(); i++) {
    if (mTabWidget->tabText(i) == session) {
      GraphicViewerImp *graphicViewer = dynamic_cast<GraphicViewerImp *>(mTabWidget->widget(i));
      mTabWidget->removeTab(i);
      if (graphicViewer) {
        delete graphicViewer;
        graphicViewer = nullptr;
      }
    }
  }
}

void EvaluationViewImp::removeErrors()
{
  QSignalBlocker blocker(mTreeWidgetErrors);

  mTreeWidgetErrors->clear();

  for (int i = 0; i < mTabWidget->count(); i++) {
    GraphicViewerImp *graphicViewer = dynamic_cast<GraphicViewerImp *>(mTabWidget->widget(0));
    mTabWidget->removeTab(0);
    if (graphicViewer) {
      delete graphicViewer;
      graphicViewer = nullptr;
    }
  }
}

double EvaluationViewImp::errorThreshold() const
{
  return mDoubleSpinBoxErrorThreshold->value();
}

} // namespace photomatch
