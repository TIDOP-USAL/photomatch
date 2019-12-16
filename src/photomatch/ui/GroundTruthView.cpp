#include "GroundTruthView.h"

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
#include <QToolBar>
#include <QGroupBox>
#include <QLineEdit>
#include <QImageReader>
#include <QMessageBox>

namespace photomatch
{


GroundTruthView::GroundTruthView(QWidget *parent, Qt::WindowFlags f)
  : IGroundTruthView(parent, f),
    mCrossGraphicItem1(nullptr),
    mCrossGraphicItem2(nullptr),
    bEnableLockViews(false),
    bLockViews(false),
    mMarkerColor("#e5097e"),
    mMarkerSize(20),
    mMarkerWidth(1),
    mMarkerType(2),
    mPointsCounter(0),
    mSelectedMarkerColor("#ff0000"),
    mSelectedMarkerWidth(2)
{
  init();

  connect(mComboBoxLeftImage,   SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidget,          SIGNAL(itemSelectionChanged()),   this, SLOT(onTreeWidgetItemSelectionChanged()));
  connect(mPushButtonAddPoint,  SIGNAL(clicked(bool)),            this, SLOT(onPushButtonAddPointClicked()));
  connect(mPushButtonLockViews, SIGNAL(toggled(bool)),            this, SLOT(onPushButtonLockViewsToggled(bool)));
  connect(mPushButtonDelete,    SIGNAL(clicked(bool)),            this, SLOT(onPushButtonDeleteClicked()));
  connect(mImportGroundTruth,   SIGNAL(triggered(bool)),          this, SIGNAL(importGroundTruth()));
  connect(mAddPoints,           SIGNAL(toggled(bool)),            this, SLOT(onPushButtonAddPoints(bool)));
  connect(mSaveGroundTruth,     SIGNAL(triggered(bool)),          this, SIGNAL(saveGroundTruth()));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(onAccept()));
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

QString GroundTruthView::leftImage() const
{
  return mComboBoxLeftImage->currentText();
}

QString GroundTruthView::rightImage() const
{
  return mComboBoxRightImage->currentText();
}

void GroundTruthView::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemText(idx));
}

void GroundTruthView::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemText(idx));
  QString image_left(mComboBoxLeftImage->currentText());
  emit rightImageChange(image_right);
  emit loadHomologousPoints(image_left, image_right);
}

void GroundTruthView::onTreeWidgetItemSelectionChanged()
{
  if (QTreeWidgetItem *item = mTreeWidget->currentItem()){
    emit selectHomologous(mComboBoxLeftImage->currentText(),
                          mComboBoxRightImage->currentText(),
                          item->text(0).toInt());
  }
}

void GroundTruthView::onGraphicsViewLeftSelectionChanged()
{

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {
      emit selectHomologous(mComboBoxLeftImage->currentText(),
                            mComboBoxRightImage->currentText(),
                            items[i]->toolTip().toInt());

      bSelectedItem = true;

      break;
    }
  }

  if (bSelectedItem == false){
    unselectHomologous();
  }

}

void GroundTruthView::onGraphicsViewRightSelectionChanged()
{

  QList<QGraphicsItem *> items = mGraphicsViewRight->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++){
    if (items[i]->isSelected() == true) {

      emit selectHomologous(mComboBoxLeftImage->currentText(),
                            mComboBoxRightImage->currentText(),
                            items[i]->toolTip().toInt());

      bSelectedItem = true;

      break;
    }
  }

  if (bSelectedItem == false){
    unselectHomologous();
  }

}

