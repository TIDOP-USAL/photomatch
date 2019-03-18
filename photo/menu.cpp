#include "menu.h"

// A custom QLabel used for the menu
MenuItem::MenuItem(QString txt, QString icon, QString setData, int closeMe, bool clickable) : QLabel(txt) {

	// Enable mouse tracking for hover effect
	this->setMouseTracking(true);

	ssNormal = "QLabel { background: transparent; border: none; color: grey; } QLabel:disabled { color: white; font-weight: bold }";
	ssHover = "QLabel { background: transparent; border: none; color: white; } QLabel:disabled { color: white; font-weight: bold; }";

	// Set the default stylesheet
	MenuItem::setStyleSheet(ssNormal);

	// Set the transmitted data
	data = setData.trimmed();
	close = closeMe;
	this->setEnabled(clickable);
	setIcon(icon);

}

// Get all the needed events and connect them to the slots
bool MenuItem::event(QEvent *e) {

	if(e->type() == QEvent::MouseMove)
		MenuItem::setStyleSheet(ssHover);
	else if(e->type() == QEvent::Leave)
		MenuItem::setStyleSheet(ssNormal);

	if(e->type() == QEvent::MouseButtonPress)
		emit clicked();

	QList<QEvent::Type> types;
	types << QEvent::MouseButtonDblClick;
	types << QEvent::MouseButtonPress;
	types << QEvent::MouseButtonRelease;

	if(!types.contains(e->type()))
		QLabel::event(e);

	return e->isAccepted();

}

// Add an icon to the front of the string
void MenuItem::setIcon(QString icon) {

	if(icon != "")
		this->setText("<img height=\"13\" src=\"" + icon + "\">&nbsp;" + this->text());

}

MenuItem::~MenuItem() { }
