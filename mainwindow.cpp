#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEditUART->setFontPointSize(16);
    ui->textEditUART->setFontFamily(tr("Times New Roman"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnOpenUART_clicked()//打开串口，启动modbus
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
    modbusThread = new ProcessThread;
    modbusThread->setModbusThread(modbus);
    modbusThread->start();
    //        modbus->modbusRead(4,QModbusDataUnit::HoldingRegisters,1,10);
}

void MainWindow::on_btnScanUART_clicked()//查询串口号，显示在下拉菜单
{
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    //    qDebug() << "串口的个数： " << serialPortInfo.count();
    ui->cbUartList->clear();
    for (int idx=0; idx < serialPortInfo.count(); idx++) {
        ui->cbUartList->addItem(serialPortInfo.at(idx).portName());
    }
}

void MainWindow::on_btnCloseUART_clicked()//关闭端口
{
    modbusThread->closeThread();
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
        // 使用迭代器 iterator 访问值
        QVector <quint16>::iterator v = buff.begin();
        while( v != buff.end()) {
            str+=QString::number(*v,16).toUpper()+" ";
            ui->textEditUART->clear();
            ui->textEditUART->append(str);
            v++;
        }
        ui->textEditUART->append("");
        buff.clear();
    }
}