void GroundTruthView::onPushButtonAddPoints(bool active)
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  const QSignalBlocker blocker2(mGraphicsViewRight);
  const QSignalBlocker blocker3(mTreeWidget);
  //const QSignalBlocker blocker4(mDeletePoints);

  if (active){
//    connect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(selectLeftPoint(QPointF)));
//    connect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(selectRightPoint(QPointF)));
    connect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointLeft(QPointF)));
    connect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointRight(QPointF)));
    //mDeletePoints->setChecked(false);
    this->setSelectLeftPoint(QPointF());
    this->setSelectedRightPoint(QPointF());
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
//    disconnect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(selectLeftPoint(QPointF)));
//    disconnect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(selectRightPoint(QPointF)));
    disconnect(mGraphicsViewLeft,  SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointLeft(QPointF)));
    disconnect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SLOT(clickedPointRight(QPointF)));
 
  
    if (mCrossGraphicItem1){
      mGraphicsViewLeft->scene()->removeItem(mCrossGraphicItem1);
      delete mCrossGraphicItem1;
      mCrossGraphicItem1 = nullptr;
    }

    if (mCrossGraphicItem2){
      mGraphicsViewRight->scene()->removeItem(mCrossGraphicItem2);
      delete mCrossGraphicItem2;
      mCrossGraphicItem2 = nullptr;
    }
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
  emit addHomologousPoints(mComboBoxLeftImage->currentText(),
                           QPointF(mLineEditLeftX->text().toDouble(),
                           mLineEditLeftY->text().toDouble()),
                           mComboBoxRightImage->currentText(),
                           QPointF(mLineEditRightX->text().toDouble(),
                           mLineEditRightY->text().toDouble()));

//  mLineEditLeftX->clear();
//  mLineEditLeftY->clear();
//  mLineEditRightX->clear();
//  mLineEditRightY->clear();
}

void GroundTruthView::onPushButtonLockViewsToggled(bool active)
{
  bLockViews = active;
  update();
}

void GroundTruthView::onPushButtonDeleteClicked()
{
  if (QTreeWidgetItem *item = mTreeWidget->currentItem()){
    emit IGroundTruthView::deleteHomologous(mComboBoxLeftImage->currentText(),
                                                 mComboBoxRightImage->currentText(),
                                                 item->text(0).toInt());
  }
}

void GroundTruthView::onAccept()
{
  if (bUnsavedChanges) {
    int i_ret = QMessageBox(QMessageBox::Information,
                              tr("Save Changes"),
                              tr("There are unsaved changes. Do you want to save them?"),
                              QMessageBox::Yes|QMessageBox::No).exec();
    
    if (i_ret == QMessageBox::Yes) {
      emit saveGroundTruth();
    } else if (i_ret == QMessageBox::Cancel) {
      return;
    }
  }
}

void GroundTruthView::removeHomologousPointInGraphicsViews(int id)
{

  for (auto &item : mGraphicsViewLeft->scene()->items()) {
    if (item->toolTip().toInt() == id){
      if (mMarkerType == 0){
        // Circle
        if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
        }
      } else if (mMarkerType == 1){
        // Cross
        if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
        }
      } else if (mMarkerType == 2){
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          mGraphicsViewLeft->scene()->removeItem(item);
        }
      }
      break;
    }
  }

  for (auto &item : mGraphicsViewRight->scene()->items()) {
    if (item->toolTip().toInt() == id){
      if (mMarkerType == 0){
        // Circle
        if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
        }
      } else if (mMarkerType == 1){
        // Cross
        if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
        }
      } else if (mMarkerType == 2){
        // Diagonal cross
        if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
          mGraphicsViewRight->scene()->removeItem(item);
        }
      }
      break;
    }
  }
}

void GroundTruthView::removeHomologousPointsInGraphicsViews()
{

  for (auto &item : mGraphicsViewLeft->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewLeft->scene()->removeItem(item);
      }
    }
  }

  for (auto &item : mGraphicsViewRight->scene()->items()) {
    if (mMarkerType == 0){
      // Circle
      if (CircleGraphicItem *keyPoints = dynamic_cast<CircleGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
      }
    } else if (mMarkerType == 1){
      // Cross
      if (CrossGraphicItem *keyPoints = dynamic_cast<CrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
      }
    } else if (mMarkerType == 2){
      // Diagonal cross
      if (DiagonalCrossGraphicItem *keyPoints = dynamic_cast<DiagonalCrossGraphicItem *>(item)){
        mGraphicsViewRight->scene()->removeItem(item);
      }
    }
  }

}

