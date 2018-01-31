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
    executionGenerationInstance(this->ui->nbrInstancesLineEdit->text().toInt(), this->ui->nbrJobsLineEdit->text().toInt(),
                                this->ui->nbrRessourcesLineEdit->text().toInt(), this->ui->nbrMachinesLineEdit->text().toInt(),
                                this->ui->instantFinLineEdit->text().toInt());
    accept();
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

