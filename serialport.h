#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class serialPort
{
public:
    serialPort();
    bool openSerial(QSerialPort port);
    QSerialPort setSerial(QSerialPortInfo port);
    QSerialPort getSerial();
    bool closeSerial(QSerialPort port);
private:
    QSerialPort currentSerial;
};

#endif // SERIALPORT_H
