#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <QObject>
#include <vector>
#include<iostream>
#include <chrono>
#include <fstream>
#include "instance.h"
#include <map>
#include "resultat.h"

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
    Heuristique(string fichierInstance, map<unsigned int, unsigned int> pourcentagesParAgent);

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
     * @brief Tri selon la méthode CCmax basée sur la somme des ressources de chaque job pour un cas multi agent
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierCCmaxSommeRessourcesMultiAgent();

    /**
     * @brief Tri selon la méthode CCmax basée sur la valeur de ressource maximale de chaque job pour un cas multi agent
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierCCmaxMaxRessourcesMultiAgent();

    /**
     * @brief Tri selon la somme des ressources de chaque job pour un cas multi agent
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierSommeRessourcesMultiAgent();

    /**
     * @brief Tri selon la moyenne des ressources de chaque sous-ensembles maximaux de l'instance pour un cas multi agent
     *
     * @return vector<unsigned int> La liste des jobs triés
     */
    vector<unsigned int> trierMoyenneRessourcesSousEnsemblesMultiAgent();

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
     * @brief Getter de l'instance pour laquelle on veut appliquer une heuristique
     *
     * @return Instance L'instance pour laquelle on veut appliquer une heuristique
     */
    Instance getInstance() const;

    /**
     * @brief Setter de l'instance pour laquelle on veut appliquer une heuristique
     *
     * @param value L'instance pour laquelle on veut appliquer une heuristique
     */
    void setInstance(Instance value);

private:

    Instance instance; /**< L'instance à résoudre */
    Resultat resultat; /**< La classe Resultat permetant de sauvegarder des résultats de résolution dans un fichier */

    map<unsigned int, unsigned int> pourcentagesParAgent; /**< Le pourcentage par agent dans un cas multi-agent */
};

#endif // HEURISTIQUE_H
