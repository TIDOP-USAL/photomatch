#ifndef FME_RSWHE_WIDGET_H
#define FME_RSWHE_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QSpinBox;
class QRadioButton;

namespace fme
{

class IRswheWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  enum class HistogramCut{
    by_mean,
    by_median
  };

public:

  IRswheWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IRswheWidget() = default;

  virtual int histogramDivisions() const = 0;
  virtual HistogramCut histogramCut() const = 0;

signals:

  void histogramDivisionsChange(int);
  void histogramCutChange(HistogramCut);

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

// FmeWidget interface

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

} // namespace fme

Q_DECLARE_METATYPE(fme::IRswheWidget::HistogramCut)

#endif // FME_RSWHE_WIDGET_H
