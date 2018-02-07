#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <QObject>
#include <vector>
#include<iostream>
#include <chrono>
#include <fstream>
#include "instance.h"

using namespace std;

class Heuristique
{
public:
    Heuristique(string fichierInstance);
    vector<int> trierCCmaxSommeRessources();
    vector<int> trierCCmaxMaxRessources();
    vector<int> trierSommeRessources();
    vector<int> trierMoyenneRessourcesSousEnsembles();
    map<int,vector<int>> getSousEnsemblesMaximaux(vector<vector<int>> eh, int nb_job);
    int resolveMachinePerMachine(QString typeTri, QString fichierResultat);
    int resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat);
    int writeInFile(vector<vector<int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution);

    Instance getInstance() const;
    void setInstance(const Instance &value);

private:

    Instance instance;

};

#endif // HEURISTIQUE_H
