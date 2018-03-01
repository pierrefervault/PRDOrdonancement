#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <QObject>
#include <vector>
#include<iostream>
#include <chrono>
#include <fstream>
#include "instance.h"
#include <map>

using namespace std;

/**
 * @brief Classe Heuristique permetant de trier et affecter des jobs sur des machines
 *
 */
class Heuristique
{
public:

    /**
     * @brief Constructeur de la classe Heuristique
     *
     * @param fichierInstance Le fichier d'instance
     */
    Heuristique(string fichierInstance);

    /**
     * @brief Tri selon la méthode CCmax basée sur la somme des ressources de chaque job
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierCCmaxSommeRessources();

    /**
     * @brief Tri selon la méthode CCmax basée sur la valeur de ressource maximale de chaque job
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierCCmaxMaxRessources();

    /**
     * @brief Tri selon la somme des ressources de chaque job
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierSommeRessources();

    /**
     * @brief Tri selon la moyenne des ressources de chaque sous-ensembles maximaux de l'instance
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierMoyenneRessourcesSousEnsembles();

    /**
     * @brief Affectation machine par machine
     *
     * @param typeTri Le type de tri à utiliser avant l'affectation
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolveMachinePerMachine(QString typeTri, QString fichierResultat);

    /**
     * @brief Affectation privilégiant la machine la moins chargée
     *
     * @param typeTri Le type de tri à utiliser avant l'affectation
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat);

    /**
     * @brief Ecriture dans un fichier de résulat
     *
     * @param jobsOrdonnances Le tableau de jobs ordonancés
     * @param typeResolution Le type de résolution
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @param dureeExecution La durée d'execution de la résolution
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int ecritureDansFichier(vector<vector<unsigned int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution);


    /**
     * @brief
     *
     * @return Instance
     */
    Instance getInstance() const;

    /**
     * @brief
     *
     * @param value
     */
    void setInstance(Instance value);

private:

    Instance instance; /**< L'instance à résoudre */

};

#endif // HEURISTIQUE_H
