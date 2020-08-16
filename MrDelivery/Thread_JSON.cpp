#include "Thread_JSON.h"

void Thread_JSON::run(){

    while(true){

        QStringList grafos = this->datos->fJSON->obtenerListaDeArchivos("JSON");
        if (grafos.size()>2){

            for (int i = 2;i<grafos.size();i++) {

                QString nArchivo = grafos[i];
                QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/JSON/"+nArchivo;
                QVariantMap infoGrafo = this->datos->fJSON->readJson(absolute);


                if (!infoGrafo.isEmpty()) {

                    QJsonArray vertices = infoGrafo["vertices"].toJsonArray();

                    Grafo * nuevo = new Grafo();
                    GrafoMatriz * nuevo2 = new GrafoMatriz();
                    for(int i = 0; i<vertices.size(); i++){ //LEER VERTICES DEL JSON

                        QString nombreVertice = vertices[i].toString();
                        nuevo->insertarVertice(nombreVertice);
                        nuevo2->agregarVertice(nombreVertice);

                    }

                    QJsonArray aristas = infoGrafo["aristas"].toJsonArray();
                    bool validar = true;


                    foreach (const QJsonValue & v, aristas){ //LEER ARISTAS DEL JSON
                        try {

                            QString origen = v.toObject().value("origen").toString();
                            QString destino = v.toObject().value("destino").toString();
                            bool activo = v.toObject().value("activo").toBool();
                            double costo = 0.0;
                            double km = 0.0;
                            double minutos = 0.0;

                            if (v.toObject().value("costo").toDouble() == 0 || v.toObject().value("km").toDouble() == 0 || v.toObject().value("minutos").toDouble() == 0) {
                                QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Error/"+nArchivo;
                                this->datos->fJSON->moverArchivo(absolute, direccionNueva); //MUEVE EL ARCHIVO A ERRORES
                                validar = false;
                                break;
                            }

                            costo = v.toObject().value("costo").toDouble();
                            km = v.toObject().value("km").toDouble();
                            minutos = v.toObject().value("minutos").toDouble();

                            validar = nuevo->insertarArista(origen,destino,activo,costo,km,minutos);
                            nuevo2->agregarArista(origen,destino,activo,costo,km,minutos);

                            if (!validar) {

                                 QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Error/"+nArchivo;
                                 this->datos->fJSON->moverArchivo(absolute, direccionNueva); //MUEVE EL ARCHIVO A ERRORES
                                 break;

                            }


                        } catch (...) {

                            QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Error/"+nArchivo;
                            this->datos->fJSON->moverArchivo(absolute, direccionNueva); //MUEVE EL ARCHIVO A ERRORES
                            validar = false;
                            break;

                        }

                    }

                    if (validar) {
                        this->datos->colaGrafo.enqueue(nuevo);
                        this->datos->colaGrafoMatriz.enqueue(nuevo2);

                        QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Cargados/"+nArchivo;
                        this->datos->fJSON->moverArchivo(absolute, direccionNueva);//MUEVE EL ARCHIVO A CARGADOS
                    }


                }  else {

                    QString direccionNueva = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/Error/"+nArchivo;
                    this->datos->fJSON->moverArchivo(absolute, direccionNueva);//MUEVE EL ARCHIVO A ERRORES

                }
            }

        }else{
            sleep(2);
        }
        emit datosCola("EN COLA: "+QString::number(this->datos->colaGrafo.size()));

        sleep(1);
    }

}
