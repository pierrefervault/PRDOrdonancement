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
WorkerInstance::WorkerInstance(int nbrInstance, int nbrJobs, int nbrRessources, int nbrMachines, int horizonPlanification)
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

    std::random_device rd;
    std::mt19937 gen(rd());

    int numInstance;
    int numJob;
    int numRessource;
    int numMachine;

    int dossier = 0;

    string cheminDossier = "Instances/"+to_string(dossier)+"/"+to_string(this->nbrJobs)+"/"+to_string(this->nbrRessources)+"/"+to_string(this->nbrMachines);

    QDir *repertoire = new QDir(QString::fromStdString(cheminDossier));

    //J'ai limité à 1000 sous-dossiers différents
    while (repertoire->exists() && dossier < 1000){
        dossier++;
        cheminDossier = "Instances/"+to_string(dossier)+"/"+to_string(this->nbrJobs)+"/"+to_string(this->nbrRessources)+"/"+to_string(this->nbrMachines);
        repertoire->setPath(QString::fromStdString(cheminDossier));
    }

    repertoire->mkpath(".");

    for(numInstance = 0; numInstance < this->nbrInstance; numInstance++){


        ofstream fichier(cheminDossier+"/instance"+to_string(numInstance)+"-"+to_string(this->nbrJobs)+"-"+to_string(this->nbrRessources)
                         +"-"+to_string(this->nbrMachines)+".data", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

        if(fichier){

            fichier << this->nbrJobs << " " << this->nbrRessources
                    << " " << this->nbrMachines << endl;

            for (numMachine = 0; numMachine < this->nbrMachines; numMachine++){

                for (numRessource = 0; numRessource < this->nbrRessources; numRessource++){

                    fichier << "1000";

                    if (numRessource != this->nbrRessources-1){
                        fichier << " ";
                    }
                }

                fichier << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> dis(0, this->horizonPlanification - 1);

            for (numJob = 0; numJob < this->nbrJobs; numJob++){
                int startTime = dis(rd);
                std::uniform_int_distribution<> disFinish(startTime + 1, this->horizonPlanification);
                int finishTime = disFinish(rd);
                fichier << numJob << "\t" << startTime << "\t" << finishTime << endl;
            }

            fichier << endl;

            std::uniform_int_distribution<> disRessource(1, 1000);

            for (numJob = 0; numJob < this->nbrJobs; numJob++){
                for (numRessource = 0; numRessource < this->nbrRessources; numRessource++){
                    fichier << disRessource(rd);
                    if (numRessource != this->nbrRessources-1){
                        fichier << " ";
                    }
                }
                fichier << endl;
            }
            fichier.close();
        }
        else cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
}
