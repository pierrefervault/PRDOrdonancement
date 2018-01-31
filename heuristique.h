#ifndef HEURISTIQUE_H
#define HEURISTIQUE_H

#include <QObject>
#include <QWidget>
#include <vector>
#include<iostream>
#include <chrono>
#include <fstream>

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
    void resolveMachinePerMachine(QString typeTri, QString fichierResultat);
    void resolveMachineLessUsedMachine(QString typeTri, QString fichierResultat);
    void writeInFile(vector<vector<int>> jobsOrdonnances, QString typeResolution, QString fichierResultat, double dureeExecution);

private:

    QString fichierInstance;
    int nbr_jobs;
    int nbr_ressources;
    int nbr_machines;

    vector<int> S_j;
    vector<int> F_j;

    vector<vector<int>> cap_ressources;
    vector<vector<int>> C;

};

#endif // HEURISTIQUE_H
