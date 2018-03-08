#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "generationinstance.h"
#include "resolutioninstance.h"
#include "comparaisonsolution.h"
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    this->setWindowTitle("Application de résolution d'instance et de comparaison de méthodes de résolution");
}

/**
 * @brief Destructeur de la Fenêtre Principale
 *
 */
FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

/**
 * @brief Action effectuée lors du clic sur le bouton de génération d'instance
 *
 */
void FenetrePrincipale::on_actionG_n_rer_des_instances_triggered()
{
    GenerationInstance generationInstance;
    if(generationInstance.exec()==QDialog::Accepted)
    {
        generationInstance.reject();
    }
}

/**
 * @brief Action effectuée lors du clic sur le bouton permetant de quitter l'application
 *
 */
void FenetrePrincipale::on_actionQuitter_l_application_triggered()
{
    close();
}

/**
 * @brief Action effectuée lors du clic sur le bouton de résolution d'instance
 *
 */
void FenetrePrincipale::on_actionR_soudre_des_instances_triggered()
{
    ResolutionInstance resolutionInstance;
    if(resolutionInstance.exec()==QDialog::Accepted)
    {
        resolutionInstance.reject();
    }
}

/**
 * @brief Action effectuée lors du clic sur le bouton de comparaison de méthode de résolution
 *
 */
void FenetrePrincipale::on_actionComparer_des_m_thodes_de_r_solutions_triggered()
{
    ComparaisonSolution comparaisonSolution;
    if(comparaisonSolution.exec()==QDialog::Accepted)
    {
        comparaisonSolution.reject();
    }
}