void GroundTruthView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->setCurrentText(leftImage);
  QString image_path = mComboBoxLeftImage->currentData().toString();
  mGraphicsViewLeft->scene()->clearSelection();
  mGraphicsViewLeft->setImage(QImage(image_path));

  update();
}

void GroundTruthView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->setCurrentText(rightImage);
  QString image_path = mComboBoxRightImage->currentData().toString();
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(image_path));

  update();
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

void GroundTruthView::setSelectLeftPoint(const QPointF &pt, bool newPoint)
{
  const QSignalBlocker blocker1(mGraphicsViewLeft);
  mGraphicsViewLeft->scene()->clearSelection();

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

    if (newPoint == false){
      mGraphicsViewLeft->zoom11();
      mGraphicsViewLeft->centerOn(pt);
      QPoint pt_left = mGraphicsViewLeft->mapFromScene(pt);
      QGraphicsItem *select_item_left = mGraphicsViewLeft->itemAt(pt_left);
      if (select_item_left) {
        select_item_left->setSelected(true);
      }
    } else {

      QColor color;
      color.setNamedColor(QString("#0000FF"));
      QPen pen(color, 1.);
      pen.setCosmetic(true);

      if (mCrossGraphicItem1){
        mGraphicsViewLeft->scene()->removeItem(mCrossGraphicItem1);
        delete mCrossGraphicItem1;
        mCrossGraphicItem1 = nullptr;
      }

      mCrossGraphicItem1 = new CrossGraphicItem(pt, mMarkerSize);
      mCrossGraphicItem1->setPen(pen);
      //mCrossGraphicItem1->setSize(20);
      mGraphicsViewLeft->scene()->addItem(mCrossGraphicItem1);
    }

  }

  update();
}

void GroundTruthView::setSelectedRightPoint(const QPointF &pt, bool newPoint)
{
  const QSignalBlocker blocker2(mGraphicsViewRight);
  mGraphicsViewRight->scene()->clearSelection();

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

    if (newPoint == false){
      mGraphicsViewRight->zoom11();
      mGraphicsViewRight->centerOn(pt);
      QPoint pt_right = mGraphicsViewRight->mapFromScene(pt);
      QGraphicsItem *select_item_right = mGraphicsViewRight->itemAt(pt_right);
      if (select_item_right) {
        select_item_right->setSelected(true);
      }
    } else {
      QColor color;
      color.setNamedColor(QString("#0000FF"));
      QPen pen(color, 1.);
      pen.setCosmetic(true);

      if (mCrossGraphicItem2){
        mGraphicsViewRight->scene()->removeItem(mCrossGraphicItem2);
        delete mCrossGraphicItem2;
        mCrossGraphicItem2 = nullptr;
      }

      mCrossGraphicItem2 = new CrossGraphicItem(pt, mMarkerSize);
      mCrossGraphicItem2->setPen(pen);
      //mCrossGraphicItem2->setSize(20);
      mGraphicsViewRight->scene()->addItem(mCrossGraphicItem2);

    }

  }

  update();
}

void GroundTruthView::setSelectedHomologous(const QPointF &ptLeft, const QPointF &ptRight)
{
  this->setSelectLeftPoint(ptLeft);
  this->setSelectedRightPoint(ptRight);

  const QSignalBlocker blocker2(mTreeWidget);

  QList<QGraphicsItem *> items = mGraphicsViewLeft->items();
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->isSelected() == true) {
      mTreeWidget->selectionModel()->clearSelection();
      for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
        QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
        if (item && item->text(0).compare(items[i]->toolTip()) == 0){
          item->setSelected(true);
          break;
        }
      }
      break;
    }
  }

  update();
}

