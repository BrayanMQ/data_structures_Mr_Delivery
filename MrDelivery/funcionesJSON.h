#ifndef FUNCIONESJSON_H
#define FUNCIONESJSON_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>

class funcionesJSON
{
public:
    funcionesJSON(){

    }

    QVariantMap readJson(QString);
    QStringList obtenerListaDeArchivos(QString);
    void moverArchivo(QString, QString);
};

#endif // FUNCIONESJSON_H
