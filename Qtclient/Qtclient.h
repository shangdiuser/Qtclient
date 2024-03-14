#pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")

#endif

#include <QtWidgets/QMainWindow>
#include "ui_Qtclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include"HttpHandle.h"
#include <QMouseEvent>
class Qtclient : public QMainWindow
{
    Q_OBJECT
      
signals:
    void punchCardRequested(const QString& employeeId);
public slots:
    void onPunchCardRequested(const QString& employeeId);
    void minimize();
    void maximize();
    void closeWindow();

public:
    Qtclient(QWidget *parent = nullptr);
    ~Qtclient();
   
    void onPunchCardButtonClicked();
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
    void showHandle();
private:
    Ui::QtclientClass ui;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    
    QPoint m_dragPosition;
    QMenu m_contextMenu;
};
