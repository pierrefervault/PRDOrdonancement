#ifndef WORKERINSTANCE_H
#define WORKERINSTANCE_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <random>

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
    WorkerInstance(int nbrInstance, int nbrJobs, int nbrRessources, int nbrMachines, int horizonPlanification);
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
    int nbrInstance; /**< Nombre d'instance à générer */
    int nbrJobs; /**< Nombre de jobs par instance */
    int nbrRessources; /**< Nombre de ressources par instance */
    int nbrMachines; /**< Nombre de machines par instance */
    int horizonPlanification; /**< Horizon maximale de planification par instance */
};

#endif // WORKERINSTANCE_H
