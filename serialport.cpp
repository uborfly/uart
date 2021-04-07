#include "serialport.h"

serialPort::serialPort()
{

}

QSerialPort serialPort::setSerial(QSerialPortInfo port)
{
    QSerialPort *serial = new QSerialPort;

}

bool serialPort::closeSerial(QSerialPort port)
{
    port.close();
    return true;
}
