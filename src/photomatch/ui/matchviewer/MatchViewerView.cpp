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


#include "MatchViewerView.h"

#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/GraphicItem.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QGraphicsItem>
#include <QComboBox>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>

namespace photomatch
{

MatchViewerViewImp::MatchViewerViewImp(QWidget *parent,
                                       Qt::WindowFlags f)
  : MatchViewerView(parent, f),
    bUnsavedChanges(false),
    mMarkerColor("#e5097e"),
    mMarkerSize(20),
    mMarkerWidth(1),
    mMarkerType(2),
    mSelectedMarkerColor("#ff0000"),
    mSelectedMarkerWidth(2)
{
  this->initUI();
  this->initSignalAndSlots();
}

MatchViewerViewImp::~MatchViewerViewImp()
{
}

void MatchViewerViewImp::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->setCurrentText(leftImage);
  mGraphicsViewLeft->scene()->clearSelection();
  mGraphicsViewLeft->setImage(QImage(mComboBoxLeftImage->currentData().toString()));
}

void MatchViewerViewImp::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->setCurrentText(rightImage);
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(mComboBoxRightImage->currentData().toString()));
}

void MatchViewerViewImp::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList){
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void MatchViewerViewImp::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList){
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void MatchViewerViewImp::setMatches(const std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float> > &matches)
{
  QSignalBlocker blocker(mTreeWidgetMatches);
  mTreeWidgetMatches->clear();

  for (auto &item : mGraphicsViewLeft->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }

  for (auto &item : mGraphicsViewRight->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }


  mGraphicsViewLeft->zoomExtend();
  mGraphicsViewRight->zoomExtend();

  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

  for (size_t i = 0; i < matches.size(); i++){
    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    size_t pp_id, query_id, train_id;
    QPointF query_point, train_point;
    double distance;
    std::tie(pp_id, query_id, query_point, train_id, train_point, distance) = matches[i];
    treeWidgetItem->setText(0, QString::number(pp_id));
    treeWidgetItem->setText(1, QString::number(query_id));
    treeWidgetItem->setText(2, QString::number(query_point.x()));
    treeWidgetItem->setText(3, QString::number(query_point.y()));
    treeWidgetItem->setText(4, QString::number(train_id));
    treeWidgetItem->setText(5, QString::number(train_point.x()));
    treeWidgetItem->setText(6, QString::number(train_point.y()));
    treeWidgetItem->setText(7, QString::number(distance));
    mTreeWidgetMatches->addTopLevelItem(treeWidgetItem);

    if (mMarkerType == 0){
      // Circle
      CircleGraphicItem *itemLeft = new CircleGraphicItem(query_point, mMarkerSize);
      itemLeft->setPen(pen);
      itemLeft->setSelectedPen(select_pen);
      itemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      itemLeft->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewLeft->scene()->addItem(itemLeft);
      CircleGraphicItem *itemRight = new CircleGraphicItem(train_point, mMarkerSize);
      itemRight->setPen(pen);
      itemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      itemRight->setSelectedPen(select_pen);
      itemRight->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewRight->scene()->addItem(itemRight);
    } else if (mMarkerType == 1){
      // Cross
      CrossGraphicItem *crossGraphicItemLeft = new CrossGraphicItem(query_point, mMarkerSize);
      crossGraphicItemLeft->setPen(pen);
      crossGraphicItemLeft->setSelectedPen(select_pen);
      crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemLeft->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      CrossGraphicItem *crossGraphicItemRight = new CrossGraphicItem(train_point, mMarkerSize);
      crossGraphicItemRight->setPen(pen);
      crossGraphicItemRight->setSelectedPen(select_pen);
      crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemRight->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
    } else if (mMarkerType == 2){
      // Diagonal cross
      DiagonalCrossGraphicItem *crossGraphicItemLeft = new DiagonalCrossGraphicItem(query_point, mMarkerSize);
      crossGraphicItemLeft->setPen(pen);
      crossGraphicItemLeft->setSelectedPen(select_pen);
      crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemLeft->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      DiagonalCrossGraphicItem *crossGraphicItemRight = new DiagonalCrossGraphicItem(train_point, mMarkerSize);
      crossGraphicItemRight->setPen(pen);
      crossGraphicItemRight->setSelectedPen(select_pen);
      crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemRight->setToolTip(QString::number(static_cast<int>(pp_id)));
      mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
    }
  }
}

void MatchViewerViewImp::setBGColor(const QString &bgColor)
{
  mGraphicsViewLeft->setBackgroundBrush(QBrush(QColor(bgColor)));
  mGraphicsViewRight->setBackgroundBrush(QBrush(QColor(bgColor)));
}

void MatchViewerViewImp::setSelectedMarkerStyle(const QString &color, int width)
{
  mSelectedMarkerColor = color;
  mSelectedMarkerWidth = width;
}

void MatchViewerViewImp::setMarkerStyle(const QString &color, int width, int type, int size)
{
  int markerTypeOld = mMarkerType;
  mMarkerColor = color;
  mMarkerSize = size;
  mMarkerWidth = width;
  mMarkerType = type;

  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

  if (markerTypeOld != mMarkerType){

    for (auto &item : mGraphicsViewLeft->scene()->items()) {

      QPointF point;
      int id = 0;

      if (markerTypeOld == 0) {
        // Circle
        if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
          point = item->pos();
          id = item->toolTip().toInt();
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (markerTypeOld == 1) {
        // Cross
        if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (markerTypeOld == 2) {
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else {
        continue;
      }

      if (mMarkerType == 0){
        // Circle
        CircleGraphicItem *itemLeft = new CircleGraphicItem(point, mMarkerSize);
        itemLeft->setPen(pen);
        itemLeft->setSelectedPen(select_pen);
        itemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
        itemLeft->setToolTip(QString::number(id));
        mGraphicsViewLeft->scene()->addItem(itemLeft);
      } else if (mMarkerType == 1) {
        // Cross
        CrossGraphicItem *crossGraphicItemLeft = new CrossGraphicItem(point, mMarkerSize);
        crossGraphicItemLeft->setPen(pen);
        crossGraphicItemLeft->setSelectedPen(select_pen);
        crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
        crossGraphicItemLeft->setToolTip(QString::number(id));
        mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      } else if (mMarkerType == 2) {
        // Diagonal cross
        DiagonalCrossGraphicItem *crossGraphicItemLeft = new DiagonalCrossGraphicItem(point, mMarkerSize);
        crossGraphicItemLeft->setPen(pen);
        crossGraphicItemLeft->setSelectedPen(select_pen);
        crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
        crossGraphicItemLeft->setToolTip(QString::number(id));
        mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      }
    }

    for (auto &item : mGraphicsViewRight->scene()->items()) {

      QPointF point;
      int id = 0;

      if (markerTypeOld == 0){
        // Circle
        if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
          point = item->pos();
          id = item->toolTip().toInt();
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (markerTypeOld == 1){
        // Cross
        if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
          point = item->pos();
          id = item->toolTip().toInt();
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else if (markerTypeOld == 2){
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
          point = item->pos();
          id = item->toolTip().toInt();
          delete keyPoint;
          keyPoint = nullptr;
        }
      } else {
        continue;
      }

      if (mMarkerType == 0){
        // Circle
        CircleGraphicItem *itemRight = new CircleGraphicItem(point, mMarkerSize);
        itemRight->setPen(pen);
        itemRight->setSelectedPen(select_pen);
        itemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
        itemRight->setToolTip(QString::number(id));
        mGraphicsViewRight->scene()->addItem(itemRight);
      } else if (mMarkerType == 1){
        // Cross
        CrossGraphicItem *crossGraphicItemRight = new CrossGraphicItem(point, mMarkerSize);
        crossGraphicItemRight->setPen(pen);
        crossGraphicItemRight->setSelectedPen(select_pen);
        crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
        crossGraphicItemRight->setToolTip(QString::number(id));
        mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
      } else if (mMarkerType == 2){
        // Diagonal cross
        DiagonalCrossGraphicItem *crossGraphicItemRight = new DiagonalCrossGraphicItem(point, mMarkerSize);
        crossGraphicItemRight->setPen(pen);
        crossGraphicItemRight->setSelectedPen(select_pen);
        crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
        crossGraphicItemRight->setToolTip(QString::number(id));
        mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
      }
    }

  } else {

    for (auto &item : mGraphicsViewLeft->scene()->items()) {
      if (mMarkerType == 0){
        // Circle
        if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      } else if (mMarkerType == 1){
        // Cross
        if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      } else if (mMarkerType == 2){
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      }
    }

    for (auto &item : mGraphicsViewRight->scene()->items()) {
      if (mMarkerType == 0) {
        // Circle
        if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      } else if (mMarkerType == 1) {
        // Cross
        if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      } else if (mMarkerType == 2) {
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          keyPoints->setPen(pen);
          keyPoints->setSelectedPen(select_pen);
          keyPoints->setSize(mMarkerSize);
        }
      }
    }

  }

}

void MatchViewerViewImp::setLineStyle(const QString &color, int width)
{
  mLineColor = color;
  mLineWidth = width;
}

void MatchViewerViewImp::initUI()
{
  this->setWindowTitle(tr("Match Viewer"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  QLabel *labelImage1 = new QLabel(tr("Left Image:"), this);
  gridLayout->addWidget(labelImage1, 0, 0, 1, 1);

  QLabel *labelImage2 = new QLabel(tr("Right Image:"), this);
  gridLayout->addWidget(labelImage2, 0, 1, 1, 1);

  mComboBoxLeftImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxLeftImage, 1, 0, 1, 1);

  mComboBoxRightImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxRightImage, 1, 1, 1, 1);

  mGraphicsViewLeft = new GraphicViewerImp(this);
  gridLayout->addWidget(mGraphicsViewLeft, 2, 0, 1, 1);

  mGraphicsViewRight = new GraphicViewerImp(this);
  gridLayout->addWidget(mGraphicsViewRight, 2, 1, 1, 1);

  QLabel *labelMatches = new QLabel(tr("Matches:"), this);
  gridLayout->addWidget(labelMatches, 3, 0, 1, 1);

  QGridLayout *gridLayout2 = new QGridLayout();

  mTreeWidgetMatches = new QTreeWidget(this);
  mTreeWidgetMatches->setMaximumSize(QSize(16777215, 285));

  QTreeWidgetItem *qTreeWidgetItem = mTreeWidgetMatches->headerItem();
  qTreeWidgetItem->setText(0, "ID");
  qTreeWidgetItem->setText(1, tr("Keypoint Left"));
  qTreeWidgetItem->setText(2, tr("Left X"));
  qTreeWidgetItem->setText(3, tr("Left Y"));
  qTreeWidgetItem->setText(4, tr("Keypoint Right"));
  qTreeWidgetItem->setText(5, tr("Right X"));
  qTreeWidgetItem->setText(6, tr("Right Y"));
  qTreeWidgetItem->setText(7, tr("Distance"));

  mTreeWidgetMatches->setAlternatingRowColors(true);

  gridLayout2->addWidget(mTreeWidgetMatches, 0, 0, 4, 1);

  mPushButtonDeleteMatch = new QPushButton(tr("Delete Match"), this);
  mPushButtonDeleteMatch->setMaximumSize(QSize(280, 16777215));
  gridLayout2->addWidget(mPushButtonDeleteMatch, 0, 1, 1, 1);
  /// Desactivo el borrado de puntos por ahora
  mPushButtonDeleteMatch->setVisible(false);

  gridLayout->addLayout(gridLayout2, 4, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 5, 0, 1, 2);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  QMenu *contextMenuLeft = new QMenu(mGraphicsViewLeft);
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), tr("Zoom In"), mGraphicsViewLeft, SLOT(zoomIn()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), tr("Zoom Out"), mGraphicsViewLeft, SLOT(zoomOut()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), tr("Zoom Extend"), mGraphicsViewLeft, SLOT(zoomExtend()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), tr("Zoom 1:1"), mGraphicsViewLeft, SLOT(zoom11()));
  mGraphicsViewLeft->setContextMenu(contextMenuLeft);

  QMenu *contextMenuRight = new QMenu(mGraphicsViewRight);
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), tr("Zoom In"), mGraphicsViewRight, SLOT(zoomIn()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), tr("Zoom Out"), mGraphicsViewRight, SLOT(zoomOut()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), tr("Zoom Extend"), mGraphicsViewRight, SLOT(zoomExtend()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), tr("Zoom 1:1"), mGraphicsViewRight, SLOT(zoom11()));
  mGraphicsViewRight->setContextMenu(contextMenuRight);

  update();
}

