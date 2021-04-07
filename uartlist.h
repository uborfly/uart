#ifndef UARTLIST_H
#define UARTLIST_H

#include <QComboBox>
#include <QMouseEvent>
class uartlist : public QComboBox
{
public:
    ~uartlist();
    explicit uartlist(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif // UARTLIST_H