void GroundTruthView::unselectHomologous()
{
  mLineEditLeftX->setText("");
  mLineEditLeftY->setText("");
  mLabelDetailLeft->clear();

  mLineEditRightX->setText("");
  mLineEditRightY->setText("");
  mLabelDetailRight->clear();

  QSignalBlocker blocker(mTreeWidget);
  mTreeWidget->selectionModel()->clearSelection();

  const QSignalBlocker blocker1(mGraphicsViewLeft);
  mGraphicsViewLeft->scene()->clearSelection();
  const QSignalBlocker blocker2(mGraphicsViewRight);
  mGraphicsViewRight->scene()->clearSelection();

  update();
}

void GroundTruthView::setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points)
{
  QSignalBlocker blocker(mTreeWidget);

  this->removeHomologousPointsInGraphicsViews();

  mTreeWidget->clear();

  mGraphicsViewLeft->zoomExtend();
  mGraphicsViewRight->zoomExtend();

  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

  mPointsCounter = static_cast<int>(points.size());
  for (size_t i = 0; i < points.size(); i++){

    QPointF query_point = points[i].first;
    QPointF train_point = points[i].second;

    if (query_point.isNull() && train_point.isNull()) continue;

    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i+1));
    treeWidgetItem->setText(1, QString::number(query_point.x()));
    treeWidgetItem->setText(2, QString::number(query_point.y()));
    treeWidgetItem->setText(3, QString::number(train_point.x()));
    treeWidgetItem->setText(4, QString::number(train_point.y()));
    mTreeWidget->addTopLevelItem(treeWidgetItem);

    if (mMarkerType == 0){
      // Circle
      CircleGraphicItem *itemLeft = new CircleGraphicItem(query_point, mMarkerSize); //mGraphicsViewLeft->scene()->addEllipse(query_point.x(), query_point.y(), mMarkerSize, mMarkerSize, pen);
      itemLeft->setPen(pen);
      itemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      itemLeft->setToolTip(QString::number(static_cast<int>(i+1)));
      itemLeft->setSelectedPen(select_pen);
      mGraphicsViewLeft->scene()->addItem(itemLeft);
      CircleGraphicItem *itemRight = new CircleGraphicItem(train_point, mMarkerSize);  //mGraphicsViewRight->scene()->addEllipse(train_point.x(), train_point.y(), mMarkerSize, mMarkerSize, pen);
      itemRight->setPen(pen);
      itemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      itemRight->setToolTip(QString::number(static_cast<int>(i+1)));
      itemRight->setSelectedPen(select_pen);
      mGraphicsViewRight->scene()->addItem(itemRight);
    } else if (mMarkerType == 1){
      // Cross
      CrossGraphicItem *crossGraphicItemLeft = new CrossGraphicItem(query_point, mMarkerSize);
      crossGraphicItemLeft->setPen(pen);
      //crossGraphicItemLeft->setSize(mMarkerSize);
      crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemLeft->setToolTip(QString::number(static_cast<int>(i+1)));
      crossGraphicItemLeft->setSelectedPen(select_pen);
      mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      CrossGraphicItem *crossGraphicItemRight = new CrossGraphicItem(train_point, mMarkerSize);
      crossGraphicItemRight->setPen(pen);
      //crossGraphicItemRight->setSize(mMarkerSize);
      crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemRight->setToolTip(QString::number(static_cast<int>(i+1)));
      crossGraphicItemRight->setSelectedPen(select_pen);
      mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
    } else if (mMarkerType == 2){
      // Diagonal cross
      DiagonalCrossGraphicItem *crossGraphicItemLeft = new DiagonalCrossGraphicItem(query_point, mMarkerSize);
      crossGraphicItemLeft->setPen(pen);
      //crossGraphicItemLeft->setSize(mMarkerSize);
      crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemLeft->setToolTip(QString::number(static_cast<int>(i+1)));
      crossGraphicItemLeft->setSelectedPen(select_pen);
      mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
      DiagonalCrossGraphicItem *crossGraphicItemRight = new DiagonalCrossGraphicItem(train_point, mMarkerSize);
      crossGraphicItemRight->setPen(pen);
      //crossGraphicItemRight->setSize(mMarkerSize);
      crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
      crossGraphicItemRight->setToolTip(QString::number(static_cast<int>(i+1)));
      crossGraphicItemRight->setSelectedPen(select_pen);
      mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
    }
  }
}

