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
    Grafo * grafoModi;
    GrafoMatriz * grafoMatrizModi;
    QQueue<Grafo*> colaGrafo;
    QQueue<GrafoMatriz*> colaGrafoMatriz;
    funcionesJSON * fJSON;

    Datos(){
        this->grafo = new Grafo();
        this->grafoMatriz = new GrafoMatriz();
        this->grafoModi = new Grafo();
        this->grafoMatrizModi = new GrafoMatriz();
        this->fJSON = new funcionesJSON();
    }
};

#endif // DATOS_H
