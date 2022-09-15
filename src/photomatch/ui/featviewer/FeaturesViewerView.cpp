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


#include "FeaturesViewerView.h"

#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/GraphicItem.h"

#include <QGraphicsItem>
#include <QComboBox>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QApplication>

namespace photomatch
{

FeaturesViewerViewImp::FeaturesViewerViewImp(QWidget *parent, Qt::WindowFlags f)
  : FeaturesViewerView(parent, f),
    mMarkerColor("#e5097e"),
    mSelectedMarkerColor("#ff0000"),
    mMarkerType(0),
    mMarkerSize(20),
    mMarkerWidth(1),
    mSelectedMarkerWidth(2)
{
  this->initUI();
  this->initSignalAndSlots();
}

FeaturesViewerViewImp::~FeaturesViewerViewImp()
{
}

void FeaturesViewerViewImp::initUI()
{
  this->setObjectName(QString("FeaturesViewerView"));

  this->setWindowTitle(tr("Keypoints Viewer"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mLabelImages = new QLabel(this);
  gridLayout->addWidget(mLabelImages, 0, 0, 1, 1);

  mComboBoxImages = new QComboBox(this);
  gridLayout->addWidget(mComboBoxImages, 0, 1, 1, 1);

  mGraphicView = new GraphicViewerImp(this);
  gridLayout->addWidget(mGraphicView, 1, 0, 1, 2);

  mTreeWidget = new QTreeWidget(this);
  mTreeWidget->setAlternatingRowColors(true);
  mTreeWidget->setMaximumSize(QSize(16777215, 192));

  gridLayout->addWidget(mTreeWidget, 2, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 3, 0, 1, 2);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  mContextMenuLeft = new QMenu(mGraphicView);

  mActionZoomIn = new QAction(this);
  QIcon iconZoomIn;
  iconZoomIn.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomIn->setIcon(iconZoomIn);
  mContextMenuLeft->addAction(mActionZoomIn);

  mActionZoomOut = new QAction(this);
  QIcon iconZoomOut;
  iconZoomOut.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomOut->setIcon(iconZoomOut);
  mContextMenuLeft->addAction(mActionZoomOut);

  mActionZoomExtend = new QAction(this);
  QIcon iconZoomExtend;
  iconZoomExtend.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomExtend->setIcon(iconZoomExtend);
  mContextMenuLeft->addAction(mActionZoomExtend);

  mActionZoom11 = new QAction(this);
  QIcon iconZoom11;
  iconZoom11.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoom11->setIcon(iconZoom11);
  mContextMenuLeft->addAction(mActionZoom11);

  mGraphicView->setContextMenu(mContextMenuLeft);

  this->retranslate();
  this->update();
}

void FeaturesViewerViewImp::initSignalAndSlots()
{
  connect(mComboBoxImages,   &QComboBox::currentTextChanged,      this,          &FeaturesViewerView::imageChange);
  connect(mTreeWidget,       &QTreeWidget::itemSelectionChanged,  this,          &FeaturesViewerViewImp::onTreeWidgetItemSelectionChanged);
  connect(mGraphicView,      &GraphicViewerImp::selectionChanged, this,          &FeaturesViewerViewImp::onGraphicsViewSelectionChanged);
  connect(mActionZoomIn,     &QAction::triggered,                 mGraphicView,  &GraphicViewerImp::zoomIn);
  connect(mActionZoomOut,    &QAction::triggered,                 mGraphicView,  &GraphicViewerImp::zoomOut);
  connect(mActionZoomExtend, &QAction::triggered,                 mGraphicView,  &GraphicViewerImp::zoomExtend);
  connect(mActionZoom11,     &QAction::triggered,                 mGraphicView,  &GraphicViewerImp::zoom11);

  connect(mButtonBox->button(QDialogButtonBox::Close),  &QAbstractButton::clicked, this, &QDialog::accept);
  connect(mButtonBox->button(QDialogButtonBox::Help),   &QAbstractButton::clicked, this, &PhotoMatchDialogView::help);
}

void FeaturesViewerViewImp::clear()
{
  this->setWindowTitle(tr("Keypoints Viewer"));
  const QSignalBlocker blockerTreeWidget(mTreeWidget);
  mTreeWidget->clear();

  const QSignalBlocker blockerComboBoxImages(mComboBoxImages);
  mComboBoxImages->clear();
}

void FeaturesViewerViewImp::update()
{

}

void FeaturesViewerViewImp::retranslate()
{
  mLabelImages->setText(QApplication::translate("FeaturesViewerView", "Images:"));
  QTreeWidgetItem *qTreeWidgetItem = mTreeWidget->headerItem();
  qTreeWidgetItem->setText(0, QApplication::translate("FeaturesViewerView", "ID"));
  qTreeWidgetItem->setText(1, QApplication::translate("FeaturesViewerView", "X"));
  qTreeWidgetItem->setText(2, QApplication::translate("FeaturesViewerView", "Y"));
  qTreeWidgetItem->setText(3, QApplication::translate("FeaturesViewerView", "Size"));
  qTreeWidgetItem->setText(4, QApplication::translate("FeaturesViewerView", "Angle"));
  mActionZoomIn->setText(QApplication::translate("FeaturesViewerView", "Zoom In"));
  mActionZoomOut->setText(QApplication::translate("FeaturesViewerView", "Zoom Out"));
  mActionZoomExtend->setText(QApplication::translate("FeaturesViewerView", "Zoom Extend"));
  mActionZoom11->setText(QApplication::translate("FeaturesViewerView", "Zoom 1:1"));
}

void FeaturesViewerViewImp::onGraphicsViewSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicView);
  const QSignalBlocker blocker2(mTreeWidget);

  QList<QGraphicsItem *> items = mGraphicView->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++) {
    if (items[i] && items[i]->isSelected() == true) {

      mTreeWidget->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
        if (item && item->text(0).compare(items[i]->toolTip()) == 0){
          item->setSelected(true);
          QModelIndex index = mTreeWidget->model()->index(j, 0);
          mTreeWidget->scrollTo(index);
          break;
        }
      }

      bSelectedItem = true;
      break;
    }
  }

  if (bSelectedItem == false){
    mTreeWidget->selectionModel()->clearSelection();
  }

  update();
}

