#ifndef FME_MATCH_VIEWER_VIEW_H
#define FME_MATCH_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QTreeWidget;
class QComboBox;
class QTreeWidgetItem;

namespace fme
{

class GraphicViewer;

class IMatchViewerView
  : public IDialogView
{
  Q_OBJECT

public:

  explicit IMatchViewerView(QWidget *parent = nullptr,
                            Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f) {}

  virtual ~IMatchViewerView() = default;

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

  virtual void setMatches(const std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> &matches) = 0;
  //virtual void deleteMatch(int id) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void loadMatches(QString, QString);
  void deleteMatch(QString, QString, int, int);
};

class MatchViewerView
  : public IMatchViewerView
{

  Q_OBJECT

public:

  MatchViewerView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~MatchViewerView() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetMatchesItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetMatchesItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonDeleteMatchClicked();

// IMatchViewerView interface

public:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setMatches(const std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> &matches) override;
  //void deleteMatch(int id) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QDialogButtonBox *mButtonBox;
  QTreeWidget *mTreeWidgetMatches;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsViewRight;
  GraphicViewer *mGraphicsViewLeft;
  QPushButton *mPushButtonDeleteMatch;
  //QPushButton *mPushButtonSaveMatches;
  bool bUnsavedChanges;

};

} // namespace fme

#endif // FME_MATCH_VIEWER_VIEW_H
