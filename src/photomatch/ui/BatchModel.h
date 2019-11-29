#ifndef PHOTOMATCH_BATCH_MODEL_H
#define PHOTOMATCH_BATCH_MODEL_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IBatchModel
  : public IModel
{

  Q_OBJECT

public:

  IBatchModel() {}
  virtual ~IBatchModel() override = default;

//  virtual QStringList sessions() const = 0;
//  virtual QString sessionName() const = 0;

//public slots:

//  virtual void setSessionName(const QString &session) = 0;

};


class BatchModel
  : public IBatchModel
{

  Q_OBJECT

public:

  BatchModel(/*IProjectModel *mProjectModel*/);
  ~BatchModel() override;

// IModel interface

private:

  void init() override;

// IBatchModel interface

//public:

//  QStringList sessions() const override;
//  QString sessionName() const override;

//public slots:

//  void setSessionName(const QString &session) override;

//protected:

//  //IProjectModel *mProjectModel;
//  QString mSession;

};

} // namespace photomatch


#endif // PHOTOMATCH_BATCH_MODEL_H
