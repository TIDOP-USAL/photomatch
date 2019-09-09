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

  explicit IMatchViewerView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IMatchViewerView() = default;

  /*!
   * \brief Establece la imagen izquierda
   * \param[in] leftImage Image izquierda
   */
  virtual void setLeftImage(const QString &leftImage) = 0;

  /*!
   * \brief Establece la imagen derecha
   * \param[in] rightImage imagen derecha
   */
  virtual void setRightImage(const QString &rightImage) = 0;

  /*!
   * \brief Establece el listado de imagenes para el selector de imagen izquierda
   * \param[in] leftImageList Listado de imagenes
   */
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) = 0;

  /*!
   * \brief Establece el listado de imagenes para el selector de imagen derecha
   * \param[in] leftImageList Listado de imagenes
   */
  virtual void setRightImageList(const std::vector<QString> &rightImageList) = 0;

  virtual void setMatches(const std::vector<std::pair<QPointF, QPointF>> &matches) = 0;

signals:

  /*!
   * \brief Señal que se emite al cambiar la imagen izquierda
   */
  void leftImageChange(QString);

  /*!
   * \brief Señal que se emite al cambiar la imagen derecha
   */
  void rightImageChange(QString);

  void loadMatches(QString, QString);

};

class MatchViewerView
  : public IMatchViewerView
{

  Q_OBJECT

public:

  MatchViewerView(QWidget *parent = nullptr);
  ~MatchViewerView() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetMatchesItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetMatchesItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();

// IMatchViewerView interface

public:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setMatches(const std::vector<std::pair<QPointF, QPointF> > &matches) override;

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

};

} // namespace fme

#endif // FME_MATCH_VIEWER_VIEW_H
