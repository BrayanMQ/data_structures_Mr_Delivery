#ifndef DATOS_H
#define DATOS_H

#include <Grafo.h>
#include <funcionesJSON.h>
#include <GrafoMatriz.h>
#include <QQueue>


class Datos{

public:

    Grafo * grafo;
    GrafoMatriz * grafoMatriz;
    QQueue<Grafo*> colaGrafo;
    QQueue<GrafoMatriz*> colaGrafoMatriz;
    funcionesJSON * fJSON;

    Datos(){
        this->grafo = new Grafo();
        this->grafoMatriz = new GrafoMatriz();
        this->fJSON = new funcionesJSON();
    }
};

#endif // DATOS_H
