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
 * @brief
 *
 */
class ComparaisonSolution : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit ComparaisonSolution(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ComparaisonSolution();


    void executionComparaison(QString dossierInstance, QString typeResolution, unsigned int nbrRessources, unsigned int nbrMachines);

private slots:

    void updateLayout(map<unsigned int,map<QString,unsigned int>> tableauComparaison, QString typeComparaison);

    /**
     * @brief
     *
     */
    void on_choisirDossierPushButton_clicked();

    /**
     * @brief
     *
     */
    void on_validerPushButton_clicked();

    /**
     * @brief
     *
     */
    void on_annulerPushButton_clicked();

    void on_netoyerLayoutPushButton_clicked();

private:
    Ui::ComparaisonSolution *ui; /**< TODO: describe */
};

#endif // COMPARAISONSOLUTION_H
