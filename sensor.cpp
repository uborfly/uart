#include "sensor.h"
#include <QtDebug>

Sensor::Sensor()
{
    //    m_iServerAddress = serverAddress;
}

Sensor::~Sensor()
{

}

void Sensor::readParse(QVector <quint16> data)
{
    QVector <quint16>::iterator v = data.begin();
    int i = 0;
    Sensor_TypeDef sensorParseBuf;
    while(v != data.end())
        sensorParseBuf.Buffer[i++] = *v++;
    data.clear();
    gSensorData = sensorParseBuf;
    //    qDebug() << sensorParseBuf.Part.fDensity_LDO;
    //    qDebug() << sensorParseBuf.Part.fTemprature_LDO;
    //    qDebug() << sensorParseBuf.Part.red_voltage;
}

void Sensor::display(QTextEdit* edit)
{
    QString str = edit->toPlainText();
    str += QString("溶解氧值:%1").arg(gSensorData.Part.fDensity_LDO)+"\t"+QString("温度:%1").arg(gSensorData.Part.fTemprature_LDO)+"\n";
    str += QString("相位差:%1").arg(gSensorData.Part.fDelta_Phase)+"\n";
    str += QString("红光相位:%1").arg(gSensorData.Part.fRed_Phase)+"\t"+QString("绿光相位:%1").arg(gSensorData.Part.fGreen_Phase)+"\n";
    str += QString("红光电压:%1").arg(gSensorData.Part.red_voltage) +"\t"+QString("绿光电压:%1").arg(gSensorData.Part.green_voltage)+"\n";
    str += QString("红光放大倍数:%1").arg(gSensorData.Part.red_amp)+"\t"+QString("绿光放大倍数:%1").arg(gSensorData.Part.green_amp)+"\n";
    str += QString("传感器软件版本:%1").arg(gSensorData.Part.LDO_soft_version)+"\t"+QString("传感器标志:%1").arg(gSensorData.Part.usLDO_sign)+"\n";
    str += QString("传感器状态:%1").arg(gSensorData.Part.usLDO_State)+"\t"+QString("单位:%1").arg(gSensorData.Part.LDO_unit)+"\n";
    str += QString("滤波:%1").arg(gSensorData.Part.LDO_damping)+"\t"+QString("大气压:%1").arg(gSensorData.Part.fAtmosphere)+"\n";
    str += "\n\n";
    edit->clear();
    edit->append(str);
    edit->append("");
}

void Sensor::write(QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data)
{

}
