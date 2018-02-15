#include "instance.h"

/**
 * @brief Constructeur de la classe Instance
 *
 */
Instance::Instance()
{

}

/**
 * @brief Permet de retourner le chemin vers le fichier d'instance
 *
 * @return QString Le chemin vers le fichier d'instance
 */
QString Instance::getFichierInstance() const
{
    return fichierInstance;
}

/**
 * @brief Setter du chemin vers le fichier d'instance
 *
 * @param value Le chemin vers le fichier d'instance que l'on souhaite
 */
void Instance::setFichierInstance(const QString &value)
{
    fichierInstance = value;
}

/**
 * @brief Permet d'obtenir le nombre de jobs de l'instance
 *
 * @return int Le nombre de jobs
 */
int Instance::getNbrJobs() const
{
    return nbrJobs;
}

/**
 * @brief Setter du nombre de jobs de l'instance
 *
 * @param value Le nombre de jobs souhaité de l'instance
 */
void Instance::setNbrJobs(int value)
{
    nbrJobs = value;
}

/**
 * @brief Permet d'obtenir le nombre de ressources de l'instance
 *
 * @return int Le nombre de ressources
 */
int Instance::getNbrRessources() const
{
    return nbrRessources;
}

/**
 * @brief Setter du nombre de ressources de l'instance
 *
 * @param value Le nombre de ressources souhaité de l'instance
 */
void Instance::setNbrRessources(int value)
{
    nbrRessources = value;
}

/**
 * @brief Permet d'obtenir le nombre de machines de l'instance
 *
 * @return int Le nombre de machines
 */
int Instance::getNbrMachines() const
{
    return nbrMachines;
}

/**
 * @brief Setter du nombre de machines de l'instance
 *
 * @param value Le nombre de machines souhaité de l'instance
 */
void Instance::setNbrMachines(int value)
{
    nbrMachines = value;
}

/**
 * @brief Permet d'obtenir le tableau des instants de départ de l'ensemble des jobs
 *
 * @return vector<int> Le tableau des instants de départ de l'ensemble des jobs
 */
vector<int> Instance::getSj() const
{
    return sj;
}

/**
 * @brief Setter du tableau des instants de départ de l'ensemble des jobs
 *
 * @param value Le tableau des instants de départ de l'ensemble des jobs souhaité
 */
void Instance::setSj(const vector<int> &value)
{
   sj = value;
}

/**
 * @brief Permet d'obtenir le tableau des instants de fin de l'ensemble des jobs
 *
 * @return vector<int> Le tableau des instants de fin de l'ensemble des jobs
 */
vector<int> Instance::getFj() const
{
    return fj;
}

/**
 * @brief Setter du tableau des instants de fin de l'ensemble des jobs
 *
 * @param value Le tableau des instants de fin de l'ensemble des jobs souhaité
 */
void Instance::setFj(const vector<int> &value)
{
    fj = value;
}

/**
 * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des machines
 *
 * @return vector<vector<int>> Le tableau des capacités en ressource pour l'ensemble des machines
 */
vector<vector<int> > Instance::getCapRessources() const
{
    return capRessources;
}

/**
 * @brief Setter du tableau des capacités en ressource pour l'ensemble des machines
 *
 * @param value Le tableau des capacités en ressource pour l'ensemble des machines souhaité
 */
void Instance::setCapRessources(const vector<vector<int> > &value)
{
    capRessources = value;
}

/**
 * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des jobs
 *
 * @return vector<vector<int>> Le tableau des capacités en ressource pour l'ensemble des jobs
 */
vector<vector<int> > Instance::getTableauRessourcesJobs() const
{
    return tableauRessourcesJobs;
}

/**
 * @brief Setter du tableau des capacités en ressource pour l'ensemble des jobs
 *
 * @param value Le tableau des capacités en ressource pour l'ensemble des jobs souhaité
 */
void Instance::setTableauRessourcesJobs(const vector<vector<int> > &value)
{
    tableauRessourcesJobs = value;
}

/**
 * @brief Permet d'obtenir l'horizon maximale de planification de l'instance
 *
 * @return int L'horizon maximale de planification de l'instance
 */
int Instance::getHorizonMax() const
{
    return horizonMax;
}

/**
 * @brief Setter de l'horizon maximale de planification de l'instance
 *
 * @param value L'horizon maximale de planification de l'instance souhaitée
 */
void Instance::setHorizonMax(int value)
{
    horizonMax = value;
}
