#include "resultat.h"

Resultat::Resultat()
{

}

void Resultat::chargerResultat(QString fichierResultat){
    this->fichierResultat = fichierResultat;

    std::ifstream f(fichierResultat.toStdString());

    if (!f)
    {
        cout << fichierResultat.toStdString() <<" invalid file" << endl;
    }

    this->nbrJobs = (unsigned int) fichierResultat.split("/")[2].toInt();
    this->nbrRessources = (unsigned int) fichierResultat.split("/")[3].toInt();
    this->nbrMachines = (unsigned int) fichierResultat.split("/")[4].toInt();

    string line;

    vector <unsigned int> solutionTrouve;
    vector<double> tempsExecution;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        unsigned int optimal = ligneOptimale.split("=")[1].toInt();
        solutionTrouve.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsExecution.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierResultat.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (unsigned int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    this->solutions = solutionTrouve;
    this->tempsExecution = tempsExecution;
}

vector<unsigned int> Resultat::getSolutions() const
{
    return solutions;
}

void Resultat::setSolutions(const vector<unsigned int> &value)
{
    solutions = value;
}

vector<double> Resultat::getTempsExecution() const
{
    return tempsExecution;
}

unsigned int Resultat::getNbrJobs() const
{
    return nbrJobs;
}

void Resultat::setNbrJobs(unsigned int value)
{
    nbrJobs = value;
}

unsigned int Resultat::getNbrRessources() const
{
    return nbrRessources;
}

void Resultat::setNbrRessources(unsigned int value)
{
    nbrRessources = value;
}

unsigned int Resultat::getNbrMachines() const
{
    return nbrMachines;
}

void Resultat::setNbrMachines(unsigned int value)
{
    nbrMachines = value;
}

QString Resultat::getFichierResultat() const
{
    return fichierResultat;
}

void Resultat::setFichierResultat(const QString &value)
{
    fichierResultat = value;
}
