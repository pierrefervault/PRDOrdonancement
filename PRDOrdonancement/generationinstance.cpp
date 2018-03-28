#include "generationinstance.h"
#include "ui_generationinstance.h"

using namespace std;

/**
 * @brief Constructeur de la fenêtre GenerationInstance
 *
 * @param parent
 */
GenerationInstance::GenerationInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerationInstance)
{
    ui->setupUi(this);
    this->setWindowTitle("Génération d'instances");
}

/**
 * @brief Destructeur de la fenêtre GenerationInstance
 *
 */
GenerationInstance::~GenerationInstance()
{
    delete ui;
}

/**
 * @brief Action effectuée lors du clic sur le bouton de génération d'instance
 *
 */
void GenerationInstance::on_okPushButton_clicked()
{
    if (this->ui->nbrInstancesLineEdit->text().toInt() >= 1 && this->ui->nbrJobsLineEdit->text().toInt() >= 1 &&
            this->ui->nbrRessourcesLineEdit->text().toInt() >= 1 && this->ui->nbrMachinesLineEdit->text().toInt() >= 1 &&
            this->ui->horizonPlanificationLineEdit->text().toInt() >= 1)
    {
        cout << "Execution de la génération d'instances" << endl;
        unsigned int horizonPlanification = 0;

        if (this->ui->horizonPlanificationComboBox->currentText() == "secondes") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt();
        if (this->ui->horizonPlanificationComboBox->currentText() == "minutes") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 60;
        if (this->ui->horizonPlanificationComboBox->currentText() == "heures") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 3600;
        if (this->ui->horizonPlanificationComboBox->currentText() == "jours") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 86400;

        executionGenerationInstance(this->ui->nbrInstancesLineEdit->text().toInt(), this->ui->nbrJobsLineEdit->text().toInt(),
                                    this->ui->nbrRessourcesLineEdit->text().toInt(), this->ui->nbrMachinesLineEdit->text().toInt(),
                                    horizonPlanification);
        accept();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Erreur","Un champs n'est pas correctement rempli");
        messageBox.setFixedSize(500,200);
    }
}

/**
 * @brief Action effectuée lors du clic sur le bouton annuler
 *
 */
void GenerationInstance::on_annulerPushButton_clicked()
{
    reject();
}

/**
 * @brief Fonction permetant d'executer la generation des instances spécifiées
 *
 * @param nbrInstance Le nombre d'instance à générer
 * @param nbrJobs Le nombre de jobs par instance
 * @param nbrRessources Le nombre de ressources par instance
 * @param nbrMachines Le nombre de machines par instance
 * @param horizonPlanification L'horizon de planification maximale par instance
 */
void GenerationInstance::executionGenerationInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification)
{
    QThread* thread = new QThread;
    WorkerInstance* workerInstance = new WorkerInstance(nbrInstance, nbrJobs, nbrRessources, nbrMachines, horizonPlanification);
    workerInstance->moveToThread(thread);
    //connect(workerInstance, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerInstance, SLOT (process()));
    connect(workerInstance, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerInstance, SIGNAL (finished()), workerInstance, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}
