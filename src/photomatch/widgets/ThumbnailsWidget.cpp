#include "ThumbnailsWidget.h"

//#include <tidop/img/imgio.h>

#include <QFileInfo>
#include <QListWidget>
#include <QGridLayout>
#include <QToolBar>
#include <QtConcurrent/QtConcurrentMap>
#include <QFutureWatcher>
#include <QImage>
#include <mutex>
#include <QImageReader>

static std::mutex sMutexThumbnail;

QImage makeThumbnail(const QString &thumb)
{  
  std::lock_guard<std::mutex> lck(sMutexThumbnail);

  QImageReader imageReader(thumb);
  QSize size = imageReader.size();
  double scale = 1.;
  int w = size.width();
  int h = size.height();
  if (w > h){
    scale = w / 200.;
  } else {
    scale = h / 200.;
  }
  size /= scale;
  imageReader.setScaledSize(size);
  QImage image_scaled = imageReader.read();

  return image_scaled;
}

namespace photomatch
{

ThumbnailsWidget::ThumbnailsWidget(QWidget *parent)
  : PhotoMatchWidget(parent),
    mListWidget(new QListWidget(this)),
    mGridLayout(new QGridLayout(this)),
    mThumbnailAction(nullptr),
    mDetailsAction(nullptr),
    mDeleteImageAction(nullptr)
{
  init();

  connect(mListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onThumbnailDoubleClicked(QListWidgetItem*)));
  connect(mListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectionChanged()));
}

void ThumbnailsWidget::setActiveImage(const QString &image)
{
  QListWidgetItem *item = nullptr;
  for (int i = 0; i < mListWidget->count(); i++){
   item = mListWidget->item(i);
   item->setSelected(item->toolTip().compare(image) == 0);
  }
}

void ThumbnailsWidget::setActiveImages(const QStringList &images)
{
  const QSignalBlocker blocker(mListWidget);
  QListWidgetItem *item = nullptr;
  for (int i = 0; i < mListWidget->count(); i++){
    item = mListWidget->item(i);
    item->setSelected(false);
    for (auto &image : images){
      if (item->toolTip().compare(image) == 0){
        item->setSelected(true);
        break;
      }
    }
  }
}

/* public slots */

void ThumbnailsWidget::addThumbnail(const QString &thumb)
{
  QImageReader imageReader(thumb);
  QSize size = imageReader.size();
  double scale = 1.;
  int w = size.width();
  int h = size.height();
  if (w > h){
    scale = w / 200.;
  } else {
    scale = h / 200.;
  }
  size /= scale;

  QFileInfo fileInfo(thumb);

  QPixmap pixmap(size.width(), size.height());
  pixmap.fill(QColor(Qt::GlobalColor::lightGray));
  QIcon icon(pixmap);
  QListWidgetItem *item = new QListWidgetItem(icon, fileInfo.fileName());
  item->setToolTip(fileInfo.absoluteFilePath());
  mListWidget->addItem(item);

  mFutureWatcherThumbnail->setFuture(QtConcurrent::mapped(thumb, makeThumbnail));
}

void ThumbnailsWidget::addThumbnails(const QStringList &thumbs)
{  
  for (auto thumb : thumbs) {

    QImageReader imageReader(thumb);
    QSize size = imageReader.size();
    double scale = 1.;
    int w = size.width();
    int h = size.height();
    if (w > h){
      scale = w / 200.;
    } else {
      scale = h / 200.;
    }
    size /= scale;

    QFileInfo fileInfo(thumb);
    QPixmap pixmap(size.width(), size.height());
    pixmap.fill(QColor(Qt::GlobalColor::lightGray));
    QIcon icon(pixmap);
    QListWidgetItem *item = new QListWidgetItem(icon, fileInfo.fileName());
    item->setToolTip(fileInfo.absoluteFilePath());
    mListWidget->addItem(item);
  }

  if (thumbs.empty() == false) {
    mFutureWatcherThumbnail->setFuture(QtConcurrent::mapped(thumbs, /*&ThumbnailsWidget::*/makeThumbnail));
  }
}

void ThumbnailsWidget::deleteThumbnail(const QString &thumb)
{
  //mListWidget
  QListWidgetItem *item = nullptr;

  for (int i = 0; i < mListWidget->count(); i++){
   item = mListWidget->item(i);
   if (item->toolTip().compare(thumb) == 0) {
     delete item;
     item = nullptr;
     break;
   }
  }
}

void ThumbnailsWidget::clear()
{
  reset();
}

void ThumbnailsWidget::onThumbnailDoubleClicked(QListWidgetItem *item)
{
  emit openImage(item->toolTip());
}

void ThumbnailsWidget::onSelectionChanged()
{
  if (mListWidget->currentItem()){
    QList<QListWidgetItem*> item = mListWidget->selectedItems();
    int size = item.size();
    if (size == 1) {
      emit selectImage(item[0]->toolTip());
    } else {
      QStringList selected_images;
      for (int i = 0; i < size; i++){
        selected_images.push_back(item[i]->toolTip());
      }
      emit selectImages(selected_images);
    }
  }
  update();
}

