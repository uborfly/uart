#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
#include "modbus.h"
#include "processthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenUART_clicked();
    void on_btnScanUART_clicked();
    void on_btnCloseUART_clicked();
    void data_read_ready(QModbusDataUnit dataUnit);
    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial=nullptr;
    My_Modbus *modbus = nullptr;
    ProcessThread *modbusThread = nullptr;
};
#endif // MAINWINDOW_H
