#include "GrafoMatriz.h"

// agregar vertice
void GrafoMatriz::agregarVertice(int v)
{
     // si hay campo y v no est'a en el grafo
   if (cantidadVertices < max && indexOfVertice(v) == -1){
        vertices[cantidadVertices] = v;
        cantidadVertices++;
   }
}

// index de un vertice
 int GrafoMatriz::indexOfVertice(int v)
    {
        for (int i = 0; i < cantidadVertices; i++) {
            if (vertices[i] == v)
                return i;
        }

        return -1;
    }
// agregar arista
    void GrafoMatriz::agregarArista(int origen, int destino, int peso)
    {
        int orig = indexOfVertice(origen);
        int dest = indexOfVertice(destino);

        if (orig != -1 && dest != -1)
        {
            matriz[dest][orig] = peso;
        }
    }

// imprimir

 void GrafoMatriz::imprimir()
    {
        qDebug()<<" \t";
        for (int i = 0; i < cantidadVertices; i++) {
            qDebug() <<vertices[i]<<"\t";
        }

        qDebug() <<endl;

        for (int i = 0; i < cantidadVertices; i++) {
            qDebug() <<vertices[i]<<"\t";
            for (int j = 0; j < cantidadVertices; j++) {

                qDebug() << matriz[i][j]<< "\t";
            }
            qDebug() << endl;
        }
    }

//limpiar visitados
void GrafoMatriz::limpiarVisitados()
{
     for (int i=0; i < cantidadVertices;i++)
         visitados[i] = false;
}

 // min vertice
    int GrafoMatriz::minVertex (int * distanciasCortas)
    {
        int x = 999999;
        int y = -1;
        // RECORRE EL ARREGLO DE DISTANCIAS CORTAS BUSCANDO EL MENOR NO VISITADO
        for (int i = 0; i < cantidadVertices; i++) {
            qDebug() <<distanciasCortas[i] << "   ";
            // CONDICION PARA OBTENER NO VISITADO Y EL MENOS DE TODOS
            if (!visitados[i] && distanciasCortas[i] < x)
            {
                y = i;
                x = distanciasCortas[i];
            }
        }
        qDebug() <<"min: " << y << "  valor = " << x <<endl;
        return y;// RETORNA LA POSICION DEL MENOR
    }

//-----------------------------------------
//dijkstra
   int* GrafoMatriz::dijkstra(int v) {
        // arreglo para llevar los nodos visitados
        limpiarVisitados();
        // arreglo que almacena las distancias más cortas desde el vertice
        int distanciasCortas[100];
        // obtiene el índice del vertice en la matriz
        int node = indexOfVertice(v);
        // coloca visitado el nodo inicial
        visitados[node] = true;
        //coloca pos node en cero, pues es el inicio
        distanciasCortas[node] = 0;


// desde 1, porque cero ya tiene valor cero,
// pues las distancia inicial es de x a x, = 0
// para cada posición en distancias cortas, va
// colocando el peso si hay arista entre el
// nodo inicial y los demás, sino, infinito
        for (int i = 1; i < cantidadVertices; i++) {
            if (matriz[i][node] != 0)
            // como sí hay camino, coloca el peso
                distanciasCortas[i] = matriz[i][node];
            else /// si no, infinito
                distanciasCortas[i] = 999999;
        }

        // no considera el primero pues es el primer nodo distancia = 0
        for (int i = 0; i < (cantidadVertices - 1); i++){
            // obtiene el menor del arreglo,
            // mientras no visitado
            int next = minVertex(distanciasCortas);
            visitados[next] = true;
            //
            for (int j = 0; j < cantidadVertices; j++) {
                // calcula el ultimo más corto (NEXT)
                //  + cada arista ady a NEXT
                int d = distanciasCortas[next] + matriz[j][next];
// si en la pos del vertice no visitado y hay
// camino a la arista se coloca en distancias
// cortas de arista la suma del menor más el
// peso de arista, para ver cual es menor, si no
// quedo el más corto inicial
                if (distanciasCortas[j] > d && matriz[j][next] > 0) {
// como d es menor, se coloca ese valor, que es sumando
// el camino acumulado + arista adyacente a next
                    distanciasCortas[j] = distanciasCortas[next] + matriz[j][next];
                }
            }
        }

        for (int i = 0; i < cantidadVertices; i++)
            qDebug() << distanciasCortas[i]<<"   ";

            qDebug() <<endl;

        return distanciasCortas;
    }
