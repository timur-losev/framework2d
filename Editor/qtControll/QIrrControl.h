/*
 * File:   QIrrControll.h
 * Author: void
 *
 * Created on September 21, 2012, 3:05 PM
 */

#ifndef QIRRCONTROLL_H
#    define	QIRRCONTROLL_H

#include <QtGui/QWidget>

namespace irr
{
    class IrrlichtDevice;
}

class QIrrControll: public QWidget
{
    Q_OBJECT

private:
irr::IrrlichtDevice* m_Device;
        WId m_Handle;
public:
    QIrrControll(QWidget* parent = nullptr);
    ~QIrrControll();

    void Init();
    unsigned long MakeWindow();
signals:
//сигнал, который делает запрос на обновление кадра
    void UpdateIrrQuery(irr::IrrlichtDevice* device);

public slots:
     //функция, которая вызывается в ответ на сигнал, который делает запрос на обновление кадра
    void UpdateIrrlicht(irr::IrrlichtDevice* device);
protected:
    //переопределенный метод для получения события перерисовки виджета
    virtual void paintEvent(QPaintEvent* event);
    //переопределенный метод для получения события таймера для объекта
    virtual void timerEvent(QTimerEvent* event);
    //переопределенный метод для получения события изменения размера виджета
    virtual void resizeEvent(QResizeEvent* event);
    //тип драйвера, с помощью которого будет создано устройство Иррлихта

    virtual bool event(QEvent* event);
} ;

#endif	/* QIRRCONTROLL_H */

