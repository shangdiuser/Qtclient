#pragma once

#include <QMainWindow>
#include "ui_SerialPortView.h"
#include<qserialportinfo.h>
#include<qserialport.h>
#include<qdebug.h>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMouseEvent>
#include"showOne.h"
class SerialPortView : public QMainWindow
{
	Q_OBJECT

public slots:
	void pushButtonOpen();
	void recvSLOTS();
	void pushButtonSend();
	void pushOpenLed();
	void pushCloseLed();
	void switchWindows();

public:
	SerialPortView(QWidget *parent = nullptr);
	~SerialPortView();
	void minimize();
	void maximize();
	void closeWindow();
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;

private:
	Ui::SerialPortViewClass ui;
	QSerialPort* serial;
	QPoint m_dragPosition;
	QMenu m_contextMenu;
};
