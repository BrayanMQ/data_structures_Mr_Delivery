#include "Thread_JSON.h"

void Thread_JSON::run(){

    while(true){

        QStringList grafos = this->fJSON->obtenerListaDeArchivos("JSON");
        if (grafos.size()>2){

            for (int i = 2;i<grafos.size();i++) {

                QString nArchivo = grafos[i];
                QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/JSON/"+nArchivo;
                QVariantMap infoGrafo = this->fJSON->readJson(absolute);


            }

        }else{
            sleep(2);
        }

        sleep(1);
    }

}
