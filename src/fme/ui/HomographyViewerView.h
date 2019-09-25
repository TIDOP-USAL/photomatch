#ifndef FME_HOMOGRAPHY_VIEWER_VIEW_H
#define FME_HOMOGRAPHY_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QComboBox;

namespace fme
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

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsView;

};

} // namespace fme


#endif // FME_HOMOGRAPHY_VIEWER_VIEW_H
