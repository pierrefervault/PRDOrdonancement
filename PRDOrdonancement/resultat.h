#ifndef RESULTAT_H
#define RESULTAT_H

#include <QObject>
#include <QWidget>
#include "iostream"
#include "fstream"

using namespace std;

class Resultat
{
public:
    Resultat();

    void chargerResultat(QString fichierResultat);

    vector<unsigned int> getSolutions() const;
    void setSolutions(const vector<unsigned int> &value);

    vector<double> getTempsExecution() const;

    unsigned int getNbrJobs() const;
    void setNbrJobs(unsigned int value);

    unsigned int getNbrRessources() const;
    void setNbrRessources(unsigned int value);

    unsigned int getNbrMachines() const;
    void setNbrMachines(unsigned int value);

    QString getFichierResultat() const;
    void setFichierResultat(const QString &value);

private:
    vector<unsigned int> solutions;
    vector<double> tempsExecution;
    unsigned int nbrJobs;
    unsigned int nbrRessources;
    unsigned int nbrMachines;
    QString fichierResultat;
};

#endif // RESULTAT_H
