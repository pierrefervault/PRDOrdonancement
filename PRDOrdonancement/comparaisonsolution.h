#ifndef COMPARAISONSOLUTION_H
#define COMPARAISONSOLUTION_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>
#include "workercomparaison.h"
#include "QCheckBox"
#include "QBoxLayout"
#include "QMessageBox"
#include "resultat.h"

#include <QMetaType>

#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>


namespace Ui {
class ComparaisonSolution;
}

/**
 * @brief La fenetre permetant d'effectuer des comparaison de méthode de résolution
 *
 */
class ComparaisonSolution : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la classe ComparaisonSolution
     *
     * @param parent
     */
    explicit ComparaisonSolution(QWidget *parent = 0);

    /**
     * @brief Destructeur de la classe ComparaisonSolution
     *
     */
    ~ComparaisonSolution();


    /**
     * @brief Execute la comparaison de solution
     *
     * @param dossierResultat Le dossier de résultat que l'on souhaite comparer
     * @param typeComparaison Le type de comparaison que l'on souhaite effectuer
     * @param nbrRessources Le nombre de ressources de chaque fichier de resultat
     * @param nbrMachines Le nombre de machines de chaque fichier de resultat
     */
    void executionComparaison(QString dossierResultat, QString typeComparaison, unsigned int nbrRessources, unsigned int nbrMachines);

private slots:

    /**
     * @brief Permet de mettre à jour le layout contenant le graphique de comparaison
     *
     * @param tableauComparaison Le tableau de comparaison contenant toute les données nécessaires à l'affichage du graphique
     * @param typeComparaison Le type de comparaison que nous avons effectué
     */
    void updateLayout(map<unsigned int,map<QString,unsigned int>> tableauComparaison, QString typeComparaison);

    /**
     * @brief Action réalisée lors du clic sur le bouton permettant de choisir un dossier de résultat
     *
     */
    void on_choisirDossierPushButton_clicked();

    /**
     * @brief Action réalisée lors du clic sur le bouton permettant de valider la comparaison
     *
     */
    void on_validerPushButton_clicked();

    /**
     * @brief Action réalisée lors du clic sur le bouton permettant d'annuler la comparaison
     *
     */
    void on_annulerPushButton_clicked();

    /**
     * @brief Action réalisée lors du clic sur le bouton permettant de nettoyer le layout contenant le graphique de comparaison
     *
     */
    void on_netoyerLayoutPushButton_clicked();

private:
    Ui::ComparaisonSolution *ui; /**< La fenetre de comparaison de méthode de résolution*/
};

#endif // COMPARAISONSOLUTION_H
