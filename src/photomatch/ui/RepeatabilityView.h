#ifndef PHOTOMATCH_REPEATABILITY_VIEW_H
#define PHOTOMATCH_REPEATABILITY_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QTreeWidget;
class QTreeWidgetItem;

namespace photomatch
{

class IRepeatabilityView
  : public IDialogView
{

  Q_OBJECT

public:

  IRepeatabilityView(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f)
  {}

  virtual ~IRepeatabilityView() override = default;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) = 0;

  /*!
   * \brief setRepeteability
   * \param repeteability
   */
  virtual void setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int>> &repeatability) = 0;

signals:

  void selectSession(QString);

};

class RepeatabilityView
  : public IRepeatabilityView
{

  Q_OBJECT

public:

  RepeatabilityView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~RepeatabilityView() override;

private slots:

  void onTreeWidgetSessionsItemSelectionChanged();

// IRepeatabilityView interface

  void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  void setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int>> &repeatability) override;

// IDialogView interface

private:

  virtual void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QDialogButtonBox *mButtonBox;
  QTreeWidget *mTreeWidgetSessions;
  QTreeWidget *mTreeWidget;
};

} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_VIEW_H
