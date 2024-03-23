#pragma once

#include <QMainWindow>
#include "ui_showOne.h"
#include <QDateTime>
#include <QMouseEvent>
#include<QTimer>
#include"HttpHandle.h"
#include"Qtclient.h"
#include "showData.h"
class showOne : public QMainWindow
{
	Q_OBJECT

public slots:
	void minimize();
	void maximize();
	void closeWindow();

public:
	showOne(QWidget *parent = nullptr);
	~showOne();
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void showInfo();
	void switchPages();
	void openQueryDialog();
	
private:
	Ui::showOneClass ui;

	QPoint m_dragPosition;
	QMenu m_contextMenu;
	QTimer timer;
	//Qtclient hand;

};
