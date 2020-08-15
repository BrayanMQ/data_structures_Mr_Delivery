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
    this->setFixedSize(1100,600);

    this->datos = new Datos();
    this->tJSON = new Thread_JSON(this->datos);
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
    if (this->ui->comboBox_2->currentIndex() == 0){

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


                this->datos->grafo = tmp;
                this->datos->grafoMatriz = tmp2;

                for (int i = 0;i<tmp->vertices.size();i++) {
                    this->ui->comboBox->addItem(tmp->vertices[i]->nombre);
                    this->ui->comboBox_3->addItem(tmp->vertices[i]->nombre);
                    this->ui->comboBox_4->addItem(tmp->vertices[i]->nombre);
                    this->ui->comboBox_5->addItem(tmp->vertices[i]->nombre);
                    this->ui->comboBox_7->addItem(tmp->vertices[i]->nombre);
                }
            }
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("No hay grafos para desencolar");
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(msgBox.Critical);
            msgBox.exec();
        }
    }
    this->ui->textBrowser->setText("\t\t##GRAFO##\t\t\n\n");
    this->ui->textBrowser->append(this->datos->grafoMatriz->imprimir());

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
        msgBox.setText("Debe desencolar un grafo primero");
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
            msgBox.setText("El grafo es conexo");
            msgBox.setWindowTitle("Información");
            msgBox.setIcon(msgBox.Information);
            msgBox.exec();
        }else{
            msgBox.setText("El grafo es disconexo");
            msgBox.setWindowTitle("Información");
            msgBox.setIcon(msgBox.Information);
            msgBox.exec();
        }

    }else{
        msgBox.setText("Debe desencolar un grafo primero");
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

        mensaje = this->datos->grafo->dijkstra(this->ui->comboBox_3->currentText());
        this->ui->textBrowser_2->setText("          ##COSTOS DESDE: "+this->ui->comboBox_3->currentText()+"##\n\n");
        this->ui->textBrowser_2->append(mensaje.remove(mensaje.size()-3,3));

    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

void MainWindow::on_btn_CostosDesde2_clicked()
{
    int index = this->ui->comboBox_6->currentIndex();
    int contador = 0;

    if (!this->datos->grafo->vertices.isEmpty()){

        this->datos->grafo->printAllPaths(this->ui->comboBox_4->currentText(), this->ui->comboBox_5->currentText(), index);

        QString mensaje = "";
        this->datos->grafo->ordenarCaminosRecorridos(); //ORDENA EL PESO DE LOS CAMINOS RECORRIDOS DE MENOR A MAYOR

        for (int i = 0; i <this->datos->grafo->caminosRecorridos.size(); i++) {
            contador += i;
            switch (index) {
                case 0:
                    mensaje += "Opción #" + QString::number(i+1) + " " +this->datos->grafo->caminosRecorridos[i]->camino
                            + ". \nCosto Total: " + QString::number(this->datos->grafo->caminosRecorridos[i]->pesoTotal) + "\n\n";
                    break;
                case 1:
                    mensaje += "Opción #" + QString::number(i+1) + " " +this->datos->grafo->caminosRecorridos[i]->camino
                            + ". \nKilómetros Totales: " + QString::number(this->datos->grafo->caminosRecorridos[i]->pesoTotal) + "\n\n";
                    break;
                case 2:
                    mensaje += "Opción #" + QString::number(i+1) + " " +this->datos->grafo->caminosRecorridos[i]->camino
                            + ". \nTiempo Total: " + QString::number(this->datos->grafo->caminosRecorridos[i]->pesoTotal) + "\n\n";
                    break;
            }

        }

        this->ui->textBrowser_2->setText(mensaje);
        this->ui->comboBox->clear();

        for (int i = 1; i <= contador; i++) { //RELLENA EL COMBOBOX CON LAS OPCIONES

            this->ui->comboBox->addItem(QString::number(i));

        }


    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero");
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

        QString mensaje = "";
        this->datos->grafo->ordenarCaminosRecorridos(); //ORDENA EL PESO DE LOS CAMINOS RECORRIDOS DE MENOR A MAYOR

            switch (index) {
                case 0:
                    mensaje += "Camino óptimo:" + this->datos->grafo->caminosRecorridos[0]->camino
                            + ". \nCosto Total: " + QString::number(this->datos->grafo->caminosRecorridos[0]->pesoTotal) + "\n\n";
                    break;
                case 1:
                    mensaje += "Camino óptimo: " + this->datos->grafo->caminosRecorridos[0]->camino
                            + ". \nKilómetros Totales: " + QString::number(this->datos->grafo->caminosRecorridos[0]->pesoTotal) + "\n\n";
                    break;
                case 2:
                    mensaje += "Camino óptimo:" + this->datos->grafo->caminosRecorridos[0]->camino
                            + ". \nTiempo Total: " + QString::number(this->datos->grafo->caminosRecorridos[0]->pesoTotal) + "\n\n";
                    break;
            }

        this->ui->textBrowser_2->setText(mensaje);
        this->ui->comboBox->clear();

    }else{
        QMessageBox msgBox;
        msgBox.setText("Debe desencolar un grafo primero");
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}
