#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generateinstance.h"
#include "resolveinstance.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionG_n_rer_des_instances_triggered()
{
    GenerateInstance generateInstance;
    if(generateInstance.exec()==QDialog::Accepted)
    {
        generateInstance.reject();
    }
}

void MainWindow::on_actionQuitter_l_application_triggered()
{
    close();
}

void MainWindow::on_actionInstances_multi_machines_triggered()
{
    ResolveInstance resolveInstance;
    if(resolveInstance.exec()==QDialog::Accepted)
    {
        resolveInstance.reject();
    }
    //Ceci fonctionne et c'est interressant
    //system("./plne instance-300-1-100.data resultatPlne-300-1-100.data");
}
