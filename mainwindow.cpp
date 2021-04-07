#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnOpenUART_clicked()
{
    QSerialPortInfo serialPortInfo(ui->cbUartList->currentText());
    qDebug() << "portName: " << serialPortInfo.portName();
    qDebug() << "isOpen"  << serialPortInfo.isBusy();
    if(serialPortInfo.isBusy())
    {
        qDebug() << serialPortInfo.portName() << "busy";
        return;
    }
    serial = new QSerialPort;
    serial->setPort(serialPortInfo);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->open(QIODevice::ReadWrite);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    QObject::connect(serial,&QSerialPort::readyRead,this,&MainWindow::read_data);
}

void MainWindow::on_btnScanUART_clicked()
{
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    //    qDebug() << "串口的个数： " << serialPortInfo.count();

    for (int idx=0; idx < serialPortInfo.count(); idx++) {
        ui->cbUartList->addItem(serialPortInfo.at(idx).portName());
    }
}

void MainWindow::on_btnCloseUART_clicked()
{
    serial->close();
}

void MainWindow::on_btnClear_clicked()
{
    ui->textEditUART->clear();
}

void MainWindow::read_data()
{
    QByteArray buff = serial->readAll();
    qDebug() << "get data" << buff;
    if(!buff.isEmpty())
    {
        QString str = ui->textEditUART->toPlainText();
        int n;
        str+=tr(buff);
        n=str.length();
        ui->textEditUART->clear();
        ui->textEditUART->append(str);
    }
    buff.clear();
}
