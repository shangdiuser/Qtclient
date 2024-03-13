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

// 某个打卡按钮的点击槽函数
void Qtclient::onPunchCardButtonClicked() {
    QString employeeId = ui.textEdit_4->toPlainText();

    qDebug() << employeeId << "employeeId";
   
   HttpHandle handle;

   QByteArray buf = handle.Clock(employeeId);
   
   int jsonDataStart = buf.indexOf("{");
   int jsonDataEnd = buf.lastIndexOf("}");

   if (jsonDataStart != -1 && jsonDataEnd != -1) {
       QByteArray jsonData = buf.mid(jsonDataStart, jsonDataEnd - jsonDataStart + 1);

       // 解析 JSON 数据
       QJsonParseError error;
       QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

       if (error.error == QJsonParseError::NoError && jsonDoc.isObject()) {
           QJsonObject jsonObj = jsonDoc.object();
           QString punch_in_time = jsonObj["punch_in_time"].toString();
           qDebug() << "punch_in_time:" << punch_in_time;

           ui.textEdit_6->setText(jsonObj["punch_in_time"].toString());
           QString chidao = "迟到";
           QString zheng = "正常";
           if (1 == jsonObj["is_late"].toInt()) {
               ui.textEdit_5->setText(QString::fromUtf8("chidao"));
           }
           else
           {
               ui.textEdit_5->setText(QString::fromUtf8("zhengcahng"));
           }
          // jsonObject["name"] = query.value("name").toString(); // 添加员工姓名
          // jsonObject["department"] = query.value("department").toString(); // 添加部门信息
           ui.textEdit->setText(jsonObj["name"].toString());
           ui.textEdit_2->setText(jsonObj["department"].toString());


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
   
    // 构造 JSON 数据
    QJsonObject jsonObject;
    jsonObject["employee_id"] = employeeId;
    jsonObject["punch_in_time"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    jsonObject["punch_out_time"] = QDateTime::currentDateTime().addSecs(8 * 3600).toString(Qt::ISODate);
    jsonObject["is_late"] = false;
    jsonObject["is_absent"] = false;
    jsonObject["fine_amount"] = 0;

    qDebug() << employeeId << "QJsonObject employeeId";

    // 转换为 JSON 文档
    QJsonDocument jsonDoc(jsonObject);
    QByteArray jsonData = jsonDoc.toJson();

    // 调用 sendRequest 函数，传递正确的 URL 和 JSON 数据
    QUrl url("http://localhost:8080/Clock"); // 替换为实际的 URL
   // requestTool::sendRequest(url, jsonData);
    // 在需要调用 sendRequest 的地方，创建一个 requestTool 对象，并调用其 sendRequest 函数
   // requestTool tool;
   // tool.sendRequest(url, jsonData);

    /*
    // 创建网络请求
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("http://localhost:8080/Clock"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送 POST 请求
    QNetworkReply* reply = manager.post(request, jsonData);

    qDebug() << reply << "发送 POST 请求";


  

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
    qDebug() << "Request Body:" << jsonData;

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
}