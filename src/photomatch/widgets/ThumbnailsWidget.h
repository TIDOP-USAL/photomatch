#ifndef PHOTOMATCH_THUMBNAILS_WIDGET_H
#define PHOTOMATCH_THUMBNAILS_WIDGET_H

#include <QImage>

#include "photomatch/widgets/PhotoMatchWidget.h"

class QListWidget;
class QListWidgetItem;
class QGridLayout;
template <typename T> class QFutureWatcher;

namespace photomatch
{

class PHOTOMATCH_EXPORT ThumbnailsWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  explicit ThumbnailsWidget(QWidget *parent = nullptr);
  virtual ~ThumbnailsWidget() override {}

  void setActiveImage(const QString &image);
  void setActiveImages(const QStringList &images);

signals:

  void openImage(QString);
  void selectImage(QString);
  void selectImages(QStringList);
  void deleteImages(QStringList);

public slots:

  void addThumbnail(const QString &thumb);
  void addThumbnails(const QStringList &thumb);
  void deleteThumbnail(const QString &thumb);
  void clear();

private slots:

  void onThumbnailDoubleClicked(QListWidgetItem *item);
  void onSelectionChanged();

  void onThumbnailToggled(bool active);
  void onThumbnailSmallToggled(bool active);
  void onDetailsToggled(bool active);
  void onDeleteImageClicked();

  void showThumbnail(int id);
  void finished();

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  virtual void init() override;

protected:

  QListWidget *mListWidget;
  QGridLayout *mGridLayout;
  QSize mIconSize;
  QAction *mThumbnailAction;
  QAction *mThumbnailSmallAction;
  QAction *mDetailsAction;
  QAction *mDeleteImageAction;
  QFutureWatcher<QImage> *mFutureWatcherThumbnail;
};

} // namespace photomatch

#endif // PHOTOMATCH_THUMBNAILS_WIDGET_H
