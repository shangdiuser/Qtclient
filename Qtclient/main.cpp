#include "Qtclient.h"
#include <QtWidgets/QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   
   
    Qtclient w;
    w.show();

  //  requestTool Tool;

    /*
    // 构造 JSON 数据
    QJsonObject jsonObject;
    jsonObject["employee_id"] = 2;
    jsonObject["punch_in_time"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["punch_out_time"] = QDateTime::currentDateTime().addSecs(8 * 3600).toString(Qt::ISODate);
    jsonObject["is_late"] = false;
    jsonObject["is_absent"] = false;
    jsonObject["fine_amount"] = 0;

    // 转换为 JSON 文档
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // 创建网络请求
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("http://localhost:8080/Clock"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送 POST 请求
    QNetworkReply* reply = manager.post(request, jsonData);

    // 处理响应
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Response:" << responseData;
        }
        else {
            qDebug() << "Request failed:" << reply->errorString();
        }

        // 释放资源
        reply->deleteLater();
        
       
        });
        */
        


    return a.exec();
}
