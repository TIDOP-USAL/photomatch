#ifndef FME_BRIEF_WIDGET_H
#define FME_BRIEF_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QCheckBox;
class QComboBox;

namespace fme
{

/*!
 * \brief Interface for BRIEF Widgets
 *
 * Michael Calonder, Vincent Lepetit, Christoph Strecha, and Pascal Fua.
 * Brief: Binary robust independent elementary features. In Computer
 * Vision–ECCV 2010, pages 778–792. Springer, 2010
 * https://www.cs.ubc.ca/~lowe/525/papers/calonder_eccv10.pdf
 */
class FME_EXPORT IBriefWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IBriefWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IBriefWidget() = default;

  /*!
   * \brief Legth of the descriptor in bytes
   * Valid values are: 16, 32 (default) or 64
   * \return Legth of the descriptor
   */
  virtual QString bytes() const = 0;

  /*!
   * \brief useOrientation
   * \return
   */
  virtual bool useOrientation() const = 0;

signals:

  void bytesChange(QString);
  void useOrientationChange(bool);

public slots:

  /*!
   * \brief Set the legth of the descriptor in bytes
   * \param[in] bytes
   */
  virtual void setBytes(const QString &bytes) = 0;

  /*!
   * \brief setUseOrientation
   * \param[in] useOrientation
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

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

// FmeWidget interface

public slots:

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
