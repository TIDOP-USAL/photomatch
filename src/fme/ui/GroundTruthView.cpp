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
    mCrossGraphicItem2(nullptr)
{
  init();

  connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));

  connect(mPushButtonAddPoint, SIGNAL(clicked(bool)), this, SLOT(onPushButtonAddPointClicked()));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
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
  emit rightImageChange(image_right);
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
  if (QTreeWidgetItem *item = mTreeWidget->currentItem()){

    QPointF query_point(item->text(1).toDouble(), item->text(2).toDouble());
    QPointF train_point(item->text(3).toDouble(), item->text(4).toDouble());

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
}

void GroundTruthView::onGraphicsViewLeftSelectionChanged()
{

}

void GroundTruthView::onGraphicsViewRightSelectionChanged()
{

}

void GroundTruthView::onPushButtonAddPoints(bool active)
{
  if (active){
    connect(mGraphicsViewLeft, SIGNAL(mouseClicked(QPointF)), this, SIGNAL(markedLeftPoint(QPointF)));
    connect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SIGNAL(markedRightPoint(QPointF)));
  } else {
    disconnect(mGraphicsViewLeft, SIGNAL(mouseClicked(QPointF)), this, SIGNAL(markedLeftPoint(QPointF)));
    disconnect(mGraphicsViewRight, SIGNAL(mouseClicked(QPointF)), this, SIGNAL(markedRightPoint(QPointF)));
  }
}

void GroundTruthView::onPushButtonDeletePoints(bool active)
{

}

void GroundTruthView::onPushButtonAddPointClicked()
{
  emit addPoint(mComboBoxLeftImage->currentText(), QPointF(mLineEditLeftX->text().toDouble(), mLineEditLeftY->text().toDouble()),
                mComboBoxRightImage->currentText(), QPointF(mLineEditRightX->text().toDouble(), mLineEditRightY->text().toDouble()));

  mLineEditLeftX->clear();
  mLineEditLeftY->clear();
  mLineEditRightX->clear();
  mLineEditRightY->clear();
}

void GroundTruthView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
  mGraphicsViewLeft->scene()->clearSelection();
  mGraphicsViewLeft->setImage(QImage(leftImage));
  mGraphicsViewLeft->zoomExtend();
}

void GroundTruthView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(rightImage));
  mGraphicsViewRight->zoomExtend();
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
  mCrossGraphicItem1->setSize(10);
  mGraphicsViewLeft->scene()->addItem(mCrossGraphicItem1);

}

void GroundTruthView::setPointRight(const QPointF &pt)
{
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
  p.end ();
  mLabelDetailRight->setPixmap(pixmap);

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
  mCrossGraphicItem2->setSize(10);
  mGraphicsViewRight->scene()->addItem(mCrossGraphicItem2);
}

void GroundTruthView::addHomologousPoints(const QPointF &pt1, const QPointF &pt2)
{
  QSignalBlocker blocker(mTreeWidget);

  QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
  treeWidgetItem->setText(0, QString::number(1));
  treeWidgetItem->setText(1, QString::number(pt1.x()));
  treeWidgetItem->setText(2, QString::number(pt1.y()));
  treeWidgetItem->setText(3, QString::number(pt2.x()));
  treeWidgetItem->setText(4, QString::number(pt2.y()));
  mTreeWidget->addTopLevelItem(treeWidgetItem);

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  DiagonalCrossGraphicItem *crossGraphicItem1 = new DiagonalCrossGraphicItem(pt1);
  crossGraphicItem1->setPen(pen);
  crossGraphicItem1->setSize(10);
  mGraphicsViewLeft->scene()->addItem(crossGraphicItem1);
  DiagonalCrossGraphicItem *crossGraphicItem2 = new DiagonalCrossGraphicItem(pt2);
  crossGraphicItem2->setPen(pen);
  crossGraphicItem2->setSize(10);
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
  this->setWindowTitle(tr("Ground Truth"));
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

  mDeletePoints = new QAction(QIcon(":/ico/48/img/material/48/icons8_erase_48px.png"), tr("Delete selected points"), this);
  mDeletePoints->setStatusTip(tr("Delete selected points"));
  mDeletePoints->setCheckable(true);
  mDeletePoints->setChecked(false);
  connect(mDeletePoints, SIGNAL(toggled(bool)), this, SLOT(onPushButtonDeletePoints(bool)));
  toolBar->addAction(mDeletePoints);

  gridLayout->addWidget(toolBar, 2, 0, 1, 2);

  mGraphicsViewLeft = new GraphicViewer(this);
  mGraphicsViewLeft->setMinimumSize(QSize(200, 200));
  gridLayout->addWidget(mGraphicsViewLeft, 3, 0, 1, 1);

  mGraphicsViewRight = new GraphicViewer(this);
  mGraphicsViewRight->setMinimumSize(QSize(200, 200));
  gridLayout->addWidget(mGraphicsViewRight, 3, 1, 1, 1);

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
  //qTreeWidgetItem->setText(5, tr("Distance"));

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
  gridLayoutLeft->addWidget(mLineEditLeftX, 0, 2, 1, 1);
  QLabel *labelLeftY = new QLabel(tr("Y:"), groupBoxLeft);
  gridLayoutLeft->addWidget(labelLeftY, 1, 0, 1, 1);
  mLineEditLeftY = new QLineEdit(groupBoxLeft);
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
  gridLayoutRight->addWidget(mLineEditRightX, 0, 2, 1, 1);
  QLabel *labelRightY = new QLabel(tr("Y:"), groupBoxRight);
  gridLayoutRight->addWidget(labelRightY, 1, 0, 1, 1);
  mLineEditRightY = new QLineEdit(groupBoxRight);
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
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 7, 0, 1, 2);

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

void GroundTruthView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void GroundTruthView::update()
{
}

} // namespace fme

