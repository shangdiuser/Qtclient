#include "Qtclient.h"

Qtclient::Qtclient(QWidget *parent)
    : QMainWindow(parent)
{
   
    ui.setupUi(this);

    connect(ui.onPunchCardButtonClicked, &QPushButton::clicked, this, &Qtclient::onPunchCardButtonClicked);
    connect(this, &Qtclient::punchCardRequested, this, &Qtclient::onPunchCardRequested);
}

Qtclient::~Qtclient()
{}

// ĳ���򿨰�ť�ĵ���ۺ���
void Qtclient::onPunchCardButtonClicked() {
    QString employeeId = ui.textEdit_4->toPlainText();

    qDebug() << employeeId << "employeeId";
    // ��ȡԱ��ID
    //QString employeeId = "123"; // ������Ҫ����ʵ�������ȡԱ��ID
    // �����ź�
   // emit punchCardRequested(employeeId);
    Qtclient qtclient;;
    qtclient.Clock(employeeId);

}

void Qtclient::Clock(const QString& employeeId)
{
    Qtclient* childObject = new Qtclient(this);
    // ���� JSON ����
    QJsonObject jsonObject;
    jsonObject["employee_id"] = employeeId;
    jsonObject["punch_in_time"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["punch_out_time"] = QDateTime::currentDateTime().addSecs(8 * 3600).toString(Qt::ISODate);
    jsonObject["is_late"] = false;
    jsonObject["is_absent"] = false;
    jsonObject["fine_amount"] = 0;

    //qDebug() << employeeId << "QJsonObject employeeId";
   
    // ת��Ϊ JSON �ĵ�
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // ������������
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //
    QNetworkRequest request(QUrl("http://localhost:8080/Clock/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = manager->post(request, jsonData);
    // ���� POST ����
   // QNetworkReply* reply = manager.post(request, jsonData);

    

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


        });
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
    qDebug() << "Request Body:" << jsonData;


    /*
    // ת��Ϊ JSON �ĵ�
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // ���� sendRequest ������������ȷ�� URL �� JSON ����
    QUrl url("http://localhost:8080/Clock"); // �滻Ϊʵ�ʵ� URL
    // requestTool::sendRequest(url, jsonData);
     // ����Ҫ���� sendRequest �ĵط�������һ�� requestTool ���󣬲������� sendRequest ����
    requestTool tool;
    tool.sendRequest(url, jsonData);*/
}




void Qtclient::onPunchCardRequested(const QString& employeeId) {
   
    // ���� JSON ����
    QJsonObject jsonObject;
    jsonObject["employee_id"] = employeeId;
    jsonObject["punch_in_time"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["punch_out_time"] = QDateTime::currentDateTime().addSecs(8 * 3600).toString(Qt::ISODate);
    jsonObject["is_late"] = false;
    jsonObject["is_absent"] = false;
    jsonObject["fine_amount"] = 0;

    qDebug() << employeeId << "QJsonObject employeeId";

    // ת��Ϊ JSON �ĵ�
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // ���� sendRequest ������������ȷ�� URL �� JSON ����
    QUrl url("http://localhost:8080/Clock"); // �滻Ϊʵ�ʵ� URL
   // requestTool::sendRequest(url, jsonData);
    // ����Ҫ���� sendRequest �ĵط�������һ�� requestTool ���󣬲������� sendRequest ����
    requestTool tool;
    tool.sendRequest(url, jsonData);

    /*
    // ������������
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("http://localhost:8080/Clock"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // ���� POST ����
    QNetworkReply* reply = manager.post(request, jsonData);

    qDebug() << reply << "���� POST ����";


  

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
    qDebug() << "Request Body:" << jsonData;

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

        });

        */
}