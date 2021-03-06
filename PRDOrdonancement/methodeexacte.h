#ifndef METHODEEXACTE_H
#define METHODEEXACTE_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>
#include <map>
#include <vector>
#include "instance.h"
#include "resultat.h"

#include <ilcplex/ilocplex.h>

using namespace std;

//Déclarartion de l'ensemble des types utilisés par cplex
ILOSTLBEGIN

/**
 * @brief Classe MethodeExacte permetant de résoudre des instances à l'aide de méthodes exactes
 *
 */
class MethodeExacte
{
public:

    /**
     * @brief Constructeur de la classe MethodeExacte
     *
     * @param fichierInstance Le chemin vers le fichier d'instance
     */
    MethodeExacte(string fichierInstance, map<unsigned int, unsigned int> pourcentagesParAgent);
    /**
     * @brief Methode de résolution exacte indéxée temps
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolutionPlneMip1(string fichierResultat);
    /**
     * @brief Methode de résolution exacte indéxée jobs
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolutionPlneMip2(string fichierResultat);

    /**
     * @brief Methode de résolution exacte indéxée temps pour un cas multi agent
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolutionPlneMip1MultiAgent(string fichierResultat);
    /**
     * @brief Methode de résolution exacte indéxée jobs pour un cas multi agent
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return unsigned int Le nombre de jobs ordonnancés
     */
    unsigned int resolutionPlneMip2MultiAgent(string fichierResultat);

    Instance getInstance() const;
    void setInstance(const Instance &value);

private:
    Instance instance; /**< L'instance à résoudre */
    Resultat resultat; /**< La classe Resultat permetant de sauvegarder des résultats de résolution dans un fichier */

    map<unsigned int, unsigned int> pourcentagesParAgent; /**< Le pourcentage par agent dans un cas multi-agent */
};

#endif // METHODEEXACTE_H
