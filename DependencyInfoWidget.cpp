#include "DependencyInfoWidget.h"
#include <QVBoxLayout>
#include <QTextEdit>

DependencyInfoWidget::DependencyInfoWidget(QWidget *parent) :
    QWidget(parent)
{
}

DependencyInfoWidget::~DependencyInfoWidget()
{
}

DependencyInfoWidget::DependencyInfoWidget(QString license, QString Description, QString URL){
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("<strong>License: </strong>"+license));

    QLabel *lbUrl = new QLabel("<a href=\""+URL+"\">"+URL+"</a>");
    lbUrl->setTextFormat(Qt::RichText);
    lbUrl->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbUrl->setOpenExternalLinks(true);

    mainLayout->addWidget(lbUrl);
    QTextEdit *txtDescription = new QTextEdit(Description);
    txtDescription->setReadOnly(true);
    txtDescription->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(txtDescription);
    setLayout(mainLayout);
}
