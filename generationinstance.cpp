#include "generationinstance.h"
#include "ui_generationinstance.h"

using namespace std;

GenerationInstance::GenerationInstance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerationInstance)
{
    ui->setupUi(this);
}

GenerationInstance::~GenerationInstance()
{
    delete ui;
}

void GenerationInstance::on_okPushButton_clicked()
{
    if (this->ui->nbrInstancesLineEdit->text().toInt() != NULL && this->ui->nbrJobsLineEdit->text().toInt() != NULL &&
            this->ui->nbrRessourcesLineEdit->text().toInt() != NULL && this->ui->nbrMachinesLineEdit->text().toInt() != NULL &&
            this->ui->horizonPlanificationLineEdit->text().toInt() != NULL)
    {
        cout << "Execution de la génération d'instances" << endl;
        int horizonPlanification = 0;

        if (this->ui->horizonPlanificationComboBox->currentText() == "secondes") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt();
        if (this->ui->horizonPlanificationComboBox->currentText() == "minutes") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 60;
        if (this->ui->horizonPlanificationComboBox->currentText() == "heures") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 3600;
        if (this->ui->horizonPlanificationComboBox->currentText() == "jours") horizonPlanification = this->ui->horizonPlanificationLineEdit->text().toInt() * 86400;

        executionGenerationInstance(this->ui->nbrInstancesLineEdit->text().toInt(), this->ui->nbrJobsLineEdit->text().toInt(),
                                    this->ui->nbrRessourcesLineEdit->text().toInt(), this->ui->nbrMachinesLineEdit->text().toInt(),
                                    horizonPlanification);
        accept();
    }
    else cout << "Un champs n'est pas correctement rempli" << endl;
}

void GenerationInstance::on_annulerPushButton_clicked()
{
    reject();
}

void GenerationInstance::executionGenerationInstance(int nbrInstance, int nbrJobs, int nbrRessources, int nbrMachines, int horizonPlanification)
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

