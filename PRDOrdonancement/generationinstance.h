#ifndef GENERATIONINSTANCE_H
#define GENERATIONINSTANCE_H

#include <QDialog>
#include "workerinstance.h"
#include <QtConcurrent/QtConcurrent>
#include <iostream>
#include "QMessageBox"

namespace Ui {
class GenerationInstance;
}

/**
 * @brief La fenêtre de génération d'instance
 *
 */
class GenerationInstance : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructeur de la fenêtre GenerationInstance
     *
     * @param parent
     */
    explicit GenerationInstance(QWidget *parent = 0);

    /**
     * @brief Destructeur de la fenêtre GenerationInstance
     *
     */
    ~GenerationInstance();

    /**
     * @brief Fonction permetant d'executer la generation des instances spécifiées
     *
     * @param nbrInstance Le nombre d'instance à générer
     * @param nbrJobs Le nombre de jobs par instance
     * @param nbrRessources Le nombre de ressources par instance
     * @param nbrMachines Le nombre de machines par instance
     * @param horizonPlanification L'horizon de planification maximale par instance
     */
    void executionGenerationInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification);

private slots:
    /**
     * @brief Action effectuée lors du clic sur le bouton de génération d'instance
     *
     */
    void on_okPushButton_clicked();

    /**
     * @brief Action effectuée lors du clic sur le bouton annuler
     *
     */
    void on_annulerPushButton_clicked();

private:
    Ui::GenerationInstance *ui; /**< La fenêtre de génération d'instance */
};

#endif //GENERATIONINSTANCE_H