void FeaturesViewerViewImp::onTreeWidgetItemSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicView);

  if (QTreeWidgetItem *item = mTreeWidget->currentItem()){

    QPointF point(item->text(1).toDouble(), item->text(2).toDouble());
    mGraphicView->scene()->clearSelection();

    mGraphicView->zoom11();
    mGraphicView->centerOn(point);
    QPoint pt_scene = mGraphicView->mapFromScene(point);
    QGraphicsItem *select_item_left = mGraphicView->itemAt(pt_scene);
    if (select_item_left) {
      select_item_left->setSelected(true);
    }

  } else {
    mGraphicView->scene()->clearSelection();
  }
  update();
}

void photomatch::FeaturesViewerViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Keypoints Viewer ").append(name));
}

void FeaturesViewerViewImp::setImageList(const std::vector<QString> &imageList)
{
  QSignalBlocker blocker(mComboBoxImages);
  mComboBoxImages->clear();
  for (auto &image : imageList){
    QFileInfo file_info(image);
    mComboBoxImages->addItem(file_info.baseName(), image);
  }
}

void FeaturesViewerViewImp::setCurrentImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxImages);
  mComboBoxImages->setCurrentText(leftImage);
  mGraphicView->scene()->clearSelection();
  mGraphicView->setImage(QImage(mComboBoxImages->currentData().toString()));
  mGraphicView->zoomExtend();
}

