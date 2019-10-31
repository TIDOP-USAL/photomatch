#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H

#include "mvp.h"

class QGridLayout;
class QComboBox;
class QDialogButtonBox;
class QSpinBox;
class QCheckBox;

namespace photomatch
{

class IFeatureExtractorView
  : public IDialogView
{

  Q_OBJECT

public:

  IFeatureExtractorView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IFeatureExtractorView(){}

  virtual void setSessionName(const QString &name) = 0;
  virtual void addKeypointDetector(QWidget *keypointDetector) = 0;
  virtual void addDescriptorExtractor(QWidget *descriptorExtractor) = 0;
  virtual QString currentKeypointDetector() const = 0;
  virtual QString currentDescriptorExtractor() const = 0;

signals:

  void keypointDetectorChange(QString);
  void descriptorExtractorChange(QString);
  void run();

public slots:

  virtual void setCurrentKeypointDetector(const QString &keypointDetector) = 0;
  virtual void setCurrentDescriptorExtractor(const QString &descriptorExtractor) = 0;
  virtual void disableDescriptorExtractor(const QString &descriptorExtractor) = 0;
  virtual void enableDescriptorExtractor(const QString &descriptorExtractor) = 0;

};


class FeatureExtractorView
  : public IFeatureExtractorView
{

  Q_OBJECT

public:

  FeatureExtractorView(QWidget *parent = nullptr);
  ~FeatureExtractorView() override;

protected slots:

// IFeatureExtractorView interface

public:

  void setSessionName(const QString &name) override;
  void addKeypointDetector(QWidget *keypointDetector) override;
  void addDescriptorExtractor(QWidget *descriptorExtractor) override;
  QString currentKeypointDetector() const override;
  QString currentDescriptorExtractor() const override;

public slots:

  void setCurrentKeypointDetector(const QString &keypointDetector) override;
  void setCurrentDescriptorExtractor(const QString &descriptorExtractor) override;
  void disableDescriptorExtractor(const QString &descriptorExtractor) override;
  void enableDescriptorExtractor(const QString &descriptorExtractor) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QGridLayout *mGridLayoutKeypointDetector;
  QGridLayout *mGridLayoutDescriptorExtractor;
  QComboBox *mComboBoxKeypointDetector;
  QComboBox *mComboBoxDescriptorExtractor;
  QDialogButtonBox *mButtonBox;
  QString mCurrentKeypointDetector;
  QString mCurrentDescriptorExtractor;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H
