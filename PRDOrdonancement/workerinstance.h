#ifndef WORKERINSTANCE_H
#define WORKERINSTANCE_H

#include <QObject>
#include <QWidget>
#include <iostream>
#include "instance.h"

using namespace std;

/**
 * @brief Le Worker permetant de gérer la génération de fichiers d'instance
 *
 */
class WorkerInstance : public QObject {
    Q_OBJECT

public:

    /**
     * @brief Constructeur de la classe WorkerInstance
     *
     * @param nbrInstance Le nombre d'instance à générer
     * @param nbrJobs Le nombre de jobs par instance
     * @param nbrRessources Le nombre de ressources par instance
     * @param nbrMachines Le nombre de machines par instance
     * @param horizonPlanification L'horizon maximale de planification par instance
     */
    WorkerInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification);

    /**
     * @brief Destructeur de la classe WorkerInstance
     *
     */
    ~WorkerInstance();

public slots :

    /**
     * @brief Action effectuée lors du lancement du worker
     *
     */
    void process();

signals:

    /**
     * @brief Action effectuée lorsque le worker a fini l'ensemble de ces tâches
     *
     */
    void finished();

    /**
     * @brief Action effectuée lorsqu'il y a une erreur dans le worker
     *
     * @param err
     */
    void error(QString err);

private:
    unsigned int nbrInstance; /**< Nombre d'instance à générer */
    unsigned int nbrJobs; /**< Nombre de jobs par instance */
    unsigned int nbrRessources; /**< Nombre de ressources par instance */
    unsigned int nbrMachines; /**< Nombre de machines par instance */
    unsigned int horizonPlanification; /**< Horizon maximale de planification par instance */
};

#endif // WORKERINSTANCE_H
