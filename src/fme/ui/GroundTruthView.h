#ifndef FME_GROUND_TRUTH_VIEW_H
#define FME_GROUND_TRUTH_VIEW_H

#include "mvp.h"

class QComboBox;
class QTreeWidgetItem;
class QTreeWidget;
class QDialogButtonBox;
class QLineEdit;
class QLabel;


namespace fme
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

  virtual void addHomologousPoints(const QPointF &pt1, const QPointF &pt2) = 0;


signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void addPoint(QString, QPointF, QString,  QPointF);
  void markedLeftPoint(QPointF);
  void markedRightPoint(QPointF);
};



class GroundTruthView
  : public IGroundTruthView
{

  Q_OBJECT

public:

  GroundTruthView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~GroundTruthView() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonAddPoints(bool active);
  void onPushButtonDeletePoints(bool active);
  void onPushButtonAddPointClicked();

// IGroundTruthView interface

public slots:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setPointLeft(const QPointF &pt) override;
  void setPointRight(const QPointF &pt) override;
  void addHomologousPoints(const QPointF &pt1, const QPointF &pt2) override;

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
  QAction *mAddPoints;
  QAction *mDeletePoints;
  CrossGraphicItem *mCrossGraphicItem1;
  CrossGraphicItem *mCrossGraphicItem2;
};

} // namespace fme

#endif // FME_GROUND_TRUTH_VIEW_H
