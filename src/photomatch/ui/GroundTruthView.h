#ifndef PHOTOMATCH_GROUND_TRUTH_VIEW_H
#define PHOTOMATCH_GROUND_TRUTH_VIEW_H

#include "mvp.h"

class QComboBox;
class QTreeWidgetItem;
class QTreeWidget;
class QDialogButtonBox;
class QLineEdit;
class QLabel;


namespace photomatch
{

class GraphicViewer;
class CrossGraphicItem;

class IGroundTruthView
  : public IDialogView
{

  Q_OBJECT

public:

  IGroundTruthView(QWidget *parent = nullptr,
                     Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f)
  {
  }

  virtual ~IGroundTruthView() = default;

  virtual QString imageLeft() const = 0;
  virtual QString imageRight() const = 0;

public slots:

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

  virtual void setPointLeft(const QPointF &pt) = 0;
  virtual void setPointRight(const QPointF &pt) = 0;

  virtual void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) = 0;
  virtual void addHomologousPoint(const QPointF &pt1, const QPointF &pt2) = 0;

  virtual void setUnsavedChanges(bool value) = 0;

  virtual void clickedPointLeft(const QPointF &pt) = 0;
  virtual void clickedPointRight(const QPointF &pt) = 0;

  virtual void setTransform(const QTransform &trf) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void addPoint(QString, QPointF, QString,  QPointF);
//  void markedLeftPoint(QPointF);
//  void markedRightPoint(QPointF);
  void loadHomologousPoints(QString, QString);
  void deleteHomologousPoint(QString, QString, int);
  void importGroundTruth();
};



class GroundTruthView
  : public IGroundTruthView
{

  Q_OBJECT

public:

  GroundTruthView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~GroundTruthView() override;

  QString imageLeft() const override;
  QString imageRight() const override;

protected slots:

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonAddPoints(bool active);
  //void onPushButtonDeletePoints(bool active);
  void onPushButtonAddPointClicked();
  void onPushButtonLockViewsToggled(bool active);

// IGroundTruthView interface

public slots:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setPointLeft(const QPointF &pt) override;
  void setPointRight(const QPointF &pt) override;
  void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) override;
  void addHomologousPoint(const QPointF &pt1, const QPointF &pt2) override;
  void setUnsavedChanges(bool value) override;
  void clickedPointLeft(const QPointF &pt) override;
  void clickedPointRight(const QPointF &pt) override;
  void setTransform(const QTransform &trf) override;
  void setBGColor(const QString &bgColor) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QDialogButtonBox *mButtonBox;
  QTreeWidget *mTreeWidget;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsViewRight;
  GraphicViewer *mGraphicsViewLeft;
  QLineEdit *mLineEditLeftX;
  QLineEdit *mLineEditLeftY;
  QLabel *mLabelDetailLeft;
  QLineEdit *mLineEditRightX;
  QLineEdit *mLineEditRightY;
  QLabel *mLabelDetailRight;
  QPushButton *mPushButtonAddPoint;
  QPushButton *mPushButtonDelete;
  QPushButton *mPushButtonLockViews;
  QAction *mImportGroundTruth;
  QAction *mAddPoints;
  //QAction *mDeletePoints;
  CrossGraphicItem *mCrossGraphicItem1;
  CrossGraphicItem *mCrossGraphicItem2;
  bool bUnsavedChanges;
  QTransform mTrf;
  bool bLockViews;
  QString mMarkerColor;
  int mMarkerSize;
  int mMarkerWidth;
  int mMarkerType;
};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_VIEW_H
