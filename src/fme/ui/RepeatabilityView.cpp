#include "RepeatabilityView.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QTreeWidget>

namespace fme
{


RepeatabilityView::RepeatabilityView(QWidget *parent, Qt::WindowFlags f)
  : IRepeatabilityView(parent, f)
{
  init();

  connect(mTreeWidgetSessions, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(onTreeWidgetSessionsItemChanged(QTreeWidgetItem *, int)));

  connect(mButtonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help), SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

RepeatabilityView::~RepeatabilityView()
{
}

void RepeatabilityView::onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item, int column)
{
  emit selectSession(item->text(0));
}

void RepeatabilityView::addSession(const QString &session, const QString &detector, const QString &descriptor)
{
  QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions);
  item->setText(0, session);
  item->setText(1, detector);
  item->setText(2, descriptor);
  item->setCheckState(0, Qt::Unchecked);
  mTreeWidgetSessions->addTopLevelItem(item);
}

void RepeatabilityView::setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int> > &repeatability)
{
  mTreeWidget->clear();

  QString session;
  QString img1;
  QString img2;
  float repet;
  int corres;
  for (size_t i = 0; i < repeatability.size(); i++){
    std::tie(session, img1, img2, repet, corres) = repeatability[i];

    QTreeWidgetItem *treeWidgetItem = new QTreeWidgetItem();
    treeWidgetItem->setText(0, QString::number(i + 1));
    treeWidgetItem->setText(1, session);
    treeWidgetItem->setText(2, img1);
    treeWidgetItem->setText(3, img2);
    treeWidgetItem->setText(4, QString::number(repet));
    treeWidgetItem->setText(5, QString::number(corres));
    mTreeWidget->addTopLevelItem(treeWidgetItem);

  }
}

void RepeatabilityView::init()
{
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(994, 688);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  QHBoxLayout *hBoxLayout = new QHBoxLayout();

  mTreeWidgetSessions = new QTreeWidget(this);
  QTreeWidgetItem *qtreewidgetitem = new QTreeWidgetItem();
  qtreewidgetitem->setText(0, tr("Session"));
  qtreewidgetitem->setText(1, tr("Detector"));
  qtreewidgetitem->setText(2, tr("Descriptor"));
  mTreeWidgetSessions->setHeaderItem(qtreewidgetitem);
  mTreeWidgetSessions->setMaximumWidth(250);
  hBoxLayout->addWidget(mTreeWidgetSessions);

  mTreeWidget = new QTreeWidget(this);
  QTreeWidgetItem *qtreewidgetitem2 = new QTreeWidgetItem();
  qtreewidgetitem2->setText(0, "ID");
  qtreewidgetitem2->setText(1, tr("Session"));
  qtreewidgetitem2->setText(2, tr("Image 1"));
  qtreewidgetitem2->setText(3, tr("Image 2"));
  qtreewidgetitem2->setText(3, tr("Repeteability"));
  qtreewidgetitem2->setText(3, tr("Image 2"));
  mTreeWidget->setHeaderItem(qtreewidgetitem2);
  mTreeWidget->setMaximumWidth(250);
  hBoxLayout->addWidget(mTreeWidgetSessions);

  gridLayout->addLayout(hBoxLayout, 0, 0);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 1, 0);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  update();
}

void RepeatabilityView::clear()
{
  QSignalBlocker blocker1(mTreeWidgetSessions);
  QSignalBlocker blocker2(mTreeWidget);
  mTreeWidgetSessions->clear();
  mTreeWidget->clear();
}

void RepeatabilityView::update()
{
}

} // namespace fme
