#include "modbus.h"
#include "qdebug.h"
#include <QModbusDevice>

My_Modbus::My_Modbus()
{
    modbusDevice = new QModbusRtuSerialMaster(nullptr);
    connect(modbusDevice, SIGNAL(errorOccurred()), this, SLOT(modbusMessage()));

    if(modbusDevice)
    {
        qDebug("创建 Modbus Master 成功。");
        connect(modbusDevice, &QModbusClient::stateChanged, this, &My_Modbus::modbusStateChanged);
    }
    else
    {
        qDebug("创建 Modbus Master 失败。");
    }
}

My_Modbus::~My_Modbus()
{
    qDebug() << "~My_Modbus";
    delete modbusDevice;
}

void My_Modbus::modbusConnect(struct Settings m_settings)
{
    if(!modbusDevice) return;

    if(modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_settings.portName);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, m_settings.baud);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, m_settings.parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, m_settings.dataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, m_settings.stopBits);

        modbusDevice->setTimeout(m_settings.responseTime);
        modbusDevice->setNumberOfRetries(m_settings.numberOfRetries);

        if(modbusDevice->connectDevice())
        {
            qDebug("Modbus 连接成功。");
        }
        else
        {
            qDebug("Modbus 连接失败。");
        }
    }
}

void My_Modbus::modbusDisconnect(void)
{
    if (modbusDevice)   modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice = nullptr;
}

void My_Modbus::modbusStateChanged(int state)
{
    if(state == QModbusDevice::UnconnectedState)
    {
        qDebug("Modbus 已断开。");
    }
    else if(state == QModbusDevice::ConnectedState)
    {
        qDebug("Modbus 已连接。");
    }
}

void My_Modbus::modbusMessage(void)
{
    qDebug() << modbusDevice->errorString();
}

void My_Modbus::modbusMessage(QString mess)
{
    qDebug() << mess;
}


void My_Modbus::modbusRead(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries)
{
    qDebug() << "modbusRead";
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug("Modbus Device is not connected!");
        return;
    }

    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numOfEntries);

    if(QModbusReply *reply = modbusDevice->sendReadRequest(dataUnit, serverAddress))
    {
        qDebug() << "wait reply!" << reply->errorString();

        if(!reply->isFinished())
        {
            qDebug("reply finished!");
            connect(reply, &QModbusReply::finished, this, &My_Modbus::modbusReadData);
        }
    }
    else
    {
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }
}

void My_Modbus::modbusReadData()
{
    qDebug() << "modbusReadData";

    QModbusDataUnit dataUnit;
    auto reply = qobject_cast<QModbusReply *>(sender());
    if(!reply) return;
    qDebug() << "reply";
    if(reply->error() == QModbusDevice::NoError)
    {
        dataUnit = reply->result();
//        qDebug() << "Get Value:" << dataUnit.valueCount();

        emit modbusReadReady(dataUnit);
    }
    else if(reply->error() == QModbusDevice::ProtocolError)
    {
        modbusMessage(tr("Read response error: %1 (Modbus exception :0x%2)")
                      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1 ,16));
    }
    else
    {
        modbusMessage(tr("Read response: %1 (code :0x%2)")
                      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1 ,16));
    }

    reply->deleteLater();
}

//服务器地址、寄存器类型、起始地址、变量数量、写入数据
void My_Modbus::modbusWrite(int serverAddress, QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data)
{
    if(!modbusDevice || modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        qDebug("Modbus Device is not connected!");
        return;
    }

    //QModbusDataUnit，是用来处理通过串口一次传输的数据
    QModbusDataUnit dataunit = QModbusDataUnit(table, startAddress, numOfEntries);

    for(uint i = 0; i < dataunit.valueCount(); i++)
    {
        dataunit.setValue( i,  data.at(i));
    }

    if(auto *reply = modbusDevice->sendWriteRequest(dataunit,  serverAddress))
    {
        connect(reply, &QModbusReply::finished, this, [this, reply](){
            if(reply->error() == QModbusDevice::ProtocolError){
                modbusMessage(tr("Write response error:%1 (modbus exception:0x%2)")
                              .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
            }else{
                modbusMessage(tr("Write response:%1 (code:0x%2)")
                              .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16));
            }

            reply->deleteLater();
        });
    }
    else{
        modbusMessage(tr("Write error:") + modbusDevice->errorString());
    }
}

