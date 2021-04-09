#ifndef MY_MODBUS_H
#define MY_MODBUS_H

#include <QObject>
#include <QSerialPort>
#include <QModbusDataUnit>
#include <QModbusRtuSerialMaster>

class My_Modbus : public QObject
{
    Q_OBJECT

public:
    My_Modbus();
    ~My_Modbus();
public:
    struct Settings {
        QString portName;
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        int responseTime = 1000;
        int numberOfRetries = 1;
    };

    void modbusConnect(struct Settings m_settings);
    void modbusDisconnect(void);
    void modbusRead(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries);
    void modbusWrite(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data);

signals:
    void modbusReadReady(QModbusDataUnit dataUnit);

public slots:
    void modbusStateChanged(int state);
    void modbusReadData(void);

    void modbusMessage(void);
    void modbusMessage(QString mess);


private:
    QModbusClient *modbusDevice = nullptr;
};
#endif
