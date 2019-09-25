#include "HomographyViewerView.h"

#include "fme/ui/utils/GraphicViewer.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QFileInfo>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>

namespace fme
{

HomographyViewerView::HomographyViewerView(QWidget *parent, Qt::WindowFlags f)
  : IHomographyViewerView(parent, f)
{
  init();

  connect(mComboBoxLeftImage,  SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxLeftImageIndexChanged(int)));
  connect(mComboBoxRightImage, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxRightImageIndexChanged(int)));

  connect(mButtonBox->button(QDialogButtonBox::Ok),     SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

HomographyViewerView::~HomographyViewerView()
{

}

void HomographyViewerView::onComboBoxLeftImageIndexChanged(int idx)
{
  emit leftImageChange(mComboBoxLeftImage->itemData(idx).toString());
}

void HomographyViewerView::onComboBoxRightImageIndexChanged(int idx)
{
  QString image_right(mComboBoxRightImage->itemData(idx).toString());
  QString image_left(mComboBoxLeftImage->currentData().toString());
  emit rightImageChange(image_right);
  emit homography(mComboBoxLeftImage->currentText(), mComboBoxRightImage->itemText(idx));
}

void HomographyViewerView::setLeftImage(const QString &leftImage)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  QFileInfo file_info(leftImage);
  mComboBoxLeftImage->setCurrentText(file_info.baseName());
  //mGraphicsViewLeft->scene()->clearSelection();
  //mGraphicsViewLeft->setImage(QImage(leftImage));
}

void HomographyViewerView::setRightImage(const QString &rightImage)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  QFileInfo file_info(rightImage);
  mComboBoxRightImage->setCurrentText(file_info.baseName());
//  mGraphicsViewRight->scene()->clearSelection();
//  mGraphicsViewRight->setImage(QImage(rightImage));
}

void HomographyViewerView::setLeftImageList(const std::vector<QString> &leftImageList)
{
  QSignalBlocker blocker(mComboBoxLeftImage);
  mComboBoxLeftImage->clear();
  for (auto &image : leftImageList){
    QFileInfo file_info(image);
    mComboBoxLeftImage->addItem(file_info.baseName(), image);
  }
}

void HomographyViewerView::setRightImageList(const std::vector<QString> &rightImageList)
{
  QSignalBlocker blocker(mComboBoxRightImage);
  mComboBoxRightImage->clear();
  for (auto &image : rightImageList){
    QFileInfo file_info(image);
    mComboBoxRightImage->addItem(file_info.baseName(), image);
  }
}

void HomographyViewerView::setHomography(const QImage &homography)
{
  mGraphicsView->scene()->clearSelection();
  mGraphicsView->setImage(homography);
  mGraphicsView->zoomExtend();
}

void HomographyViewerView::init()
{
  this->setWindowTitle(tr("Homography Viewer"));
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

  mGraphicsView = new GraphicViewer(this);
  gridLayout->addWidget(mGraphicsView, 2, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Help|QDialogButtonBox::Ok);
  gridLayout->addWidget(mButtonBox, 5, 0, 1, 2);

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(tr("Ok"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  QMenu *contextMenuLeft = new QMenu(mGraphicsView);
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), tr("Zoom In"), mGraphicsView, SLOT(zoomIn()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), tr("Zoom Out"), mGraphicsView, SLOT(zoomOut()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), tr("Zoom Extend"), mGraphicsView, SLOT(zoomExtend()));
  contextMenuLeft->addAction(QIcon(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), tr("Zoom 1:1"), mGraphicsView, SLOT(zoom11()));
  mGraphicsView->setContextMenu(contextMenuLeft);

  update();
}

void HomographyViewerView::clear()
{
  mComboBoxLeftImage->clear();
  mComboBoxLeftImage->clear();
}

void HomographyViewerView::update()
{
}

} // namespace fme
