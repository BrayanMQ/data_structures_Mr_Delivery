#ifndef THREAD_JSON_H
#define THREAD_JSON_H

#include <QThread>
#include <funcionesJSON.h>
#include <Grafo.h>
#include <GrafoMatriz.h>

class Thread_JSON : public QThread
{
    Q_OBJECT

public:
    funcionesJSON * fJSON;
    Grafo * grafo;
    GrafoMatriz * grafoMatriz;
    Thread_JSON(funcionesJSON * pFJSON, Grafo * pGrafo, GrafoMatriz * pGrafoMatriz){
        this->fJSON = pFJSON;
        this->grafo = pGrafo;
        this->grafoMatriz = pGrafoMatriz;
    }
    void run ();
};

#endif // THREAD_JSON_H
