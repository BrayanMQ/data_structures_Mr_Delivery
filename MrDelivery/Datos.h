#ifndef DATOS_H
#define DATOS_H

#include <Grafo.h>
#include <Thread_JSON.h>
#include <funcionesJSON.h>
#include <GrafoMatriz.h>


class Datos{

public:

    Grafo * grafo;
    GrafoMatriz * grafoMatriz;
    Thread_JSON * tJSON;
    funcionesJSON * fJSON;

    Datos(){
        this->grafo = new Grafo();
        this->grafoMatriz = new GrafoMatriz();
        this->fJSON = new funcionesJSON();
        this->tJSON = new Thread_JSON(this->fJSON,this->grafo, this->grafoMatriz);
        this->tJSON->start();
    }
};

#endif // DATOS_H
