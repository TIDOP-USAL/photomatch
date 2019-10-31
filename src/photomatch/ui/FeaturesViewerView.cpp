#include "FeaturesViewerView.h"

#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/KeyPointGraphicsItem.h"

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
  : IFeaturesViewerView(parent, f)
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
    KeyPointGraphicsItem *keyPoints = dynamic_cast<KeyPointGraphicsItem *>(item);
    if (keyPoints){
      mGraphicView->scene()->removeItem(item);
    }
  }

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  QBrush brush;
  brush = QBrush(Qt::NoBrush);

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

    KeyPointGraphicsItem *item = new KeyPointGraphicsItem(point);
    item->setPen(pen);
    item->setBrush(brush);
    item->setSize(size);
    item->setAngle(angle);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setToolTip(QString::number(static_cast<int>(i+1)));
    mGraphicView->scene()->addItem(item);
  }

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

} // namespace photomatch
