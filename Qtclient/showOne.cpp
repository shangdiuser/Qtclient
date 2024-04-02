#include "showOne.h"


showOne::showOne(QWidget *parent)
	: QMainWindow(parent)
{
  
    setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
    // 添加菜单项
    m_contextMenu.addAction("最小化", this, &showOne::minimize);
    m_contextMenu.addAction("最大化", this, &showOne::maximize);
    m_contextMenu.addAction("退出", this, &showOne::closeWindow);
	ui.setupUi(this);
    connect(ui.pushButton, &QPushButton::clicked, this, &showOne::switchPages);
    connect(ui.actionchaxun, &QAction::triggered, this, &showOne::openQueryDialog);
    connect(ui.actiondaochu, &QAction::triggered, this, &showOne::dowExcel);
    connect(ui.actionkz, &QAction::triggered, this, &showOne::openkz);
  
}

showOne::~showOne()
{}

void showOne::dowExcel()
{
    QByteArray jsonData = handle.allInfo("", "");

    // 解析 JSON 数据
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON: " << jsonError.errorString();
        return ;
    }

    if (!doc.isArray()) {
        qDebug() << "JSON data is not an array.";
        return ;
    }

    // 准备数据
    QStringList headers = { "员工编号", "姓名", "职位", "部门", "上班时间", "是否迟到" };
    QList<QStringList> data;

    QJsonArray jsonArray = doc.array();
    foreach(const QJsonValue & value, jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();

            QDateTime dateTime = QDateTime::fromString(obj["punch_in_time"].toString(), Qt::ISODate);
            QString formattedDateTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");

            QStringList rowData = { obj["employee_id"].toString(), obj["name"].toString(),
                                   obj["position"].toString(), obj["department"].toString(),
                                   formattedDateTime, obj["late"].toString() };
            data.append(rowData);
        }
    }

     // 生成文件名（包含日期时间）
    QString dateTimeString = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filePath = QString("F:/share18/%1_data.csv").arg(dateTimeString);
    // 保存Excel文件
   // QString filePath = "F:\\share18\\" + formattedDateTime + "data.csv";
    // 生成 CSV 文件
    //QString filePath = "data.csv";
    writeCSV(filePath, headers, data);



}

void showOne::writeCSV(const QString& filePath, const QStringList& headers, const QList<QStringList>& data)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream out(&file);

    // 写入表头
    for (const QString& header : headers) {
        out << "\"" << header << "\",";
    }
    out << "\n";

    // 写入数据
    for (const QStringList& rowData : data) {
        for (const QString& cellData : rowData) {
            out << "\"" << cellData << "\",";
        }
        out << "\n";
    }

    file.close();
    qDebug() << "CSV file saved to:" << filePath;
    // 弹出保存成功的提示
    QMessageBox::information(nullptr, "提示", "数据已导出");
}

void showOne::openkz()
{
    // Hide the main window
    this->close();
    //this->hide();
    SerialPortView* showdata = new SerialPortView();
    //showdata->initiShow();
    showdata->show();
}





/*
void showOne::dowExcel()
{
    QByteArray jsonData = handle.allInfo("", "");

    // 解析JSON数据
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &jsonError);

    if (jsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON: " << jsonError.errorString();
        return ;
    }

    if (!doc.isArray()) {
        qDebug() << "JSON data is not an array.";
        return ;
    }

    // 创建一个新的Excel实例
    QAxObject excel("Excel.Application");
    if (excel.isNull()) {
        qDebug() << "Failed to create Excel instance.";
        return ;
    }

    excel.dynamicCall("SetVisible(bool)", false); // 隐藏Excel窗口

    QAxObject* workbook = excel.querySubObject("Workbooks")->querySubObject("Add()");
    if (!workbook) {
        qDebug() << "Failed to create workbook.";
        return ;
    }

    QAxObject* worksheet = workbook->querySubObject("Worksheets(int)", 1);
    if (!worksheet) {
        qDebug() << "Failed to get worksheet.";
        return ;
    }

    // 设置表头
    QStringList headers = { "员工编号", "姓名", "职位", "部门", "上班时间", "是否迟到" };
    for (int col = 0; col < headers.size(); ++col) {
        QAxObject* cell = worksheet->querySubObject("Cells(int, int)", 1, col + 1);
        cell->setProperty("Value", headers[col]);
        delete cell;
    }

    int row = 2; // 从第二行开始写入数据
    QJsonArray jsonArray = doc.array();
    foreach(const QJsonValue & value, jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QDateTime dateTime = QDateTime::fromString(obj["punch_in_time"].toString(), Qt::ISODate);
            QString formattedDateTime = dateTime.toString("yyyy-MM-dd HH:mm:ss");

            QStringList rowData = { obj["employee_id"].toString(), obj["name"].toString(),
                                   obj["position"].toString(), obj["department"].toString(),
                                   formattedDateTime, obj["late"].toString() };

            for (int col = 0; col < rowData.size(); ++col) {
                QAxObject* cell = worksheet->querySubObject("Cells(int, int)", row, col + 1);
                cell->setProperty("Value", rowData[col]);
                delete cell;

                qDebug() << row<< "员工编号:" << obj["employee_id"].toString()
                    << "姓名:" << obj["name"].toString()
                    << "职位:" << obj["position"].toString()
                    << "部门:" << obj["department"].toString()
                    << "上班时间:" << formattedDateTime
                    << "是否迟到:" << obj["late"].toString();
            
            }
            ++row;
        }
    }

    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 格式化为字符串
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-ddHH:mm:ss");
    // 保存Excel文件
    QString filePath = "F:\\share18\\" + formattedDateTime+"data.xlsx";
    qDebug()<<filePath;
    QVariant result = workbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(filePath));
  
    // 检查返回的QVariant对象是否有效
    if (result.isValid()) {
        qDebug() << "SaveAs method executed successfully.";
    }
    else {
        qDebug() << "Failed to execute SaveAs method.";
    }

    workbook->dynamicCall("Close()");
    delete workbook;

    excel.dynamicCall("Quit()");

    // 弹出保存成功的提示
    QMessageBox::information(nullptr, "提示", "数据已成功保存到Excel文件。");

}

*/

