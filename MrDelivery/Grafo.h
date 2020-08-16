#ifndef GRAFO_H
#define GRAFO_H
#include <Vertice.h>
#include <QDebug>
#include <QQueue>
#include <caminoRecorrido.h>

class Grafo{

public:
    int size = 0;
    double totalPeso = 0;
    QList<Vertice*> vertices;
    QList<caminoRecorrido*> caminosRecorridos;
    QString prof, anch;
    Grafo();
    void insertarVertice(QString);
    bool insertarArista(QString,QString,bool,double,double,double);
    void imprimir();
    Vertice * buscarVertice(QString);
    void visitarAdyacentes(QString);
    void visitarAdyacentesConexo(QString);
    void profundidad(QString);
    void anchura(QString);
    bool conexo ();
    void ordenarAristas(int);
    void ordenarCaminosRecorridos();
    QString dijkstra(QString);
    void limpiarVisitados();
    bool visitadoVertice(QString);
    void visitarVertice(QString);
    void printAllPaths(QString, QString, int);
    void printAllPathsAux(QString, QString, QList<QString>, int);
};

#endif // GRAFO_H
