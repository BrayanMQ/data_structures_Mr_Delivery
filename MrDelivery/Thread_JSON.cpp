#include "Thread_JSON.h"

void Thread_JSON::run(){

    while(true){

        QStringList grafos = this->datos->fJSON->obtenerListaDeArchivos("JSON");
        if (grafos.size()>2){

            for (int i = 2;i<grafos.size();i++) {

                QString nArchivo = grafos[i];
                QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/JSON/"+nArchivo;
                QVariantMap infoGrafo = this->datos->fJSON->readJson(absolute);

                QJsonArray vertices = infoGrafo["vertices"].toJsonArray();

                Grafo * nuevo = new Grafo();
                GrafoMatriz * nuevo2 = new GrafoMatriz();
                for(int i = 0; i<vertices.size(); i++){ //LEER VERTICES DEL JSON

                    QString nombreVertice = vertices[i].toString();
                    nuevo->insertarVertice(nombreVertice);
                    nuevo2->agregarVertice(nombreVertice);

                }

                QJsonArray aristas = infoGrafo["aristas"].toJsonArray();


                foreach (const QJsonValue & v, aristas){ //LEER ARISTAS DEL JSON

                    QString origen = v.toObject().value("origen").toString();
                    QString destino = v.toObject().value("destino").toString();
                    bool activo = v.toObject().value("activo").toBool();
                    double costo = v.toObject().value("costo").toDouble();
                    double km = v.toObject().value("km").toDouble();
                    double minutos = v.toObject().value("minutos").toDouble();


                    nuevo->insertarArista(origen,destino,activo,costo,km,minutos);
                    nuevo2->agregarArista(origen,destino,activo,costo,km,minutos);

                }

                //grafo->imprimir();
                //grafo->profundidad("50");
                //grafo->anchura("40");
                //grafoMatriz->imprimir();
                this->datos->colaGrafo.enqueue(nuevo);
                this->datos->colaGrafoMatriz.enqueue(nuevo2);

                QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Cargados/"+nArchivo;
                this->datos->fJSON->moverArchivo(absolute, direccionNueva);


            }

        }else{
            sleep(2);
        }

        sleep(1);
    }

}