void ThumbnailsWidget::onThumbnailToggled(bool active)
{
  mIconSize  = QSize(200, 200);
  mListWidget->setIconSize(mIconSize);
  mListWidget->setViewMode(QListWidget::IconMode);
  mListWidget->setResizeMode(QListWidget::Fixed);
  const QSignalBlocker block0(mThumbnailAction);
  const QSignalBlocker block1(mThumbnailSmallAction);
  const QSignalBlocker block2(mDetailsAction);
  mThumbnailAction->setChecked(active);
  mThumbnailSmallAction->setChecked(!active);
  mDetailsAction->setChecked(!active);
}

void ThumbnailsWidget::onThumbnailSmallToggled(bool active)
{
  mIconSize  = QSize(100, 100);
  mListWidget->setIconSize(mIconSize);
  mListWidget->setViewMode(QListWidget::IconMode);
  mListWidget->setResizeMode(QListWidget::Fixed);
  const QSignalBlocker block0(mThumbnailAction);
  const QSignalBlocker block1(mThumbnailSmallAction);
  const QSignalBlocker block2(mDetailsAction);
  mThumbnailAction->setChecked(!active);
  mThumbnailSmallAction->setChecked(active);
  mDetailsAction->setChecked(!active);
}

void ThumbnailsWidget::onDetailsToggled(bool active)
{
  mIconSize  = QSize(50, 50);
  mListWidget->setIconSize(mIconSize);
  mListWidget->setViewMode(QListWidget::ListMode);
  mListWidget->setResizeMode(QListWidget::Fixed);
  const QSignalBlocker block0(mThumbnailAction);
  const QSignalBlocker block1(mThumbnailSmallAction);
  const QSignalBlocker block2(mDetailsAction);
  mThumbnailAction->setChecked(!active);
  mThumbnailSmallAction->setChecked(!active);
  mDetailsAction->setChecked(active);
}

void ThumbnailsWidget::onDeleteImageClicked()
{
  if (mListWidget->selectedItems().size() > 0){
    QStringList selectImages;
    for (const auto &item : mListWidget->selectedItems()){
      selectImages.push_back(item->toolTip());
    }

    emit deleteImages(selectImages);
  }
}

void ThumbnailsWidget::showThumbnail(int id)
{
  QListWidgetItem *item = mListWidget->item(id);
  QPixmap pixmap = QPixmap::fromImage(mFutureWatcherThumbnail->resultAt(id));
  QIcon icon(pixmap);
  item->setIcon(icon);
}

void ThumbnailsWidget::finished()
{

}

void ThumbnailsWidget::update()
{
  mDeleteImageAction->setEnabled(mListWidget->selectedItems().size() > 0);
}

void ThumbnailsWidget::retranslate()
{

}

void ThumbnailsWidget::reset()
{
  if (mFutureWatcherThumbnail->isRunning()) {
    mFutureWatcherThumbnail->cancel();
  }
  mListWidget->clear();
}

/* Private */

void ThumbnailsWidget::init()
{
  this->setWindowTitle("Thumbnails");

  QToolBar *toolBar = new QToolBar(this);

  mThumbnailAction = new QAction(QIcon(":/ico/48/img/material/48/icons8_medium_icons_48px.png"), tr("Thumbnails"), this);
  mThumbnailAction->setStatusTip(tr("Thumbnail"));
  mThumbnailAction->setCheckable(true);
  connect(mThumbnailAction, SIGNAL(toggled(bool)), this, SLOT(onThumbnailToggled(bool)));
  toolBar->addAction(mThumbnailAction);

  mThumbnailSmallAction = new QAction(QIcon(":/ico/48/img/material/48/icons8_small_icons_48px.png"), tr("Small Thumbnails"), this);
  mThumbnailSmallAction->setStatusTip(tr("Thumbnail small"));
  mThumbnailSmallAction->setCheckable(true);
  connect(mThumbnailSmallAction, SIGNAL(toggled(bool)), this, SLOT(onThumbnailSmallToggled(bool)));
  toolBar->addAction(mThumbnailSmallAction);

  toolBar->addSeparator();

  mDetailsAction = new QAction(QIcon(":/ico/48/img/material/48/icons8_details_48px.png"), tr("Details"), this);
  mDetailsAction->setStatusTip(tr("Details"));
  mDetailsAction->setCheckable(true);
  connect(mDetailsAction, SIGNAL(toggled(bool)), this, SLOT(onDetailsToggled(bool)));
  toolBar->addAction(mDetailsAction);

  toolBar->addSeparator();

  mDeleteImageAction = new QAction(QIcon(":/ico/48/img/material/48/icons8_delete_sign_48px.png"), tr("Delete image"), this);
  mDeleteImageAction->setStatusTip(tr("Delete image"));
  connect(mDeleteImageAction, SIGNAL(triggered(bool)), this, SLOT(onDeleteImageClicked()));
  toolBar->addAction(mDeleteImageAction);

  onThumbnailToggled(true);

  mListWidget->setSelectionMode(QListWidget::ExtendedSelection);

  mGridLayout->setMargin(0);
  mGridLayout->addWidget(toolBar);
  mGridLayout->addWidget(mListWidget);

  mFutureWatcherThumbnail = new QFutureWatcher<QImage>(this);
  connect(mFutureWatcherThumbnail, SIGNAL(resultReadyAt(int)), this, SLOT(showThumbnail(int)));
  connect(mFutureWatcherThumbnail, SIGNAL(finished()),         this, SLOT(finished()));

  update();
}

} // namespace photomatch
