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

  /*!
   * \brief Current left image
   * \return
   */
  virtual QString leftImage() const = 0;

  /*!
   * \brief Current right image
   * \return
   */
  virtual QString rightImage() const = 0;

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

  /*!
   * \brief Select left point
   * \param[in] pt Selected point left
   * \param[in] newPoint Point for added
   */
  virtual void setSelectLeftPoint(const QPointF &pt, bool newPoint = false) = 0;

  /*!
   * \brief Select right point
   * \param[in] pt Selected point right
   * \param[in] newPoint Point for added
   */
  virtual void setSelectedRightPoint(const QPointF &pt, bool newPoint = false) = 0;

  /*!
   * \brief Select homologous points
   * \param[in] ptLeft Left point
   * \param[in] ptRight Right point
   */
  virtual void setSelectedHomologous(const QPointF &ptLeft, const QPointF &ptRight) = 0;

  /*!
   * \brief Unselect homologous point
   */
  virtual void unselectHomologous() = 0;

  /*!
   * \brief Set pairs of homologous points
   * \param[in] points Pairs of homologous points
   */
  virtual void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) = 0;

  /*!
   * \brief Add homologous points to list
   * \param[in] pt1 Left point
   * \param[in] pt2 Right point
   */
  virtual void addHomologous(const QPointF &pt1, const QPointF &pt2) = 0;

  /*!
   * \brief Delete Homologous points
   * \param[in ] pointId Identifier of the homologous points
   */
  virtual void deleteHomologous(int pointId) = 0;

  virtual void setHomologousDistance(int pointId, double distance) = 0;

  virtual void setUnsavedChanges(bool value) = 0;
  virtual void enableLockView(bool enable) = 0;

  virtual void clickedPointLeft(const QPointF &pt) = 0;
  virtual void clickedPointRight(const QPointF &pt) = 0;

  //virtual void setTransform(const QTransform &trf) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) = 0;
  virtual void setSelectedMarkerStyle(const QString &color, int width) = 0;
  virtual void setCenterLeftViewer(const QPointF &pt, bool zoom11 = true) = 0;
  virtual void setCenterRightViewer(const QPointF &pt, bool zoom11 = true) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void loadHomologousPoints(QString, QString);
  void addHomologousPoints(QString, QPointF, QString,  QPointF);
  void deleteHomologous(QString, QString, int);
  void selectHomologous(QString, QString, int);
  void importGroundTruth();
  void saveGroundTruth();
  void leftPointClicked(QString, QString, QPointF);
  void rightPointClicked(QString, QString, QPointF);
  void findLeftPoint(QString, QString, QPointF);
  void findRightPoint(QString, QString, QPointF);
//  void markedLeftPoint(QPointF);
//  void markedRightPoint(QPointF);

};



class GroundTruthView
  : public IGroundTruthView
{

  Q_OBJECT

public:

  GroundTruthView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~GroundTruthView() override;

  QString leftImage() const override;
  QString rightImage() const override;

protected slots:

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  //void onTreeWidgetItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonAddPoints(bool active);
  //void onPushButtonDeletePoints(bool active);
  void onPushButtonAddPointClicked();
  void onPushButtonLockViewsToggled(bool active);
  void onPushButtonDeleteClicked();
  void onAccept();

private:

  void removeHomologousPointInGraphicsViews(int id);
  void removeHomologousPointsInGraphicsViews();

// IGroundTruthView interface

public slots:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setSelectLeftPoint(const QPointF &pt, bool newPoint = false) override;
  void setSelectedRightPoint(const QPointF &pt, bool newPoint = false) override;
  void setSelectedHomologous(const QPointF &ptLeft, const QPointF &ptRight) override;
  void unselectHomologous() override;
  void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) override;
  void addHomologous(const QPointF &pt1, const QPointF &pt2) override;
  void deleteHomologous(int pointId) override;
  void setHomologousDistance(int pointId, double distance) override;
  void setUnsavedChanges(bool value) override;
  void enableLockView(bool enable) override;
  void clickedPointLeft(const QPointF &pt) override;
  void clickedPointRight(const QPointF &pt) override;
  //void setTransform(const QTransform &trf) override;
  void setBGColor(const QString &bgColor) override;
  void setSelectedMarkerStyle(const QString &color, int width) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;
  void setCenterLeftViewer(const QPointF &pt, bool zoom11 = true) override;
  void setCenterRightViewer(const QPointF &pt, bool zoom11 = true) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// QWidget interface

protected:

  void closeEvent(QCloseEvent *event) override;

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
  QAction *mSaveGroundTruth;
  QAction *mAddPoints;
  //QAction *mDeletePoints;
  CrossGraphicItem *mCrossGraphicItem1;
  CrossGraphicItem *mCrossGraphicItem2;
  bool bUnsavedChanges;
  bool bEnableLockViews;
  QTransform mTrf;
  bool bLockViews;
  QString mMarkerColor;
  int mMarkerSize;
  int mMarkerWidth;
  int mMarkerType;
  int mPointsCounter;
  QString mSelectedMarkerColor;
  int mSelectedMarkerWidth;


};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_VIEW_H
