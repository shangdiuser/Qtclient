#pragma once

#include <QMainWindow>
#include "ui_showData.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>
class showData : public QMainWindow
{
	Q_OBJECT

public slots:
	void minimize();
	void maximize();
	void closeWindow();

public:
	showData(QWidget *parent = nullptr);
	~showData();
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void initiShow();

private:
	Ui::showDataClass ui;
	QPoint m_dragPosition;
	QMenu m_contextMenu;
	//QStandardItemModel* m_pModel;  //数据模型对象指针
	//showData* initishow;
};
