#ifndef FME_NEW_PROJECT_VIEW_H
#define FME_NEW_PROJECT_VIEW_H

#include "NewProjectInterfaces.h"

class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;
class QPushButton;

namespace fme
{

class NewProjectView 
  : public INewProjectView
{
  Q_OBJECT

public:

  explicit NewProjectView(QWidget *parent = nullptr);
  ~NewProjectView() override;

// INewProjectView interface

public:

  QString projectName() const override;
  QString projectPath() const override;
  void setProjectPath(const QString &path) override;
  QString projectDescription() const override;
  bool createProjectFolder() const override;

protected slots:

  void onClickButtonSelectPath() override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QLineEdit *mLineEditProjectName;
  QLineEdit *mLineEditProjectPath;
  QLineEdit *mLineEditProjectFile;
  QTextEdit *mTextEditDescription;
  QCheckBox *mCheckBoxProjectFolder;
  QPushButton *mPushButtonProjectPath;
  QDialogButtonBox *mButtonBox;

};

} // namespace fme


#endif // FME_NEW_PROJECT_VIEW_H