void showOne::switchPages()
{
    
    this->hide(); // 隐藏当前窗口

   

    Qtclient* two = new Qtclient(); //  创建 showTwo 窗口的实例

    two->showClient(ui.lineEdit->text());


    two->show(); // 显示 showTwo 窗口
    // 2秒后切回 showOne 窗口
    QTimer::singleShot(4000, [=]() {
        two->hide();
        this->show();
        });
   
}

void showOne::openQueryDialog()
{
    // Hide the main window
    this->close();
    //this->hide();
    showData* showdata = new showData();
    showdata->initiShow();
    showdata->show();

   
}





void showOne::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void showOne::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void showOne::contextMenuEvent(QContextMenuEvent* event)
{
    m_contextMenu.exec(event->globalPos());
}

void showOne::showInfo()
{
    QFont font("Arial", 44, QFont::Bold);
    ui.label_3->setFont(font);
    ui.label->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_5->setAttribute(Qt::WA_TranslucentBackground);
    ui.label_6->setAttribute(Qt::WA_TranslucentBackground);
   ui.label->setText( "欢迎");
   ui.label->setStyleSheet("QLabel { background-color: transparent; border: none;  }");
   ui.label_2->setText("晴天 20度");
   ui.label_2->setStyleSheet("QLabel { background-color: transparent; border: none;  }");
   ui.label_3->setText("时间");
   ui.label_3->setStyleSheet("QLabel { background-color: transparent; border: none; }");
   ui.label_4->setText("时间");
   ui.label_4->setStyleSheet("QLabel { background-color: transparent; border: none; }");
   ui.label_5->setText("星期几");
   ui.label_5->setStyleSheet("QLabel { background-color: transparent; border: none;}");
  // ui.label->setStyleSheet("QLabel { background-color: transparent; }");
   ui.label_6->setStyleSheet("QLabel { background-color: transparent; border: none;}");

    // 更新实时时间和日期
   
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        //QLocale::setDefault(QLocale::Chinese);
        QLocale locale(QLocale::Chinese); // 设置地区为中国，以便使用中文
       // QString weekDay = locale.toString(QDate::currentDate(), "dddd"); // 获取当前日期的星期几（中文）
        QDateTime currentTime = QDateTime::currentDateTime();
        ui.label_3->setText(currentTime.toString("hh:mm:ss"));

        ui.label_4->setText(currentTime.toString("yyyy-MM-dd hh:mm:ss"));
        // 更新农历日期，你需要自己实现一个转换函数或者使用第三方库
        // lunarDateLabel->setText(convertToLunar(currentTime));
        ui.label_5->setText(locale.toString(QDate::currentDate(), "dddd"));
       // qDebug() << currentTime.toString("yyyy-MM-dd dddd");
        });

    timer.start(1000); // 每秒更新一次
}






void showOne::minimize()
{
    this->showMinimized();
}

void showOne::maximize()
{
    if (this->isMaximized())
        this->showNormal();
    else
        this->showMaximized();
}

void showOne::closeWindow()
{
    this->close();
}
