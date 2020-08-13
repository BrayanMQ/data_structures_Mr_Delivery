#ifndef ARISTA_H
#define ARISTA_H
#include <QString>
#include <QDebug>

class Arista{

public:

    QString origen;
    QString destino;
    double costo, km, min;
    bool activo;

    Arista(QString pOrigen, QString pDestino, double pCosto, double pKm, double pMin){
        this->origen = pOrigen;
        this->destino = pDestino;
        this->costo = pCosto;
        this->km = pKm;
        this->min = pMin;
        this->activo = true;
    }

    void imprimir(){
        qDebug()<<"Destino: "+this->destino<<"Costo: "+QString::number(this->costo)+
        ", KM: "+QString::number(this->km)+", Min: "+QString::number(this->min);
    }
};

#endif // ARISTA_H
