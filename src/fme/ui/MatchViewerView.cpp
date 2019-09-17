#include "MatchViewerView.h"

#include "fme/ui/utils/GraphicViewer.h"

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
  : IMatchViewerView(parent, f)
{
  init();

  connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));
  connect(mTreeWidgetMatches,  SIGNAL(itemSelectionChanged()),   this, SLOT(onTreeWidgetMatchesItemSelectionChanged()));

  connect(mButtonBox->button(QDialogButtonBox::Ok),     SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)), this, SLOT(reject()));
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
  //mGraphicsViewLeft->zoomExtend();
}

void MatchViewerView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
  mGraphicsViewRight->scene()->clearSelection();
  mGraphicsViewRight->setImage(QImage(rightImage));
  //mGraphicsViewRight->zoomExtend();
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

void MatchViewerView::setMatches(const std::vector<std::tuple<QPointF, QPointF, float> > &matches)
{
//  std::vector<QPointF> points_left(matches.size());
//  std::vector<QPointF> points_right(matches.size());

  QSignalBlocker blocker(mTreeWidgetMatches);
  mTreeWidgetMatches->clear();

  mGraphicsViewLeft->zoomExtend();
  mGraphicsViewRight->zoomExtend();

//  /////////////////////////////////////////////////////////////////////////
//  /// No esta bien aqui...
//  Settings &settings = Settings::instance();
//  QColor color;
//  color.setNamedColor(settings.keyPointsColor());
//  QPen pen(color, 1.);
//  QBrush brush;
//  if (settings.keyPointsBgColor().compare("-") == 0){
//    brush = QBrush(Qt::NoBrush);
//  } else {
//    brush.setColor(QColor(settings.keyPointsBgColor()));
//    brush.setStyle(Qt::SolidPattern);
//  }

//  int symbol = settings.symbol();
//  double symbol_size = settings.symbolSize();
//  double r = symbol_size / 2.;

//  /////////////////////////////////////////////////////////////////////////

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  QBrush brush;
  brush = QBrush(Qt::NoBrush);
  int symbol = 0;
  double symbol_size = 10.;
  double r = symbol_size / 2.;

  for (size_t i = 0; i < matches.size(); i++){
    //points_left[i] = matches[i].first;
    //points_right[i] = matches[i].second;
    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i + 1));
    QPointF query_point, train_point;
    double distance;
    std::tie(query_point, train_point, distance) = matches[i];
    treeWidgetItem->setText(1, QString::number(query_point.x()));
    treeWidgetItem->setText(2, QString::number(query_point.y()));
    treeWidgetItem->setText(3, QString::number(train_point.x()));
    treeWidgetItem->setText(4, QString::number(train_point.y()));
    treeWidgetItem->setText(5, QString::number(distance));
    mTreeWidgetMatches->addTopLevelItem(treeWidgetItem);

    /// Dibujado de puntos
    if (symbol == 0){
      /// Circle
      QGraphicsEllipseItem *ellipse_left = mGraphicsViewLeft->scene()->addEllipse(query_point.x() - r,
                                                                          query_point.y() - r,
                                                                          r * 2, r * 2, pen, brush);
      QGraphicsEllipseItem *ellipse_right = mGraphicsViewRight->scene()->addEllipse(train_point.x() - r,
                                                                          train_point.y() - r,
                                                                          r * 2, r * 2, pen, brush);
      ///e->setToolTip("ID punto...");
      ellipse_left->setFlag(QGraphicsItem::ItemIsSelectable, true);
      ellipse_left->setToolTip(QString::number(static_cast<int>(i+1)));
      ellipse_right->setFlag(QGraphicsItem::ItemIsSelectable, true);
      ellipse_right->setToolTip(QString::number(static_cast<int>(i+1)));

    } /*else if (symbol == 1) {
      /// Cross
      mScene->addLine(keyPoints[i].x() - r, keyPoints[i].y(), keyPoints[i].x() + r, keyPoints[i].y(), pen);
      mScene->addLine(keyPoints[i].x(), keyPoints[i].y() - r, keyPoints[i].x(), keyPoints[i].y() + r, pen);
    } else if (symbol == 2) {
      /// Diagonal Cross
      mScene->addLine(keyPoints[i].x() - r, keyPoints[i].y() - r, keyPoints[i].x() + r, keyPoints[i].y() + r, pen);
      mScene->addLine(keyPoints[i].x() - r, keyPoints[i].y() + r, keyPoints[i].x() + r, keyPoints[i].y() - r, pen);
    } else if (symbol == 3) {
      /// Square
      mScene->addRect(keyPoints[i].x() - r, keyPoints[i].y() - r, symbol_size, symbol_size, pen, brush);
    } else if (symbol == 4) {
      /// Triangle
    }*/
  }
  //ui->graphicsViewLeft->setKeyPoints(points_left);
  //ui->graphicsViewRight->setKeyPoints(points_right);
}

void MatchViewerView::init()
{
  this->setWindowTitle(tr("Match Viewer"));
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

  mGraphicsViewRight = new GraphicViewer(this);
  gridLayout->addWidget(mGraphicsViewRight, 2, 1, 1, 1);

  QLabel *labelMatches = new QLabel(tr("Matches:"), this);
  gridLayout->addWidget(labelMatches, 3, 0, 1, 1);

  mComboBoxLeftImage = new QComboBox(this);
  gridLayout->addWidget(mComboBoxLeftImage, 1, 0, 1, 1);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);
  gridLayout->addWidget(mButtonBox, 5, 0, 1, 2);

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  mGraphicsViewLeft = new GraphicViewer(this);

  gridLayout->addWidget(mGraphicsViewLeft, 2, 0, 1, 1);

  mTreeWidgetMatches = new QTreeWidget(this);
  mTreeWidgetMatches->setMaximumSize(QSize(16777215, 285));
  gridLayout->addWidget(mTreeWidgetMatches, 4, 0, 1, 2);

  QTreeWidgetItem *qTreeWidgetItem = mTreeWidgetMatches->headerItem();
  qTreeWidgetItem->setText(0, tr("ID"));
  qTreeWidgetItem->setText(1, tr("Left X"));
  qTreeWidgetItem->setText(2, tr("Left Y"));
  qTreeWidgetItem->setText(3, tr("Right X"));
  qTreeWidgetItem->setText(4, tr("Right Y"));
  qTreeWidgetItem->setText(5, tr("Distance"));

  mTreeWidgetMatches->setAlternatingRowColors(true);

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

void MatchViewerView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void MatchViewerView::update()
{
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

  //pt1_string_list[0]
  mGraphicsViewLeft->zoom11();
  mGraphicsViewLeft->centerOn(query_point);
  mGraphicsViewRight->zoom11();
  mGraphicsViewRight->centerOn(train_point);
}

void MatchViewerView::onTreeWidgetMatchesItemSelectionChanged()
{
  if (QTreeWidgetItem *item = mTreeWidgetMatches->currentItem()){

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

void MatchViewerView::onGraphicsViewLeftSelectionChanged()
{

}

void MatchViewerView::onGraphicsViewRightSelectionChanged()
{

}

} // namespace fme
