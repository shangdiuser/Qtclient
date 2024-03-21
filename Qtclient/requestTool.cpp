#include "requestTool.h"


requestTool::requestTool(QObject* parent)
{
    // �������ӹ�����
     // networkManager = new QNetworkAccessManager(this);
}

// ����Ҫ��������ĵط���ʹ�����ӹ�������������
 void requestTool::sendRequest(const QUrl& url, const QByteArray& data) {
  /*
    // ������������
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // ���� POST ����
    QNetworkReply* reply = networkManager->post(request, data);

    // �鿴�����ַ
    QUrl requestUrl = request.url();
    qDebug() << "Request URL:" << requestUrl.toString();

    // �鿴����ͷ
    QList<QByteArray> requestHeaders = request.rawHeaderList();
    qDebug() << "Request Headers:";
    for (const QByteArray& header : requestHeaders) {
        qDebug() << header << ":" << request.rawHeader(header);
    }

    // �鿴������
    qDebug() << "Request Body:" << data;


    // ������Ӧ
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            qDebug() << "Response:" << responseData;
        }
        else {
            qDebug() << "Request failed:" << reply->errorString();
        }

        // �ͷ���Դ
        reply->deleteLater();

        });*/
}
