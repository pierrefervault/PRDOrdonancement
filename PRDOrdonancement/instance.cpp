#include "instance.h"

Instance::Instance()
{

}

QString Instance::getFichierInstance() const
{
    return fichierInstance;
}

void Instance::setFichierInstance(const QString &value)
{
    fichierInstance = value;
}

int Instance::getNbrJobs() const
{
    return nbrJobs;
}

void Instance::setNbrJobs(int value)
{
    nbrJobs = value;
}

int Instance::getNbrRessources() const
{
    return nbrRessources;
}

void Instance::setNbrRessources(int value)
{
    nbrRessources = value;
}

int Instance::getNbrMachines() const
{
    return nbrMachines;
}

void Instance::setNbrMachines(int value)
{
    nbrMachines = value;
}

vector<int> Instance::getSj() const
{
    return sj;
}

void Instance::setSj(const vector<int> &value)
{
   sj = value;
}

vector<int> Instance::getFj() const
{
    return fj;
}

void Instance::setFj(const vector<int> &value)
{
    fj = value;
}

vector<vector<int> > Instance::getCapRessources() const
{
    return capRessources;
}

void Instance::setCapRessources(const vector<vector<int> > &value)
{
    capRessources = value;
}

vector<vector<int> > Instance::getTableauRessourcesJobs() const
{
    return tableauRessourcesJobs;
}

void Instance::setTableauRessourcesJobs(const vector<vector<int> > &value)
{
    tableauRessourcesJobs = value;
}


