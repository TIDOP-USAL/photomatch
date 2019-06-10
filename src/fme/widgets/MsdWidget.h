#ifndef FME_MSD_WIDGET_H
#define FME_MSD_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace fme
{

class FME_EXPORT IMsdWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IMsdWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IMsdWidget() = default;

  virtual double thresholdSaliency() const = 0;
  virtual int pathRadius() const = 0;
  virtual int knn() const = 0;
  virtual int areaRadius() const = 0;
  virtual double scaleFactor() const = 0;
  virtual int NMSRadius() const = 0;
  virtual int nScales() const = 0;
  virtual int NMSScaleR() const = 0;
  virtual bool computeOrientations() const = 0;
  virtual bool affineMSD() const = 0;
  virtual int tilts() const = 0;

signals:

  void thresholdSaliencyChange(double);
  void pathRadiusChange(int);
  void KNNChange(int);
  void areaRadiusChange(int);
  void scaleFactorChange(double);
  void NMSRadiusChange(int);
  void nScalesChange(int);
  void NMSScaleRChange(int);
  void computeOrientationsChange(bool);
  void affineMSDChange(bool);
  void tiltsChange(int);

public slots:

  virtual void setThresholdSaliency(double thresholdSaliency) = 0;
  virtual void setPathRadius(int pathRadius) = 0;
  virtual void setKNN(int knn) = 0;
  virtual void setAreaRadius(int areaRadius) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setNMSRadius(int NMSRadius) = 0;
  virtual void setNScales(int nScales) = 0;
  virtual void setNMSScaleR(int NMSScaleR) = 0;
  virtual void setComputeOrientations(bool computeOrientations) = 0;
  virtual void setAffineMSD(bool affineMSD) = 0;
  virtual void setTilts(int tilts) = 0;

};

class FME_EXPORT MsdWidget
  : public IMsdWidget
{
  Q_OBJECT

public:

  MsdWidget(QWidget *parent = nullptr);
  ~MsdWidget() override;


// IMsdWidget interface

public:

  double thresholdSaliency() const override;
  int pathRadius() const override;
  int knn() const override;
  int areaRadius() const override;
  double scaleFactor() const override;
  int NMSRadius() const override;
  int nScales() const override;
  int NMSScaleR() const override;
  bool computeOrientations() const override;
  bool affineMSD() const override;
  int tilts() const override;

public slots:

  void setThresholdSaliency(double thresholdSaliency) override;
  void setPathRadius(int pathRadius) override;
  void setKNN(int knn) override;
  void setAreaRadius(int areaRadius) override;
  void setScaleFactor(double scaleFactor) override;
  void setNMSRadius(int NMSRadius) override;
  void setNScales(int nScales) override;
  void setNMSScaleR(int NMSScaleR) override;
  void setComputeOrientations(bool computeOrientations) override;
  void setAffineMSD(bool affineMSD) override;
  void setTilts(int tilts) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mThresholdSaliency;
  QSpinBox *mPathRadius;
  QSpinBox *mKNN;
  QSpinBox *mAreaRadius;
  QDoubleSpinBox *mScaleFactor;
  QSpinBox *mNMSRadius;
  QSpinBox *mNScales;
  QSpinBox *mNMSScaleR;
  QCheckBox *mComputeOrientations;
  QCheckBox *mAffineMSD;
  QSpinBox *mTilts;

};

} // namespace fme

#endif // FME_MSD_WIDGET_H
