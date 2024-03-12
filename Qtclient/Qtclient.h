#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qtclient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include"requestTool.h"
class Qtclient : public QMainWindow
{
    Q_OBJECT

signals:
    void punchCardRequested(const QString& employeeId);
public slots:
    void onPunchCardRequested(const QString& employeeId);


public:
    Qtclient(QWidget *parent = nullptr);
    ~Qtclient();

    void onPunchCardButtonClicked();

private:
    Ui::QtclientClass ui;
};
