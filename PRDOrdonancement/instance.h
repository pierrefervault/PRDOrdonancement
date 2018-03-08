#ifndef INSTANCE_H
#define INSTANCE_H

#include <QObject>
#include <QDir>
#include<iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <random>

using namespace std;

/**
 * @brief Classe représentant une instance
 *
 */
class Instance
{
public:
    /**
     * @brief Constructeur de la classe Instance
     *
     */
    Instance();

    /**
     * @brief Permet de retourner le chemin vers le fichier d'instance
     *
     * @return QString Le chemin vers le fichier d'instance
     */
    QString getFichierInstance() const;
    /**
     * @brief Setter du chemin vers le fichier d'instance
     *
     * @param value Le chemin vers le fichier d'instance que l'on souhaite
     */
    void setFichierInstance(const QString &value);

    /**
     * @brief Permet d'obtenir le nombre de jobs de l'instance
     *
     * @return unsigned int Le nombre de jobs
     */
    unsigned int getNbrJobs() const;
    /**
     * @brief Setter du nombre de jobs de l'instance
     *
     * @param value Le nombre de jobs souhaité de l'instance
     */
    void setNbrJobs(unsigned int value);

    /**
     * @brief Permet d'obtenir le nombre de ressources de l'instance
     *
     * @return unsigned int Le nombre de ressources
     */
    unsigned int getNbrRessources() const;
    /**
     * @brief Setter du nombre de ressources de l'instance
     *
     * @param value Le nombre de ressources souhaité de l'instance
     */
    void setNbrRessources(unsigned int value);

    /**
     * @brief Permet d'obtenir le nombre de machines de l'instance
     *
     * @return unsigned int Le nombre de machines
     */
    unsigned int getNbrMachines() const;
    /**
     * @brief Setter du nombre de machines de l'instance
     *
     * @param value Le nombre de machines souhaité de l'instance
     */
    void setNbrMachines(unsigned int value);

    /**
     * @brief Permet d'obtenir le tableau des instants de départ de l'ensemble des jobs
     *
     * @return vector<unsigned int> Le tableau des instants de départ de l'ensemble des jobs
     */
    vector<unsigned int> getSj() const;
    /**
     * @brief Setter du tableau des instants de départ de l'ensemble des jobs
     *
     * @param value Le tableau des instants de départ de l'ensemble des jobs souhaité
     */
    void setSj(const vector<unsigned int> &value);

    /**
     * @brief Permet d'obtenir le tableau des instants de fin de l'ensemble des jobs
     *
     * @return vector<unsigned int> Le tableau des instants de fin de l'ensemble des jobs
     */
    vector<unsigned int> getFj() const;
    /**
     * @brief Setter du tableau des instants de fin de l'ensemble des jobs
     *
     * @param value Le tableau des instants de fin de l'ensemble des jobs souhaité
     */
    void setFj(const vector<unsigned int> &value);

    /**
     * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des machines
     *
     * @return vector<vector<unsigned int>> Le tableau des capacités en ressource pour l'ensemble des machines
     */
    vector<vector<unsigned int>> getCapRessources() const;
    /**
     * @brief Setter du tableau des capacités en ressource pour l'ensemble des machines
     *
     * @param value Le tableau des capacités en ressource pour l'ensemble des machines souhaité
     */
    void setCapRessources(const vector<vector<unsigned int>> &value);

    /**
     * @brief Permet d'obtenir le tableau des capacités en ressource pour l'ensemble des jobs
     *
     * @return vector<vector<unsigned int>> Le tableau des capacités en ressource pour l'ensemble des jobs
     */
    vector<vector<unsigned int>> getTableauRessourcesJobs() const;
    /**
     * @brief Setter du tableau des capacités en ressource pour l'ensemble des jobs
     *
     * @param value Le tableau des capacités en ressource pour l'ensemble des jobs souhaité
     */
    void setTableauRessourcesJobs(const vector<vector<unsigned int> > &value);

    /**
     * @brief Permet d'obtenir l'horizon maximale de planification de l'instance
     *
     * @return unsigned int L'horizon maximale de planification de l'instance
     */
    unsigned int getHorizonMax() const;
    /**
     * @brief Setter de l'horizon maximale de planification de l'instance
     *
     * @param value L'horizon maximale de planification de l'instance souhaitée
     */
    void setHorizonMax(unsigned int value);


    /**
     * @brief Permet de charger une instance à partir d'un chemin vers un fichier d'instance
     *
     * @param fichierInstance Le chemin vers le fichier d'instance
     */
    void chargerInstance(string fichierInstance);

    /**
     * @brief Retourne les sous-ensembles maximaux de jobs de l'instance (jobs se chevauchant)
     *
     * @return map<unsigned int, vector<unsigned int> > Les sous-ensembles maximaux de jobs de l'instance
     */
    map<unsigned int,vector<unsigned int>> getSousEnsemblesMaximaux();

    /**
     * @brief Permet de sauvegarder des instances avec des paramètres particuliers
     *
     * @param nbrInstance Le nombre d'instance à générer
     * @param nbrJobs Le nombre de jobs par instance
     * @param nbrRessources Le nombre de ressources par instance
     * @param nbrMachines Le nombre de machines par instance
     * @param horizonPlanification L'horizon de planification maximal de chaque instance
     */
    void sauvegarderInstance(unsigned int nbrInstance, unsigned int nbrJobs, unsigned int nbrRessources, unsigned int nbrMachines, unsigned int horizonPlanification);


private:

    QString fichierInstance; /**< Le chemin vers le fichier d'instance*/
    unsigned int nbrJobs; /**< Le nombre de jobs de l'instance */
    unsigned int nbrRessources; /**< Le nombre de ressources de l'instance */
    unsigned int nbrMachines; /**< Le nombre de machines de l'instance */

    vector<unsigned int> sj; /**< Le tableau des instants de début pour l'ensemble des jobs */
    vector<unsigned int> fj; /**< Le tableau des instants de fin pour l'ensemble des jobs */
    unsigned int horizonMax; /**< L'horizon maximale de planification de l'instance */

    vector<vector<unsigned int>> capRessources; /**< Le tableau des capacités en ressource pour l'ensemble des machines */
    vector<vector<unsigned int>> tableauRessourcesJobs; /**< Le tableau des capacités en ressource pour l'ensemble des jobs */

};

#endif // INSTANCE_H
