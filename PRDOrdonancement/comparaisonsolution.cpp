#include "comparaisonsolution.h"
#include "ui_comparaisonsolution.h"

ComparaisonSolution::ComparaisonSolution(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ComparaisonSolution)
{
    ui->setupUi(this);
}

ComparaisonSolution::~ComparaisonSolution()
{
    delete ui;
}

void ComparaisonSolution::on_choisirDossierPushButton_clicked()
{
    QFileDialog fenetreDossier;
    QString repertoireCourant = QDir::currentPath();
    QString dossierInstance = fenetreDossier.getExistingDirectory(this,
         tr("Instance directory"), "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!dossierInstance.isNull()){
        dossierInstance = dossierInstance.split(repertoireCourant+"/").at(1);
        this->ui->choisirDossierLineEdit->setText(dossierInstance);
    }
}

void ComparaisonSolution::on_validerPushButton_clicked()
{
    QThread* thread = new QThread;
    //cout << fichierInstance << " " << fichierResultat << endl;
    WorkerComparaison * workerComparaison = new WorkerComparaison(this->ui->choisirDossierLineEdit->text(), "");
    workerComparaison->moveToThread(thread);
    //connect(workerComparaison, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
    connect(thread, SIGNAL (started()), workerComparaison, SLOT (process()));
    connect(workerComparaison, SIGNAL (finished()), thread, SLOT (quit()));
    connect(workerComparaison, SIGNAL (finished()), workerComparaison, SLOT (deleteLater()));
    connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
    thread->start();
}

void ComparaisonSolution::on_annulerPushButton_clicked()
{
    reject();
}
