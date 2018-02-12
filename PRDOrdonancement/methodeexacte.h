#ifndef METHODEEXACTE_H
#define METHODEEXACTE_H

#include <QObject>
#include <ilcplex/ilocplex.h>
#include <iostream>
#include <algorithm>
#include<string>
#include <time.h>
#include <map>
#include <vector>
#include "instance.h"

using namespace std;

//Déclarartion de l'ensemble des types utilisés par cplex
ILOSTLBEGIN

class MethodeExacte
{
public:

    MethodeExacte(string fichierInstance);
    int resolutionPlneMip1(string fichierResultat);
    int resolutionPlneMip2(string fichierResultat);
    map<int,vector<int>> getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job);

private:
    Instance instance;
};

#endif // METHODEEXACTE_H
