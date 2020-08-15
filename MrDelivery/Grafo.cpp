#include "Grafo.h"

Grafo::Grafo()
{
    this->prof = "";
    this->anch = "";
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

void Grafo::insertarArista(QString origen, QString destino, bool pActivo, double costo, double km, double min){


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
            Arista * nuevo = new Arista(origen, destino, pActivo, costo, km, min);
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


// visitar vertice
void Grafo::visitarVertice(QString dato)
{
     Vertice * tmp = buscarVertice(dato);

     if (tmp != NULL){
        tmp->visitado = true;
     }
}

// visitar vertice
bool Grafo::visitadoVertice(QString dato){
     Vertice * tmp = buscarVertice(dato);

     if (tmp != NULL)
        return tmp->visitado;
     else
         return false;
}

// limpiar visitados
void Grafo::limpiarVisitados(){

     for (int i = 0; i<this->vertices.size(); i++) {
         this->vertices[i]->visitado = false;
     }
}

void Grafo::visitarAdyacentes(QString nodo){
     // visita el nodo
     visitarVertice(nodo);
     this->prof += nodo+" -> " ;

     // busca el vertice para recorrer aristas
     Vertice * tmp = buscarVertice(nodo);

     if (tmp != NULL)
     {

        for (int i = 0; i<tmp->aristas.size(); i++) {

            // si no esta visitado
          if (visitadoVertice(tmp->aristas[i]->destino)==false){
              visitarAdyacentes(tmp->aristas[i]->destino);
          }
        }
     }
}

// PROFUNDIDAD - Recorrido por profundidad

void Grafo::profundidad(QString v)
{
    this->prof = "";
    Vertice * tmp = buscarVertice(v);

    if(tmp!=NULL){

        int pos = vertices.indexOf(tmp);

        for (int i = pos; i<this->vertices.size(); i++) {

            if (!tmp->visitado){
                visitarAdyacentes(this->vertices[i]->nombre);
            }

        }

        limpiarVisitados();

    }
}

// ANCHURA - recorrido anchura
//se le da el vertice de inicio
void Grafo::anchura(QString v){
    this->anch = "";
     Vertice * tmp = buscarVertice(v);

     if (tmp!=NULL) {
         this->anch += tmp->nombre+" -> " ;
         visitarVertice(tmp->nombre);// marca el primer nodo
         QQueue<QString> cola;
         // mete a la cola los adyacentes del nodo inicial

         for (int i = 0; i<tmp->aristas.size(); i++) {
             // encola
            cola.enqueue(tmp->aristas[i]->destino);
            // visita el nodo
            visitarVertice(tmp->aristas[i]->destino);
         }

         // mientras no se vacíe la cola
        while(!cola.isEmpty())
        {
            // trabaja con el primero de la cola
            QString actual = cola.dequeue();
            visitarVertice(actual);
            // imprime el vertice
            this->anch += actual+" -> ";
            // para cada arista del vertice en la cola
            // va a meter a la cola los adyacentes
            Vertice * nodoCola = this->buscarVertice(actual);

            for (int i = 0; i<nodoCola->aristas.size(); i++) {
                // si no se ha visitado, se mete en cola
                if (visitadoVertice(nodoCola->aristas[i]->destino) == false)
                {
                   visitarVertice(nodoCola->aristas[i]->destino);
                   cola.enqueue(nodoCola->aristas[i]->destino);
                }
            }

        }
        limpiarVisitados();
     }

}

bool Grafo::conexo(){

    bool validar = false;

    for (int j = 0;j<this->vertices.size();j++) {

        this->size = 0;

        Vertice * tmp = this->vertices[j];

        if(tmp!=NULL){

            int pos = vertices.indexOf(tmp);

            for (int i = pos; i<this->vertices.size(); i++) {

                if (!tmp->visitado){
                    visitarAdyacentesConexo(this->vertices[i]->nombre);
                }

            }

            limpiarVisitados();

        }
        qDebug()<<this->size;
        if (this->vertices.size() == this->size){
            validar = true;
            break;
        }

    }

    return validar;
}

void Grafo::visitarAdyacentesConexo(QString nodo){

    // visita el nodo
    visitarVertice(nodo);
    this->size++;

    // busca el vertice para recorrer aristas
    Vertice * tmp = buscarVertice(nodo);

    if (tmp != NULL)
    {

       for (int i = 0; i<tmp->aristas.size(); i++) {

           // si no esta visitado
         if (visitadoVertice(tmp->aristas[i]->destino)==false){
             visitarAdyacentesConexo(tmp->aristas[i]->destino);
         }
       }
    }
}

QString Grafo::dijkstra(QString v){
    QString mensaje = "";

    Vertice * tmp = buscarVertice(v);
    if (!tmp->visitado){
        mensaje += tmp->nombre+" -> ";
        tmp->visitado = true;
    }

    Vertice * tmp2 = NULL;

    for (int i = 0;i<tmp->aristas.size();i++) {

        tmp2 = buscarVertice(tmp->aristas[i]->destino);
        if (!tmp2->visitado)
            mensaje += dijkstra(tmp2->nombre);

    }


    return mensaje;
}

void Grafo::ordenarAristas(QString type){

    for (int w = 0;w<vertices.size();w++){

        int x = this->vertices[w]->aristas.size();
        for (int i = 0; i<x; i++){
            int min = i;
            for (int j = i+1; j<x; j++){
                if(this->vertices[i]->aristas[j]->costo<this->vertices[i]->aristas[j]->costo){
                    min = j;
                }
            }

            this->vertices[w]->aristas.swapItemsAt(min, i);
        }
    }

}






