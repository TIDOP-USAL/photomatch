#ifndef DEPENDENCYINFOWIDGET_H
#define DEPENDENCYINFOWIDGET_H

#include <QWidget>
#include <QLabel>

class DependencyInfoWidget : public QWidget
{
    Q_OBJECT

public:
    DependencyInfoWidget(QString license,QString Description, QString URL);
    explicit DependencyInfoWidget(QWidget *parent = 0);
    ~DependencyInfoWidget();

private:


};

#endif // DEPENDENCYINFOWIDGET_H
