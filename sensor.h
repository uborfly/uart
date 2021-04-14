#ifndef SENSOR_H
#define SENSOR_H
#include "modbus.h"
#include <QObject>
#include <QTextEdit>

class Sensor : public My_Modbus
{
public:
    typedef union hex2float
    {
        float data;
        unsigned char hex[4];
    }hex2float;

    typedef union Sensor_Reg
    {
        struct
        {
            float fDensity_LDO;             //0  溶解氧值
            float fTemprature_LDO;          //2  温度
            float fDelta_Phase;             //4  相位差
            float fRed_Phase;               //6  红光相位
            float fGreen_Phase;             //8  绿光相位
            unsigned short red_voltage;     //10  红光电压
            unsigned short red_amp;         //11  红光放大倍数
            unsigned short green_voltage;   //12  绿光电压
            unsigned short green_amp;       //13  绿光放大倍数
            float LDO_soft_version;         //14  传感器软件版本
            unsigned short usLDO_sign;      //16  传感器标志 2溶解氧
            unsigned short usLDO_State;     //17  传感器状态
            unsigned short LDO_unit;        //18  单位  0 为%，1为mg/L
            unsigned short LDO_damping;     //19  滤波
            float fAtmosphere;              //20  大气压   从大气压开始为设置数据
            float phase_zero;               //22  零点标定
            float LDO_slope;                //24  空气标定
            float phase_zero_default;       //26  厂家零点标定
            float LDO_slope_default;        //28  厂家空气标定
            unsigned long uiLDO_Serial;     //30  传感器序列
            unsigned short LDO_add;         //32  传感器地址
            unsigned short comm_rtu_ascii;  //33  通信RTU/ASCII选择，本程序只能是RTU，所以没有用这个
            unsigned short uiDemarcate_LDO; //34  标定 1为零点标定 2为空气标定 3为载入出厂值
            unsigned short error_LDO;       //35  信号错误判断
            float fDelta_mg;                //36  传感器浓度调整值（百分比不调整），测量PPB时最后加该偏移。暂时不用
            float Salinity;                 //38  盐度的数据，“盐度”  不需要读取和设置
            float fNop[3];                  //40  预留不需要读取和设置
            float fTemp_Adj_Input;          //46  温度调节输入
            float fNop2;                    //48  预留
            float fM_calibrate;             //50  不需要读取和设置
            float fF_calibrate;             //52  不需要读取和设置
            float fD_Phi1;                  //54  不需要读取和设置
            float fD_KSV1;                  //56  不需要读取和设置
            float fD_KSV;                   //58
            float fZero_Default;            //60
        } Part;
        unsigned short Buffer[62];
        unsigned char Num[62 * 2];
    } Sensor_TypeDef;
public:
    Sensor();
    ~Sensor();
    void readParse(QVector <quint16> data);
    void display(QTextEdit* edit);
    void write(QModbusDataUnit::RegisterType table, int startAddress, int numOfEntries, QVector<quint16> data);
private:
//    int m_iServerAddress;
    Sensor_TypeDef gSensorData;
    void saveToXlsx();

//public:
//    Sensor_TypeDef gSensorData;
};

#endif // SENSOR_H
