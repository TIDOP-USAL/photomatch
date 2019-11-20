#ifndef PHOTOMATCH_FEATURES_VIEWER_VIEW_H
#define PHOTOMATCH_FEATURES_VIEWER_VIEW_H

#include "mvp.h"

class QTreeWidget;
class QComboBox;
class QDialogButtonBox;

namespace photomatch
{

class GraphicViewer;

class IFeaturesViewerView
  : public IDialogView
{
  Q_OBJECT

public:

  explicit IFeaturesViewerView(QWidget *parent = nullptr,
                               Qt::WindowFlags f = Qt::WindowFlags())
       : IDialogView(parent, f) {}
  virtual ~IFeaturesViewerView() = default;

  /*!
   * \brief setSessionName
   * \param[in] name Nombre de sesión
   */
  virtual void setSessionName(const QString &name) = 0;

  /*!
   * \brief Set the list of images
   * \param[in] imageList List of images
   */
  virtual void setImageList(const std::vector<QString> &imageList) = 0;

  /*!
   * \brief setCurrentImage
   * \param leftImage
   */
  virtual void setCurrentImage(const QString &leftImage) = 0;

  /*!
   * \brief setKeyPoints
   * \param[in] keyPoints Keypoints
   */
  virtual void setKeyPoints(const std::vector<std::tuple<QPointF, double, double>> &keyPoints) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) = 0;

signals:

  void imageChange(QString);

};


class FeaturesViewerView
  : public IFeaturesViewerView
{
  Q_OBJECT

public:

  FeaturesViewerView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~FeaturesViewerView() override;

protected:

  //void changeEvent(QEvent *e) override;

protected slots:

  void onGraphicsViewSelectionChanged();
  void onTreeWidgetItemSelectionChanged();

// IFeaturesViewerView interface

  void setSessionName(const QString &name) override;
  void setImageList(const std::vector<QString> &imageList) override;
  void setCurrentImage(const QString &leftImage) override;
  void setKeyPoints(const std::vector<std::tuple<QPointF, double, double>> &keyPoints) override;
  void setBGColor(const QString &bgColor) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

// QWidget interface

protected:

  void closeEvent(QCloseEvent *event) override;

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox *mComboBoxImages;
  GraphicViewer *mGraphicView;
  QTreeWidget *mTreeWidget;
  QString mMarkerColor;
  int mMarkerType;
  int mMarkerSize;
  int mMarkerWidth;
};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_VIEW_H
