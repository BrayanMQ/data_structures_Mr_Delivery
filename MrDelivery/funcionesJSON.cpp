#include "funcionesJSON.h"

QStringList funcionesJSON::obtenerListaDeArchivos(QString pCarpeta){

    QString absolute = QFileInfo("../MrDelivery").absoluteDir().absolutePath() + "/MrDelivery/" + pCarpeta;
    QStringList lista = QDir(absolute).entryList();
    return lista;
}

QVariantMap funcionesJSON::readJson(QString pFileName){

    QFile file_obj(pFileName);
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<<pFileName;
        exit(1);
    }

    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    auto json_doc=QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        exit(2);
    }
    if(!json_doc.isObject()){
        qDebug()<<"JSON is not an object.";
        exit(3);
    }

    QJsonObject json_obj=json_doc.object();

    if(json_obj.isEmpty()){
        qDebug()<<"JSON object is empty.";
        exit(4);
    }

    QVariantMap json_map = json_obj.toVariantMap();

    return json_map;


}
