#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include <QDebug>
#include <Arista.h>

class GrafoMatriz
{
public:
    int max;
    Arista * matriz[100][100];
    QString vertices[100];
    bool activos[100];
    bool visitados[100];
    int cantidadVertices;


    GrafoMatriz(){
        max = 100;
        cantidadVertices = 0;

        // inicializa arreglos
        for (int i=0; i<100; i++)
        {
            vertices[i] = "";
            visitados[i] = 0;
            activos[i] = 1;

            // para incializar matriz
            for (int j = 0; j < 100; j++)
            {
                matriz[i][j] = NULL;
            }
        }
    }

    //prototipos
    int indexOfVertice(QString);
    void agregarVertice(QString);
    void agregarArista(QString, QString, bool, double, double, double);
    QString imprimir();
    QString imprimirModificado();
    int minVertex (int[]);
    int* dijkstra(int ) ;
    void limpiarVisitados();

};

#endif // GRAFOMATRIZ_H
