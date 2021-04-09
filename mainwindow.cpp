#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    struct My_Modbus::Settings settings;
    settings.portName = serialPortInfo.portName();
    modbus = new My_Modbus;
    modbus->modbusConnect(settings);
    connect(modbus,SIGNAL(modbusReadReady(QModbusDataUnit)),this,SLOT(data_read_ready(QModbusDataUnit)));

    modbus->modbusRead(1,QModbusDataUnit::HoldingRegisters,0,10);
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
    //    serial->close();
    modbus->modbusDisconnect();
}

void MainWindow::on_btnClear_clicked()
{
    ui->textEditUART->clear();
}

void MainWindow::data_read_ready(QModbusDataUnit dataUnit)
{
    qDebug() << "get data" << dataUnit.valueCount();
    if(dataUnit.valueCount() != 0)
    {
        QString str = ui->textEditUART->toPlainText();
        QVector <quint16> buff = dataUnit.values();
        for(int i=0;i < dataUnit.valueCount();i++)
        {
            qDebug() << buff.data()[i];
            int n;
            str+=QString::number(buff.data()[i],16)+" ";
            n=str.length();
            ui->textEditUART->clear();
            ui->textEditUART->append(str);
        }
        ui->textEditUART->append("");
        buff.clear();
    }
}
