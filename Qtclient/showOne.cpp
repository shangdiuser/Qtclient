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
}

showOne::~showOne()
{}


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
    QFont font("Arial", 40, QFont::Bold);
    ui.label_3->setFont(font);
    //ui.label->setAlignment(Qt::AlignCenter);
   // ui.label->setGeometry(50, 50, 200, 50); // 设置文本标签的位置和大小
   ui.label->setText( "欢迎");
   ui.label_2->setText("晴天 20度");
   ui.label_3->setText("时间");
   ui.label_4->setText("时间");
   ui.label_5->setText("星期几");
 

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
        qDebug() << currentTime.toString("yyyy-MM-dd dddd");
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