void GroundTruthView::addHomologous(const QPointF &pt1, const QPointF &pt2)
{
  QSignalBlocker blocker(mTreeWidget);

  mPointsCounter++;
  QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
  treeWidgetItem->setText(0, QString::number(mPointsCounter));
  treeWidgetItem->setText(1, QString::number(pt1.x()));
  treeWidgetItem->setText(2, QString::number(pt1.y()));
  treeWidgetItem->setText(3, QString::number(pt2.x()));
  treeWidgetItem->setText(4, QString::number(pt2.y()));
  mTreeWidget->addTopLevelItem(treeWidgetItem);

  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

  if (mMarkerType == 0){
    // Circle
    //QGraphicsEllipseItem *itemLeft = mGraphicsViewLeft->scene()->addEllipse(pt1.x(), pt1.y(), mMarkerSize, mMarkerSize, pen);
    CircleGraphicItem *itemLeft = new CircleGraphicItem(pt1, mMarkerSize);
    itemLeft->setPen(pen);
    itemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
    itemLeft->setToolTip(QString::number(mPointsCounter));
    itemLeft->setSelectedPen(select_pen);
    mGraphicsViewLeft->scene()->addItem(itemLeft);
    //QGraphicsEllipseItem *itemRight = mGraphicsViewRight->scene()->addEllipse(pt2.x(), pt2.y(), mMarkerSize, mMarkerSize, pen);
    CircleGraphicItem *itemRight = new CircleGraphicItem(pt2, mMarkerSize);
    itemRight->setPen(pen);
    itemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
    itemRight->setToolTip(QString::number(mPointsCounter));
    itemRight->setSelectedPen(select_pen);
    mGraphicsViewLeft->scene()->addItem(itemRight);
  } else if (mMarkerType == 1){
    // Cross
    CrossGraphicItem *crossGraphicItemLeft = new CrossGraphicItem(pt1, mMarkerSize);
    crossGraphicItemLeft->setPen(pen);
    //crossGraphicItemLeft->setSize(mMarkerSize);
    crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemLeft->setToolTip(QString::number(mPointsCounter));
    crossGraphicItemLeft->setSelectedPen(select_pen);
    mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
    CrossGraphicItem *crossGraphicItemRight = new CrossGraphicItem(pt2, mMarkerSize);
    crossGraphicItemRight->setPen(pen);
    //crossGraphicItemRight->setSize(mMarkerSize);
    crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemRight->setToolTip(QString::number(mPointsCounter));
    crossGraphicItemRight->setSelectedPen(select_pen);
    mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
  } else if (mMarkerType == 2){
    // Diagonal cross
    DiagonalCrossGraphicItem *crossGraphicItemLeft = new DiagonalCrossGraphicItem(pt1, mMarkerSize);
    crossGraphicItemLeft->setPen(pen);
    //crossGraphicItemLeft->setSize(mMarkerSize);
    crossGraphicItemLeft->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemLeft->setToolTip(QString::number(mPointsCounter));
    crossGraphicItemLeft->setSelectedPen(select_pen);
    mGraphicsViewLeft->scene()->addItem(crossGraphicItemLeft);
    DiagonalCrossGraphicItem *crossGraphicItemRight = new DiagonalCrossGraphicItem(pt2, mMarkerSize);
    crossGraphicItemRight->setPen(pen);
    //crossGraphicItemRight->setSize(mMarkerSize);
    crossGraphicItemRight->setFlag(QGraphicsItem::ItemIsSelectable, true);
    crossGraphicItemRight->setToolTip(QString::number(mPointsCounter));
    crossGraphicItemRight->setSelectedPen(select_pen);
    mGraphicsViewRight->scene()->addItem(crossGraphicItemRight);
  }

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

void GroundTruthView::deleteHomologous(int pointId)
{
  QSignalBlocker blocker(mTreeWidget);

  this->setSelectLeftPoint(QPointF());
  this->setSelectedRightPoint(QPointF());

  this->removeHomologousPointInGraphicsViews(pointId);

  for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
    QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
    if (item && item->text(0).toInt() == pointId){
      delete item;
      item = nullptr;
      break;
    }
  }

  mTreeWidget->selectionModel()->clearSelection();

  update();
}

