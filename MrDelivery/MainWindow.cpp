#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //PROPIEDADES DE LA VENTANA PRINCIPAL
    this->setWindowTitle("MrDelivery");
    this->setWindowFlags(Qt::WindowMaximizeButtonHint);
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    this->setFixedSize(1400,600);

    this->datos = new Datos();
    this->tJSON = new Thread_JSON(this->datos);
    this->recorrerCaminos = 0;
    this->pesoTotal = 0.0;
    this->tJSON->start();

    connect(this->tJSON,SIGNAL(datosCola(QString)),this,SLOT(agregarDatos(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::agregarDatos(QString dato){
    this->ui->lbl_Cola->setText(dato);
}

void MainWindow::on_btn_VerGrafo_clicked()
{

    if (!this->datos->colaGrafo.isEmpty()){
        Grafo * tmp = this->datos->colaGrafo.dequeue();
        GrafoMatriz * tmp2 = this->datos->colaGrafoMatriz.dequeue();
        if (tmp != NULL && tmp2 != NULL){

            //LIMPIEZA DE LOS COMBOBOX
            this->ui->comboBox->clear();
            this->ui->comboBox_3->clear();
            this->ui->comboBox_4->clear();
            this->ui->comboBox_5->clear();
            this->ui->comboBox_7->clear();
            this->ui->comboBox_8->clear();
            this->ui->comboBox_9->clear();
            this->ui->textBrowser->clear();
            this->ui->textBrowser_2->clear();
            this->ui->textBrowser_3->clear();


            this->datos->grafo = tmp;
            this->datos->grafoMatriz = tmp2;

            for (int i = 0;i<tmp->vertices.size();i++) {

                //ASIGNA LAS ARISTAS
                Vertice * vertice = tmp->vertices[i];
                for (int w = 0; w<vertice->aristas.size();w++) {
                    QString msg = vertice->aristas[w]->origen + "->"+ vertice->aristas[w]->destino;
                    this->ui->comboBox_9->addItem(msg);
                }

                this->ui->comboBox->addItem(vertice->nombre);
                this->ui->comboBox_3->addItem(vertice->nombre);
                this->ui->comboBox_4->addItem(vertice->nombre);
                this->ui->comboBox_5->addItem(vertice->nombre);
                this->ui->comboBox_7->addItem(vertice->nombre);
            }
        }

        this->ui->textBrowser->setText("\t\t##GRAFO##\t\t\n\n");
        this->ui->textBrowser->append(this->datos->grafoMatriz->imprimir());

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("No hay grafos para desencolar.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }



}

void MainWindow::on_btn_profundidad_clicked()
{
    if (!this->datos->grafo->vertices.isEmpty()){
        this->datos->grafo->profundidad(this->ui->comboBox_7->currentText());
        this->ui->textBrowser_2->setText("\t##PROFUNDIDAD##\t\t\n\n");
        this->ui->textBrowser_2->append((this->datos->grafo->prof).remove(this->datos->grafo->prof.size()-3,3));
    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }

}

void MainWindow::on_btn_anchura_clicked()
{
    if (!this->datos->grafo->vertices.isEmpty()){
        this->datos->grafo->anchura(this->ui->comboBox_7->currentText());
        this->ui->textBrowser_2->setText("\t##ANCHURA##\t\t\n\n");
        this->ui->textBrowser_2->append((this->datos->grafo->anch).remove(this->datos->grafo->anch.size()-3,3));
    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_HayCamino_clicked()
{
    QMessageBox msgBox;
    if (!this->datos->grafo->vertices.isEmpty()){
        bool validar = this->datos->grafo->conexo();

        if (validar){
            msgBox.setText("El grafo es conexo.");
            msgBox.setWindowTitle("Información");
            msgBox.setIcon(msgBox.Information);
            msgBox.exec();
        }else{
            msgBox.setText("El grafo es disconexo.");
            msgBox.setWindowTitle("Información");
            msgBox.setIcon(msgBox.Information);
            msgBox.exec();
        }

    }else{
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_CostosDesde1_clicked()
{
    if (!this->datos->grafo->vertices.isEmpty()){
        QString mensaje = "";
        this->datos->grafo->limpiarVisitados();

        this->datos->grafo->ordenarAristas(this->ui->comboBox_6->currentIndex());

        this->datos->grafo->totalPeso = 0.0;
        this->datos->grafo->totalPesoString = "";
        mensaje = this->datos->grafo->dijkstra(this->ui->comboBox_3->currentText());

        this->ui->textBrowser_2->setText("          ##COSTOS DESDE: "+this->ui->comboBox_3->currentText()+"##\n\n");
        this->ui->textBrowser_2->append(mensaje.remove(mensaje.size()-3,3));

    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_CostosDesde2_clicked()
{
    int index = this->ui->comboBox_6->currentIndex();
    int contador = 0;

    //LIMPIA VARIABLE PARA RECORRER EL CAMINO SELECCIONADO POR EL USUARIO
    this->pesoTotal = 0.0;
    this->recorrerCaminos = 0;

    if (!this->datos->grafo->vertices.isEmpty()){

        this->datos->grafo->printAllPaths(this->ui->comboBox_4->currentText(), this->ui->comboBox_5->currentText(), index);
        this->datos->grafo->asignarPesosTotales(index);

        QString mensaje = "";

        this->datos->grafo->ordenarCaminosRecorridos(); //ORDENA EL PESO DE LOS CAMINOS RECORRIDOS DE MENOR A MAYOR


        if (!this->datos->grafo->caminosRecorridos.isEmpty()) {
            for (int i = 0; i <this->datos->grafo->caminosRecorridos.size(); i++) {

                QString mensajeCamino = "";
                caminoRecorrido * cR = this->datos->grafo->caminosRecorridos[i];

                for (int j = 0; j <cR->camino.size(); j++) {

                    mensajeCamino += cR->camino[j] + " -> ";

                }

                mensajeCamino.remove(mensajeCamino.size()-3, 3); //SE REMUEVE LA FLECHA FINAL

                contador++;

                switch (index) {
                    case 0:
                        mensaje += "Opción #" + QString::number(i+1) + " " + mensajeCamino
                                + ". \nCosto de gasolina Total: " + QString::number(cR->pesoTotal) + "\n\n";
                        break;
                    case 1:
                        mensaje += "Opción #" + QString::number(i+1) + " " + mensajeCamino
                                + ". \nKilómetros Totales: " + QString::number(cR->pesoTotal) + "\n\n";
                        break;
                    case 2:
                        mensaje += "Opción #" + QString::number(i+1) + " " + mensajeCamino
                                + ". \nTiempo Total: " + QString::number(cR->pesoTotal) + "en minutos.\n\n";
                        break;
                }


            }

            this->ui->textBrowser_2->setText(mensaje);
            this->ui->comboBox_8->clear();

            for (int i = 1; i <= contador; i++) { //RELLENA EL COMBOBOX CON LAS OPCIONES

                this->ui->comboBox_8->addItem(QString::number(i));

            }
        } else {

            this->ui->textBrowser_2->setText("No hay caminos disponibles.");

        }

    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }

}

void MainWindow::on_btn_CaminoOptimo_clicked()
{
    int index = this->ui->comboBox_6->currentIndex();

    if (!this->datos->grafo->vertices.isEmpty()){

        this->datos->grafo->printAllPaths(this->ui->comboBox_4->currentText(), this->ui->comboBox_5->currentText(), index);

        this->datos->grafo->asignarPesosTotales(index);

        QString mensaje = "";
        QString mensajeCamino = "";
        this->datos->grafo->ordenarCaminosRecorridos(); //ORDENA EL PESO DE LOS CAMINOS RECORRIDOS DE MENOR A MAYOR

        if (!this->datos->grafo->caminosRecorridos.isEmpty()) {

            caminoRecorrido * cR = this->datos->grafo->caminosRecorridos[0]; //OBTIENE EL PRIMERO DE LA LISTA (EL QUE MENOS PESO TIENE)

            for (int j = 0; j <cR->camino.size(); j++) {

                mensajeCamino += cR->camino[j] + " -> ";

            }

            mensajeCamino.remove(mensajeCamino.size()-3, 3); //SE REMUEVE LA FLECHA FINAL

            switch (index) {
               case 0:
                   mensaje += "Camino óptimo:" + mensajeCamino
                           + ". \nCosto de gasolina Total: " + QString::number(cR->pesoTotal) + "\n\n";
                   break;
               case 1:
                   mensaje += "Camino óptimo: " + mensajeCamino
                           + ". \nKilómetros Totales: " + QString::number(cR->pesoTotal) + "\n\n";
                   break;
               case 2:
                   mensaje += "Camino óptimo:" + mensajeCamino
                           + ". \nTiempo Total: " + QString::number(cR->pesoTotal) + "en minutos.\n\n";
                   break;
           }

            this->ui->textBrowser_2->setText(mensaje);

        } else {

                    this->ui->textBrowser_2->setText("No hay caminos disponibles.");

        }


    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_AExpaMini_clicked()
{
    if (!this->datos->grafo->vertices.isEmpty()){
        QString mensaje = "";
        this->datos->grafo->limpiarVisitados();

        this->datos->grafo->ordenarAristas(this->ui->comboBox_6->currentIndex());

        mensaje = this->datos->grafo->dijkstra(this->datos->grafo->vertices[0]->nombre);
        this->ui->textBrowser_2->setText("##ÁRBOL DE EXPANSIÓN MÍNIMA##\n\n");
        this->ui->textBrowser_2->append(mensaje.remove(mensaje.size()-3,3));

    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero.");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_avanzar_clicked()
{
    if (this->ui->comboBox_8->currentText() != "") {
        if (!this->datos->grafo->caminosRecorridos.isEmpty()) {

            int index = this->ui->comboBox_8->currentIndex();
            QString msg = "";
            caminoRecorrido * cR = this->datos->grafo->caminosRecorridos[index];

            if (this->recorrerCaminos != cR->camino.size()-1) {

                msg += cR->camino[this->recorrerCaminos] + " -> " +  cR->camino[this->recorrerCaminos+1] + "\n";


                Vertice * verticeTMP = this->datos->grafo->buscarVertice(cR->camino[this->recorrerCaminos]);
                Arista * aristaTMP = verticeTMP->buscarArista(cR->camino[this->recorrerCaminos+1]);

                int index2 =  this->ui->comboBox_6->currentIndex();

                switch (index2) {
                    case 0:
                        this->pesoTotal += aristaTMP->costo;
                        msg += "Costo de gasolina de la arista: " + QString::number(aristaTMP->costo)+"\n";
                        msg += "Costo de gasolina total: " + QString::number(this->pesoTotal);
                        break;
                    case 1:
                        this->pesoTotal += aristaTMP->km;
                        msg += "Kilómetros de la arista: " + QString::number(aristaTMP->km)+"\n";
                        msg += "Kilómetros totales: " + QString::number(this->pesoTotal);
                        break;
                    case 2:
                        this->pesoTotal += aristaTMP->min;
                        msg += "Minutos de la arista: " + QString::number(aristaTMP->min)+"\n";
                        msg += "Minutos totales: " + QString::number(this->pesoTotal);
                        break;
                }


                QMessageBox msgBox;
                msgBox.setText("Realizando recorrido...");
                msgBox.setInformativeText(msg);

                QAbstractButton * pButtonYes = msgBox.addButton(tr("Avanzar"), QMessageBox::YesRole);
                msgBox.addButton(tr("Cancelar"), QMessageBox::NoRole);

                msgBox.exec();

                if (msgBox.clickedButton()==pButtonYes) {
                    this->recorrerCaminos++;
                    on_btn_avanzar_clicked();
                }

            }

              this->recorrerCaminos = 0;
              this->pesoTotal = 0;

        }else{
            QMessageBox msgBox;
            msgBox.setText("Debe buscar todos los caminos primero.");
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(msgBox.Critical);
            msgBox.exec();
        }
    }


}

void MainWindow::on_comboBox_6_activated(int index)
{
    this->ui->comboBox_8->addItem(QString::number(index)); //USELESS
    this->ui->textBrowser_2->clear();
    this->ui->comboBox_8->clear();

}

void MainWindow::on_btn_Activar_2_clicked()
{

    if (this->ui->comboBox_9->currentText() != "") {

        QString origen = "";
        QString destino = "";

        QStringList origenDestino = this->ui->comboBox_9->currentText().split("->");

        origen = origenDestino[0];
        destino = origenDestino[1];

        Vertice * verticeTMP = this->datos->grafo->buscarVertice(origen);

        if (verticeTMP->activo && this->datos->grafo->buscarVertice(destino)->activo) { //SI EL ORIGEN Y EL DESTINO ESTÁN ACTIVOS
            Arista * aristaTMP = verticeTMP->buscarArista(destino);

            int indexOrigen = this->datos->grafoMatriz->indexOfVertice(origen);
            int indexDestino = this->datos->grafoMatriz->indexOfVertice(destino);

            //CAMBIA LOS VALORES EN LOS GRAFOS

            //GRAFO
            aristaTMP->activo = !aristaTMP->activo;

            //GRAFO MATRIZ
            this->datos->grafoMatriz->matriz[indexDestino][indexOrigen]->activo = !this->datos->grafoMatriz->matriz[indexDestino][indexOrigen]->activo;

            QMessageBox msgBox;

            if (this->datos->grafoMatriz->matriz[indexDestino][indexOrigen]->activo) {
                msgBox.setText("Se ha activado la arista " + this->ui->comboBox_9->currentText() + ".");
            } else {
                msgBox.setText("Se ha desactivado la arista " + this->ui->comboBox_9->currentText() + ".");
            }

            msgBox.setWindowTitle("Información");
            msgBox.setIcon(msgBox.Information);
            msgBox.exec();

            on_btn_Activar_3_clicked();
        } else {

            QMessageBox msgBox;
            msgBox.setText("Debe activar el vértice de origen y destino antes de activar la conexión de arista correspondiente.");
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(msgBox.Critical);
            msgBox.exec();
        }


    }

}

void MainWindow::on_btn_Activar_clicked()
{

    if (this->ui->comboBox->currentText() != "") {

        Vertice * verticeTMP = this->datos->grafo->buscarVertice(this->ui->comboBox->currentText());

        //CAMBIA LOS VALORES EN LOS GRAFOS

        //GRAFO
        verticeTMP->activo = !verticeTMP->activo;
        for (int i = 0; i < verticeTMP->aristas.size(); i++) {
            verticeTMP->aristas[i]->activo = false;
        }

        for (int i = 0; i < this->datos->grafo->vertices.size(); i++) {

            Vertice * verticeTMPFOR = this->datos->grafo->vertices[i];

            for (int j = 0; j < verticeTMPFOR->aristas.size(); j++) {

                if (verticeTMPFOR->aristas[j]->destino == verticeTMP->nombre) {
                    verticeTMPFOR->aristas[j]->activo = false;
                }

            }

        }

        //GRAFO MATRIZ
        int indexVertice = this->datos->grafoMatriz->indexOfVertice(verticeTMP->nombre);
        this->datos->grafoMatriz->activos[indexVertice] = !this->datos->grafoMatriz->activos[indexVertice];

        for (int i = 0; i < this->datos->grafo->vertices.size(); i++) {

            if (this->datos->grafoMatriz->matriz[i][indexVertice] != NULL) {
                this->datos->grafoMatriz->matriz[i][indexVertice]->activo = false;
            }

            if (this->datos->grafoMatriz->matriz[indexVertice][i] != NULL) {
                this->datos->grafoMatriz->matriz[indexVertice][i]->activo = false;
            }

        }

        QMessageBox msgBox;

        if (this->datos->grafoMatriz->activos[indexVertice]) {
            msgBox.setText("Se ha activado el vértice " + this->ui->comboBox->currentText() + ".");
        } else {
            msgBox.setText("Se ha desactivado el vértice " + this->ui->comboBox->currentText() + ".");
        }

        msgBox.setWindowTitle("Información");
        msgBox.setIcon(msgBox.Information);
        msgBox.exec();

        on_btn_Activar_3_clicked();

    }

}

void MainWindow::on_btn_Activar_3_clicked()
{
    QString mensaje = this->datos->grafoMatriz->imprimir();
    this->ui->textBrowser_3->setText("\t##GRAFO MODIFICADO##\n\n");
    this->ui->textBrowser_3->append(mensaje);
}
