#include "sensor.h"

Sensor::Sensor(int serverAddress)
{
    m_iServerAddress = serverAddress;
}

Sensor::~Sensor()
{

}

void Sensor::read(QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries)
{

}

void Sensor::write(QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data)
{

}
