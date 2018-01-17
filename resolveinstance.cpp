#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "resolveinstance.h"
#include "ui_resolveinstance.h"
#include "workermip1.h"
#include "workermip2.h"
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

        int dossier = 0;
        string cheminDossier = "ResultatGenere/resultatMip1-"+(relativePath.fileName().right(relativePath.fileName().size()-8)).toStdString();

        QDir *repertoire = new QDir(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));

        //J'ai limité à 1000 sous-dossiers différents
        while (repertoire->exists() && dossier < 1000){
            dossier++;
            repertoire->setPath(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));
        }

        repertoire->mkpath(".");

        QString fichierResultat = QString::fromStdString(cheminDossier+"/"+to_string(dossier)+"/resultatMip1-"+(relativePath.fileName().right(relativePath.fileName().size()-8)).toStdString());


        processPlneMIP1(fichierInstance, fichierResultat);

        accept();
    }
    if(this->ui->typeResolutionComboBox->currentText() == "Résolution exacte indéxée jobs"){
        QString fichierInstance = this->ui->choisirFichierLineEdit->text();
        QFileInfo relativePath(fichierInstance);

        int dossier = 0;
        string cheminDossier = "ResultatGenere/resultatMip2-"+(relativePath.fileName().right(relativePath.fileName().size()-8)).toStdString();

        QDir *repertoire = new QDir(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));

        //J'ai limité à 1000 sous-dossiers différents
        while (repertoire->exists() && dossier < 1000){
            dossier++;
            repertoire->setPath(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));
        }

        repertoire->mkpath(".");

        QString fichierResultat = QString::fromStdString(cheminDossier+"/"+to_string(dossier)+"/resultatMip2-"+(relativePath.fileName().right(relativePath.fileName().size()-8)).toStdString());

        processPlneMIP2(fichierInstance, fichierResultat);

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

void ResolveInstance::processPlneMIP2(QString filename, QString fileresult)
{
    QThread* thread = new QThread;
    //cout << filename << " " << fileresult << endl;
    WorkerMip2* workerMip2 = new WorkerMip2(filename, fileresult);
    workerMip2->moveToThread(thread);
    connect(workerMip2, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerMip2, SLOT (process()));
    connect(workerMip2, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerMip2, SIGNAL (finished()), workerMip2, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}


void ResolveInstance::on_annulerPushButton_clicked()
{
    reject();
}
