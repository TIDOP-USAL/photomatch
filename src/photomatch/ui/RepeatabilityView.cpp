/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "RepeatabilityView.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QTreeWidget>

namespace photomatch
{


RepeatabilityViewImp::RepeatabilityViewImp(QWidget *parent, Qt::WindowFlags f)
  : RepeatabilityView(parent, f)
{
  this->initUI();
  this->initSignalAndSlots();
}

RepeatabilityViewImp::~RepeatabilityViewImp()
{
}

void RepeatabilityViewImp::onTreeWidgetSessionsItemSelectionChanged()
{
  emit selectSession(mTreeWidgetSessions->currentItem()->text(0));
}

void RepeatabilityViewImp::addSession(const QString &session, const QString &detector, const QString &descriptor)
{
  QSignalBlocker blocker1(mTreeWidgetSessions);

  QTreeWidgetItem *item = new QTreeWidgetItem(mTreeWidgetSessions);
  item->setText(0, session);
  item->setText(1, detector);
  item->setText(2, descriptor);
  mTreeWidgetSessions->addTopLevelItem(item);
}

void RepeatabilityViewImp::setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int> > &repeatability)
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

void RepeatabilityViewImp::initUI()
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
  qtreewidgetitem2->setText(4, tr("Repeteability"));
  qtreewidgetitem2->setText(5, tr("Image 2"));
  mTreeWidget->setHeaderItem(qtreewidgetitem2);
  hBoxLayout->addWidget(mTreeWidget);

  gridLayout->addLayout(hBoxLayout, 0, 0);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 1, 0);

  mButtonBox->button(QDialogButtonBox::Close)->setText(tr("Close"));
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");

  update();
}

void RepeatabilityViewImp::initSignalAndSlots()
{
  connect(mTreeWidgetSessions, SIGNAL(itemSelectionChanged()), this, SLOT(onTreeWidgetSessionsItemSelectionChanged()));

  connect(mButtonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help), SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

void RepeatabilityViewImp::clear()
{
  QSignalBlocker blocker1(mTreeWidgetSessions);
  QSignalBlocker blocker2(mTreeWidget);
  mTreeWidgetSessions->clear();
  mTreeWidget->clear();
}

void RepeatabilityViewImp::update()
{
}

void RepeatabilityViewImp::retranslate()
{

}

} // namespace photomatch
