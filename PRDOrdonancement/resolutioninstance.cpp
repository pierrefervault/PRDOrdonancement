#include "resolutioninstance.h"
#include "ui_resolutioninstance.h"

using namespace std;

/**
 * @brief Constructeur de la classe ResolutionInstance
 *
 * @param parent
 */
ResolutionInstance::ResolutionInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResolutionInstance)
{
    ui->setupUi(this);
    this->setWindowTitle("Résolution d'instances");
    this->pourcentageParAgent.clear();
    this->ui->agentComboBox->clear();
    this->ui->agentComboBox->addItem("Agent 1");
    this->ui->pourcentageLineEdit->setText("100");
    this->pourcentageParAgent[0] = 100;
}

/**
 * @brief Destructeur de la classe ResolutionInstance
 *
 */
ResolutionInstance::~ResolutionInstance()
{
    delete ui;
}

/**
 * @brief Action effectuée lors du clic sur le bouton permettant de choisir un fichier ou un dossier
 *
 */
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

/**
 * @brief Action effectuée lors du clic sur le bouton permettant de valider
 *
 */
void ResolutionInstance::on_validerPushButton_clicked()
{

    QString fichierInstance = this->ui->choisirFichierLineEdit->text();

    QString multiAgent = "";

    if(this->ui->agentSpinBox->text().toInt() > 1) multiAgent = "MultiAgent";

    if (fichierInstance != NULL){
        for (unsigned int i = 0; i < this->ui->treeWidget->topLevelItemCount() ; i++){
            if (this->ui->treeWidget->topLevelItem(i)->checkState(0) == 2){

                if(this->ui->fichierRadioButton->isChecked()) executionFichier(fichierInstance, trouverMethodeResolution(i)+multiAgent, pourcentageParAgent);
                if(this->ui->dossierRadioButton->isChecked()) executionDossier(fichierInstance, trouverMethodeResolution(i)+multiAgent, pourcentageParAgent);

            }
            else {

                if (this->ui->treeWidget->topLevelItem(i)->childCount() != 0){
                    for(unsigned int j = 0; j < this->ui->treeWidget->topLevelItem(i)->childCount(); j++){

                        if(this->ui->treeWidget->topLevelItem(i)->child(j)->checkState(0) == 2){

                            if(this->ui->fichierRadioButton->isChecked()) executionFichier(fichierInstance, trouverMethodeResolution(i, j)+multiAgent,pourcentageParAgent);
                            if(this->ui->dossierRadioButton->isChecked()) executionDossier(fichierInstance, trouverMethodeResolution(i, j)+multiAgent, pourcentageParAgent);

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

/**
 * @brief Execution de la résolution avec un seul fichier d'instance
 *
 * @param fichierInstance Chemin vers le fichier d'instance
 * @param typeResolution Type de la résolution
 */
void ResolutionInstance::executionFichier(QString fichierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent)
{
    QThread* thread = new QThread;
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerFichier* workerFichier = new WorkerFichier(fichierInstance, typeResolution, pourcentagesParAgent);
    workerFichier->moveToThread(thread);
    //connect(workerFichier, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerFichier, SLOT (process()));
    connect(workerFichier, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerFichier, SIGNAL (finished()), workerFichier, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

/**
 * @brief Execution de la résolution avec un seul fichier d'instance
 *
 * @param dossierInstance Chemin vers le dossier d'instances
 * @param typeResolution Type de la résolution
 */
void ResolutionInstance::executionDossier(QString fichierInstance, QString typeResolution, map<unsigned int, unsigned int> pourcentagesParAgent)
{
    QThread* thread = new QThread();
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerDossier* workerDossier = new WorkerDossier(fichierInstance, typeResolution, pourcentagesParAgent);
    workerDossier->moveToThread(thread);
    //connect(workerDossier, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerDossier, SLOT (process()));
    connect(workerDossier, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerDossier, SIGNAL (finished()), workerDossier, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}


/**
 * @brief Action effectuée lors du clic sur le bouton permettant d'annuler
 *
 */
void ResolutionInstance::on_annulerPushButton_clicked()
{
    reject();
}

/**
 * @brief Action effectuée lors du clic sur le bouton permettant de spécifié que l'on veut choisir un fichier
 *
 */
void ResolutionInstance::on_fichierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
    this->ui->fichierInstanceLabel->setText("Fichier d'instance :");
    this->ui->choisirFichierPushButton->setText("Choisir un fichier");
}

/**
 * @brief Action effectuée lors du clic sur le bouton permettant de spécifié que l'on veut choisir un dossier
 *
 */
void ResolutionInstance::on_dossierRadioButton_clicked()
{
    this->ui->choisirFichierLineEdit->clear();
    this->ui->fichierInstanceLabel->setText("Dossier d'instances :");
    this->ui->choisirFichierPushButton->setText("Choisir un dossier");
}

/**
 * @brief Fonction permetant de trouver la methode de résolution suivant les champs CheckBox remplis
 *
 * @param indexTableau Index du tableau selectionné
 * @param indexSousElement Index du sous-élément du tableau selectionné (-1 si il n'y a pas de sous-élément)
 * @return QString La méthode de résolution
 */
QString ResolutionInstance::trouverMethodeResolution(unsigned int indexTableau, int indexSousElement){

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

/**
 * @brief Action effectuée lors du changement de l'objet SpinBox spécifique au nombre d'agent
 *
 * @param arg1
 */
void ResolutionInstance::on_agentSpinBox_valueChanged(int arg1)
{
    this->ui->agentComboBox->clear();
    this->pourcentageParAgent.clear();

    for (unsigned int i = 0; i < (unsigned int) this->ui->agentSpinBox->text().toInt(); i++){
        this->ui->agentComboBox->addItem("Agent "+QString::number(i+1));
        this->pourcentageParAgent[i] = 0;
    }
    this->pourcentageParAgent[0] = 100;
    this->ui->pourcentageLineEdit->setText("100");

    if(this->ui->agentSpinBox->text().toInt() == 1){
        this->ui->agentComboBox->setEnabled(false);
        this->ui->pourcentageLineEdit->setEnabled(false);
        this->ui->pourcentageLabel->setEnabled(false);
        this->ui->validerPourcentagePushButton->setEnabled(false);
    }
    else{
        this->ui->agentComboBox->setEnabled(true);
        this->ui->pourcentageLineEdit->setEnabled(true);
        this->ui->pourcentageLabel->setEnabled(true);
        this->ui->validerPourcentagePushButton->setEnabled(true);
    }

}

/**
 * @brief Action effectuée lors du changement de l'objet ComboBox spécifique au nombre d'agent
 *
 * @param index
 */
void ResolutionInstance::on_agentComboBox_currentIndexChanged(int index)
{
    //cout << this->pourcentageParAgent.size() << endl;
    for (unsigned int i = 0; i < this->pourcentageParAgent.size(); i++){
        cout << this->pourcentageParAgent[i] << endl;
    }
    if (this->pourcentageParAgent.size() > 0){
        this->ui->pourcentageLineEdit->setText(QString::number(this->pourcentageParAgent[index]));
    }
}

/**
 * @brief Action effectuée lors du clic sur le bouton permetant de valider le pourcentage de jobs affectés à un agent
 *
 */
void ResolutionInstance::on_validerPourcentagePushButton_clicked()
{
    unsigned int sommePourcentage = 0;
    for (unsigned int i = 0; i < this->pourcentageParAgent.size(); i++){

        if (i == (unsigned int)this->ui->agentComboBox->currentIndex()){
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


/**
 * @brief Action effectuée lors du clic sur le bouton permetant de cocher l'ensemble des méthodes de résolution en meme temps
 *
 */
void ResolutionInstance::on_toutCocherCheckBox_clicked(bool checked)
{
    if (checked){
        for (unsigned int i = 0; i < (unsigned int)this->ui->treeWidget->topLevelItemCount() ; i++){

            if (this->ui->treeWidget->topLevelItem(i)->childCount() != 0){
                for(unsigned int j = 0; j < (unsigned int)this->ui->treeWidget->topLevelItem(i)->childCount(); j++){
                    this->ui->treeWidget->topLevelItem(i)->child(j)->setCheckState(0,Qt::Checked);
                }
            }
            else{
                this->ui->treeWidget->topLevelItem(i)->setCheckState(0,Qt::Checked);
            }
        }
    }
    else{
        for (unsigned int i = 0; i < (unsigned int)this->ui->treeWidget->topLevelItemCount() ; i++){

            if (this->ui->treeWidget->topLevelItem(i)->childCount() != 0){
                for(unsigned int j = 0; j < (unsigned int) this->ui->treeWidget->topLevelItem(i)->childCount(); j++){
                    this->ui->treeWidget->topLevelItem(i)->child(j)->setCheckState(0,Qt::Unchecked);
                }
            }
            else{
                this->ui->treeWidget->topLevelItem(i)->setCheckState(0,Qt::Unchecked);
            }
        }
    }
}