void MatchViewerViewImp::initSignalAndSlots()
{
  connect(mComboBoxLeftImage,     SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage,    SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetMatches,     SIGNAL(itemSelectionChanged()),   this, SLOT(onTreeWidgetMatchesItemSelectionChanged()));
  connect(mPushButtonDeleteMatch, SIGNAL(clicked(bool)),            this, SLOT(onPushButtonDeleteMatchClicked()));
  connect(mGraphicsViewLeft,      SIGNAL(selectionChanged()),       this, SLOT(onGraphicsViewLeftSelectionChanged()));
  connect(mGraphicsViewRight,     SIGNAL(selectionChanged()),       this, SLOT(onGraphicsViewRightSelectionChanged()));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

void MatchViewerViewImp::clear()
{
  const QSignalBlocker blocker1(mComboBoxLeftImage);
  const QSignalBlocker blocker2(mComboBoxLeftImage);

  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void MatchViewerViewImp::update()
{
  mPushButtonDeleteMatch->setEnabled(mTreeWidgetMatches->selectedItems().size() > 0);
}

void MatchViewerViewImp::retranslate()
{

}

void MatchViewerViewImp::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemText(idx));
}

void MatchViewerViewImp::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemText(idx));
  QString image_left(mComboBoxLeftImage->currentText());
  emit rightImageChange(image_right);
  emit loadMatches(image_left, image_right);
}

