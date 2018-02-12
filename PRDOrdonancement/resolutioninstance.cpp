#include "resolutioninstance.h"
#include "ui_resolutioninstance.h"
#include "QCheckBox"
#include "QBoxLayout"
#include "QMessageBox"

using namespace std;

ResolutionInstance::ResolutionInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionInstance)
{
    ui->setupUi(this);
    this->pourcentageParAgent.clear();
    this->ui->agentComboBox->clear();
    this->ui->agentComboBox->addItem("Agent 1");
    this->ui->pourcentageLineEdit->setText("100");
    this->pourcentageParAgent.push_back(100);
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

    QString fichierInstance = this->ui->choisirFichierLineEdit->text();

    if (fichierInstance != NULL){
        for (int i = 0; i < this->ui->treeWidget->topLevelItemCount() ; i++){
            if (this->ui->treeWidget->topLevelItem(i)->checkState(0) == 2){

                if(this->ui->fichierRadioButton->isChecked()) executionFichier(fichierInstance, trouverMethodeResolution(i));
                if(this->ui->dossierRadioButton->isChecked()) executionDossier(fichierInstance, trouverMethodeResolution(i));

            }
            else {

                if (this->ui->treeWidget->topLevelItem(i)->childCount() != 0){
                    for(int j = 0; j < this->ui->treeWidget->topLevelItem(i)->childCount(); j++){

                        if(this->ui->treeWidget->topLevelItem(i)->child(j)->checkState(0) == 2){

                            if(this->ui->fichierRadioButton->isChecked()) executionFichier(fichierInstance, trouverMethodeResolution(i, j));
                            if(this->ui->dossierRadioButton->isChecked()) executionDossier(fichierInstance, trouverMethodeResolution(i, j));

                        }
                    }
                }
            }
        }
        accept();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Le fichier ou dossier d'instance n'est pas spécifié");
        messageBox.setFixedSize(500,200);
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

QString ResolutionInstance::trouverMethodeResolution(int indexTableau, int indexSousElement){

    if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "Resolution exacte indexée temps") return "mip1";
    if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "Resolution exacte indexée jobs") return "mip2";

    QString methodeResolution = "";

    if(indexSousElement != -1){

        if(this->ui->treeWidget->topLevelItem(indexTableau)->child(indexSousElement)->text(0) == "Affectation machine par machine")
            methodeResolution += "Affectation1";

        if(this->ui->treeWidget->topLevelItem(indexTableau)->child(indexSousElement)->text(0) == "Affectation priorisant la machine avec le moins de charge")
            methodeResolution += "Affectation2";


        if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "CCmax basé sur la somme des ressources de chaque job")
            methodeResolution += " CCmaxSommeRessources";

        if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "CCmax basé sur la ressource maximale de chaque job")
            methodeResolution += " CCmaxMaxRessources";

        if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "Somme des ressources de chaque job")
            methodeResolution += " SommeRessources";

        if (this->ui->treeWidget->topLevelItem(indexTableau)->text(0) == "Valeur moyenne des ressources des sous-ensembles maximaux")
            methodeResolution += " MoyenneRessourcesSousEnsembles";

    }

    return methodeResolution;

}

void ResolutionInstance::on_agentSpinBox_valueChanged(int arg1)
{
    this->ui->agentComboBox->clear();
    this->pourcentageParAgent.clear();

    for (int i = 1; i < this->ui->agentSpinBox->text().toInt()+1; i++){
        this->ui->agentComboBox->addItem("Agent "+QString::number(i));
        this->pourcentageParAgent.push_back(0);
    }
    this->pourcentageParAgent[0] = 100;
    this->ui->pourcentageLineEdit->setText("100");
}

void ResolutionInstance::on_agentComboBox_currentIndexChanged(int index)
{
    cout << this->pourcentageParAgent.size() << endl;
    for (unsigned int i = 0; i < this->pourcentageParAgent.size(); i++){
        cout << this->pourcentageParAgent[i] << endl;
    }
    if (this->pourcentageParAgent.size() > 0){
        this->ui->pourcentageLineEdit->setText(QString::number(this->pourcentageParAgent[index]));
    }
}

void ResolutionInstance::on_validerPourcentagePushButton_clicked()
{
    int sommePourcentage = 0;
    for (unsigned int i = 0; i < this->pourcentageParAgent.size(); i++){

        if (i == this->ui->agentComboBox->currentIndex()){
            sommePourcentage += this->ui->pourcentageLineEdit->text().toInt();
        }
        else{
            sommePourcentage += this->pourcentageParAgent[i];
        }
    }

    if (sommePourcentage <= 100){
        this->pourcentageParAgent[this->ui->agentComboBox->currentIndex()] = this->ui->pourcentageLineEdit->text().toInt();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","La somme des pourcentage pour tout les agents est supérieur à 100");
        messageBox.setFixedSize(500,200);
    }
}
