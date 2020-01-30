#ifndef PHOTOMATCH_MULTIVIEW_VIEW_H
#define PHOTOMATCH_MULTIVIEW_VIEW_H

#include "mvp.h"

class QLabel;
class QDialogButtonBox;
class QListWidget;
class QGridLayout;
//template <typename T> class QFutureWatcher;

namespace photomatch
{

class IMultiViewView
  : public IDialogView
{

Q_OBJECT

public:

  IMultiViewView(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags())
  : IDialogView(parent, f) {}
  virtual ~IMultiViewView() = default;

  virtual void setSessionName(const QString &name) = 0;
  virtual void setPassPointIds(const std::vector<size_t> &id) = 0;
  virtual void addPassPointIds(size_t id) = 0;
  virtual void addPassPointIdsAndNImages(size_t id, size_t size) = 0;
  //virtual void setImages(const QStringList &images) = 0;
  //virtual void setImages(const std::vector<QPixmap> &images) = 0;
  virtual void setImages(const std::vector<std::pair<QString, QPointF>> &images) = 0;

signals:

  void idChange(int);
};


class MultiViewView
  : public IMultiViewView
{

  Q_OBJECT

public:

  MultiViewView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~MultiViewView() override;

private slots:

  //void showImages(int id);
  //void finished();
  void onListWidgetIdsCurrentRowChanged(int row);

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// IMultiViewView interface

public:

  void setSessionName(const QString &name) override;
  void setPassPointIds(const std::vector<size_t> &id) override;
  void addPassPointIds(size_t id) override;
  void addPassPointIdsAndNImages(size_t id, size_t size) override;
  //void setImages(const std::vector<QPixmap> &images) override;
  void setImages(const std::vector<std::pair<QString, QPointF>> &images) override;

protected:

  QLabel *mLabelIds;
  QListWidget *mListWidgetIds;
  QListWidget *mListWidgetImages;
  QDialogButtonBox *mButtonBox;
  //QFutureWatcher<QPixmap> *mFutureWatcher;

};

} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_VIEW_H
