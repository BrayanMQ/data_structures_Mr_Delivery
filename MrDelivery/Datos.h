#ifndef DATOS_H
#define DATOS_H

#include <Grafo.h>
#include <Thread_JSON.h>
#include <funcionesJSON.h>


class Datos{

public:

    Grafo * grafo;
    Thread_JSON * tJSON;
    funcionesJSON * fJSON;

    Datos(){
        this->grafo = new Grafo();
        this->fJSON = new funcionesJSON();
        this->tJSON = new Thread_JSON(this->fJSON,this->grafo);
        this->tJSON->start();
    }
};

#endif // DATOS_H
