#ifndef TABGENERAL_H
#define TABGENERAL_H

#include <QWidget>

#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

#include <QCheckBox>
#include <QComboBox>

#include <QSlider>
#include <QSpinBox>

#include <QFile>
#include <QDir>

#include <QMessageBox>
#include <QTextStream>

#include <QtDebug>

class General : public QWidget {

	Q_OBJECT
public:
	General(QWidget *parent = 0);
	~General();

	// The central scroll area
	QScrollArea *centralScroll;

	// ComboBox for choosing language
	QComboBox *trans;

	// CheckBox for enabling composite
	QCheckBox *composite;

	// Slider for adjusting the menu sensitivity
	QSlider *menu;

	// Changing the thumbnail size
	QSlider *thumbSizeSlider;
	QSpinBox *thumbSizeSpin;

	// Disabling the thumbnail cache
	QCheckBox *thumbCache;

	// Holding the current version (set from mainwindow.cpp)
	QString version;

public slots:
	// Load ans save settings
	void loadSettings();
	void saveSettings();

};

#endif // TABGENERAL_H
