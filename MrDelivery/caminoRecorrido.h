#ifndef CAMINORECORRIDO_H
#define CAMINORECORRIDO_H

#include <QString>

class caminoRecorrido
{
public:

    QString camino;
    double pesoTotal;

    caminoRecorrido(){

        this->pesoTotal = 0.0;
    }
};

#endif // CAMINORECORRIDO_H
