#ifndef FME_LUCID_WIDGET_H
#define FME_LUCID_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for LUCID Widgets class
 * Eric Christiansen David Kriegman Ziegler, Andrew and Serge J. Belongie.
 * Locally uniform comparison image descriptor
 */
class FME_EXPORT ILucidWidget
  : public FmeWidget
{

  Q_OBJECT

public:

  ILucidWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
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


class FME_EXPORT LucidWidget
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

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mLucidKernel;
  QSpinBox *mBlurKernel;
};

} // namespace fme

#endif // FME_LUCID_WIDGET_H
