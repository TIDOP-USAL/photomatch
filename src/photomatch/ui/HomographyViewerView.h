#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QComboBox;

namespace photomatch
{

class GraphicViewer;

class IHomographyViewerView
  : public IDialogView
{

  Q_OBJECT

public:

  IHomographyViewerView(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f) {}
  virtual ~IHomographyViewerView() = default;

  virtual void setSessionName(const QString &name) = 0;

  /*!
   * \brief Set the left image
   * \param[in] leftImage Left image
   */
  virtual void setLeftImage(const QString &leftImage) = 0;

  /*!
   * \brief Set the right image
   * \param[in] rightImage Right image
   */
  virtual void setRightImage(const QString &rightImage) = 0;

  /*!
   * \brief Set the list of images for image selector left
   * \param[in] leftImageList List of left images
   */
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) = 0;

  /*!
   * \brief Set the list of images for image selector right
   * \param[in] rightImageList List of right images
   */
  virtual void setRightImageList(const std::vector<QString> &rightImageList) = 0;

  /*!
   * \brief setHomography
   * \param matches
   */
  virtual void setHomography(const QImage &homography) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void homography(QString, QString);

};


class HomographyViewerView
  : public IHomographyViewerView
{
  Q_OBJECT

public:

  HomographyViewerView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~HomographyViewerView() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);

// IHomographyViewerView interface

public:

  void setSessionName(const QString &name) override;
  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setHomography(const QImage &homography) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsView;

};

} // namespace photomatch


#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H
