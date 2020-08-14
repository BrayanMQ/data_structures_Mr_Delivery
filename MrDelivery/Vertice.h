#ifndef VERTICE_H
#define VERTICE_H
#include <QList>
#include <Arista.h>

class Vertice{

public:

    QString nombre;
    QList<Arista*> aristas;
    bool visitado;

    Vertice(QString pNombre){
        this->nombre = pNombre;
        this->visitado = false;
    }

    //BUSCAR ARISTA
    Arista * buscarArista(QString pDestino){

        for (int i = 0;i<this->aristas.size();i++) {

            if (this->aristas[i]->destino == pDestino){
                return this->aristas[i];
            }
        }
        return NULL;
    }
};

#endif // VERTICE_H
