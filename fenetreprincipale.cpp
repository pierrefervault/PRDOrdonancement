#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "generationinstance.h"
#include "resolutioninstance.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::on_actionG_n_rer_des_instances_triggered()
{
    GenerationInstance generationInstance;
    if(generationInstance.exec()==QDialog::Accepted)
    {
        generationInstance.reject();
    }
}

void FenetrePrincipale::on_actionQuitter_l_application_triggered()
{
    close();
}

void FenetrePrincipale::on_actionInstances_multi_machines_triggered()
{
    ResolutionInstance resolutionInstance;
    if(resolutionInstance.exec()==QDialog::Accepted)
    {
        resolutionInstance.reject();
    }
    //Ceci fonctionne et c'est interressant
    //system("./plne instance-300-1-100.data resultatPlne-300-1-100.data");
}
