#include "funcionesJSON.h"

QStringList funcionesJSON::obtenerListaDeArchivos(QString pCarpeta){

    QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/" + pCarpeta;
    QStringList lista = QDir(absolute).entryList();
    return lista;
}

void funcionesJSON::moverArchivo(QString pDireccionAntigua, QString pDireccionNueva){

    QFile archivo(pDireccionNueva);
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        QFile::rename(pDireccionAntigua, pDireccionNueva);

    }else{
        archivo.close();
        QFile::remove(pDireccionNueva);
        QFile::rename(pDireccionAntigua, pDireccionNueva);
    }

}

QVariantMap funcionesJSON::readJson(QString pFileName){

    QFile file_obj(pFileName);
    QVariantMap json_map;

    if(!file_obj.open(QIODevice::ReadOnly)){
        return json_map;
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    auto json_doc=QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull()){
        return json_map;
    }

    if(!json_doc.isObject()){
        return json_map;
    }

    QJsonObject json_obj=json_doc.object();

    if(json_obj.isEmpty()){
        return json_map;
    }

    json_map = json_obj.toVariantMap();

    return json_map;

}
