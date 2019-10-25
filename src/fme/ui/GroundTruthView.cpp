#include "GroundTruthView.h"

#include "fme/ui/utils/GraphicViewer.h"
#include "fme/ui/utils/CrossGraphicItem.h"
#include "fme/ui/utils/DiagonalCrossGraphicItem.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QGraphicsItem>
#include <QComboBox>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>
#include <QToolBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QImageReader>

namespace fme
{


GroundTruthView::GroundTruthView(QWidget *parent, Qt::WindowFlags f)
  : IGroundTruthView(parent, f),
    mCrossGraphicItem1(nullptr),
    mCrossGraphicItem2(nullptr),
    bLockViews(false)
{
  init();

  connect(mComboBoxLeftImage,   SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidget,          SIGNAL(itemSelectionChanged()),   this, SLOT(onTreeWidgetItemSelectionChanged()));
  connect(mPushButtonAddPoint,  SIGNAL(clicked(bool)),            this, SLOT(onPushButtonAddPointClicked()));
  connect(mPushButtonLockViews, SIGNAL(toggled(bool)),            this, SLOT(onPushButtonLockViewsToggled(bool)));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

GroundTruthView::~GroundTruthView()
{
  if (mCrossGraphicItem1){
    delete mCrossGraphicItem1;
    mCrossGraphicItem1 = nullptr;
  }

  if (mCrossGraphicItem2){
    delete mCrossGraphicItem2;
    mCrossGraphicItem2 = nullptr;
  }
}

void GroundTruthView::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemData(idx).toString());
}

void GroundTruthView::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemData(idx).toString());
  QString image_left(mComboBoxLeftImage->currentData().toString());
  emit rightImageChange(image_right);
  emit loadHomologousPoints(image_left, image_right);
}

void GroundTruthView::onTreeWidgetItemClicked(QTreeWidgetItem *item, int col)
{
  QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
  QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());

  mGraphicsViewLeft->zoom11();
  mGraphicsViewLeft->centerOn(query_point);
  mGraphicsViewRight->zoom11();
  mGraphicsViewRight->centerOn(train_point);
}

void GroundTruthView::onTreeWidgetItemSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mGraphicsViewRight);

  if (QTreeWidgetItem *item = mTreeWidget->currentItem()){

    QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
    QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());

    this->setPointLeft(query_point);
    this->setPointRight(train_point);

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

void GroundTruthView::onGraphicsViewLeftSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewRight);
  const QSignalBlocker blocker2(mTreeWidget);

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      mGraphicsViewRight->scene()->clearSelection();
      QList<QGraphicsItem *> items_right = mGraphicsViewRight->items();
      items_right[i]->setSelected(true);
      mTreeWidget->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
        if (item && item->text(0).compare(items[i]->toolTip()) == 0){
          item->setSelected(true);
          QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
          QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());
          this->setPointLeft(query_point);
          this->setPointRight(train_point);
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
    mTreeWidget->selectionModel()->clearSelection();
    this->setPointLeft(QPointF());
    this->setPointRight(QPointF());
  }

  update();
}

void GroundTruthView::onGraphicsViewRightSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mTreeWidget);

  QList<QGraphicsItem *> items = mGraphicsViewRight->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      mGraphicsViewLeft->scene()->clearSelection();
      QList<QGraphicsItem *> items_left = mGraphicsViewLeft->items();
      items_left[i]->setSelected(true);
      mTreeWidget->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
        if (item && item->text(0).compare(items[i]->toolTip()) == 0){
          item->setSelected(true);
          QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
          QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());
          this->setPointLeft(query_point);
          this->setPointRight(train_point);
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
    mTreeWidget->selectionModel()->clearSelection();
    this->setPointLeft(QPointF());
    this->setPointRight(QPointF());
  }

  update();
}

