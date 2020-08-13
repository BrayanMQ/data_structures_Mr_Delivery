#include "Grafo.h"

Grafo::Grafo()
{

}

void Grafo::insertarVertice(QString nombre){

    Vertice * nuevo = new Vertice(nombre);
    this->vertices.append(nuevo);

}

Vertice * Grafo::buscarVertice(QString nombre){

    for (int i = 0;i<this->vertices.size();i++) {

        if (this->vertices[i]->nombre == nombre){
            return vertices[i];
        }
    }

    return NULL;
}

void Grafo::insertarArista(QString origen, QString destino, double costo, double km, double min){


    // si existe el vertice inserta
    Vertice * tmp = this->buscarVertice(origen);
    Vertice * tmpDest = this->buscarVertice(destino);
    if (tmp != NULL)
    {
       if (tmpDest != NULL)
       {
         // si la arista no existe
         Arista * arista = tmp->buscarArista(destino);
         if (arista == NULL)
         {
            Arista * nuevo = new Arista(origen,destino,costo,km,min);
            tmp->aristas.append(nuevo);
         }
         else
         {
             qDebug()<< "Arista ya existe";
         }
       }
       else
       {
           qDebug() << "Destino no existe";
       }
    }
    else
    {
        qDebug()<< "Nodo origen no existe";
    }
}

void Grafo::imprimir ()
{

    for (int i = 0;i<this->vertices.size();i++) {
        Vertice * tmp = this->vertices[i];
        qDebug()<<tmp->nombre<<": ";
        for (int w = 0;w<tmp->aristas.size();w++){
            tmp->aristas[w]->imprimir();
            qDebug()<<"     ";
        }
        qDebug()<<"\n";
    }
    qDebug()<<"\n";

}
