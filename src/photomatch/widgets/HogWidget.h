#ifndef PHOTOMATCH_HOG_WIDGET_H
#define PHOTOMATCH_HOG_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QCheckBox;

namespace photomatch
{


/*!
 * \brief HOG (Histogram of Oriented Gradients)
 * Navneet Dalal and Bill Triggs @cite Dalal2005
 */
class PHOTOMATCH_EXPORT IHogWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IHogWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IHogWidget() = default;

  virtual QSize winSize() const = 0;
  virtual QSize blockSize() const = 0;
  virtual QSize blockStride() const = 0;
  virtual QSize cellSize() const = 0;
  virtual int nbins() const = 0;
  virtual int derivAperture() const = 0;
//  virtual double winSigma() const = 0;
//  virtual QString histogramNormType() const = 0;
//  virtual double l2HysThreshold() const = 0;
//  virtual bool gammaCorrection() const = 0;
//  virtual double freeCoef() const = 0;
//  virtual int nlevels() const = 0;
//  virtual bool signedGradient() const = 0;

signals:

  void winSizeChange(QSize);
  void blockSizeChange(QSize);
  void blockStrideChange(QSize);
  void cellSizeChange(QSize);
  void nbinsChange(int);
  void derivApertureChange(int);
//  void winSigmaChange(double);
//  void histogramNormTypeChange(QString);
//  void l2HysThresholdChange(double);
//  void gammaCorrectionChange(bool);
//  void freeCoefChange(double);
//  void nlevelsChange(int);
//  void signedGradientChange(bool);

public slots:

  virtual void setWinSize(const QSize &winSize) = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setBlockStride(const QSize &blockStride) = 0;
  virtual void setCellSize(const QSize &cellSize) = 0;
  virtual void setNbins(int nbins) = 0;
  virtual void setDerivAperture(int derivAperture) = 0;
//  virtual void setWinSigma(double winSigma) = 0;
//  virtual void setHistogramNormType(const QString &histogramNormType) = 0;
//  virtual void setL2HysThreshold(double l2HysThreshold) = 0;
//  virtual void setGammaCorrection(bool gammaCorrection) = 0;
//  virtual void setFreeCoef(double freeCoef) = 0;
//  virtual void setNlevels(int nlevels) = 0;
//  virtual void setSignedGradient(bool signedGradient) = 0;

};

class PHOTOMATCH_EXPORT HogWidget
  : public IHogWidget
{

  Q_OBJECT

public:

  HogWidget(QWidget *parent = nullptr);
  ~HogWidget() override;

protected slots:

  void onWinSizeHeightChange(int height);
  void onWinSizeWidthChange(int width);
  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);
  void onBlockStrideXChange(int blockStrideX);
  void onBlockStrideYChange(int blockStrideY);
  void onCellSizeXChange(int cellSizeX);
  void onCellSizeYChange(int cellSizeY);

// IHogWidget interface

public:

  QSize winSize() const override;
  QSize blockSize() const override;
  QSize blockStride() const override;
  QSize cellSize() const override;
  int nbins() const override;
  int derivAperture() const override;
//  double winSigma() const override;
//  QString histogramNormType() const override;
//  double l2HysThreshold() const override;
//  bool gammaCorrection() const override;
//  double freeCoef() const override;
//  int nlevels() const override;
//  bool signedGradient() const override;

public slots:

  void setWinSize(const QSize &winSize) override;
  void setBlockSize(const QSize &blockSize) override;
  void setBlockStride(const QSize &blockStride) override;
  void setCellSize(const QSize &cellSize) override;
  void setNbins(int nbins) override;
  void setDerivAperture(int derivAperture) override;
//  void setWinSigma(double winSigma) override;
//  void setHistogramNormType(const QString &histogramNormType) override;
//  void setL2HysThreshold(double l2HysThreshold) override;
//  void setGammaCorrection(bool gammaCorrection) override;
//  void setFreeCoef(double freeCoef) override;
//  void setNlevels(int nlevels) override;
//  void setSignedGradient(bool signedGradient) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mWinSizeHeight;
  QSpinBox *mWinSizeWidth;
  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;
  QSpinBox *mBlockStrideX;
  QSpinBox *mBlockStrideY;
  QSpinBox *mCellSizeX;
  QSpinBox *mCellSizeY;
  QSpinBox *mNbins;
  QSpinBox *mDerivAperture;
//  QDoubleSpinBox *mWinSigma;
//  QComboBox *mHistogramNormType;
//  QDoubleSpinBox *mL2HysThreshold;
//  QCheckBox *mGammaCorrection;
//  QDoubleSpinBox *mNlevelsmFreeCoef;
//  QDoubleSpinBox *mFreeCoef;
//  QSpinBox *mNlevels;
//  QCheckBox *mSignedGradient;

};

} // namespace photomatch

#endif // PHOTOMATCH_HOG_WIDGET_H