void GroundTruthView::setHomologousDistance(int pointId, double distance)
{
  for (int j = 0; j < mTreeWidget->topLevelItemCount(); j++){
    QTreeWidgetItem *item = mTreeWidget->topLevelItem(j);
    if (item->text(0).toInt() == pointId){
      item->setText(5, QString::number(distance));
      break;
    }
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
  mImportGroundTruth = new QAction(QIcon(":/ico/48/img/material/48/icons8_opened_folder_48px.png"), tr("Import Ground Truth"), this);
  mImportGroundTruth->setStatusTip(tr("Import Ground Truth"));
  toolBar->addAction(mImportGroundTruth);

  mSaveGroundTruth= new QAction(QIcon(":/ico/48/img/material/48/icons8_save_48px.png"), tr("Save Ground Truth"), this);
  mSaveGroundTruth->setStatusTip(tr("Save Ground Truth"));
  toolBar->addAction(mSaveGroundTruth);

  toolBar->addSeparator();
  
  mAddPoints = new QAction(QIcon(":/ico/48/img/material/48/icons8_define_location_48px.png"), tr("Add Points"), this);
  mAddPoints->setStatusTip(tr("Add Points"));
  mAddPoints->setCheckable(true);
  mAddPoints->setChecked(false);
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
  mPushButtonLockViews->setVisible(false);

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
  qTreeWidgetItem->setText(5, tr("Distance"));

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
  mPushButtonDelete = new QPushButton(tr("Delete Point"), frame);
  mPushButtonDelete->setMaximumSize(QSize(280, 16777215));
  gridLayout2->addWidget(mPushButtonDelete, 1, 1, 1, 1);

  gridLayout->addWidget(frame, 5, 1, 1, 1);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Ok)->setText("Ok");
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
  const QSignalBlocker blocker1(mComboBoxLeftImage);
  const QSignalBlocker blocker2(mComboBoxRightImage);
  const QSignalBlocker blocker3(mTreeWidget);
  const QSignalBlocker blocker4(mAddPoints);

  mComboBoxLeftImage->clear();
  mComboBoxRightImage->clear();
  mLineEditLeftX->clear();
  mLineEditLeftY->clear();
  mLabelDetailLeft->clear();
  mLineEditRightX->clear();
  mLineEditRightY->clear();
  mLabelDetailRight->clear();

  mTrf.reset();

  mAddPoints->setChecked(false);
  mPushButtonAddPoint->setEnabled(false);
  mPushButtonDelete->setEnabled(false);

  mPointsCounter = 0;
}

void GroundTruthView::update()
{
  //mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bUnsavedChanges);
  mSaveGroundTruth->setEnabled(bUnsavedChanges);
  mPushButtonDelete->setEnabled(mTreeWidget->selectedItems().size() > 0);
  mPushButtonAddPoint->setEnabled(mAddPoints->isChecked() &&
                                  !mLineEditLeftX->text().isEmpty() &&
                                  !mLineEditLeftY->text().isEmpty() &&
                                  !mLineEditRightX->text().isEmpty() &&
                                  !mLineEditRightY->text().isEmpty());
  mTreeWidget->setDisabled(mAddPoints->isChecked());

  mPushButtonLockViews->setEnabled(bEnableLockViews);
}

void GroundTruthView::retranslate()
{

}

void GroundTruthView::setUnsavedChanges(bool value)
{
  bUnsavedChanges = value;
  update();
}

void GroundTruthView::enableLockView(bool enable)
{
  bEnableLockViews = enable;
  update();
}

