#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QtDebug>
#include <QEvent>

// A custom MenuItem used for the Menu
class MenuItem : public QLabel {

	Q_OBJECT
public:
	MenuItem(QString txt = "", QString icon = "", QString setData = "", int closeMe = 1, bool enabled = true);
	~MenuItem();

	// Setting an icon at the beginning of the item
	void setIcon(QString);

	// The look of the label when hovered/normal
	QString ssNormal;
	QString ssHover;

	// The data connected with this label
	QString data;

	// Closing setting for this label
	int close;

protected:
	bool event(QEvent *e);

signals:
	void clicked();

};

#endif // MENU_H
