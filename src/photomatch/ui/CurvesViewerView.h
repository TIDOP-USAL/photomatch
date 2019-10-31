#ifndef PHOTOMATCH_CURVES_VIEWER_VIEW_H
#define PHOTOMATCH_CURVES_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;

namespace QtCharts
{
class QChart;
class QValueAxis;
}

namespace photomatch
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

  virtual QString leftImage() const = 0;

  /*!
   * \brief Set the left image
   * \param[in] leftImage Image izquierda
   */
  virtual void setLeftImage(const QString &leftImage) = 0;

  virtual QString rightImage() const = 0;

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

  virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) = 0;
  virtual void eraseCurve(const QString &session) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void drawCurve(QString, QString, QString);
  void deleteCurve(QString);
};

class CurvesViewerView
  : public ICurvesViewerView
{

  Q_OBJECT

public:

  CurvesViewerView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CurvesViewerView() override;

private slots:

  void onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item,int column);

// ICurvesViewerView interface

  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  virtual QString leftImage() const override;
  virtual void setLeftImage(const QString &leftImage) override;
  virtual QString rightImage() const override;
  virtual void setRightImage(const QString &rightImage) override;
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) override;
  virtual void setRightImageList(const std::vector<QString> &rightImageList) override;
  virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) override;
  virtual void eraseCurve(const QString &session) override;

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
  QtCharts::QValueAxis *mAxisX;
  QtCharts::QValueAxis *mAxisY;
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

};



/*!
 * \brief DET (Detection Error Tradeoff) Curve
 */
class DETCurvesViewer
    : public CurvesViewerView
{

  Q_OBJECT

public:

  DETCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~DETCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_VIEW_H
