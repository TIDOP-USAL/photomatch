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


#include "MultiViewView.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QGridLayout>
#include <QApplication>
#include <QLabel>
#include <QImage>
#include <mutex>
#include <QImageReader>
#include <QFileInfo>
#include <QPainter>


namespace photomatch
{

MultiviewMatchingAssessmentViewImp::MultiviewMatchingAssessmentViewImp(QWidget *parent, Qt::WindowFlags f)
  : MultiviewMatchingAssessmentView(parent, f),
    mLabelIds(new QLabel(this)),
    mListWidgetIds(new QListWidget(this)),
    mListWidgetImages(new QListWidget(this)),
    mButtonBox(new QDialogButtonBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

MultiviewMatchingAssessmentViewImp::~MultiviewMatchingAssessmentViewImp()
{

}

void MultiviewMatchingAssessmentViewImp::onListWidgetIdsCurrentRowChanged(int row)
{
  QListWidgetItem *item = mListWidgetIds->item(row);
  emit idChange(item->data(Qt::UserRole).toInt());
}

void MultiviewMatchingAssessmentViewImp::initUI()
{

  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(750, 450);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(mLabelIds, 0, 0, 1, 1);

  mListWidgetIds->setMaximumSize(QSize(250, 16777215));
  layout->addWidget(mListWidgetIds, 1, 0, 1, 1);

  mListWidgetImages->setSelectionMode(QListWidget::ExtendedSelection);
  mListWidgetImages->setIconSize(QSize(400, 400));
  mListWidgetImages->setViewMode(QListWidget::IconMode);
  mListWidgetImages->setResizeMode(QListView::Adjust);

  layout->addWidget(mListWidgetImages, 1, 1, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Help);
  layout->addWidget(mButtonBox, 2, 0, 1, 3);

  retranslate();

  update();
}

void MultiviewMatchingAssessmentViewImp::initSignalAndSlots()
{
  connect(mListWidgetIds, SIGNAL(currentRowChanged(int)), this, SLOT(onListWidgetIdsCurrentRowChanged(int)));

  connect(mButtonBox->button(QDialogButtonBox::Close),  SIGNAL(clicked(bool)), this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)), this, SIGNAL(help()));
}

void MultiviewMatchingAssessmentViewImp::clear()
{

  const QSignalBlocker blockerListWidgetIds(mListWidgetIds);
  const QSignalBlocker blockerListWidgetImagess(mListWidgetImages);

  mListWidgetIds->clear();
  mListWidgetImages->clear();

  this->setWindowTitle(QApplication::translate("MultiViewView", "Multiview Matching Assessment", nullptr));

  update();
}

void MultiviewMatchingAssessmentViewImp::update()
{
}

void MultiviewMatchingAssessmentViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("MultiViewView", "Multiview Matching Assessment", nullptr));
  mLabelIds->setText(QApplication::translate("MultiViewView", "Pass Points ID", nullptr));
  mButtonBox->button(QDialogButtonBox::Close)->setText(QApplication::translate("MultiViewView", "Close", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("MultiViewView", "Help", nullptr));

}

void MultiviewMatchingAssessmentViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Multi-view Pass Points ").append(name));
}

void MultiviewMatchingAssessmentViewImp::setPassPointIds(const std::vector<size_t> &id)
{
  const QSignalBlocker blockerListWidgetIds(mListWidgetIds);

  mListWidgetIds->clear();
  for (size_t i = 0; i < id.size(); i++){
    mListWidgetIds->addItem(QString::number(id[i]));
  }
}

void MultiviewMatchingAssessmentViewImp::addPassPointIds(size_t id)
{
  const QSignalBlocker blockerListWidgetIds(mListWidgetIds);

  mListWidgetIds->addItem(QString::number(id));
}

void MultiviewMatchingAssessmentViewImp::addPassPointIdsAndNImages(size_t id, size_t size)
{
  const QSignalBlocker blockerListWidgetIds(mListWidgetIds);

  QListWidgetItem *item = new QListWidgetItem(QString::number(id).
                                              append(" - [").
                                              append(QString::number(size)).
                                              append(" images]"));
  item->setData(Qt::UserRole, id);
  mListWidgetIds->addItem(item);
}

void MultiviewMatchingAssessmentViewImp::setImages(const std::vector<std::pair<QString, QPointF> > &images)
{
  mListWidgetImages->clear();

  for (auto &pair : images) {
    QImageReader reader(pair.first);
    QRect rect(static_cast<int>(pair.second.x()) - 200, static_cast<int>(pair.second.y()) - 200, 400, 400);
    reader.setClipRect(rect);
    QImage image = reader.read();
    QPixmap pixmap = QPixmap::fromImage(image);
    QPainter p(&pixmap);
    p.setPen(Qt::red);
    p.drawLine(150, 200, 250, 200);
    p.drawLine(200, 150, 200, 250);
    p.end();
    QIcon icon(pixmap);
    QFileInfo fileInfo(pair.first);
    QListWidgetItem *item = new QListWidgetItem(icon, fileInfo.fileName());
    item->setToolTip(fileInfo.absoluteFilePath());
    mListWidgetImages->addItem(item);
  }

}

} // namespace photomatch


