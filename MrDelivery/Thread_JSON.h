#ifndef THREAD_JSON_H
#define THREAD_JSON_H

#include <QThread>
#include <Datos.h>


class Thread_JSON : public QThread
{
    Q_OBJECT

public:
    Datos * datos;

    Thread_JSON(Datos * pDatos){
        this->datos = pDatos;
    }
    void run ();

signals:
    void datosCola(QString);
};

#endif // THREAD_JSON_H
