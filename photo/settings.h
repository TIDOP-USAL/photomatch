#ifndef SETTINGS_H
#define SETTINGS_H

#include "tabshortcuts.h"
#include "tabgeneral.h"

class Settings : public QDialog {

	Q_OBJECT

public:
	Settings(QDialog *parent = 0);
	~Settings();

	// The two tabs
	Shortcuts *shortcuts;
	General *general;

	// The tab widget
	QTabWidget *tabs;

protected:
	void closeEvent(QCloseEvent *);

};


#endif // SETTINGS_H