void GroundTruthView::onPushButtonAddPoints(bool active)
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mGraphicsViewRight);
  const QSignalBlocker blocker3(mTreeWidget);
  //const QSignalBlocker blocker4(mDeletePoints);

  if (active){
    connect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(setPointLeft(QPointF)));
    connect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(setPointRight(QPointF)));
    connect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointLeft(QPointF)));
    connect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointRight(QPointF)));
    //mDeletePoints->setChecked(false);
    this->setPointLeft(QPointF());
    this->setPointRight(QPointF());
    mTreeWidget->selectionModel()->clearSelection();
    QList<QGraphicsItem *> itemsRight = mGraphicsViewRight->items();
    for (int i = 0; i < itemsRight.size(); i++){
      itemsRight[i]->setSelected(false);
    }
    QList<QGraphicsItem *> itemsLeft = mGraphicsViewLeft->items();
    for (int i = 0; i < itemsLeft.size(); i++){
      itemsLeft[i]->setSelected(false);
    }
  } else {
    disconnect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(setPointLeft(QPointF)));
    disconnect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(setPointRight(QPointF)));
    disconnect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointLeft(QPointF)));
    disconnect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointRight(QPointF)));
  }
  update();
}

//void GroundTruthView::onPushButtonDeletePoints(bool active)
//{
//  QSignalBlocker blocker(mAddPoints);
//  if (active){
//    mAddPoints->setChecked(false);
//  } else {
//  }
//  update();
//}

void GroundTruthView::onPushButtonAddPointClicked()
{
  emit addPoint(mComboBoxLeftImage->currentText(), QPointF(mLineEditLeftX->text().toDouble(), mLineEditLeftY->text().toDouble()),
                mComboBoxRightImage->currentText(), QPointF(mLineEditRightX->text().toDouble(), mLineEditRightY->text().toDouble()));

  mLineEditLeftX->clear();
  mLineEditLeftY->clear();
  mLineEditRightX->clear();
  mLineEditRightY->clear();
}

void GroundTruthView::onPushButtonLockViewsToggled(bool active)
{
  bLockViews = active;
  update();
}

void GroundTruthView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
  mGraphicsViewLeft->scene()->clearSelection();
  mGraphicsViewLeft->setImage(QImage(leftImage));
}

void GroundTruthView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(rightImage));
}

void GroundTruthView::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList){
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void GroundTruthView::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList){
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void GroundTruthView::setPointLeft(const QPointF &pt)
{
  if (pt.isNull()){
    mLineEditLeftX->setText("");
    mLineEditLeftY->setText("");
    mLabelDetailLeft->clear();
  } else {
    mLineEditLeftX->setText(QString::number(pt.x()));
    mLineEditLeftY->setText(QString::number(pt.y()));

    QString image_left(mComboBoxLeftImage->itemData(mComboBoxLeftImage->currentIndex()).toString());
    QImageReader reader(image_left);
    QRect rect(static_cast<int>(pt.x()) - 25, static_cast<int>(pt.y()) - 25, 50, 50);
    reader.setClipRect(rect);
    QImage image = reader.read();
    QPixmap pixmap = QPixmap::fromImage(image);
    QPainter p (&pixmap);
    p.setPen (Qt::green);
    p.drawLine (0, 25, 50, 25);
    p.drawLine (25, 0, 25, 50);
    p.end ();
    mLabelDetailLeft->setPixmap(pixmap);

  }
}

void GroundTruthView::setPointRight(const QPointF &pt)
{
  if (pt.isNull()){
    mLineEditRightX->setText("");
    mLineEditRightY->setText("");
    mLabelDetailRight->clear();
  } else {
    mLineEditRightX->setText(QString::number(pt.x()));
    mLineEditRightY->setText(QString::number(pt.y()));

    QString image_right(mComboBoxRightImage->itemData(mComboBoxRightImage->currentIndex()).toString());
    QImageReader reader(image_right);
    QRect rect(static_cast<int>(pt.x()) - 25, static_cast<int>(pt.y()) - 25, 50, 50);
    reader.setClipRect(rect);
    QImage image = reader.read();
    QPixmap pixmap = QPixmap::fromImage(image);
    QPainter p (&pixmap);
    p.setPen (Qt::green);
    p.drawLine (0, 25, 50, 25);
    p.drawLine (25, 0, 25, 50);
    p.end();
    mLabelDetailRight->setPixmap(pixmap);
  }
}

void GroundTruthView::setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points)
{
  QSignalBlocker blocker(mTreeWidget);

  mTreeWidget->clear();
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

  for (size_t i = 0; i < points.size(); i++){

    QPointF query_point = points[i].first;
    QPointF train_point = points[i].second;

    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i+1));
    treeWidgetItem->setText(1, QString::number(query_point.x()));
    treeWidgetItem->setText(2, QString::number(query_point.y()));
    treeWidgetItem->setText(3, QString::number(train_point.x()));
    treeWidgetItem->setText(4, QString::number(train_point.y()));
    mTreeWidget->addTopLevelItem(treeWidgetItem);

    DiagonalCrossGraphicItem *crossGraphicItem1 = new DiagonalCrossGraphicItem(query_point);
    crossGraphicItem1->setPen(pen);
    crossGraphicItem1->setSize(symbol_size);
    crossGraphicItem1->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItem1->setToolTip(QString::number(static_cast<int>(i+1)));
    mGraphicsViewLeft->scene()->addItem(crossGraphicItem1);
    DiagonalCrossGraphicItem *crossGraphicItem2 = new DiagonalCrossGraphicItem(train_point);
    crossGraphicItem2->setPen(pen);
    crossGraphicItem2->setSize(symbol_size);
    crossGraphicItem2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItem2->setToolTip(QString::number(static_cast<int>(i+1)));
    mGraphicsViewRight->scene()->addItem(crossGraphicItem2);
  }
}

