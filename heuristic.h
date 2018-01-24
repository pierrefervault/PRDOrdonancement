#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <QObject>
#include <QWidget>

using namespace std;

class Heuristic
{
public:
    Heuristic();
    void trierCCmax(string filename);

private:
    int nbr_jobs;
    int nbr_ressources;
    int nbr_machines;

};

#endif // HEURISTIC_H
