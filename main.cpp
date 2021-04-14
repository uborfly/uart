#include "mainwindow.h"

#include <QApplication>
#include <QtXlsx>

void xlsxInit(QString name)
{
    int col=2;
    QXlsx::Document xlsx;
    xlsx.write(1,col++,"溶解氧值");
    xlsx.write(1,col++,"温度");
    xlsx.write(1,col++,"相位差");
    xlsx.write(1,col++,"红光相位");
    xlsx.write(1,col++,"红光电压");
    xlsx.write(1,col++,"红光放大倍数");
    xlsx.write(1,col++,"绿光相位");
    xlsx.write(1,col++,"绿光电压");
    xlsx.write(1,col++,"绿光放大倍数");
    xlsx.write(1,col++,"传感器软件版本");
    xlsx.write(1,col++,"传感器标志");
    xlsx.write(1,col++,"传感器状态");
    xlsx.write(1,col++,"单位");
    xlsx.write(1,col++,"滤波");
    xlsx.write(1,col++,"大气压");
    xlsx.saveAs(name);
}
int main(int argc, char *argv[])
{
    xlsxInit("test.xlsx");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
