#include "config.h"
#include "ui_configui.h"
#include "plugin.h"

int how_many_seconds = 5;

config::config(const QString& configLocation, QWidget* parent /* = nullptr */) : QDialog(parent),
	m_ui(new Ui::configui),
	m_settings(std::make_unique<QSettings>(configLocation + "/tempMute.ini", QSettings::IniFormat, this))
{
	m_ui->setupUi(this);

	setWindowTitle("tempMute");
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setFixedSize(window()->sizeHint());

	// Connect UI Elements.
	connect(m_ui->SaveBtn, &QPushButton::clicked, this, &config::saveSettings);
	connect(m_ui->CancelBtn, &QPushButton::clicked, this, &QWidget::close);
	connect(m_ui->SetHotkeyBtn, &QPushButton::clicked, this, &config::setHotkey);

	loadSettings();
}

config::~config() {
	m_settings->sync();
	delete m_ui;
}


void config::setConfigOption(const QString& option, const QVariant& value) {
	m_settings->setValue(option, value);
}

QVariant config::getConfigOption(const QString& option) const {
	return m_settings->value(option);
}

void config::showEvent(QShowEvent* /* e */) {
	loadSettings();
}

void config::saveSettings()
{
	setConfigOption("seconds", m_ui->seconds->value());
	how_many_seconds = m_ui->seconds->value();

	close();
}

void config::loadSettings() 
{
	m_ui->seconds->setValue(getConfigOption("seconds").toInt());
	how_many_seconds = getConfigOption("seconds").toInt();
}

void config::setHotkey(){ ts3Functions.requestHotkeyInputDialog(getPluginID(), "mute", 1, this);}
