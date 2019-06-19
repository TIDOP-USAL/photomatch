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
   * \brief Comprueba si hay cambios sin guardar en el proyecto
   * \return
   */
  bool checkUnsavedChanges() const;

signals:

public slots:


  // IModel interface
private:
  void init() override;
};

} // namespace fme

#endif // MAINWINDOWMODEL_H
