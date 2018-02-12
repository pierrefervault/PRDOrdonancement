#ifndef INSTANCE_H
#define INSTANCE_H

#include <QString>
#include <vector>

using namespace std;

class Instance
{
public:
    Instance();

    QString getFichierInstance() const;
    void setFichierInstance(const QString &value);

    int getNbrJobs() const;
    void setNbrJobs(int value);

    int getNbrRessources() const;
    void setNbrRessources(int value);

    int getNbrMachines() const;
    void setNbrMachines(int value);

    vector<int> getSj() const;
    void setSj(const vector<int> &value);

    vector<int> getFj() const;
    void setFj(const vector<int> &value);

    vector<vector<int> > getCapRessources() const;
    void setCapRessources(const vector<vector<int> > &value);

    vector<vector<int> > getTableauRessourcesJobs() const;
    void setTableauRessourcesJobs(const vector<vector<int> > &value);

    int getHorizonMax() const;
    void setHorizonMax(int value);

private:

    QString fichierInstance;
    int nbrJobs;
    int nbrRessources;
    int nbrMachines;

    vector<int> sj;
    vector<int> fj;
    int horizonMax;

    vector<vector<int>> capRessources;
    vector<vector<int>> tableauRessourcesJobs;

};

#endif // INSTANCE_H
