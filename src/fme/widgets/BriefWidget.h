#ifndef FME_BRIEF_WIDGET_H
#define FME_BRIEF_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QCheckBox;
class QComboBox;

namespace fme
{

/*!
 * \brief Interface for BriefWidget class
 */
class FME_EXPORT IBriefWidget
  : public QWidget
{
  Q_OBJECT

public:

  IBriefWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IBriefWidget() = default;

  virtual QString bytes() const = 0;
  virtual bool useOrientation() const = 0;

signals:

  void bytesChange(QString);
  void useOrientationChange(bool);

public slots:

  virtual void setBytes(const QString &bytes) = 0;
  virtual void setUseOrientation(bool useOrientation) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

class FME_EXPORT BriefWidget
  : public IBriefWidget
{
  Q_OBJECT

public:

  BriefWidget(QWidget *parent = nullptr);
  ~BriefWidget() override;

// IBriefWidget interface

public:

  QString bytes() const override;
  bool useOrientation() const override;

public slots:

  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mBytes;
  QCheckBox *mUseOrientation;

};

} // namespace fme

#endif // FME_BRIEF_WIDGET_H
