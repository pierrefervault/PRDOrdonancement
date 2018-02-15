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
     * @return vector<int> La liste des jobs triés
     */
    vector<int> trierCCmaxSommeRessources();
    /**
     * @brief Tri selon la méthode CCmax basée sur la valeur de ressource maximale de chaque job
     *
     * @return vector<int> La liste des jobs triés
     */
    vector<int> trierCCmaxMaxRessources();
    /**
     * @brief Tri selon la somme des ressources de chaque job
     *
     * @return vector<int> La liste des jobs triés
     */
    vector<int> trierSommeRessources();
    /**
     * @brief Tri selon la moyenne des ressources de chaque sous-ensembles maximaux de l'instance
     *
     * @return vector<int> La liste des jobs triés
     */
    vector<int> trierMoyenneRessourcesSousEnsembles();
    /**
     * @brief Algorithme permetant de récupérer les sous-ensembles maximaux de l'instance
     *
     * @param eh La liste d'événement classée
     * @param nb_job Le nombre de jobs de l'instance
     * @return map<int, vector<int> > Les sous ensembles maximaux
     */
    map<int,vector<int>> getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job);
    /**
     * @brief Affectation machine par machine
     *
     * @param typeTri Le type de tri à utiliser avant l'affectation
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return int Le nombre de jobs ordonnancés
     */
    int resolveMachinePerMachine(QString typeTri, QString fichierResultat);
    /**
     * @brief Affectation privilégiant la machine la moins chargée
     *
     * @param typeTri Le type de tri à utiliser avant l'affectation
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return int Le nombre de jobs ordonnancés
     */
    int resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat);
    /**
     * @brief Ecriture dans un fichier de résulat
     *
     * @param jobsOrdonnances Le tableau de jobs ordonancés
     * @param typeResolution Le type de résolution
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @param dureeExecution La durée d'execution de la résolution
     * @return int Le nombre de jobs ordonnancés
     */
    int writeInFile(vector<vector<int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution);

    /**
     * @brief Retourne l'instance courante
     *
     * @return Instance L'instance courante
     */
    Instance getInstance() const;
    /**
     * @brief Permet de spécifier une instance
     *
     * @param value L'instance que l'on souhaite spécifier
     */
    void setInstance(const Instance &value);

private:

    Instance instance; /**< L'instance à résoudre */

};

#endif // HEURISTIQUE_H
