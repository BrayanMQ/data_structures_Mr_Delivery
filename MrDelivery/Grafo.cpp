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

bool Grafo::insertarArista(QString origen, QString destino, bool pActivo, double costo, double km, double min){


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
             return false;
         }
       }
       else
       {
           return false;
       }
    }
    else
    {
        return false;
    }

    return true;
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

            // si el nodo no esta visitado y la arista está activa

          if (visitadoVertice(tmp->aristas[i]->destino)==false && tmp->aristas[i]->activo){
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

            if (!tmp->visitado && tmp->activo){
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

     if (tmp != NULL && tmp->activo) {
         this->anch += tmp->nombre+" -> " ;
         visitarVertice(tmp->nombre);// marca el primer nodo
         QQueue<QString> cola;
         // mete a la cola los adyacentes del nodo inicial

         for (int i = 0; i<tmp->aristas.size(); i++) {
             // encola

             //REVISA SI LA ARISTA Y EL NODO ESTÁN ACTIVOS
             if (tmp->aristas[i]->activo && buscarVertice(tmp->aristas[i]->destino)->activo) {
                 cola.enqueue(tmp->aristas[i]->destino);

                 // visita el nodo
                 visitarVertice(tmp->aristas[i]->destino);
             }


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
                // si no se ha visitado, está activo y su arista está activa, se mete en cola
                if (visitadoVertice(nodoCola->aristas[i]->destino) == false && nodoCola->aristas[i]->activo && buscarVertice(nodoCola->aristas[i]->destino))
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

                if (!tmp->visitado && tmp->activo){
                    visitarAdyacentesConexo(this->vertices[i]->nombre);
                }

            }

            limpiarVisitados();

        }
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

           // si no esta visitado y su arista está activa
         if (visitadoVertice(tmp->aristas[i]->destino)==false && tmp->aristas[i]->activo){
             visitarAdyacentesConexo(tmp->aristas[i]->destino);
         }
       }
    }
}

QString Grafo::dijkstra(QString v){
    QString mensaje = "";
    Vertice * tmp = buscarVertice(v);

    if (!tmp->visitado && tmp->activo){
        mensaje += tmp->nombre+" -> ";
        tmp->visitado = true;
    }

    Vertice * tmp2 = NULL;

    for (int i = 0;i<tmp->aristas.size();i++) {

        tmp2 = buscarVertice(tmp->aristas[i]->destino);
        if (!tmp2->visitado && tmp2->activo && tmp->aristas[i]->activo){
            mensaje += dijkstra(tmp2->nombre);
        }

    }


    return mensaje;
}

void Grafo::ordenarAristas(int type){

    for (int w = 0;w<vertices.size();w++){

        int x = this->vertices[w]->aristas.size();
        for (int i = 0; i<x; i++){
            int min = i;
            for (int j = i+1; j<x; j++){
                switch (type) {
                    case 0:
                        if(this->vertices[i]->aristas[j]->costo<this->vertices[i]->aristas[j]->costo){
                            min = j;
                        }
                        break;

                    case 1:
                        if(this->vertices[i]->aristas[j]->km<this->vertices[i]->aristas[j]->km){
                            min = j;
                        }
                        break;

                    case 2:
                        if(this->vertices[i]->aristas[j]->min<this->vertices[i]->aristas[j]->min){
                            min = j;
                        }
                        break;
                }
            }

            this->vertices[w]->aristas.swapItemsAt(min, i);
        }
    }

}

void Grafo::ordenarCaminosRecorridos(){
    //ORDENA EL PESO DE LOS CAMINOS RECORRIDOS DE MENOR A MAYOR
    int x = this->caminosRecorridos.size();
    for (int i = 0; i<x; i++){
        int min = i;
        for (int j = i+1; j<x; j++){
            if(caminosRecorridos[j]->pesoTotal<caminosRecorridos[min]->pesoTotal){
                min = j;
            }
        }
        this->caminosRecorridos.swapItemsAt(min, i);
    }


}

void Grafo::printAllPaths(QString origen, QString destino, int type){

    //LIMPIA LAS VARIABLES
    limpiarVisitados();
    this->caminosRecorridos.clear();

    QList<QString> pathList;

    pathList.append(origen);

    printAllPathsAux(origen, destino, pathList, type);
}

void Grafo::printAllPathsAux(QString u, QString destino, QList<QString> localPathList, int type){

    buscarVertice(u)->visitado = true;

    if(u == destino){

        //SE CREA EL OBJETO CAMINO RECORRIDO QUE LLEVARÁ LA INFORMACIÓN DE CADA RECORRIDO DE UN NODO A OTRO
        caminoRecorrido * camino = new caminoRecorrido();
        camino->camino = localPathList;

        //SE AGREGA EL CAMINO A LA LISTA DE CAMINOS RECORRIDOS
        this->caminosRecorridos.append(camino);


    } else {

        Vertice * tmp = buscarVertice(u);

        for (int i = 0; i<tmp->aristas.size(); i++) {

            Vertice * tmp2 = buscarVertice(tmp->aristas[i]->destino);

            if(!tmp2->visitado && tmp2->activo && tmp->aristas[i]->activo){

                localPathList.append(tmp2->nombre);
                printAllPathsAux(tmp2->nombre, destino, localPathList, type);

                localPathList.removeOne(tmp2->nombre);

            }
        }
    }

    buscarVertice(u)->visitado = false;

}

void Grafo::asignarPesosTotales(int pIndex){



    for (int i = 0; i<this->caminosRecorridos.size(); i++) {
        double pesoTotal = 0.0;
        caminoRecorrido * cR = this->caminosRecorridos[i];

        for (int j = 0; j<cR->camino.size()-1; j++) {

            Vertice * vertTMP = buscarVertice(cR->camino[j]);


            Arista * aristaTMP = vertTMP->buscarArista(cR->camino[j+1]);

            switch (pIndex) {
                case 0:
                    pesoTotal += aristaTMP->costo;
                    break;
                case 1:
                    pesoTotal += aristaTMP->km;
                    break;
                case 2:
                    pesoTotal += aristaTMP->min;
                    break;
            }

        }

        cR->pesoTotal = pesoTotal;
    }



}