void MatchViewerViewImp::onTreeWidgetMatchesItemClicked(QTreeWidgetItem *item, int col)
{
  QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
  QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());

  mGraphicsViewLeft->zoom11();
  mGraphicsViewLeft->centerOn(query_point);
  mGraphicsViewRight->zoom11();
  mGraphicsViewRight->centerOn(train_point);
}

void MatchViewerViewImp::onTreeWidgetMatchesItemSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mGraphicsViewRight);

  if (QTreeWidgetItem *item = mTreeWidgetMatches->currentItem()){

    QPointF query_point(item->text(2).toDouble(), item->text(3).toDouble());
    QPointF train_point(item->text(5).toDouble(), item->text(6).toDouble());

    mGraphicsViewLeft->scene()->clearSelection();
    mGraphicsViewRight->scene()->clearSelection();

    mGraphicsViewLeft->zoom11();
    mGraphicsViewLeft->centerOn(query_point);
    QPoint pt_left = mGraphicsViewLeft->mapFromScene(query_point);
    QGraphicsItem *select_item_left = mGraphicsViewLeft->itemAt(pt_left);
    if (select_item_left) {
      select_item_left->setSelected(true);
    }
    mGraphicsViewRight->zoom11();
    mGraphicsViewRight->centerOn(train_point);
    QPoint pt_right = mGraphicsViewRight->mapFromScene(train_point);
    QGraphicsItem *select_item_right = mGraphicsViewRight->itemAt(pt_right);
    if (select_item_right) {
      select_item_right->setSelected(true);
    }
  } else {
    mGraphicsViewLeft->scene()->clearSelection();
    mGraphicsViewRight->scene()->clearSelection();
  }
  update();
}

