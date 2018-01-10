#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "generateinstance.h"

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
