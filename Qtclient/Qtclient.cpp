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
   
   HttpHandle handle;

   QByteArray buf = handle.Clock(employeeId);
   
   int jsonDataStart = buf.indexOf("{");
   int jsonDataEnd = buf.lastIndexOf("}");

   if (jsonDataStart != -1 && jsonDataEnd != -1) {
       QByteArray jsonData = buf.mid(jsonDataStart, jsonDataEnd - jsonDataStart + 1);

       // ���� JSON ����
       QJsonParseError error;
       QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

       if (error.error == QJsonParseError::NoError && jsonDoc.isObject()) {
           QJsonObject jsonObj = jsonDoc.object();
           QString punch_in_time = jsonObj["punch_in_time"].toString();
           qDebug() << "punch_in_time:" << punch_in_time;

           ui.textEdit_6->setText(jsonObj["punch_in_time"].toString());
         
         
               ui.textEdit_5->setText(jsonObj["is_late"].toString());
          
          // jsonObject["name"] = query.value("name").toString(); // ���Ա������
          // jsonObject["department"] = query.value("department").toString(); // ��Ӳ�����Ϣ
           ui.textEdit->setText(jsonObj["name"].toString());
           ui.textEdit_2->setText(jsonObj["department"].toString());
           qDebug() << "哈哈哈哈:" ;

       }
       else {
           qDebug() << "JSON parse error:" << error.errorString();
       }
   }
   else {
       qDebug() << "Invalid JSON data in the reply";
   }
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
   // requestTool tool;
   // tool.sendRequest(url, jsonData);

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