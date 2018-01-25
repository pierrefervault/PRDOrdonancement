#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <QObject>
#include <QWidget>
#include <vector>

using namespace std;

class Heuristic
{
public:
    Heuristic(string filename);
    vector<int> trierCCmax();
    vector<int> trierSommeRessources();
    vector<int> trierMoyenneRessourcesSousEnsembles();
    map<int,vector<int>> getSubset(vector<vector<int>> eh, int nb_job);
    void resolveMachinePerMachine(vector<int> tableauJobs);

private:
    int nbr_jobs;
    int nbr_ressources;
    int nbr_machines;

    vector<int> S_j;
    vector<int> F_j;

    vector<vector<int>> cap_ressources;
    vector<vector<int>> C;

};

#endif // HEURISTIC_H
