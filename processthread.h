#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <QDebug>
#include "modbus.h"

class ProcessThread : public QThread
{
public:
    ProcessThread();
    void run();
    void setModbusThread(My_Modbus *modbus);
    void closeThread();
private:
    My_Modbus *modbusThread = nullptr;
    bool m_bCloseStatus = true;
};

#endif // PROCESSTHREAD_H
