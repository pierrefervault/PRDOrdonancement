#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "resolveinstance.h"
#include "ui_resolveinstance.h"
#include "workermip1.h"
#include <iostream>

using namespace std;

ResolveInstance::ResolveInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolveInstance)
{
    ui->setupUi(this);
}

ResolveInstance::~ResolveInstance()
{
    delete ui;
}

void ResolveInstance::on_choisirFichierPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Instance file"), "", tr("Instance Files (*.data)"));
    this->ui->choisirFichierLineEdit->setText(fileName);
}

void ResolveInstance::on_validerPushButton_clicked()
{
    if(this->ui->typeResolutionComboBox->currentText() == "Résolution exacte indéxée temps"){
        QString fichierInstance = this->ui->choisirFichierLineEdit->text();
        QFileInfo relativePath(fichierInstance);
        QString fichierResultat = "ResultatGenere/resultatPlne"+(relativePath.fileName().right(relativePath.fileName().size()-8));

        //cout << executablePlne.toStdString() << " " << fichierInstance.toStdString() << " " << fichierResultat.toStdString() << endl;

        //cout << fichierInstance.toStdString() << " " << fichierResultat.toStdString() << endl;
        processPlneMIP1(fichierInstance, fichierResultat);

        accept();
    }
}

void ResolveInstance::processPlneMIP1(QString filename, QString fileresult)
{
    QThread* thread = new QThread;
    //cout << filename << " " << fileresult << endl;
    WorkerMip1* workerMip1 = new WorkerMip1(filename, fileresult);
    workerMip1->moveToThread(thread);
    connect(workerMip1, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerMip1, SLOT (process()));
    connect(workerMip1, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerMip1, SIGNAL (finished()), workerMip1, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void ResolveInstance::on_annulerPushButton_clicked()
{
    reject();
}