void GroundTruthView::addHomologousPoint(const QPointF &pt1, const QPointF &pt2)
{
  QSignalBlocker blocker(mTreeWidget);

  int id = mTreeWidget->topLevelItemCount();
  QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
  treeWidgetItem->setText(0, QString::number(id+1));
  treeWidgetItem->setText(1, QString::number(pt1.x()));
  treeWidgetItem->setText(2, QString::number(pt1.y()));
  treeWidgetItem->setText(3, QString::number(pt2.x()));
  treeWidgetItem->setText(4, QString::number(pt2.y()));
  mTreeWidget->addTopLevelItem(treeWidgetItem);

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  double symbol_size = 20.;
  DiagonalCrossGraphicItem *crossGraphicItem1 = new DiagonalCrossGraphicItem(pt1);
  crossGraphicItem1->setPen(pen);
  crossGraphicItem1->setSize(symbol_size);
  crossGraphicItem1->setFlag(QGraphicsItem::ItemIsSelectable, true);
  crossGraphicItem1->setToolTip(QString::number(id+1));
  mGraphicsViewLeft->scene()->addItem(crossGraphicItem1);
  DiagonalCrossGraphicItem *crossGraphicItem2 = new DiagonalCrossGraphicItem(pt2);
  crossGraphicItem2->setPen(pen);
  crossGraphicItem2->setSize(symbol_size);
  crossGraphicItem2->setFlag(QGraphicsItem::ItemIsSelectable, true);
  crossGraphicItem2->setToolTip(QString::number(id));
  mGraphicsViewRight->scene()->addItem(crossGraphicItem2);

  if (mCrossGraphicItem2){
    mGraphicsViewRight->scene()->removeItem(mCrossGraphicItem2);
    delete mCrossGraphicItem2;
    mCrossGraphicItem2 = nullptr;
  }

  if (mCrossGraphicItem1){
    mGraphicsViewLeft->scene()->removeItem(mCrossGraphicItem1);
    delete mCrossGraphicItem1;
    mCrossGraphicItem1 = nullptr;
  }
}

void GroundTruthView::init()
{
  this->setWindowTitle(tr("Ground Truth Editor"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);


  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mComboBoxRightImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxRightImage, 1, 1, 1, 1);

  QLabel *labelImage1 = new QLabel(tr("Left Image:"), this);
  gridLayout->addWidget(labelImage1, 0, 0, 1, 1);

  QLabel *labelImage2 = new QLabel(tr("Right Image:"), this);
  gridLayout->addWidget(labelImage2, 0, 1, 1, 1);

  mComboBoxLeftImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxLeftImage, 1, 0, 1, 1);

  QToolBar *toolBar = new QToolBar(this);
  mAddPoints = new QAction(QIcon(":/ico/48/img/material/48/icons8_define_location_48px.png"), tr("Add Points"), this);
  mAddPoints->setStatusTip(tr("Add Points"));
  mAddPoints->setCheckable(true);
  mAddPoints->setChecked(false);
  connect(mAddPoints, SIGNAL(toggled(bool)), this, SLOT(onPushButtonAddPoints(bool)));
  toolBar->addAction(mAddPoints);

