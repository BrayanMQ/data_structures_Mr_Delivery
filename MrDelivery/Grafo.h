#ifndef GRAFO_H
#define GRAFO_H
#include <Vertice.h>
#include <QDebug>

class Grafo{

    QList<Vertice*> vertices;

public:
    Grafo();
    void insertarVertice(QString);
    void insertarArista(QString,QString,double,double,double);
    void imprimir();
    Vertice * buscarVertice(QString);
};

#endif // GRAFO_H
