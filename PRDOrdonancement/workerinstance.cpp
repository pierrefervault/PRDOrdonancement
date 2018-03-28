#include "workerinstance.h"

/**
 * @brief Constructeur de la classe WorkerInstance
 *
 * @param nbrInstance Le nombre d'instance à générer
 * @param nbrJobs Le nombre de jobs par instance
 * @param nbrRessources Le nombre de ressources par instance
 * @param nbrMachines Le nombre de machines par instance
 * @param horizonPlanification L'horizon maximale de planification par instance
 */
WorkerInstance::WorkerInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification)
{
    this->nbrInstance = nbrInstance;
    this->nbrJobs = nbrJobs;
    this->nbrRessources = nbrRessources;
    this->nbrMachines = nbrMachines;
    this->horizonPlanification = horizonPlanification;
}

/**
 * @brief Destructeur de la classe WorkerInstance
 *
 */
WorkerInstance::~WorkerInstance(){

}

/**
 * @brief Action effectuée lors du lancement du worker
 *
 */
void WorkerInstance::process(){
    Instance instance;
    instance.sauvegarderInstance(this->nbrInstance,this->nbrJobs,this->nbrRessources,this->nbrMachines,this->horizonPlanification);

    cout << "Génération terminée" << endl;

    emit finished();
}