//  mDeletePoints = new QAction(QIcon(":/ico/48/img/material/48/icons8_erase_48px.png"), tr("Delete selected points"), this);
//  mDeletePoints->setStatusTip(tr("Delete selected points"));
//  mDeletePoints->setCheckable(true);
//  mDeletePoints->setChecked(false);
//  connect(mDeletePoints, SIGNAL(toggled(bool)), this, SLOT(onPushButtonDeletePoints(bool)));
//  toolBar->addAction(mDeletePoints);

  gridLayout->addWidget(toolBar, 2, 0, 1, 2);

  QGridLayout *gridLayoutGraphicsView = new QGridLayout(this);

  mGraphicsViewLeft = new GraphicViewer(this);
  mGraphicsViewLeft->setMinimumSize(QSize(200, 200));
  gridLayoutGraphicsView->addWidget(mGraphicsViewLeft, 0, 0, 1, 1);

  mPushButtonLockViews = new QPushButton(this);
  mPushButtonLockViews->setCheckable(true);
  mPushButtonLockViews->setIcon(QIcon(":/ico/24/img/material/24/icons8_web_lock_24px.png"));
  mPushButtonLockViews->setIconSize(QSize(24,24));
  mPushButtonLockViews->setMaximumSize(30, 30);
  gridLayoutGraphicsView->addWidget(mPushButtonLockViews, 0, 1, 1, 1);

  mGraphicsViewRight = new GraphicViewer(this);
  mGraphicsViewRight->setMinimumSize(QSize(200, 200));
  gridLayoutGraphicsView->addWidget(mGraphicsViewRight, 0, 2, 1, 1);
  gridLayout->addLayout(gridLayoutGraphicsView, 3, 0, 1, 2);

  QLabel *labelMatches = new QLabel(tr("Matches:"), this);
  gridLayout->addWidget(labelMatches, 4, 0, 1, 1);

  mTreeWidget = new QTreeWidget(this);
  mTreeWidget->setMaximumSize(QSize(16777215, 200));
  gridLayout->addWidget(mTreeWidget, 5, 0, 2, 1);

  QTreeWidgetItem *qTreeWidgetItem = mTreeWidget->headerItem();
  qTreeWidgetItem->setText(0, tr("ID"));
  qTreeWidgetItem->setText(1, tr("Left X"));
  qTreeWidgetItem->setText(2, tr("Left Y"));
  qTreeWidgetItem->setText(3, tr("Right X"));
  qTreeWidgetItem->setText(4, tr("Right Y"));

  mTreeWidget->setAlternatingRowColors(true);

  QFrame *frame = new QFrame(this);
  frame->setMaximumSize(QSize(16777215, 200));
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);

  QGridLayout *gridLayout2 = new QGridLayout(frame);
  gridLayout2->setContentsMargins(0,0,0,0);

  QGroupBox *groupBoxLeft = new QGroupBox(tr("Left Point"), frame);
  groupBoxLeft->setMaximumSize(QSize(16777215, 100));
  QGridLayout *gridLayoutLeft = new QGridLayout(groupBoxLeft);
  QLabel *labelLeftX = new QLabel(tr("X:"), groupBoxLeft);
  gridLayoutLeft->addWidget(labelLeftX, 0, 0, 1, 2);
  mLineEditLeftX = new QLineEdit(groupBoxLeft);
  mLineEditLeftX->setEnabled(false);
  gridLayoutLeft->addWidget(mLineEditLeftX, 0, 2, 1, 1);
  QLabel *labelLeftY = new QLabel(tr("Y:"), groupBoxLeft);
  gridLayoutLeft->addWidget(labelLeftY, 1, 0, 1, 1);
  mLineEditLeftY = new QLineEdit(groupBoxLeft);
  mLineEditLeftY->setEnabled(false);
  gridLayoutLeft->addWidget(mLineEditLeftY, 1, 2, 1, 1);
  mLabelDetailLeft = new QLabel(groupBoxLeft);
  mLabelDetailLeft->setMinimumSize(QSize(50, 50));
  mLabelDetailLeft->setMaximumSize(QSize(50, 50));
  gridLayoutLeft->addWidget(mLabelDetailLeft, 0, 3, 2, 1);
  gridLayout2->addWidget(groupBoxLeft);

  QGroupBox *groupBoxRight = new QGroupBox(tr("Right Point"), frame);
  groupBoxRight->setMaximumSize(QSize(16777215, 100));
  QGridLayout *gridLayoutRight = new QGridLayout(groupBoxRight);
  QLabel *labelRightX = new QLabel(tr("X:"), groupBoxRight);
  gridLayoutRight->addWidget(labelRightX, 0, 0, 1, 1);
  mLineEditRightX = new QLineEdit(groupBoxRight);
  mLineEditRightX->setEnabled(false);
  gridLayoutRight->addWidget(mLineEditRightX, 0, 2, 1, 1);
  QLabel *labelRightY = new QLabel(tr("Y:"), groupBoxRight);
  gridLayoutRight->addWidget(labelRightY, 1, 0, 1, 1);
  mLineEditRightY = new QLineEdit(groupBoxRight);
  mLineEditRightY->setEnabled(false);
  gridLayoutRight->addWidget(mLineEditRightY, 1, 2, 1, 1);
  mLabelDetailRight = new QLabel(groupBoxRight);
  mLabelDetailRight->setMinimumSize(QSize(50, 50));
  mLabelDetailRight->setMaximumSize(QSize(50, 50));
  gridLayoutRight->addWidget(mLabelDetailRight, 0, 3, 2, 1);
  gridLayout2->addWidget(groupBoxRight);

  mPushButtonAddPoint = new QPushButton(tr("Add Point"), frame);
  mPushButtonAddPoint->setMaximumSize(QSize(280, 16777215));
  gridLayout2->addWidget(mPushButtonAddPoint, 0, 1, 1, 1);
  mPushButtonDelete = new QPushButton(tr("Delete"), frame);
  mPushButtonDelete->setMaximumSize(QSize(280, 16777215));
  gridLayout2->addWidget(mPushButtonDelete, 1, 1, 1, 1);

  gridLayout->addWidget(frame, 5, 1, 1, 1);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Save)->setText("Save");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 7, 0, 1, 2);

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

