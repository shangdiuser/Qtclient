#include "SerialPortView.h"

SerialPortView::SerialPortView(QWidget *parent)
	: QMainWindow(parent)
{
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
}

SerialPortView::~SerialPortView()
{}

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
		QString sendDate = ui.lineEdit->text();
		QByteArray data = sendDate.toUtf8();
		
	int retval = 	serial->write(data);
	if (retval < 1) {
		qDebug() << "pushButtonSend secces" << data;
	}
	else {
		qDebug() << "pushButtonSend fail" << data;
	}
	}
	else{
		qDebug() << "no open";
}

}
