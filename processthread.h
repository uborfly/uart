#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QObject>

class ProcessThread : public QObject
{
    Q_OBJECT
public:
    explicit ProcessThread(QObject *parent = nullptr);

signals:

};

#endif // PROCESSTHREAD_H
