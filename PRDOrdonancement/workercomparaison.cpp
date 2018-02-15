#include "workercomparaison.h"
#include "fstream"

WorkerComparaison::WorkerComparaison(QString dossierResultat, QString typeComparaison){
    this->dossierResultat = dossierResultat;
    this->typeComparaison = typeComparaison;
}

WorkerComparaison::~WorkerComparaison(){

}

void WorkerComparaison::process(){

    QString dossierResultat = this->dossierResultat;
    QFileInfo path(dossierResultat);

    QStringList filter;
    filter << "*.data";

    QDirIterator it(dossierResultat, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
        files << it.next();
    files.sort();

    std::list<QString> list = files.toStdList();

    QString fichierSolutionOptimale = "";
    QString fichierAffectation1CCmaxSommeRessources = "";

    for(std::list<QString>::iterator it = list.begin() ; it != list.end() ; ++it){
        QString fichier = *it;

        if(fichier.contains("Affectation1-CCmaxMaxRessources")) fichierAffectation1CCmaxSommeRessources = fichier;
        cout << fichier.toStdString() << endl;

        if(fichier.contains("resolutionMip1")) fichierSolutionOptimale = fichier;
        cout << fichier.toStdString() << endl;
    }

    std::ifstream f(fichierSolutionOptimale.toStdString());

    if (!f)
    {
        cout << fichierSolutionOptimale.toStdString() <<" invalid file" << endl;
    }

    string line;

    vector<vector<int>> solution;
    vector<vector<double>> tempsSolution;

    vector <int> solutionOptimale;
    vector<double> tempsSolutionOptimale;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        int optimal = ligneOptimale.split("=")[1].toInt();
        solutionOptimale.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsSolutionOptimale.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierSolutionOptimale.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    solution.push_back(solutionOptimale);
    tempsSolution.push_back(tempsSolutionOptimale);

    f.open(fichierAffectation1CCmaxSommeRessources.toStdString());

    vector <int> solutionAffectation1CCmaxSommeRessources;
    vector<double> tempsAffectation1CCmaxSommeRessources;

    while(getline(f,line)) {
        cout << line << endl ;
        getline(f,line);

        getline(f,line);
        QString ligneOptimale = QString::fromStdString(line);
        int optimal = ligneOptimale.split("=")[1].toInt();
        solutionAffectation1CCmaxSommeRessources.push_back(optimal);

        getline(f,line);
        QString tempsEcoule = QString::fromStdString(line);
        tempsAffectation1CCmaxSommeRessources.push_back(tempsEcoule.split(":")[1].toDouble());

        getline(f,line);
        for (int i = 0; i < fichierSolutionOptimale.split("/")[4].toInt() ; i++){
            getline(f,line);
        }

        getline(f,line);
        for (int i = 0; i < optimal ; i++){
            getline(f,line);
        }
    }

    f.close();

    solution.push_back(solutionAffectation1CCmaxSommeRessources);
    tempsSolution.push_back(tempsAffectation1CCmaxSommeRessources);

    for(int i = 0; i < solutionOptimale.size(); i++){
        cout << solutionOptimale.at(i) << endl;
    }

    for(int i = 0; i < tempsSolutionOptimale.size(); i++){
        cout << tempsSolutionOptimale.at(i) << endl;
    }

    for(int i = 0; i < solutionAffectation1CCmaxSommeRessources.size(); i++){
        cout << solutionAffectation1CCmaxSommeRessources.at(i) << endl;
    }

    for(int i = 0; i < tempsAffectation1CCmaxSommeRessources.size(); i++){
        cout << tempsAffectation1CCmaxSommeRessources.at(i) << endl;
    }

    emit finished();
}
