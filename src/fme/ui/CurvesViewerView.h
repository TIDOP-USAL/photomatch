#ifndef FME_CURVES_VIEWER_VIEW_H
#define FME_CURVES_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QComboBox;
class QTreeWidget;
namespace QtCharts
{
class QChart;
}

namespace fme
{

class ICurvesViewerView
  : public IDialogView
{

  Q_OBJECT

public:

  ICurvesViewerView(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f)
  {}

  virtual ~ICurvesViewerView() override = default;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) = 0;

  /*!
   * \brief Set the left image
   * \param[in] leftImage Image izquierda
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

};

class CurvesViewerView
  : public ICurvesViewerView
{

  Q_OBJECT

public:

  CurvesViewerView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CurvesViewerView() override;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor);

  /*!
   * \brief Set the left image
   * \param[in] leftImage Image izquierda
   */
  virtual void setLeftImage(const QString &leftImage);

  /*!
   * \brief Set the right image
   * \param[in] rightImage Right image
   */
  virtual void setRightImage(const QString &rightImage);

  /*!
   * \brief Set the list of images for image selector left
   * \param[in] leftImageList List of left images
   */
  virtual void setLeftImageList(const std::vector<QString> &leftImageList);

  /*!
   * \brief Set the list of images for image selector right
   * \param[in] rightImageList List of right images
   */
  virtual void setRightImageList(const std::vector<QString> &rightImageList);

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);

// IDialogView interface

private:

  virtual void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  QTreeWidget *mTreeWidgetSessions;
  QtCharts::QChart *mChart;
};


/*!
 * \brief ROC curve (receiver operating characteristic)
 */
class ROCCurvesViewer
  : public CurvesViewerView
{

  Q_OBJECT

public:

  ROCCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~ROCCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

//public slots:

//  void clear() override;

//private slots:

//  void update() override;

};


/*!
 * \brief Precision-Recall Curve
 */
class PRCurvesViewer
    : public CurvesViewerView
{

  Q_OBJECT

public:

  PRCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~PRCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

//public slots:

//  void clear() override;

//private slots:

//  void update() override;

};

} // namespace fme

#endif // FME_CURVES_VIEWER_VIEW_H
