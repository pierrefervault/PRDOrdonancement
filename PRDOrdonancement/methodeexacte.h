#ifndef METHODEEXACTE_H
#define METHODEEXACTE_H

#include <QObject>
#include <ilcplex/ilocplex.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <time.h>
#include <map>
#include <vector>
#include "instance.h"

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
    MethodeExacte(string fichierInstance);
    /**
     * @brief Methode de résolution exacte indéxée temps
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return int Le nombre de jobs ordonnancés
     */
    int resolutionPlneMip1(string fichierResultat);
    /**
     * @brief Methode de résolution exacte indéxée jobs
     *
     * @param fichierResultat Le fichier où seront stockés les résulats
     * @return int Le nombre de jobs ordonnancés
     */
    int resolutionPlneMip2(string fichierResultat);
    /**
     * @brief Algorithme permetant de récupérer les sous-ensembles maximaux de l'instance
     *
     * @param eh La liste d'événement classée
     * @param nb_job Le nombre de jobs de l'instance
     * @return map<int, vector<int> > Les sous ensembles maximaux
     */
    map<int,vector<int>> getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job);

private:
    Instance instance; /**< L'instance à résoudre */
};

#endif // METHODEEXACTE_H
