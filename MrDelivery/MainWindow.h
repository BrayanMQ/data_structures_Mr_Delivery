#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Datos.h>
#include <QMessageBox>
#include <Thread_JSON.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Datos * datos;
    Thread_JSON * tJSON;
    int recorrerCaminos;
    double pesoTotal;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void agregarDatos(QString);

private slots:
    void on_btn_VerGrafo_clicked();

    void on_btn_profundidad_clicked();

    void on_btn_anchura_clicked();

    void on_btn_HayCamino_clicked();

    void on_btn_CostosDesde1_clicked();

    void on_btn_CostosDesde2_clicked();

    void on_btn_CaminoOptimo_clicked();

    void on_btn_AExpaMini_clicked();

    void on_btn_avanzar_clicked();

    void on_comboBox_6_activated(int index);

    void on_btn_Activar_2_clicked();

    void on_btn_Activar_clicked();

    void on_btn_Activar_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
