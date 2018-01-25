#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "resolveinstance.h"
#include "ui_resolveinstance.h"
#include "workerfile.h"
#include "workerfolder.h"
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
    if(this->ui->fichierRadioButton->isChecked()){
        QFileDialog fileDialog;
        QString actualDirectory = QDir::currentPath();
        QString fileName = fileDialog.getOpenFileName(this,
             tr("Instance file"), "./", tr("Instance Files (*.data)"));
        if(!fileName.isNull()){
            fileName = fileName.split(actualDirectory+"/").at(1);
            this->ui->choisirFichierLineEdit->setText(fileName);
        }
    }

    if(this->ui->dossierRadioButton->isChecked()){
        QFileDialog fileDialog;
        QString actualDirectory = QDir::currentPath();
        QString fileName = fileDialog.getExistingDirectory(this,
             tr("Instance directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(!fileName.isNull()){
            fileName = fileName.split(actualDirectory+"/").at(1);
            this->ui->choisirFichierLineEdit->setText(fileName);
        }
    }


}

void ResolveInstance::on_validerPushButton_clicked()
{
    if(this->ui->typeResolutionComboBox->currentText() == "Résolution exacte indéxée temps"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFile(fichierInstance, "mip1");
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFolder(fichierInstance, "mip1");
            }
            accept();
    }

    if(this->ui->typeResolutionComboBox->currentText() == "Résolution exacte indéxée jobs"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFile(fichierInstance, "mip2");
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFolder(fichierInstance, "mip2");
            }
            accept();
    }

    if(this->ui->typeResolutionComboBox->currentText() == "Méthode heuristiques"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFile(fichierInstance, "heuristique");
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                processFolder(fichierInstance, "heuristique");
            }
            accept();
    }
}

void ResolveInstance::processFile(QString filename, QString typeOfResolution)
{
    QThread* thread = new QThread;
    //cout << filename << " " << fileresult << endl;
    WorkerFile* workerFile = new WorkerFile(filename, typeOfResolution);
    workerFile->moveToThread(thread);
    connect(workerFile, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerFile, SLOT (process()));
    connect(workerFile, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerFile, SIGNAL (finished()), workerFile, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void ResolveInstance::processFolder(QString filename, QString typeOfResolution)
{
    QThread* thread = new QThread();
    //cout << filename << " " << fileresult << endl;
    WorkerFolder* workerFolder = new WorkerFolder(filename, typeOfResolution);
    workerFolder->moveToThread(thread);
    connect(workerFolder, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerFolder, SLOT (process()));
    connect(workerFolder, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerFolder, SIGNAL (finished()), workerFolder, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}


void ResolveInstance::on_annulerPushButton_clicked()
{
    reject();
}

void ResolveInstance::on_fichierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
}

void ResolveInstance::on_dossierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
}
