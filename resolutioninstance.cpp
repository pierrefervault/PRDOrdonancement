#include "resolutioninstance.h"
#include "ui_resolutioninstance.h"

using namespace std;

ResolutionInstance::ResolutionInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionInstance)
{
    ui->setupUi(this);
}

ResolutionInstance::~ResolutionInstance()
{
    delete ui;
}

void ResolutionInstance::on_choisirFichierPushButton_clicked()
{
    if(this->ui->fichierRadioButton->isChecked()){
        QFileDialog fenetreFichier;
        QString repertoireCourant = QDir::currentPath();
        QString fichierInstance = fenetreFichier.getOpenFileName(this,
             tr("Instance file"), "./", tr("Instance Files (*.data)"));
        if(!fichierInstance.isNull()){
            fichierInstance = fichierInstance.split(repertoireCourant+"/").at(1);
            this->ui->choisirFichierLineEdit->setText(fichierInstance);
        }
    }

    if(this->ui->dossierRadioButton->isChecked()){
        QFileDialog fenetreFichier;
        QString repertoireCourant = QDir::currentPath();
        QString fichierInstance = fenetreFichier.getExistingDirectory(this,
             tr("Instance directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(!fichierInstance.isNull()){
            fichierInstance = fichierInstance.split(repertoireCourant+"/").at(1);
            this->ui->choisirFichierLineEdit->setText(fichierInstance);
        }
    }


}

void ResolutionInstance::on_validerPushButton_clicked()
{
    if(this->ui->typeResolutionComboBox->currentText() == "Exacte indéxée temps"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                executionFichier(fichierInstance, "mip1");
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                executionDossier(fichierInstance, "mip1");
            }
            accept();
    }

    if(this->ui->typeResolutionComboBox->currentText() == "Exacte indéxée jobs"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                executionFichier(fichierInstance, "mip2");
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();
                executionDossier(fichierInstance, "mip2");
            }
            accept();
    }

    if(this->ui->typeResolutionComboBox->currentText() == "Heuristiques"){

            if(this->ui->fichierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();

                if(this->ui->triComboBox->currentText() == "CCmax basé sur la somme des ressources de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionFichier(fichierInstance, "Affectation1 CCmaxSommeRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionFichier(fichierInstance, "Affectation2 CCmaxSommeRessources");

                }

                if(this->ui->triComboBox->currentText() == "CCmax basé sur la ressource maximale de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionFichier(fichierInstance, "Affectation1 CCmaxMaxRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionFichier(fichierInstance, "Affectation2 CCmaxMaxRessources");

                }

                if(this->ui->triComboBox->currentText() == "Somme des ressources de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionFichier(fichierInstance, "Affectation1 SommeRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionFichier(fichierInstance, "Affectation2 SommeRessources");

                }

                if(this->ui->triComboBox->currentText() == "Valeur moyenne des ressources des sous-ensembles maximaux"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionFichier(fichierInstance, "Affectation1 MoyenneRessourcesSousEnsembles");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionFichier(fichierInstance, "Affectation2 MoyenneRessourcesSousEnsembles");

                }
            }

            if(this->ui->dossierRadioButton->isChecked()){
                QString fichierInstance = this->ui->choisirFichierLineEdit->text();

                if(this->ui->triComboBox->currentText() == "CCmax basé sur la somme des ressources de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionDossier(fichierInstance, "Affectation1 CCmaxSommeRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionDossier(fichierInstance, "Affectation2 CCmaxSommeRessources");

                }

                if(this->ui->triComboBox->currentText() == "CCmax basé sur la ressource maximale de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionDossier(fichierInstance, "Affectation1 CCmaxMaxRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionDossier(fichierInstance, "Affectation2 CCmaxMaxRessources");

                }

                if(this->ui->triComboBox->currentText() == "Somme des ressources de chaque job"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionDossier(fichierInstance, "Affectation1 SommeRessources");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionDossier(fichierInstance, "Affectation2 SommeRessources");

                }

                if(this->ui->triComboBox->currentText() == "Valeur moyenne des ressources des sous-ensembles maximaux"){

                    if(this->ui->affectationComboBox->currentText() == "Affectation machine par machine")
                        executionDossier(fichierInstance, "Affectation1 MoyenneRessourcesSousEnsembles");
                    if(this->ui->affectationComboBox->currentText() == "Affectation priorisant la machine avec le moins de charge")
                        executionDossier(fichierInstance, "Affectation2 MoyenneRessourcesSousEnsembles");

                }
            }
            accept();
    }
}

void ResolutionInstance::executionFichier(QString fichierInstance, QString typeResolution)
{
    QThread* thread = new QThread;
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerFichier* workerFichier = new WorkerFichier(fichierInstance, typeResolution);
    workerFichier->moveToThread(thread);
    //connect(workerFichier, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerFichier, SLOT (process()));
    connect(workerFichier, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerFichier, SIGNAL (finished()), workerFichier, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void ResolutionInstance::executionDossier(QString fichierInstance, QString typeResolution)
{
    QThread* thread = new QThread();
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerDossier* workerDossier = new WorkerDossier(fichierInstance, typeResolution);
    workerDossier->moveToThread(thread);
    //connect(workerDossier, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerDossier, SLOT (process()));
    connect(workerDossier, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerDossier, SIGNAL (finished()), workerDossier, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}


void ResolutionInstance::on_annulerPushButton_clicked()
{
    reject();
}

void ResolutionInstance::on_fichierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
    this->ui->fichierInstanceLabel->setText("Fichier d'instance :");
}

void ResolutionInstance::on_dossierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
    this->ui->fichierInstanceLabel->setText("Dossier d'instances :");
}

void ResolutionInstance::on_typeResolutionComboBox_currentIndexChanged(int index)
{
    if(this->ui->typeResolutionComboBox->currentText() == "Heuristiques"){
        this->ui->affectationComboBox->setEnabled(true);
        this->ui->typeAffectationLabel->setEnabled(true);
        this->ui->typeTriLabel->setEnabled(true);
        this->ui->triComboBox->setEnabled(true);
    }
    else{
        this->ui->affectationComboBox->setEnabled(false);
        this->ui->typeAffectationLabel->setEnabled(false);
        this->ui->typeTriLabel->setEnabled(false);
        this->ui->triComboBox->setEnabled(false);
    }
}
