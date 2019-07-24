#ifndef FME_PREPROCESS_VIEW_H
#define FME_PREPROCESS_VIEW_H

#include "mvp.h"

class QGridLayout;
class QComboBox;
class QDialogButtonBox;
class QSpinBox;
class QCheckBox;

namespace fme
{

class IPreprocessView
  : public IDialogView
{

  Q_OBJECT

public:

  IPreprocessView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IPreprocessView(){}

  virtual void addPreprocess(QWidget *detector) = 0;
  virtual QString currentPreprocess() const = 0;
  virtual void setCurrentPreprocess(const QString &preprocess) = 0;
  virtual int maxImageSize() = 0;
  virtual void setMaxImageSize(int imageSize) = 0;
  virtual void setFullImageSize(bool fullImageSize) = 0;
  virtual bool fullImageSize() = 0;

signals:

  void preprocessChange(QString);
  void run();

};


class PreprocessView
  : public IPreprocessView
{

  Q_OBJECT

public:

  PreprocessView(QWidget *parent = nullptr);
  ~PreprocessView() override;

protected slots:

// IPreprocessView interface

public:

  void addPreprocess(QWidget *preprocess) override;
  QString currentPreprocess() const override;
  void setCurrentPreprocess(const QString &preprocess) override;
  int maxImageSize() override;
  void setMaxImageSize(int imageSize) override;
  void setFullImageSize(bool fullImageSize) override;
  bool fullImageSize() override;

protected slots:

  void onCheckBoxFullImageChange();

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QGridLayout *mGridLayoutPreprocess;
  QComboBox *mComboBoxPreprocess;
  QCheckBox *mCheckBoxFullImage;
  QSpinBox *mSpinBoxMaxImageSize;
  QDialogButtonBox *mButtonBox;
  QString mCurrentPreprocess;
};

} // namespace fme

#endif // FME_PREPROCESS_VIEW_H
