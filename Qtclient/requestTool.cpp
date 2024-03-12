#include "requestTool.h"


requestTool::requestTool(QObject* parent)
{
    // 创建连接管理器
      networkManager = new QNetworkAccessManager(this);
}

// 在需要发送请求的地方，使用连接管理器发送请求
 void requestTool::sendRequest(const QUrl& url, const QByteArray& data) {
     
    // 创建网络请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送 POST 请求
    QNetworkReply* reply = networkManager->post(request, data);

    // 查看请求地址
    QUrl requestUrl = request.url();
    qDebug() << "Request URL:" << requestUrl.toString();

    // 查看请求头
    QList<QByteArray> requestHeaders = request.rawHeaderList();
    qDebug() << "Request Headers:";
    for (const QByteArray& header : requestHeaders) {
        qDebug() << header << ":" << request.rawHeader(header);
    }

    // 查看请求体
    qDebug() << "Request Body:" << data;


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
}
