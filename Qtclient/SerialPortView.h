#pragma once

#include <QMainWindow>
#include "ui_SerialPortView.h"

class SerialPortView : public QMainWindow
{
	Q_OBJECT

public:
	SerialPortView(QWidget *parent = nullptr);
	~SerialPortView();

private:
	Ui::SerialPortViewClass ui;
};
