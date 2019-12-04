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

namespace photomatch
{

FeaturesViewerView::FeaturesViewerView(QWidget *parent, Qt::WindowFlags f)
  : IFeaturesViewerView(parent, f),
    mMarkerColor("#e5097e"),
    mSelectedMarkerColor("#ff0000"),
    mMarkerType(0),
    mMarkerSize(20),
    mMarkerWidth(1),
    mSelectedMarkerWidth(2)
{
  init();

  connect(mComboBoxImages,  SIGNAL(currentTextChanged(QString)),  this, SIGNAL(imageChange(QString)));
  connect(mTreeWidget,      SIGNAL(itemSelectionChanged()),       this, SLOT(onTreeWidgetItemSelectionChanged()));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

FeaturesViewerView::~FeaturesViewerView()
{
}

void FeaturesViewerView::onGraphicsViewSelectionChanged()
{
  const QSignalBlocker blocker1(mGraphicView);
  const QSignalBlocker blocker2(mTreeWidget);

  QList<QGraphicsItem *> items = mGraphicView->items();
  bool bSelectedItem = false;
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->isSelected() == true) {

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

void FeaturesViewerView::onTreeWidgetItemSelectionChanged()
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

//void FeaturesViewerView::changeEvent(QEvent *e)
//{
//  QDialog::changeEvent(e);
//  switch (e->type()) {
//  case QEvent::LanguageChange:
//    ui->retranslateUi(this);
//    break;
//  default:
//    break;
//  }
//}

void photomatch::FeaturesViewerView::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Keypoints Viewer ").append(name));
}

void FeaturesViewerView::setImageList(const std::vector<QString> &imageList)
{
  QSignalBlocker blocker(mComboBoxImages);
  mComboBoxImages->clear();
  for (auto &image : imageList){
    QFileInfo file_info(image);
    mComboBoxImages->addItem(file_info.baseName(), image);
  }
}

void FeaturesViewerView::setCurrentImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxImages);
  mComboBoxImages->setCurrentText(leftImage);
  mGraphicView->scene()->clearSelection();
  mGraphicView->setImage(QImage(mComboBoxImages->currentData().toString()));
  mGraphicView->zoomExtend();
}

void FeaturesViewerView::setKeyPoints(const std::vector<std::tuple<QPointF, double, double> > &keyPoints)
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

void FeaturesViewerView::setBGColor(const QString &bgColor)
{
  mGraphicView->setBackgroundBrush(QBrush(QColor(bgColor)));
}

void FeaturesViewerView::setSelectedMarkerStyle(const QString &color, int width)
{
  mSelectedMarkerColor = color;
  mSelectedMarkerWidth = width;
}

void FeaturesViewerView::setMarkerStyle(const QString &color, int width, int type, int size)
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
  emit imageChange(mComboBoxImages->currentText());

}

void FeaturesViewerView::init()
{
  this->setWindowTitle(tr("Keypoints Viewer"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  QLabel *labelImage1 = new QLabel(tr("Images:"), this);
  gridLayout->addWidget(labelImage1, 0, 0, 1, 1);

  mComboBoxImages = new QComboBox(this);
  gridLayout->addWidget(mComboBoxImages, 0, 1, 1, 1);

  mGraphicView = new GraphicViewer(this);
  gridLayout->addWidget(mGraphicView, 1, 0, 1, 2);

  mTreeWidget = new QTreeWidget(this);
  QTreeWidgetItem *qTreeWidgetItem = mTreeWidget->headerItem();
  qTreeWidgetItem->setText(0, "ID");
  qTreeWidgetItem->setText(1, tr("X"));
  qTreeWidgetItem->setText(2, tr("Y"));
  qTreeWidgetItem->setText(3, tr("Size"));
  qTreeWidgetItem->setText(4, tr("Angle"));
  mTreeWidget->setAlternatingRowColors(true);
  mTreeWidget->setMaximumSize(QSize(16777215, 192));

  gridLayout->addWidget(mTreeWidget, 2, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 3, 0, 1, 2);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  QMenu *contextMenuLeft = new QMenu(mGraphicView);
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), tr("Zoom In"), mGraphicView, SLOT(zoomIn()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), tr("Zoom Out"), mGraphicView, SLOT(zoomOut()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), tr("Zoom Extend"), mGraphicView, SLOT(zoomExtend()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), tr("Zoom 1:1"), mGraphicView, SLOT(zoom11()));
  mGraphicView->setContextMenu(contextMenuLeft);
  connect(mGraphicView, SIGNAL(selectionChanged()), this, SLOT(onGraphicsViewSelectionChanged()));

  update();

}

void FeaturesViewerView::clear()
{
  this->setWindowTitle(tr("Keypoints Viewer"));
  const QSignalBlocker blockerTreeWidget(mTreeWidget);
  mTreeWidget->clear();

  const QSignalBlocker blockerComboBoxImages(mComboBoxImages);
  mComboBoxImages->clear();
}

void FeaturesViewerView::update()
{

}

void FeaturesViewerView::retranslate()
{

}

void FeaturesViewerView::closeEvent(QCloseEvent *event)
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
}

} // namespace photomatch
