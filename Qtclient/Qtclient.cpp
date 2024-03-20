#include "Qtclient.h"



Qtclient::Qtclient(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    // 添加菜单项
    m_contextMenu.addAction("最小化", this, &Qtclient::minimize);
    m_contextMenu.addAction("最大化", this, &Qtclient::maximize);
    m_contextMenu.addAction("退出", this, &Qtclient::closeWindow);
    ui.setupUi(this);

    connect(ui.onPunchCardButtonClicked, &QPushButton::clicked, this, &Qtclient::onPunchCardButtonClicked);
    connect(this, &Qtclient::punchCardRequested, this, &Qtclient::onPunchCardRequested);

}

Qtclient::~Qtclient()
{}

void Qtclient::showClient(const QString& employeeId)
{
    ui.label->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_5->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_6->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit_2->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit_3->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit_4->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit_5->setAttribute(Qt::WA_TranslucentBackground);
    ui.textEdit_6->setAttribute(Qt::WA_TranslucentBackground);
   // ui.textEdit_2->setAttribute(Qt::WA_TranslucentBackground);

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
            //qDebug() << "punch_in_time:" << punch_in_time;
            // 将ISO 8601格式的时间转换为QDateTime对象
            QDateTime dateTime = QDateTime::fromString(punch_in_time, Qt::ISODate);

            // 将QDateTime对象格式化为指定格式的字符串
            QString formattedDateTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");


            ui.textEdit_6->setText(formattedDateTime);


            ui.textEdit_5->setText(jsonObj["is_late"].toString());
            ui.textEdit_4->setText(jsonObj["employee_id"].toString());
            ui.textEdit_3->setText(jsonObj["position"].toString());
            // jsonObject["name"] = query.value("name").toString(); // ���Ա������
            // jsonObject["department"] = query.value("department").toString(); // ��Ӳ�����Ϣ
            ui.textEdit->setText(jsonObj["name"].toString());
            ui.textEdit_2->setText(jsonObj["department"].toString());
            qDebug() << "哈哈哈哈:";

        }
        else {
            qDebug() << "JSON parse error:" << error.errorString();
        }
    }
    else {
        qDebug() << "Invalid JSON data in the reply";
        ui.textEdit_5->setText("打卡失败！！");
    }
}



// ĳ���򿨰�ť�ĵ���ۺ���
void Qtclient::onPunchCardButtonClicked() {
    QString employeeId = ui.textEdit_4->toPlainText();

    qDebug() << employeeId << "employeeId";
   
  
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
        
           //qDebug() << "punch_in_time:" << punch_in_time;
           // 将ISO 8601格式的时间转换为QDateTime对象
           QDateTime dateTime = QDateTime::fromString(punch_in_time, Qt::ISODate);

           // 将QDateTime对象格式化为指定格式的字符串
           QString formattedDateTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");


           ui.textEdit_6->setText(formattedDateTime);


           ui.textEdit_5->setText(jsonObj["is_late"].toString());
           ui.textEdit_4->setText(jsonObj["employee_id"].toString());
           ui.textEdit_3->setText(jsonObj["position"].toString());
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

}


void Qtclient::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Qtclient::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void Qtclient::contextMenuEvent(QContextMenuEvent* event)
{
    m_contextMenu.exec(event->globalPos());
}





void Qtclient::minimize()
{
    this->showMinimized();
}

void Qtclient::maximize()
{
    if (this->isMaximized())
        this->showNormal();
    else
        this->showMaximized();
}

void Qtclient::closeWindow()
{
    this->close();
}
