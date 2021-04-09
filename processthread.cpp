#include "processthread.h"

ProcessThread::ProcessThread()
{

}

void ProcessThread::run()
{
    while (m_bCloseStatus)
    {
        qDebug()<<"modbusThread run!";
        modbusThread->modbusRead(4,QModbusDataUnit::HoldingRegisters,1,10);
        sleep(2);
    }
}

void ProcessThread::setModbusThread(My_Modbus *modbus)
{
    modbusThread = modbus;
    m_bCloseStatus = true;
}

void ProcessThread::closeThread()
{
    if(this->isRunning())
    {
        m_bCloseStatus = false;
        this->deleteLater();
        this->wait();
    }
}
