#include "Thread_JSON.h"

void Thread_JSON::run(){

    while(true){

        QStringList grafos = this->fJSON->obtenerListaDeArchivos("JSON");
        if (grafos.size()>2){

            for (int i = 2;i<grafos.size();i++) {

                QString nArchivo = grafos[i];
                QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/JSON/"+nArchivo;
                QVariantMap infoGrafo = this->fJSON->readJson(absolute);

                QJsonArray vertices = infoGrafo["vertices"].toJsonArray();

                for(int i = 0; i<vertices.size(); i++){ //LEER VERTICES DEL JSON

                    QString nombreVertice = vertices[i].toString();
                    this->grafo->insertarVertice(nombreVertice);
                    this->grafoMatriz->agregarVertice(nombreVertice);

                }

                QJsonArray aristas = infoGrafo["aristas"].toJsonArray();


                foreach (const QJsonValue & v, aristas){ //LEER ARISTAS DEL JSON

                    QString origen = v.toObject().value("origen").toString();
                    QString destino = v.toObject().value("destino").toString();
                    bool activo = v.toObject().value("activo").toBool();
                    double costo = v.toObject().value("costo").toDouble();
                    double km = v.toObject().value("km").toDouble();
                    double minutos = v.toObject().value("minutos").toDouble();


                    this->grafo->insertarArista(origen,destino,activo,costo,km,minutos);
                    this->grafoMatriz->agregarArista(origen,destino,activo,costo,km,minutos);

                }

                //grafo->imprimir();
                //grafo->profundidad("50");
                //grafo->anchura("40");
                grafoMatriz->imprimir();

                QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Cargados/"+nArchivo;
                this->fJSON->moverArchivo(absolute, direccionNueva);


            }

        }else{
            sleep(2);
        }

        sleep(1);
    }

}
