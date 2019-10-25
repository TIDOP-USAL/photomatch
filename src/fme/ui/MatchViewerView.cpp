#include "MatchViewerView.h"

#include "fme/ui/utils/GraphicViewer.h"
#include "fme/ui/utils/DiagonalCrossGraphicItem.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QGraphicsItem>
#include <QComboBox>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>

namespace fme
{

MatchViewerView::MatchViewerView(QWidget *parent, Qt::WindowFlags f)
  : IMatchViewerView(parent, f),
    bUnsavedChanges(false)
{
  init();

  connect(mComboBoxLeftImage,     SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage,    SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetMatches,     SIGNAL(itemSelectionChanged()),   this, SLOT(onTreeWidgetMatchesItemSelectionChanged()));
  connect(mPushButtonDeleteMatch, SIGNAL(clicked(bool)),            this, SLOT(onPushButtonDeleteMatchClicked()));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

MatchViewerView::~MatchViewerView()
{
}

void MatchViewerView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
  mGraphicsViewLeft->scene()->clearSelection();
  mGraphicsViewLeft->setImage(QImage(leftImage));
}

void MatchViewerView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(rightImage));
}

void MatchViewerView::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList){
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void MatchViewerView::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList){
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void MatchViewerView::setMatches(const std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float> > &matches)
{
  QSignalBlocker blocker(mTreeWidgetMatches);
  mTreeWidgetMatches->clear();
  for (auto &item : mGraphicsViewLeft->scene()->items()) {
    DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item);
    if (keyPoints){
      mGraphicsViewLeft->scene()->removeItem(item);
    }
  }
  for (auto &item : mGraphicsViewRight->scene()->items()) {
    DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item);
    if (keyPoints){
      mGraphicsViewRight->scene()->removeItem(item);
    }
  }

  mGraphicsViewLeft->zoomExtend();
  mGraphicsViewRight->zoomExtend();

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  double symbol_size = 20.;

  for (size_t i = 0; i < matches.size(); i++){
    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i + 1));
    size_t query_id, train_id;
    QPointF query_point, train_point;
    double distance;
    std::tie(query_id, query_point, train_id, train_point, distance) = matches[i];
    treeWidgetItem->setText(1, QString::number(query_id));
    treeWidgetItem->setText(2, QString::number(query_point.x()));
    treeWidgetItem->setText(3, QString::number(query_point.y()));
    treeWidgetItem->setText(4, QString::number(train_id));
    treeWidgetItem->setText(5, QString::number(train_point.x()));
    treeWidgetItem->setText(6, QString::number(train_point.y()));
    treeWidgetItem->setText(7, QString::number(distance));
    mTreeWidgetMatches->addTopLevelItem(treeWidgetItem);

    /// Dibujado de puntos
    DiagonalCrossGraphicItem *crossGraphicItemLeft = new DiagonalCrossGraphicItem(query_point);
    crossGraphicItemLeft->setPen(pen);
    crossGraphicItemLeft->setSize(symbol_size);
    crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemLeft->setToolTip(QString::number(static_cast<int>(i+1)));
    mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
    DiagonalCrossGraphicItem *crossGraphicItemRight = new DiagonalCrossGraphicItem(train_point);
    crossGraphicItemRight->setPen(pen);
    crossGraphicItemRight->setSize(symbol_size);
    crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemRight->setToolTip(QString::number(static_cast<int>(i+1)));
    mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
  }
}

//void MatchViewerView::deleteMatch(int id)
//{

//}

