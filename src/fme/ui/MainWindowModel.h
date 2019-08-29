#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include "mvp.h"

namespace fme
{

class MainWindowModel
  : public IModel
{
  Q_OBJECT

public:

  explicit MainWindowModel();

  /*!
   * \brief Devuelve la ruta por defecto donde se situan los proyectos
   * \return
   */
  QString defaultPath() const;

  std::list<std::pair<QString, QString>> exif(const QString &image) const;

signals:

public slots:


// IModel interface

private:

  void init() override;

protected:

  QString mPrjDefaultPath;

};

} // namespace fme

#endif // MAINWINDOWMODEL_H
