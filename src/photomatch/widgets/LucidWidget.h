#ifndef PHOTOMATCH_LUCID_WIDGET_H
#define PHOTOMATCH_LUCID_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for LUCID Widgets class
 * Eric Christiansen David Kriegman Ziegler, Andrew and Serge J. Belongie.
 * Locally uniform comparison image descriptor
 */
class PHOTOMATCH_EXPORT ILucidWidget
  : public PhotoMatchWidget
{

  Q_OBJECT

public:

  ILucidWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ILucidWidget() = default;

  /*!
   * \brief kernel for descriptor construction
   * 1=3x3, 2=5x5, 3=7x7 and so forth. Default=1
   * \return
   */
  virtual int lucidKernel() const = 0;

  /*!
   * \brief kernel for blurring image prior to descriptor construction
   * 1=3x3, 2=5x5, 3=7x7 and so forth. Default=2
   * \return
   */
  virtual int blurKernel() const = 0;

signals:

  void lucidKernelChange(int);
  void blurKernelChange(int);

public slots:

  /*!
   * \brief Set the kernel for descriptor construction
   * \param[in] lucidKernel kernel for descriptor construction
   */
  virtual void setLucidKernel(int lucidKernel) = 0;

  /*!
   * \brief Set the kernel for descriptor construction
   * \param[in] blurKernel kernel for descriptor construction
   */
  virtual void setBlurKernel(int blurKernel) = 0;

};


class PHOTOMATCH_EXPORT LucidWidget
  : public ILucidWidget
{

Q_OBJECT

public:

  LucidWidget(QWidget *parent = nullptr);
  ~LucidWidget() override;

// ILucidWidget interface

public:

  int lucidKernel() const override;
  int blurKernel() const override;

public slots:

  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mLucidKernel;
  QSpinBox *mBlurKernel;
};

} // namespace photomatch

#endif // PHOTOMATCH_LUCID_WIDGET_H
