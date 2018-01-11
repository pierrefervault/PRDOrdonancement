#include "generateinstance.h"
#include "ui_generateinstance.h"
#include <QDir>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <random>

using namespace std;

GenerateInstance::GenerateInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateInstance)
{
    ui->setupUi(this);
}

GenerateInstance::~GenerateInstance()
{
    delete ui;
}

void GenerateInstance::on_okPushButton_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int numInstance;
    int numJob;
    int numRessource;
    int numMachine;

    int dossier = 0;
    string cheminDossier = "InstanceGeneree/instance-"+this->ui->nbrJobsLineEdit->text().toStdString()+
            "-"+this->ui->nbrRessourcesLineEdit->text().toStdString()+"-"+this->ui->nbrMachinesLineEdit->text().toStdString();

    QDir *repertoire = new QDir(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));

    cout << dossier << endl;

    cout << repertoire->path().toStdString() << endl;

    //J'ai limité à 1000 sous-dossiers différents
    while (repertoire->exists() && dossier < 1000){
        dossier++;
        repertoire->setPath(QString::fromStdString(cheminDossier+"/"+to_string(dossier)));
    }

    repertoire->mkpath(".");

    for(numInstance = 0; numInstance < this->ui->nbrInstancesLineEdit->text().toInt(); numInstance++){


        ofstream fichier(cheminDossier+"/"+to_string(dossier)+"/instance"+to_string(numInstance)+"-"+this->ui->nbrJobsLineEdit->text().toStdString()+"-"+this->ui->nbrRessourcesLineEdit->text().toStdString()
                         +"-"+this->ui->nbrMachinesLineEdit->text().toStdString()+".data", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

        if(fichier){

            fichier << this->ui->nbrJobsLineEdit->text().toStdString() << " " << this->ui->nbrRessourcesLineEdit->text().toStdString()
                    << " " << this->ui->nbrMachinesLineEdit->text().toStdString() << endl;

            for (numMachine = 0; numMachine < this->ui->nbrMachinesLineEdit->text().toInt(); numMachine++){

                for (numRessource = 0; numRessource < this->ui->nbrRessourcesLineEdit->text().toInt(); numRessource++){

                    fichier << "1000";

                    if (numRessource != this->ui->nbrRessourcesLineEdit->text().toInt()-1){
                        fichier << " ";
                    }
                }

                fichier << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> dis(this->ui->instantDebutLineEdit->text().toInt(),
                                                this->ui->instantFinLineEdit->text().toInt() - 1);

            for (numJob = 0; numJob < this->ui->nbrJobsLineEdit->text().toInt(); numJob++){
                int startTime = dis(rd);
                std::uniform_int_distribution<> disFinish(startTime + 1, this->ui->instantFinLineEdit->text().toInt());
                int finishTime = disFinish(rd);
                fichier << numJob << "\t" << startTime << "\t" << finishTime << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> disRessource(1, 1000);

            for (numJob = 0; numJob < this->ui->nbrJobsLineEdit->text().toInt(); numJob++){
                for (numRessource = 0; numRessource < this->ui->nbrRessourcesLineEdit->text().toInt(); numRessource++){
                    fichier << disRessource(rd);
                    if (numRessource != this->ui->nbrRessourcesLineEdit->text().toInt()-1){
                        fichier << " ";
                    }
                }
                fichier << endl;
            }
            fichier.close();
        }
        else cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    accept();
}

void GenerateInstance::on_annulerPushButton_clicked()
{
    reject();
}
