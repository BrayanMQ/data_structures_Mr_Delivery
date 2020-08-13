#ifndef THREAD_JSON_H
#define THREAD_JSON_H

#include <QThread>
#include <funcionesJSON.h>
#include <Grafo.h>

class Thread_JSON : public QThread
{
    Q_OBJECT

public:
    funcionesJSON * fJSON;
    Grafo * grafo;
    Thread_JSON(funcionesJSON * pFJSON, Grafo * pGrafo){
        this->fJSON = pFJSON;
        this->grafo = pGrafo;
    }
    void run ();
};

#endif // THREAD_JSON_H