void MatchViewerViewImp::onGraphicsViewLeftSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewRight);
  const QSignalBlocker blocker2(mTreeWidgetMatches);

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      mGraphicsViewRight->scene()->clearSelection();
      QList<QGraphicsItem *> items_right = mGraphicsViewRight->items();
      items_right[i]->setSelected(true);
      mTreeWidgetMatches->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidgetMatches->topLevelItemCount(); j++){
        QTreeWidgetItem *item = mTreeWidgetMatches->topLevelItem(j);
        if (item && item->text(0).compare(items[i]->toolTip()) == 0){
          item->setSelected(true);
          QPointF train_point(item->text(5).toDouble(), item->text(6).toDouble());
          mGraphicsViewRight->centerOn(train_point);

          QModelIndex index = mTreeWidgetMatches->model()->index(j, 0);
          mTreeWidgetMatches->scrollTo(index);

          break;
        }
      }

      bSelectedItem = true;

      break;
    }
  }

  if (bSelectedItem == false){
    QList<QGraphicsItem *> items = mGraphicsViewRight->items();
    for (int i = 0; i < items.size(); i++){
      items[i]->setSelected(false);
    }
    mTreeWidgetMatches->selectionModel()->clearSelection();
  }

  update();
}

void MatchViewerViewImp::onGraphicsViewRightSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mTreeWidgetMatches);

  QList<QGraphicsItem *> items = mGraphicsViewRight->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      mGraphicsViewLeft->scene()->clearSelection();
      QList<QGraphicsItem *> items_left = mGraphicsViewLeft->items();
      items_left[i]->setSelected(true);
      mTreeWidgetMatches->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidgetMatches->topLevelItemCount(); j++){
        QTreeWidgetItem *itemProject = mTreeWidgetMatches->topLevelItem(j);
        if (itemProject && itemProject->text(0).compare(items[i]->toolTip()) == 0){
          itemProject->setSelected(true);
          QPointF query_point(itemProject->text(2).toDouble(), itemProject->text(3).toDouble());
          mGraphicsViewLeft->centerOn(query_point);

          QModelIndex index = mTreeWidgetMatches->model()->index(j, 0);
          mTreeWidgetMatches->scrollTo(index);

          break;
        }
      }

      bSelectedItem = true;

      break;
    }
  }

  if (bSelectedItem == false){
    QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
    for (int i = 0; i < items.size(); i++){
      items[i]->setSelected(false);
    }
    mTreeWidgetMatches->selectionModel()->clearSelection();
  }

  update();
}