void GroundTruthView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void GroundTruthView::update()
{
  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bUnsavedChanges);
  mPushButtonDelete->setEnabled(mTreeWidget->selectedItems().size() > 0);
  mPushButtonAddPoint->setEnabled(mAddPoints->isChecked() &&
                                  !mLineEditLeftX->text().isEmpty() &&
                                  !mLineEditLeftY->text().isEmpty() &&
                                  !mLineEditRightX->text().isEmpty() &&
                                  !mLineEditRightY->text().isEmpty());
  mTreeWidget->setDisabled(mAddPoints->isChecked());

  mPushButtonLockViews->setDisabled(mTrf.isIdentity());
}

void GroundTruthView::setUnsavedChanges(bool value)
{
  bUnsavedChanges = value;
  update();
}

void GroundTruthView::clickedPointLeft(const QPointF &pt)
{
  QColor color;
  color.setNamedColor(QString("#0000FF"));
  QPen pen(color, 1.);

  if (mCrossGraphicItem1){
    mGraphicsViewLeft->scene()->removeItem(mCrossGraphicItem1);
    delete mCrossGraphicItem1;
    mCrossGraphicItem1 = nullptr;
  }

  mCrossGraphicItem1 = new CrossGraphicItem(pt);
  mCrossGraphicItem1->setPen(pen);
  mCrossGraphicItem1->setSize(20);
  mGraphicsViewLeft->scene()->addItem(mCrossGraphicItem1);

//  if (mTrf.isIdentity() == false && bLockViews == true){
//    QPointF trf_point = mTrf.map(pt);
//    mGraphicsViewRight->centerOn(trf_point);
//  }

  update();
}

void GroundTruthView::clickedPointRight(const QPointF &pt)
{
  QColor color;
  color.setNamedColor(QString("#0000FF"));
  QPen pen(color, 1.);

  if (mCrossGraphicItem2){
    mGraphicsViewRight->scene()->removeItem(mCrossGraphicItem2);
    delete mCrossGraphicItem2;
    mCrossGraphicItem2 = nullptr;
  }

  mCrossGraphicItem2 = new CrossGraphicItem(pt);
  mCrossGraphicItem2->setPen(pen);
  mCrossGraphicItem2->setSize(20);
  mGraphicsViewRight->scene()->addItem(mCrossGraphicItem2);

//  if (mTrf.isIdentity() == false && bLockViews == true){
//    QPointF trf_point = mTrf.map(pt);
//    mGraphicsViewLeft->centerOn(trf_point);
//  }

  update();
}

void GroundTruthView::setTransform(const QTransform &trf)
{
  mTrf = trf;
  update();
}

} // namespace fme

