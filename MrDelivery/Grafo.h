#ifndef GRAFO_H
#define GRAFO_H
#include <Vertice.h>
#include <QDebug>
#include <QQueue>

class Grafo{

public:
    int size = 0;
    QList<Vertice*> vertices;
    QString prof, anch;
    Grafo();
    void insertarVertice(QString);
    void insertarArista(QString,QString,bool,double,double,double);
    void imprimir();
    Vertice * buscarVertice(QString);
    void visitarAdyacentes(QString);
    void visitarAdyacentesConexo(QString);
    void profundidad(QString);
    void anchura(QString);
    bool conexo ();
    void limpiarVisitados();
    bool visitadoVertice(QString);
    void visitarVertice(QString);
};

#endif // GRAFO_H