void MatchViewerView::init()
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

  mGraphicsViewLeft = new GraphicViewer(this);
  gridLayout->addWidget(mGraphicsViewLeft, 2, 0, 1, 1);

  mGraphicsViewRight = new GraphicViewer(this);
  gridLayout->addWidget(mGraphicsViewRight, 2, 1, 1, 1);

  QLabel *labelMatches = new QLabel(tr("Matches:"), this);
  gridLayout->addWidget(labelMatches, 3, 0, 1, 1);

  QGridLayout *gridLayout2 = new QGridLayout(this);

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

  //gridLayout->addWidget(mTreeWidgetMatches, 4, 0, 1, 1);
  gridLayout2->addWidget(mTreeWidgetMatches, 0, 0, 4, 1);

  mPushButtonDeleteMatch = new QPushButton(tr("Delete Match"), this);
  mPushButtonDeleteMatch->setMaximumSize(QSize(280, 16777215));
  gridLayout2->addWidget(mPushButtonDeleteMatch, 0, 1, 1, 1);

//  mPushButtonSaveMatches = new QPushButton(tr("Save"), this);
//  mPushButtonSaveMatches->setMaximumSize(QSize(280, 16777215));
//  gridLayout2->addWidget(mPushButtonSaveMatches, 1, 1, 1, 1);

//  QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
//  gridLayout2->addItem(verticalSpacer, 1, 0, 1, 1);

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
  connect(mGraphicsViewLeft, SIGNAL(selectionChanged()), this, SLOT(onGraphicsViewLeftSelectionChanged()));

  QMenu *contextMenuRight = new QMenu(mGraphicsViewRight);
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), tr("Zoom In"), mGraphicsViewRight, SLOT(zoomIn()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), tr("Zoom Out"), mGraphicsViewRight, SLOT(zoomOut()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), tr("Zoom Extend"), mGraphicsViewRight, SLOT(zoomExtend()));
  contextMenuRight->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), tr("Zoom 1:1"), mGraphicsViewRight, SLOT(zoom11()));
  mGraphicsViewRight->setContextMenu(contextMenuRight);
  connect(mGraphicsViewRight, SIGNAL(selectionChanged()), this, SLOT(onGraphicsViewRightSelectionChanged()));

  update();
}

void MatchViewerView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void MatchViewerView::update()
{
  mPushButtonDeleteMatch->setEnabled(mTreeWidgetMatches->selectedItems().size() > 0);
  //mPushButtonSaveMatches->setEnabled(bUnsavedChanges);
}

void MatchViewerView::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemData(idx).toString());
}

void MatchViewerView::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemData(idx).toString());
  QString image_left(mComboBoxLeftImage->currentData().toString());
  emit rightImageChange(image_right);
  emit loadMatches(image_left, image_right);
}

void MatchViewerView::onTreeWidgetMatchesItemClicked(QTreeWidgetItem *item, int col)
{
  QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
  QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());

  mGraphicsViewLeft->zoom11();
  mGraphicsViewLeft->centerOn(query_point);
  mGraphicsViewRight->zoom11();
  mGraphicsViewRight->centerOn(train_point);
}

void MatchViewerView::onTreeWidgetMatchesItemSelectionChanged()
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

void MatchViewerView::onGraphicsViewLeftSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewRight);
  const QSignalBlocker blocker2(mTreeWidgetMatches);

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      //int id = items[i]->toolTip().toInt() - 1;
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

void MatchViewerView::onGraphicsViewRightSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mTreeWidgetMatches);

  QList<QGraphicsItem *> items = mGraphicsViewRight->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      //int id = items[i]->toolTip().toInt() - 1;
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

void MatchViewerView::onPushButtonDeleteMatchClicked()
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
    }
  }

  items = mGraphicsViewRight->items();
  for (int i = 0; i < items.size(); i++){
    QGraphicsItem *item = items[i];
    if (items[i]->toolTip().compare(id) == 0) {
      mGraphicsViewRight->scene()->removeItem(item);
    }
  }

  if (query_id != -1 && train_id != -1) {
    QString image_right(mComboBoxRightImage->currentText());
    QString image_left(mComboBoxLeftImage->currentText());
    emit deleteMatch(image_right, image_left, query_id, train_id);
  }

  update();
}

} // namespace fme
