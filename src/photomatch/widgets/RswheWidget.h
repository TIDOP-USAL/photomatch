#ifndef PHOTOMATCH_RSWHE_WIDGET_H
#define PHOTOMATCH_RSWHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QRadioButton;

namespace photomatch
{

class IRswheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  enum class HistogramCut{
    by_mean,
    by_median
  };

public:

  IRswheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IRswheWidget() = default;

  virtual int histogramDivisions() const = 0;
  virtual HistogramCut histogramCut() const = 0;

signals:

  void histogramDivisionsChange(int);
  void histogramCutChange(int);

public slots:

  virtual void setHistogramDivisions(int histogramDivisions) = 0;
  virtual void setHistogramCut(HistogramCut histogramCut) = 0;

};

class RswheWidget
  : public IRswheWidget
{
  Q_OBJECT

public:

  RswheWidget(QWidget *parent = nullptr);
  ~RswheWidget() override;

protected slots:

  void onHistogramCutByMean();
  void onHistogramCutByMedian();

// IRswheWidget interface

public:

  int histogramDivisions() const override;
  HistogramCut histogramCut() const override;

public slots:

  void setHistogramDivisions(int histogramDivisions) override;
  void setHistogramCut(HistogramCut histogramCut) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  HistogramCut mHistogramCut;
  QSpinBox *mHistogramDivisions;
  QRadioButton *mHistogramCutByMean;
  QRadioButton *mHistogramCutByMedian;
};

} // namespace photomatch

Q_DECLARE_METATYPE(photomatch::IRswheWidget::HistogramCut)

#endif // PHOTOMATCH_RSWHE_WIDGET_H