void MatchViewerViewImp::onPushButtonDeleteMatchClicked()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mGraphicsViewRight);
  const QSignalBlocker blocker3(mTreeWidgetMatches);

  QString id;
  int query_id = -1;
  int train_id = -1;
  if (QTreeWidgetItem *item = mTreeWidgetMatches->currentItem()){
    id = item->text(0);
    query_id = item->text(1).toInt();
    train_id = item->text(4).toInt();
    delete item;
    item = nullptr;
  }

  mTreeWidgetMatches->selectionModel()->clearSelection();

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  for (int i = 0; i < items.size(); i++){
    QGraphicsItem *item = items[i];
    if (items[i]->toolTip().compare(id) == 0) {
      mGraphicsViewLeft->scene()->removeItem(item);
      delete item;
      item = nullptr;
    }
  }

  items = mGraphicsViewRight->items();
  for (int i = 0; i < items.size(); i++){
    QGraphicsItem *item = items[i];
    if (items[i]->toolTip().compare(id) == 0) {
      mGraphicsViewRight->scene()->removeItem(item);
      delete item;
      item = nullptr;
    }
  }

  if (query_id != -1 && train_id != -1) {
    QString image_right(mComboBoxRightImage->currentText());
    QString image_left(mComboBoxLeftImage->currentText());
    emit deleteMatch(image_right, image_left, query_id, train_id);
  }

  update();
}

void MatchViewerViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Match Viewer ").append(name));
}


void MatchViewerViewImp::closeEvent(QCloseEvent *event)
{
  for (auto &item : mGraphicsViewLeft->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }

  for (auto &item : mGraphicsViewRight->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoint = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoint = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoint = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
        delete keyPoint;
        keyPoint = nullptr;
      }
    }
  }
}

} // namespace photomatch