void FeaturesViewerViewImp::setKeyPoints(const std::vector<std::tuple<QPointF, double, double> > &keyPoints)
{
  const QSignalBlocker blocker2(mTreeWidget);
  mTreeWidget->clear();

  for (auto &item : mGraphicView->scene()->items()) {
    if (mMarkerType == 0){
      if (KeyPointGraphicsItem *keyPoint = dynamic_cast<KeyPointGraphicsItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 3){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }


  QBrush brush;
  brush = QBrush(Qt::NoBrush);

  //
  //mMarkerSize;
  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

  for (size_t i = 0; i < keyPoints.size(); i++){
    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i + 1));
    QPointF point;
    double size;
    double angle;
    std::tie(point, size, angle) = keyPoints[i];

    treeWidgetItem->setText(1, QString::number(point.x()));
    treeWidgetItem->setText(2, QString::number(point.y()));
    treeWidgetItem->setText(3, QString::number(size));
    treeWidgetItem->setText(4, QString::number(angle));
    mTreeWidget->addTopLevelItem(treeWidgetItem);

    if (mMarkerType == 0){
      KeyPointGraphicsItem *item = new KeyPointGraphicsItem(point, size, angle);
      item->setPen(pen);
      item->setSelectedPen(select_pen);
      item->setFlag(QGraphicsItem::ItemIsSelectable, true);
      item->setToolTip(QString::number(static_cast<int>(i+1)));
      mGraphicView->scene()->addItem(item);
    } else if (mMarkerType == 1){
      // Circle
      CircleGraphicItem *item = new CircleGraphicItem(point, mMarkerSize);
      item->setPen(pen);
      item->setSelectedPen(select_pen);
      item->setFlag(QGraphicsItem::ItemIsSelectable, true);
      item->setToolTip(QString::number(static_cast<int>(i+1)));
      mGraphicView->scene()->addItem(item);
    } else if (mMarkerType == 2){
      // Cross
      CrossGraphicItem *item = new CrossGraphicItem(point, mMarkerSize);
      item->setPen(pen);
      item->setSelectedPen(select_pen);
      item->setFlag(QGraphicsItem::ItemIsSelectable, true);
      item->setToolTip(QString::number(static_cast<int>(i+1)));
      mGraphicView->scene()->addItem(item);
    } else if (mMarkerType == 3){
      // Diagonal cross
      DiagonalCrossGraphicItem *item = new DiagonalCrossGraphicItem(point, mMarkerSize);
      item->setPen(pen);
      item->setSelectedPen(select_pen);
      item->setFlag(QGraphicsItem::ItemIsSelectable, true);
      item->setToolTip(QString::number(static_cast<int>(i+1)));
      mGraphicView->scene()->addItem(item);
    }

  }

}

void FeaturesViewerViewImp::setBGColor(const QString &bgColor)
{
  mGraphicView->setBackgroundBrush(QBrush(QColor(bgColor)));
}

void FeaturesViewerViewImp::setSelectedMarkerStyle(const QString &color, int width)
{
  mSelectedMarkerColor = color;
  mSelectedMarkerWidth = width;
}

void FeaturesViewerViewImp::setMarkerStyle(const QString &color, int width, int type, int size)
{
  if (mMarkerType != type){  /// TODO: ¿Es necesario?
    for (auto &item : mGraphicView->scene()->items()) {
      if (mMarkerType == 0){
        if (KeyPointGraphicsItem *keyPoint = dynamic_cast<KeyPointGraphicsItem *>(item)){
          mGraphicView->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (mMarkerType == 1){
        // Circle
        if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
          mGraphicView->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (mMarkerType == 2){
        // Cross
        if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
          mGraphicView->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (mMarkerType == 3){
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          mGraphicView->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      }
    }
  }

  mMarkerColor = color;
  mMarkerSize = size;
  mMarkerWidth = width;
  mMarkerType = type;

  QPen pen(QColor(mMarkerColor), mMarkerWidth);

  /// Para volver a cargar los puntos
  if (mComboBoxImages->currentText().isEmpty() == false)
    emit imageChange(mComboBoxImages->currentText());

}

void FeaturesViewerViewImp::closeEvent(QCloseEvent *event)
{
  for (auto &item : mGraphicView->scene()->items()) {
    if (mMarkerType == 0){
      if (KeyPointGraphicsItem *keyPoint = dynamic_cast<KeyPointGraphicsItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 3){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicView->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }

  QDialog::closeEvent(event);
}

} // namespace photomatch
