#ifndef CAMINORECORRIDO_H
#define CAMINORECORRIDO_H

#include <QString>
#include <QList>

class caminoRecorrido
{
public:

    QList <QString> camino;
    double pesoTotal;

    caminoRecorrido(){

        this->pesoTotal = 0.0;
    }
};

#endif // CAMINORECORRIDO_H