void GroundTruthView::clickedPointLeft(const QPointF &pt)
{
  emit leftPointClicked(mComboBoxLeftImage->currentText(),
                        mComboBoxRightImage->currentText(),
                        pt);

  if (mCrossGraphicItem2 == nullptr){
    emit findRightPoint(mComboBoxLeftImage->currentText(),
                        mComboBoxRightImage->currentText(),
                        pt);
  }

  //void findLeftPoint(QString, QString,  QPointF);
  //void findRightPoint(QString, QString,  QPointF);

//  QColor color;
//  color.setNamedColor(QString("#0000FF"));
//  QPen pen(color, 1.);

//  if (mCrossGraphicItem1){
//    mGraphicsViewLeft->scene()->removeItem(mCrossGraphicItem1);
//    delete mCrossGraphicItem1;
//    mCrossGraphicItem1 = nullptr;
//  }

//  mCrossGraphicItem1 = new CrossGraphicItem(pt);
//  mCrossGraphicItem1->setPen(pen);
//  mCrossGraphicItem1->setSize(20);
//  mGraphicsViewLeft->scene()->addItem(mCrossGraphicItem1);

//  if (mTrf.isIdentity() == false && bLockViews == true){
//    QPointF trf_point = mTrf.map(pt);
//    mGraphicsViewRight->centerOn(trf_point);
//  }

//  update();
}

void GroundTruthView::clickedPointRight(const QPointF &pt)
{
  emit rightPointClicked(mComboBoxLeftImage->currentText(),
                         mComboBoxRightImage->currentText(),
                         pt);

  if (mCrossGraphicItem1 == nullptr){
    emit findLeftPoint(mComboBoxLeftImage->currentText(),
                        mComboBoxRightImage->currentText(),
                        pt);
  }

//  QColor color;
//  color.setNamedColor(QString("#0000FF"));
//  QPen pen(color, 1.);

//  if (mCrossGraphicItem2){
//    mGraphicsViewRight->scene()->removeItem(mCrossGraphicItem2);
//    delete mCrossGraphicItem2;
//    mCrossGraphicItem2 = nullptr;
//  }

//  mCrossGraphicItem2 = new CrossGraphicItem(pt);
//  mCrossGraphicItem2->setPen(pen);
//  mCrossGraphicItem2->setSize(20);
//  mGraphicsViewRight->scene()->addItem(mCrossGraphicItem2);

//  if (mTrf.isIdentity() == false && bLockViews == true){
//    QTransform trf_inv = mTrf.inverted();
//    QPointF trf_point = trf_inv.map(pt);
//    mGraphicsViewLeft->centerOn(trf_point);
//  }

//  update();
}

void GroundTruthView::setBGColor(const QString &bgColor)
{
  mGraphicsViewLeft->setBackgroundBrush(QBrush(QColor(bgColor)));
  mGraphicsViewRight->setBackgroundBrush(QBrush(QColor(bgColor)));
}

void GroundTruthView::setSelectedMarkerStyle(const QString &color, int width)
{
  mSelectedMarkerColor = color;
  mSelectedMarkerWidth = width;
}

void GroundTruthView::setMarkerStyle(const QString &color, int width, int type, int size)
{
  if (mMarkerType != type){
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

  mMarkerColor = color;
  mMarkerSize = size;
  mMarkerWidth = width;
  mMarkerType = type;

  QPen pen(QColor(mMarkerColor), mMarkerWidth);
  pen.setCosmetic(true);
  QPen select_pen(QColor(mSelectedMarkerColor), mSelectedMarkerWidth);
  select_pen.setCosmetic(true);

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
}

void GroundTruthView::setCenterLeftViewer(const QPointF & pt, bool zoom11)
{
  if (pt.isNull() == false) {
    mGraphicsViewLeft->zoom11();
    mGraphicsViewLeft->centerOn(pt);
  }
}

void GroundTruthView::setCenterRightViewer(const QPointF & pt, bool zoom11)
{
  if (pt.isNull() == false) {
    mGraphicsViewRight->zoom11();
    mGraphicsViewRight->centerOn(pt);
  }
}

void GroundTruthView::closeEvent(QCloseEvent *event)
{
  onAccept();
}

} // namespace photomatch



