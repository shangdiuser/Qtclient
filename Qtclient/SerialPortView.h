#pragma once

#include <QMainWindow>
#include "ui_SerialPortView.h"
#include<qserialportinfo.h>
#include<qserialport.h>
#include<qdebug.h>

class SerialPortView : public QMainWindow
{
	Q_OBJECT

public slots:
	void pushButtonOpen();
	void recvSLOTS();
	void pushButtonSend();
public:
	SerialPortView(QWidget *parent = nullptr);
	~SerialPortView();
	

private:
	Ui::SerialPortViewClass ui;
	QSerialPort* serial;
};
