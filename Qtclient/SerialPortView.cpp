#include "SerialPortView.h"

SerialPortView::SerialPortView(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::FramelessWindowHint); // 设置无边框
	// 添加菜单项
	m_contextMenu.addAction("最小化", this, &SerialPortView::minimize);
	m_contextMenu.addAction("最大化", this, &SerialPortView::maximize);
	m_contextMenu.addAction("退出", this, &SerialPortView::closeWindow);

	ui.setupUi(this);

	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
	for (int i = 0; i < list.size(); i++)
	{
		ui.comboSer->addItem(list.at(i).portName());
	}
	serial = new QSerialPort;

	connect(serial, &QSerialPort::readyRead, this, &SerialPortView::recvSLOTS);
	connect( ui.pushButtonOpen, &QPushButton::clicked, this, &SerialPortView::pushButtonOpen);
	connect(ui.pushButtonSend, &QPushButton::clicked, this, &SerialPortView::pushButtonSend);
	connect(ui.pushOpenLed, &QPushButton::clicked, this, &SerialPortView::pushOpenLed);
	connect(ui.pushCloseLed, &QPushButton::clicked, this, &SerialPortView::pushCloseLed);
	connect(ui.pushClose, &QPushButton::clicked, this, &SerialPortView::switchWindows);

	// 连接按钮的点击事件到槽函数
	connect(ui.pushButton_3, &QPushButton::clicked, [&]() {
		QString filePath = QFileDialog::getOpenFileName(this,
		"选择程序",
		QDir::homePath(),
		"可执行文件 (*.exe);;所有文件 (*.*)");
	if (!filePath.isEmpty()) {
		ui.lineEdit_2->setText(filePath);
	}
		});


	
		}

		


SerialPortView::~SerialPortView()
{}

void SerialPortView::minimize()
{
	this->showMinimized();
}

void SerialPortView::maximize()
{
	if (this->isMaximized())
		this->showNormal();
	else
		this->showMaximized();
}

void SerialPortView::closeWindow()
{
	this->close();
}

void SerialPortView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_dragPosition = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
}

void SerialPortView::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton) {
		move(event->globalPos() - m_dragPosition);
		event->accept();
	}
}

void SerialPortView::contextMenuEvent(QContextMenuEvent* event)
{
	m_contextMenu.exec(event->globalPos());
}

void SerialPortView::pushButtonOpen()
{
	serial->setPortName(ui.comboSer->currentText());

	if (ui.comboBun->currentText() == "115200") {
		serial->setBaudRate(QSerialPort::Baud115200);
	}
	else if(ui.comboBun->currentText() == "9600")
	{
		serial->setBaudRate(QSerialPort::Baud9600);
	}

	serial->setDataBits(QSerialPort::Data8);
	

	if (ui.comboBoxStop->currentText()=="None") {
		serial->setParity(QSerialPort::NoParity);
	}
	else if (ui.comboBoxStop->currentText() == "Even") {
		serial->setParity(QSerialPort::EvenParity);
	}
	else if (ui.comboBoxStop->currentText() == "Odd") {
		serial->setParity(QSerialPort::OddParity);
	}

	if (ui.comboBoxStop->currentText() == "1") {
		serial->setStopBits(QSerialPort::OneStop);
	}
	else if (ui.comboBoxStop->currentText() == "1.5") {
		serial->setStopBits(QSerialPort::OneAndHalfStop);
	}
	else if (ui.comboBoxStop->currentText() == "3") {
		serial->setStopBits(QSerialPort::TwoStop);
	}

	bool info = serial->open(QIODevice::ReadWrite);
	if (info == true) {
		qDebug() <<"open success";
	}
	else
	{
		qDebug() << "open fail";
	}


	//serial->setStopBits(QSerialPort::OneStop);

}

void SerialPortView::recvSLOTS()
{
	QByteArray data = serial->readAll();
	ui.textEdit_2->setText(data);
}

void SerialPortView::pushButtonSend()
{
	

	if (serial->isOpen()) {
		//QString sendDate = ui.lineEdit->text();
		// 获取用户在文本框中输入的文本
		QString userInput = ui.lineEdit->text().trimmed(); // 去除两端的空格
		
		// 将用户输入的指令转换为十六进制格式
		QByteArray hexData = QByteArray::fromHex(userInput.toLatin1());

		// 打印用户输入的十六进制数据
		qDebug() << "User input in hex format: " << hexData.toHex();
		
	int retval = 	serial->write(hexData);
	if (retval < 1) {
		qDebug() << "pushButtonSend secces" << hexData;
	}
	else {
		qDebug() << "pushButtonSend fail" << hexData;
	}
	}
	else{
		qDebug() << "no open";
}

}

void SerialPortView::pushOpenLed()
{
	//QString sendDate = ui.lineEdit->text();
		// 获取用户在文本框中输入的文本
	QString userInput = "ff 01 01 01 00 01 4b af"; // 去除两端的空格

	// 将用户输入的指令转换为十六进制格式
	QByteArray hexData = QByteArray::fromHex(userInput.toLatin1());

	// 打印用户输入的十六进制数据
	qDebug() << "User input in hex format: " << hexData.toHex();

	int retval = serial->write(hexData);
	if (retval < 1) {
		qDebug() << "pushButtonSend secces" << hexData;
	}
	else {
		qDebug() << "pushButtonSend fail" << hexData;
	}
}

void SerialPortView::pushCloseLed()
{
	//QString sendDate = ui.lineEdit->text();
	// 获取用户在文本框中输入的文本
	QString userInput = "ff 01 00 01 00 00 de c9"; // 去除两端的空格

	// 将用户输入的指令转换为十六进制格式
	QByteArray hexData = QByteArray::fromHex(userInput.toLatin1());

	// 打印用户输入的十六进制数据
	qDebug() << "User input in hex format: " << hexData.toHex();

	int retval = serial->write(hexData);
	if (retval < 1) {
		qDebug() << "pushButtonSend secces" << hexData;
	}
	else {
		qDebug() << "pushButtonSend fail" << hexData;
	}
}

void SerialPortView::switchWindows()
{
	showOne* showone = new showOne();
	showone->showInfo();
	showone->show();
	this->close();
}
