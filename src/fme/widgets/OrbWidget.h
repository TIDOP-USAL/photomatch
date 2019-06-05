#ifndef FME_ORB_WIDGET_H
#define FME_ORB_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

namespace fme
{

/*!
 * \brief Interface ORB Widget
 */
class FME_EXPORT IOrbWidget
  : public QWidget
{
  Q_OBJECT

public:

  IOrbWidget(QWidget *parent = nullptr)
    : QWidget(parent){}
  virtual ~IOrbWidget() = default;

  virtual int featuresNumber() const = 0;
  virtual double scaleFactor() const = 0;
  virtual int levelsNumber() const = 0;
  virtual int edgeThreshold() const = 0;
  virtual int wta_k() const = 0;
  virtual QString scoreType() const = 0;
  virtual int patchSize() const = 0;
  virtual int fastThreshold() const = 0;

signals:

  void featuresNumberChange(int);
  void scaleFactorChange(double);
  void levelsNumberChange(int);
  void edgeThresholdChange(int);
  void wta_kChange(int);
  void scoreTypeChange(QString);
  void patchSizeChange(int);
  void fastThresholdChange(int);

public slots:

  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setFeaturesNumber(int featuresNumber) = 0;
  virtual void setLevelsNumber(int levelsNumber) = 0;
  virtual void setEdgeThreshold(int edgeThreshold) = 0;
  virtual void setWTA_K(int WTA_K) = 0;
  virtual void setScoreType(const QString &scoreType) = 0;
  virtual void setPatchSize(int patchSize) = 0;
  virtual void setFastThreshold(int fastThreshold) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class FME_EXPORT OrbWidget
  : public IOrbWidget
{
  Q_OBJECT

public:

  explicit OrbWidget(QWidget *parent = nullptr);
  ~OrbWidget() override;

// IOrbWidget interface

public:

  int featuresNumber() const override;
  double scaleFactor() const override;
  int levelsNumber() const override;
  int edgeThreshold() const override;
  int wta_k() const override;
  QString scoreType() const override;
  int patchSize() const override;
  int fastThreshold() const override;

public slots:

  void setScaleFactor(double scaleFactor) override;
  void setFeaturesNumber(int featuresNumber) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mFeaturesNumber;
  QDoubleSpinBox *mScaleFactor;
  QSpinBox *mLevelsNumber;
  QSpinBox *mEdgeThreshold;
  //QSpinBox *mFirstLevel;
  QSpinBox *mWTA_K;
  QComboBox *mScoreType;
  QSpinBox *mPatchSize;
  QSpinBox *mFastThreshold;

};

} // namespace fme

#endif // FME_ORB_WIDGET_H
